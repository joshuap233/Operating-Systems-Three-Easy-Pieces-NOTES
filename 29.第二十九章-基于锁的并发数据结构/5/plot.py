import matplotlib.pyplot as plt
import os
import re

res = os.popen('make && ./main').read()
all_ = [float(r) for r in re.findall(r'\d\.\d*', res)]

plt.plot(range(1, 9), all_)
plt.xlim(1, 8)

plt.legend()
plt.xlabel('cpu count')
plt.ylabel('time')
plt.savefig('5.png', dpi=227)
plt.show()
