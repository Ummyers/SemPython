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

//multiplicacion de matrices basica 
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
/*
* Método que imprime una matriz de tamaño @tam
Un metodo tipo Host indica que solo puede ser llamado por
el mismo host (CPU)
*/
 __host__ void ImprimeMatriz(int tam, int* mat)
{
	printf("LOL\n");
// 	for (int i = 0; i < tam; i++)
// 	{
// 		for (int j = 0; j < tam; i++)
// 		{
// 			printf("LOL, ");
// 		}
// 		printf("\n");
// 	}
}

//Metodo que imprime solo la operación que se esta haciendo

__host__ void operacion(int a)
{
	switch(a){
		case 1:
			printf("+\n");
		break;
		case 2:
			printf("*\n");
		break;
	}
}

/* Metodo que hace copia de memoria del host al device 
*	@size tamaño del las matrices
*	@a puntero a primera matriz
* 	@b putero a segunda matriz
*	@res puntero a matriz solución
*/

__host__ void addOnCuda(int size, const int* a, const int* b, int* res)
{
	//Declarando las variables del GPU
	int* dev_a = nullptr; //nullptr es null en puntero
	int* dev_b = nullptr;
	int* dev_res = nullptr;

	//Copiando en la memoria GPU las matrices. 
    cudaMalloc((void**)&dev_a, size * sizeof(int));
    cudaMalloc((void**)&dev_b, size * sizeof(int));
    cudaMalloc((void**)&dev_res, size * sizeof(int));

    //Copiando los valores de las matrices al GPU desde host
    cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_res, res, size * sizeof(int), cudaMemcpyHostToDevice);

    //Dirección destino, dir. origen, tamaño del dato, de donde a donde
    cudaMemcpy(res, dev_res, size * sizeof(int), cudaMemcpyDeviceToHost);
	
	//Libera memoria 
	cudaFree(dev_res);
	cudaFree(dev_a);
	cudaFree(dev_b);
}

int main(int argc, char const *argv[])
{
	int tamMatriz;
	//matrices
	int* a;
	int* b;
	int* res;
	printf ("¿De qué tamaño es la matriz?");
	scanf ("%d", &tamMatriz);

	size_t bytes = tamMatriz*tamMatriz*sizeof(int);
	tamMatriz = tamMatriz * tamMatriz;

	//Memoria para matrices
	a = (int*)malloc(bytes);
	b = (int*)malloc(bytes);
	res = (int*)malloc(bytes);

    //Para obtener el tiempo
    float tim = 0;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);


    //Se hace una copia de host a device
    addOnCuda(bytes, a, b, res);

    //Se hacen los calculos en GPU----------------
    cudaEventRecord(start);


    //Se sincronizan los hilos para cuando terminen
    cudaDeviceSynchronize();

   //Se termino de hacer los calculos
    cudaEventRecord(stop);
    cudaEventElapsedTime(&tim, start, stop);
    
    //Se presentan los resultados de la operacion
    ImprimeMatriz(tamMatriz, a);
    operacion(2);
    ImprimeMatriz(tamMatriz, b);
    printf("=\n");
    ImprimeMatriz(tamMatriz, res);

    printf("El tiempo tomado por el algoritmo es de: %lf\n", tim);
    cudaDeviceReset();
	return 0;
}