#!/usr/bin/python

from Tkinter import Tk,Button,Label,Listbox,RAISED,END,Scrollbar,VERTICAL, RIGHT, Y, IntVar
from ttk import Frame, Scale
from panels import PanelInformation

class ActionModulation(Frame):
    def __init__(self,parent):
        Frame.__init__(self,parent)
        self.parent = parent
        self.intensityValue = 0.0
        self.initUI()
        
    def initUI(self):
        self.frame = Frame(self.parent, relief=RAISED,borderwidth=1)
        #panel with the information to be introduced
        #self.grid(row=0,column=0)
        self.position = PanelInformation.PanelInformation(self.frame)
        self.position.getFrame().grid(row=0,column=0)
        self.position.setLabelXLabel("Position X:")
        self.position.setLabelYLabel("Position Y:")
        self.position.setLabelThetaLabel("Position Theta:")
        self.velocity = PanelInformation.PanelInformation(self.frame)
        self.velocity.getFrame().grid(row=1,column=0)
        self.velocity.setLabelXLabel("Walk Shoulder:")
        self.velocity.setLabelYLabel("Walk torso:")
        self.velocity.setLabelThetaLabel("Pose:")
        #panel for the emotion intensity
        self.frameIntensity =  Frame(self.frame, relief=RAISED,borderwidth=1)
        self.frameIntensity.grid(row = 4, column = 0)
        self.labelIntensity = Label(self.frameIntensity,text="Intensity:")
        self.labelIntensity.grid(row=0,column=0)
        self.intensity = Scale(self.frameIntensity, from_=0, to = 1,command=self.onScale)
        self.intensity.grid(row = 1, column = 0)
        self.var = IntVar()
        self.labelInfoIntensity = Label(self.frameIntensity, text=0, textvariable=self.var)
        self.labelInfoIntensity.grid(row = 2, column = 0)
        
        #panel with the robot's information
        self.positionInfo = PanelInformation.PanelInformation(self.frame)
        self.positionInfo.setDisableEntry()
        self.positionInfo.getFrame().grid(row=0,column=2)
        self.positionInfo.setLabelXLabel("Position X:")
        self.positionInfo.setLabelYLabel("Position Y:")
        self.positionInfo.setLabelThetaLabel("Position Theta:")
        self.velocityInfo = PanelInformation.PanelInformation(self.frame)
        self.velocityInfo.setDisableEntry()
        self.velocityInfo.getFrame().grid(row=1,column=2)
        self.velocityInfo.setLabelXLabel("Velocity X:")
        self.velocityInfo.setLabelYLabel("Velocity Y:")
        self.velocityInfo.setLabelThetaLabel("Velocity Theta:")
        #emotions and actions
        self.frameEmotionAction = Frame(self.frame, relief=RAISED,borderwidth=1)
        self.frameEmotionAction.grid(row=2,column=0,columnspan=3)
        self.labelEmotion = Label(self.frameEmotionAction,text="Emotion:")
        self.labelEmotion.grid(row=0,column=0)
        scrollbar = Scrollbar(self.frameEmotionAction, orient=VERTICAL)
        scrollbar.grid(row=0,column=3)
        self.listEmotion = Listbox(self.frameEmotionAction,height=4)
        self.listEmotion.grid(row=0,column=2)
        self.listEmotion.bind("<<ListboxSelect>>", self.onSelectEmotion)
        #the new emotions should be added here
        self.emotions = ['neutral','angry','happy','sad','fear','content']
        for item in self.emotions:
            self.listEmotion.insert(END,item)
        self.listEmotion.config(yscrollcommand=scrollbar.set)
        scrollbar.config(command=self.listEmotion.yview)
        self.labelAction = Label(self.frameEmotionAction,text="Action:")
        self.labelAction.grid(row=0,column=4)
        scrollbar2 = Scrollbar(self.frameEmotionAction, orient=VERTICAL)
        scrollbar2.grid(row=0,column=6)
        self.listAction = Listbox(self.frameEmotionAction,height=4)
        self.listAction.grid(row=0,column=5)
        #the new actions should be added here
        self.actions = ['not_do_anything','oscillate_shoulder','oscillate_body','move_shoulder','move_body','move_torso','oscillate_torso','walk']
        for item in self.actions:
            self.listAction.insert(END,item)
        self.listAction.config(yscrollcommand=scrollbar2.set)
        self.listAction.bind("<<ListboxSelect>>", self.onSelectAction)
        scrollbar2.config(command=self.listAction.yview)
        
        self.actionSelected = "do_nothing"
        self.emotionSelected = "neutral"
    
    def getFrame(self):
        return self.frame
    
    def onScale(self, val): 
        v = format(float(val),'.2f')
        self.intensityValue = v
        self.var.set(v) 
        
    def getIntensity(self):
        return self.intensityValue
        
    def onSelectAction(self,val):
        sender = val.widget
        idx = sender.curselection()
        self.actionSelected = sender.get(idx)
        
    def onSelectEmotion(self,val):
        sender = val.widget
        idx = sender.curselection()
        self.emotionSelected = sender.get(idx)
    
    def getListEmotion(self):
        return self.emotionSelected
        
    def getListAction(self):
        return self.actionSelected
    
    def getPanelPosition(self):
        return self.position
    
    def getPanelVelocity(self):
        return self.velocity    
    
    def getPanelInfoPosition(self):
        return self.positionInfo
    
    def getPanelInfoVelocity(self):
        return self.velocityInfo

        
def main():
    root = Tk()
    app = ActionModulationTest(root)
    root.mainloop()
    
if __name__=='__main__':
    main()
