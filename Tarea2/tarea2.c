#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>  
#include <math.h>

#define N 1000

/* Declaracion de funciones */
double * generadorAleatorios(double a, double b);
void monteCarlo(int q, int w, int e, int r, double (*funcion)());
double masa_1(double x, double y);
double masa_2(double x, double y);
void monteCarloCentro(int q, int w, int e, int r, double (*funcion)());
/*--------------------------*/

int main(int argc, char const *argv[])
{
	monteCarlo(0,1,0,1,masa_1); 
	monteCarlo(-1,1,-1,1,masa_2); 
	return 0;
}

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
void monteCarlo(int q, int w, int e, int r, double (*funcion)()){

	double a = (double) q;
	double b = (double) w;
	double c = (double) e;
	double d = (double) r;

	double* equis = generadorAleatorios(a,b);
	double* yes = generadorAleatorios(c,d);
	// imprimeAleatorios(equis);
	// imprimeAleatorios(yes);

	double suma; //Guarda la suma total
	double iz = ((b-a)*(d-c))/N;

	for(int i =1; i<=N; i++){
		suma = suma + funcion(equis[i-1],yes[i-1]);	// suma = suma + masa_1(equis[i-1],yes[i-1]);
	}
	// printf("Izquierdo: %lf\n", iz );
	suma = iz * suma;
	printf(" La aproximación es: %lf\n", suma);
}

/* Metodo que dados los limites de una doble integral calcula la 
*  suma de Monte Carlo para el centro de masa de x o y 
*/
void monteCarloCentro(int q, int w, int e, int r, double (*funcion)()){

	double a = (double) q;
	double b = (double) w;
	double c = (double) e;
	double d = (double) r;

	double* equis = generadorAleatorios(a,b);
	double* yes = generadorAleatorios(c,d);
	imprimeAleatorios(equis);
	imprimeAleatorios(yes);

	double suma; //Guarda la suma total
	double iz = ((b-a)*(d-c))/N;

	for(int i =1; i<=N; i++){
		suma = suma + funcion(equis[i-1],yes[i-1]);	// suma = suma + masa_1(equis[i-1],yes[i-1]);
	}
	// printf("Izquierdo: %lf\n", iz );
	suma = (1/1.5)* suma;
	printf(" La aproximación es: %lf\n", suma);
}


//greetMorning
double masa_1(double x, double y){
	double evalu = x + (2.0*y);
}

double masa_2(double x, double y){
	double evalu = sin(sqrt(pow(x,2)+pow(y,2)));
}