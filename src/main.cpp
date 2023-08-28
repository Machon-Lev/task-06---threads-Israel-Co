#include <mutex>
#include <list>
#include 
using std::cin
using std::cout
using std::thread


struct Message {
	size_t _tid;
	double _val;
	bool _isFinish;
};


const std::size_t numThreads;
std::list<msg> messages;
std::mutex mtx;
std::condition_variable cv;

void producer() {
	struct Message msg;
	msg._tid = std::this_thread::get_id();
	msg._val = static_cast<double>(std::hash<std::thread::id>{}(std::this_thread::get_id()));
	msg._isFinish = false;

	while (msg._val) {
		{
			std::lock_guard<std::mutex>(mtx);
			messages.push_back
		}
		cv.notify_all();

		msg._val /= 10;
		std::this_thread::sleep_for(std::chrono::milliseconds(_millisecondsToWait));
	}

	msg._isFinish = true;
	{
		std::lock_guard<std::mutex> lock(mtx);
		shared_queue.push(myMsg);
	}
	cv.notify_all();


}


int main() {
	Consumer cons;
	Prduceer producer_1;
	Prduceer producer_2;

	return 0;
}