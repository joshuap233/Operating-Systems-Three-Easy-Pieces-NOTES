import os
import matplotlib.pyplot as plt


def compute(i: int, bx1: int = 2, bx2: int = 2):
    cmd = f"python2 x86.py -p test-and-set.s -a bx={bx1},bx={bx2} -M count -c -i {i} | wc -l"
    res = os.popen(cmd).read().strip("\n")
    line = int(res) - 19
    return line


y = []
x = range(1, 10 + 1)
for i in x:
    bx1 = 2
    bx2 = 2
    # 理论执行指令数 / 实际执行指令数
    # 简单的假设cpu执行每条指令的时钟周期相同,实际并不是这样
    rate = (11 * bx1 + 1 + 11 * bx2 + 1) / compute(i, bx1, bx2)
    y.append(rate)

plt.plot(list(x), y)
plt.xlim(1, 11)
plt.ylim(0, 1)
plt.savefig('5.png', dpi=227)
plt.show()
