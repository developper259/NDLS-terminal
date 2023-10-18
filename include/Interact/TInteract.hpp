#ifndef TERMINAL_INTERACT_NDL
#define TERMINAL_INTERACT_NDL

#include <iostream>
#include <vector>

class TInteract {
    public:
        TInteract();


        void print(std::string msg);
        void print(std::vector<std::string> msgs);

        void printError(std::string error);
        void printError(std::vector<std::string> errors);

        std::string answer(std::string msg);
        std::string answer(std::vector<std::string> msgs);
        std::vector<std::string> answers(std::vector<std::string> msgs);
};
TInteract::TInteract() {}

void TInteract::print(std::string msg) {
    std::cout << msg << std::endl;
}

void TInteract::print(std::vector<std::string> msgs) {
    for (std::string msg : msgs) {
        std::cout << msg;
    }
    std::cout << std::endl;
}

void TInteract::printError(std::string error) {
    std::cerr << error << std::endl;
}

void TInteract::printError(std::vector<std::string> errors) {
    for (std::string error : errors) {
        std::cerr << error;
    }
    std::cout << std::endl;
}

std::string TInteract::answer(std::string msg) {
    std::string response = "";

    std::cout << msg;
    std::getline(std::cin, response);

    return response;
}

std::string TInteract::answer(std::vector<std::string> msgs) {
    std::string response = "";
    for (std::string msg : msgs) {
        std::cout << msg;
    }
    std::getline(std::cin, response);

    return response;
}

std::vector<std::string> TInteract::answers(std::vector<std::string> msgs) {
    std::vector<std::string> responses;
    for (std::string msg : msgs) {
        std::string response = "";
        std::cout << msg;
        std::getline(std::cin, response);

        responses.push_back(response);
    }

    return responses;
}
#endif