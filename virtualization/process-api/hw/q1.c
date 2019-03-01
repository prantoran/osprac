/*
Write a program that calls fork(). Before calling fork(), have the main
process access a variable (e.g., x) and set its value to something (e.g., 100).
What value is the variable in the child process? What happens to the variable 
when both the child and parent change the value of x?
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    
    int x = 100;
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    }

    if (!rc) {

        printf("child pid: %d, getpid: %d x: %d\n", rc, getpid(), x);
        x = 200;
        printf("child pid: %d, getpid: %d updated x: %d\n", rc, getpid(), x);

    } else {

        wait(NULL);

        printf("parent pid: %d, child pid: %d x: %d\n", getpid(), rc, x);
        x = 300;
        printf("parent pid: %d, child pid: %d updated x: %d\n", getpid(), rc, x);

    }

    return 0;
}

/*
child pid: 0, getpid: 22425 x: 100
child pid: 0, getpid: 22425 updated x: 200
parent pid: 22424, child pid: 22425 x: 100
parent pid: 22424, child pid: 22425 updated x: 300
*/