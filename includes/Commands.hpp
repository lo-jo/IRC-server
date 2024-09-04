#pragma once

# include "ft_irc.hpp"
# include "Client.hpp"
# include "Server.hpp"

bool	capLsCommand(Server &server, Client &client, std::vector<std::string> input);
bool	nickCommand(Server& server, Client &client, std::vector<std::string> input);
bool	userCommand(Server& server, Client &client, std::vector<std::string> input);
bool	whoisCommand(Server &server, Client &client, std::vector<std::string> input);
bool	passCommand(Server& server, Client &client, std::vector<std::string> input);
bool	pingCommand(Server &server, Client &client, std::vector<std::string> input);
bool	quitCommand(Server &server, Client &client, std::vector<std::string> input);
bool	joinCommand(Server &server, Client &client, std::vector<std::string> input);
bool	privmsgCommand(Server &server, Client &client, std::vector<std::string> input);
bool	kickCommand(Server &server, Client &client, std::vector<std::string> input);
bool	topicCommand(Server &server, Client &client, std::vector<std::string> input);
bool	modeCommand(Server &server, Client &client, std::vector<std::string> input);
bool	inviteCommand(Server &server, Client &client, std::vector<std::string> input);
bool	partCommand(Server &server, Client &client, std::vector<std::string> input);
bool	operCommand(Server &server, Client &client, std::vector<std::string> input);
