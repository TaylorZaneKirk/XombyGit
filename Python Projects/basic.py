# -*- coding: utf-8 -*-
"""
Created on Wed Nov 04 22:08:35 2015

@author: Michael
"""
from matplotlib.pyplot import *
import numpy as np
data1 = [1,1,2,3,5,8,13]
data2 = [2,5,9,3,2,5,0]
data3 = [2,4,6,8,10]
data4 = [1,2,3,4,5]

#generic line plotting
fig = figure(1)
fig.suptitle("plot calls")
plt = subplot(4,1,1)
plot(data1)

ylabel("y axis")
xlabel("x axis")

#plotting using red circles
plt = subplot(4,1,2)
plot(data1, 'ro')

ylabel("y axis")
xlabel("x axis")

#plotting x/y data
plt = subplot(4,1,3)
plot(data1, data2, 'gD')

ylabel("y axis")
xlabel("x axis")

#plotting two lines in one call
plt = subplot(4,1,4)
plot(data1, data2, 'r--', data3, data4, 'y-.')

ylabel("y axis")
xlabel("x axis")
show()
