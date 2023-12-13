import random
input_info = []

with open('./file.txt', 'r') as f:
    input_info = f.readline().split()

id, adr, field_count, panels_count, impact_type = input_info

koef = 0
if impact_type.lower() == 'буря':
    koef = 0.2
if impact_type.lower() == 'наводнение':
    koef = 0.4
    
panels = []

with open('./fields' + '.txt', 'w') as f:
    for i in range(int(field_count)):
            for j in range(int(panels_count)):
                state = round(random.random() + koef, 2)
                if state > 1:
                    state = 1.0
                temp_id = i * int(panels_count) + j
                f.write(str(temp_id) + ' ' + str(state) + '\n')
