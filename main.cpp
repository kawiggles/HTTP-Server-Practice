#include "server.hpp"
#include "logs.hpp"

int main() {
    initLogger();
    logMsg("Starting main.cpp");
    
    Server server = Server(); 
    server.run();

    closeLogger();
}
