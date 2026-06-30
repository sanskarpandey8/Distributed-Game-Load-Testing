#ifndef METRICS_H
#define METRICS_H

#include <atomic>

class Metrics
{
public:
    static void clientConnected();
    static void clientDisconnected();

    static void messageReceived();
    static void messageSent();

    static int getActiveClients();
    static int getPeakClients();

    static long long getMessagesReceived();
    static long long getMessagesSent();

private:
    static std::atomic<int> activeClients;
    static std::atomic<int> peakClients;

    static std::atomic<long long> receivedMessages;
    static std::atomic<long long> sentMessages;
};

#endif