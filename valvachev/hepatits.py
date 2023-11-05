from colorama import Fore

def count(choice):
    global pos, neg
    if choice.upper() == 'Y':
        pos += 1
    elif choice.upper() == 'N':
        neg += 1

print("******************************************************\n")
print(Fore.GREEN + "           СИСТЕМА ДИАГНОСТИКИ ГЕПАТИТА\n")
print(Fore.WHITE + "******************************************************\n")
print("Пожалуйста ответьте на вопросы ниже Y если ваш ответ положительный и N если ваш ответ отрицательный\n")

cont = True
while(cont):
    pos = 0
    neg = 0
    id = input(Fore.WHITE + "введите id персонала\n")
    skin = input("у вас желтый цвет кожи?\n")
    count(skin)
    weakness = input("вы ощущаете общую слабость?\n")
    count(weakness)
    headache = input("у вас есть головная боль?\n")
    count(headache)
    temperature = input("ваша температура тела больше 37.5?\n")
    count(temperature)
    blood = input("ваш уровень лейкоцитов снижен?\n")
    count(blood)

    if (neg + pos != 5):
        print("неверно указаны данные, пройдите опросник заново\n")
    else:
        print("*********************************************************\n")
        print("СОСТОЯНИЕ           |      СИМПТОМЫ       |      ПРЕПАРАТ\n")
        print("*********************************************************\n")
        if(neg == 5 and pos == 0):
            print(Fore.GREEN + "здоров              |        нет          |         4\n")
        elif(neg == 4 and pos == 1):
            print(Fore.YELLOW + "частично здоров     |        20%          |         3\n")
        elif(neg == 3 and pos == 2):
            print(Fore.YELLOW + "средней тяжести     |        40%          |         2\n")
        elif(neg == 2 and pos == 3):
            print(Fore.YELLOW + "средней тяжести     |        60%          |         2\n")
        elif(neg == 1 and pos == 4):
            print(Fore.RED + "болен               |        80%          |         1\n")
        elif(neg == 0 and pos == 5):
            print(Fore.RED + "умирает             |        100%         |         1\n")
    temp = input(Fore.WHITE + "Хотите продолжить? (Y - да, N or Q - нет)\n")
    if temp.upper() == 'Q' or temp.upper() == 'N':
        cont = False
