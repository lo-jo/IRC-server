#include "../includes/ft_irc.hpp"

# define RPL_YOUREOPER(nickName, userName) (CLIENT_ID(nickName, userName, "381") + " :You are now an IRC operator\r\n")

bool	operCommand(Server &server, Client &client, std::vector<std::string> input)
{
	std::string		msg;
	bool			flag = true;

	if (input.size() != 3)
	{
		msg = ERR_NEEDMOREPARAMS(client.getNickname(), "OPER");
		flag = false;
	}
	else if (input[1] != client.getNickname())
	{
		msg = ERR_NOSUCHNICK(client.getNickname(), input[1]);
		flag = false;
	}
	else if (input[2] != server.getPassWordOperator())
	{
		msg = ERR_PASSWDMISMATCH(client.getNickname(), client.getUserName());
		flag = false;
	}
	else
	{
		client.setIsOperator(true);
		msg = RPL_YOUREOPER(client.getNickname(), client.getUserName());
	}
	servSend(msg, client.getClientSocket());
	return (flag);
}
