#include <iostream>
#include "Parser.h"


std::queue<Token*> Parser::FilterComments(std::vector<Token*> unfilteredTokens) {
    std::queue<Token*> filteredTokens;
    for (long unsigned int i = 0; i < unfilteredTokens.size(); i++) {
        Token *token = unfilteredTokens.at(i);
        // ignore comments
        if (token->GetTokenType() == TokenType::COMMENT) {
            continue;
        } else {
            filteredTokens.push(token);
        }
    }
    return filteredTokens;
}
void Parser::Parse(std::vector<Token*> tokenVector) {
    tokens = FilterComments(tokenVector);
    // datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
    try {
        VerifyToken(TokenType::SCHEMES);
        VerifyToken(TokenType::COLON);
        Scheme();
        SchemeList();
        VerifyToken(TokenType::FACTS);
        VerifyToken(TokenType::COLON);
        FactList();
        VerifyToken(TokenType::RULES);
        VerifyToken(TokenType::COLON);
        RuleList();
        VerifyToken(TokenType::QUERIES);
        VerifyToken(TokenType::COLON);
        Query();
        QueryList();
        VerifyToken(TokenType::EOF_TYPE);
        std::cout << "Success!" << std::endl;
    } catch (Token* token) {
        std::cout << "Failure!" << std::endl;
        std::cout << token->ToString() << std::endl;
    }
}
void Parser::VerifyToken (TokenType type) {
    if (tokens.front()->GetTokenType() != type) {
        throw tokens.front();
    } else {
        tokens.pop();
    }
}
bool Parser::CompareNextTokenTypes (Token* token, TokenType type) {
    if (token->GetTokenType() != type) {
        return false;
    } else {
        return true;
    }
}
void Parser::SchemeList () {
    // schemeList	->	scheme schemeList | lambda
    if (CompareNextTokenTypes(tokens.front(), TokenType::ID)) {
        Scheme();
        SchemeList();
    }
}
void Parser::FactList () {
    // factList	->	fact factList | lambda
    if (CompareNextTokenTypes(tokens.front(), TokenType::ID)) {
        Fact();
        FactList();
    }
}
void Parser::RuleList () {
    // ruleList	->	rule ruleList | lambda
    if (CompareNextTokenTypes(tokens.front(), TokenType::ID)) {
        Rule();
        RuleList();
    }
}
void Parser::QueryList () {
    // queryList	->	query queryList | lambda
    if (CompareNextTokenTypes(tokens.front(), TokenType::ID)) {
        Query();
        QueryList();
    }

}
void Parser::Scheme () {
    // scheme  -> 	ID LEFT_PAREN ID idList RIGHT_PAREN
    VerifyToken(TokenType::ID);
    VerifyToken(TokenType::LEFT_PAREN);
    VerifyToken(TokenType::ID);
    IDList();
    VerifyToken(TokenType::RIGHT_PAREN);
}
void Parser::Fact () {
    // fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    VerifyToken(TokenType::ID);
    VerifyToken(TokenType::LEFT_PAREN);
    VerifyToken(TokenType::STRING);
    StringList();
    VerifyToken(TokenType::RIGHT_PAREN);
    VerifyToken(TokenType::PERIOD);
}
void Parser::Rule () {
    // rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
    HeadPredicate();
    VerifyToken(TokenType::COLON_DASH);
    Predicate();
    PredicateList();
    VerifyToken(TokenType::PERIOD);
}
void Parser::Query () {
    // query -> predicate Q_MARK
    Predicate();
    VerifyToken(TokenType::Q_MARK);
}
void Parser::HeadPredicate () {
    // headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
    VerifyToken(TokenType::ID);
    VerifyToken(TokenType::LEFT_PAREN);
    VerifyToken(TokenType::ID);
    IDList();
    VerifyToken(TokenType::RIGHT_PAREN);
}
void Parser::Predicate () {
    // predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    VerifyToken(TokenType::ID);
    VerifyToken(TokenType::LEFT_PAREN);
    Parameter();
    ParameterList();
    VerifyToken(TokenType::RIGHT_PAREN);
}
void Parser::PredicateList () {
    // predicateList	->	COMMA predicate predicateList | lambda
    if (CompareNextTokenTypes(tokens.front(), TokenType::COMMA)) {
        VerifyToken(TokenType::COMMA);
        Predicate();
        PredicateList();
    }
}
void Parser::ParameterList () {
    // parameterList	-> 	COMMA parameter parameterList | lambda
    if (CompareNextTokenTypes(tokens.front(), TokenType::COMMA)) {
        VerifyToken(TokenType::COMMA);
        Parameter();
        ParameterList();
    }
}
void Parser::StringList () {
    // stringList	-> 	COMMA STRING stringList | lambda
    if (CompareNextTokenTypes(tokens.front(), TokenType::COMMA)) {
        VerifyToken(TokenType::COMMA);
        VerifyToken(TokenType::STRING);
        StringList();
    }
}
void Parser::IDList () {
    // idList  	-> 	COMMA ID idList | lambda
    if (CompareNextTokenTypes(tokens.front(), TokenType::COMMA)) {
        VerifyToken(TokenType::COMMA);
        VerifyToken(TokenType::ID);
        IDList();
    }
}
void Parser::Parameter () {
    // parameter	->	STRING | ID
    if (CompareNextTokenTypes(tokens.front(), TokenType::STRING)) {
        VerifyToken(TokenType::STRING);
    } else if (CompareNextTokenTypes(tokens.front(), TokenType::ID)) {
        VerifyToken(TokenType::ID);
    } else {
        Token* token = tokens.front();
        throw token;
    }
}