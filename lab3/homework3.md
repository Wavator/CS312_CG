##  homework3

11612908

赵宇

My core mathematical calculations are as follows:

![](C:\Users\Zhao\Desktop\计算机图形学\assignment3\homework_detail.jpg)

And my code is easily to understand:

It uses the basic functions in `glm`，and get the same answer as my calculation.

And a method is not included in `glm`， it is called `Adaptive Simpson integral method`.

The code of this algorithm can be found in my github(2 years before), now I provide a python version:

```python
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

```

use `solve(left_bound, right_bound)` to get the answer.



