#include <iostream>
#include <thread>
#include <chrono>

void FunThread1 () {
    std::thread::id tid = std::this_thread::get_id();
    std::chrono::seconds s(3);
    std::cout << "[FunThread1] Thread ID: " << tid << std::endl;

    std::this_thread::sleep_for(s);
    std::cout << "Print 1" <<  std::endl;
}

void FunThread2 (std::thread* joinThread) {
    std::thread::id tid = std::this_thread::get_id();
    std::chrono::seconds s(3);
    std::cout << "[FunThread2] Thread ID: " << tid << std::endl;

    if(joinThread) {
        // Cekaj da thread1 zavrsi
        joinThread->join();
    }
    std::cout << "Print 2 " << std::endl;
}

void FunThread3 (std::thread* joinThread) {
    std::thread::id tid = std::this_thread::get_id();
    std::chrono::seconds s(3);
    std::cout << "[FunThread3] Thread ID: " << tid << std::endl;

    if(joinThread) {
        // Cekaj da thread2 zavrsi
        joinThread->join();
    }
    std::cout << "Print 3 " << std::endl;
}

int main() {
    std::thread* thread1 = new std::thread(FunThread1);
    std::thread* thread2 = new std::thread(FunThread2, thread1);
    std::thread* thread3 = new std::thread(FunThread3, thread2);

    // Cekaj da zavrsi thread3, tj svi tredovi
    thread3->join();

    delete thread1;
    delete thread2;
    delete thread3;

    return 0;
}
