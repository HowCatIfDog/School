#include "bank.h"
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t pidMutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[])
{
    if (argc != NUMBER_OF_RESOURCES)
    {
	     printf("Incorrect number of arguments\n")
         return -1;
    }

    for(int i = 0; i<NUMBER_OF_RESOURCES; i++)
    {
        int available[i] = argv[i];
    }






}

int initialize_arrays(int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES],
    int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES],
    int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES])
{
    //set maximum for each customer to available

    //initialize allocation to all 0's

    //update need
    update_need(need)
}

int request_resources(int customer_num, int request[])
{
    /* acquire the mutex lock and warn if unable */
    if(pthread_mutex_trylock(&pidMutex) != 0)
    {
        pthread_mutex_lock(&pidMutex);
    }



    /* release and warn if the mutex was not released  */
    pthread_mutex_unlock(&pidMutex);
    return;
}

int release_resources(int customer_num, int release[])
{
    /* acquire the mutex lock and warn if unable */
    if(pthread_mutex_trylock(&pidMutex) != 0)
    {
        pthread_mutex_lock(&pidMutex);
    }



    /* release and warn if the mutex was not released  */
    pthread_mutex_unlock(&pidMutex);
    return;
}

int safety_test()
{

}

int update_need(int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES])
{

}
