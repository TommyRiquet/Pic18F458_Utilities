import serial
from tkinter import *

Port = 'COM2'
Rate = 9600


def getVal():
    Val = (serial.readline()).decode()
    print(Val)


def sendVal():
    try:
        int(inputVal.get())  # Test si valeur correcte
        labelErrIn.config(fg='black')
        ErrIn.set('')

        print('Valeur envoyé :', inputVal.get())
        ValOut.set(inputVal.get())  # A MODIF pour écrire sur le port !!!!!!
    except ValueError:
        ErrIn.set('Erreur')
        labelErrIn.config(fg='red')


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
inputVal = Entry(frameIn, width=9, textvariable=IntVar())
inputVal.pack()
ErrIn = StringVar()
labelErrIn = Label(frameIn, textvariable=ErrIn, font=('Arial', 15), fg='black')
labelErrIn.pack()
btnSend = Button(frameIn, text="Send", font=('Arial', 12), padx=4, pady=4, height=1, width=5, command=sendVal)
btnSend.pack()
frameIn.pack()

frameOut = Frame(window)
ValOut = StringVar()
labelValOut = Label(frameOut, textvariable=ValOut, font=('Arial', 15), fg='black')
labelValOut.pack()
frameOut.pack()

window.mainloop()

"""
Liaison avec le PIC
"""

serial = serial.Serial(Port, Rate)

serial.close()
