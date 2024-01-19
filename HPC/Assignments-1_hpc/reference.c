#include <omp.h>
 
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char* argv[])
{
 
    // Beginning of parallel region
    printf("%d",omp_get_max_threads());
    #pragma omp parallel
    {
 
        printf("Hello World... from thread = %d\n",
               omp_get_thread_num());
    }
    // Ending of parallel region
}

//gcc-13 -fopenmp test.c -o test
//./test
//https://tildesites.bowdoin.edu/~ltoma/teaching/cs3225-GIS/fall16/Lectures/openmp.html