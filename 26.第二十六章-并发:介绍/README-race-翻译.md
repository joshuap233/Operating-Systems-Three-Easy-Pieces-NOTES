欢迎使用这个模拟器。 这个作业是通过了解线程如何交错执行来熟悉线程。
模拟器`x86.py`将帮助你解决问题。

模拟器模仿了由多个线程执行的简短汇编序列。
请注意，模拟器*不会*显示将要运行的 OS 代码（例如，执行上下文切换）； 
因此，您所看到的只是用户代码的交叉执行。

运行的汇编代码基于 x86，但有所简化。 在此指令集中，
有四个通用寄存器（ %ax，%bx，%cx，%dx ），一个程序计数器（PC）和一小部分指令就足以满足我们的要求。

这是我们将能够运行的示例代码片段：

```asm
.main
mov 2000, %ax   # get the value at the address
add $1, %ax     # increment it
mov %ax, 2000   # store it back
halt
```

该代码很容易理解。 第一条指令是 x86 的 "mov" 只是将 2000 中指定的地址中的值加载到寄存器 %ax 中。 
在这个 x86 指令的子集中，地址可以采用以下形式：

<pre>
  2000        -> 数字2000是地址
  (%cx)       -> 寄存器的内容（用括号括起来）形成地址
  1000(%dx)   -> 数字+寄存器内容构成地址
  10(%ax,%bx) -> 数字 + 寄存器1 + 寄存器2 构成地址
</pre>

为了存储一个值，同样使用了 "mov" 指令，但是这次将参数反过来，例如：

```asm
  mov %ax, 2000
```

看上面的指令序列，"add" 指令的意思应该很清晰：
它将立即数（由 $1 指定）添加到第二个参数指定的寄存器中（即 %ax=%ax +1 ）。

因此，我们现在可以理解上面的代码：它将值加载到地址 2000，对其加 1，然后将值存储回地址 2000。

假的 “halt” 指令只是停止运行该线程。

让我们运行模拟器，看看它们如何工作！ 假设上面的代码序列在文件`simple-race.s`中。

<pre>
prompt> ./x86.py -p simple-race.s -t 1 

       Thread 0
1000 mov 2000, %ax
1001 add $1, %ax
1002 mov %ax, 2000
1003 halt

prompt> 
</pre>

这里使用的参数指定程序（-p），线程数（-t 1）和中断周期，
中断周期是唤醒调度程序并运行以切换到其他任务的频率。 
因为在此示例中只有一个线程，所以此间隔无关紧要。

输出结果很容易阅读：模拟器打印程序计数器（此处显示从 1000 到 1003）和要执行的指令。
注意，我们（不切实际的）假设所有指令仅占用内存中的一个字节； 
但实际上,在 x86 中，指令是可变大小的，并且将至少占用一个字节。

我们可以使用更详细的跟踪来更好地了解机器在执行过程中的状态变化:

<pre>
prompt> ./x86.py -p simple-race.s -t 1 -M 2000 -R ax,bx

 2000      ax    bx          Thread 0
    ?       ?     ?
    ?       ?     ?   1000 mov 2000, %ax
    ?       ?     ?   1001 add $1, %ax
    ?       ?     ?   1002 mov %ax, 2000
    ?       ?     ?   1003 halt
</pre>

糟糕！ 忘记了 -c 参数（它为你计算答案）。

<pre>
prompt> ./x86.py -p simple-race.s -t 1 -M 2000 -R ax,bx -c

 2000      ax    bx          Thread 0
    0       0     0
    0       0     0   1000 mov 2000, %ax
    0       1     0   1001 add $1, %ax
    1       1     0   1002 mov %ax, 2000
    1       1     0   1003 halt
</pre>

通过使用 -M 标志，我们可以跟踪内存位置（用逗号分隔的列表可以让您跟踪多个地址，例如 2000,3000）； 
通过使用 -R 标志，我们可以跟踪指定寄存器中的值。

执行右边的指令后，左边的值显示内存/寄存器的内容。 
例如，在 "add" 指令之后，您可以看到%ax 已增加到 1； 
在第二条 "mov" 指令之后（在 PC = 1002 处），您可以看到现在 2000 处的内存的值也增加了。

您还需要了解一些其他说明，所以现在让我们开始吧。 这是循环的代码段：

