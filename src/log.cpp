#include <iostream>
#include <queue>
#include <string>



#define PRINTLN(txt) std::cout << txt << std::endl;



std::queue<std::string> msgs;
std::queue<std::string> warnings;
std::queue<std::string> errors;



void log_m() {

    while (!msgs.empty()) {

        PRINTLN(msgs.front())
        msgs.pop();

    }

}

void log_w() {

    while (!warnings.empty()) {

        PRINTLN(warnings.front())
        warnings.pop();

    }

}

void log_e() {

    while (!errors.empty()) {

        PRINTLN(errors.front())
        errors.pop();

    }

}