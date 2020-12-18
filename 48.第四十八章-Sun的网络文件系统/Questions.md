Homework (Measurement)
In this homework, you’ll do a little bit of NFS trace analysis using real
traces. The source of these traces is Ellard and Seltzer’s effort [ES03].
Make sure to read the related README and download the relevant tarball from the OSTEP homework page (as usual) before starting.
Questions
<br/>
<br/>

1. A first question for your trace analysis: using the timestamps found
in the first column, determine the period of time the traces were
taken from. How long is the period? What day/week/month/year
was it? (does this match the hint given in the file name?) Hint: Use
the tools head -1 and tail -1 to extract the first and last lines of
the file, and do the calculation.
<br/>
<br/>

2. Now, let’s do some operation counts. How many of each type of operation occur in the trace? Sort these by frequency; which operation
is most frequent? Does NFS live up to its reputation?
<br/>
<br/>

3. Now let’s look at some particular operations in more detail. For
example, the GETATTR request returns a lot of information about
files, including which user ID the request is being performed for,
the size of the file, and so forth. Make a distribution of file sizes
accessed within the trace; what is the average file size? Also, how
many different users access files in the trace? Do a few users dominate traffic, or is it more spread out? What other interesting information is found within GETATTR replies?
<br/>
<br/>

4. You can also look at requests to a given file and determine how
files are being accessed. For example, is a given file being read or
written sequentially? Or randomly? Look at the details of READ
and WRITE requests/replies to compute the answer.
<br/>
<br/>

5. Traffic comes from many machines and goes to one server (in this
trace). Compute a traffic matrix, which shows how many different
clients there are in the trace, and how many requests/replies go to
each. Do a few machines dominate, or is it more evenly balanced?
<br/>
<br/>

6. The timing information, and the per-request/reply unique ID, should
allow you to compute the latency for a given request. Compute the
latencies of all request/reply pairs, and plot them as a distribution.
What is the average? Maximum? Minimum?
<br/>
<br/>

7. Sometimes requests are retried, as the request or its reply could be
lost or dropped. Can you find any evidence of such retrying in the
trace sample?
<br/>
<br/>

8. There are many other questions you could answer through more
analysis. What questions do you think are important? Suggest
them to us, and perhaps we’ll add them here