
time sharing

challenges
- performance
  - reducing excessive overhead of virtualization
- control
  - important to os
  - without control, a process could run forever or access unauthorized info

both hardware and os support required

`limited direct execution` (LDE) Protocol
- direct execution
  - to run a program, the os creates a process entry for it in a process list, allocates some memory for it, loads the program code into memory (from disk), locates its entry point (i.e., the main() routine), jumps to it
  - two problems
    - ensuring the program does not do anything crazy
    - how to stop it running and switch to another process for time sharing


problem1: restricted operations
- A process must be able to perform I/O and some other restricted operations, but without giving the process complete control over the system. How can the OS and hardware work together to do so?

ASIDE: WHY SYSTEM CALLS LOOK LIKE PROCEDURE CALLS
You may wonder why a call to a system call, such as open() or read(),
looks exactly like a typical procedure call in C; that is, if it looks just like
a procedure call, how does the system know it’s a system call, and do all
the right stuff? The simple reason: it is a procedure call, but hidden inside that procedure call is the famous trap instruction. More specifically,
when you call open() (for example), you are executing a procedure call
into the C library. Therein, whether for open() or any of the other system calls provided, the library uses an agreed-upon calling convention
with the kernel to put the arguments to open in well-known locations
(e.g., on the stack, or in specific registers), puts the system-call number
into a well-known location as well (again, onto the stack or a register),
and then executes the aforementioned trap instruction. The code in the
library after the trap unpacks return values and returns control to the
program that issued the system call. Thus, the parts of the C library that
make system calls are hand-coded in assembly, as they need to carefully
follow convention in order to process arguments and return values correctly, as well as execute the hardware-specific trap instruction. And now
you know why you personally don’t have to write assembly code to trap
into an OS; somebody has already written that assembly for you.

user mode
- can't issue I/O requests


kernel mode
- os mode

TIP: USE PROTECTED CONTROL TRANSFER
The hardware assists the OS by providing different modes of execution.
In `user mode`, applications do not have full access to hardware resources.
In `kernel mode`, the OS has access to the full resources of the machine.
Special instructions to `trap` into the kernel and `return-from-trap` back to
user-mode programs are also provided, as well as instructions that allow
the OS to tell the hardware where the `trap table` resides in memory.

`trap table`
- set up by os at boot time
- tell the hardware what code to run when certain exceptional events occur.
  - harddisk interrupt
  - keyboard interrupt
  - system call
- `trap handlers`
  - their addresses
- hence the hardware knows waht code to jumpt to when system calls or exceptional events take place

`system-call number`
- for each system call
- The user code is thus responsible for placing the desired system-call number in a register or at a specified location on the stack; the OS, when handling the system call inside the trap handler, examines this number, ensures it is valid, and, if it is, executes the corresponding code. This level of indirection serves as a form of protection; user code cannot specify an exact address to jump to, but rather must request a particular service via number

TIP: BE WARY OF USER INPUTS IN SECURE SYSTEMS
Even though we have taken great pains to protect the OS during system calls (by adding a hardware trapping mechanism, and ensuring all calls to the OS are routed through it), there are still many other aspects to implementing a secure operating system that we must consider. One of these is the handling of arguments at the system call boundary; the OS must check what the user passes in and ensure that arguments are properly specified, or otherwise reject the call. For example, with a write() system call, the user specifies an address of a buffer as a source of the write call. If the user (either accidentally or maliciously) passes in a “bad” address (e.g., one inside the kernel’s portion of the address space), the OS must detect this and reject the call. Otherwise, it would be possible for a user to read all of kernel memory; given that kernel (virtual) memory also usually includes all of the physical memory of the system, this small slip would enable a program to read the memory of any other process in the system. In general, a secure system must treat user inputs with great suspicion. Not doing so will undoubtedly lead to easily hacked software, a despairing sense that the world is an unsafe and scary place, and the loss of job security for the all-too-trusting OS developer.


`TSS` - Task State Segment
- used to store the segment selector and stack pointer of the process' kernel stack.


THE CRUX: HOW TO REGAIN CONTROL OF THE CPU
How can the operating system regain control of the CPU so that it can
switch between processes?

A Cooperative Approach: Wait For System Calls

