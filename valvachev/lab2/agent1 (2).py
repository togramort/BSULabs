print('Введите id')
id = input()

print('Кол-во подразделений')
unit_count = input()

shops = []

for field in range(int(unit_count)):
  print('Введите регион')
  adr = input()
  print('Введите кол-во магазинов в регионе')
  shop = input()

  shops.append((adr, shop))

# print('Введите типы воздействия')
# impact_type = input()

print('Введите минимальный процент для выполнения миссии')
mission_percent = input()

print('Введите диапазон для поощрения')
correct = input().split(' ')

print('Введите диапазон для предупреждения')
broken = input().split(' ')

print('Введите диапазон увольнения')
incorrect = input().split(' ')


with open('./file.txt', 'w') as f:
    f.write(str(id) + '\n')
    f.write(str(unit_count) + '\n')
    for shop in shops:
      f.write(shop[0] + ' ' + shop[1]  + '\n')

    f.write(str(mission_percent) + '\n')
    f.write(str(correct[0]) + ' ' + str(correct[1]) + '\n')
    f.write(str(broken[0]) + ' ' + str(broken[1]) +'\n')
    f.write(str(incorrect[0]) + ' ' + str(incorrect[1]) +'\n')


