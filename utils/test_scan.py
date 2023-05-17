import matplotlib.pyplot as plt
import json
import os


def load_data(path):
    with open(path) as f:
        data = f.read()
    data = data.strip("\n").strip(",")
    data = list(map(float, data.split(",")))
    return data


def moving_average(data, data_points_count):
    output = []
    len_data = len(data)
    for i in range(len_data - data_points_count):
        output.append(sum(data[i:i+data_points_count]) / data_points_count)
    return output


def filter_bottom_part(data, threashold_point):
    # high pass filter
    # return list(map(lambda x: x if x >= threashold_point else 0, data))
    return list(filter(lambda x: x >= threashold_point, data))


def find_maximas(data, min_maximum_value):
    maximas = {}
    for i in range(1, len(data) - 1):
        if data[i-1] < data[i] and data[i] >= data[i+1] and (min_maximum_value is None or data[i] > min_maximum_value):
            maximas[i] = ({"value":  data[i],
                           "down_significance": len(data), "up_significance": len(data)})
    return maximas


def calc_significance_of_maximas(data, maximas):
    for id, maxima_data in maximas.items():
        value = maxima_data["value"]
        down_significance = 0
        up_significance = 0
        for i in range(id-1, -1, -1):
            # greater equal is hear important because it can happen that 2 maximas with same value are quite near to each other
            # in this case the left one would be taken, because the significance of the right one would be quite low because of the maxima left to it
            if data[i] >= value:
                maxima_data["down_significance"] = down_significance
                break
            down_significance += 1

        for i in range(id+1, len(data)):
            if data[i] > value:
                maxima_data["up_significance"] = up_significance
                break
            up_significance += 1

        maxima_data["overall_significance"] = min(
            maxima_data["down_significance"], maxima_data["up_significance"])


def find_most_significant_maximas(maximas, count=2):
    most_significant_maximas_ids = [0 for _ in range(count)]

    for i in range(count):
        current_maximum_significance = 0
        for id, maxima_data in maximas.items():
            if id not in most_significant_maximas_ids and maxima_data["overall_significance"] > current_maximum_significance:
                most_significant_maximas_ids[i] = id
                current_maximum_significance = maxima_data["overall_significance"]

    most_significant_maximas_ids = sorted(most_significant_maximas_ids)
    return most_significant_maximas_ids, [maximas[id]["value"] for id in most_significant_maximas_ids]


def get_color(value, color_threshold):
    return "blue" if value > color_threshold else "green"


def evaluate(path, moving_average_count, filter_threashold, maxima_count, color_threshold, min_maximum_value):
    print("------------------------------------------")
    print(path)
    data = load_data(path)
    print(f"Anzahl Werte: {len(data)}")

    # plt.scatter(range(len(data)), data, s=1, color="black")

    data = moving_average(data, moving_average_count)

    data = filter_bottom_part(data, filter_threashold)

    maximas = find_maximas(data, min_maximum_value)

    calc_significance_of_maximas(data, maximas)
    # print(json.dumps(maximas, indent=4))

    wanted_ids, wanted_values = find_most_significant_maximas(
        maximas, count=maxima_count)
    # print(wanted_ids, wanted_values)
    summed_values = 0
    for i, value in enumerate(wanted_values):
        print(f"Color {i+1}: {get_color(value, color_threshold)}, {value:.3f}")
        summed_values += value

    print(f"Average: {summed_values/len(wanted_values):.3f}")

    x_values = range(len(data))

    plt.scatter(x_values, data, s=1)
    plt.scatter(wanted_ids, wanted_values, s=100, color="green")
    plt.scatter(maximas.keys(), [maxima_data["value"]
                for maxima_data in maximas.values()], s=20, color="red")
    plt.show()


def evaluate_all(path, moving_average_count, filter_threashold, maxima_count, color_threshold, min_maximum_value):
    for file in os.listdir(path):
        if os.path.isfile(os.path.join(path, file)):
            evaluate(os.path.join(path, file),
                     moving_average_count, filter_threashold, maxima_count, color_threshold, min_maximum_value)


if __name__ == "__main__":
    evaluate_all("data", 200, 0.2, 2, 0.48, 0.25)
