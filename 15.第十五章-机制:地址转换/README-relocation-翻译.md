该程序使您可以查看在具有基址和界限寄存器的系统中如何执行地址转换。
和以前一样，有两个步骤可以运行该程序以测试您对基址和界限寄存器的理解。 
首先，在不使用 -c 标志的情况下运行以生成一组转换，并查看您是否可以自己正确执行地址转换。 
然后，完成后，使用 -c 标志运行以检查您的答案。

在这个作业中，我们假定的地址空间与规范的地址空间略有不同，规范的地址空间在两端分别是堆和栈。 
相反，我们将假定地址空间具有一个代码段，然后是一个固定大小（小）的栈，以及一个随即向下增长的堆，如下图所示。 
在这种配置中，堆只有一个增长方向，即朝向地址空间的更高区域增长。

<pre>
  -------------- 0KB
  |    Code    |
  -------------- 2KB
  |   Stack    |
  -------------- 4KB
  |    Heap    |
  |     |      |
  |     v      |
  -------------- 7KB
  |   (free)   |
  |     ...    |
</pre>

在图中，边界寄存器将设置为 7KB，因为它表示地址空间的末尾。 
在范围内任何地址均视为合法； 高于此值的范围，硬件将引发异常。

要使用默认参数运行，请在命令行中输入`relocation.py`
结果应该是这样的：

<pre>
prompt> ./relocation.py 
...
Base-and-Bounds register information:

  Base   : 0x00003082 (decimal 12418)
  Limit  : 472

Virtual Address Trace
  VA  0: 0x01ae (decimal:430) -> PA or violation?
  VA  1: 0x0109 (decimal:265) -> PA or violation?
  VA  2: 0x020b (decimal:523) -> PA or violation?
  VA  3: 0x019e (decimal:414) -> PA or violation?
  VA  4: 0x0322 (decimal:802) -> PA or violation?

For each virtual address, either write down the physical address it 
translates to OR write down that it is an out-of-bounds address 
(a segmentation violation). For this problem, you should assume a 
simple virtual address space of a given size.
</pre>

如您所见，这个作业只是简单生成随机的虚拟地址。 
您应该确定每个虚拟地址是否在范围内，如果是，则确定它转换到哪个物理地址。 
使用 -c（"为我计算答案"）可以为我们提供这些转换的结果，即它们是否有效以及有效的物理地址。 
为了方便起见，所有数字均以十六进制和十进制给出。

<pre>
prompt> ./relocation.py -c
...
Virtual Address Trace
  VA  0: 0x01ae (decimal:430) -> VALID: 0x00003230 (dec:12848)
  VA  1: 0x0109 (decimal:265) -> VALID: 0x0000318b (dec:12683)
  VA  2: 0x020b (decimal:523) -> SEGMENTATION VIOLATION
  VA  3: 0x019e (decimal:414) -> VALID: 0x00003220 (dec:12832)
  VA  4: 0x0322 (decimal:802) -> SEGMENTATION VIOLATION
]
</pre>

在基地址为 12418（十进制）的情况下，地址 430 在范围之内（即小于 472 的界限寄存器），
因此转换为(430 加 12418 或 12848)的地址。
上面显示的一些地址超出范围 （523，802），因为它们超出了界限寄存器范围。
很简单，不是吗？ 确实，这是基址和界限寄存器的优点之一：太简单了！

您可以使用一些参数来控制正在发生的事情：

<pre>
prompt> ./relocation.py -h
Usage: relocation.py [options]

Options:
  -h, --help            帮助信息
  -s SEED, --seed=SEED  设置随机种子
  -a ASIZE, --asize=ASIZE 地址空间大小 (e.g., 16, 64k, 32m)
  -p PSIZE, --physmem=PSIZE 物理内存大小(e.g., 16, 64k)
  -n NUM, --addresses=NUM # 生成虚拟地址数量
  -b BASE, --b=BASE     基址寄存器的值
  -l LIMIT, --l=LIMIT   界限寄存器的值
  -c, --compute         计算结果
]
</pre>

您可以控制虚拟地址空间的大小（-a），
物理内存的大小（-p），
要生成的虚拟地址的数量（-n）
以及为此的基址和界限寄存器的值 （分别为-b 和-l）。

