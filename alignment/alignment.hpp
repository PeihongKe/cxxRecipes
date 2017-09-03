#ifndef ALIGNMENT
#define ALIGNMENT

#include <memory>

namespace cxxRecipes
{	
	namespace alignment
	{
		template<int N>
		void* allocateAlign(int M)
		{
			void *mem = malloc(M + N-1);
			void *ptr = ((uintptr_t)mem + N-1) & ~(uintptr_t)(N-1);
			return ptr						
		}

		template<int N>
		bool checkAlign(void* p)
		{
			return ((unsigned long)p & (N - 1)) == 0
		}
	}

}

#endif