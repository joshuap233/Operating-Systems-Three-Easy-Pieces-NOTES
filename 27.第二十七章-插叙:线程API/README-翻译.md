在本作业中，您将在 Linux 上使用一个真正的工具来查找多线程代码中的问题。 该工具称为`helgrind`（作为 valgrind 调试工具套件的一部分提供）。

有关该工具的详细信息，请参阅 http://valgrind.org/docs/manual/hg-manual.htm，包括如何下载和安装它(如果您的 Linux 系统上还没有它的话)。

*笔者注:如果你使用 Ubuntu,输入:  sudo apt install valgrind 安装*

然后，您将查看许多 多线程 C 程序，以了解如何使用该工具调试有问题的线程代码。

首先，首先要下载并安装 valgrind 和相关的`helgrind`工具。

然后，键入"make"以构建所有不同的程序。 检查 Makefile，以获取有关其工作原理的更多详细信息。

然后，您需要查看一些不同的 C 程序：

- main-race.c  一个简单的竞争条件
- main-deadlock.c 一个简单的死锁
- main-deadlock-global.c 死锁问题的解决方案
- main-signal.c 一个简单的子/父信号示例
- main-signal-cv.c 通过条件变量实现更有效的信号
- mythreads.h 头文件, 包装了部分线程 api, 使函数能检查错误并增加可读性

使用这些程序，你现在可以回答教科书中的问题了。




