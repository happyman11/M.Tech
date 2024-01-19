#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "utilities.h"





// accepts num threads, size,pow,block_size,choice (1,2,3,4),
// 1-> OMM 
// 2-> OMM with Transpose
// 3-> BMM
// 4-> BMM with Transpose
int main(int arge, char *argv[]) 
{   
    // Track Time
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;
    
    // Take input from user
    int thread_num=atoi(argv[1]);
    int size=atoi(argv[2]);
    int pow=atoi(argv[3]);
    int block_size=atoi(argv[4]);
    int check_block=0;
    int user_choice=atoi(argv[5]);
   

   

    if (pow < 2) 
    {
        printf("Opps!!!Invalid input. Power must be a greater than or equal to 2 .\n");
        return 1;
    }

    clock_t start,end;
    double cpu_time_used;
    omp_set_num_threads(thread_num);

    
        

     
        
    // For normal Martix Multiplication user choice ==1
    if (user_choice ==1)
    {   
        start = clock();
        block_size=1;
        check_block=0;

        printf("Number of Thread: %d\n",thread_num);
        printf("Matrix Size: %d*%d\n",size,size);
        printf("Matrix Power: %d\n",pow);
        printf("User Choice: %d\n",user_choice);
        printf("Block Size for Multiplication: %d\n",block_size);
        gettimeofday(&tv1, &tz);
        float** myFloatMatrix;
        printf("Calculating for Normal Matrix OMM\n");
        #pragma omp parallel
        {
          myFloatMatrix = createFloatMatrix(size);
        }
        #pragma omp barrier
        //printFloatMatrix(myFloatMatrix, size);
        
       
        //result matrix
        float** result_pow ;
        result_pow=Matrix_Pow(myFloatMatrix,size,pow,block_size,check_block);

        //print result
        printf("Result Matrix of with exponent: %d\n",pow);
        //printFloatMatrix(result_pow, size);

        gettimeofday(&tv2, &tz);
        elapsed += (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
        printf("Time = %lf \n",elapsed);
        
        end=clock();
        cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
        double flops=(2.0*size*size*size*pow)/cpu_time_used;
        printf("CPU Time used%f\n",cpu_time_used);
        printf("Throughput in GFLOPS%.7f\n",flops/1e9);
        char* filename="OMM_Normal_Data.csv";
        double through=flops/1e9;
        csv_writter_initialize(filename,size,thread_num,pow, cpu_time_used,  through );
        //Free the memory
        freeFloatMatrix(myFloatMatrix, size);
        freeFloatMatrix(result_pow, size);
   }
    else if(user_choice ==2)
    {
        start = clock();
        block_size=1;
        check_block=0;

        printf("Number of Thread: %d\n",thread_num);
        printf("Matrix Size: %d*%d\n",size,size);
        printf("Matrix Power: %d\n",pow);
        printf("User Choice: %d\n",user_choice);
        printf("Block Size for Multiplication: %d\n",block_size);

        gettimeofday(&tv1, &tz);
        float** myFloatMatrix;
        //printf("Calculating for Transpose Matrix OMM");
        #pragma omp parallel
        {
          myFloatMatrix = TransposeMatrix(size);
        }
        #pragma omp barrier
        //printFloatMatrix(myFloatMatrix, size);

       
        //result matrix
        float** result_pow ;
        result_pow=Matrix_Pow(myFloatMatrix,size,pow,block_size,check_block);

        //print result
        printf("Result Matrix of with exponent: %d\n",pow);
        //printFloatMatrix(result_pow, size);

        gettimeofday(&tv2, &tz);
        elapsed += (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
        printf("Time = %lf \n",elapsed);
        
        end=clock();
        cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
        double flops=(2.0*size*size*size*pow)/cpu_time_used;
        printf("CPU Time used%f\n",cpu_time_used);
        printf("Throughput in GFLOPS%.7f\n",flops/1e9);
        char* filename="OMM_Transpose_Data.csv";
        double through=flops/1e9;
        csv_writter_initialize(filename,size,thread_num,pow, cpu_time_used,  through );
        //Free the memory
        freeFloatMatrix(myFloatMatrix, size);
        freeFloatMatrix(result_pow, size);

    }

    else if(user_choice ==3)
    {
        start = clock();
        
        check_block=1;

        printf("Number of Thread: %d\n",thread_num);
        printf("Matrix Size: %d*%d\n",size,size);
        printf("Matrix Power: %d\n",pow);
        printf("User Choice: %d\n",user_choice);
        printf("Block Size for Multiplication: %d\n",block_size);


        gettimeofday(&tv1, &tz);
        float** myFloatMatrix;
        printf("Calculating for BMM Matrix\n");
        #pragma omp parallel
        {
          myFloatMatrix = createFloatMatrix(size);
        }
        //printFloatMatrix(myFloatMatrix, size);

        #pragma omp barrier

        //result matrix
        float** result_pow ;
        result_pow=Matrix_Pow(myFloatMatrix,size,pow,block_size,check_block);

        //print result
        printf("Result Matrix of with exponent: %d\n",pow);
        //printFloatMatrix(result_pow, size);

        gettimeofday(&tv2, &tz);
        elapsed += (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
        printf("Time = %lf \n",elapsed);
        
        end=clock();
        cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
        double flops=(2.0*size*size*size*pow)/cpu_time_used;
        printf("CPU Time used%f\n",cpu_time_used);
        printf("Throughput in GFLOPS%.7f\n",flops/1e9);
        char* filename="BMM_Normal_Data.csv";
        double through=flops/1e9;
        csv_writter_initialize(filename,size,thread_num,pow, cpu_time_used,  through );
        //Free the memory
        freeFloatMatrix(myFloatMatrix, size);
        freeFloatMatrix(result_pow, size);
    }
    else if(user_choice ==4)
    {
        start = clock();
        
        check_block=1;

        printf("Number of Thread: %d\n",thread_num);
        printf("Matrix Size: %d*%d\n",size,size);
        printf("Matrix Power: %d\n",pow);
        printf("User Choice: %d\n",user_choice);
        printf("Block Size for Multiplication: %d\n",block_size);
        
        gettimeofday(&tv1, &tz);
        float** myFloatMatrix;
        printf("Calculating for BMM Transpose Matrix\n");
        #pragma omp parallel
        {
          myFloatMatrix = TransposeMatrix(size);
        }

        //printFloatMatrix(myFloatMatrix, size);

        #pragma omp barrier
        //result matrix
        float** result_pow ;
        result_pow=Matrix_Pow(myFloatMatrix,size,pow,block_size,check_block);

        printf("Result Matrix of with exponent: %d\n",pow);
        //printFloatMatrix(result_pow, size);

       
        gettimeofday(&tv2, &tz);
        elapsed += (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
        printf("Time = %lf \n",elapsed);

        end=clock();
        cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
        double flops=(2.0*size*size*size*pow)/cpu_time_used;
        printf("CPU Time used%f\n",cpu_time_used);
        printf("Throughput in GFLOPS%.7f\n",flops/1e9);
        char* filename="BMM_Normal_Data.csv";
        double through=flops/1e9;
        csv_writter_initialize(filename,size,thread_num,pow, cpu_time_used,  through );
        //Free the memory
        freeFloatMatrix(myFloatMatrix, size);
        freeFloatMatrix(result_pow, size);

    }

    return 0;
}