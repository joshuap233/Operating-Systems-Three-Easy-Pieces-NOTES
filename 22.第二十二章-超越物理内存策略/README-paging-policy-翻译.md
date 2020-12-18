这个模拟器`paging-policy.py`使您可以试用不同的页面替换策略。
例如，让我们检查一下 LRU 如何使用大小为 3 个页面的缓存处理一系列的页：

<pre>
  0 1 2 0 1 3 0 3 1 2 1
</pre>

为此，请按以下方式运行模拟器：

```shell script
prompt> ./paging-policy.py --addresses=0,1,2,0,1,3,0,3,1,2,1 --policy=LRU --cachesize=3 -c
```

你会看到的是:
<pre>

ARG addresses 0,1,2,0,1,3,0,3,1,2,1
ARG numaddrs 10
ARG policy LRU
ARG cachesize 3
ARG maxpage 10
ARG seed 0

Solving...

Access: 0 MISS LRU->      [br 0]<-MRU Replace:- [br Hits:0 Misses:1]
Access: 1 MISS LRU->   [br 0, 1]<-MRU Replace:- [br Hits:0 Misses:2]
Access: 2 MISS LRU->[br 0, 1, 2]<-MRU Replace:- [br Hits:0 Misses:3]
Access: 0 HIT  LRU->[br 1, 2, 0]<-MRU Replace:- [br Hits:1 Misses:3]
Access: 1 HIT  LRU->[br 2, 0, 1]<-MRU Replace:- [br Hits:2 Misses:3]
Access: 3 MISS LRU->[br 0, 1, 3]<-MRU Replace:2 [br Hits:2 Misses:4]
Access: 0 HIT  LRU->[br 1, 3, 0]<-MRU Replace:2 [br Hits:3 Misses:4]
Access: 3 HIT  LRU->[br 1, 0, 3]<-MRU Replace:2 [br Hits:4 Misses:4]
Access: 1 HIT  LRU->[br 0, 3, 1]<-MRU Replace:2 [br Hits:5 Misses:4]
Access: 2 MISS LRU->[br 3, 1, 2]<-MRU Replace:0 [br Hits:5 Misses:5]
Access: 1 HIT  LRU->[br 3, 2, 1]<-MRU Replace:0 [br Hits:6 Misses:5]
]
</pre>

下免列出了用于分页策略的所有可能参数，其中包括几个用于更改策略的参数，以及如何指定/生成地址以及其他重要参数（例如缓存大小）的参数。

<pre>
prompt> ./paging-policy.py --help
Usage: paging-policy.py [options]

Options:
-h, --help      显示帮助信息
-a ADDRESSES, --addresses=ADDRESSES
                一组以逗号分隔的要访问的页面
                -1 意思是随机生成
-f ADDRESSFILE, --addressfile=ADDRESSFILE
                指定包含地址的文件
-n NUMADDRS, --numaddrs=NUMADDRS
                如果 -a (--addresses)参数是 -1,这是要生成的地址数量
-p POLICY, --policy=POLICY
                替换策略: FIFO, LRU, LFU, OPT, 
                                    UNOPT, RAND, CLOCK
-b CLOCKBITS, --clockbits=CLOCKBITS
                使用 CLOCK 策略时, how many clock bits to use
-C CACHESIZE, --cachesize=CACHESIZE
                页面缓存大小
-m MAXPAGE, --maxpage=MAXPAGE
                当使用随机产生页面是,指定最大页面数
-s SEED, --seed=SEED  随机种子
-N, --notrace   不打印出详细的跟踪
-c, --compute   计算答案
]
</pre>
  
通常，“-c”用于解决一个指定的问题，当没有-c 参数时，访问信息只是被列出(程序不会告诉你访问是否成功)。

要产生随机问题，可以使用`-n /-numaddrs`参数指定随机生成地址数,
而不必使用`-a /-addresses`来指定一系列页面引用， `-s /-seed`用于指定其他随机种子。 例如：

<pre>
prompt> ./paging-policy.py -s 10 -n 3
.. .

假设使用FIFO替换策略,并且缓存大小为3个页面，计算出下面每个页面引用在页面缓存中是命中了还是没有命中。

Access: 5  Hit/Miss?  State of Memory?
Access: 4  Hit/Miss?  State of Memory?
Access: 5  Hit/Miss?  State of Memory?
]
</pre>
  
如您所见，在此示例中，我们指定`-n 3`，这意味着程序随机生成 3 个页面引用，
它分别是：5、7 和 5。随机种子被指定为 10(即指定了是什么使我们获得了这些特定的页面引用)。
在自己解决此问题后，让程序通过传递相同的参数并添加`-c`为您解决问题（下面仅显示相关部分）：

<pre>
prompt> ./paging-policy.py -s 10 -n 3 -c
...
Solving...

Access: 5 MISS FirstIn->   [br 5] <-Lastin Replace:- [br Hits:0 Misses:1]
Access: 4 MISS FirstIn->[br 5, 4] <-Lastin Replace:- [br Hits:0 Misses:2]
Access: 5 HIT  FirstIn->[br 5, 4] <-Lastin Replace:- [br Hits:1 Misses:2]
]
</pre>

默认策略是 FIFO，尽管其他策略也可用，包括 LRU、MRU、OPT(最优替换策略，它可以窥视未来，看看什么是最好的替换)、UNOPT(悲观替换)、RAND(随机替换)和 CLOCK(执行时钟算法)。
时钟算法还采用另一个参数(-b)，它表示每个页面应该保留多少位;
时钟位越多(clock bits)，算法在决定哪些页面应该保存在内存中时就越好。

其他选项包括：
<pre>
-C /-cachesize，它更改页面缓存的大小;

-m /-maxpage，当模拟器为你生成页面引用时,指定最大页码;

-f /-addressfile，如果您希望从真正的应用程序中获取跟踪信息，或者使用长跟踪信息作为输入，则可以指定包含地址的文件。
(which lets you specify a file with addresses in them, in case you wish to get traces 
from a real application or otherwise use a long trace as input.)
</pre>

