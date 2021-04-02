#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctime>
#include <string>
#include <list>
#include <algorithm>

int main(int argc, char* argv[])
{
 if (argc < 4)
 {
    printf("Not enough arguments!\n");
    return -1;
 }

  int honey = 0;
  int bee_honey = std::atoi(argv[1]);
  int bear_eat_time = std::atoi(argv[2]);
  int bear_eat_rate = std::atoi(argv[3]);

  int bear_hungry_time = 0;

  printf("Start\n");
  pid_t num;
  std::list<pid_t> bees;
  for (int i=0; i<5; i++)
  {
    num = fork();
    if (num == 0)
    {
      execl("bee", "./bee", std::to_string(bee_honey).c_str(), NULL);
    }
    else if (num < 0)
    {
       printf("Error\n");
    }
    bees.push_back(num);
  }
  printf("End of create\n");


  printf("Start wait\n");
  int timer = std::time(0);

while (bear_hungry_time <= bear_eat_time)
{
    int code;
    printf("Wait for bee\n");
    pid_t end_bee = wait(&code);

    auto it = std::find(bees.begin(), bees.end(), end_bee);
    if (it != bees.end())
    {
      bees.erase(it);
    }

    code >>= 8;
    printf("Bee return %d honey\n", code);

    int pid = fork();
    if (pid == 0)
    {
       execl("bee", "./bee", std::to_string(bee_honey).c_str(), NULL);
    }
    else if (num < 0)
    {
       printf("Error\n");
       break;
    }
    bees.push_back(pid);

    int delta = std::time(0) - timer;
    if (delta == 0)
    {
       honey += code;
       continue;
    }
    if (honey >= delta * bear_eat_rate)
    {
      printf("Bear ate\n");
      honey -= delta * bear_eat_rate;
      bear_hungry_time = 0;
    }
    else
    {
      int need_honey = delta * bear_eat_rate;
      int lack = need_honey - honey;
      honey %= bear_eat_rate;
      bear_hungry_time += (lack / bear_eat_rate);
      printf("Bear hungry for %d\n", bear_hungry_time);
    }

    if (bear_hungry_time > bear_eat_time)
    {
      printf("Bear is dead!\n");
      break;
    }

   honey +=code;
   timer = std::time(0);
   printf("now honey %d\n", honey);

}
  printf("End wait\n");

  printf("Clear processes!\n");
  for (auto it=bees.begin(); it != bees.end(); it++)
  {
    kill(*it, SIGKILL);
  }
  printf("Success!\n");
  return 0;
}
