#Toluwanimi Salako 30417945
import tkinter

class MsgBox:
    
    def __init__(self, title, message):
        self.title = title
        self.message = message
        
    def _closeDialog(self):
        self.msg.destroy()
    def showDialog(self):
        self.msg = tkinter.Tk()
        self.msg.title(self.title)
        self.msg.resizable(width = False, height = False)
        tkinter.Label(self.msg, text = self.message).grid(row = 0)
        tkinter.Button(self.msg, text = "OK", command = self._closeDialog).grid(row = 1)
        self.msg.mainloop()

    