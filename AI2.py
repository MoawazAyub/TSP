import matplotlib.path as map_path
import matplotlib.patches as map_patches
import matplotlib.pyplot as plt
import re

fig, ax = plt.subplots()

filename = input("Enter File Name: ")
f = open(filename)
file = f.readlines()
i = 0
num_lines = sum(1 for lines in open(filename))

Coordinates_X = []
Coordinates_Y = []

while i < num_lines:
    x = list(map(float, re.findall('-?\d+\.\d+', file[i])))
    Coordinates_X.append(x[0])
    Coordinates_Y.append(x[1])
    i += 1
    pass

Path = map_path.Path
path_data = []
pass
path_data.append((Path.MOVETO, (Coordinates_X[0], Coordinates_Y[0])))

i = 1
while i < num_lines:
    path_data.append((Path.LINETO, (Coordinates_X[i], Coordinates_Y[i])))
    i += 1
    pass

path_data.append((Path.CLOSEPOLY, (Coordinates_X[0], Coordinates_Y[0])))

codes, vertices = zip(*path_data)
path = map_path.Path(vertices, codes)
patch = map_patches.PathPatch(path, facecolor='r', alpha=0.0)
ax.add_patch(patch)

x, y = zip(*path.vertices)
line, = ax.plot(x, y, 'go-')

ax.grid()
ax.axis('equal')
plt.show()