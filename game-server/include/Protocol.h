#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

class ClientSession;

class Protocol
{
public:
    static std::string processCommand(
        const std::string& command,
        ClientSession& session
    );
};

#endif