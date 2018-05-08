/*
AUTHORS: JOE HOLSTON, DAN SMITH
COURSE: COMP 340- OS
DUE DATE: MAY 8, 2018
DESCRIPTION: RUNS PROCESSES AND SEND A ERROR MESSAGE WHEN RAM USAGE IS ABOVE DESIRED THRESHOLD
TO RUN/COMPILE: gcc -o task3 task3.c -lpthread
*/

#include <pthread.h>
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>

//maximum percentage of RAM usage desired
#define THRESHOLD 85
int overThreshold = 0;

//thread runner functions
void *memoryManager();
void *test1();
void *test2();
void *test3();
void memCheck();

int main(int argc, char *argv[])
{
  //creates and runs the parent thread for memory managment
  pthread_t tid1;
  pthread_attr_t attr;

  pthread_attr_init(&attr);

  pthread_create(&tid1,&attr,memoryManager,NULL);

  pthread_join(tid1,NULL);
}

//parent function that creates the various child processes to run each of the tests
void *memoryManager()
{
  memCheck();

  pthread_t tid2, tid3, tid4;
  pthread_attr_t attr;

  pthread_attr_init(&attr);

  pthread_create(&tid2,&attr,test1,NULL);
  pthread_create(&tid3,&attr,test2,NULL);
  pthread_create(&tid4,&attr,test3,NULL);

  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);
  pthread_join(tid4,NULL);
  pthread_exit(0);
}

//used to check the current state of the memory usage
void memCheck()
{
    double percentUsed;
    struct sysinfo info;
    //fills a premade struct of type sysinfo and is provided through sys/sysinfo.h
    sysinfo (&info);

    //calculated through values that are provided by calling sysinfo. Uses the total ram and free ram to calculate amount of ram being used.
    percentUsed = ((double)(info.totalram - info.freeram) / (double)info.totalram)*100;

    //not already over 85
    if(overThreshold == 0){
      if(percentUsed >= THRESHOLD){
        printf("WARNING: System Memory Usage has exceeded %d%%\n", THRESHOLD);
        overThreshold = 1;
      }
    }
    //threshold was already hit
    else{
      if(percentUsed < THRESHOLD){
        overThreshold = 0;
      }
    }
    printf("Current Memory Usage: %f%%\n",percentUsed);
}

//simple test that allocates 2GB
void *test1(){
  memCheck();
  int* p = malloc(2000000000);
  memset(p, 0, 2000000000);
  memCheck();
  pthread_exit(0);
}

//test that allocates and then clears out 1.5GB
void *test2(){
  memCheck();
  int* p = malloc(1500000000);
  memset(p, 0, 1500000000);
  memCheck();
  free(p);
  memCheck();
  pthread_exit(0);
}

//allocates 1GB
void *test3(){
  memCheck();
  int* p = malloc(1000000000);
  memset(p, 0, 1000000000);
  memCheck();
  pthread_exit(0);
}
