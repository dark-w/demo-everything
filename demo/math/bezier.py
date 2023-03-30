import matplotlib.pyplot as plt
import math
import random

x = []
y = []

controll_points = [[0, 0], [1, 2], [2, 2], [3, 0]]

def bezier(cps, t: float):
    ret_point = [0.0, 0.0]
    cps_x = [row[0] for row in cps]
    cps_y = [row[1] for row in cps]
    
    n = len(cps) - 1
    for k in range(n + 1): 
        c = math.comb(n, k) * ((1 - t) ** (n - k)) * (t ** k)
        ret_point[0] += c * cps_x[k]
        ret_point[1] += c * cps_y[k]

    return ret_point

for t in range(100):
    bn = bezier(controll_points, t / 100.0)
    x.append(bn[0])
    y.append(bn[1])

plt.plot([row[0] for row in controll_points], [row[1] for row in controll_points])
plt.scatter(x, y)

plt.xlabel('x-axis')
plt.ylabel('y-axis')
plt.title('Scatter Plot Example')

plt.show()
