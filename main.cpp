#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.h"

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " input_file" << std::endl;
    }

    std::string filename = argv[1];
    std::ifstream input(filename); //taking file as inputstream

    std::string input_str;
    if(input) {
        std::stringstream ss;
        ss << input.rdbuf(); // reading data
        input_str = ss.str();
    } else { return 1; }

    Lexer* lexer = new Lexer();

    lexer->Run(input_str);

    lexer->PrintTokens();

    delete lexer;

    return 0;
}