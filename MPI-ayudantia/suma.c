#include<stdio.h>
#include<mpi.h>
#define size 100

int my_id,nproc,i,tag=99,first,chunksize,flag;
int a[size];
double sum,psum;
MPI_Status status;
//Tiempo
double startime, endtime, maxTime;
int main(int argc,char** argv)
{

	startime = MPI_Wtime();
	MPI_Init(&argc,&argv);


	MPI_Comm_rank(MPI_COMM_WORLD,&my_id);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);

	
	/* calcula el tamanio de las partes a enviar*/
	chunksize=size/nproc;
	if(my_id==nproc-1){
		/* rellena el vector a*/
		for(i=0;i<size;i++)a[i]=i+1;
		
		/* envia las partes a los otros*/
		for(i=0;i<nproc-1;i++){
			first=i*chunksize;
			MPI_Send(&a[first],chunksize,MPI_INT,i,tag,MPI_COMM_WORLD);

		}
		/* determina lo que debo sumar yo (nproc-1)*/
		first=my_id*chunksize;
		chunksize=size-1;
		/* efectua mi suma parcial*/
		sum=0.0;
		for(i=first;i<=chunksize;i++)sum=sum+a[i];

		/* obtener las sumas parciales y calcula la total*/
		
		for(i=0;i<nproc-1;i++){
			MPI_Recv(&psum,1,MPI_DOUBLE,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD,&status);
			printf("Respondio %d - envio %10.0f\n",status.MPI_SOURCE,psum);
			sum=sum+psum;
		}

		printf("Resultado de la suma = %10.0f\n",sum);
	}

	else{
		/* recibe mi parte */
		MPI_Recv(&a,chunksize,MPI_INT,nproc-1,tag,MPI_COMM_WORLD,&status);
		
		/* efectua mi suma parcial */
		psum=0.0;
		for(i=0;i<chunksize;i++)psum=psum+a[i];

		/* devuelve mi suma parcial a (nproc-1) */
		MPI_Send(&psum,1,MPI_DOUBLE,nproc-1,tag,MPI_COMM_WORLD);
	}
	endtime = MPI_Wtime();

	MPI_Finalize();
/*Imprime los tiemps de los n procesos...*/
	double time = endtime - startime;
	if (time > maxTime)
		maxTime = time;

	printf("El tiempo del programa es: %lf\n", maxTime);

	
}
