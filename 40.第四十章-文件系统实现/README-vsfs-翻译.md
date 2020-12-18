文件系统最初的状态为空，只有一个根目录。在进行模拟时，将执行各种操作，从而缓慢更改文件系统的磁盘状态。


可能进行的操作有：

- mkdir() - 创建文件夹
- creat() - 创建新的空文件
- open(), write(), close() - 将一个块添加到文件
- link()   - 创建一个文件的硬链接
- unlink() - 删除一个硬链接 (如果 linkcnt==0,删除文件)

要了解此作业的功能，您必须首先了解如何表示此文件系统的磁盘状态。 
通过打印四种不同数据结构的内容来显示文件系统的状态：

inode bitmap - 标识哪些 inode 已经被分配
inodes       - inode 表及内容
data bitmap  - 标识哪些数据块已经被分配
data         - 数据块的内容

位图应该非常容易理解，其中 1 表示分配了相应的 inode 或数据块，0 表示该 inode 或数据块是空闲的。

每个 inodes 都有三个字段：第一个字段指示文件的类型（例如，f 表示常规文件，d 表示目录）； 
第二个指示哪个数据块属于该文件（在这里，数据块的地址为 -1 表示文件是空的，地址为非负数时,表示文件引用的数据块地址）； 
第三个显示文件或目录的引用计数。 例如，以下索引节点是一个常规文件，该文件为空（地址字段设置为 -1 ），并且在文件系统中只有一个链接：

<pre>
  [f a:-1 r:1]
</pre>

如果为该文件分配了一个块（例如块 10），则将显示如下：
<pre>
  [f a:10 r:1]
</pre>

如果有人随后创建了到该文件的硬链接，它将变成：
<pre>
  [f a:10 r:2]
</pre>

最后，数据块可以保留用户数据或目录数据。如果保存的 s 是目录数据，则块中的每个条目的格式均为
（name，inumber），其中 “name” 是文件或目录的名称，“inumber” 是文件的 inode 号。 
因此，假设根的 inode 为 0，则空的根目录如下所示：

<pre>
  [(.,0) (..,0)]
</pre>

如果我们在根目录中添加一个已分配索引号 1 的文件 “f”，则根目录内容将变为：

<pre>
  [(.,0) (..,0) (f,1)]
</pre>

如果数据块保存的是用户数据，则该数据块仅显示为单个字符，例如 “h”。 如果为空且未分配，
则仅显示一对空括号（[]）。

因此，整个文件系统如下所示：

<pre>
inode bitmap 11110000
inodes       [d a:0 r:6] [f a:1 r:1] [f a:-1 r:1] [d a:2 r:2] [] ...
data bitmap  11100000
data         [(.,0) (..,0) (y,1) (z,2) (f,3)] [u] [(.,3) (..,0)] [] ...
</pre>

该文件系统具有八个 inode 和八个数据块。 根目录包含三个条目（不包括".",".."）: "y"，"z"和 "f"。
通过查找 inode 1，我们可以看到 "y" 是一个常规文件（类型为 f），并为其分配了一个数据块（地址 1）。 
数据块 1 中是文件 "y"的内容：即 "u"。 我们还可以看到 "z" 是一个空的常规文件（地址字段设置为-1），
而 "f"（ inode 编号 3 ）是一个目录，也为空。 您还可以从位图中看到前四个 inode 位图条目被标记为已分配，
以及前三个数据位图条目被标记为已分配。

可以使用以下标志运行模拟器：

```shell script
prompt> vsfs.py -h
Usage: vsfs.py [options]

Options:
  -h, --help            显示此帮助消息并退出
  -s SEED, --seed=SEED  指定随机种子
  -i NUMINODES, --numInodes=NUMINODES 
                        文件系统中的 inode 数量
  -d NUMDATA, --numData=NUMDATA 
                        文件系统中数据块的数量
  -n NUMREQUESTS, --numRequests=NUMREQUESTS 
                        要求模拟的操作数量
  -r, --reverse         不打印状态,而是打印操作
  -p, --printFinal      打印所有文件/目录
  -c, --compute         计算结果
]
```

典型的用法是简单地指定一个随机种子（以产生一个不同的问题）以及模拟请求的数量。 
在此默认模式下，模拟器会在每个步骤中打印出文件系统的状态，并询问您必须执行哪种操作才能将文件系统从一
种状态转换为另一种状态。 例如：

<pre>
prompt> vsfs.py -n 6 -s 16
...
Initial state

inode bitmap  10000000
inodes        [d a:0 r:2] [] [] [] [] [] [] [] 
data bitmap   10000000
data          [(.,0) (..,0)] [] [] [] [] [] [] [] 

