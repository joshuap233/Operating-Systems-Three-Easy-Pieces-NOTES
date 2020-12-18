课后作业(编码)
在本节中，我们将编写一些简单的多线程程序，并使用一个叫`helgrind`的特定工具来查找程序中的问题。
阅读作业中的 README 文件，以获取有关如何构建程序和运行`helgrind`的详细信息。

问题:


<br/>
<br/>

1.首先构建`main-race.c`,查看代码，以便您可以在代码中看到（非常明显的）数据竞争。 
现在运行 `helgrind`（通过输入`valgrind --tool=helgrind main-race`）来查看其追踪结果。 
它指向正确的代码行吗？ 它还能为您提供什么其他信息？

输入`make main-race`构建,代码中的竞争条件很明显,多线程同时修改`balance`变量

输入`valgrind --tool=helgrind ./main-race` 查看结果,

跟踪结果:
<pre>
==25676== Helgrind, a thread error detector
==25676== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==25676== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==25676== Command: ./main-race
==25676== 
==25676== ---Thread-Announcement------------------------------------------
==25676== 
==25676== Thread #1 is the program's root thread
==25676== 
==25676== ---Thread-Announcement------------------------------------------
==25676== 
==25676== Thread #2 was created
==25676==    at 0x49B2282: clone (clone.S:71)
==25676==    by 0x48752EB: create_thread (createthread.c:101)
==25676==    by 0x4876E0F: pthread_create@@GLIBC_2.2.5 (pthread_create.c:817)
==25676==    by 0x4842917: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==25676==    by 0x109513: Pthread_create (mythreads.h:51)
==25676==    by 0x1095F1: main (main-race.c:14)
==25676== 
==25676== ----------------------------------------------------------------
==25676== 
==25676== Possible data race during read of size 4 at 0x10C014 by thread #1
==25676== Locks held: none
==25676==    at 0x1095F2: main (main-race.c:15)
==25676== 
==25676== This conflicts with a previous write of size 4 by thread #2
==25676== Locks held: none
==25676==    at 0x1095A6: worker (main-race.c:8)
==25676==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==25676==    by 0x4876608: start_thread (pthread_create.c:477)
==25676==    by 0x49B2292: clone (clone.S:95)
==25676==  Address 0x10c014 is 0 bytes inside data symbol "balance"
==25676== 
==25676== ----------------------------------------------------------------
==25676== 
==25676== Possible data race during write of size 4 at 0x10C014 by thread #1
==25676== Locks held: none
==25676==    at 0x1095FB: main (main-race.c:15)
==25676== 
==25676== This conflicts with a previous write of size 4 by thread #2
==25676== Locks held: none
==25676==    at 0x1095A6: worker (main-race.c:8)
==25676==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==25676==    by 0x4876608: start_thread (pthread_create.c:477)
==25676==    by 0x49B2292: clone (clone.S:95)
==25676==  Address 0x10c014 is 0 bytes inside data symbol "balance"
==25676== 
==25676== 
==25676== Use --history-level=approx or =none to gain increased speed, at
==25676== the cost of reduced accuracy of conflicting-access information
==25676== For lists of detected and suppressed errors, rerun with: -s
==25676== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
</pre>
可以看到有竞争状态提示:`Possible data race during read of size 4 at 0x10C014 by thread #1`

代码行提示:`at 0x1095A6: worker (main-race.c:8)`

地址提示: `Address 0x10c014 is 0 bytes inside data symbol "balance"`

<br/>
<br/>

2.删除有问题的代码行之一会发生什么？ 现在，在一个共享变量的更新附近添加锁，然后在所有变量更新周围添加锁。 
在每种情况下，`Helgrind`报告什么？

删除第 15 行代码或第 8 行代码,程序正确运行

加一个锁报错,依然有竞争条件,
所有变量更新周围添加锁:`cd code && make  && valgrind --tool=helgrind ./main-race` 结果正确

<br/>
<br/>

3.现在让我们看一下`main-deadlock.c`. 查看代码。 代码中有一个死锁的问题（我们将在下一章中对此进行更深入的讨论）。 您知道它可能有什么问题吗？
 
死锁情况: 

线程 0 获取锁 1,中断,线程 1 执行, 获取锁 2,造成死锁
 

<br/>
<br/>

4.现在运行`helgrind`检查这段代码。 `Helgrind`报告什么？
 
追踪:
```shell script
make main-deadlock 
valgrind --tool=helgrind ./main-deadlock 
```

结果:
<pre>
==28961== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 7 from 7)
</pre>
   
 
<br/>
<br/>

5.现在使用`main-deadlock-global.c`运行`helgrind`。 查看代码；
它有和`main-deadlock.c`有一样的问题吗？ `Helgrind`是否应该报告相同的错误？ 对于`helgrind`之类的工具,结果说明了什么？
  

执行:
```shell script
make main-deadlock-global
valgrind --tool=helgrind ./main-deadlock-global
```

执行结果:

<pre>
ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 7 from 7)
</pre>

`main-deadlock-global.c` 代码是没有问题的,但 valgrind 工具依然报错, 因此推断 `helgrind` 靠执行周期与上下文切换次数 判断死锁,因此,`helgrind` 并不能很好地判断死锁


<br/>
<br/>

6.接下来让我们看一下`main-signal.c`。 这段代码使用变量（done）来表示子进程已完成，并且父线程现在可以继续运行了。 
为什么这段代码效率低下？ （父线程最终会花时间做什么，特别是当子线程需要很长时间才能执行完成时？）

执行:
```shell script
make main-signal
valgrind --tool=helgrind ./main-signal
```
父线程使用大量时间自旋等待

<br/>
<br/>

7.现在在这个程序上运行`helgrind`。它报告什么?代码正确吗?

<pre>
==30421== Possible data race during write of size 1 at 0x52861A5 by thread #1
==30421==    by 0x109633: main (main-signal.c:17)
==30421==    by 0x1095CC: worker (main-signal.c:8)
=30326== ERROR SUMMARY: 23 errors from 2 contexts (suppressed: 40 from 36)
</pre>

竞争条件是 done 变量, 工具指示到 printf 去了, 

glibc 的 printf 函数是线程安全的函数,参考:[stackoverflow](https://stackoverflow.com/questions/467938/stdout-thread-safe-in-c-on-linux)

<br/>
<br/>

8.现在看一下`main-signal.c`稍微修改的版本:`main-signal-cv.c`。
该版本使用条件变量来发送信号（并进行加锁）。 为什么此代码比以前的版本更好？ 是正确，还是性能，或两者兼而有之？

执行:
```shell script
make main-signal-cv
valgrind --tool=helgrind ./main-signal-cv
```
  
结果正确,性能比之前的版本要好,
对 done 变量加锁, 且将自旋等待替换为 `Pthread_cond_wait`, 释放锁并让出 CPU,收到信号时被唤醒,重新获取锁

<br/>
<br/>

9.再一次在`main-signal-cv.c`上运行`helgrind`。它报告错误吗?

没有