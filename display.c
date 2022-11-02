#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/******************************************************************************/
/*
 * Fonctions externes
 */
/******************************************************************************/
extern void attente_aleatoire_traitement();
extern int *attacher_segment_memoire();
extern int P();
extern int V();

/******************************************************************************/
/*
 * Fonctions
 */
/******************************************************************************/

int display_seats(int *mem, int semid, int number_of_seats)
{

  /* On protège l'accès à la shm */
  P(semid);

  /* Si le nombre de places dans la shm = nombre de places du parking
   * alors plus de voitures à faire sortir
   * */
  if (*mem != number_of_seats)
  {
    /* On écrit dans la shm */
    // *mem=(*mem + 1);
    printf("\t DISPLAY => Dans la shm il y a %d places\n", *mem);
  }

  /* On protège l'accès à la shm */
  V(semid);

  return (0);
}

/******************************************************************************/
/*
 * Programme principal
 */
/******************************************************************************/
int main(int argc, char *argv[])
{
 printf("ARRIVE DANS DISPLAY\n");
  unsigned int delais = 1;

  int shmid = atoi(argv[1]);
  int semid = atoi(argv[2]);
  int nb_places = atoi(argv[4]);

  int *mem;

  /* Attachement du segment de mémoire partagée */
  mem = attacher_segment_memoire(mem, &shmid);

  while (1)
  {
    attente_aleatoire_traitement(delais);
    printf("\tUn siège est réservé ! \n");
    display_seats(mem, semid, nb_places);
  }

  return (0);
}
