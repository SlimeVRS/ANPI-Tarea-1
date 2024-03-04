from sympy import  exp, lambdify, Symbol

def secant(xk, ck, f, tol, iterMax):
    """
        Parameters:
            x0, x1: Initial points for the secant method.
            func: Text representing the function to which the zero is approximated.
            tol: Tolerance for approximation.
            iterMax: Maximum iterations to perform.

        Returns:
            A dictionary containing the approximation ('Approximation'), error ('Error'), and iterations ('Iterations').

        Raises:
            ValueError: If the secant method does not converge within the maximum number of iterations.
    """
    for k in range(iterMax):

        if f(xk) - f(ck) == 0:
            raise ValueError("Division by zero. Change initial points.")

        res = xk - (xk - ck) * f(xk) / (f(xk) - f(ck))

        error = abs(f(res))

        if error < tol:
            return {'Approximation': res, 'Error': error, 'Iterations': k + 1}

        ck = xk
        xk = res

    raise ValueError("Secant method did not converge within the maximum number of iterations.")

# Example usage:
x = Symbol('x')
expr = exp(x) - x - 2
func = lambdify(x, expr)
xk = 1
result_secant = secant(xk, xk-1, func, 1e-4, 1000)
print(result_secant)

#secant: {'Approximation': 1.1461929823006796, 'Error': 5.114804708661325e-07, 'Iterations': 5}
#bisection: {'Approximation': 1.14617919921875, 'Error': 3.0092328287878445e-05, 'Iterations': 13}
#false position: {'Approximation': 1.1461633234024051, 'Error': 6.416380087936879e-05, 'Iterations': 11}