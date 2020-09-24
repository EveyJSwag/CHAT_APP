#include <iostream>
#include <vector>
#include "../class/server.h"

std::thread threadArray[10];

void testFunction()
{
    std::cout << "WHY GOD";
}

int main() {
    
    ChatServer* SERVER = SERVER->getInstance();

    while(1){
        SERVER->ACCEPT_CLIENTS();
    }
    

}