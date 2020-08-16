#ifndef GRAMATYKA_H
#define GRAMATYKA_H

#include <sstream>
#include <string>
#include <vector>

#include "Token.h"

class Gramatyka{
public:
    Gramatyka(std::string const &str) : stream(str) {}
    void stworzToken();
    std::vector<Token> wszystkieTokeny(){ 
        return tokens; 
    }
private:
    std::istringstream stream;
    std::vector<Token> tokens;

    std::string pobierzLiczbe();
    bool poprawnyOperator(char c);
};

#endif