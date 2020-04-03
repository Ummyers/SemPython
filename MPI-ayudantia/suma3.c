#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#define size 100

int my_id,nproc,i,tag=99,first,chunksize;
int a[size],b[size];
double sum,psum;
MPI_Status status;

int main(int argc,char** argv)
{

MPI_Init(&argc,&argv);

MPI_Comm_size(MPI_COMM_WORLD,&nproc);
MPI_Comm_rank(MPI_COMM_WORLD,&my_id);

chunksize=size/nproc;

if(chunksize*nproc!=size){
	if(my_id==0)
		printf("'size(%d)' debe ser divisible por 'nproc(%d)'\n",size,nproc);
	MPI_Finalize();
	exit(1);
}

/* rellena el vector */
if(my_id==0) for(i=0;i<size;i++)a[i]=i+1;

/* distribuye el vector */
MPI_Scatter(a,chunksize,MPI_INT,b,chunksize,MPI_INT,0,MPI_COMM_WORLD);

/* calculen las sumas parciales*/

psum=0.0;

for(i=0;i<chunksize;i++){
	psum=psum+b[i];
}

/* hacer la reduccion de las sumas parciales para obtener la suma total*/

MPI_Reduce(&psum,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

if(my_id==0) printf("Suma : %10.0f\n",sum);


MPI_Finalize();


return 0;
}
