欢迎使用 multi.py，一个简单的的多 CPU 调度模拟器。模拟器具有许多功能，所以注意！如果你懒得这么做的话，当考试即将开始的时候...

只需输入下面的命令来运行模拟器：

```bash
prompt> ./multi.py
```



它会使用一些随机作业来运行模拟器。



在深入探讨它的运行细节之前，让我们首先看看这个模拟器的基本用法。

在默认模式下，系统中有一个或多个CPU（用 -n 标志指定）。 因此要在模拟器中运行 4 个CPU时，请输入：

```bash
prompt> ./multi.py -n 4
```



每个CPU都有一个缓存，该缓存可以保存来自一个或多个正在运行的进程的重要数据。 每个 CPU 高速缓存的大小由 -M 标志设置。 因此，要使 CPU 个数为 4 ，高速缓存大小为 100，请运行：

```bash
prompt> ./multi.py -n 4 -M 100
```



要运行模拟器，你需要安排一些作业。 有两种方法可以做到这一点。 第一种是让模拟器创建一些具有随机作业（这是默认设置，如果你不指定任何参数，就会使用这条规则运行模拟器）； 还有一些参数可以控制随机生成的作业的一些特征，如下所述。 第二种方法是是指定作业列表，以供模拟器精确调度； 下面有更详细的描述。



每个工作都有两个特征。 第一个是它的“运行时间”（它将运行多少时间单位）。 第二个是它的“工作集大小”（运行需要多少缓存空间）。 如果你随机生成作业，则可以使用 -R（最大运行时间标志）和 -W（最大工作集大小标志）来控制这些值的范围。 然后，随机生成器将生成不大于这些值的值。



如果要手动指定作业列表，则可以使用 -L 标志显式地设置每个作业。 例如，如果要运行两个作业，每个作业的运行时间为 100，但工作集大小分别为 50 和 150，则可以执行以下操作：

```bash
prompt> ./multi.py -n 4 -M 100 -L 1:100:50,2:100:150
```



请注意，你为每个作业分配了名称，第一个作业名称为“1”，第二个作业名称为“ 2”。 作业生成后，将自动分配名称（仅使用数字）。

作业在特定 CPU 上的运行效率取决于该 CPU 的缓存当前是否缓存了当前作业的工作集。 如果没有缓存，则作业运行缓慢，which means that only 1 tick of its runtime is subtracted from its remaining time left per each tick of the clock。 这是作业缓存的 “冷”（cold）模式（缓存还没有包含该作业的工作集）。 但是如果该作业以前在CPU上运行了“足够长的时间”，则该 CPU 缓存处于“热”（warm）模式，并且该作业将更快地执行。 你问快多少？ 好吧，这取决于 -r 标志的值，即 “预热速率”（warmup rate）。 在这里，默认情况下它差不多是两倍，但是你可以根据需要进行更改。

缓存需要多长时间才能预热（warm up）？这也是由 -w 标志设置的，用于设置“预热时间”（warmup time）。 默认情况下，它差不多是 10 个时间单位。 因此，如果作业以 10 个时间单位运行，则该 CPU 上的缓存会变热（warm），然后作业开始运行得更快。 当然，所有这些都是对真实系统工作原理的粗略估算，但这就是模拟的美，对吗？

因此，现在我们有多个 CPU，每个CPU都有高速缓存，以及一种指定作业的方式。 还剩啥？ 调度策略！

第一个（默认）策略很简单：集中式调度队列，将作业循环分配到空闲 CPU。 第二种是按 CPU 分配调度队列（使用 -p 打开），其中将作业分配给 N 个调度队列之一（每个 CPU 一个）； 在这种方法中，空闲的CPU有时会窥视其他CPU的队列并窃取作业，以改善负载平衡。 通过“窥视”间隔（由 -P 标志设置）来设置执行操作的频率。

有了这些基本的了解之后，你现在应该可以完成家庭作业，并研究不同的调度方法。 要查看此模拟器的完整选项列表，只需输入：

```text
prompt> ./multi.py -h
Usage: multi.py [options]

Options:
Options:
  -h, --help            显示帮助消息并退出
  -s SEED, --seed=SEED  指定随机种子
  -j JOB_NUM, --job_num=JOB_NUM
                        系统中的作业数量
  -R MAX_RUN, --max_run=MAX_RUN
                        随机生成作业的最大运行时间
  -W MAX_WSET, --max_wset=MAX_WSET
                        随机生成作业的最大工作集
  -L JOB_LIST, --job_list=JOB_LIST
  						提供以逗号分隔的 job_name：run_time：working_set_size 列表
  						例如 a:10:100,b:10:50 表示 2 个作业的运行时间为 10，第一个（a）的工作集大小为 100，
  						第二个（b）工作集大小为50
  -p, --per_cpu_queues  每个CPU的一个调度队列
  -A AFFINITY, --affinity=AFFINITY
  						作业列表以及它们可以在哪些 CPU 上运行
  						例如 a:0.1.2,b:0.1 允许作业 a 在CPU 0、1、2上运行，b 仅在CPU 0 、1 上运行
  -n NUM_CPUS, --num_cpus=NUM_CPUS
                        cpu 数量
  -q TIME_SLICE, --quantum=TIME_SLICE
                        时间片的长度
  -P PEEK_INTERVAL, --peek_interval=PEEK_INTERVAL
  						对于每个 CPU 的调度，多久检查其他调度队列；设置为 0 将其关闭
  -w WARMUP_TIME, --warmup_time=WARMUP_TIME
                        变成热缓存的时间
  -r WARM_RATE, --warm_rate=WARM_RATE
                        热缓存有多快
  -M CACHE_SIZE, --cache_size=CACHE_SIZE
                        缓存大小
  -o, --rand_order      has CPUs get jobs in random order
  -t, --trace           启用基本跟踪（显示已调度的作业）
  -T, --trace_time_left
                        trace time left for each job
  -C, --trace_cache     trace cache status (warm/cold) too
  -S, --trace_sched     trace scheduler state
  -c, --compute         compute answers for me


```

最好的了解方法是添加一些跟踪选项（例如 -t，-T，-C 和 -S）。 试一试这些选项，以更好地了解调度程序和系统在做什么。






