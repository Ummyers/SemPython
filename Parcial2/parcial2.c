/*
*	Andrea Fernanda Muñiz Patiño 311175318
Al principio quise sacar la aproximación de una esfera
pero me metio un poco de ruido el cambio de coordenadas
Solo puse una función equis de nada especifico.
Para compilar es 
$mpicc parcial2.c -lm -o exe
Ejecutar
$ ./exe 
*/

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>  
#include <math.h>

//Exactitud del programa
#define N 10000

/* Declaracion de funciones */
double * generadorAleatorios(double a, double b);
void monteCarlo(int q, int w, int e, int r,int t, int u, double (*funcion)());
double funcion(double x, double y, double z);


int main(int argc, char const *argv[])
{
	printf("Parcial 2...\n");
	monteCarlo(0,1,0,1,0,1,funcion);

	return 0;
}

//Función a evaluar
double funcion(double x, double y, double z){
	double evalu = sqrt((x*x) + (y*y) + (z*z));
	return 1* y * sin(evalu);
}

/* Metodo que genera numeros aleatorios entre a y b
*	@param double a es el limite inferior de la integral
* 	@param double b es el limite superior de la integral 
*	@return regresa un arreglo de tamaño N con números aleatorios
en el intervalo [a,b]
*/
double* generadorAleatorios(double a, double b){
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

/* Metodo que dados los limites de una triple integral calcula la 
*  suma de Monte Carlo para la masa que es pasada como last parametro
*
*/
void monteCarlo(int q, int w, int e, int r, int t, int u, double (*funcion)()){
	MPI_Init(0,0);

	double startime,endtime, time, maxTime;

	startime = MPI_Wtime();

	int my_id, nproc,chucksize;
	double* equis;
	double* yes;
	double* zetas;

	double tsuma, suma, izq;

	MPI_Status status;

	//Los usa el MPI_Scatter
	double x[N],y[N],z[N];

	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_id);	

	chucksize = N/nproc;

	//Rellenando el vector
	if(my_id==0){
		double a = (double) q;
		double b = (double) w;
		double c = (double) e;
		double d = (double) r;
		double e = (double) t;
		double f = (double) u;

		suma = 0.0; //Guarda la suma total
		izq = ((b-a)*(d-c)*(f-e))/N;
		equis = generadorAleatorios(a,b);
		yes = generadorAleatorios(c,d);
		zetas = generadorAleatorios(e,f);
	}

	tsuma = 0.0; //Se inicializa la variable para cada proceso

	MPI_Scatter(equis,chucksize,MPI_INT,x,chucksize,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Scatter(yes,chucksize,MPI_INT,y,chucksize,MPI_DOUBLE,0,MPI_COMM_WORLD);
	//MPI_Scatter(zetas,chucksize,MPI_DOUBLE,z,chucksize,MPI_INT,0,MPI_COMM_WORLD);


	for(int i =1; i<=chucksize; i++){
		tsuma = tsuma + funcion(x[i-1],y[i-1],z[i-1]);	
	}

	MPI_Reduce(&tsuma,&suma,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	
	endtime = MPI_Wtime();

	time = endtime - startime;
	if (time > maxTime)
		maxTime = time;

	if(my_id==0){
		suma = izq * suma;

		printf(" La aproximación es: %lf \n", suma);
		printf("El tiempo del programa es: %lf\n", maxTime);

	}
	MPI_Finalize();
}
