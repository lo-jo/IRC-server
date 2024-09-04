#pragma once

#include "ft_irc.hpp"

# define START 0
# define CAP_RECEIVED 1 /*1*/
# define PASS_RECEIVED 2 /*2*/
# define NICK_RECEIVED 4 /*4*/
# define USER_RECEIVED 8 /*8*/

class Client{
	private :
	/*************************** attributes *******************************/
	int				_clientSocket;
	std::string		_nick;
	std::string		_userName;
	std::string		_firstName;
	std::string		_lastName;
	std::string		_hostname;
	std::string		_inputReceived;

	//std::vector<Channel *> _channelMembership;

	int			_registeredStatus;
	bool		_isAuthentified;
	bool		_isOperator;

	/**************** constructor / destructor ***************************/
	Client();
	Client(Client const &src);
	Client& operator=(Client const &obj);

	


	public :
		
		Client(int socket);
		~Client();

	/*************************** setters ********************************/
	void			setNickname(std::string nickname);
	void			setHostname(std::string hostname);
	void			setFirstName(std::string firstName);
	void			setLastName(std::string lastname);
	void			setUserName(std::string userName);
	void			setAuthStatus(bool status);
	void			setRegistrationStatus(int state);
	void			setIsOperator(bool status);
	void			concatenateInputRecieved(std::string input);
	void			updateInput(std::string input);

	/*************************** getters ********************************/
	int				getClientSocket() const;
	int				getRegistrationStatus() const;
	bool			getAuthStatus() const;
	std::string		getNickname() const;
	std::string		getHostname() const;
	std::string		getFirstName() const;
	std::string		getLastName() const;
	std::string		getUserName() const;
	bool			getIsOperator() const;
	std::string		getInputReceived() const;

};