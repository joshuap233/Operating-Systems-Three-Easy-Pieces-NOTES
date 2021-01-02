lottery.py 程序允许你查看彩票调度策略的工作方式。 
与往常一样，有两个步骤可以运行该程序。
首先，在没有 -c 标志的情况下运行：这将向你显示要解决的问题而没有给出答案。

<pre>
prompt> ./lottery.py -j 2 -s 0
</pre>

<pre>
...
Here is the job list, with the run time of each job: 
  Job 0 ( length = 8, tickets = 75 )
  Job 1 ( length = 4, tickets = 25 )

Here is the set of random numbers you will need (at most):
Random 511275
Random 404934
Random 783799
Random 303313
Random 476597
Random 583382
Random 908113
Random 504687
Random 281838
Random 755804
Random 618369
Random 250506
]

</pre>

当你以这种方式运行模拟器时，它首先会为你分配一些随机作业（此处长度为 8 和 4），
每个作业都有一定数量的彩票（分别为 75 和 25）。
模拟器还为你提供了一个随机数列表，你需要确定随机数列表，以决定彩票调度程序将执行的操作。
随机数应 >=0,因此，你必须使用模运算符来计算彩票中奖者（即中奖者应将该随机数等于系统中彩票总数的模）。

使用 -c 参数运行可以准确显示你应该计算的内容：

<pre>
prompt> ./lottery.py -j 2 -s 0 -c
...
** Solutions **
Random 511275 -> Winning ticket 75 (of 100) -> Run 1
  Jobs:  (  job:0 timeleft:8 tix:75 ) (* job:1 timeleft:4 tix:25 )
Random 404934 -> Winning ticket 34 (of 100) -> Run 0
  Jobs:  (* job:0 timeleft:8 tix:75 ) (  job:1 timeleft:3 tix:25 )
Random 783799 -> Winning ticket 99 (of 100) -> Run 1
  Jobs:  (  job:0 timeleft:7 tix:75 ) (* job:1 timeleft:3 tix:25 )
Random 303313 -> Winning ticket 13 (of 100) -> Run 0
  Jobs:  (* job:0 timeleft:7 tix:75 ) (  job:1 timeleft:2 tix:25 )
Random 476597 -> Winning ticket 97 (of 100) -> Run 1
  Jobs:  (  job:0 timeleft:6 tix:75 ) (* job:1 timeleft:2 tix:25 )
Random 583382 -> Winning ticket 82 (of 100) -> Run 1
  Jobs:  (  job:0 timeleft:6 tix:75 ) (* job:1 timeleft:1 tix:25 )
--> JOB 1 DONE at time 6
Random 908113 -> Winning ticket 13 (of 75) -> Run 0
  Jobs:  (* job:0 timeleft:6 tix:75 ) (  job:1 timeleft:0 tix:--- )
Random 504687 -> Winning ticket 12 (of 75) -> Run 0
  Jobs:  (* job:0 timeleft:5 tix:75 ) (  job:1 timeleft:0 tix:--- )
Random 281838 -> Winning ticket 63 (of 75) -> Run 0
  Jobs:  (* job:0 timeleft:4 tix:75 ) (  job:1 timeleft:0 tix:--- )
Random 755804 -> Winning ticket 29 (of 75) -> Run 0
  Jobs:  (* job:0 timeleft:3 tix:75 ) (  job:1 timeleft:0 tix:--- )
Random 618369 -> Winning ticket 69 (of 75) -> Run 0
  Jobs:  (* job:0 timeleft:2 tix:75 ) (  job:1 timeleft:0 tix:--- )
Random 250506 -> Winning ticket 6 (of 75) -> Run 0
  Jobs:  (* job:0 timeleft:1 tix:75 ) (  job:1 timeleft:0 tix:--- )
--> JOB 0 DONE at time 12
]
</pre>

从跟踪中可以看到，你应该做的是使用随机数来确定哪张彩票中奖。
然后，给定中奖票，找出应该执行的工作。
重复此操作，直到所有作业完成运行。 就是这么简单--你只是在模拟彩票调度程序的功能，并且是手动操作！

为了使这一点更清楚，让我们看一下上面示例中的第一个决定。 
此时，我们有两个作业（作业 0 的运行时间为 8,拥有 75 张彩票，作业 1 的运行时间为 4,拥有 25 张彩票）。 
我们得到的第一个随机数是(511275%100) = 75 。
由于系统中有 100 张彩票，因此 75 是我们的中奖彩票。

如果 75 号彩票是中奖彩票，我们只需搜索工作清单，直到找到它。
对于作业 0，第一个条目有 75 张票（0 到 74），因此没有中奖； 
下一个作业是作业 1，因此我们找到了中奖者，因此我们以时间片长度(在本示例中为 1）运行作业 1。 
所有这些都在打印输出中显示如下：

<pre>
Random 511275 -> Winning ticket 75 (of 100) -> Run 1
  Jobs:  (  job:0 timeleft:8 tix:75 ) (* job:1 timeleft:4 tix:25 )
]
</pre>

如您所见，第一行总结了发生的情况，第二行仅显示了整个作业队列，并带有*表示选择了哪个作业。

模拟器还有其他一些选择，其中大多数应该是不言自明的。 
最值得注意的是，-l/-jlist 参数可用于指定一组确切的作业及其彩票数，而不是始终使用随机生成的作业列表。

<pre>
prompt> ./lottery.py -h
Usage: lottery.py [options]
</pre>

<pre>
Options:
  -h, --help            
      帮助信息
  -s SEED, --seed=SEED  
      随机种子
  -j JOBS, --jobs=JOBS  
      系统中的作业数量
  -l JLIST, --jlist=JLIST
      不使用随机作业，而是提供以逗号分隔的运行时间和彩票数列表
      (例如10：100,20：100将有两个作业，其运行时间分别为10和20，每个作业具有100张彩票)
  -m MAXLEN, --maxlen=MAXLEN
      工作的最大长度
  -T MAXTICKET, --maxtick=MAXTICKET
      最大门彩票数(如果随机分配)
  -q QUANTUM, --quantum=QUANTUM
      时间片长
  -c, --compute
      计算结果
</pre>
