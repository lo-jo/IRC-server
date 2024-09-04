#include "../includes/ft_irc.hpp"

Server	*srv;

static void	sig_handler(int sig)
{
	(void) sig;
	srv->~Server();
	std::cout << BOLD "......" << GREEN "Quit IRC server" << RESET BOLD "......" RESET << std::endl;
	exit (0);
}

int	launch_server(char **argv)
{
	Server	Server(std::atoi(argv[1]), argv[2]);
	srv = &Server;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, sig_handler);
	if (srv->receiveClientData())
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	try
	{
		if (argc != 3)
		{
			std::cout << RED "Invalid program usage. Try ./ircserv <port> <password>" RESET << std::endl;
			return 1;
		}
		launch_server(argv);
	}
	catch (Server::CatchServerException& e)
	{
		std::cerr << e.what() << "\n";
	}
	return (0);
}
