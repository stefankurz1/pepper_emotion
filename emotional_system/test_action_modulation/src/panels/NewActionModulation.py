from Tkinter import Label, Tk,Button, RAISED
from ttk import Notebook, Frame
from panels import ActionModulation, GeneralActionModulation

class NewActionModulation(Frame):
    def __init__(self,parent):
        Frame.__init__(self,parent)
        self.parent = parent
        self.initUI()
        
    def initUI(self):
         self.parent.title("Test")
         self.frameTab = Frame(self, relief=RAISED,borderwidth=1)
         self.frameTab.grid(row=3,column=0,columnspan=4)
         self.grid(row=0,column=0)
         self.frameTab.grid(row=0,column=0)
         self.note_book = Notebook(self.frameTab)
         self.specific_actions = ActionModulation.ActionModulation(self.note_book)
         self.note_book.add(self.specific_actions.getFrame(),text='specific actions')
         self.general_actions = GeneralActionModulation.GeneralActionModulation(self.note_book)
         self.note_book.add(self.general_actions.getFrame(),text='general actions')
         self.note_book.grid(row=0,column=0)
         
         self.frameButtons = Frame(self, relief=RAISED,borderwidth=1)
         self.frameButtons.grid(row=3,column=0,columnspan=4)
         self.buttonReset = Button(self.frameButtons,text="Reset")
         self.buttonReset.grid(row=0,column=0)
         self.buttonAbort = Button(self.frameButtons,text="Abort")
         self.buttonAbort.grid(row=0,column=1)
         self.buttonStop = Button(self.frameButtons,text="Stop")
         self.buttonStop.grid(row=0,column=2)
         self.buttonSendAction = Button(self.frameButtons,text="Send Action")
         self.buttonSendAction.grid(row=0,column=4)
         self.buttonSendEmotion = Button(self.frameButtons,text="Send Emotion")
         self.buttonSendEmotion.grid(row=0,column=5)

    def getCurrentTab(self):
        return self.note_book.index(self.note_book.select())
      
    def getFirstTab(self):
        return self.specific_actions
    
    def getSecondTab(self):
        return self.general_actions
    
    def getButtonSendAction(self):
        return self.buttonSendAction
    
    def getButtonSendEmotion(self):
        return self.buttonSendEmotion
    
    def getButtonReset(self):
        return self.buttonReset
    
    def getButtonAbort(self):
        return self.buttonAbort

    def getButtonStop(self):
        return self.buttonStop