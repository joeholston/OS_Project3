#include <sys/sysinfo.h>
#include <stdio.h>

#define THRESHOLD 85

int main(int argc, char *argv[]){
  double percentUsed;
  struct sysinfo info;
  sysinfo (&info);

  percentUsed = ((double)(info.totalram - info.freeram) / (double)info.totalram)*100;
  //printf("%f\n", percentUsed);
  if(percentUsed >= THRESHOLD){
    printf("WARNING: System Memory Usage has exceeded %d%%\n", THRESHOLD);
  }
  else{
    printf("You're good!\n");
  }

  return 0;
}
