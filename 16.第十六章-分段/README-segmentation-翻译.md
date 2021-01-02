该程序使您可以查看在带分段的系统中如何执行地址转换。 
该系统使用的分段非常简单：地址空间只有*两个*段； 
此外，由进程生成的虚拟地址的高位确定该地址位于哪个段中：
0 为段 0（例如，代码和堆将驻留在其中），
1 为段 1（栈位于其中）。 
段 0 沿正方向（朝更高的地址）增长，而段 1 沿负方向增长。

在视觉上，地址空间如下所示：
<pre>
 --------------- virtual address 0
 |    seg0     |
 |             |
 |             |
 |-------------|
 |             |
 |             |
 |             |
 |             |
 |(unallocated)|
 |             |
 |             |
 |             |
 |-------------|
 |             |
 |    seg1     |
 |-------------| virtual address max (size of address space)
</pre>

您可能还记得分段的情况，每个分段都有一对基址/界限寄存器。
因此，在这个问题中，存在两对基址/界限寄存器。 
段 0 的基址说明段 0 的顶部地址(top)在物理内存中的位置,而界限寄存器则表明段的大小。 
段 1 的基址说明段 1 的底部(bottom)在物理内存中的位置，而界限寄存器也表明段的大小（或它在负方向上增长了多少）。

和以前一样，有两个步骤可以运行该程序以测试您对分段的理解。
首先，在不带“ -c”标志的情况下运行以生成一组地址，并查看您是否可以自己正确执行地址转换。 
然后，完成后，使用“ -c”参数运行以检查的答案。

例如，要使用默认参数运行，输入：

<pre>
prompt> ./segmentation.py 

(or 
prompt> python ./segmentation.py 
if that doesn't work)

You should see this:
  ARG seed 0
  ARG address space size 1k
  ARG phys mem size 16k
  
  Segment register information:

    Segment 0 base  (grows positive) : 0x00001aea (decimal 6890)
    Segment 0 limit                  : 472

    Segment 1 base  (grows negative) : 0x00001254 (decimal 4692)
    Segment 1 limit                  : 450

  Virtual Address Trace
    VA  0: 0x0000020b (decimal:  523) --> PA or segmentation violation?
    VA  1: 0x0000019e (decimal:  414) --> PA or segmentation violation?
    VA  2: 0x00000322 (decimal:  802) --> PA or segmentation violation?
    VA  3: 0x00000136 (decimal:  310) --> PA or segmentation violation?
    VA  4: 0x000001e8 (decimal:  488) --> PA or segmentation violation?

  For each virtual address, either write down the physical address it translates
  to OR write down that it is an out-of-bounds address (a segmentation
  violation). For this problem, you should assume a simple address space with
  two segments: the top bit of the virtual address can thus be used to check
  whether the virtual address is in segment 0 (topbit=0) or segment 1
  (topbit=1). Note that the base/limit pairs given to you grow in different
  directions, depending on the segment, i.e., segment 0 grows in the positive
  direction, whereas segment 1 in the negative.  
</pre>

然后，在你计算完虚拟地址转换后，使用“ -c”标志再次运行该程序。 
您将看到以下内容（不包括冗余信息）：

<pre>
  Virtual Address Trace
    VA  0: 0x0000020b (decimal:  523) --> SEGMENTATION VIOLATION (SEG1)
    VA  1: 0x0000019e (decimal:  414) --> VALID in SEG0: 0x00001c88 (decimal: 7304)
    VA  2: 0x00000322 (decimal:  802) --> VALID in SEG1: 0x00001176 (decimal: 4470)
    VA  3: 0x00000136 (decimal:  310) --> VALID in SEG0: 0x00001c20 (decimal: 7200)
    VA  4: 0x000001e8 (decimal:  488) --> SEGMENTATION VIOLATION (SEG0)
</pre>

如您所见，使用 -c，该程序将为您转换地址，因此您可以检查是否了解使用分段的系统如何转换地址。


当然，您可以使用一些参数来解决不同的问题。
一个特别重要的参数是 -s 或-seed 参数，它使您可以通过传递不同的随机种子来产生不同的问题。 
当然，在生成问题然后解决它时，请确保使用相同的随机种子。

您还可以使用一些参数来处理不同大小的地址空间和物理内存。 
例如，要在小型系统中进行实验，可以输入：
<pre>
  prompt> ./segmentation.py -s 100 -a 16 -p 32
  ARG seed 0
  ARG address space size 16
  ARG phys mem size 32
 
  Segment register information:

    Segment 0 base  (grows positive) : 0x00000018 (decimal 24)
    Segment 0 limit                  : 4

    Segment 1 base  (grows negative) : 0x00000012 (decimal 18)
    Segment 1 limit                  : 5

  Virtual Address Trace
    VA  0: 0x0000000c (decimal:   12) --> PA or segmentation violation?
    VA  1: 0x00000008 (decimal:    8) --> PA or segmentation violation?
    VA  2: 0x00000001 (decimal:    1) --> PA or segmentation violation?
    VA  3: 0x00000007 (decimal:    7) --> PA or segmentation violation?
    VA  4: 0x00000000 (decimal:    0) --> PA or segmentation violation?
</pre>

它告诉程序物理内存为 32 字节, 生成使用 16 字节地址空间的虚拟地址。 
如您所见，生成的虚拟地址很小（12、8、1、7 和 0）。 
您还可以看到，该程序将根据需要选择极小的基址寄存器和极限值。 使用 -c 运行以查看答案。

这个例子也应该告诉你每个基址/界限对的确切含义。 
例如，段 0 的基址设置为 24（十进制）的物理地址，大小为 4 个字节。 
因此，“虚拟”地址 0、1、2 和 3 有效 且在段 0 中，并且分别映射到物理地址 24、25、26 和 27。

负方向增长的段 1 有些麻烦。在上面的例子中，段 1 的基址寄存器设置为物理地址 18，大小为 5 个字节。 
这意味着虚拟地址空间的*最后*五个字节（在这种情况下为 11、12、13、14 和 15）是有效的虚拟地址，并且它们分别映射到物理地址 13、14、15、16 和 15。 17。

If that doesn't make sense，请再读一遍-您必须弄清楚这是如何工作的，以便解决所有这些问题。

请注意，您可以通过在 -a 或-p 标志传递的值上加上“ k”，“ m”甚至“ g”来指定更大的值，例如“千字节”，“兆字节”和“千兆字节” ”。 
因此，如果要在 32 MB 的物理内存中设置 1 MB 的地址空间来执行某些转换，则可以输入：

```shell script
prompt> ./segmentation.py -a 1m -p 32m
```

如果要更具体一点，可以使用--b0，-l0，-b1 和--l1 寄存器自己设置基址寄存器和界限寄存器值。 试试看。

最后,你可以运行
```shell script
prompt> ./segmentation.py -h 
```

获取所有参数

Enjoy!



