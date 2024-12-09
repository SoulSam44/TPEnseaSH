#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <sys/type.h>
#include <unistd.h>

#define PROMPT "enseash %%"
#define WELCOME "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
void display_prompt (){
    write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
}

void display_welcome (){
    write(STDOUT_FILENO,WELCOME,strlen(WELCOME));
}


int main () {
    char input [256]
    display_welcome // affichage du messge d'accueil
     while (1) {
        display_prompt //affichage du prompt

        //Lecture de la saisie de l'utilisateur
        ssize_t n = read(STDIN_FILENO, input, sizeof(input) - 1);
        
        if (n > 0) {
            input[n] = '\0';  // Terminer correctement la chaîne
            if (strncmp(input, "exit", 4) == 0) {
                write(STDOUT_FILENO, "Au revoir\n", 10);
                break;
            }
        }
     }
    return 0
}
