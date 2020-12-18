课后作业(编码):
在本作业中，您将获得一些编写并发代码并评估其性能的经验。 学习构建性能良好的代码是一项关键技能，因此，从中获得一点经验是非常值得的

问题:

<br/>
<br/>

1.我们将在本章中重新进行度量。使用调用 gettimeofday()来度量程序中的时间。
这个计时器有多精确?它能确定的最小间隔是多少?要对它的工作方式有信心，因为在接下来的所有问题中我们都需要它。您还可以使用其他计时器，比如通过 x86 提供的`rdtsc`指令使用循环计数器

`gettimeofday` 精度为微秒级([参考](https://blog.csdn.net/russell_tao/article/details/7185588))
`rdtsc`指令,成本与精确度都是纳秒级(取决于 cpu 使用周期)
`rdtsc`测试方法参考:[How to Benchmark Code Execution Times on Intel® IA-32 and IA-64 Instruction Set Architectures](https://www.intel.com/content/dam/www/public/us/en/documents/white-papers/ia-32-ia-64-benchmark-code-execution-paper.pdf)

<br/>
<br/>

2.现在，构建一个简单的并发计数器，并测量随着线程数量的增加，多次增加计数器所需的时间。 您正在使用的系统上有多少个 CPU 可用？ 这个数字是否会完全影响您的测量？

运行:
```shell script
cd 2 && python3 plot.py
```

查看 CPU 信息:
```shell script
cat /proc/cpuinfo
```


<br/>
<br/>

3.接下来，构建一个 懒惰计数器(sloppy counter) 的版本。 根据线程数以及阈值来衡量其性能。 这些数字是否与您在本章中看到的一致？

```shell script
cd 3 && python3 plot.py
```

<br/>
<br/>

4.如本章所述，构建使用`and-over-hand`锁[MS04]的链表版本。 您应该先阅读 paper 以了解其工作原理，然后再实现它并且衡量其性能。 何时 基于`hand-over-hand`锁的链表 比 标准链表 更有效？

```shell script
cd 4 && make && ./main
```

<br/>
<br/>

5.选择你喜欢的数据结构，例如 B 树或其他稍微有趣的结构。 实现它，然后从简单的锁策略开始，例如单个锁。 随着并发线程数的增加来衡量其性能。

```shell script
cd 5 && python3 plot.py
```

<br/>
<br/>

6.最后，为您喜欢的这种数据结构考虑一个更有趣的锁定策略。 实施并衡量其性能。与直接加锁的方法相比，它又如何？

每个节点一个锁, 入队时, 尝试获取队尾的锁, 线程 1 获取到锁后, 创建节点 1, 发送信号通知其他线程, 发送节点 1 的指针, 线程 2 抢占到节点 1 的锁后,创建节点 2, 线程 2 发送节点 2 指针,通知其他线程...
这个方法需要另外两个数据结构来发送数据才行,具体性能变高变低我也不不知道😂