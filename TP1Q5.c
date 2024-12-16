#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define BUFSIZE 256
#define PROMPT "enseash %%"
#define PROMPTEX "enseash [exit:%d|%.3f ms] %% "
#define PROMPTSIG "enseash [sign:%d|%.3f ms] %% "
#define WELCOME "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit' ou sur CTRL + D.\n"


void display_prompt (int return_code,double elapsed_time){
    char buf[BUFSIZE];

    if (WIFEXITED(return_code)){
         int len = snprintf(buf, BUFSIZE, PROMPTEX, WEXITSTATUS(return_code),elapsed_time);
        write(STDOUT_FILENO,buf,len);
    }
    else if (WIFSIGNALED(return_code)){
         int len = snprintf(buf, BUFSIZE, PROMPTSIG, WTERMSIG(return_code),elapsed_time);
        write(STDOUT_FILENO,buf,len);

    }
    else {
        write(STDOUT_FILENO,buf,strlen(PROMPT));
    }
}

void display_welcome (){
    write(STDOUT_FILENO,WELCOME,strlen(WELCOME));
}


int main () {
    char input [256];
    int return_code = 0; // Initialisation du code de retour
    double elapsed_time = 0.0;
    struct timespec start_time, end_time;
    display_welcome(); // affichage du message d'accueil
     while (1) {
        
        display_prompt(return_code,elapsed_time); //affichage du prompt

        //Lecture de la saisie de l'utilisateur
        ssize_t n = read(STDIN_FILENO, input, sizeof(input) - 1);
        if (n ==0) { //Appuie de CTRL+D
         write(STDOUT_FILENO, "Au revoir\n", 10);
         break;
        }
        if (n > 0) {
            input[n] = '\0';  // Terminer correctement la chaîne
            if (strncmp(input, "exit", 4) == 0) {
                write(STDOUT_FILENO, "Au revoir\n", 10);
                break;
            }

            //Début du chronomètre
            if (clock_gettime(CLOCK_MONOTONIC, &start_time) == -1) {
                perror("clock_gettime start");
                exit(EXIT_FAILURE);
            }

            pid_t pid = fork (); //Processus fils pour l'éxécution

            if (pid < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            
            if (pid == 0){  //Fils donc exécution de la commande
             execlp(input, input, (char *)NULL);

                // Si la commande n'existe pas 
                perror("execlp");
                exit(EXIT_FAILURE);

            } 
            else {  //Le père attend la fin du fils
                
                 waitpid(pid, &return_code, 0);
                  // Fin du chronomètre
            if (clock_gettime(CLOCK_MONOTONIC, &end_time) == -1) {
                perror("clock_gettime end");
                exit(EXIT_FAILURE);
            }

            // Calculer le temps écoulé en millisecondes
            elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
            elapsed_time += (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;

            }
        }
     }
    return 0;
}