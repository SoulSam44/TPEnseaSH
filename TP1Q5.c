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

    if (WIFEXITED(return_code)){ //If the process end without interruption we display the return code
        
        int len = snprintf(buf, BUFSIZE, PROMPTEX, WEXITSTATUS(return_code),elapsed_time);

        write(STDOUT_FILENO,buf,len);
    }
    else if (WIFSIGNALED(return_code)){ //If the process is interrupted because of a signal we display the signal code
        
        int len = snprintf(buf, BUFSIZE, PROMPTSIG, WTERMSIG(return_code),elapsed_time);

        write(STDOUT_FILENO,buf,len);

    }
    else { //Default prompt if no return or signal code

        write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
    }
}

void display_welcome (){

    write(STDOUT_FILENO,WELCOME,strlen(WELCOME));
}


int main () {

    char input [BUFSIZE];
    int return_code = 0; 
    double elapsed_time = 0.0;
    struct timespec start_time, end_time;

    display_welcome();

     while (1) {
        
        display_prompt(return_code,elapsed_time); 

         //Reading the user input
        ssize_t n = read(STDIN_FILENO, input, sizeof(input) - 1);

        if (n ==0) { //Input of CTRL+D
        
            write(STDOUT_FILENO, "Au revoir\n", 10);
        
            break;
        }
        if (n > 0) {

            input[n] = '\0';   // To properly end the string

            if (strncmp(input, "exit", 4) == 0) {
                
                write(STDOUT_FILENO, "Au revoir\n", 10);
                
                break;
            }

            //Start of the clock
            if (clock_gettime(CLOCK_MONOTONIC, &start_time) == -1) {
                perror("clock_gettime start");
                exit(EXIT_FAILURE);
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
                
                waitpid(pid, &return_code, 0);
                 
            // End of the clock
            if (clock_gettime(CLOCK_MONOTONIC, &end_time) == -1) {
                
                perror("clock_gettime end");
                exit(EXIT_FAILURE);
            }

           // Computation of the time in milliseconds
            elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
            elapsed_time += (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;

            }
        }
     }
    return 0;
}