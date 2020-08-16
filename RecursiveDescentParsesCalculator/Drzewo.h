#ifndef DRZEWO_H
#define DRZEWO_H

#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "Token.h"
#include "Wyjatki.h"

template<class T>
class Drzewo{
public:
    Drzewo() : token(Token(Type::Brak, "")), wartosc(0), lewy(nullptr), prawy(nullptr) {}
    Drzewo(Token t) : token(t), wartosc(0), lewy(nullptr), prawy(nullptr) {}
    void buduj(std::vector<Token> postfix); 
    T sprawdz();
private:
    Token token;
    T wartosc;
    std::shared_ptr<Drzewo<T> > lewy;
    std::shared_ptr<Drzewo<T> > prawy;

    bool brakWolnychGalezi(){ 
        return (lewy!=nullptr && prawy!=nullptr); 
    }
    void zapelnijKorzen(std::shared_ptr<Drzewo<T> > n, std::shared_ptr<Drzewo<T> > m);
    T stringNaLiczbe(std::string str);
    std::shared_ptr<Drzewo<T> > budujDrzewo(std::vector<Token> &postfix);
};

template<class T>
void Drzewo<T>::zapelnijKorzen(std::shared_ptr<Drzewo<T> > n, std::shared_ptr<Drzewo<T> > m){
    // przypisanie wartosci prawy i lewy jesli jest to mozliwe (sa puste)
    // kolejnosc! prawy, lewy 
    if (n->prawy == nullptr) {
        n->prawy = m;
    }
    else if (n->lewy == nullptr) {
        n->lewy = m;
    }
    else {
        throw BladWewnetrzny("Wezel jest zapelniony!!");
    }
}

template<class T>
void Drzewo<T>::buduj(std::vector<Token> postfix){
    std::shared_ptr<Drzewo<T> > korzen = budujDrzewo(postfix);
    this->token = korzen->token;
    this->prawy = korzen->prawy;
    this->lewy = korzen->lewy;
}

template<class T>
std::shared_ptr<Drzewo<T> > Drzewo<T>::budujDrzewo(std::vector<Token> &postfix){
    // Budowanie drzewa notacja postfixowa
    std::shared_ptr<Drzewo<T> > korzen(new Drzewo<T>(postfix.back()));
    postfix.pop_back();
    while(!postfix.empty()){
        if(postfix.back().czyOperator())
            zapelnijKorzen(korzen, budujDrzewo(postfix));
        else{
            zapelnijKorzen(korzen, std::shared_ptr<Drzewo<T> >(new Drzewo<T>(postfix.back())));
            postfix.pop_back();
        }
        if(korzen->brakWolnychGalezi())
            return korzen;
    }
    return korzen;
}

template<class T>
T Drzewo<T>::stringNaLiczbe(std::string str){
    // zamiana string na liczbe ze sprawdzeniem poprawnosci operacji
    std::stringstream ss(str);
    T liczba; 
    ss >> liczba;
    if(ss.fail())
        throw BladTypuDanych("Nieudana konwersja z typu string do int.");
    return liczba;
}

template<class T>
T Drzewo<T>::sprawdz(){
    /**
    * W zaleznosci od tokenu wykonaj operacje dla liczby (zamien string na liczbe) lub odpowiednie dzialanie dla operatora
    * token nawiasu nie powinien sie pojawic w tym miejscu jesli skladnia byla poprawna - jesli jest, throw BladWewnetrzny
    * funkcja wykonywana jest rekurencyjnie dla calego drzewa
    */

    if (token.type == Type::Liczba) {
        return stringNaLiczbe(token.wartosc);
    }
    if (token.type == Type::Brak) {
        return 0;
    }
    switch (token.type){
        case Type::Dodaj : return lewy->sprawdz() + prawy->sprawdz();
        case Type::Odejmij : return lewy->sprawdz() - prawy->sprawdz();
        case Type::Mnoz : return lewy->sprawdz() * prawy->sprawdz();
        case Type::Poteguj: return std::pow(lewy->sprawdz(), prawy->sprawdz());
        case Type::Dziel: {
            if (prawy->sprawdz() == 0) {
                throw BladWewnetrzny("Dzielenie przez 0!");
            }
            else {
                return lewy->sprawdz() / prawy->sprawdz();
            }
        }
        default : throw BladWewnetrzny("Brak operatora!");
    }
    return 0;
}

#endif
