/*
Write a program that creates two children, and connects the standard output
of one to the standard input of the other, using the pipe() system call
*/

#include <stdio.h> 
#include <stdlib.h> // exit(1)
#include <unistd.h> // getpid(), fork()
#include <sys/wait.h> //wait()
#include <string.h>

int main() {

    int fd[2];
    pipe(fd);

    int rc1 = fork();

    if (rc1 < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    }

    if (!rc1) {
        // provide output
        printf("child pid: %d, getpid: %d\n", rc1, getpid());

        char s[] = "I love pizza <3";

        // closes up input side of pipe
        close(fd[0]);

        printf("child pid: %d, writing input: %s\n", getpid(), s);
        write(fd[1], s, (strlen(s) + 1));


        return 0;
    }


    int rc2 = fork();

    if (rc2 < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    }

    if (!rc2) {
        // get input
        printf("child pid: %d, getpid: %d\n", rc2, getpid());
        
        sleep(2);

        char readbuffer[100];

        // closes up output side of pipe 
        close(fd[1]);

        // Read in a string from the pipe
        int nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
        printf("child pid: %d, received string: %s\n", getpid(), readbuffer);

        return 0;
    }
    
    printf("parent pid: %d, children pid1: %d pid2: %d\n", getpid(), rc1, rc2);

    // try to wait for any children while there exists at least one
    
    pid_t pid;
    int status = 0;
    
    while ((pid=waitpid(-1,&status,0))!=-1) {
        printf("parent pid: %d, child process %d terminated\n",getpid(), pid);
    }

    return 0;
}

/*
parent pid: 693, children pid1: 694 pid2: 695
child pid: 0, getpid: 694
child pid: 0, getpid: 695
child pid: 694, writing input: I love pizza <3
parent pid: 693, child process 694 terminated
child pid: 695, received string: I love pizza <3
parent pid: 693, child process 695 terminated
*/