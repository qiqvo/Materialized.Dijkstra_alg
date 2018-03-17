from mpl_toolkits.mplot3d import Axes3D
from random import random as r
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

def plot_points_file(file_name, c='b', s=0, skip=False):
	x,y,z = [],[],[]
	file = open(file_name)
	for line in file:
		if skip:
			if r() > 1/2:
				continue
		nums = line.split()
		x.append(float(nums[0]))
		y.append(float(nums[1]))
		z.append(float(nums[2]))
	
	if s == 0:
		ax.scatter(x,y,z,c=c)
	else:
		ax.scatter(x,y,z,c=c,s=s)

	file.close()

def main():
	plot_points_file('points',skip=True)

	plot_points_file('path0', c='r', s=200)
	# plot_points_file('path1', c='r')
	plt.show()

if __name__ == '__main__':
	main()