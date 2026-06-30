#include "../include/Protocol.h"
#include "../include/ClientSession.h"

#include <iostream>

using namespace std;

string Protocol::processCommand(
    const string& command,
    ClientSession& session)
{
    cout << "\n---------------------------------\n";
    cout << "Processing Command : " << command << endl;
    cout << "Logged In Before   : "
         << (session.isLoggedIn() ? "YES" : "NO")
         << endl;

    // LOGIN
    if (command.rfind("LOGIN ", 0) == 0)
    {
        string username = command.substr(6);

        session.setUsername(username);

        return "WELCOME " + username;
    }

    if (!session.isLoggedIn())
    {
        return "PLEASE_LOGIN_FIRST";
    }

    // -----------------------
    // MOVEMENT
    // -----------------------

    if (command == "MOVE UP")
    {
        session.moveUp();

        return "POSITION " +
               to_string(session.getX()) +
               " " +
               to_string(session.getY());
    }

    if (command == "MOVE DOWN")
    {
        session.moveDown();

        return "POSITION " +
               to_string(session.getX()) +
               " " +
               to_string(session.getY());
    }

    if (command == "MOVE LEFT")
    {
        session.moveLeft();

        return "POSITION " +
               to_string(session.getX()) +
               " " +
               to_string(session.getY());
    }

    if (command == "MOVE RIGHT")
    {
        session.moveRight();

        return "POSITION " +
               to_string(session.getX()) +
               " " +
               to_string(session.getY());
    }

    // -----------------------
    // CHAT
    // -----------------------

    if (command.rfind("CHAT ", 0) == 0)
    {
        return "CHAT_OK";
    }

    // -----------------------
    // ATTACK
    // -----------------------

    if (command.rfind("ATTACK ", 0) == 0)
    {
        return "ATTACK_OK HP=" +
               to_string(session.getHealth());
    }

    // -----------------------
    // STATUS
    // -----------------------

    if (command == "STATUS")
    {
        return "PLAYER " +
               session.getUsername() +
               " HP=" +
               to_string(session.getHealth()) +
               " X=" +
               to_string(session.getX()) +
               " Y=" +
               to_string(session.getY());
    }

    return "UNKNOWN_COMMAND";
}