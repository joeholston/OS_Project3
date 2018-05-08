#include <sys/sysinfo.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>



int main(int argc, char *argv[]){
  int i;    //initizlizes int for the for loop
  struct rusage r_usage;  //initializes the struct that we get the allocation info from
  pid_t pid;    //initializes pid store variable
  
  pid = fork();
  if(pid < 0){
    printf("Error Occurred");
    return 0;
  }
  else if(pid == 0){
    execv("task1a",NULL);   //calls separate process
    //tests and prints how much memory is allocated
    getrusage(RUSAGE_SELF,&r_usage);
		printf("Memory usage = %ld\n",r_usage.ru_maxrss);
  }
  else{
    execv("task1b",NULL);    //calls separate process
    //tests and prints how much memory is allocated
    getrusage(RUSAGE_SELF,&r_usage);
		printf("Memory usage = %ld\n",r_usage.ru_maxrss);
  }
  return 0;
}