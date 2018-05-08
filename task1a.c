/*
  Authors:  Joe Holston and Dan Smith
  Course:  COMP 340, Operating Systems
  Date:    7 May 2018
  Description:   This file implements the
                 functionality required for
                 Program 3, Task 1.
  Compile with:  gcc -o task1a task1a.c 
  Run with:      ./task1a
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>



int main(){
  struct rusage r_usage;  //initializes the struct that we get the allocation info from
  
  //sets aside 1 gig of ram for the program
  int* p = malloc(1000000000);
  memset(p, 0, 1000000000);
  
  //tests and prints how much memory is allocated
  getrusage(RUSAGE_SELF,&r_usage);
  printf("Memory usage = %ld kB\n",r_usage.ru_maxrss);
  
  return 0;
}