Which operation took place?

inode bitmap  11000000
inodes        [d a:0 r:3] [f a:-1 r:1] [] [] [] [] [] [] 
data bitmap   10000000
data          [(.,0) (..,0) (y,1)] [] [] [] [] [] [] [] 

Which operation took place?

inode bitmap  11000000
inodes        [d a:0 r:3] [f a:1 r:1] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (y,1)] [u] [] [] [] [] [] [] 

Which operation took place?

inode bitmap  11000000
inodes        [d a:0 r:4] [f a:1 r:2] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (y,1) (m,1)] [u] [] [] [] [] [] [] 

Which operation took place?

inode bitmap  11000000
inodes        [d a:0 r:4] [f a:1 r:1] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (y,1)] [u] [] [] [] [] [] [] 

Which operation took place?

inode bitmap  11100000
inodes        [d a:0 r:5] [f a:1 r:1] [f a:-1 r:1] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (y,1) (z,2)] [u] [] [] [] [] [] [] 

Which operation took place?

inode bitmap  11110000
inodes        [d a:0 r:6] [f a:1 r:1] [f a:-1 r:1] [d a:2 r:2] [] ...
data bitmap   11100000
data          [(.,0) (..,0) (y,1) (z,2) (f,3)] [u] [(.,3) (..,0)] [] ...
]
</pre>

在这种模式下运行时，模拟器仅显示一系列状态，并询问是什么操作导致了这些状态的变化。 
使用 "-c" 标志运行会向我们显示答案。 具体来说，创建了文件 "/y" ，在其上附加了一个块，
创建了从 "/m" 到 "/y" 的硬链接，通过调用 unlink 删除了 "/m" ，创建了文件 "/z"，并创建目录 "/f" ：

<pre>
prompt> vsfs.py -n 6 -s 16 -c
...
Initial state

inode bitmap  10000000
inodes        [d a:0 r:2] [] [] [] [] [] [] [] 
data bitmap   10000000
data          [(.,0) (..,0)] [] [] [] [] [] [] [] 

creat("/y");

inode bitmap  11000000
inodes        [d a:0 r:3] [f a:-1 r:1] [] [] [] [] [] [] 
data bitmap   10000000
data          [(.,0) (..,0) (y,1)] [] [] [] [] [] [] [] 

fd=open("/y", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);

inode bitmap  11000000
inodes        [d a:0 r:3] [f a:1 r:1] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (y,1)] [u] [] [] [] [] [] [] 

link("/y", "/m");

inode bitmap  11000000
inodes        [d a:0 r:4] [f a:1 r:2] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (y,1) (m,1)] [u] [] [] [] [] [] [] 

unlink("/m")

inode bitmap  11000000
inodes        [d a:0 r:4] [f a:1 r:1] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (y,1)] [u] [] [] [] [] [] [] 

creat("/z");

inode bitmap  11100000
inodes        [d a:0 r:5] [f a:1 r:1] [f a:-1 r:1] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (y,1) (z,2)] [u] [] [] [] [] [] [] 

mkdir("/f");

inode bitmap  11110000
inodes        [d a:0 r:6] [f a:1 r:1] [f a:-1 r:1] [d a:2 r:2] [] ...
data bitmap   11100000
data          [(.,0) (..,0) (y,1) (z,2) (f,3)] [u] [(.,3) (..,0)] [] ...
]
</pre>

您还可以在“反向”模式（带有 "-r" 标志）下运行模拟器，打印操作而不是状态，以查看是否可以预测给定操作的状态变化：

<pre>
prompt> ./vsfs.py -n 6 -s 16 -r
Initial state

inode bitmap  10000000
inodes        [d a:0 r:2] [] [] [] [] [] [] [] 
data bitmap   10000000
data          [(.,0) (..,0)] [] [] [] [] [] [] [] 

creat("/y");

  State of file system (inode bitmap, inodes, data bitmap, data)?

fd=open("/y", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);

  State of file system (inode bitmap, inodes, data bitmap, data)?

link("/y", "/m");

  State of file system (inode bitmap, inodes, data bitmap, data)?

unlink("/m")

  State of file system (inode bitmap, inodes, data bitmap, data)?

creat("/z");

  State of file system (inode bitmap, inodes, data bitmap, data)?

mkdir("/f");

  State of file system (inode bitmap, inodes, data bitmap, data)?
]
</pre>

其他一些标志控制着模拟器的各个方面，包括 inodes 的数量（"-i"），
数据块的数量（"-d"）以及是否打印文件系统中所有目录和文件的最终列表（"-p"）。


