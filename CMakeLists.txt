cmake_minimum_required(VERSION 4.3)
project(client_server C)

set(CMAKE_C_STANDARD 11)
add_executable(client client.c)
add_executable(server server.c)