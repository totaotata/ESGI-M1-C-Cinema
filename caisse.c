#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

/******************************************************************************/
/*
 * Fonctions externes
 */
/******************************************************************************/
extern void attente_aleatoire_traitement();
extern int aleatoire_place();
extern int *attacher_segment_memoire();
extern int P();
extern int V();

/******************************************************************************/
/*
 * Fonctions
 */
/******************************************************************************/

bool achat_place(int *mem, int semid, int nbplace)
{
  bool place_attribuee = false;

  /* On protège l'accès à la shm */
  P(semid);

  /* Vérification si places suffisantes ? */
  if (*mem < aleatoire_place() && *mem == 0)
  {
    /* Plus de place */
    printf("Plus de place désolé, fermeture des caisses bon film ! \n  ");
    // printf("Dans la shm il y a %d places\n", *mem);
    return 0;
  }
  else if (*mem < aleatoire_place() && *mem > 0)
  {
    place_attribuee = true;
    // printf("Pas assez de place pour cette demande de %d places.\n", aleatoire_place());
    // printf("Dans la salle il reste %d places\n", *mem);
  }
  else
  {
    *mem = (*mem - aleatoire_place());
    place_attribuee = true;
    // printf("CAISSE => Dans la shm il y a %d places\n", *mem);
    // printf("RANDOM %i \n", aleatoire_place());
  }

  /* On protège l'accès à la shm */
  V(semid);
  return (place_attribuee);
}

/******************************************************************************/
/*
 * Programme principal
 */
/******************************************************************************/
int main(int argc, char *argv[])
{
  unsigned int delais = 1;

  int shmid = atoi(argv[1]);
  int semid = atoi(argv[2]);

  int *mem;

  // printf("Je suis %s , shmid=%d, semid=%d\n", argv[0], shmid, semid);

  /* Attachement du segment de mémoire partagée */
  mem = attacher_segment_memoire(mem, &shmid);

  attente_aleatoire_traitement(delais);
  int actualdispo = *mem;
  int nbplacesrandom = aleatoire_place();

  // printf("Un client se présente il voudrait %d places.\n", nbplacesrandom);
  while (1)
  {
    achat_place(mem, semid, nbplacesrandom);
    sleep(1);
  }
}
