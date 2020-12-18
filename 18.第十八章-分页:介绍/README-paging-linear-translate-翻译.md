在本作业中，您将使用一个简单的程序（paging-linear-translate.py）来检查你是否了解简单的虚拟到物理地址转换如何与线性页表一起使用。 
要运行该程序，请记住只输入程序的名称`./paging-linear-translate.py`，也可以输入`python pages-linear-translate.py`。 
当使用-h（帮助）标志运行它时，您将看到：

<pre>
Usage: paging-linear-translate.py [options]

Options:
-h, --help              显示帮助信息
-s SEED, --seed=SEED    随机种子
-a ASIZE, --asize=ASIZE 
                        地址空间大小(e.g., 16, 64k, ...)
-p PSIZE, --physmem=PSIZE
                        物理空间大小 (e.g., 16, 64k, ...)
-P PAGESIZE, --pagesize=PAGESIZE
                        页的大小(e.g., 4k, 8k, ...)
-n NUM, --addresses=NUM 生成的虚拟地址数量
-u USED, --used=USED    映射的有效百分比
-v                      详细模式
-c                      计算答案
</pre>


首先不使用任何参数运行:

<pre>

ARG seed 0
ARG address space size 16k
ARG phys mem size 64k
ARG page size 4k
ARG verbose False

The format of the page table is simple:
The high-order (left-most) bit is the VALID bit.
  If the bit is 1, the rest of the entry is the PFN.
  If the bit is 0, the page is not valid.
Use verbose mode (-v) if you want to print the VPN # by
each entry of the page table.

Page Table (from entry 0 down to the max size)
   0x8000000c
   0x00000000
   0x00000000
   0x80000006

Virtual Address Trace
  VA  0: 0x00003229 (decimal:    12841) --> PA or invalid?
  VA  1: 0x00001369 (decimal:     4969) --> PA or invalid?
  VA  2: 0x00001e80 (decimal:     7808) --> PA or invalid?
  VA  3: 0x00002556 (decimal:     9558) --> PA or invalid?
  VA  4: 0x00003a1e (decimal:    14878) --> PA or invalid?

For each virtual address, write down the physical address it 
translates to OR write down that it is an out-of-bounds 
address (e.g., a segmentation fault).
</pre>



如您所见，该程序为您提供的是特定进程的页表（请记住，在具有线性页表的真实系统中，每个进程有一个页表；这里我们仅关注一个进程，其地址空间 ，因此是一个单页表）。 
页表告诉你地址空间的个虚拟页号（VPN），虚拟页已映射到的特定的物理号帧（PFN），页号有效或无效。

页表项的格式很简单：最左边的（高阶）位是有效位； 其余位（如果有效为 1）为 PFN。

在上面的示例中，页表将 VPN 0 映射到 PFN 0xc（十进制 12），将 VPN 3 映射到 PFN 0x6（十进制 6），虚拟页 1 和 2 无效(高位为 0)。

由于页表是线性数组，上面打印的内容是你自己查看位时在内存中内容的副本。 
(Because the page table is a linear array, what is printed above is a replica of what you would see in memory if you looked at the bits yourself.)
但是，如果使用详细标志（-v）运行，有时使用此模拟器会更容易。 
此标志还将 VPN（索引）打印到页表中。 在上面的示例中，使用-v 标志运行：

<pre>
Page Table (from entry 0 down to the max size)
  [       0]   0x8000000c
  [       1]   0x00000000
  [       2]   0x00000000
  [       3]   0x80000006
</pre>

然后，你需要做的是使用此页表将打印结果中提供给您的虚拟地址转换为物理地址。
让我们看第一个：`VA 0x3229`。 要将这个虚拟地址转换为物理地址，我们首先必须将其分解为虚拟页码和偏移量。
我们通过观察地址空间和页面大小的大小来做到这一点。 
在此示例中，地址空间设置为 16KB（非常小的地址空间），页面大小为 4KB。
因此，我们知道虚拟地址中有 14 位，偏移量为 12 位，为 VPN 留了 2 位。 
因此，使用我们的地址 0x3229（二进制 11 0010 0010 1001），我们知道前两位指定了 VPN。
因此，0x3229 位于虚拟页面 3 上，偏移量为 0x229。

接下来，我们在页表中查看 VPN 3 是否有效, 并映射到某个物理帧，我们可以看到它时有效的（高位为 1）并映射到物理页 6。
因此，我们可以过物理页 6 并将其加偏移量上来获得最终的物理地址，
如下所示：0x6000（物理页，转义到适当的位置）或 0x0229（偏移量），得出最终物理地址：0x6229。 
因此，在此示例中，我们可以看到虚拟地址 0x3229 转换为物理地址 0x6229。

要查看其余的解决方案（在自己计算完之后！），只需使用-c 标志（一如既往）即可：

<pre>
...
VA  0: 00003229 (decimal: 12841) --> 00006229 (25129) [VPN 3]
VA  1: 00001369 (decimal:  4969) --> Invalid (VPN 1 not valid)
VA  2: 00001e80 (decimal:  7808) --> Invalid (VPN 1 not valid)
VA  3: 00002556 (decimal:  9558) --> Invalid (VPN 2 not valid)
VA  4: 00003a1e (decimal: 14878) --> 00006a1e (27166) [VPN 3]
</pre>

当然，您可以更改这些参数来产生更多有趣的问题。 使用-h 标志运行程序，以查看有哪些选项：


- The -s flag changes the random seed and thus generates different
  page table values as well as different virtual addresses to translate.
- The -a flag changes the size of the address space.
- The -p flag changes the size of physical memory.
- The -P flag changes the size of a page.
- The -n flag can be used to generate more addresses to translate
  (instead of the default 5).
- The -u flag changes the fraction of mappings that are valid, from
  0% (-u 0) up to 100% (-u 100). The default is 50, which means
  that roughly 1/2 of the pages in the virtual address space will be valid.
- The -v flag prints out the VPN numbers to make your life easier.



