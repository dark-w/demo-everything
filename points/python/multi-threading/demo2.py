import threading
import time

class my_thread(threading.Thread):
    def run(self):
        msg = "i'm " + self.name + " @ " 
        for i in range(5):
            print(msg + str(i))
            time.sleep(1)

def main():
    t = my_thread()
    t.start()
    t.join()

if __name__ == "__main__":
    main()

