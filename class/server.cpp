#include "server.h"

ChatServer::ChatServer()
{
    // INIT
    this->NUMBER_OF_CLIENTS = 0;

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

ChatServer* ChatServer::getInstance()
{
    if (Server == nullptr){
        Server = new ChatServer();
    }
    return Server;
}

void ChatServer::ACCEPT_CLIENTS()
{    
    std::cout << "######################" << std::endl;
    std::cout << "WAITING FOR CLIENTS..." << std::endl;
    std::cout << "######################" << std::endl << std::endl;
    socklen_t clnlen;
    int acceptStatus = accept(this->servSock, (sockaddr*)&(this->Server_Addr), &clnlen);
    if (acceptStatus > 0)
    {
        bindToThread();
    }
}

void ChatServer::handleClient(){
    std::cout << "###################" << std::endl;
    std::cout << "CONNECTED A CLIENT!" << std::endl;
    std::cout << this->NUMBER_OF_CLIENTS << " MANY CLIENTS" << std::endl;
    std::cout << "###################" << std::endl;
}

void ChatServer::bindToThread()
{

    this->CLIENT_THREADS[this->NUMBER_OF_CLIENTS] = std::thread(&ChatServer::handleClient, this);
    this->NUMBER_OF_CLIENTS++;

}

