#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define ACHAT_MAX 7

int aleatoire_place() {

/* Initialisation du désordre */
srandom(time(NULL));

/* Return random */
return((int)(random() % ACHAT_MAX));

}