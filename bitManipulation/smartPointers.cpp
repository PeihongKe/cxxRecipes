#include "smartPointers.hpp"
#include <sstream> 
#include <iostream> 
#include <limits>

namespace cxxRecipes
{
	namespace smartPointers
	{
		//template<typename T>
		//Shared_Pointer<T>::Shared_Pointer(const Shared_Pointer& rhs)
		//{			
		//	this->data = rhs->data;
		//	this->count = rhs->count;
		//	increase();
		//}

		//template<typename T>
		//Shared_Pointer<T>& Shared_Pointer<T>::operator=(const Shared_Pointer& rhs)
		//{
		//	if (&rhs == this)
		//		return *this;

		//	decrease();
		//	this->data = rhs->data;
		//	this->count = rhs->count;
		//	increase();
		//}

		//template<typename T>
		//Shared_Pointer<T>::~Shared_Pointer()
		//{
		//	decrease();
		//}



	}
}