import matplotlib.pyplot as plt

ACC_FACTOR = 2
DEACC_FACTOR = 2

START_SPEED = 20
END_SPEED = 80
MAX_SPEED = 100

DEG = 300


def calc_max_speed(start_speed, end_speed, deg):
    max_speed = (deg + start_speed * ACC_FACTOR + end_speed *
                 DEACC_FACTOR) / (ACC_FACTOR + DEACC_FACTOR)
    print(f"Max speed: {max_speed}")
    return max_speed


def calc_deg_acc(start_speed, max_speed):
    return ACC_FACTOR * (max_speed - start_speed)


def calc_deg_deacc(max_speed, end_speed):
    return DEACC_FACTOR * (max_speed - end_speed)


def get_speed(start_speed, max_speed, deg_acc_end, deg_deacc_start, cur_deg):
    if abs(cur_deg) < abs(deg_acc_end):
        print("Beschleunigung")
        speed = -(2 * (max_speed - start_speed) * cur_deg**3) / deg_acc_end ** 3 + \
            (3 * (max_speed - start_speed) * cur_deg**2) / \
            deg_acc_end ** 2 + start_speed
        return speed
    elif abs(cur_deg) < abs(deg_deacc_start):
        print("ohne")
        return max_speed
    else:
        print("Entschleunigen")
        x = cur_deg - deg_deacc_start
        speed = (2 * (max_speed - 80) * x**3) / deg_deacc_start ** 3 - \
            (3 * (max_speed - 80) * x**2) / \
            deg_deacc_start ** 2 + max_speed
        return speed


def gen_curve(start_speed, end_speed, max_speed_limit, deg):
    if (start_speed > 0 == end_speed > 0):
        print("Start und End speed muss in die gleiche Richtung sein")
        return []
    # if (end_speed > max_speed_limit):
    #     print("End speed darf nicht größer als max_speed limit sein")
    #     return []
    deg = abs(deg)
    if start_speed < 0:
        deg = -deg
    max_speed = calc_max_speed(start_speed, end_speed, deg)
    if start_speed > 0:
        max_speed = min(max_speed, max_speed_limit)
    else:
        max_speed = max(max_speed, -max_speed_limit)
    deg_acc_end = calc_deg_acc(start_speed, max_speed)
    deg_deacc = calc_deg_deacc(max_speed, END_SPEED)
    deg_deacc_start = deg - deg_deacc
    print(deg_acc_end, deg_deacc_start)
    if (start_speed > 0):
        return [x for x in range(0, deg+1)], [get_speed(start_speed, max_speed, deg_acc_end, deg_deacc_start, x) for x in range(0, deg+1)]
    else:
        return [x for x in range(deg, 1)], [[get_speed(start_speed, max_speed, deg_acc_end, deg_deacc_start, x)] for x in range(deg, 1)]


data = gen_curve(START_SPEED, END_SPEED, MAX_SPEED, DEG)
print(data)
x, y = data
plt.plot(x, y)
plt.plot()
plt.show()
