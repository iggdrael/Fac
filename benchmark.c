#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ECHEC -1
#define SUCCES 0
#define STOP  -1
#define ENTRANT 0
#define SORTANT 1

int main(int ac, char *av[]){

  printf("test\n");
  system("ls");
  printf("fin\n");

}
