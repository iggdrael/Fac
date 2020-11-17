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

  /*creer le pipe*/
  int tube[2];
  pipe(tube);

  /*creer string for lire le resultat de fils*/
  char lireresultat[10];

  /*creer le tableau de resultat*/
  int k[50];

  /*string for mettre le */
  char times[10];

  struct timeval t1,t2;

  double timeuse;

  int i;

    for(i=0; i < N; i++){
      switch(fork()){
        /*case de erreir*/
        case -1:perror("prob de fork");exit(0);

        /*case de fils*/
        case 0:

               gettimeofday(&t1,NULL);

                for(int k = 0;k<K;k++){
                    execlp(C,C,NULL);
               }

               printf("ouiiiii\n");
               //gettimeofday(&t2,NULL);
               //printf("\nLa commande a mit %ld ms à s'executer\n", t2.tv_usec-t1.tv_usec);

          //    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;//calculer le temps

          //    timeuse/=K;//calculer le temps moyen

          //    sprintf(times,"%2lf",timeuse);

          //     close(tube[0]);

               /*envoyer a process pere par tube*/
         //      write(tube[1],times,10);

        //close(tube[1]);

               exit(0);


        default :break;
             // close(1);

            //  read(tube[0],&lireresultat,10);

           //   sscanf(lireresultat,"%d",&k[i]);

            //  close(tube[0]);
      }
    }
  int cr;
    while(wait(&cr) != -1);

  /*on affiche les resultata*/
    putchar('[');
    for(i = 0; i < N; i++){
        printf("%d, ", k[i]);
  }
  printf("]\n");

  return 0;
}
