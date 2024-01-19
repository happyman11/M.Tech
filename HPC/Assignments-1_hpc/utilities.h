#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

// Blockwise matrix_multiply
float** Multiply( float** a, float** b,int size,int block)
{
    int bi=0;
    int bj=0;
    int bk=0;
    int i=0;
    int j=0;
    int k=0;
    int blockSize=block;
    int n=size;
    float** c=createFloatMatrix(size);
    for(bi=0; bi<n; bi+=blockSize)
    {
        for(bj=0; bj<n; bj+=blockSize)
        {
            for(bk=0; bk<n; bk+=blockSize)
            {
                for(i=0; i<blockSize; i++)
                {
                    for(j=0; j<blockSize; j++)
                    {
                        for(k=0; k<blockSize; k++)
                        {
                            c[bi+i][bj+j] += a[bi+i][bk+k]*b[bk+k][bj+j];
                        }
                    }
                }
            }
        }
    } 
    return c;
}

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
float** Matrix_Pow(float** matrix,int size,int pow, int block_size, int check_block)
{   float** power_mat ;
    for (int i = 0; i < pow;i++)
    {     
        if (i==0)
          {
             power_mat=matrixMultiplication(matrix,matrix,size);
            // for (int i = 0; i < size; i++) 
            // {
            //   power_mat[i] = (float*)malloc(size * sizeof(float));
            //   for (int j = 0; j < size; j++) 
            //   {
            //     power_mat[i][j] = 1;
            //   }
            // }
          }
        else
          {
            if (check_block==0)
            {
              power_mat=matrixMultiplication(matrix,matrix,size);
            }
            else
            {
              power_mat=Multiply( matrix, matrix,size,block_size);
            }
          }
    }
    return power_mat;

}




