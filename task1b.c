/*
  Authors:  Joe Holston and Dan Smith
  Course:  COMP 340, Operating Systems
  Date:    7 May 2018
  Description:   This file implements the
                 functionality required for
                 Program 3, Task 1.
  Compile with:  gcc -o task1b task1b.c 
  Run with:      ./task1b
*/

#include<stdio.h>
#include <sys/resource.h>


//small process that only does simple addition

int main()
{
  struct rusage r_usage;
  int a, b, c;
  
  //adds two numbers
  a = 12;
  b = 4;
  
  //stores it in c
  c = a + b; 
  
  //prints out the sum
  printf("Sum of the numbers %d + %d = %d\n", a, b, c);
  
  //prints out memory allocated
  getrusage(RUSAGE_SELF,&r_usage);
  printf("Memory usage = %ld kB\n",r_usage.ru_maxrss);
  
  return 0;
}