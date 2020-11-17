#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>


#include <sys/ipc.h>
#include <sys/sem.h>


int main(int argv,char *argc[]){

  if(argv != 4){
    printf("nombre de parametres pas bonne,il doit est 4");
  }

/*cest nombre de fois d'execution de commande*/
  int nombre_de_fois = atoi(argc[1]);

  /*cest le nombre de process de fils*/
   int nombre_de_fils = atoi(argc[3]);

/*creer le pipe*/
int tube[2];
pipe(tube);

/*creer string for lire le resultat de fils*/
char lireresultat[10];

/*creer le tableau de resultat*/
double *k = malloc(sizeof(double)*nombre_de_fils);

/*string for mettre le */
char times[10];

struct timeval t1,t2;

double timeuse;

  char *c = malloc(sizeof(argc[2]));
  strcpy(c,argc[2]);

int i = 0;

  for(;i < nombre_de_fils;i++){
    switch(fork()){
      /*case de erreir*/
      case -1:printf("prob de fork");exit(0);

      /*case de fils*/
      case 0:

              gettimeofday(&t1,NULL);

              for(int k = 0;k<nombre_de_fois;k++){
                  exec(c);
             }

             gettimeofday(&t2,NULL);

            timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;//calculer le temps

            timeuse/=nombre_de_fois;//calculer le temps moyen

            sprintf(times,"%2lf",timeuse);

             close(tube[0]);

             /*envoyer a process pere par tube*/
             write(tube[1],times,10);

             close(tube[1]);

             exit(0);


      default :
            close(1);

            read(tube[0],&lireresultat,10);

            sscanf(lireresultat,"%2lf",k[i]);

            close(tube[0]);
    }
  }
  while(wait(NULL) != -1);

double change;

/*on mettre le sequence en croissante*/
  for(i = 0;i < nombre_de_fils-1;i++){
    for(int j = i+1;j < nombre_de_fils;j++){
        if(k[i] < k[j]){
          change = k[i];
          k[i] = k[j];
          k[j] = change;
        }
    }
  }

/*on affiche les resultata*/
  for(i = 0;i < nombre_de_fils-1;i++){
      printf("le process %d coute %f microsecond \n",i,k[i]);
}
  free(k);

  return 0;
}
