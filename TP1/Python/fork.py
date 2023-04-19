import os
import time

def son(data, value = None):
 if value == None:
  value = data.get('start')
 
 children_pids = []
 if value in data.get('processes').keys(): 
  for son_value in data.get('processes').get(value):
   pid = os.fork()
   if pid:
    children_pids.append(pid)
   else:
    son(data, son_value)
    return
    
  for child_pid in children_pids:
   os.waitpid(child_pid, 0)

 print('My value is: {}. My PID is: {}. My PPID is: {}'.format(value, os.getpid(), os.getppid())) 
 time.sleep(25)

if __name__ == '__main__':
 data = {'start': 'A','processes': {'A': ['B', 'C', 'D'],'B': ['E', 'F'],'D': ['G']}}
 son(data)