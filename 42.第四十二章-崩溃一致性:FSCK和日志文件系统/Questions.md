Homework (Simulation)
This section introduces fsck.py, a simple simulator you can use to
better understand how file system corruptions can be detected (and potentially repaired). Please see the associated README for details on how
to run the simulator.
Questions
<br/>
<br/>

1. First, run fsck.py -D; this flag turns off any corruption, and thus
you can use it to generate a random file system, and see if you can
determine which files and directories are in there. So, go ahead and
do that! Use the -p flag to see if you were right. Try this for a few
different randomly-generated file systems by setting the seed (-s)
to different values, like 1, 2, and 3.
<br/>
<br/>

2. Now, let’s introduce a corruption. Run fsck.py -S 1 to start.
Can you see what inconsistency is introduced? How would you fix
it in a real file system repair tool? Use -c to check if you were right.
<br/>
<br/>

3. Change the seed to -S 3 or -S 19; which inconsistency do you
see? Use -c to check your answer. What is different in these two
cases?
<br/>
<br/>

4. Change the seed to -S 5; which inconsistency do you see? How
hard would it be to fix this problem in an automatic way? Use -c to
check your answer. Then, introduce a similar inconsistency with -S
38; is this harder/possible to detect? Finally, use -S 642; is this
inconsistency detectable? If so, how would you fix the file system?
<br/>
<br/>

5. Change the seed to -S 6 or -S 13; which inconsistency do you
see? Use -c to check your answer. What is the difference across
these two cases? What should the repair tool do when encountering
such a situation?
<br/>
<br/>

6. Change the seed to -S 9; which inconsistency do you see? Use -c
to check your answer. Which piece of information should a checkand-repair tool trust in this case?
<br/>
<br/>

7. Change the seed to -S 15; which inconsistency do you see? Use
-c to check your answer. What can a repair tool do in this case? If
no repair is possible, how much data is lost?
<br/>
<br/>

8. Change the seed to -S 10; which inconsistency do you see? Use
-c to check your answer. Is there redundancy in the file system
structure here that can help a repair?
<br/>
<br/>

9. Change the seed to -S 16 and -S 20; which inconsistency do you
see? Use -c to check your answer. How should the repair tool fix
the problem?