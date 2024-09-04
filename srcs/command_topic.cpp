#include "../includes/ft_irc.hpp"

bool	setChannelTopic(Channel *channel, Client &client, Server &server, std::vector<std::string> input){
	std::string msg;
	std::string topic;
	(void)server;

	if ((channel->getChanMode("TOPIC") == 1) && (!channel->isOperator(client.getNickname()))){
		msg = ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->getChannelName());
		servSend(msg, client.getClientSocket());
		return false;
	}
	topic = joinAllMsg(input, 2);
	channel->setTopic(topic);
	msg = RPL_TOPIC(client.getNickname(), channel->getChannelName(), topic);
	servSend(msg, client.getClientSocket());
	channel->sendMessageToMembers(&client, msg);
	return true;
}


bool	topicCommand(Server &server, Client &client, std::vector<std::string> input){
	std::string msg;

	if (input.size() == 1){
		msg = ERR_NEEDMOREPARAMS(client.getNickname(), input[0]);
		servSend(msg, client.getClientSocket());
		return false;
	}

	else if (input.size() == 2){ // case <MODE> <#channel> : reply with topic that is set
		if (server.findChannel(input[1]) != NULL)
		{
			if (!server.findChannel(input[1])->getTopic().empty()){ // if there is a topic
				msg = RPL_TOPIC(client.getNickname(), server.findChannel(input[1])->getChannelName(), server.findChannel(input[1])->getTopic());
				servSend(msg, client.getClientSocket());
				return true;
			}
			msg = RPL_NOTOPIC(client.getNickname(), server.findChannel(input[1])->getChannelName());
			servSend(msg, client.getClientSocket());
			return true;
		}
		msg = ERR_NOSUCHCHANNEL(client.getNickname(), input[1]);
		servSend(msg, client.getClientSocket());
		return false;
	}

	else if (input.size() > 2){ // case <MODE> <#channel> <topic> : set the topic to <topic>
		if (server.findChannel(input[1]) != NULL){ // if channel is found
			if (server.findChannel(input[1])->findMember(client.getNickname()) != NULL)
				return (setChannelTopic(server.findChannel(input[1]), client, server, input));
			msg = ERR_NOTONCHANNEL(client.getNickname(), input[1]);
			servSend(msg, client.getClientSocket());
			std::cout << "Client is not a member of the channel" << std::endl;
			return false;
		}
		msg = ERR_NOSUCHCHANNEL(client.getNickname(), input[1]);
		servSend(msg, client.getClientSocket());
		return false;
	}
	return (true);
}
