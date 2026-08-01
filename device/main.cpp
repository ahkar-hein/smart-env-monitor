#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <string>

enum State {
    NORMAL,
    WARNING,
    ALARM
};

std::string stateToString(State s) {
    if (s == NORMAL) return "NORMAL";
    if (s == WARNING) return "WARNING";
    if (s == ALARM) return "ALARM"  ;
    return "UNKNOW";
}

int main() {
    std::cout << "Device starting up..." << std::endl;

    while (true) {
        float temperature = 20.0 + (std::rand() % 100) / 10.0;

        State currentState;
        if (temperature >= 28.00)
        {
            currentState = ALARM;
        }
        else if (temperature >= 25.00)
        {
            currentState = WARNING;
        }
        else
        {
            currentState = NORMAL;
        }
        
        
        std::cout << "Temperature: " << temperature << " C | State: " << stateToString(currentState) << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}