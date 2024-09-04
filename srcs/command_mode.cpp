#include "../includes/ft_irc.hpp"

# define INVITE 1
# define TOPIC 2
# define KEY 4
# define OPERATOR 8
# define LIMIT 16

bool	sendChanMode(Server &server, Client &client, std::vector<std::string> input){
	std::string msg;
	Channel *channel = server.findChannel(input[1]);

	std::string mode;
	std::string modeArg;

	mode = std::string("+") + (channel->getChanMode("TOPIC") ? "t" : "") + (channel->getChanMode("INVITE") ? "i" : "") + (channel->getChanMode("LIMIT") ? "l" : "") + (channel->getChanMode("KEY") ? "k" : "");
	modeArg = std::string(" ") + (channel->getChanMode("LIMIT") ? (itos(channel->getUserMax())) : "") + " " + (channel->getChanMode("KEY") ? channel->getPassword() : "");	
	msg = RPL_CHANNELMODEIS(client.getNickname(), channel->getChannelName(), mode, modeArg);
	servSend(msg, client.getClientSocket());
	return true;
}

bool	isParam(char c)
{
	return (c == 'i' || c == 'k' || c == 'l' || c == 't' || c == 'o');
}

bool	setChanMode(Server &server, Client &client, std::vector<std::string> input){

	Channel		*channel = server.findChannel(input[1]);
	std::string	msg;
	bool		sgn;
	int			flag = 0;

	if (channel->isOperator(client.getNickname()) == false)
	{
		msg = ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->getChannelName());
		servSend(msg, client.getClientSocket());
		return (false);
	}
	else
	{
		std::string 	param = input[2];
		size_t 			indexParametre = 3;
		std::string 	mode;
		std::string 	modeArg;

		for (size_t i = 0; i < param.size(); i++)
		{
			if (param[i] == '+')
			{
				sgn = true;
				mode += '+';
			}
			else if (param[i] == '-')
			{
				sgn = false;
				mode += '-';
			}
			else if (param[i] == 'i' && !(flag & INVITE))
			{
				channel->setChanMode("INVITE", sgn);
				flag |= INVITE;
				mode += 'i';
			}
			else if (param[i] == 'k' && !(flag & KEY))
			{
				flag |= KEY;
				if (sgn)
				{
					if (input.size() >= 4 && indexParametre < input.size())
					{
						channel->setChanMode("KEY", sgn);
						mode += 'k';
						modeArg += " " + channel->getPassword();
						channel->setPassword(input[indexParametre++]);
					}
					else
						servSend(ERR_NEEDMOREPARAMS(client.getNickname(), param[i]), client.getClientSocket());
				}
				else
				{
					channel->setChanMode("KEY", sgn);
					mode += 'k';
					channel->setPassword("");
				}
			}
			else if (param[i] == 'l' && !(flag & LIMIT))
			{
				flag |= LIMIT;
				if (sgn)
				{
					if (input.size() >= 4 && indexParametre < input.size())
					{
						int max = atoi(input[indexParametre++].c_str());
						if (max > 0)
						{
							channel->setChanMode("LIMIT", sgn);
							channel->setUserMax(max);
							mode += 'l';
							modeArg += " " + itos(max);
						}
					}
					else
						servSend(ERR_NEEDMOREPARAMS(client.getNickname(), param[i]), client.getClientSocket());
				}
				else
				{
					channel->setChanMode("LIMIT", sgn);
					mode += 'l';
					channel->setUserMax(-1);
				}
			}
			else if (param[i] == 't' && !(flag & TOPIC))
			{
				channel->setChanMode("TOPIC", sgn);
				flag |= TOPIC;
				mode += 't';
			}
			else if (param[i] == 'o' && !(flag & OPERATOR))
			{
				if (!channel->isOperator(client.getNickname()))
				{
					servSend(ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->getChannelName()), client.getClientSocket());
					continue;
				}
				if (indexParametre >= input.size())
				{
					servSend(ERR_NEEDMOREPARAMS(client.getNickname(), param[i]), client.getClientSocket());
					continue;
				}
				if (channel->findMember(input[indexParametre]) == NULL)
					servSend(ERR_USERNOTINCHANNEL(input[indexParametre], channel->getChannelName()), client.getClientSocket());
				else
				{
					if (sgn)
						channel->addOperatorMember(channel->findMember(input[indexParametre++]));
					else
						channel->removeOperatorMember(input[indexParametre++]);
					mode += 'o';
					channel->setChanMode("OPERATOR", sgn);
					flag |= OPERATOR;
				}
			}
			else if (!isParam(param[i]))
				servSend(ERR_UNKNOWNMODE(client.getNickname(), param[i]), client.getClientSocket());
		}
		msg = RPL_CHANNELMODEIS(client.getNickname(), channel->getChannelName(), mode, modeArg);
		servSend(msg, client.getClientSocket());
		channel->sendMessageToMembers(&client, msg);
	}
	return true;
}

bool	modeCommand(Server &server, Client &client, std::vector<std::string> input){
	std::string msg;
	Client *clientFound = server.findClient(input[1]);
	// check not enough arg
	if (input.size() == 1){
		msg = ERR_NEEDMOREPARAMS(client.getNickname(), input[0]);
		servSend(msg, client.getClientSocket());
		return false;
	}
	else if (input.size() > 1){
		// check if target is a channel
		if (server.findChannel(input[1]) != NULL){
			if (input.size() == 2) // [MODE] [CHANNEL] > DISPLAYS CURRENT MODES
				return (sendChanMode(server, client, input));
			else if (input.size() > 2) // [MODE] [CHANNEL] [-ik] >> SETS MODE TO
				return (setChanMode(server, client, input));
		}
		else if (clientFound)
			servSend(RPL_UMODEIS(clientFound->getNickname(), clientFound->getUserName()), clientFound->getClientSocket());
		else{
			msg = ERR_NOSUCHCHANNEL(client.getNickname(), input[1]);
			servSend(msg, client.getClientSocket());
			return false;
		}
	}
	return true;
}
