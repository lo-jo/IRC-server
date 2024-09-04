#pragma once

#include "ft_irc.hpp"

class Client;
class Server;

class Channel{
	private :
		Server*							_server;
		std::string 					_chanName;
		std::vector<Client *> 			_members;
		std::string						_topic;
		Client*							_owner;
		std::string						_password;
		int								_userMax;
		bool							_isLocked;
		std::map<std::string, bool>		_chanMode;
		std::vector<Client *>			_operList;
		std::vector<Client *>			_invitedUsers;


	public :
		Channel(std::string name, Server *server);
		~Channel();

		/*******************Getter***********************/
		Server*						getServer() const;
		std::string 				getChannelName() const;
		std::vector<Client *> 		getChannelMembers() const;
		std::string					getTopic() const;
		Client*						getOwner() const;
		std::string					getPassword() const;
		int							getUserMax() const;
		bool						getLocked() const;
		bool						getChanMode(std::string mode);
		std::vector<Client *>		getOperList() const;

		/*******************Setter***********************/
		void					setServer(Server *server);
		void					setChannelName(std::string name);
		void					setChannelMembers(std::vector<Client *> members);
		void					setTopic(std::string topic);
		void					setOwner(Client *owner);
		void					setPassword(std::string password);
		void					setUserMax(int userMax);
		void					setLocked(bool isLocked);
		void					setChanMode(std::string mode, bool sgn);
		
		/********************Methode***********************/
		void					addOperatorMember(Client *client);
		void					removeOperatorMember(std::string nick);
		bool					isOperator(std::string nick);
		bool					isInvited(std::string nick);
		void					addMember(Client* member);
		void					addOwner(Client* owner);
		void					removeMember(Client* member);
		void					kickOutClient(std::string msg, std::vector<std::string> input);
		void					addInvitee(Client *client);
		Client*					findMember(std::string nickname);
		Client*					findMember(Client* client);
		void					sendMessageToMembers(Client *sender, std::string message);

};

std::ostream& operator<<(std::ostream & o, Channel const &channel);
