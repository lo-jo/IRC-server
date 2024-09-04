#include "../includes/ft_irc.hpp"
#include "../includes/Client.hpp"
#include "../includes/Commandes.hpp"
#include <sstream>

std::ostream& operator<<(std::ostream & o, pollfd const &pollfdList)
{
	o << "fd: " << pollfdList.fd << " events: " << pollfdList.events << " revents: " << pollfdList.revents;
	return (o);
};

// EXCEPTION CONSTRUCTOR
const char*	Server::CatchServerException::what() throw() { return (_message.c_str()); }

/**************************CANONICAL***************************/
Server::Server() {}

Server& Server::operator=(Server const &obj)
{
	if (this != &obj)
	{
		this->_pfds = obj._pfds;
		this->_port = obj._port;
		this->_clientList = obj._clientList;
		this->_channelList = obj._channelList;
		this->_fd = obj._fd;
		this->_servAddr = obj._servAddr;
		this->_pw = obj._pw;
		return (*this);
	}
	return (*this);
}

Server::Server(Server const &src)
{
	*this = src;
}

Server::~Server()
{
	if (_clientList.size() != 0)
	{
		for (u_int i = 0; i != _clientList.size(); i++)
			delete (_clientList[i]);
	}
	if (_channelList.size() != 0)
	{
		for (u_int i = 0; i != _channelList.size(); i++)
			delete (_channelList[i]);
	}
	if (_pfds.size() > 1)
		freeClient(this->_pfds);
	close (_fd);
}

/*********************AD-HOC CONSTRUCTOR************************/
Server::Server(int port, std::string password): _port(port),  _pw(password), _pwOperator(PASSWORDOPERATOR)
{
	std::cout << "Initialising Server on port nb." << _port << std::endl;
	initCommandList();
	initServer(port);
	ft_listen();
}

/*********************METHODS************************/
void	Server::initServer(int port)
{
	// creating server socket
	// (AF_INET : IPv4 protocol family, SOCK_STREAM : type of socket wanted,  IPPROTO_TCP : TCP transport protocol )
	_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_fd < 0)
		throw CatchServerException("ERROR opening socket");
	int optval = 1;
	setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	// creating server address
	memset(&_servAddr, 0, sizeof(_servAddr)); // set the structure variables to NULL, otherwise it may get unexpected junk values in your structure
	_servAddr.sin_family = AF_INET;  /* famille d'adresses : AF_INET (always AF_INET)*/
	_servAddr.sin_port =  htons(port);/* port dans l'ordre d'octets réseau */
	_servAddr.sin_addr.s_addr = INADDR_ANY;/* adresse Internet  INADDR_ANY (0.0.0.0) signifie un attachement à n'importe quelle adresse */
	// binding host address
	if (bind(_fd, (struct sockaddr*)(&_servAddr), sizeof(_servAddr)) < 0)
	{
		close(_fd);
		throw CatchServerException(RED "ERROR on binding : " RESET + std::string(strerror(errno)));
	}
}

void	Server::ft_listen(void)
{
	int	perror = errno;
	// start listening to clients
	if (listen(_fd, 5) < 0) // backlog is limited to a range of 1 to 5, the queue can only accommodate up to 5 clients
		throw CatchServerException("ERROR on listening : " + std::string(strerror(perror)));
	std::cout << "IRC Server started." << YEL " Now listening..." RESET << std::endl;
}

template <typename T>
void	Server::acceptNewClient(T& pfds)
{
	(void) pfds;
	int	ret = poll(&this->_pfds[0], this->_pfds.size(), -1); // Temps d'attente indefini
	int	perror = errno;

	if (ret < 0 && EINTR)
	{
		close(_fd);
		throw CatchServerException("Error: " + std::string(strerror(perror)));
	}
	else if (ret == 0)
	{
		close(_fd);
		throw CatchServerException("Error: Time expire " + std::string(strerror(perror)));
	}
	else if (ret > 0)
	{
		pollfd	tmp;
		socklen_t	sockLen = sizeof(struct sockaddr_in);
		if (this->_pfds[0].revents && POLLIN > 0)
		{
			if (_pfds.size() < CLIENT_MAX)
			{
				int	newClientSocket = accept(this->_pfds[0].fd, (struct sockaddr *)(&_servAddr), &sockLen);
				perror = errno;
				if (newClientSocket < 0)
					std::cerr << "Client socket error: " + std::string(strerror(perror)) << std::endl;
				Client *newUser = new Client(newClientSocket);
				// add client to client list
				_clientList.push_back(newUser);
				// add client to pollfd vecto		void	setStop(int stop);
				tmp.fd = newClientSocket;
				tmp.events = POLLIN;
				tmp.revents = POLLIN;
				this->_pfds.push_back(tmp);
			}
		}
		readClientData(pfds);
	}
}

std::vector<std::string>	Server::parseToken(std::string token)
{
	std::vector<std::string> 	command;
	std::stringstream 			ss(token);
	std::string					cmd;

	while(ss >> cmd)
		command.push_back(cmd);
	return (command);
}

void	Server::removeClient(int socket)
{
	for (std::vector<Client *>::iterator it = _clientList.begin(); it != _clientList.end(); it++)
    {
		if (socket == (*it)->getClientSocket())
		{
			if (socket > 2)
				close(socket);
			delete (*it);
			_clientList.erase(it);
			break;
		}
    }
}

