#include "../includes/ft_irc.hpp"
#include "../includes/Client.hpp"
#include "../includes/Defines.hpp"


bool pingCommand(Server &server, Client &client, std::vector<std::string> input){
	(void) server;

	std::string msg;
	if (input.size() != 2){
		msg = ERR_NEEDMOREPARAMS(client.getNickname(), input[0]);
		servSend(msg, client.getClientSocket());
		return false;
	}
	msg = PONG(input[1]);
	servSend(msg, client.getClientSocket());
	return true;
}
