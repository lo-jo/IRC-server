#include "../includes/ft_irc.hpp"

void	servSend(std::string msg, int socket){

	int byte_sent;
	byte_sent = send(socket, msg.c_str(), msg.length(), MSG_NOSIGNAL);
	if (byte_sent == -1)
		std::cerr << "Error on send: " << std::string(strerror(errno)) << std::endl;
}

std::string		joinAllMsg(std::vector<std::string> input, int start)
{
	std::string			msg;
	std::stringstream	ss;


	for (size_t i = start; i < input.size(); i++)
	{
		ss << (i == 2 ? input[i].substr(1, input[i].size() - 1) : input[i]);
		if (i < input.size() - 1)
			ss << " ";
	}
	msg = ss.str();
	return (msg);
}

std::string itos(int nb){
	std::stringstream ss;
	ss << nb;
	std::string myString = ss.str();
	return (myString);
}

void	printvect(std::vector<std::string> input){
	for(unsigned int i = 0; i != input.size(); i++)
		std::cout << "[" << input[i] << "]" << std::endl;
}

bool	IsAuth(std::string command)
{
	if (command == "PASS" || command == "NICK" || command == "USER" || command == "CAP")
		return (true);
	return (false);
}

bool	findDelimiter(std::string input, std::string delimiter)
{
	size_t pos = input.find(delimiter);
	if (pos != std::string::npos)
		return (true);
	return (false);
}

std::string		getCommand(std::string input, std::string delimiter)
{
	size_t pos = input.find(delimiter);
	if (pos != std::string::npos)
		return (input.substr(0, pos));
	return ("");
}
