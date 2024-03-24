// Librerias
#include "funtras.h"
#include <boost/lexical_cast.hpp>
using namespace std;

// Variables globales
cpp_dec_float_50 pi_t = 3.14159265358979323846;
cpp_dec_float_50 tol = 1e-8;
int iterMax = 2500;

/*
* Funcion factorial
*/
cpp_dec_float_50 factorial(cpp_dec_float_50 x)
{
	if (x == 1 || x == 0)
		return 1;
	cpp_dec_float_50 temp = 1;
	temp = x * factorial(x - 1);
	return temp;
}

bool is_integer(cpp_dec_float_50 x)
{
	int redondeoAbajo = static_cast<int>(x);
	int redondeoArriba = static_cast<int>(x + 1);

	return x == redondeoAbajo && x + 1 == redondeoArriba;
}

/*
* Funcion auxiliar de divi_t que calcula el epsilon
*/
cpp_dec_float_50 divi_t_aux(cpp_dec_float_50 x)
{
	cpp_dec_float_50 eps = 2.2204e-16;
	if (0 < x && x < factorial(20))
		return pow(eps, 2);

	if (factorial(20) < x && x < factorial(40))
		return pow(eps, 4);

	if (factorial(40) < x && x < factorial(60))
		return pow(eps, 8);

	if (factorial(60) < x && x < factorial(80))
		return pow(eps, 11);

	if (factorial(80) < x && x < factorial(100))
		return pow(eps, 15);

	else
		return 0;
}

/*
* Funcion base de divi_t
*/
cpp_dec_float_50 divi_t(cpp_dec_float_50 x)
{
	try
	{
		if (0 != x)
		{
			x = abs(x);
			cpp_dec_float_50 xk = divi_t_aux(x);
			cpp_dec_float_50 xk_1 = 0;

			for (int i = 0; i < iterMax; i++)
			{
				xk_1 = xk * (2 - x * xk);

				if (abs(xk_1 - xk) < tol * abs(xk_1))
					break;

				xk = xk_1;
			}
			if (x < 0)
				return -xk;
			else
			{
				return xk;
			}
		}
		else
		{
			throw runtime_error(
				"Division por cero!"
			);
		}
	}	
	
	catch (const exception& e)
	{
		cout << "\nERROR: " << e.what() << endl;
	}
	return 0;
}

/*
* Funcion para calcular raiz cuadrada
*/
cpp_dec_float_50 root_t(cpp_dec_float_50 x, cpp_dec_float_50 y)
{
	try
	{
		bool entero = is_integer(y);
		if (0 < x && 2 < y && entero)
		{
			cpp_dec_float_50 xk = x * divi_t(2);
			cpp_dec_float_50 xk_1 = 0;

			for (int i = 0; i < iterMax; i++)
			{
				cpp_dec_float_50 numerator = pow(xk, y) - x;
				cpp_dec_float_50 denominator = y * pow(xk, y - 1);

				xk_1 = xk - (numerator * divi_t(denominator));

				if (abs(xk_1 - xk) < tol * abs(xk_1))
					break;

				xk = xk_1;
			}
			return xk;

			if (x < 0)
				throw runtime_error(
					"No se puede obtener una raiz de un numero negativo!"
				);
		}
		else
		{
			return power_t(x, divi_t(y));
		}
	}
	catch (const exception& e)
	{
		cout << "\nERROR: " << e.what() << endl;
	}
	return -1;
}

/*
* Funcion que calula una raiz dado el indice
*/
cpp_dec_float_50 sqrt_t(cpp_dec_float_50 x)
{
	try
	{
		if (0 < x)
		{
			cpp_dec_float_50 x0 = x * divi_t(2);
			cpp_dec_float_50 x1 = (x0 + x * divi_t(x0)) * divi_t(2);
			for (int i = 0; i < iterMax; i++)
			{
				x0 = x1;
				x1 = (x0 + x * divi_t(x0)) * divi_t(2);
				if (abs(x1 - x0) < tol * abs(x1))
					break;
			}
			return x1;
		}
		else
		{
			throw runtime_error(
				"No se puede obtener una raiz de un numero negativo!"
			);
		}
	}
	catch (const exception& e)
	{
		cout << "\nERROR: " << e.what() << endl;
	}
	return 0;
}

