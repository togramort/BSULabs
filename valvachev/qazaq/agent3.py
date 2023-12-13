import matplotlib.pyplot as plt

with open('./file.txt', 'r') as f:
    input_info = f.readline().split()
    mission_percent = f.readline()
    correct_interval = f.readline().split()
    broken_interval = f.readline().split()
    incorrect_interval = f.readline().split()

id, adr, field_count, panels_count, impact_type = input_info

states = []

with open('./fields' + '.txt', 'r') as f:
    for i in range(int(field_count)):
        for j in range(int(panels_count)):
            panel_id, state =  f.readline().split()
            states.append((panel_id, float(state)))
    


STATE_TYPES = ['исправно', 'ремонт', 'замена']

results = []

corrected_panels_count = 0
broken_panels_count = 0
incorrected_panels_count = 0

SUM = int(panels_count) * int(field_count)

for id, state in states:
    if state >= float(correct_interval[0]) and state <= float(correct_interval[1]):
        result = STATE_TYPES[0]
        corrected_panels_count += 1
    elif state >= float(broken_interval[0]) and state <= float(broken_interval[1]):
        result = STATE_TYPES[1]
        broken_panels_count += 1
    elif state >= float(incorrect_interval[0]) and state <= float(incorrect_interval[1]):
        result = STATE_TYPES[2]
        incorrected_panels_count += 1

    results.append((id, result))

with open('./counts' + '.txt', 'w') as f:
        f.write('исправно: ' +  str(corrected_panels_count) + '\n')
        f.write('ремонтопригодно: ' + str(broken_panels_count) + '\n')
        f.write('неисправно: ' +  str(incorrected_panels_count) + '\n')

with open('./mission_completed' + '.txt', 'w') as f:
        if (int(mission_percent) < 100 * corrected_panels_count / (int(panels_count) * int(field_count))):
            f.write('Миссия выполняется, т.к. кол-во исправных панелей больше экспертной оценки: ' + str(mission_percent))
            f.write('Исправно: ' +  str(corrected_panels_count) + '\n')
            f.write('Необходимо отремонтировать: ' + str(broken_panels_count) + '\n')
            f.write('Необходимо заменить: ' +  str(incorrected_panels_count) + '\n')
        else: 
            f.write('Миссия не выполняется, т.к. кол-во исправных панелей меньше экспертной оценки: ' + str(mission_percent))
            f.write('Исправно: ' +  str(corrected_panels_count) + '\n')
            f.write('Необходимо отремонтировать: ' + str((float(mission_percent) / 100 - corrected_panels_count / SUM ) * SUM) + '\n')
            f.write('Необходимо заменить: ' +  str(incorrected_panels_count) + '\n')
        

with open('./results' + '.txt', 'w') as f:
        for j in range(int(panels_count) * int(field_count)):
            f.write(str(results[j]) + '\n')



categories = STATE_TYPES
values = [corrected_panels_count, broken_panels_count, incorrected_panels_count]

# Создание фигуры и осей
fig, ax = plt.subplots()

colors = ['red', 'green', 'blue', 'orange']

# Создание столбчатой диаграммы
bars = ax.bar(categories, values, color=colors)


# Добавление значений на столбики
for bar in bars:
    height = bar.get_height()
    ax.text(bar.get_x() + bar.get_width() / 2, height, str(height), ha='center', va='bottom')

# Настройка внешнего вида диаграммы
ax.set_ylabel('Значения')
ax.set_title('Столбчатая диаграмма управляющих решений')
ax.set_xticks(categories)
# ax.set_xticklabels(categories, rotation=45)

# Отображение диаграммы
plt.show()