process is a running program
    - major OS abstraction of the running process
    - described using machine state
        - memory
            - `address-space` is the memory that the process can access
        - registers
            - `program counter` (PC) / `instruction pointer` (IP)
                - which instruction of the program currently executed
            - `stack pointer` and associated `frame pointer`
                - used to manage the stack for function parameters, local variables and return addresses
        - persistent storage devices
            - list of files that the process currently has open
    - process API
        - calls (creation, destruction etc) that programs can make related to processes
    - process state
        - process can exist in many states such as running, runnable, blocked
        - change of state can be caused by scheduling, io etc
    - process list
        - info about all processes in the system
        - each entry is called process control block

virtualizing the cpu
    - `time-sharing`
        - smart scheduling of the execution of processes
    - `space-sharing`
        - disk

mechanisms
    - low-level machinery
    - low-level protocols or methods that implement a piece of functionality

`context-switch`
    - time-sharing
    - stop one process and run another

`policy`
    - high-level
    - algorithm to perfom OS task

`scheduling-policy`
    - which program to run from a pool of programs

static data eg. initialized variables

programs initially reside in disks in some kind of executable format.

Steps from program to process
    - load program into main memory
        - `eagerly`
        - `lazily`
            - `paging`
            - `swapping`
    - allocate memory for program's runtime stack
        - needed for local variabls, function parameters and return addresses
        - initialize the stack with function parameters, e.g. argv array, argc
        - allocate memory for heap
            - used for explicitly requested dynamically-allocated data allocated by malloc() and freed by free() in C.
            - small initially, more memory allocated as process demands more memory
    - allocate io
        - initially 3 file-descriptors assigned
            - stdout to screen, stdin from terminal, stderr

process state
    - running
    - ready 
    - blocked


OS Data Structures
    - process list / task list
        - keep track of all the running programs
        - `process control block`
            - individual structure that stores info about a process
            - also called `process descriptor`
            - generally a struct in c
    - register context
    
States of a process
    - unused
    - embryo
    - sleeping
    - zombie
    - runnable
    - running



#### running process-run.py

- python2 process-run.py -l 5:100,5:100
- python2 process-run.py -l 4:100,1:0

- python2 process-run.py -l 4:100,1:0 -c -p
```
bash-3.2$ python2 process-run.py -l 4:100,1:0 -c -p
Time     PID: 0     PID: 1        CPU        IOs
  1     RUN:cpu      READY          1
  2     RUN:cpu      READY          1
  3     RUN:cpu      READY          1
  4     RUN:cpu      READY          1
  5        DONE     RUN:io          1
  6        DONE    WAITING                     1
  7        DONE    WAITING                     1
  8        DONE    WAITING                     1
  9        DONE    WAITING                     1
 10*       DONE       DONE

Stats: Total Time 10
Stats: CPU Busy 5 (50.00%)
Stats: IO Busy  4 (40.00%)
```

- python2 process-run.py -l 1:0,4:100 -c -p
```
bash-3.2$ python2 process-run.py -l 1:0,4:100 -c -p
Time     PID: 0     PID: 1        CPU        IOs
  1      RUN:io      READY          1
  2     WAITING    RUN:cpu          1          1
  3     WAITING    RUN:cpu          1          1
  4     WAITING    RUN:cpu          1          1
  5     WAITING    RUN:cpu          1          1
  6*       DONE       DONE

Stats: Total Time 6
Stats: CPU Busy 5 (83.33%)
Stats: IO Busy  4 (66.67%)
```

- python2 process-run.py -l 4:100,1:0 -c -p -S SWITCH_ON_END
( the system will not switch to another pro-cess while one is doing I/O)
```
bash-3.2$ python2 process-run.py -l 4:100,1:0 -c -p -S SWITCH_ON_END
Time     PID: 0     PID: 1        CPU        IOs
  1     RUN:cpu      READY          1
  2     RUN:cpu      READY          1
  3     RUN:cpu      READY          1
  4     RUN:cpu      READY          1
  5        DONE     RUN:io          1
  6        DONE    WAITING                     1
  7        DONE    WAITING                     1
  8        DONE    WAITING                     1
  9        DONE    WAITING                     1
Traceback (most recent call last):
  File "process-run.py", line 318, in <module>
    (cpu_busy, io_busy, clock_tick) = s.run()
  File "process-run.py", line 220, in run
    self.next_proc(pid)
  File "process-run.py", line 111, in next_proc
    self.move_to_running(STATE_READY)
  File "process-run.py", line 99, in move_to_running
    assert(self.proc_info[self.curr_proc][PROC_STATE] == expected)
```

