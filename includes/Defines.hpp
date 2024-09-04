
#pragma once

# define SERVER_NAME "Best-IRC-In-Town"
# define PASSWORDOPERATOR "Amyourmaster123"
# define CLIENT_ID(nickName, userName, command) (std::string(":") + nickName + "!~" + userName + "@" + SERVER_NAME + " " + command + " ")
# define NICK_MESSAGE(userName, newUserName) (std::string(":") + userName + " NICK " + newUserName + "\r\n")
# define RPL_WELCOME(nickname) (std::string(":") + SERVER_NAME + " 001 " + nickname + " :Welcome to the " + SERVER_NAME + ", " + nickname + "\r\n")
# define PONG(token) (std::string(":") + SERVER_NAME + " PONG " + SERVER_NAME + " :" + token + "\r\n")
# define USER_MESSAGE(command, nickName, firstName, lastName) (command + " " + nickName + " 0 * " + firstName + " " + lastName + "\r\n")
# define JOIN_MESSAGE(nickName, userName, channelName)(CLIENT_ID(nickName, userName, "JOIN") + ":" + channelName + "\r\n")
# define RPL_TOPIC(nickName, channelName, topic) ((CLIENT_ID(nickName, nickName, "TOPIC")) + channelName + " :" + topic + "\r\n")
# define RPL_NOTOPIC(nickName, channelName) (std::string(":") + nickName + channelName + " : No topic is set\r\n")
# define RPL_CHANNELMODEIS(client, channel, modeString, modeArg) (std::string(":") + SERVER_NAME + " 324 " + client + " " + channel + " " + modeString + modeArg + "\r\n")
# define RPL_UMODEIS(nickName, userName) (CLIENT_ID(nickName, userName, "MODE") + nickName + " +i\r\n")
# define RPL_INVITING(client, nickname, channel) (std::string(":") +  " 341 " + client + " " + nickname + " " + channel + "\r\n")

/************ ERROR *******/
# define ERR_PASSWDMISMATCH(nickName, userName) (std::string(":") + nickName + userName + " Incorrect Password, try again\r\n")
# define ERR_ALREADYREGISTERED(nickName) (std::string(":") + nickName + " You may not reregister\r\n")
# define ERR_NEEDMOREPARAMS(nickName, command) (std::string(":") + nickName + "@" + SERVER_NAME + " " + command + " : Not enough parameters\r\n")
# define ERR_NONICKNAMEGIVEN(nickName) (CLIENT_ID(nickName, "*", "431") + ": No nickname given\r\n")
# define ERR_ERRONEUSNICKNAME(nickName) (CLIENT_ID(nickName, "*", "432") + ": Erroneus nickname\r\n")
# define ERR_NOSUCHCHANNEL(nickName, channelName) (std::string(":") + nickName + "@" + SERVER_NAME + " " + channelName + " :No such channel/nick\r\n")
# define ERR_CHANOPRIVSNEEDED(nickName, channel) (std::string(":") + SERVER_NAME + " 482 " + " " + nickName + " " + channel + " :You're not channel operator\r\n")
# define ERR_NOTREGISTERED(nickName) (CLIENT_ID(nickName, "*", "451") + " : You have not registered\r\n")
# define QUIT_MSG(nickName, message) (CLIENT_ID(nickName, "*", "QUIT") + message + "\r\n")
# define ERR_NICKNAMEINUSE(newNickName) (newNickName + " is already in use\r\n")
# define ERR_UNKNOWNMODE(nickName, mode) (CLIENT_ID(nickName, "*", "472") + " " + mode + " :is unknown mode char to me\r\n")
# define ERR_UNKNOWNCOMMAND(nickName, command) (CLIENT_ID(nickName, "*", "421") + " " + command + " :Unknown command\r\n")
/******** PRIVMSG ********/
# define PRIVMSG_MESSAGE(nick, chan, msg) (std::string(":") + nick + " PRIVMSG " + chan + " :" + msg + "\r\n")

/******** KICK ********/
# define KICK(nickName, channel, target, reason) (CLIENT_ID(nickName, "*", "KICK") + channel + " " + target + " " + reason + "\r\n")


# define PART_MESSAGE(nickName, userName, channel, reason) (CLIENT_ID(nickName, userName, "PART") + channel + " :" + reason + "\r\n")

/******** KICK ERROR ********/
# define ERR_CANNOTSENDTOCHAN(nickName, channel) (nickName + " " + channel + " Cannot send to channel" + "\r\n")
# define ERR_USERNOTINCHANNEL(nickName, channel) (CLIENT_ID(nickName, "*", "441") + nickName + channel + " :They aren't on that channel" + "\r\n")
# define ERR_NOTONCHANNEL(client, channel) (CLIENT_ID(client, "*", "442") + channel + " You're not on that channel" + "\r\n")
# define RPL_ENDOFWHOIS(nickName) (CLIENT_ID(nickName, "*", "318") + ": End of /WHOIS list\r\n")
# define ERR_NOSUCHNICK(nickName, userName) (CLIENT_ID(nickName, "*", "401") + ": " + userName + " No such nick/channel\r\n")

# define ERR_USERONCHANNEL(client, nickName, channel)(std::string(":") + "443" + client + " " + nickName + " " + channel + " : User is already on channel" + "\r\n")
# define ERR_INVITEONLYCHAN(client, channel)(std::string(":") + " 473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")
# define ERR_CHANNELISFULL(client, channel)(std::string(":") + " 471 " + client + " " + channel + " :Cannot join channel (+l)\r\n")
# define ERR_BADCHANNELKEY(client, channel)(std::string(":") + " 475 " + client + " " + channel + " :Bad channel key (+k)\r\n")
