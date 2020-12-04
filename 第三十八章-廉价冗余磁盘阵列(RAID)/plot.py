import matplotlib.pyplot as plt
import os
import re
import sys

args = sys.argv
img_name = 'plot.jpg'
for k in args:
    if k == '-p':
        index = args.index(k)
        args.pop(index)
        img_name = args.pop(index)
        break

params = " ".join(sys.argv[1:])

for level in [0, 1, 4, 5]:
    ts = []
    for disk in range(4, 100, 2):
        res = os.popen(f'python2 raid.py -L {level} -t -n 100 -c -D {disk} {params}').read()
        time = re.findall(r'STAT totalTime (\d*)', res)
        ts.append(int(time[0]))

    plt.plot(range(4, 100, 2), ts, label=f'level {level}')

plt.legend()
plt.xlabel('disk number')
plt.ylabel('time')
plt.savefig(img_name)
plt.show()
