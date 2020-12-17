import matplotlib.pyplot as plt
import os
import re

res = os.popen('make && ./main').read()
y = [float(r) for r in re.findall(r'\d\.\d*', res)]

plt.plot(range(1, 9), y)
plt.xlabel('cpu count')
plt.ylabel('time')
plt.xlim(1, 8)
plt.savefig('4.png', dpi=227)
plt.show()
