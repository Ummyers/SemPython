#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>  
#include <math.h>

#define N 10000

/* Declaracion de funciones */
double * generadorAleatorios(double a, double b);
void monteCarlo(int q, int w, int e, int r, double (*funcion)());
/*Funciones de masa*/
double masa_1(double x, double y);
double masa_2(double x, double y);
/*Funciones de centro de masa */

double centro_1x(double x, double y);
double centro_1y(double x, double y);
double centro_2x(double x, double y);
double centro_2y(double x, double y);

void monteCarloCentro(int q, int w, int e, int r, double div, double (*funcion)());
/*--------------------------*/

int main(int argc, char const *argv[])
{
	MPI_Init(0,0);
	double t1,t2;

	//Tiempo inicial
    t1 = MPI_Wtime();

	int n = N;
	printf("Con %d puntos los resultados son:\n", n);

	printf("---Masa 1:\n");
	monteCarlo(0,1,0,1,masa_1); 
	printf("El centro de masa en x es:\n");
	monteCarloCentro(0,1,0,1,1.5,centro_1x);
	printf("El centro de masa con y es:\n");
	monteCarloCentro(0,1,0,1,1.5,centro_1y);

	printf("---Masa 2:\n");
	monteCarlo(-1,1,-1,1,masa_2); 
	printf("El centro de masa en x es:\n");
	monteCarloCentro(-1,1,-1,1,2.6635,centro_2x);
	printf("El centro de masa con y es:\n");
	monteCarloCentro(-1,1,-1,1,2.6635,centro_2y);
	
	//Tiempo final
	t2 = MPI_Wtime();
	printf("El tiempo del programa es: %lf\n", t2-t1);

    MPI_Finalize( );

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

	if(a < 0){
		for (int i = 0; i< N; i++){
				numAle[i] = drand48() * (b-a) - b; 
		}
	}else{
		for (int i = 0; i< N; i++){
				numAle[i] = (double) rand()/RAND_MAX*b + a;
		}
	}

	
	return numAle;
}
/* Metodo auxiliar para ver el comportamiento de los
*	números aleatorios creados por rand
*/
void imprimeAleatorios(double array[]){
	for (int i = 0; i< N; i++){
			printf("%lf,",array[i]);		
	}
}

/* Metodo que dados los limites de una doble integral calcula la 
*  suma de Monte Carlo para la masa que es pasada como last parametro
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
	double izq = ((b-a)*(d-c))/N;

	for(int i =1; i<=N; i++){
		suma = suma + funcion(equis[i-1],yes[i-1]);	// suma = suma + masa_1(equis[i-1],yes[i-1]);
	}
	// printf("Izquierdo: %lf\n", iz );
	suma = izq * suma;
	printf(" La aproximación es: %lf kg\n", suma);
	suma = 0.0;
	izq = 0.0;
}

/* Metodo que dados los limites de una doble integral calcula la 
*  suma de Monte Carlo para el centro de masa de x o y 
*/
void monteCarloCentro(int q, int w, int e, int r, double div, double (*funcion)()){

	double a = (double) q;
	double b = (double) w;
	double c = (double) e;
	double d = (double) r;

	double* equis = generadorAleatorios(a,b);
	double* yes = generadorAleatorios(c,d);
	// imprimeAleatorios(equis);
	// imprimeAleatorios(yes);
	double suma; //Guarda la suma total
	double M = 1/div;
	// printf("M = %lf \n", M);
	double izq = ((b-a)*(d-c))/N;

	for(int i =1; i<=N; i++){
		suma = suma + funcion(equis[i-1],yes[i-1]);	// suma = suma + masa_1(equis[i-1],yes[i-1]);
	}
	// printf("Izquierdo: %lf\n", izq );
	suma = M*izq*suma;
	printf("La aproximación con m %lf es: %lf\n",izq, suma);
	suma = 0.0;
	izq = 0.0;
	M = 0.0;
}

//greetMorning
double masa_1(double x, double y){
	double evalu = x + (2.0*y);
}

double masa_2(double x, double y){
	// double evalu = sin(sqrt(pow(x,2)+pow(y,2)));
	double evalu = sin(sqrt(x*x+y*y));
}

double centro_1x(double x, double y){
	double evalu = x*(pow(x,2) + (2*x*y));
}

double centro_1y(double x, double y){
	double evalu = y*((x+y) + (2*y*y));
}

//Dummie?
double centro_2x(double x, double y){
	double evalu = sqrt((x*x) + (y*y)); 
    return -1* x * sin(evalu);
}

double centro_2y(double x, double y){
	double evalu = sqrt((x*x) + (y*y));
	return -1* y * sin(evalu);
}