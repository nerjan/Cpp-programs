#ifndef ZAPISZODCZYTAJ_H
#define ZAPISZODCZYTAJ_H
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
class ZapiszOdczytaj
{
public:
    static std::string odczytajPlik(std::string sciezka);
    static void zapiszPlik(std::string sciezka, std::string stringToWrite);
	static void edytujPlik(std::string sciezka);
private:
	ZapiszOdczytaj() {};
};
std::string ZapiszOdczytaj::odczytajPlik(std::string sciezka)
{
	// pobiera i zwraca z pliku 'sciezka' rownanie
	std::string rownanie;

	ifstream plik(sciezka);
	if (!plik) { // nie udalo sie otworzyc pliku
		cerr << "Blad: nie udalo sie otworzyc pliku " << sciezka << endl;
		return "";
	}
	else {
		plik >> rownanie;
		plik.close();
		return rownanie;
	}

}

void ZapiszOdczytaj::zapiszPlik(std::string sciezka, std::string rownanieDoZapisania)
{
	// pobiera od uzytkownika rownanie i zapisuje do pliku 'sciezka'
	ofstream plik(sciezka);
	if (!plik) { // nie udalo sie otworzyc pliku
		cerr << "Blad: nie udalo sie otworzyc pliku " << sciezka << endl;
	}
	else {
		plik << rownanieDoZapisania;
		plik.close();
	}
}

void ZapiszOdczytaj::edytujPlik(std::string sciezka)
{
	//otwiera plik 'sciezka' wyswietla jego zawartosc i pozwala na edycje
	int indeksPoczatkowy;
	int jakWiele;
	std::string stareRownanie = odczytajPlik(sciezka);
	std::string coZmienic;
	std::string czyPotworzycWybor;
	bool czyPowtorzyc = true;
	while (czyPowtorzyc && stareRownanie != "") {
		try {
			cout << "Twoje rownanie to:" << endl;
			int i = 0;
			for (char& c : stareRownanie)
			{
				cout << i;
				i++;
				if (i == 10) {
					i = 0;
				}
			}
			cout << i;
			cout << endl;
			cout << stareRownanie << endl;
			cout << "Podaj indes zakresu znakow, ktore chcesz edytowac" << endl;
			cout << "Indeks poczatkowy: ";
			cin >> indeksPoczatkowy;
			cout << endl;
			cout << "Jak wiele znakow ma byc usunietych?: ";
			cin >> jakWiele;
			cout << "Co wpisac w to miejsce, wpisz 'x' jesli nic" <<endl;
			cin >> coZmienic;
			if (coZmienic == "x") {
				coZmienic = "";
			}
			stareRownanie.replace(indeksPoczatkowy, jakWiele, coZmienic);
			cout << "Rownanie po zmianie:" << endl;
			cout << stareRownanie << endl;
			cout << "Czy chcesz zmienic cos jeszcze? [1] Tak" << endl;
			cin >> czyPotworzycWybor;
			if (czyPotworzycWybor == "1") {
				czyPowtorzyc = true;
			}
			else {
				czyPowtorzyc = false;
			}

		}
		catch (const exception& e) {
			cout << "Cos poszlo nie tak, sprobuj ponownie" << endl;
			czyPowtorzyc = true;
		}
	}
	ZapiszOdczytaj::zapiszPlik(sciezka, stareRownanie);

}
#endif