#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <exception>
#include <stack>

#include "Kalkulator.h"
#include "ZapiszOdczytaj.h"

using namespace std;

void rownanie(std::string rownanie) {
    if (!rownanie.empty()) {
        try {
            cout << "Wynik: " << Kalkulator<int>::oblicz(rownanie) << endl << endl;
        }
        catch (const exception& e) {
            std::cerr << "Nieprawidlowe dane!" << '\n';
        }
    }
}

void menu(){
    
    cout << "Co chcesz zrobic?" << endl;
    cout << "[1] Zapisz rownanie" << endl;
    cout << "[2] Odczytaj zapisane rownanie" << endl;
    cout << "[3] Wpisz rownanie" << endl;
    cout << "[4] Edytuj zapisane rownanie" << endl;
    cout << "[0] Zakoncz" << endl;
    std::string wybor;
    cin >> wybor;

    if (wybor == "1") {
        std::string rownanie;
        cout << "Podaj rownanie" << endl;
        cin >> rownanie;
        std::string sciezka;
        cout << "Podaj nazwke pliku" << endl;
        cin >> sciezka;
        ZapiszOdczytaj::zapiszPlik(sciezka, rownanie);
    }
    else if (wybor == "2") {
        std::string sciezka;
        cout << "Podaj nazwke pliku" << endl;
        cin >> sciezka;
        std:: string rown = ZapiszOdczytaj::odczytajPlik(sciezka);
        cout << rown << endl;
        rownanie(rown);
    }
    else if (wybor == "3") {
        cout << "Podaj wyrazenie" << endl;
        std::string rown;
        cin >> rown;
        rownanie(rown);
    }
    else if (wybor == "4") {
        std::string sciezka;
        cout << "Podaj nazwke pliku" << endl;
        cin >> sciezka;
        ZapiszOdczytaj::edytujPlik(sciezka);
    }
    else if (wybor == "0") {
        exit(1);
    }
    else {
        cout << "Podano zla wartosc!" << endl;
        menu();
    }

}


int main(){
    while (true) {
        menu();
    }
}
