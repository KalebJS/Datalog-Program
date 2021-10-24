#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " input_file" << std::endl;
    }

    std::string filename = argv[1];
    std::ifstream input(filename); //taking file as inputstream

    std::string input_str;
    if (input) {
        std::stringstream ss;
        ss << input.rdbuf(); // reading data
        input_str = ss.str();
    } else {
        std::cout << "Unable to read file." << std::endl;
        return 1;
    }

    Lexer *lexer = new Lexer();
    Parser *parser = new Parser();

    lexer->Run(input_str);

    bool wasParsed = parser->Parse(lexer->GetTokens());
    std::cout << parser->GetResult() << std::endl;
    if (wasParsed) {
        std::cout << parser->GetDatalog().toString();
    }

    delete lexer;
    delete parser;

    return 0;
}