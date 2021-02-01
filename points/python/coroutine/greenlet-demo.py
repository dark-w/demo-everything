from greenlet import greenlet

def task_1():
    while True:
        print("--- task_1 ---")
        gl_task_2.switch()
        

def task_2():
    while True:
        print("--- task_2 ---")
        gl_task_1.switch()

gl_task_1 = greenlet(task_1)
gl_task_2 = greenlet(task_2)

gl_task_1.switch()

