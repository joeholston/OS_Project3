#include<stdio.h>
#include <sys/resource.h>

int main()
{
  struct rusage r_usage;
  int a, b, c;
  
  a = 12;
  b = 4;
  
  c = a + b;
  
  printf("Sum of the numbers %d + %d = %d\n", a, b, c);
  
  getrusage(RUSAGE_SELF,&r_usage);
  printf("Memory usage = %ld kB\n",r_usage.ru_maxrss);
  
  return 0;
}