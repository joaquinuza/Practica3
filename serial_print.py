# -*- coding: utf-8 -*-
"""
Created on Mon Oct 25 11:39:44 2021

@author: joaso
"""

import serial
import csv
import time
import re

ser = serial.Serial('COM5', 9600) #object to handle serial port
try:
    ser.readline()
    while True:
        s_bytes = ser.readline()
        decoded_bytes = s_bytes.decode('utf-8')
        s_data = [float(s) for s in re.findall(r'-?\d+\.?\d*', decoded_bytes)]
        print(decoded_bytes)
        with open("test_data.csv","a") as f:
            writer = csv.writer(f)
            writer.writerow(s_data)
except KeyboardInterrupt:
    ser.close()
    
            
