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

FILE *sortie;                   /* On va ecrire dans un fichier que tout le monde va utiliser */

void
Vie_des_fils 
(int fd[2], int premier)
{

  int val = 0;                  /* tous les entiers sont stockes dans val */

  /*  Si ce processus est destine a devenir pere il a besoin  */
  int fd2[2];                   /*  d'une variable pour l'identificateur d'un tube */
  int status = SUCCES;          /*  d'une variable pour recuperer le status des fils */
  int pid = 0;                  /*  d'une variable pour l'identificateur d'un processus */

  do
  {
    read (fd[ENTRANT], &val, sizeof (int));

    if (val % premier != 0)
    {
      if (pid == 0 && val != STOP)
      {

        /* le fils prepare un tube */
        if (pipe (fd2) == -1)
        {
          perror ("impossible de creer un tube");
          exit (ECHEC);
        }
        /*  le fils se clone   */
        switch (pid = fork ())
        {
        case -1:
          perror ("impossible de creer un fils");
          exit (ECHEC);
        case 0:
          close (fd2[SORTANT]); /* fermeture de  la partie
                                   sortante  du  tube   non
                                   utilis\'ee */
          read (fd2[ENTRANT], &val, sizeof (int));      /* on r\'ecup\'ere  la 
                                                           premi\`ere valeur */

          fprintf (sortie, "%d\n", val);        /* sauvegarde de l'entier dans
                                                   un fichier */

          fflush (sortie);      /* jolie illustration du fait que p\`ere et
                                   fils partagent le m\^eme environnement.
                                   Sans  cette commande  au  moment  de la
                                   fermeture par fclose,   chaque     fils
                                   sauvegarde TOUT ce qui a \'et\'e sauv\'e par
                                   son p\`ere !!!  */
          Vie_des_fils (fd2, val);
        default:
          close (fd2[ENTRANT]); /* fermeture de la    partie  du
                                   tube inutilis\'ee */
        }
      }
      write (fd2[SORTANT], &val, sizeof (int)); /* le processus   passe
                                                   l'entier \`a son fils */
    }
  }
  while (val != STOP);

  close (fd[ENTRANT]);          /*  fermeture du tube puisqu'il ne sert plus */

  /*  si le processus est p\`ere il a des responsabilit\'es */
  if (pid != 0)
  {
    wait (&status);             /*  attendre la mort de ces fils */
    close (fd2[SORTANT]);       /*  fermer le tube de sortie */
  }
  fclose (sortie);              /*  dans tous les cas fermeture du fichier */
  exit (status);                /*  suicide */
}

int
main (int argc, char **argv)
{

  int fd[2];                    /* le tableau      suivant  contiendra    des   "files
                                   descriptor" */
  int status = SUCCES;          /* une variable pour r\'ecup\'erer le statut des
                                   fils */

  /*  ces variables servent \`a \'enumerer les entiers entre 2 et MaxVal */
  int val;
  int MaxVal;

  if (argc < 2)
    MaxVal = 7;
  else
    MaxVal = atoi (argv[1]);

  sortie = fopen ("nombrepremier", "w");

  /* La  commande pipe  permet   la communication entre processus   de
     mani\`ere unidirectionnel de fd[1] \`a fd[0] */
  if (pipe (fd) == -1)
  {
    perror ("impossible de creer un tube");
    exit (ECHEC);
  }

  /* clonage */
  switch (fork ())
  {
  case -1:
    perror ("impossible de creer un fils");
    exit (ECHEC);
  case 0:                      /*  action du fils  */

    close (fd[SORTANT]);

    read (fd[ENTRANT], &val, sizeof (int));     /* on r\'ecup\`ere la premi\`ere
                                                   valeur */

    fprintf (sortie, "%d\n", val);
    fflush (sortie);

    Vie_des_fils (fd, val);

  default:                     /* action du pere */

    close (fd[ENTRANT]);        /* fermeture  de  la partie  du  tube non
                                   utilis\'ee */

    for (val = 2; val <= MaxVal; val++)
      write (fd[SORTANT], &val, sizeof (int));

    /*  il faut envoyer le message de fin \`a ses fils */
    val = -1;
    write (fd[SORTANT], &val, sizeof (int));
  }

  wait (&status);               /*  le p\`ere attend la mort de son fils  */

  close (fd[SORTANT]);          /*  on ferme le tube */

  fclose (sortie);              /*  on ferme le fichier */

  return status;
}