```asm
.main
.top
sub  $1,%dx
test $0,%dx     
jgte .top         
halt
```

这里介绍了一些东西: 
首先是 “test” 指令。 该指令接受两个参数并进行比较； 
然后，它设置隐式的“条件代码”（condition codes,类似于 1 位寄存器），后续指令可以对其进行操作。

在本例中，另一条新指令是 “jump” 指令(在本例中，“jgte” 表示“大于或等于时跳转”)。
如果第二个值大于或等于 "test" 指令中的第一个值，则此指令跳转。

最后一点：要使此代码真正运行，必须将 dx 初始化为 1 或更大。

因此，我们像这样运行程序：

<pre>
prompt> ./x86.py -p loop.s -t 1 -a dx=3 -R dx -C -c

   dx   >= >  <= <  != ==        Thread 0
    3   0  0  0  0  0  0
    2   0  0  0  0  0  0  1000 sub  $1,%dx
    2   1  1  0  0  1  0  1001 test $0,%dx
    2   1  1  0  0  1  0  1002 jgte .top
    1   1  1  0  0  1  0  1000 sub  $1,%dx
    1   1  1  0  0  1  0  1001 test $0,%dx
    1   1  1  0  0  1  0  1002 jgte .top
    0   1  1  0  0  1  0  1000 sub  $1,%dx
    0   1  0  1  0  0  1  1001 test $0,%dx
    0   1  0  1  0  0  1  1002 jgte .top
   -1   1  0  1  0  0  1  1000 sub  $1,%dx
   -1   0  0  1  1  1  0  1001 test $0,%dx
   -1   0  0  1  1  1  0  1002 jgte .top
   -1   0  0  1  1  1  0  1003 halt
</pre>

"-R dx"标志跟踪%dx 的值； "-C"参数跟踪由"test"指令设置的条件代码的值。 
最后，"-a dx=3"参数将%dx 寄存器的值设置为 3。

从跟踪中可以看到，"sub"指令会缓慢减少%dx 的值。 
在前几次调用"test"时，仅设置了">="，">"和"!="条件。 
但是，跟踪中的最后一个"test"发现%dx 和 0 相等，因此随后的跳转不会发生，程序最终停止。

最后，我们进入一个更有趣的场景，即具有多个线程的竞争条件。 让我们先看一下代码：

```asm
.main
.top
# critical section
mov 2000, %ax       # get the value at the address
add $1, %ax         # increment it
mov %ax, 2000       # store it back

# see if we're still looping
sub  $1, %bx
test $0, %bx
jgt .top

halt
```

该代码有一个关键部分，该部分加载变量的值（在地址 2000 处），然后将该值加 1，最后将其存储回去。

在对循环计数器(以%bx 为单位)进行递减之后的代码，测试它是否大于或等于零，如果是，则再次跳到最上面的临界区。

<pre>

prompt> ./x86.py -p looping-race-nolock.s -t 2 -a bx=1 -M 2000 -c

 2000      bx          Thread 0                Thread 1
    0       1
    0       1   1000 mov 2000, %ax
    0       1   1001 add $1, %ax
    1       1   1002 mov %ax, 2000
    1       0   1003 sub  $1, %bx
    1       0   1004 test $0, %bx
    1       0   1005 jgt .top
    1       0   1006 halt
    1       1   ----- Halt;Switch -----  ----- Halt;Switch -----
    1       1                            1000 mov 2000, %ax
    1       1                            1001 add $1, %ax
    2       1                            1002 mov %ax, 2000
    2       0                            1003 sub  $1, %bx
    2       0                            1004 test $0, %bx
    2       0                            1005 jgt .top
    2       0                            1006 halt
</pre>

在这里，您可以看到每个线程运行了一次，并且每个线程都更新了地址 2000 处的共享变量，从而导致那里的计数为 2。

每当一个线程停止并且必须运行另一个线程时，插入"Halt;Switch"行。

最后一个例子：在上面执行相同的操作，但是中断频率较小。 如下所示：
<pre>
[mac Race-Analyze] ./x86.py -p looping-race-nolock.s -t 2 -a bx=1 -M 2000 -i 2

 2000          Thread 0                Thread 1
    ?
    ?   1000 mov 2000, %ax
    ?   1001 add $1, %ax
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?                            1000 mov 2000, %ax
    ?                            1001 add $1, %ax
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?   1002 mov %ax, 2000
    ?   1003 sub  $1, %bx
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?                            1002 mov %ax, 2000
    ?                            1003 sub  $1, %bx
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?   1004 test $0, %bx
    ?   1005 jgt .top
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?                            1004 test $0, %bx
    ?                            1005 jgt .top
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?   1006 halt
    ?   ----- Halt;Switch -----  ----- Halt;Switch -----
    ?                            1006 halt
