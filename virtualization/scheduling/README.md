`scheduling policies` or `disciplines`

THE CRUX: HOW TO DEVELOP SCHEDULING POLICY
How should we develop a basic framework for thinking about
scheduling policies? What are the key assumptions? What metrics are
important? What basic approaches have been used in the earliest of computer systems?

`workload` - processes running in the system

`job` - process

`scheduling metric`
- `performance metric`
  - `turaround`
    - Tturnaround = Tcompletion − Tarrival
  - `fairness`
    - `Jain's Fairness Index`

`FIFO` or `FCFS`
- `convoy effect`
  - lightweight tasks after heavyweight tasks

`SJF`
- shortest job first
- non-preemptive scheduler
- bad for response time

PREEMPTIVE SCHEDULERS
In the old days of batch computing, a number of non-preemptive schedulers were developed; such systems would run each job to completion
before considering whether to run a new job. Virtually all modern schedulers are preemptive, and quite willing to stop one process from running in order to run another. This implies that the scheduler employs the
mechanisms we learned about previously; in particular, the scheduler can
perform a context switch, stopping one running process temporarily and
resuming (or starting) another.

`STCF`
- shortest time-to-completion first
- `PSJF` - preemptive shortest job first
- bad for response time

`response time`
- metric
- needed for `time-shared machines`
- Tresponse = Tfirstrun − Tarrival

`round robin`
- good for response time
- `time slice` or `scheduling quantum`
- runs jobs from the run queue for given time slice


TIP: AMORTIZATION CAN REDUCE COSTS
The general technique of amortization is commonly used in systems
when there is a fixed cost to some operation. By incurring that cost less
often (i.e., by performing the operation fewer times), the total cost to the
system is reduced. For example, if the time slice is set to 10 ms, and the
context-switch cost is 1 ms, roughly 10% of time is spent context switching and is thus wasted. If we want to amortize this cost, we can increase
the time slice, e.g., to 100 ms. In this case, less than 1% of time is spent
context switching, and thus the cost of time-slicing has been amortized.

cpu caches
TLB
branch preductors

schedulers
- optimize turaround time
  - SJF, STCF
- optimize response time
  - RR


OVERLAP ENABLES HIGHER UTILIZATION
When possible, overlap operations to maximize the utilization of systems. Overlap is useful in many different domains, including when performing disk I/O or sending messages to remote machines; in either case,
starting the operation and then switching to other work is a good idea,
and improves the overall utilization and efficiency of the system.

`multi-level feedback queue`
- use recent past to predict the future