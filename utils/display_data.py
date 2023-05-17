import matplotlib.pyplot as plt

with open("output/output_rolled_average.txt") as f:
    data = list(map(float, f.read().strip("\n").strip(",").split(",")))

plt.scatter(list(range(len(data))), data, s=1)
plt.show()
plt.close()
