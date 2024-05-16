import numpy as np
import sympy as sp
import pandas as pd
import math

def newton_raphson(f, x, x0, iterMax, tol):
    Ertable = [1]
    xtable = np.array([x0])
    i = 0
    while Ertable[i] > tol and i <= iterMax:
        deltax = NR_iteration(f, x, xtable[i])
        x_1 = xtable[i] + deltax
        xtable = np.vstack((xtable, x_1))
        er = np.linalg.norm(xtable[i + 1] - xtable[i])/np.linalg.norm(xtable[i + 1])
        Ertable = np.vstack((Ertable, er))
        i += 1
    
    # Crear el dataframe de forma dinamica segun la cantidad de variables

    col_names = ["Iteracion"] + [f"x{i+1}_in" for i in range(len(x))] +[f"x{i+1}_out" for i in range(len(x))] + ["er"]
    data = []

    for i in range(len(Ertable) - 1):
        row = [i + 1] + xtable[i].tolist() + xtable[i + 1].tolist() + [Ertable[i + 1][0]]
        data.append(row)

    T = pd.DataFrame(data, columns=col_names)
    return T

def NR_iteration(f, x, x0):
    n = len(f)
    ruletable = {x[i] : x0[i] for i in range(n)}

    # Calculo de la matriz Jacobiana
    jac = sp.Matrix([[fj.diff(xi) for xi in x] for fj in f])
    jac_numeric = np.array(jac.subs(ruletable)).astype(np.float64)

    # Calculo de los valores de f
    f_numeric = np.array([fj.subs(ruletable) for fj in f]).astype(np.float64)

    # Calculo de la solucion al sistema de ecuaciones tal que jac_numeric * dx = -f_numeric
    dx = np.linalg.solve(jac_numeric, -f_numeric)

    return dx

x1, x2 = sp.symbols("x1 x2")
f = [sp.sympify('x1**2+x2**2-1'), sp.sympify('x1**2-x2**2+0.5')]
x = [x1, x2]
x0 = [0.7, 1.2]
print(newton_raphson(f, x, x0, 50, 1e-5))
print(sp.nsolve(f, x, x0))