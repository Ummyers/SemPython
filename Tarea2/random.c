#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    double random_value;

    //srand ( time ( NULL));

    random_value = (double)rand()/RAND_MAX*2.0-1.0;//float in range -1 to 1

    printf ( "%f\n", random_value);

    return 0;
}