#include <sys/sysinfo.h>
#include <stdio.h>

#define THRESHOLD 85

void memCheck()
{
    double percentUsed;
    struct sysinfo info;
    sysinfo (&info);

    percentUsed = ((double)(info.totalram - info.freeram) / (double)info.totalram)*100;
    if(percentUsed >= THRESHOLD){
      printf("WARNING: System Memory Usage has exceeded %d%%\n", THRESHOLD);
    }
    else{
      printf("You're good!\n");
    }
}

int main(int argc, char *argv[]){

  memCheck();

  return 0;
}
