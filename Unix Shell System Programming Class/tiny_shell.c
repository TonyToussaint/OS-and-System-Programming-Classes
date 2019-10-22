//#Name: Anthony Toussaint
//#Date: 2/15/18
//#Tech shell

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

char **get_input(char *);

/*int cd(char *path) {
  return chdir(path);
  } */

int main() {
  char **command;
  char *input;
  pid_t child_pid;
  int stat_loc;

  int cd(char *path) {
    return chdir(path);
  }

  while (1) {
    input = readline("Techsh> ");
    command = get_input(input);

    if (!command[0]) { //if user presses enter with no input//
      continue;
     }

    if (strcmp(command[0],"cd") == 0) { //Change directory//
      int status;
      status = chdir(command[1]);
      if (status == -1) {
	printf("Couldn't find dir: %s\n", command[1]);
      }	
	// chdir(command[1]);
      continue;
    }

    if (strcmp(command[0],"exit") == 0) { //Exits the shell//
      return 0;
    
    }

    child_pid = fork();
    if (child_pid < 0) { //error handling for if the fork fails//
      perror("Unable to fork");
      exit(1);
    }
    
    if (child_pid == 0) {
      //Spawns the child process//
      execvp(command[0], command);
      printf("%s : command not found\n", command[0]);
   
    } else {
      waitpid(child_pid, &stat_loc, WUNTRACED);
    }

    free(input);
    free(command);
    
  }

}

char **get_input(char *input) {
  char **command = malloc(8 * sizeof(char *));
  char *separator = " ";
  char *parsed;
  int index = 0;

  parsed = strtok(input, separator);
  while (parsed != NULL) {
    command[index] = parsed;
    index++;

    parsed = strtok(NULL, separator);
  }

  command[index] = NULL;
  return command;

}

  
