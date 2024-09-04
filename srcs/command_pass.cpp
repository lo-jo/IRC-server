#include "../includes/ft_irc.hpp"
#include "../includes/Client.hpp"
#include "../includes/Defines.hpp"

bool passCommand(Server &server, Client &client, std::vector<std::string> input){
	
	std::string		msg;
	bool			flag = true;

	if (client.getAuthStatus() == true)
	{ // cannot re-register
		msg = ERR_ALREADYREGISTERED(client.getNickname());
		servSend(msg, client.getClientSocket());
		flag = false;
	}
	else if (client.getRegistrationStatus() != CAP_RECEIVED)
	{
		msg = ERR_NOTREGISTERED(client.getNickname());
		client.setRegistrationStatus(START);
		servSend(msg, client.getClientSocket());
		flag = false;
	}
	else if (client.getAuthStatus() == false)
	{
		if (input.size() != 2){ // need more parameters
			msg = ERR_NEEDMOREPARAMS(client.getNickname(), input[0]);
			servSend(msg, client.getClientSocket());
			flag = false;
		}
		if (server.getPass() != input[1]){
			msg = ERR_PASSWDMISMATCH(client.getNickname(), client.getUserName());
			servSend(msg, client.getClientSocket());
			flag = false;
		}
		client.setRegistrationStatus(client.getRegistrationStatus() | PASS_RECEIVED);
	}
	return (flag);
}
