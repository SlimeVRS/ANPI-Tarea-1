import numpy as np
import sympy as sp

def muller_method(a, b, func_str, tol=1e-4, iterMax=1000):
    """
    Implementación del método de Muller para encontrar una raíz de la función dada.

    Args:
        a (float): Extremo izquierdo del intervalo.
        b (float): Extremo derecho del intervalo.
        func_str (str): Cadena que representa la función para la cual se busca la raíz.
                        Debe ser una expresión que Python pueda evaluar, por ejemplo: 'exp(-w) + (w/5) - 1'.
        tol (float): Tolerancia para la aproximación.
        iterMax (int): Máximo número de iteraciones.

    Returns:
        dict: Un diccionario conteniendo la aproximación de la raíz ('Approximation'), el error ('Error') y el número de iteraciones ('Iterations').

    Raises:
        ValueError: Si el método de Muller no converge dentro del número máximo de iteraciones.
    """
    w = sp.symbols('w')
    func_num = sp.lambdify(w, func_str)

    for k in range(iterMax):
        x0 = a
        x1 = (a + b) / 2
        x2 = b

        h1 = x1 - x0
        h2 = x2 - x1
        d1 = (func_num(x1) - func_num(x0)) / h1
        d2 = (func_num(x2) - func_num(x1)) / h2
        d = (d2 - d1) / (h2 + h1)

        b = d2 + h2 * d
        E = np.sqrt(b**2 - 4 * func_num(x2) * d)
        h = -2 * func_num(x2) / (b + E if abs(b + E) > abs(b - E) else b - E)
        p = x2 + h

        if abs(h) < tol:
            return {'Approximation': p, 'Error': abs(func_num(p)), 'Iterations': k + 1}

        a, b = b, p

    raise ValueError("Muller method did not converge within the maximum number of iterations.")

# Argumentos
a = 0.1
b = 10
func_str = 'exp(-w) + (w/5) - 1'

# Llamada a la función muller_method
result = muller_method(a, b, func_str)
print(result)
