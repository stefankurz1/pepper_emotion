#!/usr/bin/python

from Tkinter  import Tk, Frame, Label

class Example(Frame):
    
    def __init__(self,parent):
        Frame.__init__(self, parent, background="white")
        self.parent = parent
        self.initUI()
        
    def initUI(self):
        self.parent.title("Simple")
        self.grid(row=0,column=0)
        l= Label(self,text="xxxxxxxxxxxxxxxxxxx")
        l.grid(row=1,column=0)
        m= Label(self,text="yyyyyyyyyyyyyyyyyyy")
        m.grid(row=0,column=0)
        g= Label(self,text="<<<<<<<<<<<<<<<<")
        g.grid(row=0,column=1)
        
        
def main():
    root = Tk()
    app = Example(root)
    root.mainloop()
    
if __name__ == '__main__':
    main()