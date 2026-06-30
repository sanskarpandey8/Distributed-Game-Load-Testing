#include <iostream>

#include "../include/Server.h"
#include "../include/MetricsPrinter.h"

using namespace std;

int main()
{
    cout << "=====================================\n";
    cout << " Distributed Game Server\n";
    cout << "=====================================\n\n";

    MetricsPrinter::start();

    Server server(8080);

    if (!server.start())
    {
        return 1;
    }

    server.run();

    return 0;
}