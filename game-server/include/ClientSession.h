#ifndef CLIENTSESSION_H
#define CLIENTSESSION_H

#include <winsock2.h>
#include <string>

class ClientSession
{
public:
    explicit ClientSession(SOCKET socket);

    SOCKET getSocket() const;

    void setUsername(const std::string& username);
    std::string getUsername() const;

    bool isLoggedIn() const;

    // Player Movement
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    // Player State
    int getX() const;
    int getY() const;
    int getHealth() const;

private:
    SOCKET clientSocket;

    std::string username;

    bool loggedIn;

    int health;

    int positionX;

    int positionY;
};

#endif