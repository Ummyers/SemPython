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
/* Metodo que dados los limites de una doble integral calcula la 
*  suma de Monte Carlo para la masa 
*
*/

void monteCarlo(int q, int w, int e, int r){

	double a = (double) q;
	double b = (double) w;
	double c = (double) e;
	double d = (double) r;

	double* equis = generadorAleatorios(0.0,1.0);
	double* yes = generadorAleatorios(0.0,1.0);
	//imprimeAleatorios(equis);
	double suma; //Guarda la suma total
	double iz = ((b-a)*(d-c))/N;

	for(int i =1; i<=N; i++){
		suma = suma + equis[i-1] + (2*yes[i-1]);
	}
	printf("Izquierdo: %lf\n", iz );
	suma = iz * suma;
	printf(" La aproximación es: %lf\n", suma);
}

 int main(int argc, char const *argv[])
{
	monteCarlo(0,1,0,1);
	
	return 0;
}