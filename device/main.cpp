#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

enum State {
    NORMAL,
    WARNING,
    ALARM
};

std::string stateToString(State s) {
    if (s == NORMAL) return "NORMAL";
    if (s == WARNING) return "WARNING";
    if (s == ALARM) return "ALARM";
    return "UNKNOWN";
}

int main() {
    WSADATA wsaData;
    int startupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (startupResult != 0) {
        std::cout << "WSAStartup failed: " << startupResult << std::endl;
        return 1;
    }

    std::cout << "Winsock initialized successfully." << std::endl;

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == INVALID_SOCKET) {
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
    
    u_long mode = 1;
    ioctlsocket(clientSocket, FIONBIO, &mode);

    std::srand(std::time(nullptr));

    while (true) {
        float temperature = 20.0 + (std::rand() % 100) / 10.0;

        State currentState;
        if (temperature >= 28.0) {
            currentState = ALARM;
        } else if (temperature >= 25.0) {
            currentState = WARNING;
        } else {
            currentState = NORMAL;
        }

        std::string message = "Temperature: " + std::to_string(temperature) + " C | State: " + stateToString(currentState) + "\n";

        send(clientSocket, message.c_str(), message.length(), 0);\

        char recvBuffer[256];
        int bytesReceived = recv(clientSocket, recvBuffer, sizeof(recvBuffer) -1, 0);

        if (bytesReceived > 0) {
            recvBuffer[bytesReceived] = '\0';
            std::cout << "Received command: " << recvBuffer << std::endl;
        }

        std::cout << "Sent: " << message;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}