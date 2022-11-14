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

int display_seats(int *mem, int semid, int number_of_seats, char *title)
{

  /* On protège l'accès à la shm */
  P(semid);

  /* Si le nombre de places dans la shm = nombre de places du parking
   * alors plus de voitures à faire sortir
   * */
  if (*mem != number_of_seats)
  {
    // Affichage du nombre de places
    printf("\t Pour le film %s, il reste %d places\n", title, *mem);
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
  unsigned int delais = 1;

  int shmid = atoi(argv[1]);
  int semid = atoi(argv[2]);
  int nb_places = atoi(argv[3]);
  char *title = argv[4];

  int *mem;

  /* Attachement du segment de mémoire partagée */
  mem = attacher_segment_memoire(mem, &shmid);

  while (1)
  {
    // Attente toutes les 5 secondes pour appel de la fonction d'affichage
    sleep(5);
    display_seats(mem, semid, nb_places, title);
  }

  return (0);
}
