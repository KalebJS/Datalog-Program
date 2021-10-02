cmake_minimum_required(VERSION 3.16.3)
project(datalog)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
include_directories(.)

add_executable(Project_1
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        CommaAutomaton.cpp
        CommaAutomaton.h
        PeriodAutomaton.cpp
        PeriodAutomaton.h
        QuestionMarkAutomaton.cpp
        QuestionMarkAutomaton.h
        LeftParenAutomaton.cpp
        LeftParenAutomaton.h
        RightParenAutomaton.cpp
        RightParenAutomaton.h
        MultiplyAutomaton.cpp
        MultiplyAutomaton.h
        AddAutomaton.cpp
        AddAutomaton.h
        SchemesAutomaton.cpp
        SchemesAutomaton.h
        FactsAutomaton.cpp
        FactsAutomaton.h
        RulesAutomaton.cpp
        RulesAutomaton.h
        QueriesAutomaton.cpp
        QueriesAutomaton.h
        IdentifiersAutomaton.cpp
        IdentifiersAutomaton.h
        StringAutomaton.cpp
        StringAutomaton.h
        CommentAutomaton.cpp
        CommentAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h
        Parser.cpp
        Parser.h
        DatalogProgram.cpp
        DatalogProgram.h
        Predicate.cpp
        Predicate.h
        Rule.cpp
        Rule.h
        Parameter.cpp
        Parameter.h
        )
