Homework (Code)
This homework lets you explore some real code that deadlocks (or
avoids deadlock). The different versions of code correspond to different
approaches to avoiding deadlock in a simplified vector add() routine.
See the README for details on these programs and their common substrate.
Questions
<br/>
<br/>

1. First let’s make sure you understand how the programs generally work, and
some of the key options. Study the code in vector-deadlock.c, as well
as in main-common.c and related files.
Now, run ./vector-deadlock -n 2 -l 1 -v, which instantiates two
threads (-n 2), each of which does one vector add (-l 1), and does so in
verbose mode (-v). Make sure you understand the output. How does the
output change from run to run?
<br/>
<br/>

2. Now add the -d flag, and change the number of loops (-l) from 1 to higher
numbers. What happens? Does the code (always) deadlock?
<br/>
<br/>

3. How does changing the number of threads (-n) change the outcome of the
program? Are there any values of -n that ensure no deadlock occurs?
<br/>
<br/>

4. Now examine the code in vector-global-order.c. First, make sure you
understand what the code is trying to do; do you understand why the code
avoids deadlock? Also, why is there a special case in this vector add()
routine when the source and destination vectors are the same?
<br/>
<br/>

5. Now run the code with the following flags: -t -n 2 -l 100000 -d.
How long does the code take to complete? How does the total time change
when you increase the number of loops, or the number of threads?
<br/>
<br/>

6. What happens if you turn on the parallelism flag (-p)? How much would
you expect performance to change when each thread is working on adding
different vectors (which is what -p enables) versus working on the same
ones?
<br/>
<br/>

7. Now let’s study vector-try-wait.c. First make sure you understand
the code. Is the first call to pthread mutex trylock() really needed?
Now run the code. How fast does it run compared to the global order approach? How does the number of retries, as counted by the code, change as
the number of threads increases?
<br/>
<br/>

8. Now let’s look at vector-avoid-hold-and-wait.c. What is the main
problem with this approach? How does its performance compare to the
other versions, when running both with -p and without it?
<br/>
<br/>

9. Finally, let’s look at vector-nolock.c. This version doesn’t use locks at
all; does it provide the exact same semantics as the other versions? Why or
why not?
<br/>
<br/>

10. Now compare its performance to the other versions, both when threads are
working on the same two vectors (no -p) and when each thread is working
on separate vectors (-p). How does this no-lock version perform?


