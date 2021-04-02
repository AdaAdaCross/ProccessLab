#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  int seed = (int)getpid();
  srand(std::time(0)+seed);
  if (argc < 2)
  {
    printf("Not enough arguments\n");
    exit(-1);
  }
  int num = std::atoi(argv[1]);
  int sleep_time = rand() % 10;
  printf("%d\n", sleep_time);
  sleep(sleep_time);
  exit(num);
}
