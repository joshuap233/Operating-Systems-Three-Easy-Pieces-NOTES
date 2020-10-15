import random
import matplotlib.pyplot as plt
import numpy as np

# 本章假设地址空间很小,小于物理内存
# 且设定limit 与base register时, limit+base <= 物理内存大小
ADDR_SPACE = 1 * 1024  # 1K
PHY_MEM = 10 * 1024 * 1024  # 10M
BASE = 1024
limit = 0
a = [0.0] * ADDR_SPACE

while limit < ADDR_SPACE:
    effect = [random.randint(0, ADDR_SPACE) for i in range(1000) if i <= limit]
    a[limit] = len(effect) / 1000
    limit += 1

plt.plot(np.array(range(limit)), np.array(a))
plt.xlim(0, ADDR_SPACE)
plt.ylim(0, 1)

# plt.title(u'随着界限寄存器值增长, 生成虚拟地址有效的概率')
# plt.xlabel(u'生成虚拟地址有效的概率')
# plt.ylabel(u'界限寄存器大小')
plt.show()
