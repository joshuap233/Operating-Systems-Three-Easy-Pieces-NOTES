mlfq.py 可让您查看本章介绍的 MLFQ 调度程序的行为。 
和以前一样，可以使用随机种子使用它来为自己产生问题，也可以使用它来构建精心设计的实验，以了解 MLFQ 在不同情况下的工作方式。
要运行该程序，请输入：

```shell script
prompt> ./mlfq.py
```

使用 -h 参数查看帮助：
<pre>
Usage: mlfq.py [options]
Options:
  -h, --help            显示此帮助信息并退出
  -s SEED, --seed=SEED  指定随机种子
  -n NUMQUEUES, --numQueues=NUMQUEUES
                        MLFQ中的队列数（如果没有使用-Q）
  -q QUANTUM, --quantum=QUANTUM
                        时间片长度(如果没有使用-Q参数)
  -Q QUANTUMLIST, --quantumList=QUANTUMLIST
                        指定为x，y，z，...为每个队列级别的时间片长度，
                        其中x是优先级最高的队列的时间片长度，y是第二高的队列的时间片长度，依此类推
  -j NUMJOBS, --numJobs=NUMJOBS
                        系统中的作业数
  -m MAXLEN, --maxlen=MAXLEN
                        作业的最大运行时间（如果是随机的）
  -M MAXIO, --maxio=MAXIO
                        作业的最大I/O频率（如果是随机的）
  -B BOOST, --boost=BOOST
                        将所有作业的优先级提高到高优先级的频率（0表示从不）
  -i IOTIME, --iotime=IOTIME
                        I/O 持续时间（固定常数)
  -S, --stay            发出I/O时重置并保持相同的优先级
  -l JLIST, --jlist=JLIST
                        以逗号分隔的要运行的作业列表，格式为x1，y1，z1：x2，y2，z2：...。
                        其中x是开始时间，y是运行时间，z是作业I/O的频率
  -c                    计算答案
]
</pre>

模拟器有几种使用方法。 
一种方法是生成一些随机作业，并查看您是否可以确定 MLFQ 调度程序的工作方式。 
例如，如果您想创建一个随机生成的三个作业，则只需输入：

```shell script
prompt> ./mlfq.py -j 3
```

然后您将看到指定的问题定义：

<pre>
Here is the list of inputs:
OPTIONS jobs 3
OPTIONS queues 3
OPTIONS 时间片长  作业2 为  10
OPTIONS 时间片长  作业1 为  10
OPTIONS 时间片长  作业0 为  10
OPTIONS 提高整体优先级 0
OPTIONS io时间 0
OPTIONS IO后保持优先级 False
</pre>

对于每个作业，给出了三个特征值：
startTime：该作业在什么时候进入系统
runTime：任务完成所需的总 CPU 时间
ioFreq：I/O 需要 ioTime 时间来完成

<pre>
Job List:
  Job  0: startTime   0 - runTime  84 - ioFreq   7
  Job  1: startTime   0 - runTime  42 - ioFreq   2
  Job  2: startTime   0 - runTime  51 - ioFreq   4
</pre>

计算给定工作负载的跟踪结果。
如果你愿意，还可以计算每个作业的响应时间和周转时间。

当您完成时，使用 -c 参数来获得确切的结果。

这将生成了三个作业的随机工作负载（如指定的）,使用默认设置与队列数量
如果您再次使用（-c）参数运行，则会看到与上述相同的打印输出，以及以下内容：

