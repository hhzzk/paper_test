import numpy as np
import matplotlib.pyplot as plt
import matplotlib




s2_n2_time = [0.024,0.035,0.047,0.063,0.087]
s2_n3_time = [0.024,0.041,0.055,0.080,0.084]
s2_n4_time = [0.035,0.046,0.056,0.077,0.090]
s2_n5_time = [0.031,0.047,0.060,0.093,0.110]
s2_n6_time = [0.039,0.055,0.065,0.116,0.120]

s3_n2_time = [0.033,0.043,0.053,0.068,0.094]
s3_n3_time = [0.034,0.050,0.073,0.075,0.110]
s3_n4_time = [0.035,0.055,0.076,0.093,0.136]
s3_n5_time = [0.032,0.052,0.078,0.11,0.16]
s3_n6_time = [0.034,0.062,0.086,0.13,0.24]


s4_n2_time = [0.034,0.043,0.058,0.071,0.144]
s4_n3_time = [0.034,0.058,0.09,0.12,0.18]
s4_n4_time = [0.038,0.08,0.09,0.15,0.25]
s4_n5_time = [0.032,0.060,0.10,0.18,0.27]
s4_n6_time = [0.036,0.082,0.18,0.22,0.31]


s5_n2_time = [0.034,0.064,0.073,0.11,0.15]
s5_n3_time = [0.037,0.058,0.11,0.22,0.25]
s5_n4_time = [0.035,0.090,0.12,0.19,0.25]
s5_n5_time = [0.037,0.075,0.15,0.21,0.34]
s5_n6_time = [0.037,0.12,0.20,0.26,0.34]


width = 0.15       # the width of the bars
N = 5 
ind = np.arange(N)

fs = 28 


fig, ((ax11, ax12), (ax21, ax22)) = plt.subplots(2, 2, sharex = False, sharey = False)


# server=2
rects21 = ax11.bar(ind, s2_n2_time, width, color='y', label='2')
rects22 = ax11.bar(ind+width, s2_n3_time, width, color='b', label='3')
rects23 = ax11.bar(ind+2*width, s2_n4_time, width, color='r', label='4')
rects24 = ax11.bar(ind+3*width, s2_n5_time, width, color='g', label='5')
rects25 = ax11.bar(ind+4*width, s2_n6_time, width, color='c', label='6')

ax11.set_ylim(0.00,0.35)
ax11.set_ylabel('Time (second)', fontsize=fs)

ax11.set_xlim(-0.3,len(ind)+0.3)
ax11.set_xticks(ind+2*width)
ax11.set_xticklabels((100, 300, 500, 700, 900), fontsize=fs)
ax11.set_xlabel('Number of Flow', fontsize=fs)

ax11.grid(True)
ax11.set_title("(a) Two Servers.",fontsize=fs )
ax11.legend(loc='upper left')


# server=3
rects31 = ax12.bar(ind, s3_n2_time, width, color='y', label='2')
rects32 = ax12.bar(ind+width, s3_n3_time, width, color='b', label='3')
rects33 = ax12.bar(ind+2*width, s3_n4_time, width, color='r', label='4')
rects34 = ax12.bar(ind+3*width, s3_n5_time, width, color='g', label='5')
rects35 = ax12.bar(ind+4*width, s3_n6_time, width, color='c', label='6')

ax12.set_ylim(0.00,0.35)
ax12.set_ylabel('Time (second)', fontsize=fs)

ax12.set_xlim(-0.3,len(ind)+0.3)
ax12.set_xticks(ind+2*width)
ax12.set_xticklabels((100, 300, 500, 700, 900), fontsize=fs)
ax12.set_xlabel('Number of Flow', fontsize=fs)

ax12.grid(True)
ax12.set_title("(b) Three Servers.", fontsize=fs)
ax12.legend(loc='upper left')



# server=4
rects41 = ax21.bar(ind, s4_n2_time, width, color='y', label='2')
rects42 = ax21.bar(ind+width, s4_n3_time, width, color='b', label='3')
rects43 = ax21.bar(ind+2*width, s4_n4_time, width, color='r', label='4')
rects44 = ax21.bar(ind+3*width, s4_n5_time, width, color='g', label='5')
rects45 = ax21.bar(ind+4*width, s4_n6_time, width, color='c', label='6')

ax21.set_ylim(0.00,0.35)
ax21.set_ylabel('Time (second)', fontsize=fs)

ax21.set_xlim(-0.3,len(ind)+0.3)
ax21.set_xticks(ind+2*width)
ax21.set_xticklabels((100, 300, 500, 700, 900), fontsize=fs)
ax21.set_xlabel('Number of Flow', fontsize=fs)

ax21.grid(True)
ax21.set_title("(c) Four Servers.",fontsize=fs)
ax21.legend(loc='upper left')


# server=5
rects31 = ax22.bar(ind, s5_n2_time, width, color='y', label='2')
rects32 = ax22.bar(ind+width, s5_n3_time, width, color='b', label='3')
rects33 = ax22.bar(ind+2*width, s5_n4_time, width, color='r', label='4')
rects34 = ax22.bar(ind+3*width, s5_n5_time, width, color='g', label='5')
rects35 = ax22.bar(ind+4*width, s5_n6_time, width, color='c', label='6')

ax22.set_ylim(0.00,0.35)
ax22.set_ylabel('Time (second)', fontsize=fs)

ax22.set_xlim(-0.3,len(ind)+0.3)
ax22.set_xticks(ind+2*width)
ax22.set_xticklabels((100, 300, 500, 700, 900), fontsize=fs)
ax22.set_xlabel('Number of Flow', fontsize=fs)

ax22.grid(True)
ax22.set_title("(d) Five Servers.",fontsize=fs)
ax22.legend(loc='upper left')


for tick in ax11.xaxis.get_major_ticks():
     tick.label1.set_fontsize(fs)
for tick in ax11.yaxis.get_major_ticks():
     tick.label1.set_fontsize(fs)

for tick in ax21.xaxis.get_major_ticks():
     tick.label1.set_fontsize(fs)
for tick in ax21.yaxis.get_major_ticks():
     tick.label1.set_fontsize(fs)

for tick in ax12.xaxis.get_major_ticks():
     tick.label1.set_fontsize(fs)
for tick in ax12.yaxis.get_major_ticks():
     tick.label1.set_fontsize(fs)

for tick in ax22.xaxis.get_major_ticks():
     tick.label1.set_fontsize(fs)
for tick in ax22.yaxis.get_major_ticks():
     tick.label1.set_fontsize(fs)

plt.tight_layout()
plt.show()
