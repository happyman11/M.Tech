#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "utilities.h"



int main() 
{   
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;

    float** myFloatMatrix;
    int size=512;
    int pow=2;
    int block=4;

    if (pow < 0) 
    {
        printf("Invalid input. Power must be a non-negative integer.\n");
        return 1;
    }
    gettimeofday(&tv1, &tz);

    // Create the Normal Metric 
    myFloatMatrix = createFloatMatrix(size);
    printFloatMatrix(myFloatMatrix, size);
    

    // for Transpose Metric
    // myFloatMatrix = TransposeMatrix(size);
    // printFloatMatrix(myFloatMatrix, size);

    int check_block=1;
    //result matrix
    float** result_pow ;
    result_pow=Matrix_Pow(myFloatMatrix,size,pow,block,check_block);
    
    

    // //print result
    printf("Result Matrix of with exponent: %d\n",pow);
    printFloatMatrix(result_pow, size);


    gettimeofday(&tv2, &tz);
    elapsed += (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("Time = %lf \n",elapsed);
    //  // Free the memory
    freeFloatMatrix(myFloatMatrix, size);
    freeFloatMatrix(result_pow, size);

    return 0;
}