Client*	Server::findClient(int socket)
{

	for (std::vector<Client *>::iterator it = _clientList.begin(); it != _clientList.end(); it++)
	{
		if (socket == (*it)->getClientSocket())
			return (*it);
	}
	return (NULL);
};

Client*	Server::findClient(std::string nickname)
{

	for (std::vector<Client *>::iterator it = _clientList.begin(); it != _clientList.end(); it++)
    {
		if (nickname == (*it)->getNickname())
			return (*it);
    }
	return (NULL);
};

bool	Server::handleCommand(Client &client ,std::vector<std::string> command)
{
	if (_commandList.find(command[0]) != _commandList.end())
		return (_commandList[command[0]](*this, client, command));
	else
	{
		servSend(ERR_UNKNOWNCOMMAND(client.getNickname(), command[0]), client.getClientSocket());
		return (false);
	}
}

template <typename T>
void	Server::readClientData(T& pfds)
{
	//int	perror = errno;
	typename	T::iterator	it = pfds.begin();

	for (; it != (pfds.end() - 1); it++)
	{
		if ((it + 1)->revents & POLLIN)
		{
			char buffer[1024];
			memset(buffer, 0, sizeof(buffer));
			Client	*client = findClient((it + 1)->fd);
			int bytes_received = 0;
			if (client != NULL)
				bytes_received = recv((it + 1)->fd, buffer, sizeof(buffer), 0);;
			if (bytes_received > 0 && ((it + 1)->fd) != -1)
			{
				client->concatenateInputRecieved(buffer);
				if (findDelimiter(client->getInputReceived(), "\r") == false)
					continue;
				else
				{
					while(findDelimiter(client->getInputReceived(), "\r"))
					{
						std::cout << YEL "log:" RESET << buffer << std::endl;
						std::string	token = getCommand(client->getInputReceived(), "\r");
						int index = client->getInputReceived().find("\r");
						client->updateInput(client->getInputReceived().substr(index + 1, client->getInputReceived().size() - index));
						std::vector<std::string> command = parseToken(token);
						if (command.empty())
							break;
						if (IsAuth(command[0]) || client->getAuthStatus())
						{
							if (!handleCommand(*client ,command))
								break;
						}
						else
						{
							servSend(ERR_NOTREGISTERED(client->getNickname()), client->getClientSocket());
							break;
						}
					}
				}
			}
			else if (bytes_received == 0)
			{
				if(findClient((it+1)->fd) != NULL && (it+1)->revents != POLLHUP)
					removeClient((it + 1)->fd);
				pfds.erase(it + 1);
				it--;
				// std::cout << "Client gone away : " << GREEN BOLD << std::strerror(perror) << RESET << std::endl;
			}
			else if (bytes_received < 0)
			{
				close((it + 1)->fd);
				(it + 1)->fd = -1;
				pfds.erase(it + 1);
				//std::cerr << "Client error: " << std::strerror(perror) << std::endl;
			}
		}
	}
}

int	Server::receiveClientData(void)
{
	pollfd	fds;

	fds.fd = _fd;
	fds.events = POLLIN;
	fds.revents = POLLIN;
	_pfds.push_back(fds);
	while (1)
	{
		acceptNewClient(_pfds);
	}
	return (0);
}

void	Server::freeClient(std::vector<pollfd> pfds)
{
	for (size_t i = 0; i < pfds.size(); i++)
	{
		if (pfds[i].fd > 2)
		{
			close (pfds[i].fd);
			pfds[i].fd = -1;
		}
	}
}

void	Server::initCommandList()
{
	_commandList["CAP"] = &capLsCommand;
	_commandList["NICK"] = &nickCommand;
	_commandList["USER"] = &userCommand;
	_commandList["WHOIS"] = &whoisCommand;
	_commandList["PASS"] = &passCommand;
	_commandList["PING"] = &pingCommand;
	_commandList["QUIT"] = &quitCommand;
	_commandList["JOIN"] = &joinCommand;
	_commandList["PRIVMSG"] = &privmsgCommand;
	_commandList["KICK"] = &kickCommand;
	_commandList["TOPIC"] = &topicCommand;
	_commandList["MODE"] = &modeCommand;
	_commandList["INVITE"] = &inviteCommand;
	_commandList["PART"] = &partCommand;
	_commandList["OPER"] = &operCommand;
}

std::string Server::getPass(){
	return _pw;
}

std::string Server::getPassWordOperator() const {
	return (_pwOperator);
}

void	Server::setPassWordOperator(std::string passWordOperator)
{
	_pwOperator = passWordOperator;
};

std::vector<Client *>	Server::getClientList() const
{
	return (_clientList);
}

std::vector<Channel *>	Server::getChannelList() const {
	return (_channelList);
};

void	Server::addChannel(Channel *channel) {
	_channelList.push_back(channel);
};

Channel*	Server::findChannel(std::string name) {

	for (std::vector<Channel *>::iterator it = _channelList.begin(); it != _channelList.end(); it++)
	{

		if (name == (*it)->getChannelName()){
			return (*it);
		}
	}
	return (NULL);
};

void	Server::removeChannel(std::string name) {
	for (std::vector<Channel *>::iterator it = _channelList.begin(); it != _channelList.end(); it++)
	{
		if (name == (*it)->getChannelName()){
			_channelList.erase(it);
			break;
		}
	}
};

void Server::hangUpClient(int socket){
	std::vector<pollfd>::iterator it = _pfds.begin();
	for (; it != _pfds.end(); it++){
		if ((it)->fd == socket){
			(it)->revents = POLLHUP;
		}
	}
}
