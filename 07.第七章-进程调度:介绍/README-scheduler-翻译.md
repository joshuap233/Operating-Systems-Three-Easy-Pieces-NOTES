scheduler.py 可让你查看在调度指标（例如响应时间，周转时间和总等待时间）下不同的调度程序如何执行
程序实现了三个调度算法：FIFO(先到先服务)，SJF(最短任务优先)和 RR(轮转)。
运行该程序有两个步骤:
首先，以不带-c 参数运行: 这显示了你需要解决什么问题，而没有透露答案。
例如,如果你要使用 FIFO 策略计算响应时间，周转时间并等待三个作业，请运行以下命令：

```shell script
./scheduler.py -p FIFO -j 3 -s 100
```

如果上面的命令没有生效,执行下面的命令:
```shell script
python ./scheduler.py -p FIFO -j 3 -s 100
```

这指定了具有三个作业的 FIFO 策略，并且指定随机种子为 100。
如果您想查看此确切问题的解决方案，你可以再次指定这个完全相同的随机种子。

让我们运行它，看看会发生什么。 这是会看到的：
```shell script
prompt> ./scheduler.py -p FIFO -j 3 -s 100
ARG policy FIFO
ARG jobs 3
ARG maxlen 10
ARG seed 100

Here is the job list, with the run time of each job: 
  Job 0 (length = 1)
  Job 1 (length = 4)
  Job 2 (length = 7)

Compute the turnaround time, response time, and wait time for each job.  When
you are done, run this program again, with the same arguments, but with -c,
which will thus provide you with the answers. You can use -s <somenumber> or
your own job list (-l 10,15,20 for example) to generate different problems for
yourself.
```

从该示例可以看到，生成了三个作业：长度为 1 的作业 0，长度为 4 的作业 1，以及长度为 7 的作业 2。
如程序所描述的, 你现在可以使用它来计算一些统计信息，并检查您是否掌握了相关基本概念。

完成后，您可以使用相同的程序来“解决”问题，并查看您的工作是否正确。使用“ -c”标志来达到目的。
输出：

```shell script
prompt> ./scheduler.py -p FIFO -j 3 -s 100 -c
ARG policy FIFO
ARG jobs 3
ARG maxlen 10
ARG seed 100

Here is the job list, with the run time of each job: 
  Job 0 (length = 1)
  Job 1 (length = 4)
  Job 2 (length = 7)

** Solutions **

Execution trace:
  [time   0] Run job 0 for 1.00 secs (DONE)
  [time   1] Run job 1 for 4.00 secs (DONE)
  [time   5] Run job 2 for 7.00 secs (DONE)

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 1.00  Wait 0.00
  Job   1 -- Response: 1.00  Turnaround 5.00  Wait 1.00
  Job   2 -- Response: 5.00  Turnaround 12.00  Wait 5.00

  Average -- Response: 2.00  Turnaround 6.00  Wait 2.00

```

从打印结果可以看到，-c 标志向你栈示发生了什么。 
作业 0 首先运行 1 秒，作业 1 运行 4 秒，然后作业 2 运行 7 秒。
不是太难; 毕竟是 FIFO！ 程序跟踪显示这些结果。

最终统计信息也很有用：
它们计算“响应时间”（作业到达后到第一次运行之前花费的时间），
“周转时间”（自到达以来完成工作所花费的时间）和总计 “等待时间”（准备就绪但没有运行的时间）。
统计信息显示每个作业的信息与平均值，
当然，在使用“ -c”标志运行之前，您应该已经计算了所有这些内容！

如果您想尝试相同类型的问题，但输入内容不同，
请尝试更改作业数量或更改随机种子或同时更改两者。 
基本上，不同的随机种子为您提供了一种为自己产生无限数量的不同问题的方法，
而“ -c”标志可让您检查自己的工作。 继续这样做，直到您真正了解这些概念为止。

另一个有用的标志是“ -l”（小写 L），
它使您可以指定要查看的确切作业调度信息。 
例如，如果您想了解 SJF 如何处理长度为 5、10 和 15 的三个作业，则可以运行：

<pre>
prompt> ./scheduler.py -p SJF -l 5,10,15
ARG policy SJF
ARG jlist 5,10,15

Here is the job list, with the run time of each job: 
  Job 0 (length = 5.0)
  Job 1 (length = 10.0)
  Job 2 (length = 15.0)
...
</pre>

然后，您可以使用-c 参数再次解决它。
请注意，当您指定确切的作业时，无需指定随机种子或作业数量：作业长度取自逗号分隔的列表。

当然，当您使用 SJF（最短作业优先）或 RR（轮询）调度程序时，会发生更多有趣的事情。 试试看！


你可以随时运行

```shell script
  ./scheduler.py -h 
```

以获得完整参数列表（包括诸如设置 RR 调度程序的时间片之类的选项）。

译者注:
参数列表
<pre>
Options:
  -h, --help            帮助信息
  -s SEED, --seed=SEED  随机种子
  -j JOBS, --jobs=JOBS  作业数量
  -l JLIST, --jlist=JLIST
                        提供一个以逗号分隔的运行时间列表，而不是随机长度作业
  -m MAXLEN, --maxlen=MAXLEN
                        作业的最大长度(运行时间)
  -p POLICY, --policy=POLICY
                        调度策略: SJF, FIFO, RR
  -q QUANTUM, --quantum=QUANTUM
                        RR策略的时间片长度
  -c                    计算答案
</pre>