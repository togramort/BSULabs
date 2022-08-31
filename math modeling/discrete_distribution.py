import math
import random
from scipy import stats


def binomial(m: int, p: float):
    result = random.random()
    i = 0
    border = (1 - p) ** (m - i)
    while result - border > 1e-6:
        i += 1
        border += math.comb(m, i) * (p ** i) * (1 - p) ** (m - i)
    return i, border


def negative_binomial(m: int, p: float):
    result = random.random()
    i = 0
    border = p ** m
    while result - border > 1e-6:
        i += 1
        border += math.comb(i + m - 1, i) * (p ** m) * ((1 - p) ** i)
    return i, border


def statistical_test(theory_expectation, theory_dispersion, random_values, probability):
    stat_expectation = sum(random_values) / len(random_values)
    print(f"Theory expectation = {theory_expectation}, practical expectation = {stat_expectation}")
    diff_sum = 0
    for i in range(len(random_values)):
        diff_sum += (random_values[i] - stat_expectation) ** 2
    stat_dispersion = (1 / (len(random_values) - 1)) * diff_sum
    print(f"Theory dispersion = {theory_dispersion}, practical dispersion = {stat_dispersion}")


def pierson_criteria(dist, is_negative, n=1000):
    size = len(set(dist))
    quantile = 0
    if is_negative:
        quantile = stats.distributions.chi2.ppf(1 - 0.05, size - 2)
    else:
        quantile = stats.distributions.chi2.ppf(1 - 0.05, size - 3)
    p = list()
    stat_lambda = sum(dist) / len(dist)
    stat_p = stat_lambda / 6
    m = 4
    p_p = 0.2
    for i in range(size):
        if is_negative:
            p.append(math.comb(i + m - 1, i) * (p_p ** m) * ((1 - p_p) ** i))
        else:
            p.append((math.factorial(size - 1) / (math.factorial(i) * math.factorial(size - i - 1))) * stat_p ** i * \
                     (1 - stat_p) ** (size - i - 1))

    first_kind_error = True
    for value in p:
        if not 0 < value < 1:
            first_kind_error = False
    print("First kind error is equal to 0.05 - ", first_kind_error)

    dist.sort()

    result = 0
    for i in range(len(set(dist))):
        result += ((dist.count(i) - n * p[i]) ** 2) / (n * p[i])

    if result <= quantile:
        print("Pierson criteria is passed!")
    else:
        print("Pierson criteria was not passed(")

    print(f"{result} < {quantile}")


def main():
    n = 10000
    negative = list()
    p_list = list()
    for _ in range(n):
        x, p = negative_binomial(4, 0.2)
        negative.append(x)
        p_list.append(p)

    print("negative binomial distribution")
    statistical_test(theory_expectation=16, theory_dispersion=80, random_values=negative, probability=p_list)
    pierson_criteria(negative, True, n)

    bin_distribution = list()
    p_list2 = list()
    for _ in range(n):
        x, p = binomial(6, 0.33)
        bin_distribution.append(x)
        p_list2.append(p)

    print("binomial distribution")
    statistical_test(theory_expectation=1.98, theory_dispersion=1.326, random_values=bin_distribution, probability=p_list2)
    pierson_criteria(bin_distribution, False, n)


if __name__ == '__main__':
    main()
