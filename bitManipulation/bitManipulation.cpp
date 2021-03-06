#include "bitManipulation.hpp"
#include <sstream> 
#include <iostream> 
#include <limits>

namespace cxxRecipes
{
	
	int leftShift(int v, int n)
	{
		return v << n;
	}

	string printInBit(int n)
	{
		stringstream ss;
		//int sizeOfBits = sizeof(n) * CHAR_BIT;
		//int sizeOfBits = sizeof(n) * std::numeric_limits<char>::digits; // this returns 7 instead of 8
		int sizeOfBits = sizeof(n) * std::numeric_limits<unsigned char>::digits;
		/*int maskAllOne = 0xffffffff;
		int maskAllOneButFirst = 0x7fffffff;*/
		int maskZeroButFirst = 0x80000000;
		while (sizeOfBits--)
		{
			if ((maskZeroButFirst & n) != 0)
			{
				ss << "1";
			}
			else
			{
				ss << "0";
			}
			n <<= 1;
		}

		return ss.str();		
	}

	int numOfBitsOne(int n)
	{
		if (n == 0)
			return 0;

		int count = 0;
		
		while ((n) != 0)
		{
			++count;
			n = n&(n - 1);
		}
		return count;
	}

	int numOfBitsOccupied(int n) 
	{
		int j = ~0;
		int count = 0;
		while ((j ) & n)
		{
			j <<= 1;
			++count;
		}
		return count;
	}

	int isPowerOfTwo(int n)
	{
		return n>0 && !(n&(n - 1));
	}

	bool isEven(int n)
	{
		return !(n & 1);
	}

	int NOnesOnRight(int n)
	{
		int i = ~0;
		while (n)
		{
			i <<= 1;
			--n;
		}

		return ~i;
	}

	int NOnesOnRight2(int n)
	{
		int i = 0;
		while (n)
		{
			--n;
			//i = i << 1 + 1; // NOTE: this is wrong as << has higher precedence than +
			i = (i << 1) + 1;
		}
		return i;
	}
}