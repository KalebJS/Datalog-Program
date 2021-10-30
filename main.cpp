#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

void CleanUp(DatalogProgram *datalogProgram, Database *database, Parser *parser, Lexer *lexer, Interpreter
*interpreter);

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

    DatalogProgram *program = new DatalogProgram();
    Database *database = new Database();
    Lexer *lexer = new Lexer();
    Parser *parser = new Parser(program);
    Interpreter *interpreter = new Interpreter(program, database);

    lexer->Run(input_str);

    bool wasParsed = parser->Parse(lexer->GetTokens());
    if (!wasParsed) {
        CleanUp(program, database, parser, lexer, interpreter);
        exit(500);
    }

    interpreter->Interpret();

    CleanUp(program, database, parser, lexer, interpreter);

    return 0;
}

void CleanUp(DatalogProgram *datalogProgram, Database *database, Parser *parser, Lexer *lexer, Interpreter
*interpreter) {
    delete datalogProgram;
    delete database;
    delete interpreter;
    delete parser;
    delete lexer;
}