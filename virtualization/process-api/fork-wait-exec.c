#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    printf("hello world (pid:%d)\n", (int) getpid());

    int rc = fork();

    if (rc < 0) { // fork failed; exit

        fprintf(stderr, "fork failed\n");

        exit(1);

    } else if (rc == 0) { // child (new process)

        printf("hello, I am child (pid:%d)\n", (int) getpid());

        char *myargs[3];

        myargs[0] = strdup("wc"); // program: "wc" (word count)

        myargs[1] = strdup("fork-wait-exec.c"); // argument: file to count

        myargs[2] = NULL; // marks end of array

        execvp(myargs[0], myargs); // runs word count

        printf("this shouldn’t print out");

    } else { // parent goes down this path (main)

        int rc_wait = wait(NULL);

        printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n",
            rc, rc_wait, (int) getpid());

    }

    return 0;

}

/*

$ gcc -Wall -o fork.out fork-wait-exec.c; ./fork.out

hello world (pid:26830)
hello, I am child (pid:26831)
 45 122 968 fork-wait-exec.c
hello, I am parent of 26831 (rc_wait:26831) (pid:26830)

*/