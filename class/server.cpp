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
    
    std::cout << "######################" << std::endl;
    std::cout << "WAITING FOR CLIENTS..." << std::endl;
    std::cout << "######################" << std::endl << std::endl;

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
    int acceptStatus = accept(this->servSock, nullptr, nullptr);
    if (acceptStatus > 0)
    {
        std::cout << this->NUMBER_OF_CLIENTS << std::endl;
        CLIENTS[this->NUMBER_OF_CLIENTS].Client_Sock = acceptStatus;
        bindToThread();
    }
}

void ChatServer::handleClient()
{
    char buffer[100];
    socklen_t clientLength;
    static unsigned short* currentIP;
    getpeername(CLIENTS[this->NUMBER_OF_CLIENTS].Client_Sock, (sockaddr*)&CLIENTS[this->NUMBER_OF_CLIENTS].Client_Addr,  &clientLength);
    currentIP = parseIPV4(CLIENTS[this->NUMBER_OF_CLIENTS].Client_Addr.sin_addr.s_addr);
    
    int currentSocket = CLIENTS[this->NUMBER_OF_CLIENTS].Client_Sock;

    std::cout << "###################" << std::endl;
    std::cout << "CONNECTED A CLIENT!" << std::endl;
    printIPV4(currentIP);
    std::cout << this->NUMBER_OF_CLIENTS+1 << " TOTAL CLIENTS" << std::endl;
    std::cout << "WAITING FOR DATA..." << std::endl;
    std::cout << "###################" << std::endl;
    this->NUMBER_OF_CLIENTS++;
    while(1){

        if (recv(currentSocket, buffer, 100,0) > 0)
        {
            std::cout << buffer << std::endl;
        }

    }
    
}

void ChatServer::bindToThread()
{
    this->CLIENT_THREADS[this->NUMBER_OF_CLIENTS] = std::thread(&ChatServer::handleClient, this);
}

unsigned short* ChatServer::parseIPV4(in_addr_t addrInt)
{
    static unsigned short octArr[4];
    unsigned long  ipMask   = 0xFF;
    unsigned short shiftAmt = 0;
    char*          ipStr    = (char*)malloc(15);
    for (int i = 0; i < 4; i++){
        octArr[i] = (addrInt & ipMask) >> shiftAmt;
        shiftAmt+=8;
        ipMask <<= 8;
    }
    return octArr;
}

void ChatServer::printIPV4(unsigned short* addr)
{
    while ( *(addr+1) ){
        std::cout << *addr << ".";
        addr++;
    }
    std::cout << *addr << std::endl;
}