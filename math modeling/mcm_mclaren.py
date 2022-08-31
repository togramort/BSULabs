from math import sqrt

from scipy import stats


def mk(alpha: int, beta: int, m: int, n: int):
    arr = []
    for i in range(n):
        alpha = ((beta * alpha) % m)
        arr.append(alpha / m)

    for i in arr:
        print(i, end=' ')
    return arr


def maclaren(n: int, k: int, mk_arr: []):
    arr = []
    x = 7
    for i in range(n):
        x = (x * 17 + 13) % 113
        arr.append(x / 113)

    v = []
    for i in range(k):
        v.append(mk_arr[i])

    result = []
    for i in range(n):
        index = int(arr[i] * k)
        result.append(v[index])
        if i >= 952:
            v[index] = mk_arr[i]
        else:
            v[index] = mk_arr[i + k]

    for i in result:
        print(i, end=' ')

    return result


def kolmogorov(arr: [], n: int):
    arr.sort()
    d = 0.0
    for i in range(n):
        if d < abs((i + 1) / n - arr[i]):
            d = abs((i + 1) / n - arr[i])

    if sqrt(n) * d <= 1.63:
        print("\nkolmogorov criteria is passed!")
    else:
        print("\nkolmogorov criteria not passed :(")
    print(f"{sqrt(n) * d} <= 1.63")


def pierson(arr: [], n: int, partitions: int):
    arr.sort()
    step = 1 / partitions
    p = step
    current_level = step
    frequency = []
    count = 0

    for value in arr:
        if value - current_level > 1e-6:
            current_level += step
            frequency.append(count)
            count = 0
        count += 1
    frequency.append(count)

    result = 0
    for i in range(partitions):
        result += ((frequency[i] - n * p) ** 2) / (n * p)

    kvantil = stats.distributions.chi2.ppf(1 - 0.05, partitions)

    if result <= kvantil:
        print("\npierson criteria is passed!")
    else:
        print("\npierson criteria was not passed :(")

    print(f"{result} < {kvantil}")


def main():
    alpha = beta = 16387
    m = 2 ** 31
    n = 1000
    print("\nmk sheet")
    mk_arr = mk(alpha, beta, m, n)

    kolmogorov(mk_arr, n)
    pierson(mk_arr, n, 10)

    k = 48
    print("\nmaclaren sheesh")
    maclaren_arr = maclaren(n, k, mk_arr)

    kolmogorov(maclaren_arr, n)
    pierson(maclaren_arr, n, 10)


if __name__ == '__main__':
    main()
