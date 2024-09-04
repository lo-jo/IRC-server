# include "../includes/ft_irc.hpp"
# include "../includes/Client.hpp"
# include "../includes/Server.hpp"

bool	kickCommand(Server &server, Client &client, std::vector<std::string> input)
{
	std::string	msg;
	std::string reason = "";
	Channel	*channel = server.findChannel(input[1]);
	Client	*foundClient = server.findClient(input[2]);
	bool	flag = true;

	if (channel == NULL){
		msg = ERR_NOSUCHCHANNEL(client.getNickname(), input[1]);
		servSend(msg, client.getClientSocket());
		flag = false;
	}
	else if (channel->findMember(client.getNickname()) == NULL){ // if the kicker is not on channel
		msg = ERR_NOTONCHANNEL(client.getNickname(), input[1]);
		servSend(msg, client.getClientSocket());
		flag = false;
	}
	else if (channel->findMember(foundClient) == NULL) // if the user being kicked is not on the channel
	{
		msg = ERR_USERNOTINCHANNEL(client.getNickname(), input[0]);
		servSend(msg, client.getClientSocket());
		flag = false;
	}
	else if (input.size() < 3)
	{
		msg = ERR_NEEDMOREPARAMS(client.getNickname(), input[0]);
		servSend(msg, client.getClientSocket());
		flag = false;
	}
	else if(!channel->isOperator(client.getNickname()))
	{
		msg = ERR_CHANOPRIVSNEEDED(client.getNickname(), input[1]);
		servSend(msg, client.getClientSocket());
		flag = false;
	}
	else
	{
		if (input.size() > 3)
			reason = joinAllMsg(input, 3);
		msg = KICK(client.getNickname(), input[1], input[2], reason);
		servSend(msg, client.getClientSocket());
		channel->sendMessageToMembers(&client, msg);
		channel->removeMember(server.findClient(input[2]));
	}
	return (flag);
}
