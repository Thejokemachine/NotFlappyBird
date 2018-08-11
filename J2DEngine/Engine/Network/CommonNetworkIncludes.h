#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#include "NetMessageManager.h"
#include "NetMessages.h"

#pragma comment(lib, "Ws2_32.lib")

#define PRINT(text) std::cout << (text) << std::endl;

#define MAX_BUFFER_SIZE 512
#define SOCKET_BUFFER_SIZE 65000