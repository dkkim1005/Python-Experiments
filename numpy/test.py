#!/usr/bin/python2.7
import numpy as np
from tester import scalar_dot

a = np.array([[1,2,3],[4,5,6]],dtype='float64')

print "before a:",a
scalar_dot(a,3)
print a
