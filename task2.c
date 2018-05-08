/*
  Authors:  Joe Holston and Dan Smith
  Course:  COMP 340, Operating Systems
  Date:    7 May 2018
  Description:   This file implements the
                 functionality required for
                 Program 3, Task 2.
  Compile with:  gcc -o task2 task2.c  
  Run with:      ./task2
*/

#include <sys/sysinfo.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>



int main(int argc, char *argv[]){
  int i;    //initializes int for the for loop
  struct rusage r_usage;  //initializes the struct that we get the allocation info from
  pid_t pid;     //initializes pid storage variable
  
  //printf("The parent pid is %d\n", getpid());
  for(i = 0; i < 3; i++){
    
    if(fork() == 0){     //tests if it is a child
    
      //tests and prints how much memory is allocated
      getrusage(RUSAGE_SELF,&r_usage);
      printf("Memory usage = %ld kB\n",r_usage.ru_maxrss);
    }
  }
  return 0;
}