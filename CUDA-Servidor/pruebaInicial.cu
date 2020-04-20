/* Tarea 3 Seminario de Introducción a openMP-MPI y CUDA
*	Muñiz Patiño, Andrea Fernanda
*	Abril, Sem 2020-2 Semestre del coronavirus
*/
#include "cuda_runtime.h"
#include<stdio.h>
#include<stdlib.h>
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
	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; i < tam; i++)
		{
			printf("%d, ",mat[mat*tam+i][mat* tam +j]);
		}
		printf("\n");
	}
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
	int* dev_a; //nullptr es null en puntero
	int* dev_b;
	int* dev_res;

	//Copiando en la memoria GPU las matrices. 
    cudaMalloc((void**)&dev_a, size * sizeof(int));
    cudaMalloc((void**)&dev_b, size * sizeof(int));
    cudaMalloc((void**)&dev_res, size * sizeof(int));

    //Copiando los valores de las matrices al GPU desde host
    cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_res, res, size * sizeof(int), cudaMemcpyHostToDevice);
}

/* Metodo que extrae del GPU el resultado calculado
* @res puntero de donde se guardará el resultado de la operación
* @size tamaño del parametro res
*/
__host__ void extractFromCuda(int* res, int size){
	//Dirección destino, dir. origen, tamaño del dato, de donde a donde
    cudaMemcpy(res, dev_res, size * sizeof(int), cudaMemcpyDeviceToHost);
	
	//Libera memoria 
	cudaFree(dev_res);
	cudaFree(dev_a);
	cudaFree(dev_b);
}

int main(int argc, char const *argv[])
{
	printf("Se ejecutara un ejemplo\n");
	const int arraySize = 3;
	//Matrices
    const int a[arraySize][arraySize] = {{1,2,3},{3,2,1},{3,1,2}};
    const int b[arraySize][arraySize] = {{4,5,6,},{6,5,4},{5,4,6}};
    //Resultado
    int res[arraySize][arraySize] = {{0}};

    //Se hace una copia de host a device
    addOnCuda(arraySize, a, b, res);

    //Se hacen los calculos en GPU----------------

    //Se sincronizan los hilos para cuando terminen
    cudaDeviceSynchronize();

    //Se copia el resultado del device al host
    extractFromCuda(res, arraySize);

    //Se presentan los resultados de la operacion
    ImprimeMatriz(arraySize, a);
    operacion(2);
    ImprimeMatriz(arraySize, b);

    cudaDeviceReset();
	return 0;
}