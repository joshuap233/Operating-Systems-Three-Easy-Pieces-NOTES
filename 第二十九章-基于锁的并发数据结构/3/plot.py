import matplotlib.pyplot as plt
import os
import re

res = os.popen('make && ./main').read()
all_ = [float(r) for r in re.findall(r'\d\.\d*', res)]

threshold = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024]
while all_:
    y, all_ = all_[:8], all_[8:]

    plt.plot(range(1, 9), y, label=f'threshold: {threshold[0]}')
    plt.xlim(1, 8)
    threshold = threshold[1:]

plt.legend()
plt.xlabel('cpu count')
plt.ylabel('time')
plt.savefig('4.png', dpi=227)
plt.show()
