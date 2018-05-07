#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



int main(){
  char store[10];
  sprintf(store, "free");
  
  //see how much memory is free before allocating anything
  system(store);
  
  int* p = malloc(2000000000);
  memset(p, 0, 2000000000);
  
  //now that allocation has happened, check how much is free again
  system(store);
}