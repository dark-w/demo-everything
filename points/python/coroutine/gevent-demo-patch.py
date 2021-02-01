from gevent import monkey 
import gevent
import time

monkey.patch_all()

def coroutine_task(name):
    while True:
        print("----- {} -----".format(name))
        time.sleep(0.5)

gevent.joinall(
    [gevent.spawn(coroutine_task, "hello task"),
    gevent.spawn(coroutine_task, "world task")]
)

