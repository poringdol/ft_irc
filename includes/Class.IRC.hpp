/*
**==========================
** Class IRC - 
**==========================
*/
#include <openssl/ssl.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "main.hpp"
#include "Class.Socket.hpp"

//#include "Class.Client.hpp"
#include "Class.Message.hpp"
#include "Class.User.hpp"
//#include "Class.Getting.hpp"
//#include "Class.Sending.hpp"

class IRC	// иземенить на Irc
{
	private:
		Socket					_network;
		std::string				_network_ip;
		int						_network_port;
		std::string				_network_pass;
		Socket					_localhost;
		std::string				_localhost_pass;
		std::map<int, int>		_array_fd_select;
		std::vector<User *>		_users;
		std::vector<Client *>	_clients;
		// std::map<std::string, User>	users;
		// std::map<std::string, Server> servers;
		fd_set					_fd_set_sockets;
		int						_select_res;
		bool					_ssl;
		SSL_CTX*				_ctx;

	public:
		IRC();
		IRC(std::string network_ip,
			   std::string network_port,
			   std::string network_pass,
			   std::string current_port,
			   std::string _current_pass,
			   bool ssl = false);

		IRC &operator=(const IRC &other);

		void create_socket_network();
		void create_socket_local();

		void init_fd_select();
		void do_select();
		void check_fd_select();
		void do_command(Message * message, int socket_fd);
		void init_ssl();
		void init_ctx();
		void ssl_connection(int fd);
};