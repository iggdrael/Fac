#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

#define ECHEC -1
#define SUCCES 0
#define STOP  -1
#define ENTRANT 0
#define SORTANT 1

int main(int ac,char *av[]){

  /* on fait executer K fois C par N processus */
  int K;        /* Nombre d'executions */
  int N;        /* Nombre de processus */
  char C[50];   /* Commande */
  
  if ( ac != 4 ){
    fprintf(stderr, "usage : %s <K> <C> <N>\n", av[0]);
    exit(STOP);
  }
  sscanf(av[1], "%d", &K);
  sscanf(av[2], "%s", C);
  sscanf(av[3], "%d", &N);

  int tube[2];
  pipe(tube);
  int k[50];
  double tabTemps[10];
  struct timeval T0, T1;
  double Ti;
  int i;

    for(i=0; i < N; i++){
      switch(fork()){
        case -1:
          perror("Erreur fork\n");
          exit(ECHEC);

      
        case 0:
          close(tube[ENTRANT]);

          gettimeofday(&T0, NULL);
          for(int j = 0; j < K; j++)
            system(C);

          gettimeofday(&T1, NULL);                

          Ti = T1.tv_sec - T0.tv_sec + (T1.tv_usec - T0.tv_usec) / 1000000.0;
          Ti /= K;

 					write(tube[SORTANT], &Ti, sizeof(double));
          close(tube[SORTANT]);

          exit(0);


        default :break;
          close(tube[SORTANT]);
          
          read(tube[ENTRANT], &(tabTemps[i]), sizeof(double));

         // sscanf(lireresultat,"%ld", &tabTemps);

          close(tube[ENTRANT]);
      }
    }
  int cr;
  while(wait(&cr) != -1);


  putchar('[');
  for(i = 0; i < N*K; i++){
      printf("%d, ", tabTemps[i]);
  }
  printf("]\n");

  return 0;
}
