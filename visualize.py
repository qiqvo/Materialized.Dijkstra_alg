from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

def plot_points_file(file_name, c='b'):
	x,y,z = [],[],[]
	file = open(file_name)
	for line in file:
		nums = line.split()
		x.append(float(nums[0]))
		y.append(float(nums[1]))
		z.append(float(nums[2]))
	
	ax.scatter(x,y,z,c=c)
	file.close()

def main():
	plot_points_file('points')

	plot_points_file('path1', c='r')
	# plot_points_file('path2', c='r')
	plt.show()

if __name__ == '__main__':
	main()