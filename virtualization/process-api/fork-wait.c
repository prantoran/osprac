#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {

printf("hello world (pid:%d)\n", (int) getpid());

int rc = fork();

    if (rc < 0) { // fork failed; exit

        fprintf(stderr, "fork failed\n");

        exit(1);

    } else if (rc == 0) { // child (new process)

        printf("hello, I am child (pid:%d)\n", (int) getpid());

    } else { // parent goes down this path (main)

        // int rc_wait = wait(NULL);
        int rc_wait = waitpid(rc, NULL, WUNTRACED);


        printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n",
            rc, rc_wait, (int) getpid());

    }

    return 0;

}

/*

$ gcc -Wall -o a.out fork-wait.c; ./a.out

hello world (pid:26076)
hello, I am child (pid:26077)
hello, I am parent of 26077 (rc_wait:26077) (pid:26076)

*/