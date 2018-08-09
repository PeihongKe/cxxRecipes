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

			void setNextInt(const Shared_Pointer<IntStruct>& a)
			{
				next = a;
			}


		private:
			int data;
			Shared_Pointer<IntStruct> next;
		};

		struct SmallInStruct : public IntStruct
		{
			SmallInStruct(int rhs): IntStruct(rhs)
			{				
			}
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

		BOOST_AUTO_TEST_CASE(SP_WithClassHier)
		{
			Shared_Pointer<IntStruct> q1(new SmallInStruct(7));
			BOOST_CHECK(q1.getCount() == 1);
			BOOST_CHECK(q1->getData() == 7);
		}

		BOOST_AUTO_TEST_CASE(SP_cyclic_reference)
		{
			Shared_Pointer<IntStruct> q1;
			Shared_Pointer<IntStruct> q2;
			{
				Shared_Pointer<IntStruct> p1(new IntStruct(5));
				Shared_Pointer<IntStruct> p2(new IntStruct(5));
				BOOST_CHECK(p1.getCount() == 1);
				BOOST_CHECK(p2.getCount() == 1);

				q1 = p1;
				q2 = p2;

				p1->setNextInt(p2);
				p2->setNextInt(p1);

				BOOST_CHECK(p1.getCount() == 3);
				BOOST_CHECK(p2.getCount() == 3);
			}		

			BOOST_CHECK(q1.getCount() == 2);
			BOOST_CHECK(q2.getCount() == 2); // one count from q2, one from cyclic count
			
		}
	}
}