</pre>

如您所见，我们通过"-i 2"参数指定每个线程每 2 条指令中断一次。 
在整个运行过程中，内存 \[2000\]的值是多少？ 应该是什么？

现在，让我们提供更多有关此程序可以模拟的信息。 
全部寄存器：%ax，%bx，%cx，%dx 和 PC。 
在此版本中，不支持"stack"，也没有调用和返回指令。

所有可以模拟的指令是

```asm
mov immediate, register     # 移动值立即值至寄存器
mov memory, register        #从内存加载到寄存器
mov register, register      # 将值从一个寄存器移动到另一个寄存器
mov register, memory        # 寄存器的值储存到内存中
mov immediate, memory       # 即时值存储到内存中
add immediate, register     # register  = register  + immediate
add register1, register2    # register2 = register2 + register1
sub immediate, register     # register  = register  - immediate
sub register1, register2    # register2 = register2 - register1

test immediate, register    # 比较立即值与寄存器 (set condition codes)
test register, immediate    # same but register and immediate
test register, register     # same but register and register

jne                         # 如果test指令的值不相等则跳转
je                          # 如果test指令的值相等则跳转
jlt                         # 如果test指令第二个参数小于第一个则跳转
jlte                        # 如果test指令第二个参数小于等于第一个则跳转          
jgt                         # 如果test指令第二个参数大于第一个则跳转    
jgte                        # 如果test指令第二个参数大于等于第一个则跳转   

xchg register, memory       # atomic exchange: 
                            #   put value of register into memory
                            #   return old contents of memory into reg
                            # do both things atomically

nop                         # no op
```

Notes: 
- 'immediate' 形如: $number
- 'memory' 形如 '数字' 或 '(寄存器)' 或 '数字(寄存器)' 或 '数字(寄存器,寄存器)' (如上面所描述的)
- '寄存器' 是 %ax, %bx, %cx, %dx 中的一个

最后，这是模拟器的所有选项，可-h 查看

<pre>

Usage: x86.py [options]

Options:
  -h, --help            显示帮助信息
  -s SEED, --seed=SEED  随机种子
  -t NUMTHREADS, --threads=NUMTHREADS
                        线程数
  -p PROGFILE, --program=PROGFILE
                        源程序 (in .s)
  -i INTFREQ, --interrupt=INTFREQ
                        中断周期
  -r, --randints        中断周期是否随机
  -a ARGV, --argv=ARGV  逗号分隔每个线程参数(例如: ax=1,ax=2 设置线程0 ax 寄存器为1,线程1 ax 寄存器为2)
                        通过冒号分隔列表为每个线程指定多个寄存器(例如，ax=1:bx=2,cx=3设 置线程0 ax和bx，对于线程1只设置cx)
  -L LOADADDR, --loadaddr=LOADADDR
                        加载代码的地址
  -m MEMSIZE, --memsize=MEMSIZE
                        地址空间大小(KB)
  -M MEMTRACE, --memtrace=MEMTRACE
                        以逗号分隔的要跟踪的地址列表 (例如:20000,20001)
  -R REGTRACE, --regtrace=REGTRACE
                        以逗号分隔的要跟踪的寄存器列表 (例如:ax,bx,cx,dx)
  -C, --cctrace         是否跟踪条件代码condition codes)
  -S, --printstats      打印额外信息
  -c, --compute         计算结果
</pre>

大多数参数是很容易理解的的。 使用-r 会打开一个随机周期中断器（从-i 指定为 1 到中断周期），这可以在家庭作业出现问题时带来更多乐趣。


<pre>

-L 指定在地址空间的何处加载代码。

-m 指定地址空间的大小（以KB为单位）。

-S 打印额外信息

-c is not really used (unlike most simulators in the book); use the tracing or condition codes.
</pre>
现在您已经具备了基础知识。 请阅读本章末尾的问题，以更深入地研究竞争情况和相关问题。


