cmake_minimum_required(VERSION 3.9)
project(CompilersAssignment)

set(CMAKE_CXX_STANDARD 11)

add_executable(CompilersAssignment main.cpp Lexer/LexerImplementation.cpp Lexer/LexerImplementation.h Lexer/Token.cpp Lexer/Token.h Lexer/State.h Lexer/Keywords.cpp Lexer/Keywords.h Parser/PredictiveParser.cpp Parser/PredictiveParser.h ASTHierarchy/ASTNode.h Visitors/Visitor.h ASTHierarchy/ASTExprNode.cpp ASTHierarchy/ASTExprNode.h ASTHierarchy/ASTStatementNode.cpp ASTHierarchy/ASTStatementNode.h ASTHierarchy/ASTNode.cpp)