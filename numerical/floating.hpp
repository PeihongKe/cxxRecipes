 
#include <float.h>
// references
// https://www.johndcook.com/blog/IEEE_exceptions_in_cpp/
// https://www.codeproject.com/Articles/824516/Concept-of-NaN-IND-INF-and-DEN
// floating point exceptions


//1.#INF on Windows or inf on Linux
//- 1.#INF or -inf


inline bool IsFiniteNumber(double x)
{
	return (x <= DBL_MAX && x >= -DBL_MAX);
}

bool IsNumber(double x)
{
	// This looks like it should always be true, 
	// but it's false if x is a NaN.
	return (x == x);
}