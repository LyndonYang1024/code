#include <iostream>
#include <unistd.h>
#include <sys/time.h> 

int main() {
  struct timeval start, end;
  gettimeofday(&start, NULL);
  sleep(5);
  gettimeofday(&end, NULL);
  int64_t time_use = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
  std::cout << "time:" << time_use << "us" << std::endl;
}
