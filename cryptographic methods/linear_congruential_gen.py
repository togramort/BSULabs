import matplotlib.pyplot as plt

n = 2 ** 10


def gen(x, a, c, m):
    arr = []
    for i in range(n):
        x = (x * a + c) % m
        arr.append(x)
    plt.scatter(arr[0:len(arr) - 1], arr[1: len(arr)])
    if m < 103:
        plt.xlabel("first")
    else:
        plt.xlabel("second")
    plt.show()


def main():
    print("lets start with the first gen M < 103")
    x = 35
    a = 9 #b  8 (кратно 4) и p = 2
    c = 11 #с и м взаимно простые
    m = 64 #кратно 4
    print("x =", x, " a =", a, " c =", c, " m =", m)
    gen(x, a, c, m)
    print("now lets do sth harder gen M = 1031 * 2^5 * 18")
    x = 12032
    a = 1031 * 12 + 1 # = 12 373 b = 12 372 (кратно 4) и кратно всем простым делителям числа m : 2 3 1031
    c = 1093 #с и м взаимно простые
    m = 1031 * 18 * (2 ** 5) # = 593 856 (кратно 4)
    print("x =", x, " a =", a, " c =", c, " m =", m)
    gen(x, a, c, m)


if __name__ == '__main__':
    main()
