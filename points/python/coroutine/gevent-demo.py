import gevent

def task_1(n):
    for i in range(n):
        print(gevent.getcurrent(), i)
        gevent.sleep(1)

def task_2(n):
    for i in range(n):
        print(gevent.getcurrent(), i)
        gevent.sleep(1)

def task_3(n):
    for i in range(n):
        print(gevent.getcurrent(), i)
        gevent.sleep(1)

g1 = gevent.spawn(task_1, 5) 
g2 = gevent.spawn(task_2, 5) 
g3 = gevent.spawn(task_3, 5)

g1.join()
g2.join()
g3.join()

