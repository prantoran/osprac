/*
 Write a program that calls fork() and then calls some form of exec() to
run the program /bin/ls. See if you can try all of the variants of exec(),
including (on Linux) execl(), execle(), execlp(), execv(), execvp(),
and execvpe(). Why do you think there are so many variants of the same
basic call?
*/

#include <stdio.h> 
#include <stdlib.h> // exit(1)
#include <unistd.h> // getpid(), fork()
#include <sys/wait.h> //wait()
#include <string.h>


void execute(
    int (*f) (const char *__file, char *const __argv[]),
    char *const __argv[]) {
    
    int rc = fork();

    if (rc < 0) { // fork failed; exit

        fprintf(stderr, "%s: fork failed\n", __argv[0]);

        exit(1);
    }
    
    if (!rc) { // child (new process)

        printf("%s: hello, I am child (pid:%d)\n",
            __argv[0], (int) getpid());

        char *myargs[2];

        myargs[0] = strdup("/bin/ls"); // program: "ls"

        myargs[1] = NULL; // marks end of array

        (*f)(myargs[0], myargs); // runs word count

        printf("%s: this shouldn’t print out\n",
            __argv[0]);
    } 
}


int main() {

    printf("hello world (pid:%d)\n", (int) getpid());

    char *myargs[2];

    myargs[0] = strdup("execvp"); // program: "ls"
    myargs[1] = NULL; // marks end of array

    execute(execvp, myargs);

    myargs[0] = strdup("execv"); // program: "ls"
    myargs[1] = NULL; // marks end of array

    execute(execv, myargs);

    int status = -1; // wait for any child process to finish
    int rc_wait = wait(&status);

    printf("hello, I am parent (rc_wait:%d) (pid:%d)\n",
        rc_wait, (int) getpid());

    return 0;
}

/*
hello world (pid:28883)
execvp: hello, I am child (pid:28884)
execv: hello, I am child (pid:28885)
a.out  q1.c  q2.c  q2.output  q3.c  q4.c  q5.c
a.out  q1.c  q2.c  q2.output  q3.c  q4.c  q5.c
hello, I am parent (rc_wait:28884) (pid:28883)
*/