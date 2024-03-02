#ifndef FUNTRAS_H
#define FUNTRAS_H

#include <iostream>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;

/*
* @brief Gets the factorial of a given value
* @param x Value to be operated
* @return Factorial of the given value
*/
cpp_dec_float_50 factorial(cpp_dec_float_50 x);

/*
* @brief Initial value of x to be inversed
* @param x Value to be inversed
* @return Specific value of epsilon to know the inital value
*/
cpp_dec_float_50 divi_t_aux(cpp_dec_float_50 x);

/**
* @brief Aproximates 1/x
* @param x Value to be inversed
* @return Decimal aproximation
*/
cpp_dec_float_50 divi_t(cpp_dec_float_50 x);

/**
* @brief Gets the root value of x with an specific index
* @param x Value to be rooted
* @param y Index of the root operation
* @return Root aproximation
*/
cpp_dec_float_50 root_t(cpp_dec_float_50 x, cpp_dec_float_50 y);

/**
* @brief Gets the square root value of x
* @param x Value to be rooted
* @return Square root aproximation
*/
cpp_dec_float_50 sqrt_t(cpp_dec_float_50 x);

/**
* @brief Gets the exp value of x as e^x, where 'e' is Euler's constant
* @param x Value to be operated
* @return Exponencial aproximation
*/
cpp_dec_float_50 exp_t(cpp_dec_float_50 x);

/**
* @brief Gets the sine value of x
* @param x Value to be operated
* @return Decimal aproximation
*/
cpp_dec_float_50 cos_t(cpp_dec_float_50 x);

/**
* @brief Gets the cosine value of x
* @param x Value to be operated
* @return Decimal aproximation
*/
cpp_dec_float_50 sin_t(cpp_dec_float_50 x);

/**
* @brief Gets the tangent of x
* @param x Value to be operated
* @return Decimal aproximation
*/
cpp_dec_float_50 tan_t(cpp_dec_float_50 x);
/**
* @brief Gets the natural logarithm of x
* @param x Value to be operated
* @return Decimal aproximation
*/
cpp_dec_float_50 ln_t(cpp_dec_float_50 x);

/**
* @brief Gets the logarithm of x given a y base
* @param x Argument of the logarithm
* @param y Base of the logarithm
* @return Decimal aproximation
*/
cpp_dec_float_50 log_t(cpp_dec_float_50 x, cpp_dec_float_50 y);

/**
* @brief Gets the sine hyperbolic value of x
* @param x Value to be operated
* @return Decimal aproximation
*/
cpp_dec_float_50 sinh_t(cpp_dec_float_50 x);

/**
* @brief Gets the cosine hyperbolic value of x
* @param x Value to be operated
* @return Decimal aproximation
*/
cpp_dec_float_50 cosh_t(cpp_dec_float_50 x);

/**
* @brief Gets the tangent hyperbolic value of x
* @param x Value to be operated
* @return Decimal aproximation
*/
cpp_dec_float_50 tanh_t(cpp_dec_float_50 x);

/**
* @brief Gets the arcsine value of x
* @param x Value to be operated
* @return Decimal aproximation
*/
cpp_dec_float_50 asin_t(cpp_dec_float_50 x);

/**
* @brief Gets the arcosine value of x
* @param x Value to be operated
* @return Decimal aproximation
*/
cpp_dec_float_50 acos_t(cpp_dec_float_50 x);

/**
* @brief Gets the arctangent value of x
* @param x Value to be operated
* @return Decimal aproximation
*/
cpp_dec_float_50 atan_t(cpp_dec_float_50 x);

/**
* @brief Gets the cosecant value of x
* @param x Value to be operated
* @return Decimal aproximation
*/
cpp_dec_float_50 csc_t(cpp_dec_float_50 x);

/**
* @brief Gets the secant value of x
* @param x Value to be operated
* @return Decimal aproximation
*/
cpp_dec_float_50 sec_t(cpp_dec_float_50 x);

/**
* @brief Gets the cotangent value of x
* @param x Value to be operated
* @return Decimal aproximation
*/
cpp_dec_float_50 cot_t(cpp_dec_float_50 x);

#endif // !FUNTRAS_H