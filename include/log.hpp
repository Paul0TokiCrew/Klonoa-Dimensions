#pragma once



#include <cstdio>
#include <iostream>
#include <queue>
#include <string>



#define PRINT(txt) std::cout << txt;
#define PRINTLN(txt) std::cout << txt << std::endl;
#define PRINTF(...) std::printf(__VA_ARGS__);



extern std::queue<std::string> msgs;
extern std::queue<std::string> warnings;
extern std::queue<std::string> errors;



extern void log_m();
extern void log_w();
extern void log_e();