#!/usr/bin/env python2
# encoding: utf-8

from __future__ import print_function
from Tkinter import *
import ttk

class DCSGui(object):
    def __init__(self, tkroot):
        self.root = tkroot
        self.frame = Frame(self.root)
        self.eventDictionary = {}

        self.create_DCSentries()
        self.create_DCSdata()
        self.frame.grid(column=0, row=0)
    def create_DCSentries(self):
        self.entryTree = ttk.Treeview(self.frame)
        self.entryTree.grid(column=0, row=0)
        self.entryTree.bind("<Double-1>", self.entryTreeOnDoubleClick)

    def create_DCSdata(self):
        self.dataTree = ttk.Treeview(self.frame)
        self.dataTree.grid(column=1, row=0)

    def createEntries(self, entries, parent="", fullName=""):
        count = 0
        for key,value in entries.items():
            fullNameLocal = "%s/%s"%(fullName,key)
            self.entryTree.insert(parent, count, fullNameLocal, text=key)
            count += 1
            if type(value) == type({}):
                self.createEntries(value, fullNameLocal, fullNameLocal)
            else:
                print("Creating callback: ", fullNameLocal)
                self.eventDictionary[fullNameLocal] = self.visualizeData

    def entryTreeOnDoubleClick(self, event):
        item = self.entryTree.identify('item', event.x, event.y)
        self.reactToEventOnItem(item)
    
    def reactToEventOnItem(self, item):
        if item in self.eventDictionary:
            self.eventDictionary[item](item)

    def visualizeData(self, keyName):
        dataFormat = ["Key", "Value1", "Value2"]
        data = {
            "/entry1/entry11/entry111": ["Ak1 v11 v12", "Ak2 v21 v22","Ak3 v31 v32","Ak4 v41 v42","Ak5 v51 v52"],
            "/entry1/entry12": ["Bk1 v11 v12", "Bk2 v21 v22","Bk3 v31 v32","Bk4 v41 v42","Bk5 v51 v52"],
            "/entry2": ["CkA v1A v1A", "Ck2 v21 v22","Ck3 v31 v32","Ck4 v41 v42","Ck5 v51 v52"],
            "/entry3": ["Dk1 v11 v12", "Dk2 v21 v22","Dk3 v31 v32","Dk4 v41 v42","Dk5 v51 v52"],
        }
        
        self.createData(dataFormat, data[keyName])
        

    def createData(self, dataFormat, data):
        self.dataTree["columns"] = dataFormat[1:]
        self.dataTree.heading("#0", text=dataFormat[0])
        for entry in dataFormat[1:]:
            self.dataTree.column(entry, width=100)
            self.dataTree.heading(entry, text=entry)
    
        self.dataTree.delete(*self.dataTree.get_children())
                    
        count = 1
        for entryVals in data:
            entries = entryVals.split()
            self.dataTree.insert("", count, text=entries[0], values=entries[1:])
            count += 1


root = Tk()

app = DCSGui(root)

info = {"entry1": {"entry11": {"entry111": ""}, "entry12": ""}, "entry2": "", "entry3": ""}
app.createEntries(info)

#dataFormat = ["Key", "Value1", "Value2"]
#data = ["k1 v11 v12", "k2 v21 v22","k3 v31 v32","k4 v41 v42","k5 v51 v52"]
#app.createData(dataFormat, data)

root.mainloop()