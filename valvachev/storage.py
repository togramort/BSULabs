from colorama import Fore
import random

def generate():
    choice = random.randint(1, 3)
    if (choice == 1):
        return Fore.GREEN + "ЗЕЛЕНЫЙ"
    elif (choice == 2):
        return Fore.YELLOW +"ЖЕЛТЫЙ"
    elif(choice == 3):
        return Fore.RED + "КРАСНЫЙ"
    else:
        return "error"

def solu(choice):
    print(choice)
    if (str(choice) == Fore.GREEN + "ЗЕЛЕНЫЙ"):
        return "НАБЛЮДАТЬ"
    elif (choice == Fore.YELLOW + "ЖЕЛТЫЙ"):
        return "НАБЛЮДАТЬ"
    elif (choice == Fore.RED + "КРАСНЫЙ"):
        return "ОТПРАВИТЬ СИСТЕМУ ДЛЯ ВОРОШЕНИЯ"
    else:
        return "error"
    
cont = True
while(cont):
    id = input("Ведите id хранилища\n")
    floor = input("Введите номер этажа\n")

    print("*********************************************************\n")
    print(Fore.GREEN + "           СИСТЕМА ОПРЕДЕЛИЕНИЯ ВЫДАЧИ КРЕДИТА\n")
    print(Fore.WHITE + "*********************************************************\n")
    print("СОСТОЯНИЕ           |      ПОКАЗАТЕЛИ       |      РЕШЕНИЕ\n")
    print(Fore.GREEN +"ЗЕЛЕНЫЙ             |         <15C          |      НАБЛЮДАТЬ\n")
    print(Fore.YELLOW +"ЖЕЛТЫЙ              |        15-30С         |      НАБЛЮДАТЬ\n")
    print(Fore.RED +"КРАСНЫЙ             |         >30C          |      ВОРОШИТЬ\n")

    temp = ""
    for i in range(1, 9):
        temp = generate()
        print(Fore.WHITE +"мини-склад №" + str(i) + " - показатель: " + temp + Fore.WHITE + " - решение: " + solu(temp) + Fore.WHITE)
    temp = input(Fore.WHITE + "Хотите продолжить? (Y - да, N or Q - нет)\n")
    if temp.upper() == 'Q' or temp.upper() == 'N':
        cont = False