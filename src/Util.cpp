#include "../include/Util.h"

void ErrorIf(bool condition, const char* message){
    if(condition){
        perror(message);
        exit(EXIT_FAILURE);
    }
}

void log(const char* message){
    std::cout << "----------" << std::endl;
    std::cout << message << std::endl;
    std::cout << "----------" <<std::endl;
}