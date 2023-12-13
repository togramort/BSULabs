import random

regions = []
with open('./file.txt', 'r') as f:
    id = int(f.readline())
    unit_count = int(f.readline())
    for _ in range(int(unit_count)):
        region = f.readline().split(' ')
        regions.append((region[0], int(region[1])))


for region in regions:
    region_addr = region[0]
    region_count = region[1]
    with open(f'./{region_addr}' + '.txt', 'w') as f:
        for shop_id in range(region_count):
            state = round(random.random(), 2)
            f.write(str(shop_id) + ' ' + str(state) + '\n')

