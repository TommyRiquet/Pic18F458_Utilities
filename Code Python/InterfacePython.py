import serial
from tkinter import *
import time

Port = 'COM3'
Rate = 9600

portSerie = serial.Serial(Port, Rate)


def getVal():
    while True :
        Val = portSerie.readline().decode()
        Val = Val[:-1]
        ValOut.set(Val + " cm")
        if int(Val) < 100:
            labelValIn.config(fg='green')  # Si Alarme
        else:
            labelValIn.config(fg='red')  # Si pas d'alarme

        window.update()

        portSerie.flush()




"""
Interface Graphique
"""

window = Tk()
window.title('PIC18F458')
window.geometry('200x200')
window.resizable(False, False)

frameIn = Frame(window)
labelValIn = Label(frameIn, text='Valeur', font=('Arial', 12), fg='black')
labelValIn.pack()
frameIn.pack()

frameOut = Frame(window)
ValOut = StringVar()
labelValOut = Label(frameOut, textvariable=ValOut, font=('Arial', 15), fg='black')
labelValOut.pack()
frameOut.pack()


getVal()

portSerie.close()
