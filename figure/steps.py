import numpy as np
import matplotlib.pyplot as plt

cookie_means = (20.7, 47, 29.6, 2.7)
cookie_means0 = (0, 20.7, 67.7, 97.3, 100)
multi_means = (7.8, 65.2, 26.7, 0.4)
multi_means0 = (0, 7.8, 73.0, 99.6, 100)

datas0 = [-0.35, 0.35, 1+0.35, 2+0.35, 3+0.35]
datas1 = [1.35, 2.35, 3.35, 4.35]
datas2 = [1+0.35/2, 2+0.35/2, 3+0.35/2, 4+0.35/2]

width = 0.35       # the width of the bars
N = 4
ind = np.arange(N)
#fig = plt.figure(figsize=(10,5))
#ax = plt.subplots()
fig, ax = plt.subplots(figsize=(12,5))
rects1 = ax.bar(ind, cookie_means, width, color='r' )

rects3 = ax.plot(datas0, cookie_means0, linewidth=2, linestyle="--", color ='blue')
rects4 = ax.plot(datas0, multi_means0, linewidth=2, linestyle="-", color="y")

rects2 = ax.bar(ind+width, multi_means, width, color='y')

# add some text for labels, title and axes ticks
ax.set_ylim(0,100)
ax.set_ylabel('Slice')
#ax.set_title('Scores by group and gender')
ax.set_xticks(ind+width)
ax.set_xlabel('Steps')
ax.set_xlim(-width,len(ind)+width)
ax.set_xticklabels((1, 2, 3, 4))

ax.legend((rects1[0], rects2[0], rects3[0], rects4[0]),
          ('HTTP Cookie', 'Multistep', 'HTTP Cookie', 'Multistep'),
          loc='upper left')

plt.grid(True)


plt.show()
