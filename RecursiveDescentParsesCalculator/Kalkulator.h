#ifndef KALKULATOR_H
#define KALKULATOR_H

#include <string>

#include "Gramatyka.h"
#include "Parser.h"
#include "Drzewo.h"

template<class T>
class Kalkulator{
public:
    static T oblicz(std::string const &str);
private:
    Kalkulator() {}
};

template<class T>
T Kalkulator<T>::oblicz(std::string const &str){
    //Polaczenie wsztkich funkcji
    Gramatyka gramatyka(str);
    gramatyka.stworzToken();
    Parser parser(gramatyka.wszystkieTokeny());
    Drzewo<T> drzewo;
    drzewo.buduj(parser.stworzPostfix());
    return drzewo.sprawdz();
}

#endif