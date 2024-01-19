#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"'

int main() 
{
    float** myFloatMatrix;
    int size=4;
    int pow=2;

    if (pow < 0) 
    {
        printf("Invalid input. Power must be a non-negative integer.\n");
        return 1;
    }

    // Create the Normal Metric 
    myFloatMatrix = createFloatMatrix(size);
    printFloatMatrix(myFloatMatrix, size);
    

    // for Transpose Metric
    //myFloatMatrix = TransposeMatrix(size);
    //printFloatMatrix(myFloatMatrix, size);

    //result matrix
    float** result_pow ;
    result_pow=Matrix_Pow(myFloatMatrix, size,pow);

    //print result
    printf("Result Matrix of %d\n",pow);
    printFloatMatrix(result_pow, size);



     // Free the memory
    freeFloatMatrix(myFloatMatrix, size);
    freeFloatMatrix(result_pow, size);

    return 0;
}