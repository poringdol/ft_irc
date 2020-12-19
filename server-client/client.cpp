#include "Client.hpp"

// --------------------------------Constructors--------------------------------

Client::Client() : port(SERVER_PORT), ip(SERVER_IP) {}
Client::Client(int port, std::string const & ip) : port(port), ip(ip) {}


// ---------------------------Creating connection------------------------------

void	Client::create_socket()
{
	if ((this->client = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		Client::error("Esteblishing socket error");

	bzero(&this->server_addr, sizeof(this->server_addr));
	this->server_addr.sin_family = AF_INET;
	this->server_addr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_IP, &this->server_addr.sin_addr);

	std::cout << "Client socket created\n";
}

void	Client::connection()
{
	if ((connect(this->client, reinterpret_cast<struct sockaddr *>(&this->server_addr), sizeof(this->server_addr))) == 0)
		std::cout << "Connection to server...\n"
				  << inet_ntoa(server_addr.sin_addr)
				  << " with port number "
				  << this->port << std::endl;
	else
		Client::error("Connection error");

	recv(this->client, this->buffer, BUFFER_SIZE, 0);
	std::cout << "Connection established!" << std::endl;
}

void	Client::chat()
{
	while (1)
	{
		std::cout << "Client: ";
		std::cin.getline(this->buffer, BUFFER_SIZE);
		send(this->client, this->buffer, BUFFER_SIZE, 0);
		if (Client::end_connection(this->buffer))
			break;

		std::cout << "Server: ";
		recv(this->client, this->buffer, BUFFER_SIZE, 0);
		std::cout << this->buffer << std::endl;
		if (Client::end_connection(this->buffer))
			break;
	}
}

void	Client::close_connection()
{
	close(this->client);
	std::cout << "\nEnd\n";
}


// --------------------------Helpful functions----------------------------

bool	Client::end_connection(const char *line)
{
	std::string str(line);

	if (str == "end connection" || str == "end connectin\n")
		return (true);
	return (false);
}

void	Client::error(std::string const &str)
{
	std::cout << str << std::endl;
	exit(0);
}
