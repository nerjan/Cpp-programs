#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <stack>
#include <stack>

#include "Token.h"

class Parser{
public:
    Parser(std::vector<Token> const &wektor) : tokeny(wektor) {}
    std::vector<Token> stworzPostfix();
private:
    std::vector<Token> tokeny;

    bool sprawdzCzyPoprawnaSkladnia();
    Token wezPierwszy(std::stack<Token> &stack){ 
        Token lcz = stack.top(); 
        stack.pop(); 
        return lcz; 
    }
};

#endif