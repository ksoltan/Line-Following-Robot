import serial
import time
import matplotlib.pyplot as plt
import csv
import sys

# Establish the connection
ser = serial.Serial('/dev/ttyACM1', 9600)

times = []
port_values = []
starboard_values = []
port_motors = []
starboard_motors = []
counter_max = 200
counter = 0
while (counter < counter_max):
	print(counter)
	l = ser.readline().strip()
	sensor_values = l.split(b",")
	if(len(sensor_values) == 4):
		#print(sensor_values[0])
		times.append(time.time()) # gives in seconds
		port_values.append(float(sensor_values[0]) * 5 / 1023)
		starboard_values.append(float(sensor_values[1]) * 5 / 1023)
		port_motors.append(float(sensor_values[2]) / 21)
		starboard_motors.append(float(sensor_values[3]) / 21)
		time.sleep(0.1)
		counter += 1
print(port_values)
print(starboard_values)
print(port_motors)
print(starboard_motors)
plt.plot(starboard_values, 'r--', port_values, 'b--', starboard_motors, 'rs', port_motors, 'bs')
plt.show()
