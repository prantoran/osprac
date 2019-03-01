/*
Now write a program that uses wait() to wait for the child process to finish
in the parent. What does wait() return? What happens if you use wait()
in the child?
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

        wait(NULL);

        printf("child pid: %d, good", getpid());

    } else {

        int rc_wait = wait(NULL);
        
        printf("bye\nrc_wait = %d\n", rc_wait);

    }

    return 0;
}

/*
child pid: 28668, goodbye
rc_wait = 28668
*/