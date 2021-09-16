#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    EOF_TYPE,
    COMMA,
    SPACE,
    NEWLINE,
    TAB,
    PERIOD,
    Q_MARK,
    UNDEFINED
};

class Token
{
private:
    TokenType type;
    std::string description;
    int line;

public:
    Token(TokenType type, std::string description, int line);

    std::string ToString ();

    std::string TokenTypeToString (TokenType tokenType);
};

#endif // TOKEN_H

