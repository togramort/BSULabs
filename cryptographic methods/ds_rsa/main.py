import random


class Alice:
    def __init__(self):
        randoms = get_random_numbers(upper=10000000)
        self.p = random.choice(randoms)
        randoms.remove(self.p)
        self.q = random.choice(randoms)
        randoms.remove(self.q)
        self.n = self.p * self.q
        self.phi = (self.p - 1) * (self.q - 1)
        self.e = random.choice(randoms[:len(randoms) // 2])
        self.d = get_private_key(self.e, self.phi)

    def get_open_key(self):
        return self.e

    def check_sign(self, cipher):
        return pow(cipher, self.d, self.n)

    def print_state(self):
        print("Alice state:\np =", self.p, "\nq =", self.q, "\nphi =", self.phi, "\nModule =", self.n, "\nOpen key =",
              self.e, "\nSecret key =", self.d)


class Bob:
    def __init__(self, n, e):
        self.n = n
        self.e = e

    def sign(self, cipher):
        return pow(cipher, self.e, self.n)

    def print_state(self):
        print("Bob state:\nModule =", self.n, "\nOpen key =", self.e)


def get_random_numbers(upper: int):
    sieve = [True] * (upper + 1)
    for i in range(2, upper + 1):
        if sieve[i]:
            for j in range(i ** 2, upper + 1, i):
                sieve[j] = False

    randoms = [i for i in range(upper + 1) if sieve[i]]
    return randoms


def get_linear_decomposition_of_gcd(a, b, gcd):
    if a == 0:
        return 0, 1

    x, y = get_linear_decomposition_of_gcd(b % a, a, gcd)
    return y - (b // a) * x, x


def get_private_key(e, phi):
    x, y = get_linear_decomposition_of_gcd(e, phi, 1)
    return x % phi


def main():
    alice = Alice()
    bob = Bob(alice.n, alice.e)
    alice.print_state()
    print("\n")
    bob.print_state()
    print("\n")
    file = open("bin_message.txt")
    message = int(file.read(), 2)
    print(message)
    sign = bob.sign(message)
    print(sign)
    result = alice.check_sign(sign)
    print(result)
    if bin(result) == bin(message % alice.n):
        print("Sign confirmed")
    else:
        print("Sign not confirmed")


if __name__ == '__main__':
    main()
