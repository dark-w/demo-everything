import threading
import time

mutex_a = threading.Lock()
mutex_b = threading.Lock()

def fun1():
    mutex_a.acquire()
    time.sleep(1)
    mutex_b.acquire()
    
    mutex_a.release()
    mutex_b.release()
    print("------- fun1 over ------")

def fun2():
    mutex_b.acquire()
    time.sleep(1)
    mutex_a.acquire()

    mutex_a.release()
    mutex_b.release()

def main():
    t1 = threading.Thread(target = fun1)
    t2 = threading.Thread(target = fun2)
    t1.start()
    t2.start()
    t1.join()
    t2.join()

    print("--------- main over ---------- ")
    
if __name__ == "__main__":
    main()

