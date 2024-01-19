#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Function to free the memory allocated for a float matrix
void freeFloatMatrix(float** matrix, int size) 
{   
    printf("Starting Memory Deallocation.....\n");
    int i;
    #pragma omp parallel for private(i)
    
    for (i = 0; i < size; i++) 
    {
        free(matrix[i]);
    }

    #pragma omp barrier
    
    free(matrix);
    printf("Memory Deallocation Complete.....\n");
}

// Function to create and return a float matrix
float** createFloatMatrix(int size) 
{
    printf("Creating Matrix.....\n");
    float** matrix = (float**)malloc(size * sizeof(float*));
    int i,j;
    #pragma omp parallel for private(i, j)
    
    for (i = 0; i < size; i++) 
    {
        matrix[i] = (float*)malloc(size * sizeof(float));
        for (j = 0; j < size; j++) 
        {
            matrix[i][j] = (float)(i + j + 1) / 1000.0;
        }
    }
    #pragma omp barrier
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



//Function for Matrix Multilication
float** matrixMultiplication(float** matrixA,float** matrixB,int size) 
{
    float** result = (float**)malloc(size * sizeof(float*));
    int i,j,k;
    #pragma omp parallel for private(i, j, k)
    for ( i = 0; i < size; i++) 
    {
      result[i] = (float*)malloc(size * sizeof(float));
      for ( j = 0; j < size; j++) 
      {
        for ( k = 0; k < size; k++) 
        {   
          result[i][j]= result[i][j] +matrixA[i][k] * matrixB[k][j];                         
        }
      }       
    }
    #pragma omp barrier
    return result;
}

//Function for Matrix Power
float** Matrix_Pow(float** matrix,int size,int pow)
{   float** power_mat ;
    for (int i = 0; i < pow;i++)
    {     
        #pragma omp parallel
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
    }
    return power_mat;

}

// Function to Transpose a Existing Matrix
float** TransposeMatrix(int size) 
{
    printf("Creating Transpose Matrix .....\n");
    float** matrix= createFloatMatrix(size);
    printFloatMatrix(matrix,size);
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
    printf("Matrix Creation Complete.....\n");
    printFloatMatrix(transposematrix,size);
    freeFloatMatrix(matrix, size);
    return matrix;
}


// No of thread,matrix_size,power,0=Transpose/else Normal

int main(int arge, char *argv[]) 
{
    clock_t start_time, end_time;
    double elapsed_cpu_time;
    time_t start_real_time, end_real_time;
    struct tm *start_time_info, *end_time_info;
    char start_time_str[26], end_time_str[26];

    float** myFloatMatrix;
    int thread_num=atoi(argv[1]);
    int size=atoi(argv[2]);
    int pow=atoi(argv[3]);
    char user_choice = atoi(argv[4]);


    printf("Number of Thread: %d\n",thread_num);
    printf("Matrix Size: %d*%d\n",size,size);
    printf("Matrix Power: %d\n",pow);
    printf("User Choice: %d\n",user_choice);


    if (pow < 0) 
    {
        printf("Invalid input. Power must be a non-negative integer.\n");
        return 1;
    }
    omp_set_num_threads(thread_num);

    
    start_time = clock();
    if (user_choice==0)
    {
        printf("Calculating for Transpose Matrix");

        #pragma omp parallel
        {
          myFloatMatrix = createFloatMatrix(size);
        }
        printFloatMatrix(myFloatMatrix, size);

        float** result_pow ;
        result_pow=Matrix_Pow(myFloatMatrix, size,pow);
    
        //print result
        printf("Result Matrix of %d\n",pow);
        printFloatMatrix(result_pow, size);

        #pragma omp barrier
        freeFloatMatrix(myFloatMatrix, size);
        freeFloatMatrix(result_pow, size);



        time(&start_real_time);
        start_time_info = localtime(&start_real_time);
        strftime(start_time_str, sizeof(start_time_str), "%Y-%m-%d %H:%M:%S", start_time_info);
        printf("Start Time: %s\n", start_time_str);

        end_time = clock();

        time(&end_real_time);
        end_time_info = localtime(&end_real_time);
        strftime(end_time_str, sizeof(end_time_str), "%Y-%m-%d %H:%M:%S", end_time_info);
        printf("End Time: %s\n", end_time_str);


        elapsed_cpu_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Elapsed Time: %.6f seconds\n", elapsed_cpu_time);
    }

    else
    {   printf("Calculating for Normal Matrix");
        #pragma omp parallel
        {
          myFloatMatrix = createFloatMatrix(size);
        }
        printFloatMatrix(myFloatMatrix, size);

        float** result_pow ;
        result_pow=Matrix_Pow(myFloatMatrix, size,pow);
    
        //print result
        printf("Result Matrix of %d\n",pow);
        printFloatMatrix(result_pow, size);

        #pragma omp barrier
        freeFloatMatrix(myFloatMatrix, size);
        freeFloatMatrix(result_pow, size);

        time(&start_real_time);
        start_time_info = localtime(&start_real_time);
        strftime(start_time_str, sizeof(start_time_str), "%Y-%m-%d %H:%M:%S", start_time_info);
        printf("Start Time: %s\n", start_time_str);

        end_time = clock();

        time(&end_real_time);
        end_time_info = localtime(&end_real_time);
        strftime(end_time_str, sizeof(end_time_str), "%Y-%m-%d %H:%M:%S", end_time_info);
        printf("End Time: %s\n", end_time_str);


        elapsed_cpu_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Elapsed Time: %.6f seconds\n", elapsed_cpu_time);

    }

    return 0;
}