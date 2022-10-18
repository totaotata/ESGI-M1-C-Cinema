
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "shm_const.h"

extern int creer_initialiser_semaphore();
extern int *attacher_segment_memoire();
extern int P();
extern int V();

extern int creer_segment_memoire();

int main(int argc, char *argv[])
{
    pid_t pid_caisse;  /* no du processus du processus caisse  */
    pid_t pid_display; /* no du processus du processus display */

    int code_retour_fin_caisse;
    int code_retour_fin_display;

    int number_of_seats;       /* Pour écriture dans la shm */
    char *number_of_seats_str; /* Pour conversion du semid (int) en chaine */

    int shmid; /* Id du segment de mémoire partagé */
    int semid; /* Id du sémaphore */

    char shmid_str[20]; /* Pour conversion du shmid (int) en chaine */
    char semid_str[20]; /* Pour conversion du semid (int) en chaine */

    int *mem; /* Adresse du segment de mémoire partagée */

    char param_gnome_terminal[80];

    if (argc != 4)
    {
        fprintf(stderr, "Usage : %s caisse_number, film_title, number_of_seats\n", argv[1], argv[2], argv[3]);
        return (3);
    }

    number_of_seats_str = argv[3];
    number_of_seats = atoi(number_of_seats_str);

    /* Avant de créer les fils :
     * - on crée le semaphore
     * - on crée le segment de mémoire partagé
     * - on s'attache le segment de mémoire partagé
     * - on initialise le noombre de places de parking libres dans la shm
     */

    /* Création sémaphore */
    creer_initialiser_semaphore(CLE_SEM, &semid);

    /* Création segment de mémoire partagé */
    creer_segment_memoire(CLE_SHM, &shmid);

    /*
    printf("DEBUg : parking : shmid=%d\n", shmid);
    */

    /* Attachement du segment de mémoire partagée */
    mem = attacher_segment_memoire(mem, &shmid);

    /* Pas besoin de sémaphore on est seul :-) */
    *mem = number_of_seats;

    /* Conversion des shmid et semid  (int) en chaine pour appel programme externe */
    sprintf(shmid_str, "%d", shmid);
    sprintf(semid_str, "%d", semid);

    pid_display = fork();
    if (pid_display == -1)
    {
        printf("error\n");
    }
    else if (pid_display == 0)
    {
        printf("création display\n");
        execl("display", "display", shmid_str, semid_str, number_of_seats_str, NULL);
    }
    int nb_caisse = atoi(argv[1]);
    for (int i = 1; i <= nb_caisse; i++)
    {
        printf("numéro %d", i);
        pid_t pid_caisse = fork();
        if (pid_caisse == 0)
        {
            printf("création caisse\n");
            execl("caisse", "caisse", shmid_str, semid_str, NULL);
            // exit(0); // child process
        }
        // parent process
        printf("At i = %d, process %d is terminated.\n", i, pid_caisse);
        waitpid(pid_display, &code_retour_fin_display, 0);
        // waitpid(pid_caisse, &code_retour_fin_caisse, 0);

        wait(NULL);
    }
    /* création du fils caisse */
    // pid_caisse = fork();

    // if (pid_caisse == -1) {
    //     /* Erreur */
    //     perror("pb fork sur création caisse");
    //     return(1);
    // }

    // if (pid_caisse == 0) {
    //     /*
    //     printf("Je suis le fils caisse, je vais faire execl dans 10s shmid_str=%s, semid_str=%s\n", shmid_str, semid_str);
    //     */
    //     execl("caisse", "caisse", shmid_str, semid_str, NULL);
    // }

    // if (pid_caisse > 0) {
    //     /* processus père */

    //     /* création du fils display */
    //     pid_display = fork();

    //     if (pid_display == -1) {
    //         /* Erreur */
    //         perror("pb fork sur création display");
    //         return(1);
    //     }

    //     if (pid_display == 0) {
    //          execl("display", "display", shmid_str, semid_str, number_of_seats_str, NULL);
    //     }

    //     /* processus père */

    //     printf("Père, on attend 1000s \n");
    //     sleep(1000);

    //     waitpid(pid_caisse, &code_retour_fin_caisse, 0);

    //     waitpid(pid_display, &code_retour_fin_display, 0);

    //     printf("P: processus père fin\n");
    //     return(0);
    // }
}
