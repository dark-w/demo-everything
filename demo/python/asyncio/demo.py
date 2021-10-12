import asyncio
import time

async def coro_func(cnt = 10):
    for i in range(cnt):
        await asyncio.sleep(1)
        print(i)

    return cnt

tasks = [
    asyncio.ensure_future(coro_func(2)),
    asyncio.ensure_future(coro_func(4)),
    asyncio.ensure_future(coro_func(6)),
]

loop = asyncio.get_event_loop()
loop.run_until_complete(asyncio.wait(tasks))

for task in tasks:
    print('Task ret: ', task.result())
