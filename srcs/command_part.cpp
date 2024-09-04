#include "../includes/ft_irc.hpp"

// #define PART_MESSAGE(nickName, chan) (std::string(":") + nickName + " PART " + chan + "\r\n")

bool	partCommand(Server &server, Client &client, std::vector<std::string> input)
{
	std::string				msg;
	std::string				reason = "";
	Channel					*channel;
	bool					flag = true;

	if (server.findChannel(input[1]) == NULL)
	{
		msg = ERR_NOSUCHCHANNEL(client.getNickname(), input[1]);
		servSend(msg, client.getClientSocket());
		flag = false;
	}
	else
	{
		if (input.size() >= 3)
			reason = joinAllMsg(input, 2);
		msg = PART_MESSAGE(client.getNickname(), client.getUserName(), input[1], reason);
		channel = server.findChannel(input[1]);
		channel->sendMessageToMembers(&client, msg);
		servSend(msg, client.getClientSocket());
		channel->removeMember(&client);
	}
	return (flag);
}
