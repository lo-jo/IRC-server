#include "../includes/ft_irc.hpp"
#include "../includes/Client.hpp"
#include "../includes/Defines.hpp"

bool	whoisCommand(Server &server, Client &client, std::vector<std::string> input) //@TODO: Need to be expended !! (RPL_NAMREPLY)
{
	Client			*target;
	std::string		msg;
	bool			flag = true;

	target = server.findClient(input[1]);
	if (target == NULL)
	{
		msg = ERR_NOSUCHNICK(client.getNickname(), input[1]);
		flag = false;
	}
	msg = RPL_ENDOFWHOIS(client.getNickname());
	servSend(msg, client.getClientSocket());
	return (flag);
}