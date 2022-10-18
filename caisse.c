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
  if (*mem == 0)
  {
    /* No more */
    printf("Plus de place, désolé : \n  ");
    printf("Dans la shm il y a %d places\n", *mem);
  }
  else
  {
    /* On écrit dans la shm */
    *mem = (*mem - nbplace);
    printf("Dans la shm il y a %d places\n", *mem);
    place_attribuee = true;
  }

  /* On protège l'accès à la shm */
  V(semid);

  return (place_attribuee);
}

/******************************************************************************/
/*
 * Programme principalp
 */
/******************************************************************************/
int main(int argc, char *argv[])
{

  unsigned int delais = 1;
  unsigned int random_places = 1;

  int shmid = atoi(argv[1]);
  int semid = atoi(argv[2]);

  int *mem;

  printf("Je suis %s, shmid=%d, semid=%d\n", argv[0], shmid, semid);

  /* Attachement du segment de mémoire partagée */
  mem = attacher_segment_memoire(mem, &shmid);

  while (1)
  {
    attente_aleatoire_traitement(delais);
    int nbplacesrandom = aleatoire_place();
    int actualdispo = *mem;
    if (nbplacesrandom != 0 && nbplacesrandom <= actualdispo)
    {
      printf("Un client se présente il voudrait %d places.\n", nbplacesrandom);
      while (achat_place(mem, semid, nbplacesrandom))
      {
        sleep(1);
      }
    }
  }

  return (0);
}
