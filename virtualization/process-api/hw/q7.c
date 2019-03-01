/*
Write a program that creates a child process, and then in the child closes
standard output (STDOUT FILENO). What happens if the child calls printf()
to print some output after closing the descriptor?
*/

#include <stdio.h> 
#include <stdlib.h> // exit(1)
#include <unistd.h> // getpid(), fork()
#include <sys/wait.h> //wait()

int main() {


    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    }

    if (!rc) {

        close(STDOUT_FILENO);

        printf("child pid: %d, getpid: %d\n", rc, getpid());

    } else {

        // wait(NULL);
        printf("parent pid: %d, child pid: %d\n", getpid(), rc);

    }

    return 0;
}

/*
parent pid: 30483, child pid: 30484

** no stdout from child process
*/