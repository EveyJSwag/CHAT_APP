#include <iostream>
#include "../class/server.h"

int main() {
    
    ChatServer* SERVER = SERVER->getInstance();

    //std::cout << "LISTENING ON PORT " << CHAT_PORT << std::endl;

    SERVER->ACCEPT_CLIENTS();

}