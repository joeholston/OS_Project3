#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>



int main(){
  char store[10];
  
  struct rusage r_usage;
  
  int* p = malloc(2000000000);
  memset(p, 0, 2000000000);
  
  getrusage(RUSAGE_SELF,&r_usage);
  printf("Memory usage = %ld kB\n",r_usage.ru_maxrss);
  
  return 0;
}