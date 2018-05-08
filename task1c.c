/*
  Authors:  Joe Holston and Dan Smith
  Course:  COMP 340, Operating Systems
  Date:    7 May 2018
  Description:   This file implements the
                 functionality required for
                 Program 3, Task 1.
  Compile with:  gcc -o task1c task1c.c -lpthread 
  Run with:      ./task1c
*/

#include <pthread.h>
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/resource.h>


//THREAD AND SEMAPHORE EXAMPLE

int sum; /* this data is shared by the thread(s) */
 pthread_mutex_t mutexsum;  //from power point week6

void *runner1(); /* the thread */
void *runner2(); /* the thread */

int main(int argc, char *argv[])
{
  struct rusage r_usage;    //initializes the struct that we get the allocation info from
 
  pthread_mutex_init(&mutexsum, NULL);   //initialize pthread


  pthread_t tid1, tid2; /* the thread identifiers */
  pthread_attr_t attr; /* set of attributes for the thread */
  
  sum = 0;

  srandom((unsigned)time(NULL));

  /* get the default attributes */
  pthread_attr_init(&attr);
  
  /* create the thread */
  pthread_create(&tid1,&attr,runner1,NULL);
  pthread_create(&tid2,&attr,runner2,NULL);

  /* now wait for the thread to exit */
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);

  printf("sum = %d\n",sum);
  pthread_mutex_destroy(&mutexsum);
  
  //prints out memory allocated
  getrusage(RUSAGE_SELF,&r_usage);
  printf("Memory usage = %ld kB\n",r_usage.ru_maxrss);
}

void *runner1() 
{
  pthread_mutex_lock (&mutexsum);
  int value = sum;
  double wait_time = 4.0 * rand()/RAND_MAX;
  //printf("thread1 sleeping for %f\n", wait_time);
  sleep(wait_time);
  sum = value - 5;
  printf("Running thread1 setting sum to %d\n", sum);
  pthread_mutex_unlock (&mutexsum);
  pthread_exit(0);
}

void *runner2() 
{
  pthread_mutex_lock (&mutexsum);
  int value = sum;
  double wait_time = 4.0 * rand()/RAND_MAX;
  //printf("thread2 sleeping for %f\n", wait_time);
  sleep(wait_time);
  sum = value + 15;
  printf("Running thread2 setting sum to %d\n", sum);
  pthread_mutex_unlock (&mutexsum);
  pthread_exit(0);
}