/*
* Funcion que calcula un exponencial
*/
cpp_dec_float_50 exp_t(cpp_dec_float_50 x)
{
	if (x == 0)
		return 1;

	cpp_dec_float_50 sk = 0;
	cpp_dec_float_50 sk_1 = 0;
	for (int i = 0; i < iterMax; i++)
	{
		sk += pow(x, i) * divi_t(factorial(i));
		sk_1 = sk + pow(x, i + 1) * divi_t(factorial(i + 1));

		if (abs(sk_1 - sk) < tol)
			break;
	}

	return sk;
}

/*
* Funcion que arregla un valor para algunas funciones trigonometricas
*/
cpp_dec_float_50 fix_trigonometry_numb(cpp_dec_float_50 x)
{
	while (x < 0 || 2*pi_t < x)
	{
		if (x < 0)
		{
			x = x + 2 * pi_t;
		}
		else
		{
			x = x - 2 * pi_t;
		}
	}
	return x;
}

/*
* Funcion que calcula el seno de un valor
*/
cpp_dec_float_50 sin_t(cpp_dec_float_50 x)
{
	x = fix_trigonometry_numb(x);
	cpp_dec_float_50 sk = 0;
	cpp_dec_float_50 sk_1 = 0;
	int i;
	for (i = 0; i < iterMax; i++)
	{
		sk += pow(-1, i) * pow(x, 2 * i + 1) * divi_t(factorial(2 * i + 1));
		int i_1 = i + 1;
		sk_1 = sk + pow(-1, i_1) * pow(x, 2 * i_1 + 1) * divi_t(factorial(2 * i_1 + 1));

		if (abs(sk_1 - sk) < tol)
			break;
	}
	return sk;
}

/*
* Funcion que calcula el coseno de un valor
*/
cpp_dec_float_50 cos_t(cpp_dec_float_50 x)
{
	x = fix_trigonometry_numb(x);
	cpp_dec_float_50 sk = 0;
	cpp_dec_float_50 sk_1 = 0;
	for (int i = 0; i < iterMax; i++)
	{
		sk += pow(-1, i) * pow(x, 2 * i) * divi_t(factorial(2 * i));
		int i_1 = i + 1;
		sk_1 = sk + pow(-1, (i_1 + 1)) * pow(x, 2 * (i_1 + 1)) * divi_t(factorial(2 * (i_1 + 1)));

		if (abs(sk_1 - sk) < tol)
			break;
	}
	return sk;
}

/*
* Funcion que calcula la tangente de un valor
*/
cpp_dec_float_50 tan_t(cpp_dec_float_50 x)
{
	try
	{
		cpp_dec_float_50 num = sin_t(x);
		cpp_dec_float_50 den = cos_t(x);
		if (den == 0)
			throw runtime_error(
				"Tangente de n * pi/2"
			);
	}
	catch (const exception& e)
	{
		cout << "\nERROR: " << e.what() << endl;
	}
	return 0;
}

/*
* Funcion que calcula el logaritmo natural de un valor
*/
cpp_dec_float_50 ln_t(cpp_dec_float_50 x)
{
	try
	{
		if (x <= 0)
			throw runtime_error(
				"No existe el logaritmo natural de numeros negativos!"
			);
		cpp_dec_float_50 sk = 0;
		cpp_dec_float_50 sk_1 = 0;

		for (int i = 0; i < iterMax; i++)
		{
			sk += divi_t(2 * i + 1) * pow((x - 1) * divi_t(x + 1), 2 * i);
			int i_1 = i + 1;
			sk_1 = sk + divi_t(2 * i_1 + 1) * pow((x - 1) * divi_t(x + 1), 2 * i_1);

			if (abs(sk_1 - sk) < tol)
				break;
		}

		return (2 * (x - 1)) * divi_t(x + 1) * sk;
	}
	catch (const exception& e)
	{
		cout << "\nERROR: " << e.what() << endl;
	}
	return 0;
}

