课后作业（编码）
通过该作业，您可以查看一些实际的代码，这些代码会发生死锁（或避免死锁）。
在简单的 vector_add() 函数中，不同版本的代码对应不同的避免死锁的方法。 
有关这些程序及其常用基础的详细信息，请参见 README。

问题：

<br/>
<br/>

1.首先，先了解程序的总体运行方式以及一些关键选项。 研究 vector-deadlock.c，main-common.c 和相关文件中的代码。
现在运行 `./vector-deadlock -n 2 -l 1 -v`，它指定运行两个线程（-n 2），每个线程执行一次 vector_add （-l 1），
并以详细模式（-v）执行 。 确保你能理解输出。 输出在程序运行时如何变化？

结果：
<pre>
❯ ./vector-deadlock -n 2 -l 1 -v
->add(0, 1)
<-add(0, 1)
              ->add(0, 1)
              <-add(0, 1)
</pre>

源码部分：
```c
//mina-common.c
void *worker(void *arg) {
        //...
        print_info(0, args->tid, v0, v1);
        vector_add(&v[v0], &v[v1]);
        print_info(1, args->tid, v0, v1);
        //..
}
void print_info(int call_return, int thread_id, int v0, int v1) {
    //...
    for (j = 0; j < thread_id; j++) printf("              ");
    if (call_return)
        printf("<-add(%d, %d)\n", v0, v1);
    else
        printf("->add(%d, %d)\n", v0, v1);
    //...
}

//vector-deadlock.c
void vector_add(vector_t *v_dst, vector_t *v_src) {
    // lock v_dst->lock & lock v_src->lock
    for (int i = 0; i < VECTOR_SIZE; i++) {
        v_dst->values[i] = v_dst->values[i] + v_src->values[i];
    }
    // unlock
}
```
vector_add 函数将 dst 与 src 的值相加，存入 dst 中，相加时获取锁，先获取 v_dst->lock 锁，再获取 v_src->lock 锁

worker 为线程目标函数，调用 `vector_add` ，调用前 打印`printf("->add(%d, %d)\n", v0, v1);` 
,调用后打印 `printf("<-add(%d, %d)\n", v0, v1);` 

线程数从 -n 参数读入，依次编号，例如 -n 3，则 tid 分别为 0,1,2，且 worker 函数调用 print_info 打印时，
会先打印 
<pre>tid × “              ”</pre> 
个空格


理论上有两种输出结果：
<pre>
#线程 0 调用在前
->add(0, 1)
<-add(0, 1)
              ->add(0, 1)
              <-add(0, 1)
# 或线程 0 调用在后:
              ->add(0, 1)
              <-add(0, 1)
->add(0, 1)
<-add(0, 1)
</pre>

看不怎么办？那就多调用几次，比如调用 50 次，总能看到:
```shell script
for i in {1..50}                            
do
./vector-deadlock -n 2 -l 1 -v
done  
```


<br/>
<br/>

2.现在添加 -d 标志，并将循环次数（-l）从 1 更改为更高的数字。会发生什么？ 代码（总是）会死锁吗？

有概率发生死锁，但不总是

多调用几次，总能找到死锁的时候：
```shell script
for i in {1..50}
do
 ./vector-deadlock -d -n 2 -l 10000 -v
done
```

    死锁分析:plainplainplainplainplain
    线程 1:
    调用：vector_add(v1,v2)，获取 v1 的锁，切换到线程 2
    线程 2:
    调用：vector_add(v2,v1)，获取 v2 的锁，然后尝试获取 v1 的锁，最终循环等待造成死锁


<br/>
<br/>

3.更改线程数（-n），程序的运行结果会发生什么变化？ 是否有 -n 的值可确保不发生死锁？

    死锁概率变大， -n 0 、-n 1 不会发生死锁plainplainplainplain

<br/>
<br/>

4.现在查看 `vector-global-order.c` 中的代码。 首先，请确保您理解代码的执行过程； 
您理解为什么代码能避免死锁吗？ 另外，当源和目标 vectors 相同时，为什么在这个 vector_add（）中有特殊情况发生？

    代码按照锁的地址大小获取锁，所有线程获取锁的顺序相同，因此不会发生上面的锁的调用顺序问题而造成死锁（见书 p284）plainplainplainplainplainplain
    当 vectors 相同时，锁只能获取一次

