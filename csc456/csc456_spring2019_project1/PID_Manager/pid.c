/**
 * A solution to the pid manager problem.
 *
 */

#include "pid.h"
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t pidMutex = PTHREAD_MUTEX_INITIALIZER;
const int size = PID_MAX-PID_MIN;
int *map;

// Allocates the pid map.
int allocate_map(void)
{
    map = (int *)malloc(sizeof(_Bool)*size);
    if(map == NULL)
    {
        return -1;
    }
    return 0;
}

// Allocates a pid
int allocate_pid(void)
{
   /* local variables */

   /* acquire the mutex lock and warn if unable */
   if(pthread_mutex_trylock(&pidMutex) != 0)
   {
       printf("mutex locked for allocating\n");
       pthread_mutex_lock(&pidMutex);
   }
   /* find the next available pid */
   for(int i=0; i<size; i++)
   {
       if(map[i] == 0)
       {
           last = PID_MIN+i;
           map[i] = 1;
           i = size;
       }
   }
   /* release and warn if the mutex was not released */
   pthread_mutex_unlock(&pidMutex);
   return last;
}

// Releases a pid
void release_pid(int pid)
{
   /* acquire the mutex lock and warn if unable */
   if(pthread_mutex_trylock(&pidMutex) != 0)
   {
       printf("mutex locked for releasing\n");
       pthread_mutex_lock(&pidMutex);
   }
   map[pid-PID_MIN] = 0;
   /* release and warn if the mutex was not released  */
   pthread_mutex_unlock(&pidMutex);
   return;
}
