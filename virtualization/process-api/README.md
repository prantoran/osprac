PID - process identifier

fork()
- creates an almost exact copy of the calling process
- as if both the copies of the process are about to return from the fork() system call
- created child process starts execution from the fork() call, not from the start of the main() function.
- child process has its own copy of the addresss space, registers, PC etc.
- but the return value of fork() for parent and child processes are different
- child receive a return code of zero from fork()


wait()
- pid_t wait(int *status)
- pid_t waitpid(pid_t pid, int *status, int options)
- when wait() is called, this system call won't return until the child has run and exited

exec()
- run an external program different from the calling program
- how it works:
    - given the name of an executable and arguments, it loads code (and static data) from that executable and overwrites its current code segment (and current static data)
    - heap and stack are re-initialized
- does not create a new process
- transforms the currently running program
- a successful call to exec() never returns

The shell is just an user program which waits for you to type something into it.
When you type a command, the shell figures out where in the file system the executable resides, calls fork() to create a new child process to run the command, calls some variant of exec() to run the command, and then waits for the command to complete by calling wait().


UNIX systems start looking for free file descriptors at zero. In this case, STDOUT FILENO will be the first available one and thus get assigned when open() is called. Subsequent writes by the child process to the standard output file descriptor, for example by routines such as printf(), will then be routed transparently to the newly-opened file instead of the screen.