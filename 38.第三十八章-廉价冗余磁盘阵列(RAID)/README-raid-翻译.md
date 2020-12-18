本部分介绍 raid.py，这是一个简单的 RAID 模拟器，可用于增强你 RAID 系统的工作原理的了解。 它具有许多选项，如下所示：

Usage: raid.py [options]

<pre>
Options:
  -h, --help            查看帮助信息
  -s SEED, --seed=SEED  设置随机种子
  -D NUMDISKS, --numDisks=NUMDISKS
                        设置 RAID 磁盘数量
  -C CHUNKSIZE, --chunkSize=CHUNKSIZE
                        设置 RAID 块大小
  -n NUMREQUESTS, --numRequests=NUMREQUESTS
                        需要模拟的请求数量
  -S SIZE, --reqSize=SIZE
                        请求大小
  -W WORKLOAD, --workload=WORKLOAD
                        使用"rand"或"seq"指定随机或顺序工作方式
  -w WRITEFRAC, --writeFrac=WRITEFRAC
                        设置写入所占百分比（例如设置为，100，则所有请求为写入，设置为0，则所有请求为读取）
  -R RANGE, --randRange=RANGE
                        请求块范围（当使用"rand"工作方式时生效）
  -L LEVEL, --level=LEVEL
                        RAID 等级 (0, 1, 4, 5)
  -5 RAID5TYPE, --raid5=RAID5TYPE
                        RAID-5 left-symmetric "LS" or left-asym "LA"
  -r, --reverse         不显示逻辑读写操作，而是显示读写物理操作详情
  -t, --timing          use timing mode, instead of mapping mode
  -c, --compute         计算结果
</pre>

在其基础模式下，您可以使用它来了解不同的 RAID 级别如何将逻辑块映射到物理磁盘与计算偏移量。 
例如，假设我们希望看到具有四个磁盘的简单条带化 RAID（RAID-0）如何进行映射。

```shell script
prompt> ./raid.py -n 5 -L 0 -R 20 
```

<pre>
...
LOGICAL READ from addr:16 size:4096
  Physical reads/writes?

LOGICAL READ from addr:8 size:4096
  Physical reads/writes?

LOGICAL READ from addr:10 size:4096
  Physical reads/writes?

LOGICAL READ from addr:15 size:4096
  Physical reads/writes?

LOGICAL READ from addr:9 size:4096
  Physical reads/writes?
</pre>

在此示例中，我们模拟五个请求（-n 5），将 RAID 级别指定为 0（-L 0），并将随机请求的范围限制为 RAID 的前二十个块（-R 20）。 
结果是对 RAID 的前二十个块进行了一系列的随机读取。然后，对于每次逻辑读取，模拟器都会要求您猜测访问了哪些底层磁盘/偏移量来为请求服务。

在这种情况下，计算答案很容易：在 RAID-0 中，回想起为请求提供服务的基础磁盘和偏移量是通过模运算来计算的：

<pre>
  disk   = address % number_of_disks
  offset = address / number_of_disks
</pre>

因此，对地址为 16 的第一个请求应由磁盘 0（偏移量 4）来服务。
依此类推。 您可以照常查看答案（一旦计算出结果！），方法是使用方便的"-c"标志来计算结果。

```shell script
prompt> ./raid.py -R 20 -n 5 -L 0 -c
```

<pre>
...
LOGICAL READ from addr:16 size:4096
  read  [disk 0, offset 4]   

LOGICAL READ from addr:8 size:4096
  read  [disk 0, offset 2]   

LOGICAL READ from addr:10 size:4096
  read  [disk 2, offset 2]   

LOGICAL READ from addr:15 size:4096
  read  [disk 3, offset 3]   

LOGICAL READ from addr:9 size:4096
  read  [disk 1, offset 2]   
</pre>

为了让我们玩得开心，所以也可以使用" -r"标志来反向解决此问题。 
以这种方式运行模拟器将向您显示物理磁盘的读写，并要求您反向计算必须向 RAID 发出哪些逻辑请求：

```shell script
prompt> ./raid.py -R 20 -n 5 -L 0 -r
```

<pre>
...
LOGICAL OPERATION is ?
  read  [disk 0, offset 4]   

LOGICAL OPERATION is ?
  read  [disk 0, offset 2]   

LOGICAL OPERATION is ?
  read  [disk 2, offset 2]   

LOGICAL OPERATION is ?
  read  [disk 3, offset 3]   

LOGICAL OPERATION is ?
  read  [disk 1, offset 2]   
</pre>

您可以再次使用 -c 查看答案。 为了获得更多的遍体，可以使用不同的随机种子（-s）。

通过检查不同的 RAID 级别，甚至可以提供更多的多样性。 在模拟器中，支持 RAID-0（块条带化），
RAID-1（镜像），RAID-4（块条带化和一个奇偶校验磁盘）和 RAID-5（带奇偶校验的块条带化）。

