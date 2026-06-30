#include "../include/MetricsPrinter.h"
#include "../include/Metrics.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void MetricsPrinter::start()
{
    thread([]()
    {
        while (true)
        {
            this_thread::sleep_for(chrono::seconds(5));

            cout << "\n";
            cout << "=====================================\n";
            cout << "         SERVER METRICS\n";
            cout << "=====================================\n";

            cout << "Active Clients    : "
                 << Metrics::getActiveClients() << endl;

            cout << "Peak Clients      : "
                 << Metrics::getPeakClients() << endl;

            cout << "Messages Received : "
                 << Metrics::getMessagesReceived() << endl;

            cout << "Messages Sent     : "
                 << Metrics::getMessagesSent() << endl;

            cout << "=====================================\n";
        }

    }).detach();
}