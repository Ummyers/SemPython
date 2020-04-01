#include<stdio.h>
#include<mpi.h>
#include <stdlib.h>  

#define N 100 


/* Metodo que genera numeros aleatorios entre a y b
*	@param double a es el limite inferior de la integral
* 	@param double b es el limite superior de la integral 
*	@return regresa un arreglo de tamaño N con números aleatorios
en el intervalo [a,b]
*/
double * generadorAleatorios(double a, double b){
	static double numAle[N];
	for (int i = 0; i< N; i++){
				numAle[i] = (double) rand()/RAND_MAX*b + a;
	}
	return numAle;
}

void imprimeAleatorios(double array[]){

	for (int i = 0; i< N; i++){
			printf("%lf,",array[i]);
				
	}

}
 int main(int argc, char const *argv[])
{
	double* arreglo = generadorAleatorios(0.0,1.0);
	imprimeAleatorios(arreglo);
	return 0;
}