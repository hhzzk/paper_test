import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(13, 6))

time =       [0,1,2,3,4,5,6,7,8,9,10,11,12]
instance_1 = (0,1,2,2,3,3,2,2,3,1,2,1,2)
instance_2 = (0,1,2,3,4,2,2,3,2,1,2,3,4) 
instance_3 = (0,1,2,4,4,1,2,3,4,5,3,3,4)

plt.subplot(3, 1, 1)
plt.plot(time, instance_1,  linewidth=1.5, linestyle="-", marker='o')
plt.ylim(0, 4)
plt.yticks([0,1,2,3,4])
plt.xlim(0, 13)
plt.xticks(time)
plt.title("100pps")


plt.subplot(3, 1, 2)
plt.plot(time, instance_2,  linewidth=1.55555, linestyle="-", marker='o')
plt.ylim(0, 5)
plt.xlim(0, 13)
plt.xticks(time)
plt.title("200pps")


plt.subplot(3, 1, 3)
plt.plot(time, instance_3,  linewidth=1.5, linestyle="-", marker='o')
plt.ylim(0, 6)
plt.xlim(0, 13)
plt.xticks(time)
plt.title("400pps")


plt.show()
