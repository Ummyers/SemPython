/* Tarea 3 Seminario de Introducción a openMP-MPI y CUDA
*	Muñiz Patiño, Andrea Fernanda
*	Abril, Sem 2020-2 Semestre del coronavirus
*/
#include "cuda_runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>
#include <sys/time.h>

/* Metodo ejecutado en el GPU que suma matrices
*	@m matriz a
*	@n matriz b
*	@p matriz c que contiene el resultado
*	@size el tamaño de la matriz
*/
__global__ void matrixSum(int* a,int* b, int* c, int size)
{
	// printf("ERROR en global\n");
	int pos = threadIdx.x;
	if(pos<size*size){
		c[pos] = a[pos] + b[pos];
	}
}

/* Metodo ejecutado en el GPU que multiplica matrices
*	@m matriz a
*	@n matriz b
*	@p matriz c que contiene el resultado
*	@size el tamaño de la matriz
*/
__global__ void matrixMult(int* m,int* n, int* p, int size)
{
	int row=blockIdx.y*blockDim.y+threadIdx.y;
	int col=blockIdx.x*blockDim.x+threadIdx.x;
	int p_sum;

	for(int i=0;i<size;i++){
		p_sum += m[row*size+i] * n[col*size+i];
	}
	p[row*size+col]=p_sum;
}

/* Metodo que inicializa las matrices con valores aleatorios
*	@a Matriz
*	@b Matriz
*	@n cantida de elementos de la matriz
*/

__host__ void inicializarMatriz(int* a, int* b, int n)
{
	srand(5);
	printf("Valor de tam: %d \n", n );
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			a[i*n+j]=rand() % 10 +1;
			b[i*n+j]=rand() % 10 +1;
		}
	}	
}

/*
* Método que imprime una matriz de tamaño @tam
* Un metodo tipo Host indica que solo puede ser llamado por
*  el mismo host (CPU)
*/
 __host__ void ImprimeMatriz(int tam, int* mat)
{
	for (int i = 0; i< tam; i++){
		for (int j = 0; j< tam; j++){
			printf("%d, ", mat[i*tam +j]);
		}
		printf(" \n");
	}
}

//Metodo que imprime solo la operación que se esta haciendo

__host__ void operacion(int a)
{
	switch(a){
		case 1:
			printf("*\n");
		break;
		case 2:
			printf("+\n");
		break;
	}
}

/* Metodo que hace copia de memoria del host al device y viceversa
*	@size tamaño del las matrices
*	@a puntero a primera matriz
* 	@b putero a segunda matriz
*	@res puntero a matriz solución
*	@op integer que indica que operación hará
*/

__host__ void addOnCuda(int size, const int* a, const int* b, int* res, int oper, int dim)
{
	//Declarando las variables del GPU
	int* dev_a = nullptr; //nullptr es null en puntero
	int* dev_b = nullptr;
	int* dev_res = nullptr;

	//Copiando en la memoria GPU las matrices. 
    cudaMalloc((void**)&dev_a, size);
    cudaMalloc((void**)&dev_b, size);
    cudaMalloc((void**)&dev_res, size);

    //Copiando los valores de las matrices al GPU desde host
    cudaMemcpy(dev_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, size, cudaMemcpyHostToDevice);
	
    //Dependiendo de la operación es la creación de Hilos y bloques

    //Para obtener el tiempo
    float tim = 0.0;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    //Se hacen los calculos en GPU----------------
    cudaEventRecord(start);
	
    //Opción de la multiplicación
    if(oper==1){
    	int threads_per_block = (int) dim/2;
    	int n = dim*dim; 
		dim3 block_size(threads_per_block,threads_per_block);
		dim3 grid_size(n / block_size.x, n / block_size.y);
		// llamar el kernel
		matrixMult<<< grid_size,block_size >>>(dev_a,dev_b,dev_res,dim);
   	//Opción de suma
   	}else{
   		int hilos = dim*dim;
		matrixSum<<<1,hilos>>>(dev_a,dev_b,dev_res,dim);
   	}

    //Se sincronizan los hilos para cuando terminen
    cudaDeviceSynchronize();

   //Se termino de hacer los calculos
    cudaEventRecord(stop);
    cudaEventElapsedTime(&tim, start, stop);
    printf("El tiempo tomado por CUDA el algoritmo es de: %lf\n", tim);

    //Dirección destino, dir. origen, tamaño del dato, de donde a donde
    cudaMemcpy(res, dev_res, size, cudaMemcpyDeviceToHost);
}

int main(int argc, char const *argv[])
{
	int tamMatriz, opera;
	//matrices
	int* a;
	int* b;
	int* res;
	printf ("¿De qué tamaño es la matriz? \n");
	scanf ("%d", &tamMatriz);

	printf("¿Deseas multiplicar (1) o sumar (2) la matriz con valores aleatorios?\n");
	scanf("%d", &opera);

	//Validamos que el usuario ingrese una opción valida. 
	if((opera!=1)&&(opera!=2))
	{
		printf("Por favor indica un numero valido, 1 o 2.\n");
		return 0;
	}

	size_t bytes = tamMatriz*tamMatriz*sizeof(int);

	//Memoria para matrices
	a = (int*)malloc(bytes);
	b = (int*)malloc(bytes);
	res = (int*)malloc(bytes);

	//Llenamos la matriz
	inicializarMatriz(a, b, tamMatriz);

    //Para obtener el tiempo
    struct timeval inicio, fin;//nos permiten medir el tiempo de ejecucion
	gettimeofday(&inicio, NULL);//guarda el tiempo al inicio del programa
	int tiempo;
   
   //Se hacen los calculos en GPU----------------
    addOnCuda(bytes, a, b, res, opera, tamMatriz);
    
   //Se termino de hacer los calculos
    gettimeofday(&fin, NULL); //guarda el tiempo al final del programa
	tiempo = (fin.tv_sec - inicio.tv_sec)* 1000000 + (fin.tv_usec - inicio.tv_usec);
   

    //Se presentan los resultados de la operacion
    ImprimeMatriz(tamMatriz, a);
    operacion(opera);
    ImprimeMatriz(tamMatriz, b);
    printf("=\n");
    ImprimeMatriz(tamMatriz, res);
    //ImprimeMatriz(tamMatriz, res);

    printf("El tiempo tomado por el sistema del algoritmo es de:: %lf\n", tiempo);

    cudaDeviceReset();
	return 0;
}