// ==========================================================================
//
// Main header file, where program starts. 
//
// ==========================================================================

#pragma once

#include "derivative.h"

//#define MAX_WYRAZENIE_LENGTH 100 //Maksymalna d³ugoœæ wyra¿enia

class zdanie { //klasa przygotowujaca otrzymane wyrazenie do zrozcznikowania oraz sprawdzajaca czy podane wyrazenie nie zawiera bledow
private:
	string wyrazenie;//zmienna przechowujaca otrzymane przez uzytkownika wyrazenie a nastepnie policznoa pochodna z tego wyrazenia

public:
	zdanie(string odczytane) { //constructor
		wyrazenie = odczytane;	
	}
	~zdanie() {} //destructor

public:
	void setWyrazenie(string odczytane) { wyrazenie = odczytane; } //setter
	string getWyrazenie(void) { return wyrazenie; } //getter

public:
	bool checkWyrazenie(void) { //funkcja sprawdzajaca czy podane wyrazenie jest poprawne, na ten moment sprawdzajaca tylko zgodnosc liczby nawiasow
		int bracket_counter{ 0 }; //licznik par nawiasów, je¿eli liczba nawiasów siê zgadza, wartoœæ pozostanie równa 0
		int bracket_all_counter{ 0 }; //licznik wszystkich nawiasów, sprawdza jak du¿o jest nawiasów
		wyrazenie.erase(remove(wyrazenie.begin(), wyrazenie.end(), ' '), wyrazenie.end());
		size_t found_przecinek = wyrazenie.find_first_of(",");
		while (found_przecinek != std::string::npos) {
			wyrazenie[found_przecinek] = '.';
			found_przecinek = wyrazenie.find_first_of(",", found_przecinek + 1);
		}
		if (wyrazenie[0]=='+'|| wyrazenie[0] == '/' || wyrazenie[0] == '*') {
			wyrazenie.erase(wyrazenie.begin());
		}
		if (wyrazenie[wyrazenie.length() - 1] == '+' || wyrazenie[wyrazenie.length() - 1] == '/' || wyrazenie[wyrazenie.length() - 1] == '*') {
			wyrazenie.erase(wyrazenie.length() - 1);
		}
		for (auto i = 0; i < wyrazenie.length();i++) {
			wyrazenie[i]=tolower(wyrazenie[i]);
			if (wyrazenie[i] == '*' && ((wyrazenie[size_t(i - 1)] == 'x' && wyrazenie[size_t(i + 1)] >= '0' && wyrazenie[size_t(i + 1)] <= '9') || (wyrazenie[size_t(i + 1)] == 'x' && wyrazenie[size_t(i - 1)] >= '0' && wyrazenie[size_t(i - 1)] <= '9'))) {
				wyrazenie.erase(wyrazenie.begin() + i);
			}
			if (wyrazenie[i] == '(') bracket_counter++;
			else if (wyrazenie[i] == ')')bracket_counter--;
		}
		if (bracket_counter != 0) {
			system("cls");
			std::cout << "Podano bledne wyrazenie (liczba nawiasow sie nie zgadza).";
			return false;
		}
		return true;
	}
	void simplify(void) { //funkcja upraszczajaca wyrazenie, na ten moment upraszcza tylko mnozenie liczb
		if(wyrazenie.length()>1){
			for (auto i = 1; i < wyrazenie.length(); i++) {
				if (i < wyrazenie.length() - 1) {
					if (wyrazenie[i] == '*' && (wyrazenie[size_t(i + 1)] >= '0' && wyrazenie[size_t(i + 1)] <= '9') && (wyrazenie[size_t(i - 1)] >= '0' && wyrazenie[size_t(i - 1)] <= '9')) {
						size_t index_liczby[2][2] = { {size_t(i - 1),size_t(i - 1)}, {size_t(i + 1),size_t(i + 1)} };
						int j = i - 1;
						while (j > 0) {
							if (wyrazenie[j] == '+' || wyrazenie[j] == '-' || wyrazenie[j] == '*' || wyrazenie[j] == '/') {
								index_liczby[0][0] = size_t(j + 1);
								break;
							}
							j--;
						}
						j = i + 1;
						while (j < wyrazenie.length()) {
							if (wyrazenie[j] == '+' || wyrazenie[j] == '-' || wyrazenie[j] == '*' || wyrazenie[j] == '/' || wyrazenie[j] == ')') {
								index_liczby[1][1] = size_t(j - 1);
								break;
							}
							if (j == wyrazenie.length() - 1 && wyrazenie[j] != ')') {
								index_liczby[1][1] = j;
								break;
							}
							j++;
						}
						string liczba1 = wyrazenie.substr(index_liczby[0][0], index_liczby[0][1] - index_liczby[0][0] + 1);
						string liczba2 = wyrazenie.substr(index_liczby[1][0], index_liczby[1][1] - index_liczby[1][0] + 1);
						auto wynik{ 0.0 };
						size_t found_liczba1 = liczba1.find(".");
						size_t found_liczba2 = liczba2.find(".");
						wyrazenie.erase(index_liczby[0][0], index_liczby[1][1] - index_liczby[0][0]);
						if (found_liczba1 != string::npos || found_liczba2 != string::npos) {
							auto mnozona{ 0.0 };
							auto mnoznik{ 0.0 };
							auto dziesiec{ 10.0 };
							bool przecinek = false;
							for (size_t k = 0; k < liczba1.length(); k++) {
								if (liczba1[k] == '.') {
									przecinek = true;
									continue;
								}
								if (przecinek) {
									mnozona = mnozona + (double)(liczba1[k] - '0') / dziesiec;
									dziesiec *= dziesiec;
								}
								else {
									mnozona = mnozona * dziesiec + (double)(liczba1[k] - '0');
								}
							}
							dziesiec = 10.0;
							przecinek = false;
							for (size_t k = 0; k < liczba1.length(); k++) {
								if (liczba1[k] == '.') {
									przecinek = true;
									continue;
								}
								if (przecinek) {
									mnoznik = mnoznik + (double)(liczba1[k] - '0') / dziesiec;
									dziesiec *= dziesiec;
								}
								else {
									mnoznik = mnoznik * dziesiec + (double)(liczba1[k] - '0');
								}
							}
							wynik = mnoznik * mnoznik;
							liczba1 = std::to_string((int)wynik);
							vector <char> wstaw;
							for (auto k = 0; k < liczba1.length() - 3; k++) {
								wstaw.push_back(liczba1[k]);
								wyrazenie.insert(wyrazenie.begin() + index_liczby[0][0] + k, wstaw[k]);
							}
						}
						else {
							auto mnozona = stoi(liczba1);
							auto mnoznik = stoi(liczba2);
							wynik = mnoznik * mnoznik;
							liczba1 = std::to_string((int)wynik);
							vector <char> wstaw;
							for (auto k = 0; k < liczba1.length(); k++) {
								wstaw.push_back(liczba1[k]);
								wyrazenie.insert(wyrazenie.begin() + index_liczby[0][0] + k, wstaw[k]);
							}
						}
						i = 1;
					}
					if (wyrazenie[i] == 'x' && (wyrazenie[size_t(i + 1)] >= '0' && wyrazenie[size_t(i + 1)] <= '9') && (wyrazenie[size_t(i - 1)] >= '0' && wyrazenie[size_t(i - 1)] <= '9')) {
						size_t index_liczby[2][2] = { {size_t(i - 1),size_t(i - 1)}, {size_t(i + 1),size_t(i + 1)} };
						int j = i - 1;
						while (j > 0) {
							if (wyrazenie[j] == '+' || wyrazenie[j] == '-' || wyrazenie[j] == '*' || wyrazenie[j] == '/') {
								index_liczby[0][0] = size_t(j + 1);
								break;
							}
							j--;
						}
						j = i + 1;
						while (j < wyrazenie.length()) {
							if (wyrazenie[j] == '+' || wyrazenie[j] == '-' || wyrazenie[j] == '*' || wyrazenie[j] == '/' || wyrazenie[j] == ')') {
								index_liczby[1][1] = size_t(j - 1);
								break;
							}
							if (j == wyrazenie.length() - 1 && wyrazenie[j] != ')') {
								index_liczby[1][1] = j;
								break;
							}
							j++;
						}
						string liczba1 = wyrazenie.substr(index_liczby[0][0], index_liczby[0][1] - index_liczby[0][0] + 1);
						string liczba2 = wyrazenie.substr(index_liczby[1][0], index_liczby[1][1] - index_liczby[1][0] + 1);
						auto wynik{ 0.0 };
						size_t found_liczba1 = liczba1.find(".");
						size_t found_liczba2 = liczba2.find(".");
						wyrazenie.erase(index_liczby[1][0], index_liczby[1][1] - index_liczby[1][0] + 1);
						wyrazenie.erase(index_liczby[0][0], index_liczby[0][1] - index_liczby[0][0] + 1);
						if (found_liczba1 != string::npos || found_liczba2 != string::npos) {
							auto mnozona{ 0.0 };
							auto mnoznik{ 0.0 };
							auto dziesiec{ 10.0 };
							bool przecinek = false;
							for (size_t k = 0; k < liczba1.length(); k++) {
								if (liczba1[k] == '.') {
									przecinek = true;
									continue;
								}
								if (przecinek) {
									mnozona = mnozona + (double)(liczba1[k] - '0') / dziesiec;
									dziesiec *= dziesiec;
								}
								else {
									mnozona = mnozona * dziesiec + (double)(liczba1[k] - '0');
								}
							}
							dziesiec = 10.0;
							przecinek = false;
							for (size_t k = 0; k < liczba1.length(); k++) {
								if (liczba1[k] == '.') {
									przecinek = true;
									continue;
								}
								if (przecinek) {
									mnoznik = mnoznik + (double)(liczba1[k] - '0') / dziesiec;
									dziesiec *= dziesiec;
								}
								else {
									mnoznik = mnoznik * dziesiec + (double)(liczba1[k] - '0');
								}
							}
							wynik = mnoznik * mnoznik;
							liczba1 = std::to_string(wynik);
							vector <char> wstaw;
							for (auto k = 0; k < liczba1.length() - 3; k++) {
								wstaw.push_back(liczba1[k]);
								wyrazenie.insert(wyrazenie.begin() + index_liczby[0][0] + k, wstaw[k]);
							}
						}
						else {
							auto mnozona = stoi(liczba1);
							auto mnoznik = stoi(liczba2);
							wynik = mnozona * mnoznik;
							liczba1 = std::to_string((int)wynik);
							vector <char> wstaw;
							for (auto k = 0; k < liczba1.length(); k++) {
								wstaw.push_back(liczba1[k]);
								wyrazenie.insert(wyrazenie.begin() + index_liczby[0][0] + k, wstaw[k]);
							}
						}
						i = 1;
					}
					
					if (i < wyrazenie.length() - 2) {
						if ((wyrazenie[i] == '+' || wyrazenie[i] == '-') && (wyrazenie[size_t(i + 1)] >= '0' && wyrazenie[size_t(i + 1)] <= '9') && (wyrazenie[size_t(i - 1)] >= '0' && wyrazenie[size_t(i - 1)] <= '9')) {
							int j = i + 1;
							bool zX = false;
							for (; j < wyrazenie.length() && wyrazenie[j] != '+' && wyrazenie[j] != '-';j++) {
								if (wyrazenie[j]=='x') {
									zX = true;
									break;
								}
								if (wyrazenie[j] == '*' || wyrazenie[j] == '/') {
									break;
								}
							}
							if (zX)continue;
							size_t index_liczby[2][2] = { {size_t(i - 1),size_t(i - 1)}, {size_t(i + 1),size_t(i + 1)} };
							j = i - 1;
							while (j > 0) {
								if (wyrazenie[j] == '+' || wyrazenie[j] == '-' || wyrazenie[j] == '*' || wyrazenie[j] == '/') {
									index_liczby[0][0] = size_t(j + 1);
									break;
								}
								j--;
							}
							j = i + 1;
							while (j < wyrazenie.length()) {
								if (wyrazenie[j] == '+' || wyrazenie[j] == '-' || wyrazenie[j] == '*' || wyrazenie[j] == '/' || wyrazenie[j] == ')') {
									index_liczby[1][1] = size_t(j - 1);
									break;
								}
								if (j == wyrazenie.length() - 1 && wyrazenie[j] != ')') {
									index_liczby[1][1] = j;
									break;
								}
								j++;
							}
							string liczba1 = wyrazenie.substr(index_liczby[0][0], index_liczby[0][1] - index_liczby[0][0] + 1);
							string liczba2 = wyrazenie.substr(index_liczby[1][0], index_liczby[1][1] - index_liczby[1][0] + 1);
							auto wynik{ 0.0 };
							size_t found_liczba1 = liczba1.find(".");
							size_t found_liczba2 = liczba2.find(".");
							wyrazenie.erase(index_liczby[1][0], index_liczby[1][1] - index_liczby[1][0] + 1);
							wyrazenie.erase(index_liczby[0][0], index_liczby[0][1] - index_liczby[0][0] + 1);
							if (found_liczba1 != string::npos || found_liczba2 != string::npos) {
								auto suma1{ 0.0 };
								auto suma2{ 0.0 };
								auto dziesiec{ 10.0 };
								bool przecinek = false;
								for (size_t k = 0; k < liczba1.length(); k++) {
									if (liczba1[k] == '.') {
										przecinek = true;
										continue;
									}
									if (przecinek) {
										suma1 = suma1 + (double)(liczba1[k] - '0') / dziesiec;
										dziesiec *= dziesiec;
									}
									else {
										suma1 = suma1 * dziesiec + (double)(liczba1[k] - '0');
									}
								}
								dziesiec = 10.0;
								przecinek = false;
								for (size_t k = 0; k < liczba1.length(); k++) {
									if (liczba1[k] == '.') {
										przecinek = true;
										continue;
									}
									if (przecinek) {
										suma2 = suma2 + (double)(liczba1[k] - '0') / dziesiec;
										dziesiec *= dziesiec;
									}
									else {
										suma2 = suma2 * dziesiec + (double)(liczba1[k] - '0');
									}
								}
								if (wyrazenie[i] == '+')wynik = suma1 + suma2;
								else wynik = suma1 - suma2;
								
								liczba1 = std::to_string(wynik);
								vector <char> wstaw;
								for (auto k = 0; k < liczba1.length() - 3; k++) {
									wstaw.push_back(liczba1[k]);
									wyrazenie.insert(wyrazenie.begin() + index_liczby[0][0] + k, wstaw[k]);
								}
							}
							else {
								auto suma1 = stoi(liczba1);
								auto suma2 = stoi(liczba2);
								if (wyrazenie[i] == '+')wynik = suma1 + suma2;
								else wynik = suma1 - suma2;
								liczba1 = std::to_string((int)wynik);
								vector <char> wstaw;
								for (auto k = 0; k < liczba1.length(); k++) {
									wstaw.push_back(liczba1[k]);
									wyrazenie.insert(wyrazenie.begin() + index_liczby[0][0] + k, wstaw[k]);
								}
							}
							i = 1;
						}
						if (wyrazenie[i] == 'x' && (wyrazenie[size_t(i + 1)] == '+' || wyrazenie[size_t(i + 1)] == '-') && (wyrazenie[size_t(i + 2)] >= '0' && wyrazenie[size_t(i + 2)] <= '9')) {
							int j = i + 1;
							bool zX = true;
							for (; j < wyrazenie.length() && wyrazenie[j] == 'x' && wyrazenie[j] != '-'; j++) {
								if (wyrazenie[j] == '+' || wyrazenie[j] == '-') {
									zX = false;
									break;
								}
								if (wyrazenie[j] == '*' || wyrazenie[j] == '/') {
									break;
								}
							}
							if (!zX)continue;
							size_t index_liczby[2][2] = { {size_t(i - 1),size_t(i - 1)}, {size_t(i + 1),size_t(i + 1)} };
							string liczba1;
							if (!(wyrazenie[index_liczby[0][0]] >= '0' && wyrazenie[index_liczby[0][0]] <= '9')) liczba1 = "0";
							else {
								j = i - 1;
								while (j > 0) {
									if (wyrazenie[j] == '+' || wyrazenie[j] == '-' || wyrazenie[j] == '*' || wyrazenie[j] == '/') {
										index_liczby[0][0] = size_t(j + 1);
										break;
									}
									j--;
								}
								liczba1 = wyrazenie.substr(index_liczby[0][0], index_liczby[0][1] - index_liczby[0][0] + 1);
							}
							j = i + 1;
							while (j < wyrazenie.length()) {
								if (wyrazenie[j] == '+' || wyrazenie[j] == '-' || wyrazenie[j] == '*' || wyrazenie[j] == '/' || wyrazenie[j] == ')') {
									index_liczby[1][1] = size_t(j - 1);
									break;
								}
								if (j == wyrazenie.length() - 1 && wyrazenie[j] != ')') {
									index_liczby[1][1] = j;
									break;
								}
								j++;
							}
							string liczba2 = wyrazenie.substr(index_liczby[1][0], index_liczby[1][1] - index_liczby[1][0] + 1);
							auto wynik{ 0.0 };
							size_t found_liczba1 = liczba1.find(".");
							size_t found_liczba2 = liczba2.find(".");
							wyrazenie.erase(index_liczby[1][0], index_liczby[1][1] - index_liczby[1][0] + 1);
							wyrazenie.erase(index_liczby[0][0], index_liczby[0][1] - index_liczby[0][0] + 1);
							if (found_liczba1 != string::npos || found_liczba2 != string::npos) {
								auto suma1{ 0.0 };
								auto suma2{ 0.0 };
								auto dziesiec{ 10.0 };
								bool przecinek = false;
								for (size_t k = 0; k < liczba1.length(); k++) {
									if (liczba1[k] == '.') {
										przecinek = true;
										continue;
									}
									if (przecinek) {
										suma1 = suma1 + (double)(liczba1[k] - '0') / dziesiec;
										dziesiec *= dziesiec;
									}
									else {
										suma1 = suma1 * dziesiec + (double)(liczba1[k] - '0');
									}
								}
								dziesiec = 10.0;
								przecinek = false;
								for (size_t k = 0; k < liczba1.length(); k++) {
									if (liczba1[k] == '.') {
										przecinek = true;
										continue;
									}
									if (przecinek) {
										suma2 = suma2 + (double)(liczba1[k] - '0') / dziesiec;
										dziesiec *= dziesiec;
									}
									else {
										suma2 = suma2 * dziesiec + (double)(liczba1[k] - '0');
									}
								}
								if (wyrazenie[size_t(i + 1)] == '+')wynik = suma1 + suma2;
								else wynik = suma1 - suma2;
								liczba1 = std::to_string(wynik);
								vector <char> wstaw;
								for (auto k = 0; k < liczba1.length() - 3; k++) {
									wstaw.push_back(liczba1[k]);
									wyrazenie.insert(wyrazenie.begin() + index_liczby[0][0] + k, wstaw[k]);
								}
							}
							else {
								auto suma1 = stoi(liczba1);
								auto suma2 = stoi(liczba2);
								if (wyrazenie[size_t(i + 1)] == '+')wynik = suma1 + suma2;
								else wynik = suma1 - suma2;
								liczba1 = std::to_string((int)wynik);
								vector <char> wstaw;
								for (auto k = 0; k < liczba1.length(); k++) {
									wstaw.push_back(liczba1[k]);
									wyrazenie.insert(wyrazenie.begin() + index_liczby[0][0] + k, wstaw[k]);
								}
							}
							i = 1;
						}
						if (wyrazenie[i] == 'x' && (wyrazenie[size_t(i + 1)] == '+' || wyrazenie[size_t(i + 1)] == '-') && wyrazenie[size_t(i + 2)] == 'x') {
							if (wyrazenie[size_t(i + 1)] == '+' && wyrazenie[size_t(i + 3) != '*']) {
								wyrazenie.erase(i, 3);
								wyrazenie.insert(i, "2x");
								i = 1;
							}
							else if (wyrazenie[size_t(i + 1)] == '-' && wyrazenie[size_t(i + 3) != '*']) {
								wyrazenie.erase(size_t(i - 1), 3);
								i = 1;
							}
						}
					}
				}
			}
		}
		return;
	}
};

void loop(); //petla glowna programu
