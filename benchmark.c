#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#define ECHEC -1
#define SUCCES 0
#define STOP  -1
#define ENTRANT 0
#define SORTANT 1

int K;
int N;
char C[50];

int main(int ac, char *av[]){
 struct timeval t1, t2;
 
 printf("1: %d\n", gettimeofday(&t1,NULL));
 printf("1: %ld\n", t1.tv_usec);
 
 execl("ls", "ls", NULL);
 
 
 printf("2: %d\n", gettimeofday(&t1,NULL));
 printf("2: %ld\n", t2.tv_usec);
        
 printf("\nLa commande a mit %ld ms à s'executer\n", t2.tv_usec-t1.tv_usec);



 //execlp("ls", "ls", NULL);
 /* int i;
  int pid[2];
  int tab[50];

  if ( ac != 4 ){
    fprintf(stderr, "usage : %s <K> <C> <N>\n", av[0]);
    exit(STOP);
  }
  sscanf(av[1], "%d", &K);
  sscanf(av[2], "%s", C);
  sscanf(av[3], "%d", &N);

  for (int i = 0 ; i < N ; i++) {
    switch(fork()) {
      case -1:
        printf("Erreur fork\n");
        exit(STOP);
      case 0:
        exit(i);
    }
   // kill(getpid(), SIGQUIT);
  }
  
  int cr;
  while (wait(&cr) != -1)  
      for (i = 0 ; i < N ; i++){
        tab[i] = cr;
        printf("%d ", tab[i]);
      }
  putchar('\n');*/
}
