import random
import sys

numAddr = 10


# 空间局部性
def generate_spatial_locality_trace():
    trace = [random.randint(0, numAddr)]
    for i in range(8):
        l = trace[-1]
        rand = [l, (l + 1) % numAddr, (l - 1) % numAddr, random.randint(0, numAddr)]
        trace.append(random.choice(rand))
    # 问题给的paging-policy.py -a参数里, 逗号后不能空格,因此拼接再打印
    print(','.join([str(i) for i in trace]))


# 时间局部性
def generate_temporal_locality_trace():
    trace = [random.randint(0, numAddr)]
    for i in range(8):
        rand = [random.randint(0, numAddr), random.choice(trace)]
        trace.append(random.choice(rand))
    print(','.join([str(i) for i in trace]))


if len(sys.argv) != 1:
    if sys.argv[1] == '-t':
        generate_temporal_locality_trace()
    elif sys.argv[1] == '-s':
        generate_spatial_locality_trace()
