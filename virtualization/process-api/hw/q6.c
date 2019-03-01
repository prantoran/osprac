/*
Write a slight modification of the previous program, this time using waitpid()
instead of wait(). When would waitpid() be useful?
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

        // hanging a process
        for (int i = 1; i > 0; i --) {}

        printf("child pid: %d, good", getpid());

    } else {

        int statlog; // will contain the pid of hanged child

        int rc_wait = waitpid(rc, &statlog, WNOHANG);
        sleep(1);
        
        printf("bye\nrc = %d rc_wait = %d statlog: %d\n",rc, rc_wait, statlog);

    }

    return 0;
}

/*

** not hanged **
child pid: 30190, goodbye
rc = 30190 rc_wait = 0 statlog: 0

** hanged **
child pid: 30149, goodbye
rc = 30149 rc_wait = 0 statlog: 4195984

** for some reason, waitpid is not waiting for child process to finish

*/