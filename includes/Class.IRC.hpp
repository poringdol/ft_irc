#pragma once 

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
#include "Class.Command.hpp"
#include "Class.User.hpp"
#include "Class.Channel.hpp"
#include "Class.Server.hpp"

using std::map;
using std::string;
using std::vector;

class Channel;
class Command;

class IRC
{
	private:
		Socket						_network;
		string						_network_ip;
		int							_network_port;
		string						_network_pass;

		Socket						_localhost;
		Socket						_localhost_ssl;
		string						_localhost_pass;

		map<int, int>				_array_fd_select;
		fd_set						_fd_set_sockets;

		vector<User *>				_users;
		vector<Client *>			_clients;
		vector<Server *>			_servers;
		map<string, Channel>		_channels;

		int							_select_res;
		SSL*						_ssl;
		SSL_CTX*					_ctx;

	public:
		IRC();
		IRC(string network_ip,
			string network_port,
			string network_pass,
			string current_port,
			string _current_pass);

		IRC&						operator=(const IRC &other);

		void						create_socket_network();
		void						create_socket_local();
		void						init_fd_select();
		void						do_select();
		void						check_fd_select();
		void						do_command(Command * command, int socket_fd);

		void						init_ssl();
		void						init_ctx();
		SSL*						ssl_connection(int fd);

		int 						_send(int, int, const char *, size_t, int);
		int 						_recv(int, int, char *, size_t, int);

		
		void						delete_user(int fd);
		void						delete_client(int fd);

		vector<string> 				check_buffer(int fd, const char *buffer);
		void						join_channel(string, string);

		User*						get_user(string nickname);
		vector<User *> & 			get_users();
		vector<Client *> & 			get_clients();
		vector<Server *> & 			get_servers();
		map<string, Channel> & 		get_channels();
		string const &				get_localhost_pass() const;

		template <typename T>
		static int					find_fd(std::vector<T> *vect, int fd);
		template <typename T>
		static int					find_nickname(std::vector<T> *vect, string const & nickname);
};

#include "../Class.IRC.templates.cpp"