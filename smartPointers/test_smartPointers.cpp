#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE smart_pointers
#include <boost/test/unit_test.hpp>
#include "smartPointers.hpp"
#include <limits>
#include <iostream>
#include <math.h>

using namespace cxxRecipes::smartPointers;


namespace cxxRecipes
{
	namespace smartPointerTest
	{
		struct IntStruct
		{
		public:

			IntStruct(int rhs)
			{
				data = rhs;
			}

			int getData()
			{
				return data;
			}


		private:
			int data;
		};


		BOOST_AUTO_TEST_CASE(SP_operators_test)
		{
			Shared_Pointer<int> p(new int(5));
			BOOST_CHECK(*p == 5);

			Shared_Pointer<IntStruct> p1(new IntStruct(5));
			BOOST_CHECK(p1->getData() == 5);
		}

		BOOST_AUTO_TEST_CASE(SP_ctor_test)
		{
			Shared_Pointer<int> p(new int(5));
			BOOST_CHECK(*p == 5);
			BOOST_CHECK(p.getCount() == 1);			

			Shared_Pointer<int> p1(p);
			BOOST_CHECK(*p1 == 5);
			BOOST_CHECK(p.getCount() == 2);

			Shared_Pointer<int> q(new int(6));
			BOOST_CHECK(*q == 6);
			BOOST_CHECK(q.getCount() == 1);

			p = q;
			BOOST_CHECK(*p == *q);
			BOOST_CHECK(*p == 6);
			BOOST_CHECK(*q == 6);
			BOOST_CHECK(*p1 == 5);

			BOOST_CHECK(p1.getCount() == 1);
			BOOST_CHECK(p.getCount() == 2);
			BOOST_CHECK(q.getCount() == 2);
		}

		BOOST_AUTO_TEST_CASE(SP_dtor_test)
		{
			Shared_Pointer<int>* pp;
			{
				pp = new Shared_Pointer<int>(new int(5));
				BOOST_CHECK(pp->getCount() == 1);

				Shared_Pointer<int> p1(*pp);
				BOOST_CHECK(p1.getCount() == 2);
				BOOST_CHECK(pp->getCount() == 2);

				{
					Shared_Pointer<int> p2(*pp);
					BOOST_CHECK(p2.getCount() == 3);
					BOOST_CHECK(pp->getCount() == 3);
				}

				BOOST_CHECK(p1.getCount() == 2);
				BOOST_CHECK(pp->getCount() == 2);

				delete pp;
				BOOST_CHECK(p1.getCount() == 1);								
			}			
			
		}
	}
}

