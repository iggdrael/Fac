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

#define K 2
#define C "ls"
#define N 2

int main(int ac, char *av[]){
  int i;
  
  for (i = 0; i < N; i++){
    fork();
    //system("ls");
  }
  printf("oui\n");


}
