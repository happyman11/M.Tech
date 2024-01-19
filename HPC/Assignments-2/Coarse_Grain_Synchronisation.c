#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <omp.h>
#include <unistd.h>


//gcc-13 -fopenmp Coarse_Grain_Synchronisation.c -o test
//gcc -o myprogram myprogram.c -pthread
//gcc-13 -pthread Coarse_Grain_Synchronisation.c -o test
//https://www.javatpoint.com/doubly-linked-list

struct node  
{  
    struct node *prev;  
    struct node *next;  
    int data;  
};  
struct node *head;  
int lock=0;
int counter=1;

void display()  
{  
    struct node *ptr;  
    printf("\n ........Inside print function......\n");  
    ptr = head;  
    while(ptr != NULL)  
    {  
        printf("%d\n",ptr->data);  
        ptr=ptr->next;  
    } 
    printf("\n ........Exiting print function......\n"); 
} 

void insertion_last()  
{  
    printf("\n ........Inside insertion_last function......\n"); 
   while(lock!=0);
   lock=1;
   struct node *ptr,*temp;  
   int item;  
   ptr = (struct node *) malloc(sizeof(struct node));  
   if(ptr == NULL)  
   {  
       printf("\nOVERFLOW");  
   }  
   else  
   {  
        item=counter;
        counter=counter+1;
        ptr->data=item;  
        printf("\nInserted Data into Doubly Linked List: %d\n",item);
       if(head == NULL)  
       {  
           ptr->next = NULL;  
           ptr->prev = NULL;  
           head = ptr;  
       }  
       else  
       {  
          temp = head;  
          while(temp->next!=NULL)  
          {  
              temp = temp->next;  
          }  
          temp->next = ptr;  
          ptr ->prev=temp;  
          ptr->next = NULL;  
          }  
             
       }  
     printf("\n ........Exiting insertion_last function......\n"); 
     lock=0;
    } 

void delete_last()  
{  
   printf("\n ........Inside delete_last function......\n"); 
   while(lock!=0);
   lock=1;
   struct node *ptr;  
    if(head == NULL)  
    {  
        printf("\n .......UNDERFLOW............");  
    }  
    else if(head->next == NULL)  
    {  
        head = NULL;   
        free(head);   
        printf("\n............Node deleted Completed.......\n");  
    }  
    else   
    {  
        ptr = head;   
        if(ptr->next != NULL)  
        {  
            ptr = ptr -> next;   
        }  
        ptr -> prev -> next = NULL;   
        free(ptr);  
        printf("\n ........Exiting delete_last function......\n");
    }   
     lock=0;
}  

int  main()
{

    
    int number_threads = 2; 
    int create_oprations=5;
    int delete_oprations=1;

    omp_set_num_threads(number_threads);
    
    int i=0;
    #pragma omp parallel shared(i,create_oprations)
    for (i=0;i<create_oprations;i++)
    {
        insertion_last();
        
    }
    #pragma omp barrier
    
    display();

    i=0;
    #pragma omp parallel shared(i,delete_oprations)
    for (i=0;i<delete_oprations;i++)
    {
     delete_last();
    }
    #pragma omp barrier

    

    return 0;


}
