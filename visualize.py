from mpl_toolkits.mplot3d import Axes3D
from random import random as r
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

def plot_points_file(file_name, c='b', s=0, skip=False):
	x,y,z = [],[],[]
	try:
		file = open(file_name)
	except Exception as e:
		print("No file found with name " , file_name)
		return 

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
	plot_points_file('path1', c='g', s=200)
	plot_points_file('path2', c='y', s=200)
	plot_points_file('path3', c='violet', s=200)
	plot_points_file('path4', c='m', s=200)
	plt.show()

if __name__ == '__main__':
	main()