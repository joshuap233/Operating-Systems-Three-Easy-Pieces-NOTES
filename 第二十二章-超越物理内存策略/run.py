import re
import os

import matplotlib.pyplot as plt
import numpy as np

# 页号
with open('./test.txt') as f:
    # 只读取1000行
    lines = (f.readline() for i in range(1000))
    res = []
    for line in lines:
        addr = re.findall(r" ([\dabcdef]*),", line)
        if len(addr) == 1:
            bit_length = int(addr[0], 16).bit_length()
            page = int(addr[0], 16) >> (39 - (48 - bit_length))
            res.append(page)
    addr_list = ','.join([str(page) for page in res])


def computer_answer(cacheSize=1, policy='FIFO'):
    output = os.popen(f'python2 paging-policy.py -p {policy}  -C {cacheSize} -c -a  {addr_list}')
    out = output.read().split('\n')
    index = -1
    while out[index] == '':
        index -= 1

    out = re.findall(r'\b(\d+)\b.*\b(\d+)\b.*\b(\d+\.\d+)$', out[index])
    return out[0]


# 生成图

policies = ['FIFO', 'LRU', 'OPT', 'UNOPT', 'RAND', 'CLOCK']

plot = []

cacheSize = 10
for policy in policies:
    hitRates = [0.00] * cacheSize
    for i in range(1, cacheSize + 1):
        h, m, hitRate = computer_answer(i, policy)
        hitRates[i - 1] = hitRate
    plot.extend([np.array(range(cacheSize)), np.array(hitRates)])

plt.plot(*plot)
plt.xlim(1, cacheSize)

plt.legend(policies)
plt.xlabel(u'cache size(page)')
plt.ylabel(u'hit rate')
plt.show()
