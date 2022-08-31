import math
from math import exp, pi, sqrt
from random import uniform
import numpy as np
from matplotlib import pyplot as plt
from scipy import stats


def pierson_criteria(random_values, partitions: int, prob_func, *args):
    random_values.sort()
    step = (random_values[-1] - random_values[0]) / partitions
    current_level = random_values[0] + step
    n = 1000
    frequency = [0] * partitions
    counter = 0
    j = 0

    for value in random_values:
        if value - current_level > 1e-9:
            current_level += step
            frequency[j] = counter
            j += 1
            counter = 0
        counter += 1
    frequency[partitions - 1] = counter

    result = 0
    current_level = random_values[0]
    for i in range(partitions):
        low = prob_func(*args, current_level)
        up = prob_func(*args, current_level + step)
        p = up - low
        result += ((frequency[i] - n * p) ** 2) / (n * p)
        current_level += step

    kvantil = stats.distributions.chi2.ppf(1 - 0.05, partitions)

    if result <= kvantil:
        print("Pirson criteria is passed!")
    else:
        print("Pirson criteria was not passed(")

    print(f"{result} < {kvantil}")


def kolmogorov_criteria(random_values, partitions: int, prob_func, *args):
    critical_value = 1.36
    random_values.sort()
    step = (random_values[-1] - random_values[0]) / partitions
    current_level = random_values[0] + step
    n = 1000
    frequency = [0] * partitions
    counter = 0
    j = 0

    for value in random_values:
        if value - current_level > 1e-9:
            current_level += step
            frequency[j] = counter
            j += 1
            counter = 0
        counter += 1
    frequency[partitions - 1] = counter

    result = 0
    current_level = random_values[0]

    max_d = -1e10
    current_d = 0
    current_level = random_values[0]
    for i in range(partitions):
        low = prob_func(*args, current_level)
        up = prob_func(*args, current_level + step)
        p = up - low
        current_d = (frequency[i] / 1000) - p
        current_level += step
        if current_d > max_d:
            max_d = current_d

    if sqrt(n) * max_d <= critical_value:
        print("Kolmogorov criteria is passed!")
    else:
        print("Kolmogorov criteria was not passed(")
    print(f"{sqrt(n) * max_d} <= {critical_value}")


def moment_1(a):  # мат ожидание
    return sum(a) / len(a)


def moment_2(a):  # мат ожидание
    return moment_1(a ** 2) - moment_1(a) ** 2


def _comp(x1, x2):  # сравнение с истинным
    return abs(x1 - x2)


def func1(x, fi, k):
    return 1 / (fi * sqrt(2 * pi)) * exp(-(x - k) ** 2 / (2 * fi ** 2))


def simulation1(n, min_, max_):
    i = 0
    answer = []

    while (i < n):
        x = uniform(min_, max_)
        y = uniform(0, 1)
        if (y < func1(x, 1, -2)):
            answer.append(x)
            i += 1

    return answer


simulation1(10, -10, 10)


def print_graf(a, step, min_, max_):
    n = len(a)
    a.sort()

    keys = []
    values = []
    it = min_
    i = 0

    while (it < max_):
        temp = 0

        while (i < n and a[i] < it + step):
            temp += 1
            i += 1

        it += step

        keys.append(it)
        values.append(temp / n)

    plt.plot(keys, values)
    plt.show()


print_graf(simulation1(100000, -10, 10), 0.1, -10, 10)

m1 = moment_1(simulation1(100000, -10, 10))
m2 = moment_2(np.array(simulation1(100000, -10, 10)))

print("нормальное распределение")

print("практическое мат ожидание ", m1)
print("отлчиие от теоретического ", _comp(m1, -2))


print("практическая дисперсия ", m2)
print("отлчиие от теоретического ", _comp(m2, 1))


def func2(x, k, l):  # распределение вейбулла
    return (k/l) * (x/l)**(k-1) * exp(-(x/l)**k)


def simulation2(n, min_, max_):
    i = 0
    answer = []

    while (i < n):
        x = uniform(min_, max_)
        y = uniform(0, 1)
        if (y < func2(x, 0.5, 1)):
            answer.append(x)
            i += 1

    return answer


print_graf(simulation2(100000, 0, 10), 0.1, 0, 10)


def func3(x, k, s):  # логистическое распределение
    return exp(-(x - k) / s) / (s * (1 + exp(-(x - k) / s)) ** 2)


def simulation3(n, min_, max_):
    i = 0
    answer = []

    while (i < n):
        x = uniform(min_, max_)
        y = uniform(0, 1)
        if (y < func3(x, 0, 1.5)):
            answer.append(x)
            i += 1

    return answer


print_graf(simulation3(200000, -15, 15), 0.1, -15, 15)


m1 = moment_1(simulation3(100000, -15, 15))
m2 = moment_2(np.array(simulation3(100000, -15, 15)))

print("логичстическое распределение")

print("практическое мат ожидание ", m1)
print("отлчиие от теоретического ", _comp(m1, 0))


print("практическая дисперсия ", m2)
print("отлчиие от теоретического ", _comp(m2, (1.5 * pi) ** 2 / 3))


result = simulation3(1000, -15, 15)
pierson_criteria(result, 10, func3, 0, 1.5)
kolmogorov_criteria(result, 3000, func3, 0, 1.5)
