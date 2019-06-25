import sys

import numpy as np
import numpy.random as rnd

instance_size = int(sys.argv[1]) #1000
instance_maxn = int(sys.argv[2]) #50000
instance_minn = instance_maxn / instance_size

pA = []
pB = []

maxn = rnd.randint(low=(instance_maxn - instance_minn), high=instance_maxn)

A = B = maxn / 2

if maxn % 2 != 0:
    B += 1

k = rnd.randint(low=1, high=instance_minn)

while (A - k) > 0:
    pA.append(k)
    A -= k
    k = rnd.randint(low=1, high=instance_minn)

pA.append(A)

while (B - k) > 0:
    pB.append(k)
    B -= k
    k = rnd.randint(low=1, high=instance_minn)

pB.append(B)
sumAB = sum(pA) + sum(pB)
numbers = pA + pB 

numbers = filter(lambda x: x > 0, numbers)
rnd.shuffle(numbers)

if sumAB  == maxn:
    print(len(numbers))
    print(" ".join(map(str, numbers)))
else:
    print("bad instance %d != %d" % (sumAB, maxn))


