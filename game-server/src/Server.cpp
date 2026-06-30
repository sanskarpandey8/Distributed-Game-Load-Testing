#include "../include/Server.h"
#include "../include/Protocol.h"
#include "../include/ClientSession.h"
#include "../include/Metrics.h"
#include "../include/Logger.h"

#include <iostream>
#include <thread>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

Server::Server(int port)
{
    this->port = port;
    serverSocket = INVALID_SOCKET;
}

Server::~Server()
{
    if (serverSocket != INVALID_SOCKET)
    {
        closesocket(serverSocket);
    }

    WSACleanup();
}

bool Server::start()
{
    Logger::info("Initializing Winsock...");

    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        Logger::error("Failed to initialize Winsock.");
        return false;
    }

    Logger::info("Creating server socket...");

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (serverSocket == INVALID_SOCKET)
    {
        Logger::error("Failed to create server socket.");
        return false;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    Logger::info("Binding socket...");

    if (bind(
            serverSocket,
            reinterpret_cast<sockaddr*>(&serverAddress),
            sizeof(serverAddress))
        == SOCKET_ERROR)
    {
        Logger::error("Bind failed.");
        return false;
    }

    Logger::info("Starting listener...");

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        Logger::error("Listen failed.");
        return false;
    }

    cout << "\n====================================\n";
    cout << "Game Server Started Successfully\n";
    cout << "Listening on Port " << port << "\n";
    cout << "====================================\n\n";

    return true;
}

void Server::run()
{
    Logger::info("Waiting for players...");

    while (true)
    {
        SOCKET clientSocket = accept(
            serverSocket,
            nullptr,
            nullptr
        );

        if (clientSocket == INVALID_SOCKET)
        {
            Logger::error("Failed to accept client.");
            continue;
        }

        Metrics::clientConnected();

        Logger::info(
            "New client connected. Active Clients: " +
            to_string(Metrics::getActiveClients())
        );

        thread clientThread(
            &Server::handleClient,
            this,
            clientSocket
        );

        clientThread.detach();
    }
}

void Server::handleClient(SOCKET clientSocket)
{
    ClientSession session(clientSocket);

    Logger::info("Client thread started.");

    char buffer[1024];

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));

        int bytesReceived = recv(
            clientSocket,
            buffer,
            sizeof(buffer) - 1,
            0
        );

        if (bytesReceived <= 0)
        {
            Logger::warning("Client disconnected.");
            break;
        }

        buffer[bytesReceived] = '\0';

        string command(buffer);

        // Remove trailing newline / carriage return
        while (!command.empty() &&
              (command.back() == '\n' ||
               command.back() == '\r'))
        {
            command.pop_back();
        }

        Metrics::messageReceived();

        Logger::info("Received: " + command);

        string response =
            Protocol::processCommand(
                command,
                session
            );

        Logger::info("Sending: " + response);

        Metrics::messageSent();

        send(
            clientSocket,
            response.c_str(),
            static_cast<int>(response.length()),
            0
        );
    }

    Metrics::clientDisconnected();

    Logger::info(
        "Client disconnected. Active Clients: " +
        to_string(Metrics::getActiveClients())
    );

    closesocket(clientSocket);
}