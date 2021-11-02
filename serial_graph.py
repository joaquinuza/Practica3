# -*- coding: utf-8 -*-
"""
Created on Mon Oct 25 12:18:25 2021

@author: Joaquin Sopena
"""

import serial
import time
import re
import numpy as np
import matplotlib.pyplot as plt

seconds = 5
ax = np.array([])
ay = np.array([])
az = np.array([]) 
ser = serial.Serial('COM5', 9600) #object to handle serial port

try:
    ser.readline()
    while True:
        start_time = time.time()
        while True:
            current_time = time.time()
            elapsed_time = current_time - start_time
            if elapsed_time <= seconds:
                s_bytes = ser.readline()    #read one line of the serial buffer
                decoded_bytes = s_bytes.decode('utf-8') #convert byte to str
                s_data = [float(s) for s in re.findall(r'-?\d+\.?\d*', decoded_bytes)]
                #extract a list of data, in this case ax, ay, az
                ax = np.append(ax, s_data[0])
                ay = np.append(ay, s_data[1])
                az = np.append(az, s_data[2])
            else:
                break
        
        avg_ax = np.average(ax)
        avg_ay = np.average(ay)
        avg_az = np.average(az)
        sd_ax  = np.std(ax) 
        sd_ay =  np.std(ay)
        sd_az = np.std(az)
except KeyboardInterrupt:
    plt.plot(ax)
    plt.plot(ay)
    plt.plot(az)
    ser.close()