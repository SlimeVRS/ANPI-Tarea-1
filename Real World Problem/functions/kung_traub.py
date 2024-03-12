from sympy import Symbol, lambdify, diff

def kung_traub(func, approximation, tol, max_iter):
    """
    Parameters:
        func: Lambda function representing the nonlinear equation.
        x: Initial guess for the root.
        tol: Tolerance for approximation.
        max_iter: Maximum iterations to perform.

    Returns:
        A dictionary containing the approximation ('Approximation'), error ('Error'), and iterations ('Iterations').

    Raises:
        ValueError: If the method does not converge within the maximum number of iterations.
    """
    x_sym = Symbol('x')  # Symbolic variable
    derivative = diff(func(x_sym), x_sym)

    for k in range(max_iter):
        eval_func = func(approximation)
        eval_derivative = derivative.subs(x_sym, approximation)

        if abs(eval_derivative) < tol:
            raise ValueError("Kung-Traub's method: Derivative is too small.")

        delta = -eval_func / eval_derivative

        approximation += delta

        error = abs(delta)
        if error < tol:
            return {'Approximation': float(approximation), 'Error': float(error), 'Iterations': k}

    raise ValueError("Kung-Traub's method did not converge within the maximum number of iterations.")