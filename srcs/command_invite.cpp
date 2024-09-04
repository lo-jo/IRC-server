#include "../includes/ft_irc.hpp"
// invite <channel> <nickname>
bool	inviteCommand(Server &server, Client &client, std::vector<std::string> input){
	std::string msg;

	if (input.size() < 3){
		msg = ERR_NEEDMOREPARAMS(client.getNickname(), input[0]);
		servSend(msg, client.getClientSocket());
		return false;
	}
	else{
		if (server.findChannel(input[2]) && server.findChannel(input[2])->getChannelMembers().size() > 0 && server.findClient(input[1])){
			if (server.findChannel(input[2])->findMember(&client)){
				if (server.findChannel(input[2])->getChanMode("INVITE") == 1){
					if (!server.findChannel(input[2])->isOperator(client.getNickname())){
						msg = ERR_CHANOPRIVSNEEDED(client.getNickname(), input[2]);
						servSend(msg, client.getClientSocket());
						return false;
					}
				}
				if (server.findChannel(input[2])->findMember(input[1]) != NULL){ // if the invited member is already on the channel
					msg = ERR_USERONCHANNEL(client.getNickname(), input[1], server.findChannel(input[2])->getChannelName());
					servSend(msg, client.getClientSocket());
					return false;
				}
				msg = RPL_INVITING(client.getNickname(), input[1], server.findChannel(input[2])->getChannelName());
				servSend(msg, server.findClient(input[1])->getClientSocket());
				// add target to invite list
				server.findChannel(input[2])->addInvitee(server.findClient(input[1]));
				return true;
			}
			else {
				msg = ERR_NOTONCHANNEL(client.getNickname(), server.findChannel(input[2])->getChannelName());
				servSend(msg, client.getClientSocket());
				return false;
			}
		}
		msg = ERR_NOSUCHCHANNEL(client.getNickname(), input[2]);
		servSend(msg, client.getClientSocket());
		return false;
	}
	return (true);
}

