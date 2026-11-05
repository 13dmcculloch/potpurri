#include <sys/random.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
  while(~feof(stdin) && ~ferror(stdin))
  {
    char in_c, rnd_c;
    int ret;
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 150000;
    ret = setvbuf(stdout, NULL, _IONBF, 0);
    if(ret != 0)
    {
      perror("setvbuf");
      return 1;
    }
    rnd_c = 0;
    ret = fgetc(stdin);
    if (ret != EOF)
    {
      in_c = (char)ret;
    }
    else
    {
      return 1;
    }
    while(in_c != rnd_c)
    {
      ssize_t ret;
      ret = getrandom((void *)&rnd_c, sizeof rnd_c, 0);
      if(ret != 1)
      {
        return 1;
      }
      clock_nanosleep(CLOCK_REALTIME, 0, &ts, NULL);
    }
    putc(rnd_c, stdout);
  }
  return 0;
}
