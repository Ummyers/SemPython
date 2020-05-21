#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

// Kernel (funcion) que se invoca desde el Host y se ejecuta en un dispositivo
__global__ void suma_vectores(int* c, const int* a, const int* b, int size) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < size) {
        c[i] = a[i] + b[i];
    }
}

// Funcion auxiliar que encapsula la suma con CUDA
void suma_CUDA(int* c, const int* a, const int* b, int tam) {
    int* dev_a = nullptr;
    int* dev_b = nullptr;
    int* dev_c = nullptr;

    // Reservamos espacio de memoria para los datos, 2 de entrada y una salida
    cudaMalloc((void**)&dev_c, tam * sizeof(int));
    cudaMalloc((void**)&dev_a, tam * sizeof(int));
    cudaMalloc((void**)&dev_b, tam * sizeof(int));

    // Copiamos los datos de entrada desde el CPU a la memoria del GPU
    cudaMemcpy(dev_a, a, tam * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, tam * sizeof(int), cudaMemcpyHostToDevice);

    // Se invoca al kernel en el GPU con un hilo por cada elemento
    // 2 es el numero de bloques y (tam + 1)/2 es el numero de hilos en cada bloque
    suma_vectores<<<2, (tam + 1) / 2>>>(dev_c, dev_a, dev_b, tam);
    
    // Esta funcion espera a que termine de ejecutarse el kernel y 
    // devuelve los errores que se hayan generado al ser invocado
    cudaDeviceSynchronize();

    // Copiamos el vector resultado de la memoria del GPU al CPU
    cudaMemcpy(c, dev_c, tam * sizeof(int), cudaMemcpyDeviceToHost);

    // Se libera la memoria empleada
    cudaFree(dev_c);
    cudaFree(dev_a);
    cudaFree(dev_b);
}

// Funcion principal que sirve de prueba para el algoritmo
int main(int argc, char** argv) {
    
    // Datos de entrada para nuestra funcion
    const int tam = 5;
    const int a[tam] = {  1,  2,  3,  4,  5 };
    const int b[tam] = { 10, 20, 30, 40, 50 };
    int c[tam] = { 0 };

    // Se llama a la funcion que encapsula el Kernel
    suma_CUDA(c, a, b, tam);

    // Mostramos resultado
    printf("{1, 2, 3, 4, 5} + {10, 20, 30, 40, 50} = {%d, %d, %d, %d, %d}\n", c[0], c[1], c[2], c[3], c[4]);

    // Se liberan recursos
    cudaDeviceReset();

    return 0;
}
