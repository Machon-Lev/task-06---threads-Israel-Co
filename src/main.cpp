#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

struct Message {
	size_t _tid;
	double _val;
	bool _isFinish;
};


std::size_t numThreads;
std::list<Message> messages;
std::mutex mtx;
std::condition_variable cv;


/// <summary>
/// producer function
/// </summary>
/// <param name="milliSecToWait">millisec to suspend the function</param>
void producer(size_t milliSecToWait) 
{
	struct Message msg;
	msg._tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
	msg._val = static_cast<double>(msg._tid);
	msg._isFinish = false;

	while (msg._val > 0) 
	{
		{
			std::lock_guard<std::mutex> lock(mtx);
			messages.push_back(msg);
		}
		cv.notify_all();
		msg._val /= 10;

		std::this_thread::sleep_for(std::chrono::milliseconds(milliSecToWait));
	}

	msg._isFinish = true;
	{
		std::lock_guard<std::mutex> lock(mtx);
		messages.push_back(msg);
	}
	cv.notify_all();
}

/// <summary>
/// consumer function
/// </summary>
void consumer() {
	int threadFinishCounter = 0;

	while (threadFinishCounter < numThreads) {
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [&]() { return !messages.empty(); });

		struct Message msg = messages.front();
		messages.pop_front();

		lock.unlock();

		if (msg._isFinish)
		{
			std::cout << msg._tid << " finished " << std::endl;
			++threadFinishCounter;
			continue;
		}

		std::cout << msg._tid << " sent: " << msg._val << std::endl;
	}
}

int main() {
	numThreads = 2;

	// Create threads
	std::thread consumer_thread(consumer);
	std::thread producer_thread1(producer, 20);
	std::thread producer_thread2(producer, 33);

	producer_thread1.join();
	producer_thread2.join();
	consumer_thread.join();

	return 0;
}