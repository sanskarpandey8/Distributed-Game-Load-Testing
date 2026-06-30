#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "ClientSession.h"

#include <unordered_map>
#include <memory>
#include <mutex>

class ClientManager
{
public:
    void addClient(std::shared_ptr<ClientSession> client);

    void removeClient(SOCKET socket);

    std::shared_ptr<ClientSession> getClient(SOCKET socket);

    int getClientCount();

private:
    std::unordered_map<SOCKET, std::shared_ptr<ClientSession>> clients;

    std::mutex clientsMutex;
};

#endif