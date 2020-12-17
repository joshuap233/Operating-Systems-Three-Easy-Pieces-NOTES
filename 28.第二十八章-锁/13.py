import os
import matplotlib.pyplot as plt


def compute(t: int = 3, bx: int = 1000):
    cmd = f"python2 x86.py -p ticket.s -a bx={bx} -c -M count -t {t} | wc -l"
    res = os.popen(cmd).read().strip("\n")
    line = int(res) - 19
    return line


y = []
x = range(1, 5 + 1)
for threadN in x:
    bx = 1000
    # 理论执行指令数 / 实际执行指令数
    rate = ((14 * bx + 2) * threadN) / compute(threadN, bx)
    y.append(rate)

plt.plot(list(x), y)
plt.xlim(1, 6)
plt.ylim(0, 1)
plt.savefig('13.png', dpi=227)
plt.show()
