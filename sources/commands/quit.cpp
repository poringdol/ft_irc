#include "Class.Command.hpp"
#include "Class.IRC.hpp"
#include "utils.hpp"

/*
** ====================================================================
** Команда: QUIT
** ====================================================================
** Параметры: [<Quit message>]
** Сессия клиента заканчивается с QUIT-сообщением. Сервер должен закрыть 
** соединение с клиентом, когда увидит посланное сообщение. 
** При нетсплите (разрыве соединения между двумя серверами), сообщение 
** QUIT содержит в себе имена двух серверов, разделенные пробелами. 
** Первое имя это сервер, который соединяется, второе имя сервера, который 
** отсоединился. 
** Если, по какой-либо причине, соединение клиента закрылось без введения 
** клиентом команды QUIT (например, обрыв связи), сервер потребует запаса 
** в quit-сообщениях с некоторой сортировкой сообщения, в поисках причины 
** разрыва. 
** =====================================================================
*/

int Command::cmd_quit(IRC& irc, int fd)
{
    vector<User*>& vec_users = irc.get_users();
    
    if (irc.find_fd(vec_users, fd) == -1)
    {
        irc.push_cmd_queue(fd, irc.response(ERR_USERSDISABLED, fd, "ERR_USERSDISABLED", ERR_USERSDISABLED_MESS));
        return (ERR_USERSDISABLED);
    }
    irc.close_connect(fd, 0);
    return (0);
}
