import matplotlib.pyplot as plt
import serial
import time

ser = serial.Serial()
ser.port = '/dev/rfcomm0'
ser.open()

print("opened serial port")
start_time = None
with open("data.txt", "w") as f:
    while (resp := ser.read().decode()) != "\n":
        if start_time is None:
            start_time = time.time()
        f.write(resp)
ser.close()
print("closed serial port")
end_time = time.time()

with open("data.txt") as f:
    data = f.read().split("; ")

data = list(map(lambda x: x.split(','), data))
errors = []
scan_diffs = []

data.remove([''])
for error, scan_diff in data:
    errors.append(error)
    scan_diffs.append(scan_diff)


print(f"Count values: {len(data)}")
print(f"Taken time: {end_time-start_time} seconds")

errors = list(map(float, filter(lambda x: x != '', errors)))
scan_diffs = list(map(float, filter(lambda x: x != '', scan_diffs)))

plt.plot(errors)
plt.plot(scan_diffs)
plt.show()
