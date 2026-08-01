#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

int main() {
    std::cout << "Device starting up..." << std::endl;

    while (true) {
        float temperature = 20.0 + (std::rand() % 100) / 10.0;
        std::cout << "Temperature: " << temperature << " C" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}