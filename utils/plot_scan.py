import matplotlib.pyplot as plt
import os
import sys

from shutil import copyfile


def plot_file(filepath):
    data = []
    with open(filepath) as f:
        lines = f.read().strip("\n").split("\n")

        for line in lines:
            data.append(list(map(float, line.strip(",").split(","))))

    datapoints = data[0]

    plt.scatter(list(range(len(datapoints))), datapoints, s=1, color='black')

    rolled_average = data[1]
    plt.scatter(list(range(len(rolled_average))),
                rolled_average, s=1, color='blue')

    if len(data) > 3:
        selected_maximas = list(map(int, data[3]))
        plt.scatter(selected_maximas, [rolled_average[selected_maxima]
                                       for selected_maxima in selected_maximas], s=100, color="green")

    if len(data) > 2:
        maximas = list(map(int, data[2]))

        plt.scatter(maximas, [rolled_average[maxima]
                              for maxima in maximas], s=10, color="red")

    plt.show()
    plt.close()


DIR_PATH = "utils/data"
COPY = False

if __name__ == '__main__':
    if len(sys.argv) > 1:
        plot_file(sys.argv[1])
    else:
        try:
            copyfile("/media/max/EV3_WRO/blocks.txt", "utils/data/blocks.txt")
            copyfile("/media/max/EV3_WRO/containers.txt",
                     "utils/data/containers.txt")
        except Exception:
            print("Failed to load files from robot")
        for file in os.listdir(DIR_PATH):
            file_path = os.path.join(DIR_PATH, file)
            print("--------------------------")
            print(file_path)
            plot_file(file_path)
