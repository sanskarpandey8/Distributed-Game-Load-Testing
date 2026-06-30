#include "../include/ClientSession.h"

using namespace std;

ClientSession::ClientSession(SOCKET socket)
{
    clientSocket = socket;

    loggedIn = false;

    username = "";

    health = 100;

    positionX = 0;
    positionY = 0;
}

SOCKET ClientSession::getSocket() const
{
    return clientSocket;
}

void ClientSession::setUsername(const string& name)
{
    username = name;
    loggedIn = true;
}

string ClientSession::getUsername() const
{
    return username;
}

bool ClientSession::isLoggedIn() const
{
    return loggedIn;
}

// ----------------------
// Movement
// ----------------------

void ClientSession::moveUp()
{
    positionY++;
}

void ClientSession::moveDown()
{
    positionY--;
}

void ClientSession::moveLeft()
{
    positionX--;
}

void ClientSession::moveRight()
{
    positionX++;
}

// ----------------------
// Getters
// ----------------------

int ClientSession::getX() const
{
    return positionX;
}

int ClientSession::getY() const
{
    return positionY;
}

int ClientSession::getHealth() const
{
    return health;
}