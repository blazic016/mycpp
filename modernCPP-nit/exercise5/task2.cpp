#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mutex;
std::condition_variable cv;

int var1 = 0;
int var2 = 0;

void FunWrite() {
    while (true) {
        {
            mutex.lock(); // old school
            var1 = 1;
            var2 = 2;

            std::cout << "[write] (" << var1 << ", " << var2 << ")\n";

            // odblokiraj sve tredove (u ovom slucaju samo reader)
            cv.notify_all();
            mutex.unlock();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));

        {
            std::lock_guard<std::mutex> lock(mutex);
            var1 = 3;
            var2 = 4;

            // odblokiraj read thread
            cv.notify_one(); // 
            std::cout << "[write] (" << var1 << ", " << var2 << ")\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));

        {
            std::lock_guard<std::mutex> lock(mutex);
            var1 = 5;
            var2 = 6;

            // odblokiraj read thread
            cv.notify_one(); // 
            std::cout << "[write] (" << var1 << ", " << var2 << ")\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void FunRead() {
    while (true) {
        std::unique_lock<std::mutex> lock(mutex);

        // Cekaj dok se ne dodeli vrednost razlicita od 0 u write threadu
        cv.wait(lock, [&] () { return var1 != 0; });

        int sum = var1 + var2;
        std::cout << "[read] Sum = " << sum << "\n----------------\n";

        var1 = 0;
        var2 = 0;
    }
}

int main() {
    std::thread write(FunWrite);
    std::thread read(FunRead);

    write.join();
    read.join();

    return 0;
}
