课后作业(编码):
在本作业中，您将获得一些编写并发代码并评估其性能的经验。 学习构建性能良好的代码是一项关键技能，因此，从中获得一点经验是非常值得的

问题:

1.我们将在本章中重新进行度量。使用调用gettimeofday()来度量程序中的时间。
这个计时器有多精确?它能确定的最小间隔是多少?要对它的工作方式有信心，因为在接下来的所有问题中我们都需要它。您还可以使用其他计时器，比如通过x86提供的`rdtsc`指令使用循环计数器

`gettimeofday` 精度为微秒级([参考](https://blog.csdn.net/russell_tao/article/details/7185588))
`rdtsc`指令,成本与精确度都是纳秒级(取决于cpu使用周期)
`rdtsc`测试方法参考:[How to Benchmark Code Execution Times on Intel® IA-32 and IA-64 Instruction Set Architectures](https://www.intel.com/content/dam/www/public/us/en/documents/white-papers/ia-32-ia-64-benchmark-code-execution-paper.pdf)

2.现在，构建一个简单的并发计数器，并测量随着线程数量的增加，多次增加计数器所需的时间。 您正在使用的系统上有多少个CPU可用？ 这个数字是否会完全影响您的测量？

运行:
```
cd 2 && python3 plot.py
```

查看CPU信息:
```
cat /proc/cpuinfo
```


3.接下来，构建一个 懒惰计数器(sloppy counter) 的版本。 根据线程数以及阈值来衡量其性能。 这些数字是否与您在本章中看到的一致？

```
cd 3 && python3 plot.py
```

4.如本章所述，构建使用`and-over-hand`锁[MS04]的链表版本。 您应该先阅读 paper 以了解其工作原理，然后再实现它并且衡量其性能。 何时 基于`hand-over-hand`锁的链表 比 标准链表 更有效？

5.选择你喜欢的数据结构，例如B树或其他稍微有趣的结构。 实现它，然后从简单的锁策略开始，例如单个锁。 随着并发线程数的增加来衡量其性能。

6.最后，为您喜欢的这种数据结构考虑一个更有趣的锁定策略。 实施并衡量其性能。与直接加锁的方法相比，它又如何？
