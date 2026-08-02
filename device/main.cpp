#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

// enum State {
//     NORMAL,
//     WARNING,
//     ALARM
// };

// std::string stateToString(State s) {
//     if (s == NORMAL) return "NORMAL";
//     if (s == WARNING) return "WARNING";
//     if (s == ALARM) return "ALARM"  ;
//     return "UNKNOW";
// }

int main() {
    // std::cout << "Device starting up..." << std::endl;

    // while (true) {
    //     float temperature = 20.0 + (std::rand() % 100) / 10.0;

    //     State currentState;
    //     if (temperature >= 28.00)
    //     {
    //         currentState = ALARM;
    //     }
    //     else if (temperature >= 25.00)
    //     {
    //         currentState = WARNING;
    //     }
    //     else
    //     {
    //         currentState = NORMAL;
    //     }
        
        
    //     std::cout << "Temperature: " << temperature << " C | State: " << stateToString(currentState) << std::endl;
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
 
    // }
        WSADATA wsaData;
        int startupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (startupResult !=0)
        {
            std::cout << "WSAStartup failed: " << startupResult << std::endl;
        }

        std::cout << "Winsock initialized successfully." << std::endl;

        SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

        if (serverSocket == INVALID_SOCKET)
            {
                std::cout << "Failed to create socket." << std::endl;
                WSACleanup();
                return 1;
            }
        std::cout << "Socket created successfully." << std::endl;

        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(8080);

        int bindResult = bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));

        if (bindResult == SOCKET_ERROR) {
            std::cout << "Bind failed." << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "Socket bound to port 8080." << std::endl;

        int listenResult = listen(serverSocket, SOMAXCONN);

        if (listenResult == SOCKET_ERROR) {
            std::cout << "Listen failed." << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "Listening on port 8080..." << std::endl;

        std::cout << "Waiting for a connection..." << std::endl;

        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket == INVALID_SOCKET) {
            std::cout << "Accept failed." << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "Client connected!" << std::endl;

        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup;
        return 0;
}