/*
* Funcion que calcula el logaritmo de un valor segun la base dada
*/
cpp_dec_float_50 log_t(cpp_dec_float_50 x, cpp_dec_float_50 y)
{
	try
	{
		if (x <= 0)
			throw runtime_error(
				"No existe el logaritmo para numeros negativos!"
			);
		return ln_t(x) * divi_t(ln_t(y));
	}
	catch (const exception& e)
	{
		cout << "\nERROR: " << e.what() << endl;
	}
	return 0;
}

/*
* Funcion que calcula el seno hipervolico de un valor
*/
cpp_dec_float_50 sinh_t(cpp_dec_float_50 x)
{
	cpp_dec_float_50 sk = 0;
	cpp_dec_float_50 sk_1 = 0;
	for (int i = 0; i < iterMax; i++)
	{
		sk += pow(x, 2 * i + 1) * divi_t(factorial(2 * i + 1));
		int i_1 = i + 1;
		sk_1 = sk + pow(x, 2 * i_1 + 1) * divi_t(factorial(2 * i_1 + 1));

		if (abs(sk_1 - sk) < tol)
			break;
	}
	return sk;
}

/*
* Funcion que calcula el coseno hiperbolico de una funcion
*/
cpp_dec_float_50 cosh_t(cpp_dec_float_50 x)
{
	cpp_dec_float_50 sk = 0;
	cpp_dec_float_50 sk_1 = 0;
	for (int i = 0; i < iterMax; i++)
	{
		sk += pow(x, 2 * i) * divi_t(factorial(2 * i));
		int i_1 = i + 1;
		sk_1 = sk + pow(x, 2 * i_1) * divi_t(factorial(2 * i_1));

		if (abs(sk_1 - sk) < tol)
			break;
	}
	return sk;
}

/*
* Funcion que calcula la tangente hiperbolica de una funcion
*/
cpp_dec_float_50 tanh_t(cpp_dec_float_50 x)
{
	return sinh_t(x) * divi_t(cosh_t(x));
}

/*
* Funcion que calcula el arcoseno de un valor
*/
cpp_dec_float_50 asin_t(cpp_dec_float_50 x)
{
	try
	{
		if (1 < x or x < -1)
			throw runtime_error(
				"Fuera de dominio [-1, 1]"
			);

		cpp_dec_float_50 sk = 0;
		cpp_dec_float_50 sk_1 = 0;
		for (int i = 0; i < iterMax; i++)
		{
			sk += factorial(2 * i) * divi_t(pow(4, i) * pow(factorial(i), 2) * (2 * i + 1)) * pow(x, 2 * i + 1);
			int i_1 = i + 1;
			sk_1 = sk + factorial(2 * i_1) * divi_t(pow(4, i_1) * pow(factorial(i_1), 2) * (2 * i_1 + 1)) * pow(x, 2 * i_1 + 1);

			if (abs(sk_1 - sk) < tol)
				break;
		}
		return sk;
	}
	catch (const exception e)
	{
		cout << "\nERROR: " << e.what() << endl;
	}
	return -2;
}

/*
* Funcion que calcula el arcocoseno de un valor
*/
cpp_dec_float_50 acos_t(cpp_dec_float_50 x)
{
	try
	{
		if (1 < x or x < -1)
			throw runtime_error(
				"Fuera de dominio [-1, 1]"
			);

		return pi_t * divi_t(2) - asin_t(x);
	}
	catch (const exception e)
	{
		cout << "\nERROR: " << e.what() << endl;
	}
	return -1;
}

