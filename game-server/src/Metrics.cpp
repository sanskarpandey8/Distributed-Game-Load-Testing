#include "../include/Metrics.h"

using namespace std;

atomic<int> Metrics::activeClients{0};
atomic<int> Metrics::peakClients{0};

atomic<long long> Metrics::receivedMessages{0};
atomic<long long> Metrics::sentMessages{0};

void Metrics::clientConnected()
{
    int current = ++activeClients;

    if (current > peakClients)
    {
        peakClients = current;
    }
}

void Metrics::clientDisconnected()
{
    --activeClients;
}

void Metrics::messageReceived()
{
    ++receivedMessages;
}

void Metrics::messageSent()
{
    ++sentMessages;
}

int Metrics::getActiveClients()
{
    return activeClients;
}

int Metrics::getPeakClients()
{
    return peakClients;
}

long long Metrics::getMessagesReceived()
{
    return receivedMessages;
}

long long Metrics::getMessagesSent()
{
    return sentMessages;
}