<pre>
    Execution Trace:
    
    [ time 0 ] JOB BEGINS by JOB 0
    [ time 0 ] JOB BEGINS by JOB 1
    [ time 0 ] JOB BEGINS by JOB 2
    [ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 83 (of 84) ]
    [ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 82 (of 84) ]
    [ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 81 (of 84) ]
    [ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 80 (of 84) ]
    [ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 79 (of 84) ]
    [ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 78 (of 84) ]
    [ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 77 (of 84) ]
    [ time 7 ] IO_START by JOB 0
    IO DONE
    [ time 7 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 41 (of 42) ]
    [ time 8 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 40 (of 42) ]
    [ time 9 ] Run JOB 1 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 39 (of 42) ]
    ...
    
    Final statistics:
      Job  0: startTime   0 - response   0 - turnaround 175
      Job  1: startTime   0 - response   7 - turnaround 191
      Job  2: startTime   0 - response   9 - turnaround 168
    
      Avg  2: startTime n/a - response 5.33 - turnaround 178.00
    ]
</pre>

跟踪以毫秒为单位, 准确显示了调度程序决定执行的操作。 
在此示例中，它从运行作业 0 7 毫秒开始，直到作业 0 发出 I/O 结束。
这完全可以预见，因为作业 0 的 I/O 频率设置为 7ms，这意味着它每运行 7ms，它将发出一个 I/O 并等待其完成才继续。
此时，调度程序将切换到作业 1，该作业仅在发出 I/O 之前运行 2 ms。 
调度程序以这种方式打印整个执行跟踪，最后还计算每个作业的响应时间和周转时间以及平均值。

你还可以控制模拟的其他各个方面。 
例如，你可以指定系统中要有多少个队列（-n），
以及所有这些队列的时间片长度应为（-q）,
如果您想要每个队列更多的控制权和可变的时间片长度，
则可以使用 -Q 为每个队列指定量子（时间片）的长度，
例如 -Q 10,20,30 模拟具有三个队列的调度程序， 优先级最高的队列具有 10 毫秒的时间片，
次高的队列具有 20 毫秒的时间片，低优先级队列具有 30 毫秒的时间片。

你可以使用 -a 为所有队列或使用 -A 的每个队列单独设置队列分配时间.
例如 -A 20,40,60 将每个队列的时间分配分别设置为 20ms，40ms 和 60ms。

如果你随机生成作业，则还可以控制它们可能运行多长时间(-m)或进行 I/O 的频率(-M)
但是，如果您想更好地控制系统中运行的作业的特征，则可以使用 -l（小写 L）或 --jlist，这允许您指定要模拟的作业集。
列表的格式为：x1，y1，z1：x2，y2，z2：...其中 x 是作业的开始时间，y 是运行时间(即，它需要多少 CPU 时间),
而 z I/O 频率（即，在运行 z ms 之后，作业将进行 I/O；如果 z 为 0，则不会发出 I/O）。

例如，如果您想重新创建图 8.3 中的示例，则可以如下指定作业列表：

```shell script
prompt> ./mlfq.py --jlist 0,180,0:100,20,0 -q 10 
```

以这种方式运行模拟器会创建一个三级 MLFQ，每级都有 10 毫秒的时间片。 
创建了两个作业：作业 0 从时间 0 开始，总共运行 180 毫秒，并且从不发出 I/O。
作业 1 从 100 毫秒开始，仅需要 20 毫秒即可完成，并且永远不会发出 I/O。

最后，还有三有趣的参数。 
如果将-B 参数设置为非零值，则按如下方式每 N 毫秒将所有作业提升到优先级最高的队列：

```shell script
prompt> ./mlfq.py -B N 
```

调度程序使用此功能来避免饥饿,但是，默认情况下处于关闭状态。

-S 参数调用较旧的规则 4a 和 4b(p58 4a,4b 规则)，
这意味着，如果作业在完成其时间片之前发出 I/O，
则它将在恢复执行时返回到相同的优先级队列，时间片重置。
这使得调度器能够进行游戏。

最后，您可以使用 -i 标志轻松更改 I/O 的持续时间。 在此简化模型中，默认情况下，每个 I/O 占用固定的 5 毫秒时间，或使用此标志设置的时间。 

您还可以使用-I 标志来解决是将刚完成 I/O 的作业移到它们所在队列的开头还是后面.检查一下，这很有趣！
