import time
import serial
import tkinter

Port = 'COM2'
Rate = 9600

# Liaison avec le PIC
serial = serial.Serial(Port, Rate)


def read():
    line = (serial.readline()).decode()
    print(line)


def write(x):
    serial.write(x)


write(b'1')

serial.close()
