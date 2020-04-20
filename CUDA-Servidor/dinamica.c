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