/*
* Funcion que calcula la arcotangente de un valor
*/
cpp_dec_float_50 atan_t(cpp_dec_float_50 x)
{
	cpp_dec_float_50 sk = 0;
	cpp_dec_float_50 sk_1 = 0;
	if (-1 <= x && x <= 1)
	{
		for (int i = 0; i < iterMax; i++)
		{
			sk += pow(-1, i) * pow(x, 2 * i + 1) * divi_t(2 * i + 1);
			int i_1 = i + 1;
			sk_1 = sk + pow(-1, i_1) * pow(x, 2 * i_1 + 1) * divi_t(2 * i_1 + 1);

			if (abs(sk_1 - sk) < tol)
				break;
		}
		return sk;
	}
	else
	{
		for (int i = 0; i < iterMax; i++)
		{
			sk = pow(-1, i) * divi_t(2 * i + 1) * divi_t(pow(x, 2 * i + 1));
			int i_1 = i + 1;
			sk_1 = sk + pow(-1, i_1) * divi_t(2 * i_1 + 1) * divi_t(pow(x, 2 * i_1 + 1));

			if (abs(sk_1 - sk) < tol)
				break;
		}
		if (x < -1)
		{
			return -pi_t * divi_t(2) - sk;
		}
		else
		{
			return pi_t * divi_t(2) - sk;
		}

	}
}

/*
* Funcion que calcula la cosecante de un valor
*/
cpp_dec_float_50 csc_t(cpp_dec_float_50 x)
{
	try
	{
		cpp_dec_float_50 ans = sin_t(x);
		if (ans == 0)
			throw runtime_error(
				"Cosecante de n * pi"
			);
		return divi_t(ans);
	}
	catch (const exception e)
	{
		cout << "\nERROR: " << e.what() << endl;
	}
	return 0;
}

/*
* Funcion que calcula la secante de un valor
*/
cpp_dec_float_50 sec_t(cpp_dec_float_50 x)
{
	try
	{
		cpp_dec_float_50 ans = cos_t(x);
		if (ans == 0)
			throw runtime_error(
				"Secante de n * pi / 2"
			);
		return divi_t(ans);
	}
	catch (const exception& e)
	{
		cout << "\nERROR: " << e.what() << endl;
	}
	return 0;
}

/*
* Funcion que calcula la cotangente de un valor
*/
cpp_dec_float_50 cot_t(cpp_dec_float_50 x)
{
	try
	{
		cpp_dec_float_50 num = cos_t(x);
		cpp_dec_float_50 den = sin_t(x);
		if (den == 0)
			throw runtime_error(
				"Cotangente de n * pi"
			);
		return num * divi_t(den);
	}
	catch (const exception& e)
	{
		cout << "\nERROR: " << e.what() << endl;
	}
	return 0;
}

cpp_dec_float_50 power_t(cpp_dec_float_50 x, cpp_dec_float_50 y)
{
	try
	{
		if (x == 0 && y == 0)
			throw runtime_error(
				"0^0 es indeterminado"
			);
		if (x == 0 && y < 0)
			throw runtime_error(
				"Division por cero!"
			);
		if (x == 0)
			return 0;
		if (x < 0)
			return -exp_t(y * ln_t(-x));
		return exp_t(y * ln_t(x));
	}
	catch (const exception& e)
	{
		cout << "\nERROR: " << e.what() << endl;
	}
	return 0;
}

