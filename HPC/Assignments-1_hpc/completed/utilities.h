#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Function to free the memory allocated for a float matrix
void freeFloatMatrix(float** matrix, int size) 
{   
    printf("Starting Memory Deallocation.....\n");
    for (int i = 0; i < size; i++) 
    {
        free(matrix[i]);
    }
    free(matrix);
    printf("Memory Deallocation Complete.....\n");
}
    
// Function to create and return a float matrix
float** createFloatMatrix(int size) 
{
    printf("Creating Matrix.....\n");
    float** matrix = (float**)malloc(size * sizeof(float*));

    for (int i = 0; i < size; i++) 
    {
        matrix[i] = (float*)malloc(size * sizeof(float));
        for (int j = 0; j < size; j++) 
        {
            matrix[i][j] = (float)(i * size + j + 1) / 100.0;
        }
    }
    printf("Matrix Creation Complete.....\n");
    return matrix;
}

// Function to print a float matrix
void printFloatMatrix(float** matrix, int size) 
{   
    printf("Starting Display Function.....\n");
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            printf("%.4f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("Ending Display Function.....\n");
}

// Function to Transpose a Existing Matrix
float** TransposeMatrix(int size) 
{
    printf("Creating Transpose Matrix .....\n");
    float** matrix= createFloatMatrix(size);
    printFloatMatrix(matrix,size);

    float** transposematrix = (float**)malloc(size * sizeof(float*));

    for (int i = 0; i < size; i++) 
    {
        transposematrix[i] = (float*)malloc(size * sizeof(float));
        for (int j = 0; j < size; j++) 
        {
            transposematrix[i][j] = matrix[j][i];
        }
    }
    printf("Matrix Creation Complete.....\n");
    printFloatMatrix(transposematrix,size);
    freeFloatMatrix(matrix, size);
    return matrix;
}


//Function for Matrix Multilication
float** matrixMultiplication(float** matrixA,float** matrixB,int size) 
{
    float** result = (float**)malloc(size * sizeof(float*));
    
    for (int i = 0; i < size; i++) 
    {
      result[i] = (float*)malloc(size * sizeof(float));
      for (int j = 0; j < size; j++) 
      {
        for (int k = 0; k < size; k++) 
        {   
          result[i][j]= result[i][j] +matrixA[i][k] * matrixB[k][j];                         
        }
      }       
    }
    return result;
}

//Function for Matrix Power
float** Matrix_Pow(float** matrix,int size,int pow)
{   float** power_mat ;
    for (int i = 0; i < pow;i++)
    {     
        if (i==0)
          {
          power_mat=matrixMultiplication(matrix,matrix,size);
          }
          else
          {
            power_mat=matrixMultiplication(power_mat,matrix,size);
          }
    }
    return power_mat;

}


