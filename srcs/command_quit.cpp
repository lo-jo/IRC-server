#include "../includes/ft_irc.hpp"
#include "../includes/Client.hpp"
#include "../includes/Defines.hpp"

bool	quitCommand(Server &server, Client &client, std::vector<std::string> input)
{
	Client	*findClient = server.findClient(client.getNickname());
	std::string	log;
	std::string	msg = ": leaving";
	std::string	chanName;
	if (input.size() > 1)
		msg = joinAllMsg(input, 1);

	if (server.getChannelList().size() > 0){
		for (u_int i = 0; i < server.getChannelList().size(); i++)
		{
			if (server.findClient(client.getNickname()) == server.getChannelList()[i]->findMember(&client))
			chanName = server.getChannelList()[i]->getChannelName();
		}
		Channel	*channel = server.findChannel(chanName);
		log = QUIT_MSG(client.getNickname(), msg);
		if (server.findChannel(chanName) != NULL){
			server.findChannel(chanName)->sendMessageToMembers(&client, log);
			channel->removeMember(findClient);
		}
	}
	log = QUIT_MSG(client.getNickname(), msg);
	servSend(log, client.getClientSocket());
	server.hangUpClient(client.getClientSocket());
	
	return (true);
};

