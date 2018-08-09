#ifndef ALIGNMENT
#define ALIGNMENT

#include <memory>

namespace cxxRecipes
{	
	/*
	32 bit can point to 2^32 bytes, which is equivalent to 4GB. 
	1: memory is in the unite of bytes (not bits)
	2: an address p is 32 bit aligned, if p%32 == 0 
	
	*/
	namespace alignment // working on addresses, 32 bytes or 64 bytes alignment  
	{
		// allocateAlign<128>(1000) will return a memory address that is a multiple of 128 and that points to memory of size 1000 bytes.
		template<int N> // N is 32 or 64 bytes 
		void* allocateAlign(int M) // M in bytes
		{
			void *mem = malloc(M + N-1); // make sure there is enough memory after the alignment 
			void *ptr = ((uintptr_t)mem + N-1) & ~(uintptr_t)(N-1); // 
			return ptr						
		}

		template<int N>
		bool checkAlign(void* p)
		{
			return ((unsigned long)p & (N - 1)) == 0 // equivalent to static_cast<uintptr_t>(static_cast<void *>(p))  % N == 0 
		}
	}

}

#endif