#include <iostream>
#include <thread>
#include <string.h>
#include <queue>

void thread_function()
{
	std::cout << "thead function" << std::endl;
}

void thread_function_with_param_value(std::string s)
{
	std::cout << "thead function with param value" << std::endl;
	std::cout << "message is  = " << s << std::endl;
}

void thread_function_with_param_ref(std::string& s)
{
	std::cout << "thead function with param ref" << std::endl;
	std::cout << "message is  = " << s << std::endl;
	s = "Hello Dog";
}

struct functor
{
	void operator()()
	{
		std::cout << "functor" << std::endl;
	}
};









