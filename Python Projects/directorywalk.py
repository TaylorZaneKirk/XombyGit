import os

def walk(dirname):
    for name in os.listdir(dirname):
       #join the directory name with the filename
       path = os.path.join(dirname, name)
       if os.path.isfile(path):
           print (path)
       else:
           print(path)
           walk(path)
       
walk ('D:\Games')
