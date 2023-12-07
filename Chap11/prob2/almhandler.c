#include <stdio.h>
#include <signal.h>
void alarmHandler();

int main( )
{
   signal(SIGALRM, alarmHandler);
   alarm(5);
   printf("무한 루프 \n");
   while (1) {
      sleep(1);
      printf("1초 경과 \n");
   }
   printf("실행되지 않음 \n");
}

void alarmHandler(int signo)
{
   printf("일어나세요\n");
   exit(0);
}