<br/>
<br/>

5.现在，运行带有以下参数的代码：`-t -n 2 -l 100000 -d`。 
代码需要多长时间才能运行完成？ 当您增加循环数或线程数时，总时间如何变化？
    
<pre>
❯ ./vector-global-order -t -n 2 -l 100000 -d
Time: 0.05 seconds

❯ ./vector-global-order -t -n 2 -l 200000 -d
Time: 0.09 seconds

❯ ./vector-global-order -t -n 4 -l 100000 -d
Time: 0.25 seconds
</pre>
    
<br/>
<br/>

6.如果打开并行标志（-p），会发生什么？ 当每个线程修改不同的 vectors（-p 启用）而不是在相同的 vectors 上运行时，您期望性能变化多少？

<pre>
❯ ./vector-global-order -t -n 2 -l 100000 -d -p
Time: 0.03 seconds

❯ ./vector-global-order -t -n 2 -l 200000 -d -p
Time: 0.03 seconds

❯ ./vector-global-order -t -n 4 -l 100000 -d -p
Time: 0.04 seconds
</pre>

多线程不需要竞争等待锁

<br/>
<br/>

7.现在我们研究 `vector-try-wait.c`。 首先确保您理解代码。 第一个对互斥锁 trylock() 的调用有必要吗？ 
现在运行代码。 global-order 方法相比，它运行速度有多快？ retry 变量大小（记录 trylock 尝试次数）如何随着线程数的增加而变化？

    这种方法有小概率造成活锁plainplainplain
    可以将第一个try_lock 替换为 Pthread_mutex_lock()，不会造成死锁
    
<pre>
❯ ./vector-try-wait -t -n 2 -l 100000 -d -p
Retries: 0
Time: 0.02 seconds

❯ ./vector-try-wait  -t -n 2 -l 200000 -d -p
Retries: 0
Time: 0.03 seconds

❯ ./vector-try-wait -t -n 4 -l 100000 -d -p
Retries: 0
Time: 0.03 seconds
</pre>
 
<br/>
<br/>

8.现在让我们看一下`vector-avoid-hold-and-wait.c`。 这种方法的主要问题是什么？ 
在使用 -p 和不使用 -p 的情况下，其性能与其他版本相比如何？

    锁太多，影响性能plainplain

<pre>
❯ ./vector-avoid-hold-and-wait -t -n 2 -l 100000 -d
Time: 0.18 seconds

❯ ./vector-avoid-hold-and-wait   -t -n 2 -l 200000 -d
Time: 0.41 seconds

❯ ./vector-avoid-hold-and-wait -t -n 4 -l 100000 -d
Time: 0.40 seconds

❯ ./vector-avoid-hold-and-wait -t -n 2 -l 100000 -d -p
Time: 0.06 seconds

❯ ./vector-avoid-hold-and-wait   -t -n 2 -l 200000 -d -p
Time: 0.07 seconds

❯ ./vector-avoid-hold-and-wait -t -n 4 -l 100000 -d -p
Time: 0.07 seconds
</pre>

<br/>
<br/>

9.最后，让我们看一下 `vector-nolock.c`。 这个版本根本不使用锁； 它提供与其他版本完全相同的语义吗？ 为什么或者为什么不？

    使用 fetch_and_add 原语

<br/>
<br/>

10.当线程在相同的两个 vectors 上运行时（没有 -p 参数），以及每个线程在单独的 vectors 上工作时（-p），
与其他版本进行比较。无锁版本的性能如何？

<pre>
❯ ./vector-nolock -t -n 2 -l 100000 -d
Time: 0.35 seconds

❯ ./vector-nolock  -t -n 2 -l 200000 -d
Time: 0.77 seconds

❯ ./vector-nolock   -t -n 4 -l 100000 -d
Time: 0.65 seconds

❯ ./vector-nolock -t -n 2 -l 100000 -d -p
Time: 0.05 seconds

❯ ./vector-nolock  -t -n 2 -l 200000 -d -p
Time: 0.10 seconds

❯ ./vector-nolock   -t -n 4 -l 100000 -d -p
Time: 0.09 seconds
</pre>