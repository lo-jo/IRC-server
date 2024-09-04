#include "../includes/ft_irc.hpp"

bool	capLsCommand(Server &server, Client &client, std::vector<std::string> input)
{
	std::string		msg;
	bool			flag = true;

	(void)server;
	(void)input;
	if (client.getAuthStatus() == true)
	{
		msg = ERR_ALREADYREGISTERED(client.getNickname());
		flag = false;
	}
	else if (client.getRegistrationStatus() != START)
	{
		msg = msg = ERR_NOTREGISTERED(client.getNickname());
		flag = false;
	}
	else
		client.setRegistrationStatus(CAP_RECEIVED);
	servSend(msg, client.getClientSocket());
	return (flag);
}
