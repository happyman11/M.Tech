#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//csv writter
void csv_writter_initialize(char* filename, int Matrix_Size,int Thread_No,int Power, double elapse_time, double Throughput )
{
    printf("inside Writter");
    printf( "\n%d, %d,%d,%.4f,%.7f \n", Matrix_Size, Thread_No, Power,elapse_time,Throughput);
    FILE* file = fopen(filename, "a");
     
     fprintf(file, "%d, %d,%d,%.4f,%.7f\n", Matrix_Size, Thread_No, Power,elapse_time,Throughput);
  // fprintf(file, "Matrix_Size, Thread_No, Power, Time,Througput\n");
    fclose(file);

    printf("CSV file %s created Updated.\n", filename);
    
}

  
// Function to create and return a float matrix
float** createFloatMatrix(int size) 
{
    printf("Creating Matrix.....%d\n",omp_get_thread_num());
    float** matrix = (float**)malloc(size * sizeof(float*));
    int i,j;

    #pragma omp parallel for shared(i, j)
    
    for (i = 0; i < size; i++) 
    {
        matrix[i] = (float*)malloc(size * sizeof(float));
        for (j = 0; j < size; j++) 
        {
            matrix[i][j] = (float)(i * size + j + 1) / 100.0;
        }
    }
    #pragma omp barrier
    printf("Matrix Creation Complete.....%d\n",omp_get_thread_num());
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

    

    #pragma omp parallel private(bi,bj,bk,i,j,k) 

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
                           #pragma omp barrier
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
    printf("Starting Memory Deallocation.....%d\n",omp_get_thread_num());
    for (int i = 0; i < size; i++) 
    {
      free(matrix[i]);
    }
    free(matrix);
    printf("Memory Deallocation Complete.....%d\n",omp_get_thread_num());
}
    


// Function to print a float matrix
void printFloatMatrix(float** matrix, int size) 
{   
    printf("Starting Display Function.....%d\n",omp_get_thread_num());
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            printf("%.4f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("Ending Display Function.....%d\n",omp_get_thread_num());
}

// Function to Transpose a Existing Matrix
float** TransposeMatrix(int size) 
{
    printf("Creating Transpose Matrix .....%d\n",omp_get_thread_num());
    float** matrix= createFloatMatrix(size);
    //printFloatMatrix(matrix,size);
    float** transposematrix = (float**)malloc(size * sizeof(float*));
    int i,j;
    #pragma omp parallel for private(i, j)
    for (i = 0; i < size; i++) 
    {
        transposematrix[i] = (float*)malloc(size * sizeof(float));
        for (j = 0; j < size; j++) 
        {
            transposematrix[i][j] = matrix[j][i];
        }
    }
    
    #pragma omp barrier
    //printFloatMatrix(transposematrix,size);
    printf("Matrix Creation Complete.....%d\n",omp_get_thread_num());
    
    return matrix;
}


//Function for Matrix Multilication
float** matrixMultiplication(float** matrixA,float** matrixB,int size) 
{
    float** result = (float**)malloc(size * sizeof(float*));
    int i,j,k;
    #pragma omp parallel private(i,j,k) 
   
    printf("Calculating Power of Matrix....%d\n",omp_get_thread_num());
    for (i = 0; i < size; i++) 
    {
      result[i] = (float*)malloc(size * sizeof(float));
      for (j = 0; j < size; j++) 
      {
        for ( k = 0; k < size; k++) 
        {   
          result[i][j]= result[i][j] +matrixA[i][k] * matrixB[k][j];                         
        }
      }       
    }
    printf("Completed Calculating Power of Matrix....%d\n",omp_get_thread_num());
    #pragma omp barrier
    return result;
}

//Function for Matrix Power
float** Matrix_Pow(float** matrix,int size,int pow, int block_size, int check_block)
{   
  float** power_mat ;
  int i=0;
  #pragma omp parallel 
  printf("Calculating Power of Matrix....%d\n",omp_get_thread_num());
  
  {
    for (i = 0; i < pow;i++)
    {     
        if (i==0)
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
        else
          {
            if (check_block==0)
            {
              power_mat=matrixMultiplication(matrix,power_mat,size);
            }
            else
            {
              power_mat=Multiply( matrix, matrix,size,block_size);
            }
          }
    }
  } 
  printf("Completed Calculating Power of Matrix...%d\n",omp_get_thread_num());
  #pragma omp barrier
  
  return power_mat;

}



