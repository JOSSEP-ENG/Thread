/*c++ multi-Thread source exmaple*/
#include <iostream>
#include <thread>
#include <mutex>

int sharedResource = 0;
std::mutex mtx;

void threadMain(int threadID) {
	for(int i=0; i<10000000; i++) {
		mtx.lock();
		sharedResource++;
		mtx.unlock();
	}
}

int main() {
	std::thread thread1(threadMain, 1);	
	std::thread thread2(threadMain, 2);
	std::thread thread3(threadMain, 3);

	thread1.join();
	thread2.join();
	thread3.join();
	
	std::cout << "result : " << sharedResource << std::endl;
	return EXIT_SUCCESS;
}
