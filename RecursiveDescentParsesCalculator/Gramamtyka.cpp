#include "Gramatyka.h"
#include "Wyjatki.h"

bool Gramatyka::poprawnyOperator(char c){
    std::string operatory = "+-*/^()";
    for(char o : operatory){
        if (o == c) {
            return true;
        }
    }
    return false;
}

std::string Gramatyka::pobierzLiczbe(){
    // Pobierz liczbe i sprawdz czy jest zmiennoprzecinkowa, to znaczy ma tylko jedna kropke, lub jest intem
    std::string liczba;
    bool czyFloat = false;
    char c;
    while(stream.good()){
        c = stream.peek();
        if (c != '.' && !isdigit(c)){
            break;
        }
        c = stream.get();
        if(c=='.'){
            if(czyFloat)
                throw BladSkladni("Za duzo kropek!");
            else czyFloat = true;
        }
        liczba += c;
    }
    return liczba;
}

void Gramatyka::stworzToken(){
    // Pobiera kolejne znaki i wykonuje dla nich odpowiednie operacje, podzial na liczby i operatory
    char c = stream.peek(); // Nasteny znak
    while (stream.good()) {
        if (isdigit(c) || c == '.') {
            tokens.push_back(Token(Type::Liczba, pobierzLiczbe()));
        }
        else{
            stream.get(c);
            if (isspace(c)){
                while (stream.good() && isspace(stream.peek())) {
                    stream.get();
                }
            }
            else if (poprawnyOperator(c)) {
                tokens.push_back(Token(static_cast<Type>(c), { c }));
            }
            else {
                throw BladSkladni("Nieprawidlowy znak");
            }
        }
        c = stream.peek(); // sprawdzanie czy istnieje kolejny znak
    }
}