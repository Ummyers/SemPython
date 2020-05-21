#include<stdio.h>
#include<stdlib.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>

__host__ float barra(float* x, int n)
{
	int i;
	float xb = 0.0;
	for (i = 0;i < n;i++) {
		xb += x[i];
	}
	xb = xb / n;

	return xb;
}

__global__ void Saxx_device(float* x, float* c, float xb, int n)
{
	int i = threadIdx.x;
	if (i < n)
		c[i] = (x[i] - xb) * (x[i] - xb);

}

__global__ void Saxy_device(float* x, float* y, float* d, float xb, float yb, int n)
{
	int i = threadIdx.x;

	if (i < n)
		d[i] = (x[i] - xb) * (y[i] - yb);

}

int main()
{

	// cuerpo de las variables del host
	float* x;
	float* y;
	float h_xb;
	float h_yb;
	float* h_saxy;
	float* h_saxx;
	float sxx;
	float sxy;
	int size;
	// cuerpo de las variables del device
	float* c;
	float* d_saxx;
	float* d_saxy;
	float* d;
	float* d_x;
	float* d_y;


	// numero de elementos

	printf("ingrese\n");
	scanf("%d", &size);

	// alocamos las variables en el host

	x = (float*)malloc(sizeof(float) * size);
	y= (float*)malloc(sizeof(float) * size);

	// llenamos los vectores
	for (int i = 0;i < size;i++) {

		x[i] = rand() + (float)i * 0.01;
		y[i] = rand() - (float)i * 0.01;
	}

	// llamamos a barra para calcular el promedio

	h_xb= barra(x, size);
	h_yb= barra(y, size);

	// alocamos memoria en el device 

	cudaMalloc((void**)&c, sizeof(float) * size);
	cudaMalloc((void**)&d, sizeof(float) * size);
	cudaMalloc((void**)&d_x, sizeof(float) * size);
	cudaMalloc((void**)&d_y, sizeof(float) * size);

	// pasando el contenido al device

	cudaMemcpy(d_x, x, sizeof(float) * size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_y, y, sizeof(float) * size, cudaMemcpyHostToDevice);



	// invocamos los kernel

	Saxx_device <<< 1, size >>> (d_x,c, h_xb, size);
	Saxy_device <<< 1, size >>> (d_x,d_y,d, h_xb, h_yb, size);


		// alocamos en el host

	h_saxx = (float*)malloc(sizeof(float) * size);
	h_saxy = (float*)malloc(sizeof(float) * size);

	// obtenemos del device los elementos

	cudaMemcpy(h_saxx, c, sizeof(float) * size, cudaMemcpyDeviceToHost);

	cudaMemcpy(h_saxy, d, sizeof(float) * size, cudaMemcpyDeviceToHost);


	//  llamamos a barra
	sxx = barra(h_saxx, size);
	sxy = barra(h_saxy, size);

	// declaramos variables de regresion
	float beta1G, beta0G;

	beta1G = sxy / sxx; // coeficiente beta 1 gorro
	beta0G = h_xb * (-beta1G) + h_yb ;	// coeficiente beta 0 gorro
	printf(" y = %f + %f x", beta0G, beta1G);
	return 0;
}