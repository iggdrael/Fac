#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
int 
main() 
{
  srandom(getpid());

  switch( random()%5 ) 
    {
    case 0 :
      sleep(1) ;
      exit(0) ;
    case 1 : 
      kill( getpid() , SIGINT ) ; 
      break ; 
    case 2 : 
      kill( getpid() , SIGQUIT ) ;
      break ; 
    case 3 :
      exit(1) ;
    case 4 : 
      exit(64) ;
    }
  exit(0) ;
}

