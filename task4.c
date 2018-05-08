#include <pthread.h>
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>

#define THRESHOLD 85
int overThreshold = 0;
pthread_t tid1, tid2, tid3, tid4, tid5;

void *memoryManager();
void *test1();
void *test2();
void *test3();
void *test4();
void memCheck();

int main(int argc, char *argv[])
{
  pthread_attr_t attr;

  pthread_attr_init(&attr);

  pthread_create(&tid1,&attr,memoryManager,NULL);

  pthread_join(tid1,NULL);

}

void *memoryManager()
{
  memCheck(tid1);

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

void memCheck()
{
    double percentUsed;
    struct sysinfo info;
    sysinfo (&info);

    percentUsed = ((double)(info.totalram - info.freeram) / (double)info.totalram)*100;

    //not already over 85
    if(overThreshold == 0){
      if(percentUsed >= THRESHOLD){
        printf("WARNING: System Memory Usage has exceeded %d%%\n", THRESHOLD);
        overThreshold = 1;
        percentUsed = ((double)(info.totalram - info.freeram) / (double)info.totalram)*100;
        printf("Memory Before: %f%%\n",percentUsed);
        printf("Killing thread.\n");
        pthread_exit(0);
      }
    }
    //threshold was already hit
    else{
      if(percentUsed < THRESHOLD){
        overThreshold = 0;
      }
      else{
        printf("Killing thread.\n");
        pthread_exit(0);
      }
    }
    percentUsed = ((double)(info.totalram - info.freeram) / (double)info.totalram)*100;
    printf("Current Memory Usage: %f%%\n",percentUsed);

}

void *test1(){
  int i;
  memCheck();
  int* p = malloc(2000000000);
  memset(p, 0, 2000000000);
  memCheck();
  pthread_exit(0);
}

void *test2(){
  memCheck();
  int* p = malloc(1500000000);
  memset(p, 0, 1500000000);
  memCheck();
  pthread_exit(0);
}

void *test3(){
  memCheck();
  int* p = malloc(1000000000);
  memset(p, 0, 1000000000);
  memCheck();
  pthread_exit(0);
}