- python2 process-run.py -l 1:0,4:100 -c -p -S SWITCH_ON_END
( the system will not switch to another pro-cess while one is doing I/O)
```
Time     PID: 0     PID: 1        CPU        IOs
  1      RUN:io      READY          1
  2     WAITING      READY                     1
  3     WAITING      READY                     1
  4     WAITING      READY                     1
  5     WAITING      READY                     1
  6*       DONE    RUN:cpu          1
  7        DONE    RUN:cpu          1
  8        DONE    RUN:cpu          1
  9        DONE    RUN:cpu          1

Stats: Total Time 9
Stats: CPU Busy 5 (55.56%)
Stats: IO Busy  4 (44.44%)
```

- python2 process-run.py -l 1:0,4:100 -c -p -S SWITCH_ON_IO
```
bash-3.2$ python2 process-run.py -l 1:0,4:100 -c -p -S SWITCH_ON_IO
Time     PID: 0     PID: 1        CPU        IOs
  1      RUN:io      READY          1
  2     WAITING    RUN:cpu          1          1
  3     WAITING    RUN:cpu          1          1
  4     WAITING    RUN:cpu          1          1
  5     WAITING    RUN:cpu          1          1
  6*       DONE       DONE

Stats: Total Time 6
Stats: CPU Busy 5 (83.33%)
Stats: IO Busy  4 (66.67%)
```

- python2 process-run.py -l 4:100,1:0 -c -p -S SWITCH_ON_IO
```
bash-3.2$ python2 process-run.py -l 4:100,1:0 -c -p -S SWITCH_ON_IO
Time     PID: 0     PID: 1        CPU        IOs
  1     RUN:cpu      READY          1
  2     RUN:cpu      READY          1
  3     RUN:cpu      READY          1
  4     RUN:cpu      READY          1
  5        DONE     RUN:io          1
  6        DONE    WAITING                     1
  7        DONE    WAITING                     1
  8        DONE    WAITING                     1
  9        DONE    WAITING                     1
 10*       DONE       DONE

Stats: Total Time 10
Stats: CPU Busy 5 (50.00%)
Stats: IO Busy  4 (40.00%)
```

- python2 process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
(when an I/O completes, the process that issued it is notnecessarily run right away)
```
bash-3.2$ python2 process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
Time     PID: 0     PID: 1     PID: 2     PID: 3        CPU        IOs
  1      RUN:io      READY      READY      READY          1
  2     WAITING    RUN:cpu      READY      READY          1          1
  3     WAITING    RUN:cpu      READY      READY          1          1
  4     WAITING    RUN:cpu      READY      READY          1          1
  5     WAITING    RUN:cpu      READY      READY          1          1
  6*      READY    RUN:cpu      READY      READY          1
  7       READY       DONE    RUN:cpu      READY          1
  8       READY       DONE    RUN:cpu      READY          1
  9       READY       DONE    RUN:cpu      READY          1
 10       READY       DONE    RUN:cpu      READY          1
 11       READY       DONE    RUN:cpu      READY          1
 12       READY       DONE       DONE    RUN:cpu          1
 13       READY       DONE       DONE    RUN:cpu          1
 14       READY       DONE       DONE    RUN:cpu          1
 15       READY       DONE       DONE    RUN:cpu          1
 16       READY       DONE       DONE    RUN:cpu          1
 17      RUN:io       DONE       DONE       DONE          1
 18     WAITING       DONE       DONE       DONE                     1
 19     WAITING       DONE       DONE       DONE                     1
 20     WAITING       DONE       DONE       DONE                     1
 21     WAITING       DONE       DONE       DONE                     1
 22*     RUN:io       DONE       DONE       DONE          1
 23     WAITING       DONE       DONE       DONE                     1
 24     WAITING       DONE       DONE       DONE                     1
 25     WAITING       DONE       DONE       DONE                     1
 26     WAITING       DONE       DONE       DONE                     1
 27*       DONE       DONE       DONE       DONE

Stats: Total Time 27
Stats: CPU Busy 18 (66.67%)
Stats: IO Busy  12 (44.44%)
```

