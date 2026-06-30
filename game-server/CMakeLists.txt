cmake_minimum_required(VERSION 3.20)

project(GameServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(GameServer
    src/main.cpp
    src/Server.cpp
    src/Protocol.cpp
    src/ClientSession.cpp
    src/Logger.cpp
    src/ClientManager.cpp
    src/Metrics.cpp
    src/MetricsPrinter.cpp
)

target_link_libraries(GameServer
    PRIVATE
    Threads::Threads
    ws2_32
)