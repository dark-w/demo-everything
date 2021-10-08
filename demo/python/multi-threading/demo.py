import threading
import time

def communicate(n):
    for i in range(n):
        print("------ communicate -----")
        time.sleep(1)

def accept(n):
    for i in range(n):
        print("------ accept -----")
        time.sleep(1)

def main():
    t1 = threading.Thread(target = communicate, args = (3,))
    t2 = threading.Thread(target = accept, args = (5,))
    t1.start();
    t2.start();

    print(threading.enumerate())
    print("num of threading who is running: %d" % len(threading.enumerate()))

    t1.join();
    t2.join();
    print("----- process over -----")

if __name__ == "__main__":
    main()