A Non-Cooperative Approach: The OS Takes Control

THE CRUX: HOW TO GAIN CONTROL WITHOUT COOPERATION
How can the OS gain control of the CPU even if processes are not being
cooperative? What can the OS do to ensure a rogue process does not take
over the machine?
- using a `timer interrupt`
  - a pre-configured `interrupt handler` in the OS runs
    - calls `switch()` routing if decided to switch the running process which saves current register values into the process structure of the switched process, restores register values of next process, and then `switches contexts` by changing the stack pointer to use next process's kernel stack
- the os must inform the hardware at boot time of which code to run which code to run when the timer interrupt occurs
- during the boot sequence, the os must start the timer

TIP: USE THE TIMER INTERRUPT TO REGAIN CONTROL
The addition of a timer interrupt gives the OS the ability to run again
on a CPU even if processes act in a non-cooperative fashion. Thus, this
hardware feature is essential in helping the OS maintain control of the
machine

`Saving and Restoring Context`
- `scheduler`
  - whether to continue running the currently-running process, or switch to a different one
  - If the decision is made to switch, the OS then executes a low-level piece of code which we refer to as a `context switch`
- `context switch`
  - save a few register values for the currently-executing process (onto its kernel stack, for example)
  - restore a few for the soon-to-be-executing process (from its kernel stack)
  - By doing so, the OS thus ensures that when the return-from-trap instruction is finally executed, instead of returning to the process that was running, the system resumes execution of another process.
  - To save the context of the currently-running process, the OS will execute some low-level assembly code to save the general purpose registers, PC, and the kernel stack pointer of the currently-running process, and then restore said registers, PC, and switch to the kernel stack for the soon-to-be-executing process

two types of register saves/restores that happens during the `Limited Direct Execution Protocol (Timer Interrupt)`:
- The first is when the timer interrupt occurs; in this case, the user registers of the running process are implicitly saved by the hardware, using the kernel stack of that process.
- The second is when the OS decides to switch from A to B; in this case, the kernel registers are explicitly saved by the software (i.e., the OS), but this time into memory in the process structure of the process

ASIDE: HOW LONG CONTEXT SWITCHES TAKE 
A natural question you might have is: how long does something like a context switch take? Or even a system call? For those of you that are curious, there is a tool called lmbench [MS96] that measures exactly those things, as well as a few other performance measures that might be relevant. Results have improved quite a bit over time, roughly tracking processor performance. For example, in 1996 running Linux 1.3.37 on a 200-MHz P6 CPU, system calls took roughly 4 microseconds, and a context switch roughly 6 microseconds [MS96]. Modern systems perform almost an order of magnitude better, with sub-microsecond results on systems with 2- or 3-GHz processors. It should be noted that not all operating-system actions track CPU performance. As Ousterhout observed, many OS operations are memory intensive, and memory bandwidth has not improved as dramatically as processor speed over time [O90]. Thus, depending on your workload, buying the latest and greatest processor may not speed up your OS as much as you might hope.


handling interrupts for `concurrency`
- `disable interrupts`
- `locking` schemes to protect concurrent access to internal data structures.


ASIDE: KEY CPU VIRTUALIZATION TERMS (MECHANISMS)
• The CPU should support at least two modes of execution: a restricted user mode and a privileged (non-restricted) kernel mode.
• Typical user applications run in user mode, and use a system call
to trap into the kernel to request operating system services.
• The trap instruction saves register state carefully, changes the hardware status to kernel mode, and jumps into the OS to a pre-specified
destination: the trap table.
• When the OS finishes servicing a system call, it returns to the user
program via another specialreturn-from-trap instruction, which reduces privilege and returns control to the instruction after the trap
that jumped into the OS.
• The trap tables must be set up by the OS at boot time, and make
sure that they cannot be readily modified by user programs. All
of this is part of the limited direct execution protocol which runs
programs efficiently but without loss of OS control.
• Once a program is running, the OS must use hardware mechanisms
to ensure the user program does not run forever, namely the timer
interrupt. This approach is a non-cooperative approach to CPU
scheduling.
• Sometimes the OS, during a timer interrupt or system call, might
wish to switch from running the current process to a different one,
a low-level technique known as a context switch.