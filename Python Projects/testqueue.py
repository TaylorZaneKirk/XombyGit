# Using Lists as Queues
queue = ["Eric", "John", "Michael"]
print ('Initial Queue: ', queue)

queue.append("Terry")           # Terry arrives
queue.append("Graham")          # Graham arrives
print ('Queue after adding Terry and Graham: ', queue, '\n')

s=queue.pop(0)
print ('Deq  element: ' , s)

s=queue.pop(0)
print ('Deq  element: ' , s)

print ('Final queue: ' , queue)