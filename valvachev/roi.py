from colorama import Fore

print("******************************************************\n")
print(Fore.GREEN + "           СИСТЕМА МОДЕЛИРОВАНИЯ РОЯ\n")
print(Fore.WHITE + "******************************************************\n")

cont = True
while(cont):
    id = input(Fore.WHITE + "введите id роя\n")
    # amount_ved = input("введите количество ведущих:\n")
    # amount_vedm = input("введите количество ведомых:\n")
    cargo = input("сколько минимально груза нужно перевезти для выполнения миссии?\n")
    distance = input("введите расстояние на которое нужно доставить груз:\n")
    print("введите условие окружающей среды (от 0 до 5):\n")

    print("*********************************************************\n")
    print("ОЦЕНКА           |      УСЛОВИЕ       \n")
    print("*********************************************************\n")
    print(Fore.GREEN + "0               |        идеальные погодные условия          \n")
    print(Fore.GREEN + "1               |        средние погодные условия        \n")
    print(Fore.YELLOW + "2               |        средняя охота на дронов          \n")
    print(Fore.YELLOW + "3               |        плохие погодные условия          \n")
    print(Fore.RED + "4               |        активная охота на дронов          \n")
    print(Fore.RED + "5               |        активная охота на дронов и катастрофические погодные условия        \n" + Fore.WHITE)
    cond = input()

    print(Fore.WHITE + "в рамках данных условий возможны следующие исходные данные для выполнения миссии:\n")
    delta = float(int(cargo) * int(distance) / 100)
    cargo = float(cargo)
    cond = int(cond)
    drones = -1
    if (cond == 0):
        drones = cargo * 1.1 + delta * 0.05
    elif (cond == 1):
        drones = cargo * 1.3 + delta * 0.1
    elif (cond == 2):
        drones = cargo * 1.5 + delta * 0.2
    elif (cond == 3):
        drones = cargo * 1.7 + delta * 0.4
    elif (cond == 4):
        drones = cargo * 2.0 + delta * 0.5
    elif (cond == 5):
        drones = cargo * 2.5 + delta * 0.7

    print("всего необходимо " + str(drones) + " дронов\n")

    ved = -1
    vedm = -1
    if (cond == 0):
        ved = drones * 0.05
        vedm = drones * 0.95
    elif (cond == 1):
        ved = drones * 0.1
        vedm = drones * 0.9
    elif(cond == 2):
        ved = drones * 0.2
        vedm = drones * 0.8
    elif (cond == 3):
        ved = drones * 0.3
        vedm = drones * 0.7
    elif (cond == 4):
        ved = drones * 0.4
        vedm = drones * 0.6
    elif (cond == 5):
        ved = drones * 0.5
        vedm = drones * 0.5
    
    print("из которых ведущих должно быть " + str(ved) + " и ведомых должно быть " + str(vedm) + "\n")
    


    temp = input(Fore.WHITE + "Хотите продолжить? (Y - да, N or Q - нет)\n")
    if temp.upper() == 'Q' or temp.upper() == 'N':
        cont = False
