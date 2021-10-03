#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    EOF_TYPE,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
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
    virtual ~Token() = default;

    std::string GetDescription() { return description; }
    std::string ToString ();
    std::string TokenTypeToString (TokenType tokenType);
    TokenType GetTokenType ();
};

#endif // TOKEN_H

