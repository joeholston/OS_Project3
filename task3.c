#include <sys/sysinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#define THRESHOLD 85
int overThreshold = 0;

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
      }
    }
    //threshold was already hit
    else{
      if(percentUsed < THRESHOLD){
        overThreshold = 0;
      }
    }
    printf("%f%%\n",percentUsed);
}

void test1(){
  char store[10];

  struct rusage r_usage;

  int* p = malloc(2000000000);
  memset(p, 0, 2000000000);
}

void test2(){
  char store[10];

  struct rusage r_usage;

  int* p = malloc(1000000000);
  memset(p, 0, 1000000000);
  memCheck();
  free(p);
  memCheck();
}

void test3(){
  char store[10];

  struct rusage r_usage;

  int* p = malloc(1000000000);
  memset(p, 0, 1000000000);
}

int main(int argc, char *argv[]){

  memCheck();
  test1();
  memCheck();
  test2();
  test3();
  memCheck();
  test3();
  memCheck();
  return 0;
}
