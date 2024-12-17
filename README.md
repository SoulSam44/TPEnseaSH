#TPEnseaSH

L'objectif de ce tp est de créer un terminal enseash qui nous permet d'éxécuter des commandes avec plusieurs arguments tout en affichant les codes de retours et le temps d'exécution des commandes.

1. On crée un micro shell sur C dans lequel on affiche un message d'accueil avec un prompt. On utilise la fonction read afin de lire l'input de l'utilisateur que l'on compare à la chaine de caractère "exit" afin de savoir si l'utilisateur désire quitter le terminal ou non.

2. On exécute une commande en créant un processus fils à l'aide d'un fork. On exécute alors l'input de l'utilisateur si il existe à l'aide de la fonction execlp, si la commande n'existe pas on affiche un message d'erreur à l'aide de perror. On faiit ensuite attendre le processus père jusqu'à la fin de l'exécution du fils. Pour l'instant on ne prend en compte que des argument simples

3. Gestion de la sortie. La prise en compte de la saisie étant prise en compte dans la question 1 on ajoute la prise en compte de CTRL + D.

4. On affiche le prompt avec un code de retour si le processus se termine normalement, si il est interrompu par un signal on affiche le code du signal. Pour cela on crée une variable buf dans laquelle on formate le texte du prompt avec le code à l'aide de snprintf et on l'écrit avec la fonction write.

5. Mesure du temps à l'aide de la fonction clock_gettime. Pour cela on mesure le temps entre la création du processus fils (avant l'exécution de la commande) et sa fin (après l'exécution de la commande) que l'on converti ensuite en millisecondes.

6. Pour pouvoir exécuter une commande complexe on sépare les éléments de la chaine de caractère saisie à chaque espace ou tabulation afin de les prendre en compte comme argument distinct à l'aide de strtok(). Et avec la fonction execvp on exécute alors chaque argument dans le tableau de pointeur args dans lequel on les place. 



Le nous a permis de comprendre et d'implémenter les fonctionnalités d'un terminal. Nous avons appris à manipuler les processus et à mesurer le temps d'exécution des commandes. Ce projet a renforcé nos compétences en programmation système en C et en gestion des processus.
