#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " input_file" << std::endl;
    }

    std::string filename = argv[1];
    std::ifstream input(filename); //taking file as inputstream

    std::cout << filename << std::endl;

    std::string input_str;
    if(input) {
        std::stringstream ss;
        ss << input.rdbuf(); // reading data
        input_str = ss.str();
    } else {
        std::cout << "Unable to read file." << std::endl;
        return 1;
    }

    Lexer* lexer = new Lexer();
    Parser* parser = new Parser();

    lexer->Run(input_str);

    lexer->PrintTokens();

    std::cout << std::endl << std::endl;

    parser->Parse(lexer->GetTokens());

    delete parser;
    delete lexer;

    return 0;
}