from colorama import Fore
import random
import time
import math

cont = True
while(cont):

    print("******************************************************\n")
    print(Fore.GREEN + "           СИСТЕМА КОНТРОЛЯ ПОДАЧИ ПЕЛЛЕТ\n")
    print(Fore.WHITE + "******************************************************\n")
    print("СОСТОЯНИЕ         |      ТЕМПЕРАТУРА       |      РЕШЕНИЕ\n")
    print("*********************************************************\n")
    print(Fore.RED + "печь охладилась   |          <50C          |      открыть подачу пеллет\n")
    print(Fore.WHITE + "печь работает     |          >50C          |      наблюдать\n")
    print("*********************************************************\n")
    print("СОСТОЯНИЕ         |      ТЕМПЕРАТУРА       |      РЕШЕНИЕ\n")
    print("*********************************************************\n")
    print(Fore.RED + "пеллет мало       |          <15 кг        |      оформить доставку пеллет\n")
    print(Fore.WHITE + "пеллет достаточно |          >15 кг        |      наблюдать\n")

    houses = [20, 35, 80, 62, 70, 67, 89]
    rand_area = random.randint(1, 7)
    rand_house = random.randint(1, houses[rand_area - 1])
    weight = random.uniform(0.0, 100.0)
    temperature_house = random.uniform(0.0, 30.0)

    print(f"информация о печи в {rand_area} районе в {rand_house} доме\n")
    for i in range (1, 13):
        print(Fore.WHITE + f"температура в доме {temperature_house} градусов")
        if (temperature_house >= 22.0):
            print("в доме тепло и уютно. печь топить не нужно\n")
            temperature_house -= random.uniform(2.5, 4.5)
        else:
            print(Fore.BLUE + "в доме прохладно... топим печь\n")
            time.sleep(2)
            print(Fore.WHITE + "проверка количества оставшихся пеллет...")
            print(f"осталось {weight} кг пеллет")
            if (weight <= 25.0):
                print(Fore.RED + f"срочно отправить уведомление о доставки пеллет в {rand_area} район в {rand_house} дом со склада №{rand_area} - {math.ceil(rand_house / 20)}\n")
                weight = 100.0
            elif(weight > 25.0):
                print(Fore.WHITE + f"пеллет осталось достаточно\n")
            temperature = random.uniform(0.0, 100.0)
            print(Fore.WHITE + f"текущая температура в печи {temperature} градусов")
            if (temperature <= 50.0):
                print(Fore.YELLOW + "состояние: печь охладилась\nрешение: отправка сигнала для подачи пеллет\n")
            elif (temperature > 50.0):
                print("состояние: печь топится\nрешение: наблоюдать\n")
            temperature_house += random.uniform(2.5, 4.5)
            weight -= random.uniform(5.1, 7.1)
        print(Fore.WHITE + "----------------------------------------\n")


    temp = input(Fore.WHITE + "Хотите продолжить? (Y - да, N or Q - нет)\n")
    if temp.upper() == 'Q' or temp.upper() == 'N':
            cont = False