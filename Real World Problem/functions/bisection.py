from sympy import  exp

"""
    Parameters:
        a, b: Interval [a, b] where the zero is sought.
        func: Text representing the function to which the zero is approximated.
        tol: Tolerance for approximation.
        iterMax: Maximum iterations to perform.

    Returns:
        A dictionary containing the approximation ('Approximation'), error ('Error'), and iterations ('Iterations').

    Raises:
        ValueError: If the bisection method does not converge within the maximum number of iterations
                    or if Bolzano's condition is not satisfied with the given data.
"""
def bisection(a, b, func, tol, iterMax):
    if func(a) * func(b) < 0:
        for k in range(iterMax):
            xk = (a + b) / 2
            if func(a) * func(xk) < 0:
                b = xk
            else:
                a = xk
            error = abs(func(xk))
            if error < tol:
                return {'Approximation': xk, 'Error': error, 'Iterations': k}
        raise ValueError("Bisection method did not converge within the maximum number of iterations.")
    else:
        raise ValueError("Bolzano condition is not satisfied")

expr = lambda x: exp(x) - x - 2
result = bisection(1, 2, expr, 1e-4, 1000)
print(result)