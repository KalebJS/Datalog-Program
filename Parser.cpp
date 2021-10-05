#include <iostream>
#include "Parser.h"


std::queue<Token*> Parser::FilterComments(std::vector<Token*> unfilteredTokens) {
    std::queue<Token*> filteredTokens;
    for (long unsigned int i = 0; i < unfilteredTokens.size(); i++) {
        Token* token = unfilteredTokens.at(i);
        // ignore comments
        if (token->GetTokenType() == TokenType::COMMENT) {
            continue;
        } else {
            filteredTokens.push(token);
        }
    }
    return filteredTokens;
}
bool Parser::Parse(std::vector<Token*> tokenVector) {
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
        result += "Success!";
        return true;
    } catch (Token* token) {
        result += "Failure! \n" + token->ToString();
        return false;
    }
}
void Parser::VerifyToken (TokenType type) {
    if (tokens.front()->GetTokenType() != type) {
        throw tokens.front();
    } else {
        tokens.pop();
    }
}
void Parser::VerifyToken (TokenType type, Predicate& predicate) {
    if (tokens.front()->GetTokenType() != type) {
        throw tokens.front();
    } else {
        predicate.AddElement(tokens.front());
        tokens.pop();
    }
}
void Parser::VerifyToken (TokenType type, Rule& rule) {
    if (tokens.front()->GetTokenType() != type) {
        throw tokens.front();
    } else {
        //rule.AddElement(tokens.front());
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
        RuleMethod();
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
    Predicate scheme = Predicate();
    VerifyToken(TokenType::ID, scheme);
    VerifyToken(TokenType::LEFT_PAREN, scheme);
    VerifyToken(TokenType::ID, scheme);
    IDList(scheme);
    VerifyToken(TokenType::RIGHT_PAREN, scheme);
    datalog.AddScheme(scheme);
}
void Parser::Fact () {
    // fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    Predicate fact = Predicate();
    VerifyToken(TokenType::ID, fact);
    VerifyToken(TokenType::LEFT_PAREN, fact);
    VerifyToken(TokenType::STRING, fact);
    StringList(fact);
    VerifyToken(TokenType::RIGHT_PAREN, fact);
    VerifyToken(TokenType::PERIOD, fact);
    datalog.AddFact(fact);
}
void Parser::RuleMethod () {
    // rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
    Rule rule = Rule();
    HeadPredicate(rule);
    VerifyToken(TokenType::COLON_DASH);
    PredicateMethod(rule);
    PredicateList(rule);
    VerifyToken(TokenType::PERIOD);
    datalog.AddRule(rule);
}
void Parser::Query () {
    // query -> predicate Q_MARK
    Predicate query = Predicate();
    PredicateMethod(query);
    VerifyToken(TokenType::Q_MARK, query);
    datalog.AddQuery(query);
}
void Parser::HeadPredicate () {
    // headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
    VerifyToken(TokenType::ID);
    VerifyToken(TokenType::LEFT_PAREN);
    VerifyToken(TokenType::ID);
    IDList();
    VerifyToken(TokenType::RIGHT_PAREN);
}
void Parser::HeadPredicate (Rule& rule) {
    // headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
    Predicate headPredicate = Predicate();
    VerifyToken(TokenType::ID, headPredicate);
    VerifyToken(TokenType::LEFT_PAREN, headPredicate);
    VerifyToken(TokenType::ID, headPredicate);
    IDList(headPredicate);
    VerifyToken(TokenType::RIGHT_PAREN, headPredicate);
    rule.SetHeadPredicate(headPredicate);
}
void Parser::PredicateMethod () {
    // predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    VerifyToken(TokenType::ID);
    VerifyToken(TokenType::LEFT_PAREN);
    Parameter();
    ParameterList();
    VerifyToken(TokenType::RIGHT_PAREN);
}
void Parser::PredicateMethod (Predicate& predicate) {
    // predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    VerifyToken(TokenType::ID, predicate);
    VerifyToken(TokenType::LEFT_PAREN, predicate);
    Parameter(predicate);
    ParameterList(predicate);
    VerifyToken(TokenType::RIGHT_PAREN, predicate);
}
void Parser::PredicateMethod (Rule& rule) {
    // predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    Predicate predicate = Predicate();
    VerifyToken(TokenType::ID, predicate);
    VerifyToken(TokenType::LEFT_PAREN, predicate);
    Parameter(predicate);
    ParameterList(predicate);
    VerifyToken(TokenType::RIGHT_PAREN, predicate);
    rule.AddPredicate(predicate);
}
void Parser::PredicateList () {
    // predicateList	->	COMMA predicate predicateList | lambda
    if (CompareNextTokenTypes(tokens.front(), TokenType::COMMA)) {
        VerifyToken(TokenType::COMMA);
        PredicateMethod();
        PredicateList();
    }
}
void Parser::PredicateList (Rule& rule) {
    // predicateList	->	COMMA predicate predicateList | lambda
    if (CompareNextTokenTypes(tokens.front(), TokenType::COMMA)) {
        VerifyToken(TokenType::COMMA);
        PredicateMethod(rule);
        PredicateList(rule);
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
void Parser::ParameterList (Predicate& predicate) {
    // parameterList	-> 	COMMA parameter parameterList | lambda
    if (CompareNextTokenTypes(tokens.front(), TokenType::COMMA)) {
        VerifyToken(TokenType::COMMA, predicate);
        Parameter(predicate);
        ParameterList(predicate);
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
void Parser::StringList (Predicate& predicate) {
    // stringList	-> 	COMMA STRING stringList | lambda
    if (CompareNextTokenTypes(tokens.front(), TokenType::COMMA)) {
        VerifyToken(TokenType::COMMA, predicate);
        VerifyToken(TokenType::STRING, predicate);
        StringList(predicate);
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
void Parser::IDList (Predicate& predicate) {
    // idList  	-> 	COMMA ID idList | lambda
    if (CompareNextTokenTypes(tokens.front(), TokenType::COMMA)) {
        VerifyToken(TokenType::COMMA, predicate);
        VerifyToken(TokenType::ID, predicate);
        IDList(predicate);
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
void Parser::Parameter (Predicate& predicate) {
    // parameter	->	STRING | ID
    if (CompareNextTokenTypes(tokens.front(), TokenType::STRING)) {
        VerifyToken(TokenType::STRING, predicate);
    } else if (CompareNextTokenTypes(tokens.front(), TokenType::ID)) {
        VerifyToken(TokenType::ID, predicate);
    } else {
        Token* token = tokens.front();
        throw token;
    }
}