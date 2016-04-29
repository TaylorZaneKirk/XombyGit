import matplotlib.pyplot as plt

def plotHistogram(h):
     #get the lists for the X, Y axes    
     mykeys = sorted(h.keys())
     myvalues = list()
     for key in mykeys:
         myvalues.append(h[key])

     # the bar chart of the data
     plt.figure()
     plt.bar(range(len(mykeys)), myvalues, align="center")
   
     #labels
     plt.xticks(range(len(mykeys)), mykeys)
     plt.xlabel('letters')
     plt.ylabel('freq')
     plt.title('Histogram of Frequency Counts')
     plt.margins(0.025,0)
     
     plt.show()

#count letters in string
def frequency (s):
    d = dict()
    for c in s:
         if c not in d:
              d[c] = 1
         else:
              d[c] += 1
    return d
 
#created a sorted list of items from a dictionary   
def printSortedFrequencyByValue(h):
    print ('\nSorted dictionary by value')
    mylist = sorted(h, key=h.get)

    for key in mylist:
        print (key, h[key]) 
        
#created a sorted list of items from a dictionary   
def printSortedFrequencyByKey(h):
    print ('\nSorted dictionary by key')
    mylist = sorted(h.keys())

    for key in mylist:
        print (key, h[key]) 
    
#print items in a dictionary    
def printSortedFrequency(h):   
    print('\nList of dictionary values')
    for k, v in h.items(): 
        print (k, v)
    
h = frequency('a brown cow jumped over the moon')
print ('Dictionary =', h)

printSortedFrequency(h)

printSortedFrequencyByValue(h)

printSortedFrequencyByKey(h)

plotHistogram(h)