在下一个示例中，我们显示如何在镜像模式下运行模拟器。 我们直接显示答案来节省空间：

```shell script
prompt> ./raid.py -R 20 -n 5 -L 1 -c
```

<pre>
...
LOGICAL READ from addr:16 size:4096
  read  [disk 0, offset 8]   
 
LOGICAL READ from addr:8 size:4096
  read  [disk 0, offset 4]   

LOGICAL READ from addr:10 size:4096
  read  [disk 1, offset 5]   

LOGICAL READ from addr:15 size:4096
  read  [disk 3, offset 7]   

LOGICAL READ from addr:9 size:4096
  read  [disk 2, offset 4]   
</pre>

您可能会注意到有关这个示例的一些信息。首先，镜像的 RAID-1 采取条带化布局（有人可能将其称为 RAID-01），
其中逻辑块 0 映射到磁盘 0 和 1 的第 0 块，逻辑块 1 映射到磁盘 2 和磁盘 3 的第 0 块。，依此类推（在这个示例中有四个磁盘）。 
其次，从镜像 RAID 系统读取单个块时，RAID 可以选择读取两个块中的哪个。 在此模拟器中，我们使用了一种相对简单的方式：
对于偶数逻辑块，RAID 在该对中选择偶数磁盘； 奇数盘读取奇数逻辑块。
这样做是为了使您可以轻松地猜测每次运行的结果（而不是随机选择等）。

我们还可以使用 -w 标志探索写操作的方式（而不是仅读取），该标志指定工作负载的“写比例”，即写请求的比例。 
默认情况下，它设置为零，因此到目前为止的示例为 100% 读取。 让我们看看引入一些写操作后镜像 RAID 会发生什么：

```shell script
prompt> ./raid.py -R 20 -n 5 -L 1 -w 100 -c
```

<pre>
... 
LOGICAL WRITE to  addr:16 size:4096
  write [disk 0, offset 8]     write [disk 1, offset 8]   

LOGICAL WRITE to  addr:8 size:4096
  write [disk 0, offset 4]     write [disk 1, offset 4]   

LOGICAL WRITE to  addr:10 size:4096
  write [disk 0, offset 5]     write [disk 1, offset 5]   

LOGICAL WRITE to  addr:15 size:4096
  write [disk 2, offset 7]     write [disk 3, offset 7]   

LOGICAL WRITE to  addr:9 size:4096
  write [disk 2, offset 4]     write [disk 3, offset 4]   
</pre>

对于写入操作，RAID 必须更新两个磁盘，而不是仅对单个物理磁盘进行写操作，因此会发出两次写入操作的请求。 
您可能会猜到，RAID-4 和 RAID-5 会发生更多有趣的事情。 我们将在问题中探索这些事情。

其余选项可通过 help 标志找到。他们分别是：

<pre>
Options:
  -h, --help            show this help message and exit
  -s SEED, --seed=SEED  the random seed
  -D NUMDISKS, --numDisks=NUMDISKS
                        number of disks in RAID
  -C CHUNKSIZE, --chunkSize=CHUNKSIZE
                        chunk size of the RAID
  -n NUMREQUESTS, --numRequests=NUMREQUESTS
                        number of requests to simulate
  -S SIZE, --reqSize=SIZE
                        size of requests
  -W WORKLOAD, --workload=WORKLOAD
                        either "rand" or "seq" workloads
  -w WRITEFRAC, --writeFrac=WRITEFRAC
                        write fraction (100->all writes, 0->all reads)
  -R RANGE, --randRange=RANGE
                        range of requests (when using "rand" workload)
  -L LEVEL, --level=LEVEL
                        RAID level (0, 1, 4, 5)
  -5 RAID5TYPE, --raid5=RAID5TYPE
                        RAID-5 left-symmetric "LS" or left-asym "LA"
  -r, --reverse         instead of showing logical ops, show physical
  -t, --timing          use timing mode, instead of mapping mode
  -c, --compute         compute answers for me
</pre>

-C 标志允许您设置 RAID 的块大小，而不是使用默认大小（默认每个块 4 KB）。 
可以使用 -S 标志让模拟器调整每个请求的大小。 默认工作负载访问随机块； 
使用 -W 探索顺序访问的行为。使用 RAID-5 时，可以使用两种不同的布局方案，
即左对称（left-symmetric）和非左对称（left-asymmetric）。
使用 -5 LS 或 -5 LA 来使用 （-L 5）。


最后，在计时模式（-t）中，模拟器使用了一个非常简单的磁盘模型来估计一组请求所花费的时间，
而不仅仅是关注映射。在这种模式下，随机请求需要 10 毫秒，而顺序请求则需要 0.1 毫秒。 
假定该磁盘的每个磁道的块数量很少（100），并且磁道的数量也类似（100）。 
因此，您可以使用模拟器来估计某些不同工作负载下的 RAID 性能。

