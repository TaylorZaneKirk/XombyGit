##############################################################################
#                    Project Name: Quadratic Functions
#                           Name: Taylor Kirk
#                    Data Structures Date: 03/13/2015
##############################################################################
#        This program reads in a data file which should contain the
#     values to be used to form a quadratic equation, and, using the
#     quadratic formula will process and return a factored form.
##############################################################################

import cmath

DataFile = open('data.txt', 'r')    #Open data file

#for-Loop to read in each line of integers from data file
for line in DataFile:
    
    stringNumbers = line.split()    #split line string by white-space
    
    #convert each item in stringNumber list in a list
        #of float-type integers
    floatNumbers = [float(x) for x in stringNumbers]
    
    #Assign each float-integer to a variable
    a = floatNumbers[0]
    b = floatNumbers[1]
    c = floatNumbers[2]
    
    disc = (b**2) - (4*a*c) #Discriminate
    
    #Calculate both answers
    first = (-b-cmath.sqrt(disc))/(2*a)
    second = (-b+cmath.sqrt(disc))/(2*a)
    
    #print result
    print('[%d, %d, %d] {0} {1}'.format(first,second)) % (a, b, c)
        
DataFile.close()    #close data file