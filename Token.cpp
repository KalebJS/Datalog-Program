#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    this->type = type;
    this->description = description;
    this->line = line;
}

std::string Token::TokenTypeToString(TokenType tokenType) {
    switch (tokenType) {
        case TokenType::COLON:
            return "COLON";
            break;
        case TokenType::COLON_DASH :
            return "COLON_DASH";
            break;
        case TokenType::EOF_TYPE :
            return "EOF";
            break;
        case TokenType::COMMA :
            return "COMMA";
            break;
        case TokenType::PERIOD :
            return "PERIOD";
            break;
        case TokenType::Q_MARK :
            return "Q_MARK";
            break;
        case TokenType::LEFT_PAREN :
            return "LEFT_PAREN";
            break;
        case TokenType::RIGHT_PAREN :
            return "RIGHT_PAREN";
            break;
        case TokenType::MULTIPLY :
            return "MULTIPLY";
            break;
        case TokenType::ADD :
            return "ADD";
            break;
        case TokenType::SCHEMES :
            return "SCHEMES";
            break;
        case TokenType::FACTS :
            return "FACTS";
            break;
        case TokenType::RULES :
            return "RULES";
            break;
        case TokenType::QUERIES :
            return "QUERIES";
            break;
        case TokenType::ID :
            return "ID";
            break;
        case TokenType::STRING :
            return "STRING";
            break;
        case TokenType::COMMENT :
            return "COMMENT";
            break;

        case TokenType::UNDEFINED :
            return "UNDEFINED";
            break;
    }
    return "UNDEFINED"; // a string MUST be returned by the end
}

std::string Token::ToString() {
    std::string tokenReturnString = "(" + TokenTypeToString(type) + ",\"" + description + "\"," + std::to_string
            (line) + ")";
    return tokenReturnString;
}

TokenType Token::GetTokenType() {
    return this->type;
}