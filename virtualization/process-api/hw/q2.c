/*
Write a program that opens a file (with the open() system call) and then
calls fork() to create a new process. Can both the child and parent 
access the file descriptor returned by open()? What happens when they are
writing to the file concurrently, i.e., at the same time?
*/

#include <stdio.h> 
#include <stdlib.h> // exit(1)
#include <unistd.h> // getpid(), fork()
#include <fcntl.h> // open() and flags
#include <sys/wait.h> //wait()

int main() {

    close(STDOUT_FILENO);

    open("./q2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    }

    if (!rc) {

        printf("child pid: %d, getpid: %d\n", rc, getpid());

    } else {

        // wait(NULL);

        printf("parent pid: %d, child pid: %d\n", getpid(), rc);

    }

    return 0;
}
/*
$ cat q2.output
parent pid: 24104, child pid: 24105
parent pid: 24104, child pid: 24105
child pid: 0, getpid: 24105
child pid: 0, getpid: 24105
*/