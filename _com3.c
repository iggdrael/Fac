#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
int 
main() 
{
  sleep(1) ;
  kill( getpid() , SIGQUIT ) ; 
  exit(0) ;
}

