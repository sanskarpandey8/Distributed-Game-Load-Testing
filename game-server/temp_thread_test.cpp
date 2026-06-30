#include <thread>
#include <iostream>
int main() { std::thread t([]{}); t.detach(); std::cout<<"ok\n"; }
