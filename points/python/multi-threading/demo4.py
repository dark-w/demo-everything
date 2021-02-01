import threading

# pls thinking about if there not use mutex...
# you must try it, comment the line 12 and the line 14...
mutex = threading.Lock()
num = 0

def fun1(n):
    global num
 
    for i in range(n):
        mutex.acquire()
        num += 1
        mutex.release()
    
    print("num result: {}".format(num))        

def main():
    t1 = threading.Thread(target = fun1, args = (1000000,))
    t2 = threading.Thread(target = fun1, args = (1000000,))
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    print("num result: {}".format(num))        
    
if __name__ == "__main__":
    main()
    
