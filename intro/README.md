- virtualizing the CPU
    -  Turning a single CPU (or small set of them) into a seemingly infinite number of CPUs

- policy
    -  if two programs want to run at a particular time, which should run?

- virtualizing memory
    - Each process accesses its own private virtual address space which is mapped onto the physical memory of the machine.

- thread
    - function running within the same memory space as other functions, with more than one of them active at a time.

- file system
    - manages the disk, responsible for storing any files the user creates in a reliable and efficient manner on the disks of the system

- To handle the problems of system crashes during writes, most file systems incorporate some kind of intricate write protocol, such as `journaling` or `copy-on-write`, carefully ordering writes to disk

- device driver
    - OS code to deal with a specific device

- protection
    - isolation of processes

- diff betwn system call and procedure call
    - a system call transfers control (i.e., jumps) into the OS while simultaneously raising the hardware privilege level.
    - User applications run in what is referred to as user mode which means the hardware restricts what applications can do.

- trap
    - special hardware instruction used to initialize a system call
    - hardware transfers control to a pre-specified trap handler (that the OS set up previously) and simultaneously raises the privilege level to kernel mode

- In kernel mode, OS has full access

- return-from-trap
    - instruction used to pass control back to the user
    - reverts to user mode, passing control back to where the application left off

#### from manpages
- getpid() returns the process ID (PID) of the calling process.
- pthread_create() create a new thread