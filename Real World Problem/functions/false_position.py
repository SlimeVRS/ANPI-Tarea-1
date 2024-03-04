from sympy import  exp, lambdify, Symbol

def false_position(a, b, func, tol, iterMax):
    """
    Parameters:
        a, b: Interval [a, b] where the zero is sought.
        func: Function to which the zero is approximated.
        tol: Tolerance for approximation.
        iterMax: Maximum iterations to perform.

    Returns:
        A dictionary containing the approximation ('Approximation'), error ('Error'), and iterations ('Iterations').

    Raises:
        ValueError: If the false position method does not converge within the maximum number of iterations.
    """
    if func(a) * func(b) >= 0:
        raise ValueError("Bolzano condition is not satisfied.")

    for k in range(iterMax):
        c = a - (func(a) * (a - b)) / (func(a) - func(b))

        if func(c) == 0:
            return {'Approximation': c, 'Error': 0, 'Iterations': k + 1}

        if func(a) * func(c) < 0:
            b = c
        else:
            a = c

        error = abs(func(c))

        if error < tol:
            return {'Approximation': c, 'Error': error, 'Iterations': k + 1}

    raise ValueError("False position method did not converge within the maximum number of iterations.")

x = Symbol('x')
expr = exp(x) - x - 2
func = lambdify(x, expr)
result_false_position = false_position(1, 2, func, 1e-4, 1000)
print(result_false_position)
