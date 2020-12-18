Homework (Code)
In this section, we’ll write some simple communication code to get
you familiar with the task of doing so. Have fun!
Questions
<br/>
<br/>

1. Using the code provided in the chapter, build a simple UDP-based
server and client. The server should receive messages from the
client, and reply with an acknowledgment. In this first attempt,
do not add any retransmission or robustness (assume that communication works perfectly). Run this on a single machine for testing;
later, run it on two different machines.
<br/>
<br/>

2. Turn your code into a communication library. Specifically, make
your own API, with send and receive calls, as well as other API
calls as needed. Rewrite your client and server to use your library
instead of raw socket calls.
<br/>
<br/>

3. Add reliable communication to your burgeoning communication library, in the form of timeout/retry. Specifically, your library should
make a copy of any message that it is going to send. When sending
it, it should start a timer, so it can track how long it has been since
the message was sent. On the receiver, the library should acknowledge received messages. The client send should block when sending, i.e., it should wait until the message has been acknowledged
before returning. It should also be willing to retry sending indefinitely. The maximum message size should be that of the largest
single message you can send with UDP. Finally, be sure to perform
timeout/retry efficiently by putting the caller to sleep until either
an ack arrives or the transmission times out; do not spin and waste
the CPU!
<br/>
<br/>

4. Make your library more efficient and feature-filled. First, add verylarge message transfer. Specifically, although the network limit maximum message size, your library should take a message of arbitrarily large size and transfer it from client to server. The client should
transmit these large messages in pieces to the server; the server-side
library code should assemble received fragments into the contiguous whole, and pass the single large buffer to the waiting server
code.
<br/>
<br/>

5. Do the above again, but with high performance. Instead of sending
each fragment one at a time, you should rapidly send many pieces,
thus allowing the network to be much more highly utilized. To do
so, carefully mark each piece of the transfer so that the re-assembly
on the receiver side does not scramble the message.
<br/>
<br/>

6. A final implementation challenge: asynchronous message send with
in-order delivery. That is, the client should be able to repeatedly call
send to send one message after the other; the receiver should call receive and get each message in order, reliably; many messages from
the sender should be able to be in flight concurrently. Also add a
sender-side call that enables a client to wait for all outstanding messages to be acknowledged.
<br/>
<br/>

7. Now, one more pain point: measurement. Measure the bandwidth
of each of your approaches; how much data can you transfer between two different machines, at what rate? Also measure latency:
for single packet send and acknowledgment, how quickly does it
finish? Finally, do your numbers look reasonable? What did you
expect? How can you better set your expectations so as to know if
there is a problem, or that your code is working well?