#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_threading
#include <boost/test/unit_test.hpp>
#include "threading\threading.hpp"
#include <mutex>


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


std::mutex qMutex;
std::condition_variable cv;
int Max_Queue_Length = 5;
int Max_Total = 10;
std::queue<int> queue;

class Producer
{
public:
	Producer(std::queue<int> & q) : m_prodCount(0), m_queue(q) 
	{
	}

	void run()
	{
		
		while (true )
		{
			std::unique_lock<std::mutex> lc(qMutex);
			if (m_prodCount > Max_Total)
			{
				std::cout << "producer stops producing " << std::endl;
				lc.unlock();
				cv.notify_all();
				break;
			}
			cv.wait(lc, [&] {
				auto isNotFull = (Max_Queue_Length != m_queue.size());
				if (!isNotFull)
				{
					std::cout << "producer is waiting " << std::endl;
				}
				return isNotFull; });


			auto newProdue = ++m_prodCount;
			std::cout << "Producing " << newProdue << std::endl;
			
			m_queue.push(newProdue);
			lc.unlock();
			cv.notify_all();
			std::this_thread::sleep_for(std::chrono::seconds(1));

		}
	}

private:
	int m_prodCount = 0;	
	std::queue<int>& m_queue;
 
};

class Consumer
{
public:
	Consumer(std::queue<int>& q): m_queue(q)
	{}

	void comsume()
	{
		
		while (true)
		{
			std::unique_lock<std::mutex> lc(qMutex);
			auto consumedProduct = m_queue.front();
			if (consumedProduct == Max_Total)
			{
				std::cout << "consumer stops consuming " << std::endl;
				lc.unlock();
				cv.notify_all();
				break;
			} 
			cv.wait(lc, [&] {
				auto isEmptyFull = ( 0 != m_queue.size());
				if (!isEmptyFull)
				{
					std::cout << "consumer is waiting " << std::endl;
				}
				return isEmptyFull; }
			);

			m_queue.pop();
			std::cout << "Comsuming	 " << consumedProduct << std::endl;
			

			lc.unlock();
			cv.notify_all();
			std::this_thread::sleep_for(std::chrono::seconds(1));
			

		}
	}

private:
	std::queue<int>& m_queue;
};

BOOST_AUTO_TEST_CASE(comsumer_producer)
{
	Producer p(queue);
	Consumer c(queue);
	std::cout << "Producer starts" << std::endl;
	std::thread t1(&Producer::run, p);
	
	std::this_thread::sleep_for(std::chrono::seconds(5));

	std::cout << "Consumer starts" << std::endl;
	std::thread t2(&Consumer::comsume, c);
	

	t1.join();
	t2.join();

	std::cout << "finished" << std::endl;

}


void FunctionToBeBlocked()
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "FunctionToBeBlocked starts" << std::endl;
	std::lock_guard<std::mutex> lc(qMutex);
	int i = 0;
	while (++i <=3)
	{
		std::cout << "FunctionToBeBlocked is running for " << i << " seconds" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "FunctionToBeBlocked finished" << std::endl;
}

void FunctionBlocking()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Blocking function starts but is blocked" << std::endl;	
	std::lock_guard<std::mutex> lc(qMutex);
	std::cout << "Blocking function - block for 5 seconds" << std::endl;
	int i = 0;
	while (++i <= 5)
	{
		std::cout << "blocking function is running for " << i << " seconds " << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Blocking function finished" << std::endl;
	
}


BOOST_AUTO_TEST_CASE(MutexTest)
{
	std::thread t1(FunctionToBeBlocked);
	std::thread t2(FunctionBlocking);

	t1.join();
	t2.join();
}