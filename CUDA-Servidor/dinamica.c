#include <stdio.h>
#include <stdlib.h>
int main ()
{
	int numeroElementos;
	int* vector;

	printf ("¿Cuántos elementos quieres? ");
	scanf ("%d", &numeroElementos);

	vector = (int*)malloc(numeroElementos*sizeof(int));
	if (vector==NULL)
	{
		perror("Problemas reservando memoria");
		exit (1);
	}

	// trabajamos con el vector

	// lo liberamos
	free (vector);

	return 0;
}

// printf("Se ejecutara un ejemplo\n");
// 	const int arraySize = 3;
// 	//Matrices
//     const int a[arraySize][arraySize] = {{1,2,3},{3,2,1},{3,1,2}};
//     const int b[arraySize][arraySize] = {{4,5,6,},{6,5,4},{5,4,6}};
//     //Resultado
//     int res[arraySize][arraySize] = {{0}};
