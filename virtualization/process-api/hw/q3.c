/*
Write another program using fork(). The child process should print “hello”;
the parent process should print “goodbye”. You should try to ensure that
the child process always prints first; can you do this without calling 
wait() in the parent?
*/

#include <stdio.h> 
#include <stdlib.h> // exit(1)
#include <unistd.h> // getpid(), fork()


int main() {

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    }

    if (!rc) {

       printf("good");

    } else {

        sleep(1);

        printf("bye\n");

    }

    return 0;
}