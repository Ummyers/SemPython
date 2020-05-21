#include<stdio.h>
#include<mpi.h>
#define size 100

int my_id,nproc,a[size],i,tag=99,first,last,chunksize;
double sum=0.0,psum=0.0;
MPI_Status status;
int main(int argc,char** argv)
{

MPI_Init(&argc,&argv);

MPI_Comm_size(MPI_COMM_WORLD,&nproc);
MPI_Comm_rank(MPI_COMM_WORLD,&my_id);

/* rellena el vector a*/
if(my_id==0) for(i=0;i<size;i++)a[i]=i+1;

/* Difunde el vector a*/

MPI_Bcast(a,size,MPI_INT,0,MPI_COMM_WORLD);

/* determina numeros a sumar*/

chunksize=size/nproc;

if(my_id==nproc-1){
	first=(nproc-1)*chunksize;
	last=size-1;
}
else{
	first=my_id*chunksize;
	last=(my_id+1)*chunksize-1;

}

/* computa la suma parcial */
for(i=first;i<=last;i++){
	psum=psum+a[i];
}

/* Hacer la reduccion de las sumas parciales para obtener la suma total */

MPI_Reduce(&psum,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

if(my_id==0) printf("Suma : %10.0f\n",sum);

MPI_Finalize();


return 0;
}
