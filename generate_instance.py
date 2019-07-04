import sys

import numpy as np
import numpy.random as rnd

if len(sys.argv) != 3:
    print "Usage ./%s size maxn"
    exit(1)

instance_size = int(sys.argv[1]) #1000
instance_maxn = int(sys.argv[2]) #50000
instance_minn = instance_maxn / instance_size
instance_name = sys.argv[1] 
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

    f = open(instance_name + ".in", "w")
    f.write(str(len(numbers)))
    f.write("\n")
    f.write(" ".join(map(str, numbers)))
    f.close()
    
    f = open(instance_name + ".ans", "w")
    f.write(str(len(pA)) + "\n")
    f.write(" ".join(map(str, pA)) + "\n")
    f.write(str(len(pB)) + "\n")
    f.write(" ".join(map(str, pB)) + "\n")
    f.close()
else:
    print("bad instance %d != %d" % (sumAB, maxn))


