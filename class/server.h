#ifndef CHAT_SERVER
#define CHAT_SERVER

#include <netinet/in.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#define CHAT_PORT 51820

class ChatServer{

    private:
    ChatServer();
    static ChatServer *Server;
    struct sockaddr_in Server_Addr;
    

    public:
    unsigned long NUMBER_OF_CLIENTS;
    int servSock;
    static ChatServer* getInstance();
    void ACCEPT_CLIENTS();

};


#endif