#include <stdio.h>
//#include <omp.h>
#include <math.h>

//double start = omp_get_wtime();

int main(int argc, char ** argv)
{
    if(argc < 2){
        printf("No indicaste el nùmero de precision");
        exit(1);
    }
    
    double suma, x, pi, error;
    int delta = argv[1] *; //Presicion delta de equis
        //No se si es la misma N y n
    for(int ini = 1; i<n; i++){
        x = delta * i;
        suma = sqrt(1-x*x) /n;
        
    }
    
    pi = suma * 4;
    
    //Para calcular el error
    error = acos(-1.0); // menos pi obtenida entre nuestra precision


    printf("El tiempo fue de: %d ", start);
    return 0;
}
