import os
from PIL import Image
import tkinter as tk
from tkinter import ttk
from tkinter import filedialog

def main():
    root = tk.Tk()
    
    root.withdraw()
    folder_name = filedialog.askdirectory(initialdir='../../../../')
    root.deiconify()

    photos = []

    check = True
    for root_folder, dirs, files in os.walk(folder_name):
        for file in files:
            check = False
            image = Image.open(folder_name + '/' + file)
            if not image.verify:
                continue
            photos.append((file, ('x').join(map(str, image.size)), image.info.get('dpi'), image.mode, image.info.get('compression'), image.info.get('model'), image.info.get('datetime')))
    if check:
        print('\nThere are no any files in the folder "' + folder_name + '", try other folder...')
        root.destroy()
        return


    root.title("info")
    root.geometry("1400x500") 

    columns = ("file", "size", "dpi", "color_depth", "compression", "model", "date")
    
    tree = ttk.Treeview(columns=columns, show="headings")
    tree.pack(fill=tk.BOTH, expand=1)
    
    tree.heading("file", text="File:")
    tree.heading("size", text="Size(in px):")
    tree.heading("dpi", text="DPI:")
    tree.heading("color_depth", text="Color depth:")
    tree.heading("compression", text="Compression:")
    tree.heading("model", text="Model:")
    tree.heading("date", text="Date:")
    
    for image in photos:
        tree.insert("", tk.END, values=image)
    
    root.mainloop()


if __name__ == '__main__':
    main()
