#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

std::mutex mtx;
std::condition_variable cv;
bool data_ready = false;

void producer() {
    std::cout << "Start producer\n";
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate some work
    std::cout << "producer dbrojao\n";
    {
        std::lock_guard<std::mutex> lock(mtx);
        data_ready = true;
    }
    cv.notify_one(); // Notify the consumer that data is ready
}

void consumer() {
    std::cout << "Start consumer\n";
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return data_ready; }); // Wait until data is ready
    std::cout << "Data is ready\n";
}

int main() {
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}