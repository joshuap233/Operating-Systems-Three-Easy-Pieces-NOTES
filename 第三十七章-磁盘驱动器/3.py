import os
import re


def get_time(ss, a):
    r = []
    for S in ss:
        res = os.popen(f'python2 disk.py  -a {a} -c -R {S} ').read()
        time = re.findall(r'TOTALS.*Total:[ ]?(\d*)\n', res)[0]
        r.append(time)
    print(r)


for a in ['0', '30', '7,30,8', '10,11,12,13']:
    get_time([0.1, 0.5, 0.01], a)
