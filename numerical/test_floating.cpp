#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_floating
#include <boost/test/unit_test.hpp>
#include "floating.hpp"


namespace numerical
{

	bool IsNumber(double x)
	{
		// This looks like it should always be true, 
		// but it's false if x is a NaN.
		return (x == x);
	}

	BOOST_AUTO_TEST_CASE(test_floating)
	{
		double b = 0.;
		double a = 1 / b;


	}
}