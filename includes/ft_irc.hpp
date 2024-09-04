#pragma once

// ************** CPP LIBRARY *******************
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstring>
#include <csignal>
#include <sstream>

// ************** C LIBRARY *********************
#include <sys/types.h>
#include <unistd.h> // close
#include <stdio.h>
#include <cstdlib> //std::atoi
#include <netinet/in.h> //sockaddr
#include <arpa/inet.h> // inet_addr()
#include <sys/socket.h> // listen
#include <poll.h>
#include <string.h> // memset
#include <cerrno> // errno

// **************** ANSI COLORS *****************
#define WBG "\x1B[47m"
#define RBG "\e[41m"
#define RESET "\x1B[0m"
#define BOLD "\x1B[1m"
#define MAG "\x1B[35m"
#define YEL "\x1B[33m"
#define RED "\x1B[31m"
#define BLK "\e[0;30m"
#define GREEN "\e[0;32m"
#define BLUE "\e[0;34m"
#define WHITE "\e[1m"
// **************** HEADER FILES ****************
#include "Server.hpp"
#include "Client.hpp"
#include "Defines.hpp"
#include "Commands.hpp"
#include "Channel.hpp"

# define CLIENT_MAX 100

void			servSend(std::string msg, int socket);
std::string		itos(int nb);
std::string		joinAllMsg(std::vector<std::string> input, int start);
void			printvect(std::vector<std::string> input);
bool			IsAuth(std::string command);
bool			findDelimiter(std::string input, std::string delimiter);
std::string		getCommand(std::string input, std::string delimiter);
