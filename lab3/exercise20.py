# Author: Wavator

from math import e

EPS = 1e-8


# This is Adaptive Simpson algorithm
class Simpson:

    def __init__(self, fx):
        self.f = fx

    def simpson(self, a, b):
        c = a + (b - a) / 2.0
        return (self.f(a) + 4.0 * self.f(c) + self.f(b)) * (b - a) / 6.0

    def asr(self, a, b, eps, left_a):
        c = a + (b - a) / 2
        l = self.simpson(a, c)
        r = self.simpson(c, b)
        return l + r + (l + r - left_a) / 15. if abs(l + r - left_a) <= 15 * eps else \
            self.asr(a, c, eps / 2, l) + self.asr(c, b, eps / 2, r)

    def _asr(self, a, b, eps):
        return self.asr(a, b, eps, self.simpson(a, b))

    def solve(self, l, r):
        return self._asr(l, r, EPS)


if __name__ == '__main__':
    def f(x):
        return pow(6 - pow(e, 2 * x), 2)
    print(Simpson(f).solve(0, 1))

# 11.065200914703283
