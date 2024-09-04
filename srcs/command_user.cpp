#include "../includes/ft_irc.hpp"

bool	userCommand(Server &server, Client &client, std::vector<std::string> input)
{
	std::string	msg;
	int	byte_sent;

	(void)server;
	if (client.getAuthStatus() == true)
	{
		msg = ERR_ALREADYREGISTERED(client.getNickname());
		byte_sent = send(client.getClientSocket(), msg.c_str(), msg.length(), MSG_NOSIGNAL);
		if (byte_sent != (int)msg.length())
			std::cerr << "Error sending message" << std::endl;
		return (false);
	}
	else if (client.getRegistrationStatus() != (CAP_RECEIVED | PASS_RECEIVED | NICK_RECEIVED))
	{
		msg = ERR_NOTREGISTERED(client.getNickname());
		client.setRegistrationStatus(START);
		byte_sent = send(client.getClientSocket(), msg.c_str(), msg.length(), MSG_NOSIGNAL);
		if (byte_sent != (int)msg.length())
			std::cerr << "Error sending message" << std::endl;;
		return (false);
	}
	if (input.size() < 5)
	{
		msg = ERR_NEEDMOREPARAMS(client.getNickname(), input[0]);
		byte_sent = send(client.getClientSocket(), msg.c_str(), msg.length(), MSG_NOSIGNAL);
		if (byte_sent != (int)msg.length())
			std::cerr << "Error sending message" << std::endl;
		return (false);
	}
	if (input.size() == 6)
		client.setLastName(input[5]);
	client.setFirstName(input[4]);
	client.setUserName(input[1]);
	client.setHostname(input[3]);
	client.setRegistrationStatus(client.getRegistrationStatus() | USER_RECEIVED);
	client.setAuthStatus(true);
	msg = RPL_WELCOME(client.getNickname());
	byte_sent = send(client.getClientSocket(), msg.c_str(), msg.length(), MSG_NOSIGNAL);
	if (byte_sent != (int)msg.length())
		std::cerr << "Error sending message" << std::endl;
	return (false);
}
