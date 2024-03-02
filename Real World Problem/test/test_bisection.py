import unittest
from sympy import  exp
from functions.bisection import bisection

class TestBisectionMethod(unittest.TestCase):
    def test_correct_approximation(self):
        expr = lambda x: exp(x) - x - 2
        result = bisection(1, 2, expr, 1e-4, 1000)
        self.assertAlmostEqual(result['Approximation'], 1.14617919921875, delta=1e-4)

    def test_maximum_iterations(self):
        expr = lambda x: exp(x) - x - 2
        with self.assertRaises(ValueError):
            bisection(1, 2, expr, 1e-4, 5)  # Force the maximum iterations error

    def test_does_not_satisfy_bolzanos_condition(self):
        expr = lambda x: exp(x) + x + 2  # Expression to make it not satisfy Bolzano's condition
        with self.assertRaises(ValueError):
            bisection(1, 2, expr, 1e-4, 1000)

if __name__ == '__main__':
    unittest.main()