- python2 process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
```
bash-3.2$ python2 process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
Time     PID: 0     PID: 1     PID: 2     PID: 3        CPU        IOs
  1      RUN:io      READY      READY      READY          1
  2     WAITING    RUN:cpu      READY      READY          1          1
  3     WAITING    RUN:cpu      READY      READY          1          1
  4     WAITING    RUN:cpu      READY      READY          1          1
  5     WAITING    RUN:cpu      READY      READY          1          1
  6*     RUN:io      READY      READY      READY          1
  7     WAITING    RUN:cpu      READY      READY          1          1
  8     WAITING       DONE    RUN:cpu      READY          1          1
  9     WAITING       DONE    RUN:cpu      READY          1          1
 10     WAITING       DONE    RUN:cpu      READY          1          1
 11*     RUN:io       DONE      READY      READY          1
 12     WAITING       DONE    RUN:cpu      READY          1          1
 13     WAITING       DONE    RUN:cpu      READY          1          1
 14     WAITING       DONE       DONE    RUN:cpu          1          1
 15     WAITING       DONE       DONE    RUN:cpu          1          1
 16*       DONE       DONE       DONE    RUN:cpu          1
 17        DONE       DONE       DONE    RUN:cpu          1
 18        DONE       DONE       DONE    RUN:cpu          1

Stats: Total Time 18
Stats: CPU Busy 18 (100.00%)
Stats: IO Busy  12 (66.67%)
```

- python2 process-run.py -s 1 -l 3:50,3:50 -c -p
```
bash-3.2$ python2 process-run.py -s 1 -l 3:50,3:50 -c -p
Time     PID: 0     PID: 1        CPU        IOs
  1     RUN:cpu      READY          1
  2      RUN:io      READY          1
  3     WAITING    RUN:cpu          1          1
  4     WAITING    RUN:cpu          1          1
  5     WAITING    RUN:cpu          1          1
  6     WAITING       DONE                     1
  7*     RUN:io       DONE          1
  8     WAITING       DONE                     1
  9     WAITING       DONE                     1
 10     WAITING       DONE                     1
 11     WAITING       DONE                     1
 12*       DONE       DONE

Stats: Total Time 12
Stats: CPU Busy 6 (50.00%)
Stats: IO Busy  8 (66.67%)
```

- python2 process-run.py -s 2 -l 3:50,3:50 -c -p
```
bash-3.2$ python2 process-run.py -s 2 -l 3:50,3:50 -c -p
Time     PID: 0     PID: 1        CPU        IOs
  1      RUN:io      READY          1
  2     WAITING    RUN:cpu          1          1
  3     WAITING     RUN:io          1          1
  4     WAITING    WAITING                     2
  5     WAITING    WAITING                     2
  6*     RUN:io    WAITING          1          1
  7     WAITING    WAITING                     2
  8*    WAITING     RUN:io          1          1
  9     WAITING    WAITING                     2
 10     WAITING    WAITING                     2
 11*    RUN:cpu    WAITING          1          1
 12        DONE    WAITING                     1
 13*       DONE       DONE

Stats: Total Time 13
Stats: CPU Busy 6 (46.15%)
Stats: IO Busy  11 (84.62%)
```

- python2 process-run.py -s 3 -l 3:50,3:50 -c -p
```
bash-3.2$ python2 process-run.py -s 3 -l 3:50,3:50 -c -p
Time     PID: 0     PID: 1        CPU        IOs
  1     RUN:cpu      READY          1
  2      RUN:io      READY          1
  3     WAITING     RUN:io          1          1
  4     WAITING    WAITING                     2
  5     WAITING    WAITING                     2
  6     WAITING    WAITING                     2
  7*    RUN:cpu    WAITING          1          1
  8*       DONE     RUN:io          1
  9        DONE    WAITING                     1
 10        DONE    WAITING                     1
 11        DONE    WAITING                     1
 12        DONE    WAITING                     1
 13*       DONE    RUN:cpu          1

Stats: Total Time 13
Stats: CPU Busy 6 (46.15%)
Stats: IO Busy  9 (69.23%)
```