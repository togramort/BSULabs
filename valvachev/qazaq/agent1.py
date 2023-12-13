print('Введите id')
id = input()
print('Адрес')
adr = input()
print('Кол-во полей')
field_count = input()
print('Кол-во панелей в поле')
panels_count = input()
print('Введите типы воздействия')
impact_type = input()
print('Введите минимальный процент для выполнения миссии')
mission_percent = input()

print('Введите диапазон исправного состояния')
correct = input().split(' ')

print('Введите диапазон ремонтного состояния')
broken = input().split(' ')

print('Введите диапазон неисправного состояния')
incorrect = input().split(' ')


with open('./file.txt', 'w') as f:
    f.write(str(id) + ' ' + str(adr) + ' ' +  str(field_count) + ' ' + str(panels_count) + ' ' + str(impact_type) + '\n')
    f.write(str(mission_percent) + '\n')
    f.write(str(correct[0]) + ' ' + str(correct[1]) + '\n')
    f.write(str(broken[0]) + ' ' + str(broken[1]) +'\n')
    f.write(str(incorrect[0]) + ' ' + str(incorrect[1]) +'\n')