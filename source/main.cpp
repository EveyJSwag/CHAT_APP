#include <iostream>
#include <vector>
#include "../class/server.h"

int main() {
    
    ChatServer* SERVER = SERVER->getInstance();
    while(1)
        SERVER->ACCEPT_CLIENTS();
}
