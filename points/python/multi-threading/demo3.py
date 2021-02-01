import threading
import time

num = 100

class my_thread(threading.Thread):
    def run(self):
        global num

        for i in range(5):
            num += 1
            print("i'm {} @ {}, num = {}".format(self.name, str(i), num))
            time.sleep(1)

def main():
    t1 = my_thread()
    t2 = my_thread()

    t1.start()
    t2.start()

    t1.join()
    t2.join()

if __name__ == "__main__":
    main()

