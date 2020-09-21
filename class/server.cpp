#include "server.h"

ChatServer::ChatServer()
{
    // CREATE SOCKET
    this->servSock = socket(AF_INET, SOCK_STREAM, 0);
    // CONFIGURE ADDRESS SETTINGS FOR THE SERVER
    this->Server_Addr.sin_family      = AF_INET;
    this->Server_Addr.sin_port        = htons(CHAT_PORT);
    this->Server_Addr.sin_addr.s_addr = INADDR_ANY;

    // BIND THE SOCKET
    int bindRes = bind(this->servSock, (sockaddr*)&(this->Server_Addr), sizeof(this->Server_Addr));

    // LISTEN
    listen(this->servSock, 5);

}

ChatServer* ChatServer::Server = nullptr;

ChatServer* ChatServer::getInstance(){
    if (Server == nullptr){
        Server = new ChatServer();
    }
    return Server;
}

void ChatServer::ACCEPT_CLIENTS()
{    
    socklen_t clnlen;
    accept(this->servSock, (sockaddr*)&(this->Server_Addr), &clnlen);
}

