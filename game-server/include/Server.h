#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>

class Server
{
public:
    Server(int port);
    ~Server();

    bool start();
    void run();

private:
    void handleClient(SOCKET clientSocket);

    int port;
    SOCKET serverSocket;
};

#endif