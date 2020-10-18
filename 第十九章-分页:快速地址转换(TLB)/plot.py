import matplotlib.pyplot as plt
import re


x = []
y = []
with open('./out.txt') as f:
    for line in f:
        time, page = re.findall(r'time: (\d*).*?page: (\d*)', line)[0]
        x.append(page)
        y.append(time)

plt.plot(x, y)
plt.xlabel(u'number of pages')
plt.ylabel(u'time per access')
plt.show()
