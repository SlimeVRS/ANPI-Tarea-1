# ##############################################################################
#
#  ███████╗   ███████║   ██████║
#            ██╔══╝   ██║                     ██║
#            ██║           ███████║   ██║
#            ██║           ██║                     ██║
#            ██║           ███████║   ██████║
#
###############################################################################
# Authors:   Juan Rodriguez Montero
# Course: ANPI
# Problem Description:
#   We are solving for the volume in the context of Van der Waals’ equation,
#   a mathematical expression that models the behavior of real gases. This equation
#   considers deviations from the ideal gas law by accounting for the finite volume
#   of gas molecules and interactions between them, such as attractive and repulsive forces.
#
# Constants:
#   - n: Number of moles of gas.
#   - R: Gas constant (0.0820578).
#   - T: Temperature.
#   - a: Constant representing attractive forces between gas molecules.
#   - b: Constant representing repulsive forces between gas molecules.
#
# Variables:
#   - x: The variable representing the volume of the gas.
#   - a, b, n, R, T: Parameters of the Van der Waals equation.
#
###############################################################################
from sympy import Symbol, lambdify
from functions.bisection import  bisection
from functions.false_position import  false_position
from functions.muller import muller_method

x = Symbol('x')
n = 10
R = 0.0820578
T = 58
a = 1.36
b = 0.0318

expr = (n * R * T) / (x - n * b) - (a * n**2) / x**2
func = lambdify(x, expr)

if __name__ == '__main__':
    result1 = bisection(1, 100, func, 1e-4, 1000)
    result2 = false_position(1, 100, func, 1e-4, 1000)
    result3 = muller_method(1, 100, func, 1e-4,1000)

    formatted_result1 = {
        'Approximation': round(result1['Approximation'], 6),
        'Error': round(float(result1['Error']), 6),
        'Iterations': result1['Iterations']
    }

    formatted_result2 = {
        'Approximation': round(float(result2['Approximation']), 6),
        'Error': round(float(result2['Error']), 6),
        'Iterations': result2['Iterations']
    }

    formatted_result3 = {
        'Approximation': round(float(result3['Approximation']), 6),
        'Error': round(float(result3['Error']), 6),
        'Iterations': result3['Iterations']
    }

    print("Bisection Method:")
    for key, value in formatted_result1.items():
        print(f"{key}: {value}")

    print("\nFalse Position Method:")
    for key, value in formatted_result2.items():
        print(f"{key}: {value}")

    print("\nMuller Method:")
    for key, value in formatted_result3.items():
        print(f"{key}: {value}")


