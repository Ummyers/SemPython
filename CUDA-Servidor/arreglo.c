#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	
	int tamMatriz;
	//matrices
	int* a;
	int* b;
	int* res;
	printf ("¿De qué tamaño es la matriz? \n");
	scanf ("%d", &tamMatriz);

	size_t bytes = tamMatriz*tamMatriz*sizeof(int);

	//int numElem = tamMatriz*tamMatriz;

	//Memoria para matrices
	a = (int*)malloc(bytes);
	b = (int*)malloc(bytes);
	res = (int*)malloc(bytes);

	printf("Rellenando \n");
	for(int i=0;i<tamMatriz*tamMatriz;i++){
		// for(int j=0;j<tamMatriz;j++){
			a[i]=rand() % 1024;
			b[i]=rand() % 1024;
		// }
	}	

	printf("Tratando de imprimir\n");

	for (int i = 0; i<tamMatriz; i++){
		for (int j = 0; j<tamMatriz; j++){
			printf("%d, ", a[i*tamMatriz + j]);
		}
		printf(" \n");
	}

for (int i = 0; i<tamMatriz*tamMatriz; i++){
			res[pos] = a[pos] + b[pos];

			printf("%d, ", a[i*tamMatriz + j]);
		}
		printf(" \n");
	}
		c[pos] = a[pos] + b[pos];


	return 0;
}