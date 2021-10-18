import asyncio
import time
import threading
from typing import Tuple

# # demo 1
# async def main_demo1():
#     print('Hello ...')
#     await asyncio.sleep(1)
#     print('... World!')

# print('before main')
# asyncio.run(main_demo1())
# print('after main')

# # demo 2
# async def say_after(delay, content):
#     await asyncio.sleep(delay)
#     print(content)

# async def main_demo2():
#     print("start time: {}".format(time.strftime('%X')))
    
#     await say_after(1, 'hello')
#     await say_after(2, 'world')

#     print("end time: {}".format(time.strftime('%X')))

# asyncio.run(main_demo2())

# async def main_demo2_after_modified():
#     task1 = asyncio.create_task(say_after(1, 'hello'))
#     task2 = asyncio.create_task(say_after(2, 'world'))

#     print("start time: {}".format(time.strftime('%X')))

#     # Wait until both tasks are completed (should take
#     # around 2 seconds.)
#     await task1
#     await task2

#     print("end time: {}".format(time.strftime('%X')))
    
# asyncio.run(main_demo2_after_modified())

# # demo 3
# async def nested():
#     return 42

# async def main_demo3():
#     print(await nested())

# asyncio.run(main_demo3())

# # demo 4
# async def main_demo4():
#     task1 = asyncio.create_task(nested())
    
#     print(await task1)

# asyncio.run(main_demo4())

# # demo 5
# async def factorial(name, num):
#     f = 1
#     for i in range(2, num + 1):
#         print("Task {}: Compute factorial({})...".format(name, i))
#         await asyncio.sleep(1)
#         f *= i

#     print("Task {}: factorial({}) = {}".format(name, num, f))

# async def main_demo5():
#     await asyncio.gather(
#         factorial("A", 2),
#         factorial("B", 3),
#         factorial("C", 4),
#     )

# asyncio.run(main_demo5())

# # demo 6

# async def grandmom_func():
#     await asyncio.sleep(3600)
#     return 42

# async def main():
#     try:
#         await asyncio.wait_for(grandmom_func(), 1)
#     except asyncio.TimeoutError:
#         print("timeout!")

# asyncio.run(main())

# # demo 7
# async def demo7_fun(n):
#     await asyncio.sleep(n)
#     return n

# async def main_demo7():
#     task1 = asyncio.create_task(demo7_fun(2))
#     task2 = asyncio.create_task(demo7_fun(4))

#     done, pending = await asyncio.wait({task1, task2}, timeout=3)

#     print("task1's name: {}, task2's name: {}".format(task1.get_name(), \
#                                                       task2.get_name()))
#     print("done:")
#     for item in done:
#         print(item.get_name())
#     print("pending:")
#     for item in pending:
#         print(item.get_name())

# asyncio.run(main_demo7())

# # demo 8
# async def func_demo8(name, delay):
#     for i in range(delay):
#         # print("{} {}".format(name, i))
#         await asyncio.sleep(1)
#     # print("{} is done".format(name))
#     return delay

# async def main_demo8():
#     task1 = asyncio.create_task(func_demo8('A', 2))
#     task2 = asyncio.create_task(func_demo8('B', 4))
#     task3 = asyncio.create_task(func_demo8('C', 6))
#     task4 = asyncio.create_task(func_demo8('D', 8))
#     task5 = asyncio.create_task(func_demo8('E', 10))
    
#     # like a async generator
#     for future_obj in asyncio.as_completed({task1, task2, task3, task4, task5}):
#         print("before iterate...")
#         print("for_each: {}".format(await future_obj))

# asyncio.run(main_demo8())

# demo 9
class coro_executor(threading.Thread):
    def __init__(self, args):
        threading.Thread.__init__(self)
        self.args = args

    async def coro1(self):
        task_name = "task1"
        while True:
            print(task_name)
            await asyncio.sleep(1)

    def run(self):
        task1 = asyncio.create_task(self.coro1())
        asyncio.run(task1())

class other_thread_that_produce_coros(threading.Thread):
    def run(self):
        pass

ce = coro_executor(1)
ce.start()
ce.join()
