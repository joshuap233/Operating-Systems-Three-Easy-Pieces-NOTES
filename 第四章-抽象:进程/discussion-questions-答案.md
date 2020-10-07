- 什么是寄存器，栈，堆，指令指针，堆栈指针？

> 寄存器（Register）是中央处理器内用来暂存指令、数据和地址的电脑存储器。寄存器的存贮容量有限，读写速度非常快。

> 栈是为执行线程预留的暂存空间(静态)。

> 堆是为动态分配预留的内存。

> IP――指令指针寄存器（Instruction Pointer），指示要执行指令所在存储单元的地址。IP寄存器是一个专用寄存器。

> SP――堆栈指针寄存器（Stack Pointer），指示堆栈区域的栈顶地址

- 什么是进程？
- - 他们代表什么?
- - 这是什么抽象的?
- - 抽象中包含了什么?

> 是指计算机中已运行的程序。

- 分时系统如何提供虚拟化?


- 就绪和运行状态有什么区别?

- 为什么您可能希望能够创建/销毁/暂停进程?

- 是否应该限制用户可以并发运行的进程数量?
- 
是,`ulimit -a |grep processes`查看LINUX系统最大进程数

- 为什么把机制和策略分开是个好主意?

> 你可以将机制看成为系统的"如何(how)"问题 提供答案. 例如,操作系统如何执行上下文切换,策略为哪个"(which)" 问题提供答案. 例如, 操作系统现在应该在运行哪个进程? 将连个分开可以轻松地改变策略, 而不必重新考虑机制

- 查看LINUX操作系统下PCB

```
❯ cat /proc/self/status
Name:	cat
Umask:	0002
State:	R (running)
Tgid:	46269
Ngid:	0
Pid:	46269
PPid:	45767
TracerPid:	0
Uid:	1000	1000	1000	1000
Gid:	1000	1000	1000	1000
FDSize:	64
Groups:	4 24 27 30 46 120 131 132 136 1000 
NStgid:	46269
NSpid:	46269
NSpgid:	46269
NSsid:	45767
VmPeak:	   11300 kB
VmSize:	   11300 kB
VmLck:	       0 kB
VmPin:	       0 kB
VmHWM:	     592 kB
VmRSS:	     592 kB
RssAnon:	      68 kB
RssFile:	     524 kB
RssShmem:	       0 kB
VmData:	     316 kB
VmStk:	     136 kB
VmExe:	      28 kB
VmLib:	    1640 kB
VmPTE:	      52 kB
VmSwap:	       0 kB
HugetlbPages:	       0 kB
CoreDumping:	0
THP_enabled:	1
Threads:	1
SigQ:	0/31120
SigPnd:	0000000000000000
ShdPnd:	0000000000000000
SigBlk:	0000000000000000
SigIgn:	0000000000000000
SigCgt:	0000000000000000
CapInh:	0000000000000000
CapPrm:	0000000000000000
CapEff:	0000000000000000
CapBnd:	0000003fffffffff
CapAmb:	0000000000000000
NoNewPrivs:	0
Seccomp:	0
Speculation_Store_Bypass:	thread vulnerable
Cpus_allowed:	ff
Cpus_allowed_list:	0-7
Mems_allowed:	00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000001
Mems_allowed_list:	0
voluntary_ctxt_switches:	0
nonvoluntary_ctxt_switches:	0

```