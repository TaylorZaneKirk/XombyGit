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
def printFrequency(h):   
    print('\nList of dictionary values')
    for k, v in h.items(): 
        print (k, v)
    
h = frequency('a brown cow jumped over the moon')
print ('Dictionary =', h)

printFrequency(h)

printSortedFrequencyByValue(h)

printSortedFrequencyByKey(h)

