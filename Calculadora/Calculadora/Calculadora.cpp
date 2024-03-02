#include "funtras.h"
using namespace std;

// Variables globales
cpp_dec_float_50 pi_t = 3.14159265358979323846;
cpp_dec_float_50 tol = 1e-8;
int iterMax = 2500;

cpp_dec_float_50 factorial(cpp_dec_float_50 x)
{
	if (x == 1 || x == 0)
		return 1;
	cpp_dec_float_50 temp = 1;
	temp = x * factorial(x - 1);
	return temp;
}

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

cpp_dec_float_50 divi_t(cpp_dec_float_50 x)
{
	if (0 < x)
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
		return xk;	
	}
	else
	{
		return -1;
	}
	
}

cpp_dec_float_50 root_t(cpp_dec_float_50 x, cpp_dec_float_50 y)
{
	if (0 < x && 2 < y)
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
	}
	if (x < 0)
		return -1;
}

cpp_dec_float_50 sqrt_t(cpp_dec_float_50 x)
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
		return -1;
	}
}

cpp_dec_float_50 exp_t(cpp_dec_float_50 x)
{
	if (x == 0)
		return 1;

	cpp_dec_float_50 sum = 0;
	for (int i = 0; i < iterMax; i++)
	{
		cpp_dec_float_50 sk = pow(x, i) * divi_t(factorial(i));
		cpp_dec_float_50 sk_1 = sk + pow(x, i + 1) * divi_t(factorial(i + 1));

		if (abs(sk_1 - sk) < tol)
			break;
		sum += sk;
	}

	return sum;
}

// Revisar
cpp_dec_float_50 sin_t(cpp_dec_float_50 x)
{
	cpp_dec_float_50 sk = 0;
	cpp_dec_float_50 sk_1 = 0;
	for (int i = 0; i < iterMax; i++)
	{
		sk += pow(-1, i) * pow(x, 2 * i + 1) * divi_t(factorial(2 * i + 1));
		sk_1 = sk + pow(-1, i) * pow(x, 2 * i + 1) * divi_t(factorial(2 * i + 1));

		if (abs(sk_1 - sk) < tol)
			break;
	}
	return sk;
}

// Revisar
cpp_dec_float_50 cos_t(cpp_dec_float_50 x)
{
	cpp_dec_float_50 sum = 0;
	for (int i = 0; i < iterMax; i++)
	{
		cpp_dec_float_50 sk = pow(-1, i) * pow(x, 2 * i) * divi_t(factorial(2 * i));
		cpp_dec_float_50 sk_1 = pow(-1, (i + 1)) * pow(x, 2 * (i + 1)) * divi_t(factorial(2 * (i + 1)));

		if (abs(sk_1 - sk) < tol)
			break;

		sum += sk;
	}

	return sum;
}

// Revisar
cpp_dec_float_50 tan_t(cpp_dec_float_50 x)
{
	if (x == pi_t * divi_t(2))
		return NULL;
	else
		return sin_t(x) * divi_t(cos_t(x));
}

cpp_dec_float_50 ln_t(cpp_dec_float_50 x)
{
	if (x < 0)
		return -1;
	cpp_dec_float_50 sum = 0;

	for (int i = 0; i < iterMax; i++)
	{
		int i_1 = i + 1;

		cpp_dec_float_50 sk = divi_t(2 * i + 1) * pow((x - 1) * divi_t(x + 1), 2 * i);
		cpp_dec_float_50 sk_1 = divi_t(2 * i_1 + 1) * pow((x - 1) * divi_t(x + 1), 2 * i_1);

		if (abs(sk_1 - sk) < tol)
			break;

		sum += sk;
	}

	return (2 * (x - 1)) * divi_t(x + 1) * sum;
}

cpp_dec_float_50 log_t(cpp_dec_float_50 x, cpp_dec_float_50 y)
{
	if (x < 0)
		return -1;
	return ln_t(x) * divi_t(ln_t(y));
}

cpp_dec_float_50 sinh_t(cpp_dec_float_50 x)
{
	cpp_dec_float_50 sk = 0;
	cpp_dec_float_50 sk_1 = 0;
	for (int i = 0; i < iterMax; i++)
	{
		sk += pow(x, 2 * i + 1) * divi_t(factorial(2 * i + 1));
		sk_1 = sk + pow(x, 2 * i + 1) * divi_t(factorial(2 * i + 1));

		if (abs(sk_1 - sk) < tol)
			break;
	}
	return sk;
}

cpp_dec_float_50 cosh_t(cpp_dec_float_50 x)
{
	cpp_dec_float_50 sk = 0;
	cpp_dec_float_50 sk_1 = 0;
	for (int i = 0; i < iterMax; i++)
	{
		sk += pow(x, 2 * i) * divi_t(factorial(2 * i));
		sk_1 = sk + pow(x, 2 * i) * divi_t(factorial(2 * i));
		
		if (abs(sk_1 - sk) < tol)
			break;
	}
	return sk;
}

cpp_dec_float_50 tanh_t(cpp_dec_float_50 x)
{
	return sinh_t(x) * divi_t(cosh_t(x));
}

