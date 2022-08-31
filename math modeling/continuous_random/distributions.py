
import math

import random


class NormalDistribution:
    def __init__(self, m, s2):
        self.m_ = m
        self.s2_ = s2
        self.n_ = 24

    def rand(self):
        result = 0
        for _ in range(self.n_):
            result += random.random()
        result -= self.n_ / 2
        result *= math.sqrt(12 / self.n_)
        return result * math.sqrt(self.s2_) + self.m_


class ExponentialDistribution:
    def __init__(self, lyambda):
        self.lyambda = lyambda

    def rand(self):
        a = random.random()
        return -1/self.lyambda * math.log(a)


class CauchyDistribution:
    def __init__(self, c, m):
        self.c = c
        self.m = m
        self.normal_dist = NormalDistribution(0, 1)

    def rand(self):
        return self.m + self.c * math.tan(math.pi * ((self.normal_dist.rand() / self.normal_dist.rand()) - 0.5))
