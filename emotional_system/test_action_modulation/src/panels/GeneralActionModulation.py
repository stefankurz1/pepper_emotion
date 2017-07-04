from Tkinter import Tk, Text, RAISED, Label
from ttk import Frame

class GeneralActionModulation(Frame):
    def __init__(self,parent):
        Frame.__init__(self,parent)
        self.parent = parent
        self.initUI()
        
    def initUI(self):
        self.frame = Frame(self.parent, relief=RAISED,borderwidth=1)
        self.frame_text = Frame(self.frame, relief=RAISED,borderwidth=1)
        self.frame_text.grid(row=0 , column=0)
        self.area = Text(self.frame_text)
        self.area.grid(row=0, column=0, columnspan=1, rowspan=1, 
            padx=5)
        
    def getFrame(self):
        return self.frame
    
    def getText(self):
        return self.area.get('1.0', 'end')