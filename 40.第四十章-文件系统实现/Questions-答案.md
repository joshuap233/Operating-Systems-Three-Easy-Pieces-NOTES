作业:

使用工具 vsfs.py 来研究文件系统状态如何随着各种操作的发生而改变。文件系统以空
状态开始，只有一个根目录。模拟发生时会执行各种操作，从而慢慢改变文件系统的磁
盘状态。详情请参阅 README 文件

问题:

<br/>
<br/>

1.用一些不同的随机种子（比如 17、18、19、20）运行模拟器，看看你是否能确定每
次状态变化之间一定发生了哪些操作。

```shell script
python2 vsfs.py -n 6 -s 17
python2 vsfs.py -n 6 -s 18
python2 vsfs.py -n 6 -s 19
python2 vsfs.py -n 6 -s 20
```


<pre>
❯ python2 vsfs.py -n 6 -s 17
Initial state

inode bitmap  10000000
inodes        [d a:0 r:2] [] [] [] [] [] [] [] 
data bitmap   10000000
data          [(.,0) (..,0)] [] [] [] [] [] [] [] 

Which operation took place?

# mkdir('/u'); 

inode bitmap  11000000
inodes        [d a:0 r:3] [d a:1 r:2] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (u,1)] [(.,1) (..,0)] [] [] [] [] [] [] 

Which operation took place?

# create('/a')

inode bitmap  11100000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:-1 r:1] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (u,1) (a,2)] [(.,1) (..,0)] [] [] [] [] [] [] 

Which operation took place?

# unlink('/a')

inode bitmap  11000000
inodes        [d a:0 r:3] [d a:1 r:2] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (u,1)] [(.,1) (..,0)] [] [] [] [] [] [] 

Which operation took place?

# mkdir('/z')

inode bitmap  11100000
inodes        [d a:0 r:4] [d a:1 r:2] [d a:2 r:2] [] [] [] [] [] 
data bitmap   11100000
data          [(.,0) (..,0) (u,1) (z,2)] [(.,1) (..,0)] [(.,2) (..,0)] [] [] [] [] [] 

Which operation took place?

# mkdir('/s')

inode bitmap  11110000
inodes        [d a:0 r:5] [d a:1 r:2] [d a:2 r:2] [d a:3 r:2] [] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (u,1) (z,2) (s,3)] [(.,1) (..,0)] [(.,2) (..,0)] [(.,3) (..,0)] [] [] [] [] 

Which operation took place?

# create('/z/x')

inode bitmap  11111000
inodes        [d a:0 r:5] [d a:1 r:2] [d a:2 r:2] [d a:3 r:2] [f a:-1 r:1] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (u,1) (z,2) (s,3)] [(.,1) (..,0)] [(.,2) (..,0) (x,4)] [(.,3) (..,0)] [] [] [] [] 
</pre>

<br/>
<br/>

2.现在使用不同的随机种子（比如 21、22、23、24），但使用 -r 标志运行，这样做可
以让你在显示操作时猜测状态的变化。关于 inode 和数据块分配算法，根据它们喜欢分配的
块，你可以得出什么结论？

<pre>
❯ python2 vsfs.py -s 21 -r
Initial state

inode bitmap  10000000
inodes        [d a:0 r:2] [] [] [] [] [] [] [] 
data bitmap   10000000
data          [(.,0) (..,0)] [] [] [] [] [] [] [] 

mkdir("/o");

  State of file system (inode bitmap, inodes, data bitmap, data)?

inode bitmap  11000000
inodes        [d a:0 r:3] [d a:1 r:2] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (o,1)] [(.,1) (..,0)] [] [] [] [] [] [] 

creat("/b");

  State of file system (inode bitmap, inodes, data bitmap, data)?

inode bitmap  11100000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:-1 r:1] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0)] [] [] [] [] [] [] 

creat("/o/q");

  State of file system (inode bitmap, inodes, data bitmap, data)?

inode bitmap  11110000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:-1 r:1] [f a:-1 r:1] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0) (q,3)] [] [] [] [] [] [] 


fd=open("/b", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);

  State of file system (inode bitmap, inodes, data bitmap, data)?

inode bitmap  11110000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:2 r:1] [f a:-1 r:1] [] [] [] [] 
data bitmap   11100000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0) (q,3)] [b] [] [] [] [] [] 


fd=open("/o/q", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);

  State of file system (inode bitmap, inodes, data bitmap, data)?

inode bitmap  11110000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:2 r:1] [f a:3 r:1] [] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0) (q,3)] [b] [q] [] [] [] [] 


creat("/o/j");

  State of file system (inode bitmap, inodes, data bitmap, data)?

inode bitmap  11111000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:2 r:1] [f a:3 r:1] [f a:-1 r:1] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0) (q,3) (j,4)] [b] [q] [] [] [] [] 

unlink("/b");

  State of file system (inode bitmap, inodes, data bitmap, data)?

inode bitmap  11011000
inodes        [d a:0 r:3] [d a:1 r:2] [] [f a:3 r:1] [f a:-1 r:1] [] [] [] 
data bitmap   11010000
data          [(.,0) (..,0) (o,1)] [(.,1) (..,0) (q,3) (j,4)] [] [q] [] [] [] [] 

fd=open("/o/j", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);

  State of file system (inode bitmap, inodes, data bitmap, data)?

inode bitmap  11011000
inodes        [d a:0 r:3] [d a:1 r:2] [] [f a:3 r:1] [f a:2 r:1] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (o,1)] [(.,1) (..,0) (q,3) (j,4)] [j] [q] [] [] [] [] 

creat("/o/x");

  State of file system (inode bitmap, inodes, data bitmap, data)?

inode bitmap  11111000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:-1 r:1] [f a:3 r:1] [f a:2 r:1] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (o,1)] [(.,1) (..,0) (q,3) (j,4) (x,2)] [j] [q] [] [] [] [] 

mkdir("/o/t");

  State of file system (inode bitmap, inodes, data bitmap, data)?

inode bitmap  11111100
inodes        [d a:0 r:3] [d a:1 r:3] [f a:-1 r:1] [f a:3 r:1] [f a:2 r:1] [d a:4 r:2] [] [] 
data bitmap   11111000
data          [(.,0) (..,0) (o,1)] [(.,1) (..,0) (q,3) (j,4) (x,2) (t,5)] [j] [q] [(.,5) (..,1)] [] [] [] 

</pre>

    使用最近可分配 inode 与数据块plainplainplainplainplain

<br/>
<br/>

3.现在将文件系统中的数据块数量减少到非常少（比如两个），并用 100 个左右的请
求来运行模拟器。在这种高度约束的布局中，哪些类型的文件最终会出现在文件系统中？
什么类型的操作会失败？

```shell script
python2 vsfs.py -d 2 -c -n 100 -p
```
    
    不知道模拟器好像有点问题还是 vsfs 设计问题,最后一个数据块不能使用plainplainplainplainplainplainplainplainplain
    create 操作不会失败,create 操作不会添加数据块
    
<br/>
<br/>

4.现在做同样的事情，但针对 inodes。只有非常少的 inode，什么类型的操作才能成功？
哪些通常会失败？文件系统的最终状态可能是什么？

```shell script
python2 vsfs.py -i 2 -c -n 100 -p
```
    
    mkdir,create 都会失败,会使用 inodeplainplainplainplainplainplain