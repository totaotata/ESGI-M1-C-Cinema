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

  /* Reste-t-il des places libres ? */
  if (*mem < nbplace)
  {
    /* No more */
    printf("Plus de place, désolé : \n  ");
    printf("Dans la shm il y a %d places\n", *mem);
    return 0;
  }
  else
  {
    // int nbplacesrandom = aleatoire_place(random_places);
    // printf("Nombre place random => %d\n", nbplacesrandom);
    /* On écrit dans la shm */
    
    *mem = (*mem - aleatoire_place());
    printf("CAISSE => Dans la shm il y a %d places\n", *mem);
    printf("RANDOM %i \n", aleatoire_place());
    place_attribuee = true;
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
  printf("ARRIVE DANS CAISSE\n");
  unsigned int delais = 1;

  int shmid = atoi(argv[1]);
  int semid = atoi(argv[2]);

  int *mem;

  printf("Je suis %s , shmid=%d, semid=%d\n", argv[0], shmid, semid);

  /* Attachement du segment de mémoire partagée */
  mem = attacher_segment_memoire(mem, &shmid);
  // while (1)
  // {

  attente_aleatoire_traitement(delais);
  int actualdispo = *mem;
  int nbplacesrandom = aleatoire_place();
  printf("Nombre place random 0 => %d\n", nbplacesrandom);
  if (nbplacesrandom >= 0)
  {
    printf("Un client se présente il voudrait %d places.\n", nbplacesrandom);
    while (achat_place(mem, semid, nbplacesrandom))
    {
      sleep(1);
    }
  }
  else
  {
    return (0);
  }
  // }

  // return (0);
}
