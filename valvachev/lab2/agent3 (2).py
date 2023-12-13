import matplotlib.pyplot as plt

regions = []

with open('./file.txt', 'r') as f:
    id = int(f.readline())
    unit_count = int(f.readline())
    for _ in range(int(unit_count)):
        region = f.readline().split(' ')
        regions.append((region[0], int(region[1])))
    mission_percent = int(f.readline())
    correct_interval = f.readline().split()
    broken_interval = f.readline().split()
    incorrect_interval = f.readline().split()


statistics = []

good_shop_counts = 0
warning_shop_count = 0
bad_shop_count = 0
    
SHOPS_COUNT = 0

for region in regions:
    region_addr = region[0]
    region_count = region[1]
    SHOPS_COUNT += region_count

    statistics.append((region_addr, []))
    with open(f'./{region_addr}' + '.txt', 'r') as f:
        for _ in range(region_count):
            state = (f.readline().split(' '))
            statistics[-1][1].append(float(state[1]))
    
STATE_TYPES = ['поощрение', 'предупреждение', 'увольнение']

results = []

for region, states in statistics:
    id = 0
    results.append((region, []))
    for state in states:
      if state >= float(correct_interval[0]) and state <= float(correct_interval[1]):
          result = STATE_TYPES[0]
          good_shop_counts += 1
      elif state >= float(broken_interval[0]) and state <= float(broken_interval[1]):
          result = STATE_TYPES[1]
          warning_shop_count += 1
      elif state >= float(incorrect_interval[0]) and state <= float(incorrect_interval[1]):
          result = STATE_TYPES[2]
          bad_shop_count += 1
      results[-1][1].append((id, result))
      id += 1


with open('./counts' + '.txt', 'w') as f:
        f.write('Нужно поощрить: ' +  str(good_shop_counts) + '\n')
        f.write('Нужно предупредить: ' + str(warning_shop_count) + '\n')
        f.write('Уволить: ' +  str(bad_shop_count) + '\n')

with open('./mission_completed' + '.txt', 'w') as f:
        if (int(mission_percent) < 100 * good_shop_counts / SHOPS_COUNT):
            f.write('Миссия выполняется, т.к. кол-во прибыльных магазинов больше экспертной оценки: ' + str(mission_percent))
            f.write('Исправно: ' +  str(good_shop_counts) + '\n')
            f.write('Необходимо предупредить: ' + str(warning_shop_count) + '\n')
            f.write('Необходимо Уволить: ' +  str(bad_shop_count) + '\n')
        else: 
            f.write('Миссия не выполняется, т.к. кол-во прибыльных магазинов меньше экспертной оценки: ' + str(mission_percent))
            f.write('Исправно: ' +  str(good_shop_counts) + '\n')
            f.write('Необходимо предупредить: ' + str((float(mission_percent) / 100 - good_shop_counts / SHOPS_COUNT ) * SHOPS_COUNT) + '\n')
            f.write('Необходимо Уволить: ' +  str(bad_shop_count) + '\n')
        

with open('./results' + '.txt', 'w') as f:
        i = 0
        for region in regions:
          f.write(region[0] + '\n')

          for j in range(region[1]):
              f.write(str(results[i][1][j]) + '\n')
          i += 1
          

categories = STATE_TYPES
values = [good_shop_counts, warning_shop_count, bad_shop_count]

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