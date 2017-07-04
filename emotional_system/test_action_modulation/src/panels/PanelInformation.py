'''
Created on Jul 15, 2014

@author: julian
'''

from Tkinter import Tk, RAISED,DISABLED, BOTH, Label, Entry,StringVar, END
from ttk import Frame

class PanelInformation(Frame):
    def __init__(self,parent):
        Frame.__init__(self, parent)
        self.parent = parent
        self.initUI()
        
    def initUI(self):
        self.frame = Frame(self.parent, relief=RAISED,borderwidth=1)
        self.xL = StringVar()
        self.xLE = StringVar()
        self.positionXL = Label(self.frame, textvariable=self.xL)
        self.positionXL.grid(row=0,column=0)
        self.positionXE = Entry(self.frame, textvariable=self.xLE)
        self.positionXE.grid(row=0,column=1)
        self.xLE.set(0)
        self.yL = StringVar()
        self.yLE = StringVar()
        self.positionYL = Label(self.frame, textvariable=self.yL)
        self.positionYL.grid(row=1,column=0)
        self.positionYE = Entry(self.frame, textvariable=self.yLE)
        self.positionYE.grid(row=1,column=1)
        self.yLE.set(0)
        self.thetaL = StringVar()
        self.thetaLE = StringVar()
        self.positionThetaL = Label(self.frame, textvariable=self.thetaL)
        self.positionThetaL.grid(row=2,column=0)
        self.positionThetaE = Entry(self.frame, textvariable=self.thetaLE)
        self.positionThetaE.grid(row=2,column=1)
        self.thetaLE.set(0)
    
    def getInfo(self):
        return (self.positionXE.get(),self.positionYE.get(),self.positionThetaE.get())
    
    def setInfo(self,x,y,theta):
        self.xLE.set(x)
        self.yLE.set(y)
        self.thetaLE.set(theta)
       
    def getFrame(self):
        return self.frame 
    
    def setDisableEntry(self):
        self.positionXE.config(state=DISABLED)
        self.positionYE.config(state=DISABLED)
        self.positionThetaE.config(state=DISABLED)
        
    def setLabelXLabel(self,text):
        self.xL.set(text)
        
    def setLabelYLabel(self,text):
        self.yL.set(text)
        
    def setLabelThetaLabel(self,text):
        self.thetaL.set(text)