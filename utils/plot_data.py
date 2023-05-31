import matplotlib.pyplot as plt
import sys

if (len(sys.argv) < 2):
    exit(1)

data = []

with open(sys.argv[1]) as f:
    lines = f.read().strip("\n").split("\n")

    for line in lines:
        data.append(list(map(float, line.strip(",").split(","))))


datapoints = data[0]

plt.scatter(list(range(len(datapoints))), datapoints, s=1)

if len(data) > 2:
    selected_maximas = list(map(int, data[2]))
    plt.scatter(selected_maximas, [datapoints[selected_maxima]
                                   for selected_maxima in selected_maximas], s=100, color="green")

if len(data) > 1:
    maximas = list(map(int, data[1]))
    
    plt.scatter(maximas, [datapoints[maxima]
                          for maxima in maximas], s=10, color="red")

plt.show()
plt.close()
