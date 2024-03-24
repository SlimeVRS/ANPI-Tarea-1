#include "funtras.h"

cpp_dec_float_50 test()
{
	cpp_dec_float_50 cosine = cos_t(2 * divi_t(7));
	cpp_dec_float_50 nat_log = ln_t(2);
	cpp_dec_float_50 root = root_t(cosine + nat_log, 3);

	cpp_dec_float_50 den = divi_t(sinh_t(sqrt_t(2)));

	return root * den + atan_t(exp_t(-1));
}