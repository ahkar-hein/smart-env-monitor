#include <iostream>
#include <chrono>
#include <thread>

int main() {
    std::cout << "Device starting up..." << std::endl;

    while (true) {
        std::cout << "Reading Sensor..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}