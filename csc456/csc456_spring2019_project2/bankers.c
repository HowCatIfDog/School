#include "bank.h"
#include "customer.h"
#include <pthread.h>
#include <stdio.h>
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
        available[i] = atoi(argv[i+1]);
        //available[i] = i+1;
    }

    initialize_arrays(maximum, allocation, need);

    print_table(need, allocation, maximum, available);



    return 0;
}

int initialize_arrays(int maximum[][NUMBER_OF_RESOURCES],
    int allocation[][NUMBER_OF_RESOURCES],
    int need[][NUMBER_OF_RESOURCES])
{
    int i = 0;
    int j = 0;
    //set maximum for each customer to available
    for(i = 0; i<NUMBER_OF_CUSTOMERS; i++)
    {
        for(j = 0; j<NUMBER_OF_RESOURCES; j++)
        {
            maximum[i][j] = 2;
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
    update_need(need, maximum, allocation);
}

int request_resources(int customer_num, int request[])
{
    /* acquire the mutex lock and warn if unable */
    // if(pthread_mutex_trylock(&pidMutex) != 0)
    // {
    //     pthread_mutex_lock(&pidMutex);
    // }
    //
    //
    //
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
    //
    //
    //
    // /* release and warn if the mutex was not released  */
    // pthread_mutex_unlock(&pidMutex);
    return 0;
}

int safety_test()
{

}

int update_need(int need[][NUMBER_OF_RESOURCES],
    int allocation[][NUMBER_OF_RESOURCES],
    int maximum[][NUMBER_OF_RESOURCES])
{
    for(int i = 0; i<NUMBER_OF_CUSTOMERS; i++)
    {
        for(int j = 0; j<NUMBER_OF_RESOURCES; j++)
        {
            //no idea why but there needs to be a negative there
            need[i][j] = -(maximum[i][j] - allocation[i][j]);
            //printf("%d \n", maximum[i][j]-allocation[i][j]);
        }
    }

    return 0;
}

void print_table(int need[][NUMBER_OF_RESOURCES],
    int allocation[][NUMBER_OF_RESOURCES],
    int maximum[][NUMBER_OF_RESOURCES],
    int available[])
{
    printf("     Allocation    Need     Maximum     Available\n");
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