cpp_dec_float_50 asin_t(cpp_dec_float_50 x)
{
	if (1 < x or x < -1)
		return NULL;

	cpp_dec_float_50 sk = 0;
	cpp_dec_float_50 sk_1 = 0;
	for (int i = 0; i < iterMax; i++)
	{
		sk += factorial(2 * i) * divi_t(pow(4, i) * pow(factorial(i), 2) * (2 * i + 1)) * pow(x, 2 * i + 1);
		sk_1 = sk + factorial(2 * i) * divi_t(pow(4, i) * pow(factorial(i), 2) * (2 * i + 1)) * pow(x, 2 * i + 1);

		if (abs(sk_1 - sk) < tol)
			break;
	}
	return sk;
}

cpp_dec_float_50 acos_t(cpp_dec_float_50 x)
{
	if (1 < x or x < -1)
		return NULL;

	return pi_t * divi_t(2) - asin_t(x);
}

cpp_dec_float_50 atan_t(cpp_dec_float_50 x)
{
	cpp_dec_float_50 sk = 0;
	cpp_dec_float_50 sk_1 = 0;
	if (-1 <= x && 1 <= x)
	{
		for (int i = 0; i < iterMax; i++)
		{
			sk += pow(-1, i) * pow(x, 2 * i + 1) * divi_t(2 * i + 1);
			sk_1 = sk + pow(-1, i) * pow(x, 2 * i + 1) * divi_t(2 * i + 1);

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
			sk_1 = sk + pow(-1, i) * divi_t(2 * i + 1) * divi_t(pow(x, 2 * i + 1));

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

cpp_dec_float_50 csc_t(cpp_dec_float_50 x)
{
	cpp_dec_float_50 ans = sin_t(x);
	if (ans == 0)
		return NULL;
	return divi_t(ans);
}

cpp_dec_float_50 sec_t(cpp_dec_float_50 x)
{
	cpp_dec_float_50 ans = cos_t(x);
	if (ans == 0)
		return NULL;
	return divi_t(ans);
}

cpp_dec_float_50 cot_t(cpp_dec_float_50 x)
{
	cpp_dec_float_50 num = cos_t(x);
	cpp_dec_float_50 den = sin_t(x);
	if (den == 0)
		return NULL;
	return num * divi_t(den);
}

int main()
{
	cpp_dec_float_50 x = 10;

	// Factorial
	cpp_dec_float_50 fact = factorial(x);
	cout << "Factorial de " << x << " es " << fact;

	// Inverso
	cpp_dec_float_50 inv = divi_t(x);
	cout << "\nInverso de " << x << " es aproximadamente " << inv;

	// Raiz cuadrada
	cpp_dec_float_50 sqrt = sqrt_t(x);
	cout << "\nRaiz cuadrada de " << x << " es aproximadamente " << sqrt;

	// Raiz
	cpp_dec_float_50 y = 3;
	cpp_dec_float_50 root = root_t(x, y);
	cout << "\nRaiz de " << x << " con indice " << y << " es aproximadamente " << root;

	// Exponencial
	x = 3;
	cpp_dec_float_50 exp = exp_t(x);
	cout << "\nExponencial de " << x << " es aproximadamente " << exp;

	// Logaritmo natural
	x = 100;
	cpp_dec_float_50 ln = ln_t(x);
	cout << "\nLogaritmo natural de " << x << " es aproximadamente " << ln;

	// Logaritmo x base y
	y = 10;
	cpp_dec_float_50 log = log_t(x, y);
	cout << "\nLogaritmo de " << x << " base " << y << " es aproximadamente " << log;

	// Sen
	cpp_dec_float_50 sen = sin_t(x);
	cout << "\nSen de " << x << " es aproximadamente " << sen;

	// Cos
	cpp_dec_float_50 cos = cos_t(x);
	cout << "\nCos de " << x << " es aproximadamente " << cos;

	// Tan
	cpp_dec_float_50 tan = tan_t(x);
	cout << "\nTan de " << x << " es aproximadamente " << tan;

	// Seno hiperbolic
	cpp_dec_float_50 sinh = sinh_t(x);
	cout << "\nSeno hiperbolico de " << x << " es aproximadamente " << sinh;

	// Coseno hiperbolico
	cpp_dec_float_50 cosh = cosh_t(x);
	cout << "\nCoseno hiperbolico de " << x << " es aproximadamente " << cosh;

	// Tangente hiperbolico
	cpp_dec_float_50 tanh = tanh_t(x);
	cout << "\nTangente hiperbolico de " << x << " es aproximadamente " << tanh;

	// Arcoseno (revisar)
	x = 1;
	cpp_dec_float_50 asin = asin_t(x);
	cout << "\nArcseno de " << x << " es aproximadamente " << asin;

	cpp_dec_float_50 acos = acos_t(x);
	cout << "\nArcoseno de " << x << " es aproximadamente " << acos;

	cpp_dec_float_50 atan = atan_t(x);
	cout << "\nArcotangente de " << x << " es aproximadamente " << atan;
	return 0;
}
