#include "../includes/ft_irc.hpp"

std::ostream& operator<<(std::ostream & o, Channel const & channel){
	o << "Name: " << channel.getChannelName() << std::endl
		<< "Nb members: " << channel.getChannelMembers().size() << std::endl
		<< "Topic: " << channel.getTopic() << std::endl
		<< "Owner: " << channel.getOwner() << std::endl
		<< "PassWord: " << channel.getPassword() << std::endl
		<< "User Max" << channel.getUserMax() << std::endl
		<< "Lock: " << (channel.getLocked() ? "Yes" : "No");
	return (o);
};

Channel::Channel(std::string name, Server *server): _server(server)
{
	_chanName = name;
	_userMax = -1;
	_isLocked = false;
	_chanMode["INVITE"] = 0;
	_chanMode["TOPIC"] = 0;
	_chanMode["KEY"] = 0;
	_chanMode["OPERATOR"] = 0;
	_chanMode["LIMIT"] = 0;
};

Channel::~Channel() {

};

Server*					Channel::getServer() const {
	return (_server);
};

std::string 			Channel::getChannelName() const {
	return (_chanName);
};

std::vector<Client *> 	Channel::getChannelMembers() const {
	return (_members);
};

std::string				Channel::getTopic() const {
	return (_topic);
};

Client*				Channel::getOwner() const {
	return (_owner);
};

std::string				Channel::getPassword() const {
	return (_password);
};

int						Channel::getUserMax() const {
	return (_userMax);
};

bool					Channel::getLocked() const {
	return (_isLocked);
};

std::vector<Client *>	Channel::getOperList() const {
	return (_operList);
};

void					Channel::setServer(Server *server) {
	_server = server;
};

void	Channel::setChannelName(std::string name) {
	_chanName = name;
};

void	Channel::setChannelMembers(std::vector<Client *> members) {
	_members = members;
};

void	Channel::setTopic(std::string topic) {
	_topic = topic;
};

void	Channel::setOwner(Client *owner) {
	_owner = owner;
};

void	Channel::setPassword(std::string password) {
	_password = password;
};

void	Channel::setUserMax(int userMax) {
	_userMax = userMax;
};

void	Channel::setLocked(bool isLocked) {
	_isLocked = isLocked;
};

void	Channel::setChanMode(std::string mode, bool sgn)
{
	_chanMode[mode] = sgn;
};

void	Channel::addMember(Client* member){
	_members.push_back(member);
};

void	Channel::addOwner(Client* owner){
	_owner = owner;
	addMember(owner);
};

void	Channel::addOperatorMember(Client *client){
	_operList.push_back(client);
};

void	Channel::removeOperatorMember(std::string nick){
	for (std::vector<Client *>::iterator it = _operList.begin(); it != _operList.end(); it++)
	{
		if (nick == (*it)->getNickname())
		{
			_operList.erase(it);
			break;
		}
	}
};

bool	Channel::isOperator(std::string nick) {
	for (std::vector<Client *>::iterator it = _operList.begin(); it != _operList.end(); it++)
	{
		if (nick == (*it)->getNickname())
			return (true);
	}
	return (false);
};

Client*	Channel::findMember(std::string nickname){

	for (std::vector<Client *>::iterator it = _members.begin(); it != _members.end(); it++)
	{
		if (nickname == (*it)->getNickname()){
			return (*it);
		}
	}
	return (NULL);
};

Client*	Channel::findMember(Client *client){

	for (std::vector<Client *>::iterator it = _members.begin(); it != _members.end(); it++)
	{
		if (client == (*it))
			return (*it);
	}
	return (NULL);
};

void	Channel::removeMember(Client* member){
	for (std::vector<Client *>::iterator it = _members.begin(); it != _members.end(); it++)
	{
		if (member == (*it))
		{
			_members.erase(it);
			break ;
		}
	}
};

bool	Channel::getChanMode(const std::string mode){
	std::map<std::string, bool>::const_iterator it = _chanMode.find(mode);

	return (it->second);
}

void	Channel::sendMessageToMembers(Client *sender, std::string message)
{
	for (std::vector<Client *>::iterator it = _members.begin(); it != _members.end(); it++)
	{
		if (sender != (*it))
			servSend(message, (*it)->getClientSocket());
	}
};

void	Channel::kickOutClient(std::string msg, std::vector<std::string> input)
{
	std::vector<Client *>::iterator	it = _members.begin();
	for ( ; it != _members.end(); it++)
	{
		if (input[2] == (*it)->getNickname())
		{
			servSend(msg, (*it)->getClientSocket());
			_members.erase(it);
			break ;
		}
	}
}

void	Channel::addInvitee(Client *client){
	_invitedUsers.push_back(client);
};

bool	Channel::isInvited(std::string nick) {
	for (std::vector<Client *>::iterator it = _invitedUsers.begin(); it != _invitedUsers.end(); it++)
	{
		if (nick == (*it)->getNickname())
			return (true);
	}
	return (false);
};
