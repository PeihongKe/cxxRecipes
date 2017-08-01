#ifndef SMART_POINTERS
#define SMART_POINTERS

#include <sstream> 
#include <iostream> 
#include <limits>

namespace cxxRecipes
{	
	namespace smartPointers 
	{
		template<typename T>
		class Weak_Pointer
		{

		};

		/*
		a naive implementation of shared pointer;
		do not consider move;		
		*/
		template<typename T>
		class Shared_Pointer
		{
		public:

			Shared_Pointer()
			{ 
				count = new int(0);
			}

			template<typename U>
			Shared_Pointer(U* rhs)
			{
				initialize(rhs);
			}

			Shared_Pointer(T* rhs)
			{
				initialize(rhs);
			}

			Shared_Pointer(const Shared_Pointer& rhs): data(rhs.data), count(rhs.count)
			{						
				increase();
			}

			T* operator ->() // (p.operator->())->m
			{
				return data;
			}

			T& operator*()
			{
				return *data;
			}

			Shared_Pointer& operator=(const Shared_Pointer& rhs)
			{
				if (&rhs != this)
				{
					decrease();
					this->data = rhs.data;
					this->count = rhs.count;
					increase();
				}

				return *this;
			}

			~Shared_Pointer()
			{
				decrease();
			}

			int getCount() const
			{
				return *count;
			}

		private:

			void initialize(T* rhs)
			{
				count = new int(1);
				data = rhs;
			}

			void decrease() 
			{ 
				// well, 
				if (*count == 0)
				{
					delete count; // for empty shared_pointer
				}

				*count -= 1; 
				if (*count == 0)
				{
					delete data;
					delete count;
				}
			};

			void increase() 
			{ 
				*count += 1; 
			};

			T* data;
			int* count;
		};
	}
}

#endif