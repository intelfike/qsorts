def qsort(data):
    L, R = qset(data)
    if len(L) > 1: L = qsort(L)
    if len(R) > 1: R = qsort(R)
    return L + R
def qset(data):
    start, end = 0, len(data) - 1
    center = (data[start] + data[end]) >> 1
    while True:
        while data[start] <= center:
            if start >= end: return data[:start], data[start:]
            start += 1
        while data[end] > center:
            if start >= end: return data[:start], data[start:]
            end -= 1
        data[start],data[end] = data[end],data[start]
    return data[:start], data[start:]
    

# 利用
import random
d = []
n = 0
while n < 2000000:
    d.append(random.randint(0, 2000000))
    n += 1
import time
s = time.time()
print(qsort(d)[:20])
print(time.time() - s)