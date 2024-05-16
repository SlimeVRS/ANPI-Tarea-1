import numpy as np
import sympy as sp
import pandas as pd

def NR_iteration(f, x, x0):
    n = len(f)
    ruletable = {x[i]:x0[i] for i in range(n)}

    jac = sp.Matrix([[fj.diff(xi) for xi in x] for fj in f])

    print("Matriz jacobiana:")
    print(jac)

    dx = jac.inv() * sp.Matrix(f)
    print("Matriz dx:")
    print(dx)

    return np.array([-i.subs(ruletable) for i in dx]).astype(np.float64)

def newton_raphson(f, x, x0, iterMax, tol):
    Ertable = [1]
    xtable = np.array([x0])
    i = 0
    while Ertable[i] > tol and i <= iterMax:
        deltax = NR_iteration(f, x, xtable[i])
        x_1 = xtable[i] + deltax
        xtable = np.vstack((xtable, x_1))
        er = np.linalg.norm(xtable[i+1] - xtable[i])/np.linalg.norm(xtable[i+1])
        Ertable =np.vstack((Ertable, er))
        i += 1
    
    T = pd.DataFrame([[i + 1, xtable[i, 0], xtable[i, 1],
                       xtable[i + 1, 0], xtable[i + 1, 1],
                       Ertable[i + 1][0]] for i in range(len(Ertable) - 1)],
                       columns=["Iteration", "x1_in", "x2_in", "x1_out", "x2_out", "er"])
    return(T)

x1 = sp.symbols("x1")
x2 = sp.symbols("x2")
f = [x1**2 + x1*x2 - 10,
     x2 + 3*x1*x2**2 - 57]
x = [x1, x2]
x0 = [1.5, 3.5]
print(newton_raphson(f, x, x0, 50, 1e-5))
print(sp.nsolve(f, x, x0))