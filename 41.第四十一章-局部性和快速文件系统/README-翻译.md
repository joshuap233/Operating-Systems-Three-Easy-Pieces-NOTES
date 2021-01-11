这是 ffs.py 的 README 文件，它是 FFS 分配策略的模拟器。 使用它来研究在不同文件和目录创建方案下的 FFS 行为。 

通过使用 -f 标志指定命令文件来使用该工具，该命令文件由一系列的文件创建、文件删除和目录创建操作组成。

例如，运行：

```shell script
prompt> ./ffs.py -f in.example1 -c
```

来查看第一个示例的输出来了解基于 FFS 的工作原理。

in.example1 中的文件由以下命令组成：

```text
dir /a
dir /b
file /a/c 2
file /a/d 2
file /a/e 2
file /b/f 2
```

这告诉模拟器创建两个目录(/a and /b) 于四个文件(/a/c, /a/d, /a/e, and /b/f).根目录会自动创建.

模拟器的输出是所有现存文件和目录的 inodes 和数据块的位置。 例如，运行上面的命令，我们最终会看到（启用 -c 标志，以向您显示结果）：

```text
prompt> ./ffs.py -f in.example1 -c
num_groups:       10
inodes_per_group: 10
blocks_per_group: 30

free data blocks: 289 (of 300)
free inodes:      93 (of 100)

spread inodes?    False
spread data?      False
contig alloc:     1

      0000000000 0000000000 1111111111 2222222222
      0123456789 0123456789 0123456789 0123456789

group inodes     data
    0 /--------- /--------- ---------- ----------
    1 acde------ accddee--- ---------- ----------
    2 bf-------- bff------- ---------- ----------
    3 ---------- ---------- ---------- ----------
    4 ---------- ---------- ---------- ----------
    5 ---------- ---------- ---------- ----------
    6 ---------- ---------- ---------- ----------
    7 ---------- ---------- ---------- ----------
    8 ---------- ---------- ---------- ----------
    9 ---------- ---------- ---------- ----------

prompt>
```


输出的第一部分向我们展示了模拟器的各种参数，从创建的 FFS 柱面组的数量到一些策略详细信息。
但是输出的主要部分是实际分配图：

```text

      0000000000 0000000000 1111111111 2222222222
      0123456789 0123456789 0123456789 0123456789

group inodes     data
    0 /--------- /--------- ---------- ----------
    1 acde------ accddee--- ---------- ----------
    2 bf-------- bff------- ---------- ----------
    3 ---------- ---------- ---------- ----------
    4 ---------- ---------- ---------- ----------
    5 ---------- ---------- ---------- ----------
    6 ---------- ---------- ---------- ----------
    7 ---------- ---------- ---------- ----------
    8 ---------- ---------- ---------- ----------
    9 ---------- ---------- ---------- ----------
```


对于这个示例，我们创建了一个具有 10 个组的文件系统，每个组具有 10 个 inode 和 30 个数据块。 每个组仅显示 inode 和数据块以及它们的分配方式。 如果它们是空闲的，则显示 -。否则，每个文件显示一个不同的符号。

如果要查看符号到文件名的映射，则应使用 -M 标志：

```shell script
prompt> ./ffs.py -f in.example1 -c -M
```

然后，您将在输出的底部看到一个表格，表格中显示了每个符号的含义：

```text
symbol  inode#  filename     filetype
/            0  /            directory
a           10  /a           directory
c           11  /a/c           regular
d           12  /a/d           regular
e           13  /a/e           regular
b           20  /b           directory
f           21  /b/f           regular
```

在这里，您可以看到根目录由符号 / 表示，文件 /a 由符号 a 表示，依此类推。



通过查看输出，您可以看到许多有趣的事情：
- 根 inode 在 inode 表的 Group 0 的第一个插槽中
- root 数据块在分配的第一个数据块（Group 0）中找到 
- 目录 /a 放置在组 1 中，目录 /b 放置在组 2 中
- 每个常规文件的文件（节点和数据）与它们的父节点位于同一组中（根据 FFS）

其余选项使您可以使用 FFS 和一些较小的变体。 他们是：

```text
prompt> ./ffs.py -h
Usage: ffs.py [options]

Options:
  -h, --help            显示帮助信息
  -s SEED, --seed=SEED  随机种子
  -n NUM_GROUPS, --num_groups=NUM_GROUPS
                        柱面组的数量
  -d BLOCKS_PER_GROUP, --datablocks_per_groups=BLOCKS_PER_GROUP
                        每个组的块数量
  -i INODES_PER_GROUP, --inodes_per_group=INODES_PER_GROUP
                        每个组的inodes数量
  -L LARGE_FILE_EXCEPTION, --large_file_exception=LARGE_FILE_EXCEPTION
                        0：关闭，N> 0：在将文件存储到下一个组之前在组中进行阻止
  -f INPUT_FILE, --input_file=INPUT_FILE
                        命令文件
  -I, --spread_inodes   不将文件 inode 放在父目录组中，不如将它们均匀分布在所有组中
  -D, --spread_data     不要将数据放在inode附近，而是将数据均匀地分布在所有组中
  -A ALLOCATE_FARAWAY, --allocate_faraway=ALLOCATE_FARAWAY
                        When picking a group, examine this many groups at a
                        time
  -C CONTIG_ALLOCATION_POLICY,
  --contig_allocation_policy=CONTIG_ALLOCATION_POLICY  
                        需要分配的 contig 空闲块数
  -T, --show_spans      显示文件和目录范围
  -M, --show_symbol_map
                        显示符号图
  -B, --show_block_addresses
                        show block addresses alongside groups
  -S, --do_per_file_stats
                        print out detailed inode stats
  -v, --show_file_ops   print out detailed per-op success/failure
  -c, --compute         compute answers for me

We'll explore more of these options in the homework.
```




