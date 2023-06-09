import matplotlib.pyplot as plt

PATH_DRIVE_SMOOTH_OUTPUT = "data/temp/drive_smooth_output.txt"

if __name__ == '__main__':
    with open(PATH_DRIVE_SMOOTH_OUTPUT) as f:
        file_data = f.read().strip("\n")

    values = list(map(float, file_data.strip(";").split(";")))

    plt.scatter(list(range(len(values))), values, c="black", s=1)
    plt.show()