int main()
{

	// Explicacion
	cout << "Calculadora funtras\n" << endl;
	cout << "Como utilizar:" << endl;
	cout << "Se va a desplegar un menu con diferentes opciones (1-21), las cuales correponden a las funciones implementadas." << endl;
	cout << "Una vez seleccionado la funcion, ingrese el valor para \"x\" que usted usted desee." << endl;
	cout << "De ser necesario, tambien debera ingresar un valor para \"y\".\n" << endl;
	cout << "Nota importante:" << endl;
	cout << "Si quiere utilizar el valor de \"pi\", ingrese textualmente \"pi_t\"" << endl;
	cout << "La calculadora esta preparada para utilizar dicho valor.\n" << endl;

	cout << "Elaborado por:" << endl;
	cout << "- Axel Bruno Flores Lara" << endl;
	cout << "- Marco Vinicio Rivera Serrano" << endl;
	cout << "- Juan Daniel Rodriguez Montero" << endl;
	cout << "- Julio Josue Varela Venegas" << endl;

	system("pause");
	system("cls");

	while (true)
	{
		// Menú de opciones
		cout << "Seleccione una funcion a calcular:" << endl;
		cout << "1.  senh (x)" << endl;
		cout << "2.  cosh (x)" << endl;
		cout << "3.  tanh (x)" << endl;
		cout << "4.  asen (x)" << endl;
		cout << "5.  acos (x)" << endl;
		cout << "6.  atan (x)" << endl;
		cout << "7.  sec (x)" << endl;
		cout << "8.  csc (x)" << endl;
		cout << "9.  cot (x)" << endl;
		cout << "10. sen (x)" << endl;
		cout << "11. cos (x)" << endl;
		cout << "12. tan (x)" << endl;
		cout << "13. ln (x)" << endl;
		cout << "14. log10 (x)" << endl;
		cout << "15. x!" << endl;
		cout << "16. 1/x (x)" << endl;
		cout << "17. raiz (x)" << endl;
		cout << "18. exp (x)" << endl;
		cout << "19. raiz_y (x)" << endl;
		cout << "20. x^y " << endl;
		cout << "21. log_y (x)" << endl;

		// Selección de función
		int opcion;
		cout << "Opcion: ";
		cin >> opcion;

		// Valores de entrada

		string input_1, input_2;
		cpp_dec_float_50 x, y;
		cout << "Ingrese el valor de x: ";
		cin >> input_1;
		if (input_1 == "pi_t")
		{
			x = pi_t;
		}
		else
		{
			x = boost::lexical_cast<cpp_dec_float_50>(input_1);
		}

		if (opcion == 20) {
			cout << "Ingrese el valor de y: ";
			cin >> input_2;
			if (input_2 == "pi_t")
			{
				y = pi_t;
			}
			else
			{
				y = boost::lexical_cast<cpp_dec_float_50>(input_2);
			}
		}

		// Resultado de la operación
		cpp_dec_float_50 resultado;

		switch (opcion) {
		case 1:
			resultado = sinh_t(x);
			break;
		case 2:
			resultado = cosh_t(x);
			break;
		case 3:
			resultado = tanh_t(x);
			break;
		case 4:
			resultado = asin_t(x);
			break;
		case 5:
			resultado = acos_t(x);
			break;
		case 6:
			resultado = atan_t(x);
			break;
		case 7:
			resultado = sec_t(x);
			break;
		case 8:
			resultado = csc_t(x);
			break;
		case 9:
			resultado = cot_t(x);
			break;
		case 10:
			resultado = sin_t(x);
			break;
		case 11:
			resultado = cos_t(x);
			break;
		case 12:
			resultado = tan_t(x);
			break;
		case 13:
			resultado = ln_t(x);
			break;
		case 14:
			resultado = log(x);
			break;
		case 15:
			resultado = factorial(x);
			break;
		case 16:
			resultado = divi_t(x);
			break;
		case 17:
			resultado = sqrt_t(x);
			break;
		case 18:
			resultado = exp_t(x);
			break;
		case 19:
			cout << "Ingrese el valor de y: ";
			cin >> input_2;
			if (input_2 == "pi_t")
			{
				y = pi_t;
			}
			else
			{
				y = boost::lexical_cast<cpp_dec_float_50>(input_2);
			}
			resultado = root_t(x, y);
			break;
		case 20:
			resultado = power_t(x, y);
			break;
		case 21:
			cout << "Ingrese el valor de y: ";
			cin >> input_2;
			if (input_2 == "pi_t")
			{
				y = pi_t;
			}
			else
			{
				y = boost::lexical_cast<cpp_dec_float_50>(input_2);
			}
			resultado = log_t(x, y);
			break;
		default:
			cerr << "Opción no válida." << endl;
			return 1;
		}

		// Muestra el resultado de la operación
		cout << "Resultado de la operacion es: ";
		cout << setprecision(numeric_limits<cpp_dec_float_50>::digits10) << resultado << endl;

		cout << "Desea hacer otra operacion? 1 (y) / 0 (n): ";
		int close;
		cin >> close;

		switch (close)
		{
		case 1:
			system("cls");
			break;
		case 0:
			return 0;
		default:
			break;
		}
	}
	return 0;
}