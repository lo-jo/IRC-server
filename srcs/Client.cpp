#include "../includes/Client.hpp"

/**************************CANONICAL***************************/
Client::Client() {}

Client& Client::operator=(Client const &obj)
{
	if (this != &obj)
	{
		return (*this);
	}
	return (*this);
}

Client::Client(Client const &src)
{

	*this = src;
}

Client::~Client() {}

/*********************AD-HOC CONSTRUCTOR************************/
Client::Client(int socket): _clientSocket(socket), _registeredStatus(START), _isAuthentified(false), _isOperator(false) {}

/******************      GETTERS         **********************/

void			Client::setNickname(std::string nickname) {
	_nick = nickname;
};

void			Client::setHostname(std::string hostname) {
	_hostname = hostname;
};

void			Client::setFirstName(std::string firstName) {
	_firstName = firstName;
};

void			Client::setLastName(std::string lastname) {
	_lastName = lastname;
};

void			Client::setUserName(std::string userName) {
	_userName = userName;
};

void			Client::setRegistrationStatus(int state) {
	_registeredStatus = state;
};

void			Client::setAuthStatus(bool status) {
	_isAuthentified = status;
};

void			Client::setIsOperator(bool status) {
	_isOperator = status;
};

void			Client::updateInput(std::string input)
{
	_inputReceived = input;
};

void			Client::concatenateInputRecieved(std::string input)
{
	_inputReceived = _inputReceived + input;
};

int				Client::getClientSocket() const {
	return (_clientSocket);
};

std::string		Client::getNickname() const {
	return (_nick);
};

std::string		Client::getHostname() const {
	return (_hostname);
};

std::string		Client::getFirstName() const {
	return (_firstName);
};

std::string		Client::getLastName() const {
	return (_lastName);
};

std::string		Client::getUserName() const {
	return (_userName);
};

int			Client::getRegistrationStatus() const {
	return (_registeredStatus);
}

bool			Client::getAuthStatus() const{
	return (_isAuthentified);
};

bool			Client::getIsOperator() const{
	return (_isOperator);
};

std::string		Client::getInputReceived() const{
	return (_inputReceived);
};
