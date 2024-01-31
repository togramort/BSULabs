import random
from colorama import Fore

print(Fore.GREEN + "АНАЛИТИКА СТАБЛИЛЬНОСТИ БАНКА\n")

id_bank = input(Fore.WHITE + "Введите идентификатор банка\n")
amount_unit = input("Введите число подразделений банка\n")

print("Подразделения присылают данные в виде (идентификатор, прибыль, коммуникации)\n")
print(f"пример: subunit #1 = ({1}, {100}, {1})")

sum_yesterday = 0
sum_today = 0
amount_unit = int(amount_unit) + 1


for j in range(1, amount_unit):
    sum_yesterday += random.randint(0, 200)

print("*********************************************************\n")
print("СОСТОЯНИЕ         |      d(ПРИБЫЛЬ)       |      РЕШЕНИЕ\n")
print("*********************************************************\n")
for i in range(2, 9):
    for j in range(1, amount_unit):
        sum_today += random.randint(0, 200)
    print(Fore.WHITE + f"{i - 1}.12.2023")
    if (sum_today > sum_yesterday):
        print(Fore.GREEN + f"стабильность высокая |          {sum_today - sum_yesterday}        |      выдать премию в размере {(sum_today - sum_yesterday)*0.1} у.е.\n")
    elif(sum_today == sum_yesterday):
        print(Fore.YELLOW + f"стабильность под угрозой |          {sum_today - sum_yesterday}        |      предупредить руководство\n")
    elif(sum_today < sum_yesterday):
        print(Fore.RED + f"банк не стабилен    |          {sum_today - sum_yesterday}        |      сменить руководство банка\n")
    else:
        print("error")
    sum_yesterday = sum_today
    sum_today = 0
