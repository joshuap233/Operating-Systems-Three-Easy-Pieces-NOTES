这个程序叫 process-run.py, 允许您查看进程状态在 CPU 上运行时的变化情况.
如本章所述，进程可以处于几种不同的状态：

<pre>
  运行(RUNNING) - 进程正在使用CPU
  就绪(READY)   - 进程现在可以使用CPU，但是其他进程正在使用
  等待(WAITING) - 进程正在等待I / O完成(例如，它向磁盘发出请求)
  完成(DONE)    - 过程执行完毕
</pre>

在本作业中，我们将看到这些进程状态如何随着程序运行而改变，从而更好地了解进程如何工作。

要运行该程序并获取操作选项，请执行以下操作：

```shell script
prompt> ./process-run.py -h
```

如果这不起作用，请在命令前键入“ python”，如下所示：

```shell script
prompt> python process-run.py -h
```

您会看到的是：

<pre>
Usage: process-run.py [options]

Options:
  -h, --help            查看帮助信息
  -s SEED, --seed=SEED  随机种子
  -l PROCESS_LIST, --processlist=PROCESS_LIST
                        以逗号分隔的要运行的进程列表，格式为X1：Y1，X2：Y2，...，其中X是该进程应运行的指令数，Y是该指令将运行的概率（从0到100）,指令包括使用CPU或进行IO

  -L IO_LENGTH, --iolength=IO_LENGTH
                        IO花费时间
  -S PROCESS_SWITCH_BEHAVIOR, --switch=PROCESS_SWITCH_BEHAVIOR
                        当进程发出IO时,系统的反应: 
                        - SWITCH_ON_IO
                        - SWITCH_ON_END 
  -I IO_DONE_BEHAVIOR, --iodone=IO_DONE_BEHAVIOR
                        IO结束时的行为类型: IO_RUN_LATER/IO_RUN_IMMEDIATE
                        - IO_RUN_IMMEDIATE: 立即切换到这个进程
                        - IO_RUN_LATER: 自然切换到这个进程(例如:取决于进程切换行为)
  -c                    计算结果
  -p, --printstats      打印统计数据； 仅与-c参数一起使用是有效
</pre>

需要理解的最重要的是 PROCESS_LIST（由-l 或--processlist 参数指定），它精确指定每个正在运行的程序（或“进程”）将执行的操作。 一进程由指令组成，每个指令只能执行以下两项操作之一：
- 使用 cpu
- 发出 IO 请求（并等待其完成）

