import random
import copy
from colorama import Fore
import numpy as np
import matplotlib.pyplot as plt

predpr = input("Введите количество предприятий\n")
parameters = input("Введите количество параметров\n")
etalon = input("Введите количесвто эталонов\n")

print("*********************************************************\n")
print(Fore.GREEN + "           СИСТЕМА ОПРЕДЕЛИЕНИЯ ВЫДАЧИ КРЕДИТА\n")
print(Fore.WHITE + "*********************************************************\n")
print("СОСТОЯНИЕ           |      ПОКАЗАТЕЛИ       |      РЕШЕНИЕ\n")
v1 = []
v2 = [0] * int(parameters)

for i in range(int(etalon) - 1):
    choice = "oops"
    if i + 1 <= 5:
        choice = "\033[92mКрупный\033[0m"
    elif i + 1 <= 10:
        choice = "\033[93mСредний\033[0m"
    else:
        choice = "\033[91mНе выдавать\033[0m"
    print("*********************************************************\n")
    result = str(i + 1) + " | " + " ".join(str(round(x, 5)) for x in v2) + " | " + choice
    print(result)
    v1.append(copy.deepcopy(v2))
    for j in range(len(v2)):
        v2[j] += round((1 / (int(etalon) - 1)), 5)
print("*********************************************************\n")
v2 = [1] * int(parameters)
result = str(etalon) + " | " + " ".join(str(round(x, 5)) for x in v2) + " | " + "\033[91mНе выдавать\033[0m"
print(result)
v1.append(copy.deepcopy(v2))
print("*********************************************************\n")

vectors = []
for _ in range(int(predpr)):
    vector = [round(random.random(), 3) for _ in range(int(parameters))]
    vectors.append(vector)

for i, vector in enumerate(vectors, 1):
    print(f"Предприятие №{i}: {vector}")

good = 0
avg = 0
bad = 0
for i, vector in enumerate(vectors, 1):
    min = 1000
    num_of_etalon = 1000
    temp = sum(vector) / len(vector)
    for j, vect in enumerate(v1, 1):
        if abs(temp - vect[0]) < min:
            min = abs(temp - vect[0])
            num_of_etalon = j
    if num_of_etalon <= 5:
        good += 1
        #print(f"Предприятие №{i}:\nср. арф. = {temp}\nэталон №{num_of_etalon} \033[92mвыдать крупный кредит\033[0m")
        print(f"Предприятие №{i}:\nэталон №{num_of_etalon} \033[92mвыдать крупный кредит\033[0m")
    elif num_of_etalon <= 10:
        avg += 1
        print(f"Предприятие №{i}:\nэталон №{num_of_etalon} \033[93mвыдать средний кредит\033[0m")
    else:
        bad += 1
        print(f"Предприятие №{i}:\nэталон №{num_of_etalon} \033[91mне выдавать кредит\033[0m")

categories = ['Крупные кредиты', 'Средние кредиты', 'Отказ']
credits = [good, avg, bad]
colors = ['green', 'yellow', 'red']  

plt.bar(categories, credits, color=colors)

plt.xlabel('Статус')
plt.ylabel('Количество кредитов')
plt.title('Статистика одобрения кредитов')

for i, v in enumerate(credits):
    plt.text(i, v, str(v), ha='center', va='bottom')

plt.show()