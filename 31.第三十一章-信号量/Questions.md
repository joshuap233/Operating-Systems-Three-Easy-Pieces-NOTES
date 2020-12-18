Homework (Code)
In this homework, we’ll use semaphores to solve some well-known
concurrency problems. Many of these are taken from Downey’s excellent
“Little Book of Semaphores”3
, which does a good job of pulling together
a number of classic problems as well as introducing a few new variants;
interested readers should check out the Little Book for more fun.
Each of the following questions provides a code skeleton; your job is
to fill in the code to make it work given semaphores. On Linux, you
will be using native semaphores; on a Mac (where there is no semaphore
support), you’ll have to first build an implementation (using locks and
condition variables, as described in the chapter). Good luck!
Questions
<br/>
<br/>

1. The first problem is just to implement and test a solution to the fork/join
problem, as described in the text. Even though this solution is described in
the text, the act of typing it in on your own is worthwhile; even Bach would
rewrite Vivaldi, allowing one soon-to-be master to learn from an existing
one. See fork-join.c for details. Add the call sleep(1) to the child to
ensure it is working.
<br/>
<br/>

2. Let’s now generalize this a bit by investigating the rendezvous problem.
The problem is as follows: you have two threads, each of which are about
to enter the rendezvous point in the code. Neither should exit this part of
the code before the other enters it. Consider using two semaphores for this
task, and see rendezvous.c for details.
<br/>
<br/>

3. Now go one step further by implementing a general solution to barrier synchronization. Assume there are two points in a sequential piece of code,
called P1 and P2. Putting a barrier between P1 and P2 guarantees that all
threads will execute P1 before any one thread executes P2. Your task: write
the code to implement a barrier() function that can be used in this manner. It is safe to assume you know N (the total number of threads in the
running program) and that all N threads will try to enter the barrier. Again,
you should likely use two semaphores to achieve the solution, and some
other integers to count things. See barrier.c for details.
<br/>
<br/>

4. Now let’s solve the reader-writer problem, also as described in the text. In
this first take, don’t worry about starvation. See the code in reader-writer.c
for details. Add sleep() calls to your code to demonstrate it works as you
expect. Can you show the existence of the starvation problem?
<br/>
<br/>

5. Let’s look at the reader-writer problem again, but this time, worry about
starvation. How can you ensure that all readers and writers eventually
make progress? See reader-writer-nostarve.c for details.
<br/>
<br/>

6. Use semaphores to build a no-starve mutex, in which any thread that tries to
acquire the mutex will eventually obtain it. See the code in mutex-nostarve.c
for more information.
<br/>
<br/>

7. Liked these problems? See Downey’s free text for more just like them. And
don’t forget, have fun! But, you always do when you write code, no?