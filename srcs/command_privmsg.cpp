#include "../includes/ft_irc.hpp"
#include "../includes/Client.hpp"
#include "../includes/Defines.hpp"

bool	privmsgCommand(Server &server, Client &client, std::vector<std::string> input)
{
	std::string				msg;
	Client	*findClient = server.findClient(client.getNickname());
	bool	flag = true;

	if (input.size() < 3)
	{
		msg = ERR_NEEDMOREPARAMS(client.getNickname(), "PRIVMSG");
		servSend(msg, client.getClientSocket());
		flag = false;
	}
	// si target est une channel
	if (input[1][0] == '#'){
		if (server.findChannel(input[1]) == NULL)
		{
			msg = ERR_NOSUCHNICK(client.getNickname(), input[1]);
			servSend(msg, client.getClientSocket());
			flag = false;
		}
		else
		{
			std::string messagePrivate;
			if (server.findChannel(input[1])->findMember(&client) != NULL)
			{
				messagePrivate = joinAllMsg(input, 2);
				msg = PRIVMSG_MESSAGE(client.getNickname(), input[1], messagePrivate);
				server.findChannel(input[1])->sendMessageToMembers(&client, msg);
			}
			else
			{
				msg = ERR_NOTONCHANNEL(findClient->getNickname(), input[1]);
				servSend(msg, client.getClientSocket());
				flag = false;
			}
		}
	}
	// si target est un user
	else {
		std::string messagePrivate;
		if (server.findClient(input[1]) != NULL){
			messagePrivate = joinAllMsg(input, 2);
			msg = PRIVMSG_MESSAGE(client.getNickname(), input[1], messagePrivate);
			servSend(msg, server.findClient(input[1])->getClientSocket());
		}
		else 
		{
			msg = ERR_NOSUCHNICK(client.getNickname(), input[1]);
			servSend(msg, client.getClientSocket());
			flag = false;
		}

	}
	return (flag);
}
