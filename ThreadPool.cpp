#include "ThreadPool.h"

ThreadPool::ThreadPool(std::size_t numThreads) {
	start(numThreads);
}

ThreadPool::~ThreadPool() {
	stop();
}

void ThreadPool::start(std::size_t numThreads) {
	for (size_t i = 0; i < numThreads; ++i) {
		threads.emplace_back(
			[=]() {
				while (true) {
					Task task;

					{
						std::unique_lock<std::mutex> lock{ eventMutex };
						eventVar.wait(lock, [=] {
							return stopping || !tasks.empty();
							});
						if (stopping && tasks.empty()) {
							break;
						}
						task = std::move(tasks.front());
						tasks.pop();
					}
					task();
				}
			}
		);
	}
}

void ThreadPool::stop() {
	{
		std::unique_lock<std::mutex> lock{ eventMutex };
		stopping = true;
	}
	eventVar.notify_all();
	for (std::thread& thread : threads) {
		thread.join();
	}
}
