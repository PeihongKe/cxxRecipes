#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_threading
#include <boost/test/unit_test.hpp>
#include "threading\threading.hpp"

// https://www.bogotobogo.com/cplusplus/C11/1_C11_creating_thread.php

BOOST_AUTO_TEST_CASE(thread_creating_join)
{
	std::thread t(&thread_function);
	std::cout << "main thread" << std::endl;
	t.join();
}

BOOST_AUTO_TEST_CASE(thread_creating_detach)
{
	std::thread t(&thread_function);
	std::cout << "main thread" << std::endl;
	t.detach();  // become a daemon thread
	// t.join();  error: cannot join after detach
	if (t.joinable())
		t.join();
}

BOOST_AUTO_TEST_CASE(thread_from_callable)
{
	functor f;
	std::thread t(f);
	// std::thread t( functor()); #  this does not work
	// std::thread t( (functor())); #  this works...
	std::cout << "main" << std::endl;
	t.join();
}

BOOST_AUTO_TEST_CASE(thread_param_by_value)
{
	std::string s = "Hello Kitty";
	std::thread t(&thread_function_with_param_value, s);	
	t.join();
	std::cout << "main thread message = " << s << std::endl;
}

BOOST_AUTO_TEST_CASE(threading_parma_by_ref_wrong)
{
	std::string s = "Hello Kitty";
	std::thread t(&thread_function_with_param_ref, s); // s is not modified by  thread_function_with_param_ref	
	t.join();
	std::cout << "main thread message = " << s << std::endl;
}


BOOST_AUTO_TEST_CASE(threading_parma_by_ref)
{
	std::string s = "Hello Kitty";
	std::thread t(&thread_function_with_param_ref, std::ref(s)); 
	t.join();
	std::cout << "main thread message = " << s << std::endl; // s is now modified by  thread_function_with_param_ref	
}

BOOST_AUTO_TEST_CASE(threading_parma_by_value_move)
{
	std::string s = "Hello Kitty";
	std::thread t(&thread_function_with_param_value, std::move(s));
	t.join();
	std::cout << "main thread message = " << s << std::endl;  // s is empty as it has been moved
}


BOOST_AUTO_TEST_CASE(thread_cannot_copy)
{
	std::thread t(&thread_function);
	t.join();
	// std::thread t2 = t; // compile error : does not support copy
}

BOOST_AUTO_TEST_CASE(thread_can_move)
{
	std::thread t(&thread_function);
	std::thread t2 = std::move(t); 
	t2.join();
	std::cout << "main thread_can_move";
}

BOOST_AUTO_TEST_CASE(thread_id)
{	
	std::thread t(&thread_function);
	std::cout << "main thread id " << std::this_thread::get_id() << std::endl;
	std::cout << "child thread id " << t.get_id() << std::endl;
	t.join();
}

BOOST_AUTO_TEST_CASE(thread_suggestion)
{
	std::cout << "Number of threads = "
		<< std::thread::hardware_concurrency() << std::endl; // out put 4 on my machine as the logical processsor is 4 (2 cores)
}

BOOST_AUTO_TEST_CASE(thread_from_lambda)
{
	std::thread t([]()
	{
		std::cout << "thread function from lambda" << std::endl;
	});

	std::cout << "main thread thread_from_lambda" << std::endl;
	t.join();
	
}