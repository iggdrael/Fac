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

int f_sort(const void * a, const void * b) {
  return a - b;
}

int main(int ac, char *av[]){

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
  strcat(C, " >> /dev/null");
  sscanf(av[3], "%d", &N);

  struct timeval T0, T1;
  double Ti, Tsortant, resMediane;
  int i, cr;
  
  int tube[N][2];
	for(i = 0; i < N; i++) {
		pipe(tube[i]);
	}
  
  double *tabTemps = malloc(sizeof(double) * N);
  if (!tabTemps){
    perror("Problème Malloc\n");
    exit(ECHEC);
  }

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

        Ti = (T1.tv_sec - T0.tv_sec) + ((T1.tv_usec - T0.tv_usec) / 1000000.0);
        Ti /= K;

        write(tube[i][SORTANT], &Ti, sizeof(double));
        close(tube[i][SORTANT]);
        exit(0);

      default:
        close(tube[i][SORTANT]);
        read(tube[i][ENTRANT], &Tsortant, sizeof(double));
        tabTemps[i] = Tsortant;
        printf("T%d : %f s\n", i, Tsortant);
        close(tube[i][ENTRANT]);
        break;
      }
  }

  qsort(tabTemps, N, sizeof(double), f_sort);

  putchar('[');
  for(i = 0; i < N; i++){
      printf("%f, ", tabTemps[i]);
  }
  printf("]\n");
  
  resMediane = tabTemps[N / 2];
  if (N % 2 == 0){
    resMediane +=  tabTemps[N / 2 - 1];
    resMediane /= 2;
  }
  
  printf("Le temps d'execution moyen de %s est de %f s\n", av[2], resMediane);
  
  free(tabTemps);
  return 0;
}
