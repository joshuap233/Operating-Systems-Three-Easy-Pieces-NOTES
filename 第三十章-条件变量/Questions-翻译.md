课后作业 (编码)

通过本作业，您可以探索一些使用锁和条件变量的实际代码，以实现本章中讨论的各种形式的生产者/消费者队列。 
您将查看真实的代码，以各种配置运行它，并使用它来了解什么有效，什么无效以及其他复杂性。 阅读 README 文件了解详细信息。

Questions：

1.我们的第一个问题集中在main-two-cvs-while.c（有效解决方案）上。 首先，研究代码。 您认为您了解运行该程序时应该怎么做吗？

2.指定一个生产者和一个消费者运行，并让生产者产生一些值。 
缓冲区大小从1 开始，然后增加。较大的缓冲区如何改变代码的行为？
What would you predict num full to be with different buffer sizes (e.g., -m 10) and different numbers of produced items
(e.g., -l 100), when you change the consumer sleep string from
default (no sleep) to -C 0,0,0,0,0,0,1?

3.If possible, run the code on different systems (e.g., a Mac and Linux).
Do you see different behavior across these systems?
4.Let’s look at some timings. How long do you think the following execution, with one producer, three consumers, a single-entry
shared buffer, and each consumer pausing at point c3 for a second, will take? ./main-two-cvs-while -p 1 -c 3 -m 1 -C
0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0 -l 10 -v -t

5.Now change the size of the shared buffer to 3 (-m 3). Will this make
any difference in the total time?

6.Now change the location of the sleep to c6 (this models a consumer taking something off the queue and then doing something
with it), again using a single-entry buffer. What time do you predict in this case? ./main-two-cvs-while -p 1 -c 3 -m 1
-C 0,0,0,0,0,0,1:0,0,0,0,0,0,1:0,0,0,0,0,0,1 -l 10
-v -t

7.Finally, change the buffer size to 3 again (-m 3). What time do you
predict now?

8.Now let’s look at main-one-cv-while.c. Can you configure
a sleep string, assuming a single producer, one consumer, and a
buffer of size 1, to cause a problem with this code?

9.Now change the number of consumers to two. Can you construct
sleep strings for the producer and the consumers so as to cause a
problem in the code?

10.Now examine main-two-cvs-if.c. Can you cause a problem to
happen in this code? Again consider the case where there is only
one consumer, and then the case where there is more than one.

11.Finally, examine main-two-cvs-while-extra-unlock.c. What
problem arises when you release the lock before doing a put or a
get? Can you reliably cause such a problem to happen, given the
sleep strings? What bad thing can happen?

