`multi-level feedback queue` (MLFQ)
- `compatible time-sharing system` (CTSS)
- fundamental problem solved is two fold
    - optimize turnaround time. In case of SJF, STCF, we do not know how long a job will run
    - minimize response time. RR is bad for turnaround time
- queues of different priority level
    • Rule 1: If Priority(A) > Priority(B), A runs (B doesn’t).
    • Rule 2: If Priority(A) = Priority(B), A & B run in RR.
- Rather than giving a fixed priority to each job, MLFQ varies the priority of a job based on its observed behavior.
    - increases priority of process which relinquishes the CPU frequently for asynchronous tasks
    - decreases priority of process which uses CPU intensively for long periods of time
- use history of job to predict future behaviour

`multics`

how job priority changes overtime
- how to change priority
    • Rule 3: When a job enters the system, it is placed at the highest priority (the topmost queue).
    • Rule 4a: If a job uses up an entire time slice while running, its priority is reduced (i.e., it moves down one queue).
    • Rule 4b: If a job gives up the CPU before the time slice is up, it stays at the same priority level.
    - problems
        - `starvation`: too many interactive jobs consume all cpu time ang long running jobs will not receive cpu time.
        - a smart user could rewrite their program to game the scheduler
        - a program may change its behaviour over time.
- priority boost
    • Rule 5: After some time period S, move all the jobs in the system to the topmost queue. (boosting)
    - Our new rule solves two problems at once. First, processes are guaranteed not to starve: by sitting in the top queue, a job will share the CPU with other high-priority jobs in a round-robin fashion, and thus eventually receive service. Second, if CPU-bound job has become interactive, the scheduler treats it properly once it has received the priority boost.
    - what should the period S be? (voodoo constant)
- better accounting
    - We rewrite Rules 4a and 4b to the following single rule:
    • Rule 4: Once a job uses up its time allotment at a given level (regardless of how many times it has given up the CPU), its priority is reduced (i.e., it moves down one queue).

THE CRUX:
HOW TO SCHEDULE WITHOUT PERFECT KNOWLEDGE?
How can we design a scheduler that both minimizes response time for
interactive jobs while also minimizing turnaround time without a priori
knowledge of job length?

TIP: LEARN FROM HISTORY
The multi-level feedback queue is an excellent example of a system that learns from the past to predict the future. Such approaches are common in operating systems (and many other places in Computer Science, including hardware branch predictors and caching algorithms). Such approaches work when jobs have phases of behavior and are thus predictable; of course, one must be careful with such techniques, as they can easily be wrong and drive a system to make worse decisions than they would have with no knowledge at all.    

TIP: SCHEDULING MUST BE SECURE FROM ATTACK
You might think that a scheduling policy, whether inside the OS itself (as discussed herein), or in a broader context (e.g., in a distributed storage system’s I/O request handling [ +18]), is not a security concern, but in increasingly many cases, it is exactly that. Consider the modern datacenter, in which users from around the world share CPUs, memories, networks, and storage systems; without care in policy design and enforcement, a single user may be able to adversely harm others and gain advantage for itself. Thus, scheduling policy forms an important part of the security of a system, and should be carefully constructed.


how many queues?
how big the time slice per queue?
- high priority queues usually have shorter time slices than low priority queues
how often the priority queue be boosted in order to avoid starvation and account for changes in behaviour?


TIP: AVOID VOO-DOO CONSTANTS (OUSTERHOUT’S LAW)
Avoiding voo-doo constants is a good idea whenever possible. Unfortunately, as in the example above, it is often difficult. One could try to make the system learn a good value, but that too is not straightforward. The frequent result: a configuration file filled with default parameter values that a seasoned administrator can tweak when something isn’t quite working correctly. As you can imagine, these are often left unmodified, and thus we are left to hope that the defaults work well in the field. This tip brought to you by our old OS professor, John Ousterhout, and hence we call it Ousterhout’s Law.

decayed usage algorithm
- a form of boosting priority


TIP: USE ADVICE WHERE POSSIBLE
As the operating system rarely knows what is best for each and every process of the system, it is often useful to provide interfaces to allow users or administrators to provide some hints to the OS. We often call such hints advice, as the OS need not necessarily pay attention to it, but rather might take the advice into account in order to make a better decision. Such hints are useful in many parts of the OS, including the scheduler (e.g., with nice), memory manager (e.g., madvise), and file system (e.g., informed prefetching and caching