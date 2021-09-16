#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    this->type = type;
    this->description = description;
    this->line = line;
}

std::string Token::TokenTypeToString(TokenType tokenType) {
    switch (tokenType) {
        case TokenType::COLON: return "COLON"; break;
        case TokenType::COLON_DASH : return "COLON_DASH"; break;
        case TokenType::EOF_TYPE : return "EOF"; break;
        case TokenType::SPACE : return "SPACE"; break;
        case TokenType::COMMA : return "COMMA"; break;
        case TokenType::NEWLINE : return "NEWLINE"; break;
        case TokenType::TAB : return "TAB"; break;
        case TokenType::PERIOD : return "PERIOD"; break;
        case TokenType::Q_MARK : return "Q_MARK"; break;
        case TokenType::UNDEFINED : return "UNDEFINED"; break;
    }
    return "UNDEFINED"; // a string MUST be returned by the end
}
std::string Token::ToString () {
    std::string tokenReturnString = "(" + TokenTypeToString(type) + ", " + description + ", " + std::to_string(line) + ")";
    return tokenReturnString;
}