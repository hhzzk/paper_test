import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(13, 8))

time =       [0,1,2,3,4,5,6,7,8,9,10,11,12]
instance_1 = (0,1,2,2,3,3,2,2,3,1,2,1,2)
instance_2 = (0,1,2,3,4,2,2,3,2,1,2,3,4) 
instance_3 = (0,1,2,4,4,1,2,3,4,5,3,3,4)

plt.plot(time, instance_1,  linewidth=1.5, linestyle="-", marker='o')
plt.plot(time, instance_2,  linewidth=1.55555, linestyle="-", marker='o')
plt.plot(time, instance_3,  linewidth=1.5, linestyle="-", marker='o')
plt.yticks([0,1,2,3,4], fontsize=30)
plt.xlim(0, 13)
plt.xticks(time, fontsize=30)
plt.title("100pps", fontsize = 30)



plt.yticks([0,1,2,3,4,5,6], fontsize=30)
plt.ylim(0, 6)
plt.xlim(0, 13)
plt.xticks(time, fontsize=30)

#ax1.set_ylabel('Instances', fontsize=32)
#ax2.set_xlabel('Time', fontsize=32)

#plt.tight_layout()

plt.show()
