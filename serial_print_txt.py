
# -*- coding: utf-8 -*-
"""
Created on Mon Oct 25 11:39:44 2021

@author: Joaquin Sopena
"""

import serial

ser = serial.Serial('COM5', 9600) #object to handle serial port
try:
    ser.readline()
    while True:
        s_bytes = ser.readline()
        decoded_bytes = float(s_bytes[0:len(s_bytes)-2].decode("utf-8"))
        print(decoded_bytes)
        with open("test_data.txt","a") as f:
            f.write(str(decoded_bytes))
            f.write("; \n")
except KeyboardInterrupt:
    ser.close()