#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define TEMPS_TRAITEMENT_MAX 3

void attente_aleatoire_traitement(unsigned int delais)
{

    /* Initialisation du désordre */
    srandom(time(NULL) % delais);

    /* Attente */
    sleep((unsigned int)(random() % TEMPS_TRAITEMENT_MAX));
}
