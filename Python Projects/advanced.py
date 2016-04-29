# -*- coding: utf-8 -*-
"""
Created on Wed Nov 04 22:47:45 2015

@author: Michael
"""
import matplotlib.pyplot as plt
import numpy as np
from numpy import sin, pi, arange

constant = []
x = arange(0.0, 1.01, 0.01)
x2 = arange(0, 11, 1)
x3 = arange(0, 10001, 1)
for const in range(0, 10001):
    constant.append(3)

#plotting sin for fun
plt.plot(x, sin(2*pi*x), '--')

#plotting some standard big(0)
#plt.plot(x2, x2*x2, 'b', label = 'n^2') 
#plt.plot(x2, x2*np.log(x2), 'r', label = 'nlog(n)')
#plt.plot(x2, [3,3,3,3,3,3,3,3,3,3,3], 'g', label = 'C')

#plotting big(0) with selective data sizes.
#plt.plot(x3, x3*x3, 'b', label = 'n^2', lw = 2.0) 
#plt.plot(x3, x3*np.log(x3), 'r', label = 'nlog(n)', lw = 2.0)
#plt.plot(x3, constant, 'g', label = 'C', lw = 2.0)
#plt.axis([0, 10000, 0, 100000])

plt.ylabel("y axis")
plt.xlabel("x axis")
plt.legend()
plt.show()
