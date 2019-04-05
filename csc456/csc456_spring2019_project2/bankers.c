#include "bank.h"
#include "customer.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t pidMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex;
pthread_mutex_t test_mutex;

int main(int argc, char *argv[])
{
    if (argc != NUMBER_OF_RESOURCES+1)
    {
	     printf("Incorrect number of arguments\n");
         return -1;
    }

    for(int i = 0; i<NUMBER_OF_RESOURCES; i++)
    {
        // available[i] = strtol(argv[i+1]);
        available[i] = atoi(argv[i+1]);//this one works best on my machine
        //available[i] = i+1;
    }

    initialize_arrays();
    //testing
    // maximum[1][1] = 4;
    // update_need();
    print_table();
    //testing
    // int temp = 0;
    // temp=safety_test();
    // printf("%d\n", temp);



    return 0;
}

int initialize_arrays()
{
    int i = 0;
    int j = 0;
    //set maximum for each customer to available
    for(i = 0; i<NUMBER_OF_CUSTOMERS; i++)
    {
        for(j = 0; j<NUMBER_OF_RESOURCES; j++)
        {
            maximum[i][j] = available[j]/2;
        }
    }

    //initialize allocation to all 0's
    for(i = 0; i<NUMBER_OF_CUSTOMERS; i++)
    {
        for(j = 0; j<NUMBER_OF_RESOURCES; j++)
        {
            allocation[i][j] = 0;
        }
    }
    //update need
    update_need();
}

int request_resources(int customer_num, int request[])
{
    /* acquire the mutex lock and warn if unable */
    // if(pthread_mutex_trylock(&pidMutex) != 0)
    // {
    //     pthread_mutex_lock(&pidMutex);
    // }

    // 1) If Requesti <= Needi
    // Goto step (2) ; otherwise, raise an error condition, since the process has exceeded its maximum claim.

    int temp = 0;
    for(int i=0; i<NUMBER_OF_RESOURCES; i++)
    {
        if(request[i]>need[customer_num][i])
            temp = -1;
    }
    if(temp<0)
    {
        return -1;
    }

    // 2) If Requesti <= Available
    // Goto step (3); otherwise, Pi must wait, since the resources are not available.

    int temp2 = 0;
    for(int i=0; i<NUMBER_OF_RESOURCES; i++)
    {
        if(request[i]>available[i])
            temp2 = -1;
    }
    if(temp<0)
    {
        //wait
    }

    // 3) Have the system pretend to have allocated the requested resources to process Pi by modifying the state as
    // follows:
    // Available = Available – Requesti
    // Allocationi = Allocationi + Requesti
    // Needi = Needi– Requesti
    for(int j=0; j<NUMBER_OF_RESOURCES; j++)
    {
        available[j]=available[j]-request[j];
        allocation[customer_num][j]=allocation[customer_num][j]+request[j];
        need[customer_num][j]=need[customer_num][j]-request[j];
    }

    update_need();
    // /* release and warn if the mutex was not released  */
    // pthread_mutex_unlock(&pidMutex);
    return 0;
}

int release_resources(int customer_num, int release[])
{
    /* acquire the mutex lock and warn if unable */
    // if(pthread_mutex_trylock(&pidMutex) != 0)
    // {
    //     pthread_mutex_lock(&pidMutex);
    // }

    for(int j=0; j<NUMBER_OF_RESOURCES; j++)
    {
        available[j]=available[j]+release[j];
        allocation[customer_num][j]=allocation[customer_num][j]-release[j];
        need[customer_num][j]=need[customer_num][j]+release[j];
    }

    update_need();

    // /* release and warn if the mutex was not released  */
    // pthread_mutex_unlock(&pidMutex);
    return 0;
}

int safety_test()
{
    // 1) Let Work and Finish be vectors of length ‘m’ and ‘n’ respectively.
    // Initialize: Work = Available
    // Finish[i] = false; for i=1, 2, 3, 4….n
    int work[NUMBER_OF_RESOURCES];
    int finish[NUMBER_OF_CUSTOMERS]; //0=TRUE -1=FALSE

    for(int i=0; i<NUMBER_OF_RESOURCES; i++)
    {
        work[i]=available[i];
    }
    for(int j=0; j<NUMBER_OF_CUSTOMERS; j++)
    {
        finish[j]=-1;
    }

    // 2) Find an i such that both
    // a) Finish[i] = false
    // b) Needi <= Work
    // if no such i exists goto step (4)
    for(int i=0; i<NUMBER_OF_CUSTOMERS; i++)
    {
        int temp = 0;
        for(int k=0; k<NUMBER_OF_RESOURCES; k++)
        {
            if(need[i][k]>work[k])
                temp = -1;
        }

        // 3) Work = Work + Allocation[i]
        // Finish[i] = true
        // goto step (2)
        if(finish[i]==-1 && temp==0)
        {
            for(int j=0; j<NUMBER_OF_RESOURCES; j++)
                work[j]=work[j]+allocation[i][j];

            finish[i] = 0;
        }
    }

    // 4) if Finish [i] = true for all i
    // then the system is in a safe state
    //if every element in finish is true then return true else return false
    for(int k=0; k<NUMBER_OF_CUSTOMERS; k++)
    {
        if(finish[k]!=0)
            return -1;
    }
    return 0;
}

int update_need()
{
    for(int i = 0; i<NUMBER_OF_CUSTOMERS; i++)
    {
        for(int j = 0; j<NUMBER_OF_RESOURCES; j++)
        {
            need[i][j] = (maximum[i][j] - allocation[i][j]);
            //printf("%d \n", maximum[i][j]-allocation[i][j]);
        }
    }

    return 0;
}

void print_table()
{
    //print out a poorly formated table of all the arrays
    printf("     Allocation    Need     Maximum    Available\n");
    for(int i = 0; i<NUMBER_OF_CUSTOMERS; i++)
    {
        printf("P%d     ", i);
        for(int j = 0; j<NUMBER_OF_RESOURCES; j++)
        {
            printf("%d ", allocation[i][j]);
        }
        printf("     ");
        for(int k = 0; k<NUMBER_OF_RESOURCES; k++)
        {
            printf("%d ", need[i][k]);
        }
        printf("     ");
        for(int l = 0; l<NUMBER_OF_RESOURCES; l++)
        {
            printf("%d ", maximum[i][l]);
        }
        if(i == 0)
        {
          printf("     ");
          for(int m = 0; m < NUMBER_OF_RESOURCES; m++)
          {
            printf("%d ", available[m]);
          }
        }
        printf("\n");
    }


    return;
}
