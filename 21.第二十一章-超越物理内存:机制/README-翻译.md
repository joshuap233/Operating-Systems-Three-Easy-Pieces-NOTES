在这个作业中，您将使用一个简单程序 mem.c 来研究交换性能。这个程序非常简单:它只分配一个特定大小的整数数组，然后(重复地)对其进行循环，对数组中的每个值进行递增。

输入 make 来构建它(并查看文件 Makefile，了解构建工作的详细信息)。

然后，输入 ./mem ，加一个数字来运行它。 该数字是数组的大小（以 MB 为单位）。 因此，使用小型数组（大小为 1 MB）运行：

```shell script
prompt> ./mem 1
```

使用更大的数组 (1 GB):

```shell script
prompt> ./mem 1024
```

程序将打印出完成每个循环所需的时间以及带宽（以 MB/s 为单位）。 
带宽特别有趣，因为它可以让您了解你的系统数据访问速度。 在现代系统上，值可能以 GB/s 为单位。

下面是运行的输出实例：

<pre>
prompt> ./mem 1000
allocating 1048576000 bytes (1000.00 MB)
  number of integers in array: 262144000
loop 0 in 448.11 ms (bandwidth: 2231.61 MB/s)
loop 1 in 345.38 ms (bandwidth: 2895.38 MB/s)
loop 2 in 345.18 ms (bandwidth: 2897.07 MB/s)
loop 3 in 345.23 ms (bandwidth: 2896.61 MB/s)
^C
prompt> 
</pre>

该程序首先告诉您它分配了多少内存（以字节，MB 和整数形式），
然后开始循环遍历数组。 第一个循环（在上面的示例中）花费了 448 毫秒； 因为该程序在不到半秒的时间内访问了 1000 MB，所以计算的带宽刚好超过 2000 MB/s（不足为奇）。


程序继续一遍又一遍地做同样的事情，for 循环 1，循环 2，等等。

重要提示:要停止程序，你必须杀死它。在 Linux(和所有基于 unix 的系统)上通过输入上面所示的 control-C (^C)来完成。

注意，当您使用较小的数组运行时，不会打印每个循环的性能数字。例如

<pre>
prompt>  ./mem 1
allocating 1048576 bytes (1.00 MB)
  number of integers in array: 262144
loop 0 in 0.71 ms (bandwidth: 1414.61 MB/s)
loop 607 in 0.33 ms (bandwidth: 3039.35 MB/s)
loop 1215 in 0.33 ms (bandwidth: 3030.57 MB/s)
loop 1823 in 0.33 ms (bandwidth: 3039.35 MB/s)
^C
prompt> 
</pre>

在这种情况下，程序只打印输出的一个示例，这样就不会有太多的输出充满屏幕。


代码本身很容易理解。一个重要的部分是内存分配:
<pre>
    // the big memory allocation happens here
    int *x = malloc(size_in_bytes);
</pre>

然后主循环开始:
```c
    while (1) {
	x[i++] += 1; // main work of loop done here.
```

剩下的只是计时和打印信息。详情请参阅 mem.c。

很多作业都是关于如何使用 vmstat 工具来监视系统的运行情况。阅读 vmstat 手册页(输入 man vmstat)，了解它如何工作的详细信息，以及输出的每一列意味着什么。



