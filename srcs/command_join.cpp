#include "../includes/ft_irc.hpp"

bool	joinCommand(Server &server, Client &client, std::vector<std::string> input)
{
	std::string				msg;
	bool					flag = true;
	Channel					*newChannel;
	std::string				channelname;

	if (input[1][0] != '#')
		channelname = "#" + input[1];
	else
		channelname = input[1];
	if (input.size() < 2)
	{
		msg =ERR_NEEDMOREPARAMS(client.getNickname(), "JOIN");
		flag = false;
	}
	else
		msg = JOIN_MESSAGE(client.getNickname(), client.getUserName(), channelname);
	if (server.findChannel(input[1]) == NULL)
	{
		newChannel = new Channel(channelname, &server);
		server.addChannel(newChannel);// TODO free channel
		newChannel->addOwner(&client);
		newChannel->addOperatorMember(&client);
		servSend(msg, client.getClientSocket());
	}
	else
	{
		if (server.findChannel(input[1])->getChanMode("INVITE") && !server.findChannel(input[1])->isInvited(client.getNickname())){
			msg = ERR_INVITEONLYCHAN(client.getNickname(), input[1]);
			servSend(msg, client.getClientSocket());
			return false;
		}
		if ((server.findChannel(input[1])->getChanMode("LIMIT")) && (static_cast<int>(server.findChannel(input[1])->getChannelMembers().size()) >= server.findChannel(input[1])->getUserMax())){
			msg = ERR_CHANNELISFULL(client.getNickname(), input[1]);
			servSend(msg, client.getClientSocket());
			return false;
		}
		if (server.findChannel(input[1])->getChanMode("KEY")){
			if ((input.size() < 3) || (input[2] != server.findChannel(input[1])->getPassword())){
				msg = ERR_BADCHANNELKEY(client.getNickname(), input[1]);
				servSend(msg, client.getClientSocket());
				return false;
			}
		}
		server.findChannel(input[1])->addMember(&client);
		servSend(msg, client.getClientSocket());
		server.findChannel(input[1])->sendMessageToMembers(&client, msg);
	}
	return (flag);
}
