# TPEnseaSH

1. On crée un micro shell sur C dans lequel on affiche un message d'accueil avec un prompt

2. Exécution d'une commande

3. Gestion de la sortie. La prise en compte de la saisie étant prise en compte dans la question 1 on ajoute la prise en compte de CTRL + D (Retour donc le nombre d'input est de 1)

4. Affichage d'un code de retour

5. Mesure du temps

6. Pour pouvoir exécuter une commande complexe on sépare les éléments de la chaine de caractère saisie à chaque espace ou tabulation afin de les prendre en compte comme argument distinct. Et avec la fonction execvp on exécute alors chaque argument dans le tableau de pointeur dans lequel on les place. 
