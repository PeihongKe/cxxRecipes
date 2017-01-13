#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE iterator_trait
#include <boost/test/unit_test.hpp>
#include "bitManipulation.hpp"
#include <limits>
#include <iostream>
#include <math.h>

using namespace cxxRecipes;


BOOST_AUTO_TEST_CASE(numOfBitsOne_test)
{
	int nBits = numOfBitsOne(8);
	BOOST_CHECK(nBits == 1);
	int nBits1 = numOfBitsOne(0xffffffff);
	BOOST_CHECK(nBits1 == 32);
	int nBits2 = numOfBitsOne(5);
	BOOST_CHECK(nBits2 ==  2);
}

BOOST_AUTO_TEST_CASE(numOfBitsOccupied_test)
{
	int nBits = numOfBitsOccupied(8);
	BOOST_CHECK(nBits == 4);
	int nBits1 = numOfBitsOccupied(0xffffffff);
	BOOST_CHECK(nBits1 == 32);
	int nBits2 = numOfBitsOccupied(5);
	BOOST_CHECK(nBits2 == 3);
}


BOOST_AUTO_TEST_CASE(NOnesOnRight_test)
{
	int nOnesOnRight1 = NOnesOnRight(1);
	BOOST_CHECK(nOnesOnRight1 == 1);

	int nOnesOnRight2 = NOnesOnRight(2);
	BOOST_CHECK(nOnesOnRight2 == 3);

	int nOnesOnRight3 = NOnesOnRight(3);
	BOOST_CHECK(nOnesOnRight3 == 7);

	int nOnesOnRight4 = NOnesOnRight(4);
	BOOST_CHECK(nOnesOnRight4 == 15);
}





BOOST_AUTO_TEST_CASE(printInBit_test)
{
	unsigned int systemMax = std::numeric_limits<unsigned int>::max();
	string maxUnsignedInStr = cxxRecipes::printInBit(systemMax);
	BOOST_CHECK(maxUnsignedInStr == "11111111111111111111111111111111");
	BOOST_CHECK(maxUnsignedInStr.size() == sizeof(unsigned int) *  std::numeric_limits<unsigned char>::digits); // 32
	
	BOOST_CHECK(cxxRecipes::printInBit(1) == "00000000000000000000000000000001");
	BOOST_CHECK(cxxRecipes::printInBit(2) == "00000000000000000000000000000010");
}

BOOST_AUTO_TEST_CASE(bit_hex_constant_test)
{	
	BOOST_CHECK(cxxRecipes::printInBit(0x00000001) == "00000000000000000000000000000001");
	BOOST_CHECK(cxxRecipes::printInBit(0xffffffff) == "11111111111111111111111111111111");
	BOOST_CHECK(cxxRecipes::printInBit(0x7fffffff) == "01111111111111111111111111111111");
	BOOST_CHECK(cxxRecipes::printInBit(0x80000000) == "10000000000000000000000000000000");
	BOOST_CHECK(cxxRecipes::printInBit(0x55555555) == "01010101010101010101010101010101");
	BOOST_CHECK(cxxRecipes::printInBit(0xaaaaaaaa) == "10101010101010101010101010101010");
}

BOOST_AUTO_TEST_CASE(bit_complement_test) 
{		
	unsigned int bitMax = ~0;
	unsigned int systemMax = std::numeric_limits<unsigned int>::max();
	BOOST_CHECK(bitMax == systemMax);
}


BOOST_AUTO_TEST_CASE(bit_xor_test)
{
	// test1: myBits ^ 0 : No change
	int input1 = 1234;			
	BOOST_CHECK((input1^0) == input1);

	// test2:  myBits ^ 1: Flip 
	int max = 0xffffffff;
	int mask = 0xffffffff;
	int min = 0;
	BOOST_CHECK((max ^ mask) == 0);
	BOOST_CHECK((min ^ mask) == max);

	// test3: A xor A == 0	
	BOOST_CHECK((input1^input1) == 0);

	// test4: A xor B xor A == B
	int input2 = 3456;
	BOOST_CHECK((input1^input2^input1) == input2);
}

BOOST_AUTO_TEST_CASE(bit_right_shift_test)
{	
	// test1: right shift positive
	int input = 8;
	BOOST_CHECK((input >> 1) == 4);
	BOOST_CHECK((input >> 2) == 2);
	BOOST_CHECK((input >> 3) == 1);
	BOOST_CHECK((input >> 4) == 0);
	BOOST_CHECK((input >> 5) == 0);

	// test2: right shift negative
	int input2 = -8;	
	BOOST_CHECK((input2 >> 1) == -4);
	BOOST_CHECK((input2 >> 2) == -2);
	BOOST_CHECK((input2 >> 3) == -1);
	BOOST_CHECK((input2 >> 4) == 0xffffffff);
	BOOST_CHECK((input2 >> 5) == 0xffffffff);
}

BOOST_AUTO_TEST_CASE(bit_left_shift_test)
{
	// test1: left shift positive
	int input = 1;
	BOOST_CHECK((1 << 0) == 1);
	BOOST_CHECK((input << 1) == 2);
	BOOST_CHECK((input << 2) == 4);
	BOOST_CHECK((input << 3) == 8);
	BOOST_CHECK((input << 4) == 16);

	// test2: left shift negative
	int input2 = -1;
	BOOST_CHECK((input2 << 1) == -2);
	BOOST_CHECK((input2 << 2) == -4);
	BOOST_CHECK((input2 << 3) == -8);
	BOOST_CHECK((input2 << 4) == -16);

	// test3: a << n == a * pow(2, n)
	int v = 10;
	int n = 3;
	BOOST_CHECK((v<<n) == static_cast<int>(v* pow(2,n)));	
}


BOOST_AUTO_TEST_CASE(IsEven_test)
{
	BOOST_CHECK(isEven(100));
	BOOST_CHECK(!isEven(99));
	BOOST_CHECK(isEven(98));
	BOOST_CHECK(isEven(2));
	BOOST_CHECK(!isEven(1));
	BOOST_CHECK(isEven(0));
}

BOOST_AUTO_TEST_CASE(trickOfIMinusOne_test)
{
	vector<int> res;
	res.push_back(0);
	for (int i = 1; i <= 64; ++i)
	{
		res.push_back(i&(i - 1));
	}
	int aaa = 1;

}


