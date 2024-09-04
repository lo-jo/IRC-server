#pragma once

#include "ft_irc.hpp"

class Client;
class Channel;

class Server
{
	public:
		// ALIASES
		typedef	std::vector<pollfd>	pfds;

		// CONSTRUCTORS/DESTUCTORS
		Server();
		Server(int port, std::string password);
		~Server();
		Server(Server const &src);
		Server& operator=(Server const &obj);

		// METHODS
		void	initServer(int port);

		std::vector<std::string>	parseToken(std::string token);
		std::vector<Client *>		getClientList() const;
		Client*						findClient(int socket);
		Client*						findClient(std::string nickname);

		std::vector<Channel *>		getChannelList() const;
		void						addChannel(Channel *channel);
		Channel*					findChannel(std::string name);
		void						removeChannel(std::string name);
		void						removeChannel(Channel *channel);
		void						hangUpClient(int socket);
		void						removeClient(int socket);

    	int	receiveClientData(void);

		template <typename T>
		void	readClientData(T& pfds);

		void	freeClient(std::vector<pollfd> pfds);

		void	ft_listen();

		template <typename T>
		void	acceptNewClient(T& pfds);

		//STRUCTURES
		struct sockaddr_in	_servAddr;

		// EXCEPTION
		class CatchServerException
		{
			public:
				CatchServerException(const std::string message) : _message(message) {};
			const char	*what() throw();
			private:
				std::string	_message;
		};
	/******************************   getters   *************************************/
		std::string getPass();
		std::string getPassWordOperator() const;

		void	setPassWordOperator(std::string passWordOperator);

	private:
	/****************************   server management   *****************************/
		int				_port;
    	int				_fd;
		std::string 	_pw;
		std::string		_pwOperator;
		std::string 	_servName;

		std::map<std::string, bool (*)(Server&, Client&, std::vector<std::string>)>	_commandList;
		void	initCommandList();
		bool	handleCommand(Client &client ,std::vector<std::string> command);

	/****************************   client management   ****************************/
		std::vector<Client *>		_clientList;
		pfds			_pfds;
		std::vector<Channel *>		_channelList;




	/**********************   constructor/destructor   *****************************/
};

extern Server	*srv;

std::ostream& operator<<(std::ostream & o, pollfd const &pollfdList);