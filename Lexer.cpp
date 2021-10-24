#include "Lexer.h"
#include "Token.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QuestionMarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IdentifiersAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include <iostream>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    for (Automaton *automaton: automata) {
        delete automaton;
    }
    automata.clear();;
    for (Token *token: tokens) {
        delete token;
    }
    tokens.clear();
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QuestionMarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    // this must be the final automaton for priority in parallel and max
    // keyword > automata
    automata.push_back(new IdentifiersAutomaton());
}

void Lexer::Run(std::string &input) {
    int lineNumber = 1;
    // While there are more characters to tokenize
    while (input.size() > 0) {
        Automaton *maxAutomaton = automata.at(0);
        int maxRead = 0;

        if (isspace(input.at(0)) || input.at(0) == '\t' || input.at(0) == '\n') {
            if (input.at(0) == '\n') {
                lineNumber++;
            }
            input = input.substr(1);
            continue;
        }

        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        for (long unsigned int i = 0; i < automata.size(); i++) {
            int inputRead = automata.at(i)->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }

        // Here is the "Max" part of the algorithm
        if (maxRead > 0) {
            Token *newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }
            // No automaton accepted input®
            // Create single character undefined token
        else {
            maxRead = 1;
            Token *newToken = new Token(TokenType::UNDEFINED, input.substr(0, maxRead), lineNumber);
            tokens.push_back(newToken);
        }

        input = input.substr(maxRead);
    }
    tokens.push_back(new Token(TokenType::EOF_TYPE, "", lineNumber));
}

void Lexer::PrintTokens() {
    for (long unsigned int i = 0; i < tokens.size(); i++) {
        std::cout << tokens.at(i)->ToString() << std::endl;
    }
    std::cout << "Total Tokens = " << tokens.size();
}