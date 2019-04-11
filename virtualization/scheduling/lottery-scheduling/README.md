`proportional-share` scheduler
- `fair-share` scheduler
- insteadof optimizing for turnaround or response time, a scheduler might instead try to guarantee that each job obtain a certain percentage of CPUtime
- eg: `lottery scheduling`


CRUX: HOWTOSHARETHECPU PROPORTIONALLYHow can we design a scheduler to share the CPU in a proportionalmanner? What are the key mechanisms for doing so? How effective arethey?

Basic Concept: Tickets Represent Your Share

tickets
- the share of a resource that a process (or user or whatever) should receive. The percent of tickets that a processhas represents its share of the system resource in question.


TIP: USERANDOMNESS
One of the most beautiful aspects of lottery scheduling is its useofran-domness. When you have to make a decision, using such a randomizedapproach is often a robust and simple way of doing so.Random approaches has at least three advantages over more traditionaldecisions. First, random often avoids strange corner-case behaviors thata more traditional algorithm may have trouble handling. For example,consider the LRU replacement policy (studied in more detail in afuturechapter on virtual memory); while often a good replacement algorithm,LRU attains worst-case performance for some cyclic-sequentialwork-loads. Random, on the other hand, has no such worst case.Second, random also is lightweight, requiring little state to track alter-natives. In a traditional fair-share scheduling algorithm, tracking howmuch CPU each process has received requires per-process accounting,which must be updated after running each process. Doing so randomlynecessitates only the most minimal of per-process state (e.g., the numberof tickets each has).Finally, random can be quite fast. As long as generating a randomnum-ber is quick, making the decision is also, and thus random can be usedin a number of places where speed is required. Of course, the faster theneed, the more random tends towards pseudo-random.

TIP: USETICKETSTOREPRESENTSHARESOne of the most powerful (and basic) mechanisms in the design of lottery(and stride) scheduling is that of theticket. The ticket is used to representa process’s share of the CPU in these examples, but can be appliedmuchmore broadly. For example, in more recent work on virtual memory man-agement for hypervisors, Waldspurger shows how tickets can be used torepresent a guest operating system’s share of memory [W02]. Thus, if youare ever in need of a mechanism to represent a proportion of ownership,this concept just might be ... (wait for it) ... the ticket.

`ticket currency`
- Currency allows a user with a set of tick-ets to allocate tickets among their own jobs in whatever currencytheywould like; the system then automatically converts said currency into thecorrect global value

`ticket transfer`
- a processcan temporarily hand off its tickets to another process. This ability is especially useful in a client/server setting

`ticket inflation`
- a process can temporarily raise or lower the number of tickets it owns
- inflation can be applied in an environment where a group of processes trust oneanother
- if any one process knows it needs more CPU time,it can boost its ticket value as a way to reflect that need to the system, all without communicating with any other processes.

lottery sharing works better (is more fair) for long running jobs

how to assign tickets
- leave it to user
  - user have some alloted tickets which the user can assign to its running jobs
- ticket assignment problem by the system is an open problem


stride scheduling
- deterministic fair-share scheduler
- tries to solve the problem of lottery scheduling unfairness for short runtime jobs
- Each job in the system hasa stride, which is inverse in proportion to the number of tickets it has.
- we can compute the stride of each by dividing some large number by the number of tickets each process has been assigned - the stride of each process
- every time a process runs, we will increment a counter for it (called its pass value) by its stride to track its global progress
- the scheduler then uses the stride and pass to determine which process should run next. The basic idea is simple: at any given time, pick the process to run that has the lowest pass value so far; when you run a process, increment its pass counter by its stride.


lottery scheduling vs stride scheduling
- lottery has global state
  - Imagine a newjob enters in the middle of our stride scheduling example above what should its pass value be? Should it be set to 0? If so, it will monopolizethe CPU
  - With lottery scheduling, there is no global state per process;we simply add a new process with whatever tickets it has, update thesingle global variable to track how many total tickets we have, and gofrom there. In this way, lottery makes it much easier to incorporate newprocesses in a sensible manner


Linux Completely Fair Scheduler (CFS)
- To achieve its efficiency goals, CFS aims to spend very little time mak-ing scheduling decisions, through both its inherent design andits cleveruse of data structures well-suited to the task
- does not use fixed time slice
- Its goal is simple: to fairly divide aCPU evenly among all competing processes. It does so through a simplecounting-based technique known asvirtual runtime(vruntime)
- As each process runs, it accumulatesvruntime. In the most basiccase, each process’svruntimeincreases at the same rate, in proportionwith physical (real) time. When a scheduling decision occurs,CFS willpick the process with thelowestvruntimeto run next.
- This raises a question: how does the scheduler know when to stopthe currently running process, and run the next one? The tensionhere isclear: if CFS switches too often, fairness is increased, as CFSwill ensurethat each process receives its share of CPU even over miniscule time win-dows, but at the cost of performance (too much context switching; if CFSswitches less often, performance is increased (reduced context switching),but at the cost of near-term fairness.
- how does the scheduler know when to stopthe currently running process, and run the next one?
  - switch too often, increase fairness but increased context switching costs
  - control via controll parameters
    - `sched_latency`
      - CFS uses this value to determine how long one process should run before considering a switch (effectively determining its time slice but in a dynamic fashion). A typical schedlatency value is 48 (milliseconds); CFS divides this value by the number (n) of processes running on the CPU to determine the time slice for a process, and thus ensures that over this period of time, CFS will be completely fair.
      - too many processes will lead to smaller time slices and more context switches, which is bad
    - `min_granularity`
      - to address the situation where there are too many processes
      - usually 6ms
      - CFS will never set the time slice of a process lower than this value, ensuring that not too much time is spent in scheduling overhead.