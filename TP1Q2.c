#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE 256
#define PROMPT "enseash %"
#define WELCOME "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"

void display_prompt (){

    write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
}

void display_welcome (){

    write(STDOUT_FILENO,WELCOME,strlen(WELCOME));
}


int main () {

    char input [BUFSIZE];

    display_welcome();

     while (1) {

        display_prompt(); 

        //Reading the user input
        ssize_t n = read(STDIN_FILENO, input, sizeof(input) - 1);
        
        if (n > 0) {

            input[n] = '\0';  // To properly end the string

            if (strncmp(input, "exit", 4) == 0) {

                write(STDOUT_FILENO, "Au revoir\n", 10);

                break;
            }
            pid_t pid = fork (); //Creation of a child process for the execution

            if (pid < 0) {

                perror("fork");
                exit(EXIT_FAILURE);
            }
            
            if (pid == 0){  //Child process, we execute the command

                execlp(input, input, (char *)NULL);

                // If the command doesn't exist 
                perror("execlp");
                exit(EXIT_FAILURE);

            } 
            else {  //The parent process wait for the end of the child

                int status = 0;

                waitpid(pid, &status, 0);
            }
        }
     }
    return 0;
}