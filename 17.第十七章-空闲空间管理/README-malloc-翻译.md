malloc.py 允许您查看简单的内存分配器的工作方式。 以下是您可以使用的选项：

<pre>
  -h, --help            帮助信息
  -s SEED, --seed=SEED  随机种子
  -S HEAPSIZE, --size=HEAPSIZE
                        堆大小
  -b BASEADDR, --baseAddr=BASEADDR
                        堆的开始地址
  -H HEADERSIZE, --headerSize=HEADERSIZE
                        header块大小
  -a ALIGNMENT, --alignment=ALIGNMENT
                        align allocated units to size; -1->no align
  -p POLICY, --policy=POLICY
                        空闲空间搜索算法 (BEST, WORST, FIRST)
  -l ORDER, --listOrder=ORDER
                        空闲列表排序 (ADDRSORT, SIZESORT+, SIZESORT-, INSERT-FRONT, INSERT-BACK)
  -C, --coalesce        合并空闲列表

  -n OPSNUM, --numOps=OPSNUM
                        要生成的随机操作的数量
  -r OPSRANGE, --range=OPSRANGE
                        最大分配空间大小
  -P OPSPALLOC, --percentAlloc=OPSPALLOC
                        分配空间的操作的百分比
  -A OPSLIST, --allocList=OPSLIST
                        不随机分配操作, 指定操作列表(+10,-0,etc)
  -c, --compute         计算答案
</pre>

一种使用它的方法是让程序生成一些随机分配/释放(allocation/free)操作,
检查你能不能弄清楚空闲列表是什么样子的,以及每个操作的成功或失败。
这里有一个简单的例子:

<pre>
prompt> ./malloc.py -S 100 -b 1000 -H 4 -a 4 -l ADDRSORT -p BEST -n 5 

ptr[0] = Alloc(3)  returned ?
List?

Free(ptr[0]) returned ?
List?

ptr[1] = Alloc(5)  returned ?
List?

Free(ptr[1]) returned ?
List?

ptr[2] = Alloc(8)  returned ?
List?

</pre>

在此示例中，我们指定了一个大小为 100 字节（-S 100）的堆，从地址 1000（-b 1000）开始。 
我们为每个分配的块指定另外的 4 个字节的 Header 块（-H 4），
并确保每个分配的空间都向上舍入到最接近的 4 字节(的整数倍)的空闲块大小（-a 4）。 
我们指定空闲列表按地址排序（递增）。 
最后，我们指定“最佳适应算法”的空闲列表搜索策略（-p BEST），并要求生成 5 个随机操作（-n 5）。
运行结果在上面； 你需要做的是弄清楚每个分配/释放(allocation/free)操作返回什么，以及每个操作之后空闲列表的状态。

我们使用-c 选项查看结果。
```shell script
prompt> ./malloc.py -S 100 -b 1000 -H 4 -a 4 -l ADDRSORT -p BEST -n 5 -c
```

<pre>
ptr[0] = Alloc(3)  returned 1004 (searched 1 elements)
Free List [ Size 1 ]:  [ addr:1008 sz:92 ]

Free(ptr[0]) returned 0
Free List [ Size 2 ]:  [ addr:1000 sz:8 ] [ addr:1008 sz:92 ]

ptr[1] = Alloc(5)  returned 1012 (searched 2 elements)
Free List [ Size 2 ]:  [ addr:1000 sz:8 ] [ addr:1020 sz:80 ]

Free(ptr[1]) returned 0
Free List [ Size 3 ]:  [ addr:1000 sz:8 ] [ addr:1008 sz:12 ] [ addr:1020 sz:80 ]

ptr[2] = Alloc(8)  returned 1012 (searched 3 elements)
Free List [ Size 2 ]:  [ addr:1000 sz:8 ] [ addr:1020 sz:80 ]
</pre>


如你所见，第一个分配操作（分配）返回以下信息：
<pre>
ptr[0] = Alloc(3)  returned 1004 (searched 1 elements)
Free List [ Size 1 ]:  [ addr:1008 sz:92 ]
</pre>

因为空闲列表的初始状态只是一整块大内存，所以很容易猜测到 Alloc(3)将请求成功。
此外，它将仅返回内存的第一块并将其余部分放入空闲列表。 
返回的指针将刚好超出 header 块（地址：1004），并且分配的空间将向上舍入为 4 个字节，
在空闲列表中,剩余了从 1008 开始的 92 字节空间。

下一个操作是 free 操作(`"ptr [0]"`)，该操作存储前一个内存分配请求的结果。
如你所料，free 将成功(返回"0"），并且 free 列表现在看起来有些复杂：

<pre>
Free(ptr[0]) returned 0
Free List [ Size 2 ]:  [ addr:1000 sz:8 ] [ addr:1008 sz:92 ]
</pre>

确实，因为我们没有合并空闲列表，所以我们现在有两个块，第一个块是 8 字节,保存着刚释放的空间，第二个块是 92 字节大块。

我们确实可以通过-C 标志合并，结果是：

<pre>
prompt> ./malloc.py -S 100 -b 1000 -H 4 -a 4 -l ADDRSORT -p BEST -n 5 -c -C
ptr[0] = Alloc(3)  returned 1004 (searched 1 elements)
Free List [ Size 1 ]:  [ addr:1008 sz:92 ]

Free(ptr[0]) returned 0
Free List [ Size 1 ]:  [ addr:1000 sz:100 ]

ptr[1] = Alloc(5)  returned 1004 (searched 1 elements)
Free List [ Size 1 ]:  [ addr:1012 sz:88 ]

Free(ptr[1]) returned 0
Free List [ Size 1 ]:  [ addr:1000 sz:100 ]

ptr[2] = Alloc(8)  returned 1004 (searched 1 elements)
Free List [ Size 1 ]:  [ addr:1012 sz:88 ]
</pre>

你可以看到，当执行 Free 操作时，空闲列表将按预期合并。
.

还有其他一些有趣的参数可供探索：
<pre>
* -p (BEST, WORST, FIRST)
  该选项允许您使用这三种不同的策略来查找要在分配请求期间使用的内存块

* -l (ADDRSORT, SIZESORT+, SIZESORT-, INSERT-FRONT, INSERT-BACK)
  该选项使您可以按特定顺序保留空闲列表，
  例如按空闲块的地址，空闲块的大小（a + 为递增, a - 为递减）排序，
  或仅将空闲块插入空闲列表前面（INSERT- FRONT）或后方（INSERT-BACK）。

* -A (list of ops)
  该选项允许您详细指定操作，而不是随机生成的操作。

  例如，使用标志“ -A +10,+10,+10,-0,-2”运行将分配三个大小为10字节的块（包括Header块），
  然后释放第一个（"-0"）,然后释放第三个（"-2"）。 那么，空闲列表会是什么样？
</pre>
 
这些是基础。 使用本书章节中的问题来探索更多内容，或者自己创建新的有趣的问题，以更好地了解分配器的功能。





  

  
