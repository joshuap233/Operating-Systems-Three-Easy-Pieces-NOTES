通过本作业，您可以尝试多种方法使用 C 中实现小的无死锁 vector 对象。vector 对象的作用非常有限
（例如，它仅具有 add() 和 init() 函数），仅用于 说明了避免死锁的不同方法。

您应注意的一些文件如下。 特别是，本作业中的所有版本的代码都使用它们。

- mythreads.h
  封装了一些常用的库，比如 pthread 库，以确保它们不会执行失败后没有任何提醒
  
- vector-header.h
  简单头的文件，包括向量大小，以及向量结构体（vector_t）
  
- main-header.h
  不同程序共有的全局变量

- main-common.c
  包含 main() 函数（带有命令行参数解析），用于初始化两个 vectors，启动一些线程来访问它们
  （通过调用 worker() 函数），然后等待 vector_add() 调用完成  
 
在下面的文件中找到本次作业的不同版本。 每种版本都采用不同的方法来处理向量加法（ vector_add() ）中的并发。 
检查这些文件中的代码以了解发生了什么。 他们都使用上面列出的文件来制作一个完整的可运行程序。

- vector-deadlock.c
  该版本巧妙地以特定顺序（先抢占 v_dst 的锁然后抢占 v_src 的锁）抢夺锁。它会创建 “invitation to deadlock”，
  因为一个线程可能调用 vector_add(v1，v2)，而另一个线程同时调用 vector_add(v2，v1)。
  
- vector-global-order.c
  这个版本的 vector_add() 根据向量的地址的大小获取锁。

- vector-try-wait.c
  这个版本的 vector_add() 使用 pthread_mutex_trylock（）尝试获取锁； 
  当尝试失败时，代码将释放它可能持有的所有锁，然后返回顶部，然后再次尝试。
  
- vector-avoid-hold-and-wait.c
  这个版本的 vector_add() 通过在锁获取周围使用单个锁来确保它不会一直阻塞在持有锁并等待其他锁的模式中。
  
- vector-nolock.c
  这个版本的 vector_add() 不使用锁。 相反，它使用原子的 fetch-and-add 来实现 vector_add() 例程。 
  其语义（结果）略有不同。
  

输入 "make" (读取 Makefile 文件) 来构建五个可执行文件 

```shell script
prompt> make
```

然后您只需输入名称即可运行程序：

```shell script
prompt> ./vector-deadlock
```

每个程序都使用相同的参数集（有关详细信息，请参见 main-common.c ）：

<pre>
-d                 
   该标志打开线程死锁的功能。 当您将 -d 传递给程序时，每个其他线程以不同的顺序调用 vector_add()，
   例如，两个线程启用了 -d，线程 0 调用 vector_add(v1，v2)，线程 1 调用 vector_add(v2，v1)
   
-p
   该标志为每个线程提供了一组不同的 vectors 来调用 add()，而不仅仅是两个 vectors。 
   使用它来查看没有竞争同一组 vectors 的锁的情况如何。
   

-n num_threads
   创建 num_threads 个线程; you need more than one to deadlock.

-l loops
   每个线程调用 vector_add() 的次数?

-v 
   Verbose 标志:打印出更多关于正在发生的事情的信息。

-t
   打开计时器，并显示每件事所花费的时间。

</pre>