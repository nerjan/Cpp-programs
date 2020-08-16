#ifndef WYJATKI_H
#define WYJATKI_H

#include <stdexcept>
#include <string>

class KalkulatorException : public std::exception{
public:
    KalkulatorException(std::string const &typBledu, std::string const &wiadomosc) :  wiadomosc(wiadomosc), typBledu(typBledu) {}
    const char* what() const throw(){
        return (typBledu + ": " + wiadomosc).c_str();
    }
private:
    std::string wiadomosc;
    std::string typBledu;
};

class BladSkladni : public KalkulatorException{
public:
    BladSkladni(std::string const &wiadomosc) : KalkulatorException("Zla skladnia", wiadomosc) {}
};

class BladTypuDanych : public KalkulatorException{
public:
    BladTypuDanych(std::string const &wiadomosc) : KalkulatorException("Niepoprawne dane", wiadomosc) {}
};

class BladWewnetrzny : public KalkulatorException{
public:
    BladWewnetrzny(std::string const &wiadomosc) : KalkulatorException("Blad Wewnetrzny", wiadomosc) {}
};

#endif