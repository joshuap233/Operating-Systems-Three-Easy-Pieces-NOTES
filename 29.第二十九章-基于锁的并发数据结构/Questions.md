Homework (Code)

In this homework, you’ll gain some experience with writing concur-rent code and measuring its performance. Learning to build code that performs well is a critical skill and thus gaining a little experience herewith it is quite worthwhile


Questions

<br/>
<br/>

1.We’ll start by redoing the measurements within this chapter. Use the call gettimeofday()to measure time within your program.How accurate is this timer? What is the smallest interval it can mea-sure? Gain confidence in its workings, as we will need it in all sub-sequent questions. You can also look into other timers, such as the cycle counter available on x86 via the rdtsc instruction

<br/>
<br/>

2.Now, build a simple concurrent counter and measure how long it takes to increment the counter many times as the number of threads increases. How many CPUs are available on the system you are using? Does this number impact your measurements at all?

<br/>
<br/>

3.Next, build a version of the sloppy counter. Once again, measure its performance as the number of threads varies, as well as the thresh-old. Do the numbers match what you see in the chapter?

<br/>
<br/>

4.Build a version of a linked list that uses hand-over-hand locking[MS04], as cited in the chapter.  You should read the paper first to understand how it works, and then implement it. Measure its performance. When does a hand-over-hand list work better than a standard list as shown in the chapter?

<br/>
<br/>

5.Pick your favorite data structure, such as a B-tree or other slightly more interesting structure. Implement it, and start with a simple locking strategy such as a single lock. Measure its performance as the number of concurrent threads increases.

<br/>
<br/>

6. Finally, think of a more interesting locking strategy for this favorite data structure of yours. Implement it, and measure its performance.How does it compare to the straightforward locking approach?