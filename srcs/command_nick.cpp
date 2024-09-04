#include "../includes/ft_irc.hpp"

static bool	validNickName(std::string newNickName) //@TODO: check rules for nickname is valid
{
	if (newNickName.length() > 9)
		return (false);
	if (newNickName[0] == '#')
		return false;
	for (size_t i = 0; i != newNickName.length(); i++)
	{
		if (i == 0 && !isalpha(newNickName[i]))
			return (false);
		else if (!isalnum(newNickName[i]))
			return (false);
	}
	return (true);
}

static bool	nickNameInUse(Server &server, std::string newNickName)
{
	std::vector<Client *>	clientList = server.getClientList();

	for (size_t i = 0; i != clientList.size(); i++)
	{
		if (clientList[i]->getNickname() == newNickName)
			return (true);
	}
	return (false);
}

bool	nickCommand(Server &server, Client &client, std::vector<std::string> input)
{
	std::string				msg;
	std::vector<Client *>	clientList = server.getClientList();
	bool					flag = true;

	if (input.size() != 2)
	{
		msg = ERR_NONICKNAMEGIVEN(client.getNickname());
		flag = false;
	}
	else if (nickNameInUse(server, input[1]))
	{
		msg = ERR_NICKNAMEINUSE(input[1]);
		flag = false;
	}
	else if (!validNickName(input[1]))
	{
		msg = ERR_ERRONEUSNICKNAME(client.getNickname());
		flag = false;
	}
	else if (client.getAuthStatus() == true)
	{
		msg = NICK_MESSAGE(client.getNickname(), input[1]);
		client.setNickname(input[1]);
	}
	else if (client.getRegistrationStatus() == (CAP_RECEIVED | PASS_RECEIVED))
	{
		client.setRegistrationStatus(client.getRegistrationStatus() | NICK_RECEIVED);
		msg = NICK_MESSAGE(client.getNickname(), input[1]);
		client.setNickname(input[1]);
	}
	else
	{
		msg = ERR_NOTREGISTERED(client.getNickname());
		client.setRegistrationStatus(START);
		flag = false;
	}
	servSend(msg, client.getClientSocket());
	return (flag);
}
