PID - process identifier, process ID

fork()
- used in UNIX systems to create a new process.
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
- allows a child to break free from its similarity to its parent and execute an entirely new program.

The shell is just an user program which waits for you to type something into it.
When you type a command, the shell figures out where in the file system the executable resides, calls fork() to create a new child process to run the command, calls some variant of exec() to run the command, and then waits for the command to complete by calling wait(). When the child completes, the shell returns from wait() and prints out a prompt again, ready for your next command.

A UNIX shell commonly uses fork(), wait(), and exec() to launch user commands; the separation of fork and exec enables features like input/output redirection, pipes, and other cool features, all without changing anything about the programs being run.

Process control is available in the form of signals, which can cause
jobs to stop, continue, or even terminate.

kill()

Ctrl-c sends a SIGINT (interrupt) to the process (normally terminating
it) and Ctrl-z sends a SIGTSTP (stop) signal thus pausing the process
in mid-execution (you can resume it later with a command, e.g., the fg
built-in command found in many shells)

signal()
- used to catch external events and signals
- when a particular signal is delivered to a process, it will suspend its normal execution and run a particular piece of code in response to the signal

ps
- see running processes

top
- displays the processes of the system and how much CPU and other resources they are eating up.
