#include "../include/ClientManager.h"

using namespace std;

void ClientManager::addClient(shared_ptr<ClientSession> client)
{
    lock_guard<mutex> lock(clientsMutex);

    clients[client->getSocket()] = client;
}

void ClientManager::removeClient(SOCKET socket)
{
    lock_guard<mutex> lock(clientsMutex);

    clients.erase(socket);
}

shared_ptr<ClientSession> ClientManager::getClient(SOCKET socket)
{
    lock_guard<mutex> lock(clientsMutex);

    auto it = clients.find(socket);

    if (it == clients.end())
        return nullptr;

    return it->second;
}

int ClientManager::getClientCount()
{
    lock_guard<mutex> lock(clientsMutex);

    return static_cast<int>(clients.size());
}