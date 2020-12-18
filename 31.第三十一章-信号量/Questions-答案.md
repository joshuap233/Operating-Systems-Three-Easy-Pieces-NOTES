课后作业 (编程)

在这个作业中，我们将使用信号量来解决一些常见的的并发问题。
其中很多都来自 Downey 的优秀的书籍 “Little Book of Semaphores”3，
它很好地将一些经典问题结合在一起，并引入了一些新的变体;有兴趣的读者应该看看这本小书来获得更多的乐趣。
以下每个问题都提供了一个代码框架;您的工作是完善代码，使其在给定的信号量下工作。
在 Linux 上，您将使用 Linux 系统提供的信号量;在 Mac(不支持信号量)上，您必须首先构建一个信号量实现(使用锁和条件变量，如本章所述)。好运！

问题：

<br/>
<br/>

1.第一个问题就是实现和测试 fork/join 问题的解决方案，如本文所述。 即使在文本中描述了此解决方案，
重新自己实现一遍也是值得的。 even Bach would rewrite Vivaldi，
allowing one soon-to-be master to learn from an existing one。
有关详细信息，请参见 fork-join.c。 将添加 sleep(1) 到 child 函数内以确保其正常工作。

```shell script
cd code && make fj && ./a.out
```

<br/>
<br/>

2.现在，我们通过研究集合点问题 [rendezvous problem](https://en.wikipedia.org/wiki/Rendezvous_problem) 来对此进行概括。 
问题如下：您有两个线程，每个线程将要在代码中进入集合点。 任何一方都不应在另一方进入之前退出代码的这一部分。 
该任务使用两个信号量，有关详细信息，请参见 rendezvous.c。

```shell script
cd code && make r && ./a.out
```

<br/>
<br/>

3.现在，通过实现屏障（barrier）同步的通用解决方案，更进一步。假设在一段连续的代码中有两个点，称为 P1 和 P2。
在 P1 和 P2 之间放置一个 barrier 可确保所有线程将在任何一个线程执行 P2 之前执行完 P1。 
您的任务：编写代码以实现可以这种方式使用的 barrier（）函数。
可以假设您知道 N（正在运行的程序中的线程总数），并且所有 N 个线程都将尝试进入该屏障。
同样，您可能应该使用两个信号量来实现解决方案，并使用其他一些整数来计数。有关详细信息，请参见 barrier.c。

```shell script
cd code && make b && ./a.out 3
``` 
    
    3 为需要创建线程数plainplainplainplainplain

<br/>
<br/>

4.现在按照文本中所述，解决读者写者问题。 首先，不用考虑进程饥饿。 有关详细信息，请参见 reader-writer.c 中的代码。 
将 sleep（）调用添加到您的代码中，以证明它可以按预期工作****。 你能证明饥饿问题的存在吗？

```shell script
cd code && make rw && ./a.out 5 5 10
``` 

    5,5,10 三个参数分别为读者数，写者数，每个读者、写者进行的读写操作数plainplainplain
    当读者数量远大于写者时，写者可能饿死，读者不需要锁就能进入临界区，只要有一个读者获得锁，
    其他读者线程就能运行，读者数量可能一直大于0，而写者始终无法获取锁

<br/>
<br/>

5.让我们再次看一下读者写者问题，但这一次需要考虑进程饥饿。 您如何确保所有读者和写者运行？ 有关详细信息，请参见 reader-writer-nostarve.c。

```shell script
cd code && make rwn && ./a.out 500 5 10
```
    
    新增 write_waiting 锁，写者读者都需要竞争这个锁，正如上所说读者写者锁看死很酷，事实上意味着复杂与缓慢plainplainplainplainplainplainplainplain

<br/>
<br/>

6.使用信号量构建一个没有饥饿的互斥量，其中任何试图获取该互斥量的线程都将最终获得它。 有关更多信息，请参见 mutex-nostarve.c 中的代码。

    首先，为什么用互斥量加锁会饿死，比如多线程死循环，反复进入临界区，plainplainplainplain
    分别为线程a,b,c,d...
    互斥量无法保证a,b,c,d...都会运行,
    运行序列可能时 a,b,a,a,a,a,b,b,b,...因此其他线程饿死
    
    实现在 code/mutex-nostarve.c,原理为，释放临界区锁后，
    调用 调用barrier.c内实现的barrier函数，等待所有线程执行完再继续进行

<br/>
<br/>

7.喜欢这些问题吗？ 查看 Downey 的免费书籍，以获取更多与他们一样的信息。 并且不要忘记，玩得开心！ 但是，编写代码时总是玩的开心的，不是吗？
