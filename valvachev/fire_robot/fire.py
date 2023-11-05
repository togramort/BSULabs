import random
import copy
from colorama import Fore
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
from pydub import AudioSegment
from pydub.playback import play
from playsound import playsound

print("*********************************************************\n")
print(Fore.GREEN + "           СИСТЕМА ДЕМОНСТРАЦИИ ДЕЯТЕЛЬНОСТИ РОБОТА\n")
print(Fore.WHITE + "*********************************************************\n")
print(              "СОСТОЯНИЕ            |      ПОКАЗАТЕЛИ       |      ДЕЙСТВИЕ\n")
print(Fore.GREEN +  "норма                |        0              |         ничего не делать\n")
print(Fore.YELLOW + "робот перегрелся     |        0.5            |         уводить робота\n")
print(Fore.RED +    "робот умер           |        1              |         плакать\n")


cont = True
while(cont):
    id = input(Fore.WHITE + "Введите id робота\n")
    state = random.randint(1, 3)
    if (state == 1):
        image = Image.open("D:\\program etc\\projects4\\valv\\tt\\rob1.jpg")
        image.show()
        playsound('D:/program etc/projects4/valv/tt/r1.mp3')
        print(Fore.GREEN + "робот в нормальном состоянии\n")
    elif (state == 2):
        image = Image.open("D:\\program etc\\projects4\\valv\\tt\\rob2.jpg")
        image.show()
        playsound('D:/program etc/projects4/valv/tt/r2.mp3')
        print(Fore.YELLOW + "робот перегрелся\n")
    elif (state == 3):
        image = Image.open("D:\\program etc\\projects4\\valv\\tt\\rob3.jpg")
        image.show()
        playsound('D:/program etc/projects4/valv/tt/r3.mp3')
        print(Fore.RED + "робот умер\n")