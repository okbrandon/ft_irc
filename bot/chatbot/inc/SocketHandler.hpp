#ifndef SOCKETHANDLER_H
# define SOCKETHANDLER_H

# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <unistd.h>
# include <string>

class SocketHandler {

    private:
        int         _socket;
        sockaddr_in _address;
        int         _port; 
    
    public:
        SocketHandler(int port);
        ~SocketHandler(void);

        void    createSocket(void);
        void    connectSocket(std::string addr);
        void    closeSocket(void);
        int     getSocket(void) const;
};

#endif
