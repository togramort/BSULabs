import random 
import time
from colorama import Fore

count_cars = input("введите количество тракторов\n")
distance = input("введите какое расстояние должно быть между тракторами\n")

total_route = random.randint(1, 10)
amount = random.randint(2, 4)
print ("тракторы определиши ширину поля равной " + str(total_route) + "км\n")
print("тракторы определили количество проходок равной " + str(amount) + "\n")
print ("тракторы начали работу...\n")
time.sleep(1)

for i in range(1, amount + 1):
    for i in range (1, total_route + 1):
        choice_situation = random.randint(1, 4)
        if (choice_situation == 1):
            print("показатели всех датчиков в порядке. тракторы продолжают работу...\n")
        elif (choice_situation == 2):
            print("показатели всех датчиков в порядке. тракторы продолжают работу...\n")
        elif (choice_situation == 3):
            lost_car = random.randint(1, int(count_cars) - 1)
            lost_dist = random.randint(1, int(distance) / 2)
            print(Fore.RED + "тракторы начали сближаться! срочно скорректировать движение!!\n")
            print(Fore.WHITE + "трактор №" + str(lost_car) + " сместился на " + str(lost_dist) + "\n")
        elif (choice_situation == 4):
            print ("трактор №" + str(count_cars) + "сломался! отправляем координаты сломанного трактора для эвакуации/замены\n")      
        time.sleep(1)  

    print("тракторы дошли до заданной цели\n")
    time.sleep(1)
    print("тракторы развернулись\n")

print("тракторы завершили работу...")