import os
from collections import Counter

m = Counter()

for i in range(int(1e4)):
    with os.popen('./subexp-4', mode='r') as res:
        out = res.read(3)
        m[out] += 1
        if i % 20 == 0:
            print(f'\r round {i}', end='')
print()
print(m)