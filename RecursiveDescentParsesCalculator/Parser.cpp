#include "Parser.h"
#include "Wyjatki.h"

bool Parser::sprawdzCzyPoprawnaSkladnia(){
    // Sprawdz poprawnosc skladni, czyli nawiasy, ktorych musi byc wiecej lub 0 gdy ( to +1 a ) to -1
    // czy wystepuje operator
    int nawiasy = 0;
    bool operation = false;
    if (tokeny.size() > 0 && tokeny[0].czyOperator()) {
        return false;
    }
    for(unsigned i = 0; i < tokeny.size(); i++){
        if (tokeny[i].type == Type::Brak) {
            continue;
        }
        if (tokeny[i].czyOperator()) {
            if (operation) {
                return false;
            }
            else {
                operation = true;
            }
        }
        else {
            if (tokeny[i].type != Type::nawiasZamknij) {
                operation = false;
            }
        }
        if (i > 0 && tokeny[i].type == Type::Liczba && tokeny[i - 1].type == Type::Liczba) {
            return false;
        }
        if (tokeny[i].type == Type::nawiasOtworz && i > 0 && tokeny[i - 1].type == Type::Liczba) {
            return false;
        }
        if (tokeny[i].type == Type::nawiasOtworz) {
            nawiasy++;
        }
        if (tokeny[i].type == Type::nawiasZamknij) {
            nawiasy--;
        }
        if (nawiasy < 0) {
            return false;
        }
    }
    return (nawiasy==0 && operation==false);
}

std::vector<Token> Parser::stworzPostfix(){
    //Tworzenie posftixowej wersji dzialania
    if (!sprawdzCzyPoprawnaSkladnia()) {
        throw BladSkladni("Niepoprawna skladnia");
    }
    std::vector<Token> tokenVector;
    std::stack<Token> operatory;
    for(unsigned i = 0; i < tokeny.size(); i++){
        if (tokeny[i].type == Type::Brak) {
            continue;
        }
        if (tokeny[i].type == Type::Liczba) {
            tokenVector.push_back(tokeny[i]);
        }
        else if(tokeny[i].type == Type::nawiasOtworz){
            operatory.push(tokeny[i]);
            //dodaj 0 aby obsluzyc liczby ujemne(0-3=-3)
            if (i < tokeny.size() - 1 && (tokeny[i + 1].type == Type::Dodaj || tokeny[i + 1].type == Type::Odejmij)) {
                tokenVector.push_back(Token(Type::Liczba, "0"));
            }
        }
        else if(tokeny[i].type == Type::nawiasZamknij){
            while (operatory.top().type != Type::nawiasOtworz) {
                tokenVector.push_back(wezPierwszy(operatory));
            }
            operatory.pop();
        }
        else{
            while (!operatory.empty() && operatory.top().kolejnoscWykonywaniaDzialan >= tokeny[i].kolejnoscWykonywaniaDzialan) {
                tokenVector.push_back(wezPierwszy(operatory));
            }
            operatory.push(tokeny[i]);
        }
    }
    while (!operatory.empty()) {
        tokenVector.push_back(wezPierwszy(operatory));
    }
    return tokenVector;
}