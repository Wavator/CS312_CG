from math import sin, e

EPS = 1e-8


## This is Adaptive Simpson algorithm
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
        return sin(x)


    def g(x):
        return pow(e, x)


    def h(x):
        return f(x) + g(x)


    F = Simpson(f)
    G = Simpson(g)
    H = Simpson(h)
    ans_f = F.solve(0, 1)
    ans_g = G.solve(0, 1)
    ans_h = H.solve(0, 1)
    print(ans_f, ans_g, ans_h)
    print(ans_h - ans_f - ans_g)
    print('Equal' if (abs(ans_h - ans_f - ans_g)) < EPS else 'Not Equal')

## 0.45969769413095374 1.7182818284607817 2.1779795225916914
## -4.418687638008123e-14
## Equal
## -4.4e-14 is very close to 0, as we have eps in the calculation, so -4.4e-14 can be eq to 0.
