#!/usr/bin/python

from Tkinter import Tk,Button,Label,Listbox,RAISED,END,Scrollbar,VERTICAL, RIGHT, Y
from ttk import Frame
from panels import PanelInformation
import threading

class ActionModulationTest(threading.Thread):
    def __init__(self,info_queue,data_queue):
        threading.Thread.__init__(self)  
        self.info_queue = info_queue
        self.data_queue = data_queue
    
    def run(self):
        self = Tk()
        self.title("Test")
        self.position = PanelInformation.PanelInformation(self)
        self.position.getFrame().grid(row=0,column=0)
        self.position.setLabelXLabel("Position X:")
        self.position.setLabelYLabel("Position Y:")
        self.position.setLabelThetaLabel("Position Theta:")
        self.velocity = PanelInformation.PanelInformation(self)
        self.velocity.getFrame().grid(row=1,column=0)
        self.velocity.setLabelXLabel("Velocity X:")
        self.velocity.setLabelYLabel("Velocity Y:")
        self.velocity.setLabelThetaLabel("Velocity Theta:")
        
        self.positionInfo = PanelInformation.PanelInformation(self)
        self.positionInfo.setDisableEntry()
        self.positionInfo.getFrame().grid(row=0,column=2)
        self.positionInfo.setLabelXLabel("Position X:")
        self.positionInfo.setLabelYLabel("Position Y:")
        self.positionInfo.setLabelThetaLabel("Position Theta:")
        self.velocityInfo = PanelInformation.PanelInformation(self)
        self.velocityInfo.setDisableEntry()
        self.velocityInfo.getFrame().grid(row=1,column=2)
        self.velocityInfo.setLabelXLabel("Velocity X:")
        self.velocityInfo.setLabelYLabel("Velocity Y:")
        self.velocityInfo.setLabelThetaLabel("Velocity Theta:")
        
        self.frameEmotionAction = Frame(self, relief=RAISED,borderwidth=1)
        self.frameEmotionAction.grid(row=2,column=0,columnspan=3)
        self.labelEmotion = Label(self.frameEmotionAction,text="Emotion:")
        self.labelEmotion.grid(row=0,column=0)
        scrollbar = Scrollbar(self.frameEmotionAction, orient=VERTICAL)
        scrollbar.grid(row=0,column=3)
        self.listEmotion = Listbox(self.frameEmotionAction,height=2)
        self.listEmotion.grid(row=0,column=2)
        self.emotions = ['angry','happy','sad']
        for item in self.emotions:
            self.listEmotion.insert(END,item)
        self.listEmotion.config(yscrollcommand=scrollbar.set)
        scrollbar.config(command=self.listEmotion.yview)
        self.labelAction = Label(self.frameEmotionAction,text="Action:")
        self.labelAction.grid(row=0,column=4)
        scrollbar2 = Scrollbar(self.frameEmotionAction, orient=VERTICAL)
        scrollbar2.grid(row=0,column=6)
        self.listAction = Listbox(self.frameEmotionAction,height=2)
        self.listAction.grid(row=0,column=5)
        self.actions = ['oscillate_shoulder','oscillate_body','move_shoulder','move_body','walk','walk_and_speak']
        for item in self.actions:
            self.listAction.insert(END,item)
        self.listAction.config(yscrollcommand=scrollbar2.set)
        scrollbar2.config(command=self.listAction.yview)
        
        
        self.frameButtons = Frame(self, relief=RAISED,borderwidth=1)
        self.frameButtons.grid(row=3,column=0,columnspan=4)
        self.buttonReset = Button(self.frameButtons,text="Reset")
        self.buttonReset.grid(row=0,column=0)
        self.buttonStop = Button(self.frameButtons,text="Stop")
        self.buttonStop.grid(row=0,column=2)
        self.buttonSend = Button(self.frameButtons,text="Send")
        self.buttonSend.grid(row=0,column=4)
        self.mainloop()
    
    def updateInterface(self):
        print 'update'   
    def printThing(self):
        self.position.setLabelXLabel("Position XXX:")
    def configureButtonSend(self,function):
        pass
        
'''def main():
    root = Tk()
    app = ActionModulationTest(root)
    root.mainloop()
    
if __name__=='__main__':
    main()'''