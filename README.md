## Start with :
```
make
```


# Au cinéma

Sujet : Simulation du système de vente de places de cinéma.
Chaque caisse est indépendante des autres mais les caisses vendent indépendamment les places
Chaque caisse a connaissance du nombre de places restantes et ne peut vendre que les places restantes.
Le public dispose d’un écran qui affiche le nombre restantes

Travail demandé : par groupe de 2, 3 ou 4 personnes écrire un programme qui prend en
paramètre :
• le nombre de caisses,
• le titre d’un film
• le nombre de places pour ce film.


Ce programme va engendrer les processus suivants :
• autant de processus caisse que de caisses demandées
• un processus afficheur mis à jour toutes les 5 secondes
Les caisses simuleront des clients (achat d’un nombre aléatoire de places compris entre 1
et 7) avec un temps de traitement aléatoire compris entre 1 et 3s.
Dès que le nombre de places restantes est égal à zéro, les caisses ferment (les processus
se terminent), seul l’afficheur reste actif.


Exemple :
cinema 15 "Matrix reloaded" 300