当一个进程使用 CPU（完全不进行 IO）时，它应该在 CPU 上的运行(RUNNING 态）或准备运行(READY 态)两个状态之间进行切换。 例如，下面是一个简单的例子，仅运行一个程序，而该程序仅使用 CPU（不进行 IO）。

<pre>
prompt> ./process-run.py -l 5:100 
Produce a trace of what would happen when you run these processes:
Process 0
  cpu
  cpu
  cpu
  cpu
  cpu

Important behaviors:
  System will switch when the current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO will run LATER (when it is its turn)

prompt> 
</pre>

我们指定的参数为"5：100"，这意味着程序应该由 5 条指令组成，并且每条指令为 CPU 指令的机会为 100％。

您可以使用-c 标志查看该过程发生了什么，该参数为您计算答案：

<pre>
You can see what happens to the process by using the -c flag, which computes the
answers for you:

prompt> ./process-run.py -l 5:100 -c
Time     PID: 0        CPU        IOs
  1     RUN:cpu          1
  2     RUN:cpu          1
  3     RUN:cpu          1
  4     RUN:cpu          1
  5     RUN:cpu          1
</pre>

这个结果不是很有趣:这个进程只是处于运行态，然后就执行完成了，在整个运行过程中都使用 CPU，因此在整个运行过程中都保持 CPU 忙碌，而不做任何 I/Os。

通过运行两个进程，让它稍微复杂一些：

<pre>
prompt> ./process-run.py -l 5:100,5:100
Produce a trace of what would happen when you run these processes:
Process 0
  cpu
  cpu
  cpu
  cpu
  cpu

Process 1
  cpu
  cpu
  cpu
  cpu
  cpu

Important behaviors:
  Scheduler will switch when the current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO will run LATER (when it is its turn)
</pre>

在这种情况下，将运行两个不同的进程，每个进程仅使用 CPU。 操作系统运行它们时会发生什么？让我们来看看: 

<pre>
prompt> ./process-run.py -l 5:100,5:100 -c
Time     PID: 0     PID: 1        CPU        IOs
  1     RUN:cpu      READY          1
  2     RUN:cpu      READY          1
  3     RUN:cpu      READY          1
  4     RUN:cpu      READY          1
  5     RUN:cpu      READY          1
  6        DONE    RUN:cpu          1
  7        DONE    RUN:cpu          1
  8        DONE    RUN:cpu          1
  9        DONE    RUN:cpu          1
 10        DONE    RUN:cpu          1
</pre>

正如您在上面看到的，首先运行“进程 ID”(或“PID”)为 0 的进程，而进程 1 准备运行，但只能等待 0 完成。当 0 完成后,它就移动到“完成”状态,1 进程开始运行。当 1 结束时，跟踪就完成了。

在提出一些问题之前，让我们再看一个例子。 在此示例中，该进程仅发出 I/O 请求。 我们使用-L 参数指定 I/O 以 5 个时钟周期完成

<pre>
prompt> ./process-run.py -l 3:0 -L 5
Produce a trace of what would happen when you run these processes:
Process 0
  io-start
  io-start
  io-start

Important behaviors:
  System will switch when the current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO will run LATER (when it is its turn)
</pre>

你认为执行跟踪会是什么样的?让我们来看看:

<pre>
prompt> ./process-run.py -l 3:0 -L 5 -c
Time     PID: 0        CPU        IOs
  1  RUN:io-start          1
  2     WAITING                     1
  3     WAITING                     1
  4     WAITING                     1
  5     WAITING                     1
  6* RUN:io-start          1
  7     WAITING                     1
  8     WAITING                     1
  9     WAITING                     1
 10     WAITING                     1
 11* RUN:io-start          1
 12     WAITING                     1
 13     WAITING                     1
 14     WAITING                     1
 15     WAITING                     1
 16*       DONE
</pre>

如你所见，该程序仅处理三个 I/O。 发出每个 I/O 时，进程进入等待状态，并且在设备忙于 I/O 时，CPU 处于空闲状态。

让我们打印一些统计信息（运行与上面相同的命令，但带有-p 参数）以查看一些总体行为：

<pre>
Stats: Total Time 16
Stats: CPU Busy 3 (18.75%)
Stats: IO Busy  12 (75.00%)
</pre>

如你所见，跟踪了 16 个时钟周期，但 CPU 忙的时间不到 20％。另一方面，IO 设备非常繁忙。 通常，我们希望使所有设备保持忙碌状态，因为这样可以更好地利用资源。

还有其他一些重要参数：

<pre>
There are a few other important flags:
  -s SEED, --seed=SEED  the random seed  
    this gives you way to create a bunch of different jobs randomly

  -L IO_LENGTH, --iolength=IO_LENGTH
    this determines how long IOs take to complete (default is 5 ticks)

  -S PROCESS_SWITCH_BEHAVIOR, --switch=PROCESS_SWITCH_BEHAVIOR
                        when to switch between processes: SWITCH_ON_IO, SWITCH_ON_END
    this determines when we switch to another process:
    - SWITCH_ON_IO, the system will switch when a process issues an IO
    - SWITCH_ON_END, the system will only switch when the current process is done 

  -I IO_DONE_BEHAVIOR, --iodone=IO_DONE_BEHAVIOR
                        type of behavior when IO ends: IO_RUN_LATER, IO_RUN_IMMEDIATE
    this determines when a process runs after it issues an IO:
    - IO_RUN_IMMEDIATE: switch to this process right now
    - IO_RUN_LATER: switch to this process when it is natural to 
      (e.g., depending on process-switching behavior)
</pre>

现在去回答本章后面的问题来了解更多。





