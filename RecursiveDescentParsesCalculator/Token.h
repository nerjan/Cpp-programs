#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class Type : char{
    Liczba = 'n',
    Dodaj = '+',
    Odejmij = '-',
    Mnoz = '*',
    Dziel = '/',
    Poteguj = '^',
    nawiasOtworz = '(',
    nawiasZamknij = ')',
    Brak = 'e'
};

struct Token{
    Type type;
    std::string wartosc;
    int kolejnoscWykonywaniaDzialan;
    Token(Type t, std::string wart) : type(t), wartosc(wart), kolejnoscWykonywaniaDzialan(0) {
        if (t == Type::Poteguj) {
            kolejnoscWykonywaniaDzialan = 3;
        }
        if (t == Type::Dziel || t == Type::Mnoz) {
            kolejnoscWykonywaniaDzialan = 2;
        }
        if (t == Type::Dodaj || t == Type::Odejmij) {
            kolejnoscWykonywaniaDzialan = 1;
        }
    }
    // Pomocnicza funkcja sprawdzajaca czy token jest operatorem dzialania
    bool czyOperator(){
        return ( type!=Type::Liczba 
              && type != Type::nawiasZamknij
              && type != Type::nawiasOtworz
              && type != Type::Brak ); 
    }
};

#endif