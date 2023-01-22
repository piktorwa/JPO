// ==========================================================================
//
// In this header file is defined how to divide sentence provided by user
// and then how to calculate derivative
// 
// ==========================================================================

#pragma once


#include <iostream>
#include <string>
#include <vector>

using std::string, std::vector;
using podzielone = vector <string>;
using doZrozniczkowania = vector <bool>;

class Ladder { //klasa dzielac¹ podane wyra¿enie na mniejsze fragmenty a¿ do funkcji elementarnych, oraz ³¹cz¹ca wynik pochodnych w ci¹g znaków
private:
	podzielone divided;
	doZrozniczkowania checkToDerivative;
public:
	Ladder() {}
	virtual ~Ladder(){}
public:
	podzielone getDivided() {
		return divided;
	}
	void setDivided(podzielone result) {
		divided = result;
	}
public:	
	void dividing(string skladowa) { //funkcja dzielaca podane wyrazenie na mniejsze czesci do zrozniczkowania
		int bracket_counter{ 0 };//zmienna pilnuj¹ca nawiasy, je¿eli nie jest równa 0 to nie podzieli wyrazenia na mniejsze czesci
		size_t skladowa_index[2]{};//zmienan przechowujaca indexy wyrazenia do wyciecia
		for (int i = 0; i < skladowa.length();i++) {
			if (skladowa[i] == '(') {
				bracket_counter++;
				if (i == 0)continue;
				skladowa_index[0] = (size_t)(i + 1);
				if (i > 1) {

				}
			}
			else if (skladowa[i] == ')') {
				bracket_counter--;
				if (bracket_counter == 0 && i == skladowa.length() - 1)continue;
				if (bracket_counter == 0) {
					skladowa_index[1] = (size_t)(i - 1);
					divided.push_back(skladowa.substr(skladowa_index[0], skladowa_index[1]));
					checkToDerivative.push_back(true);
				}
			}
			else if ((skladowa[i] == '+' || skladowa[i] == '-')&&!bracket_counter) {
				skladowa_index[1] = (size_t)(i - 1);
				divided.push_back(skladowa.substr(skladowa_index[0], skladowa_index[1]));
				skladowa_index[0] = skladowa_index[1] + 2;
				checkToDerivative.push_back(true);
				divided.push_back("+");
				checkToDerivative.push_back(false);
			}
			else if (skladowa[i] == '*'&&!bracket_counter) {
				podzielone tmpString;
				doZrozniczkowania tmpBool;
				int j = i + 1;
				int liczba_mnozen{ 1 };
				int bracket_counter2{};
				skladowa_index[1] = (size_t)(i - 1);
				tmpString.push_back(skladowa.substr(skladowa_index[0], skladowa_index[1]));
				tmpBool.push_back(true);
				tmpString.push_back("*");
				tmpBool.push_back(false);
				skladowa_index[0] = skladowa_index[1] + 2;
				while (j < skladowa.length() && ((skladowa[j] != '+' && skladowa[j] != '-' && skladowa[j] != '/') && !bracket_counter2)) {
					if (skladowa[i] == '(') bracket_counter2++;
					else if (skladowa[i] == ')') bracket_counter2--;
					if (skladowa[j] == '*' && !bracket_counter2) { 
						liczba_mnozen++;
						skladowa_index[1] = (size_t)(j - 1);
						tmpString.push_back(skladowa.substr(skladowa_index[0], skladowa_index[1]));
						tmpBool.push_back(false);
						tmpString.push_back("*");
						tmpBool.push_back(false);
						skladowa_index[0] = skladowa_index[1] + 2;
					}
					j++;
				}
				if (j != skladowa.length()) {
					j--;
					if (skladowa[j] == '+' || skladowa[j] == '-' || skladowa[j] == '/') {
						tmpString.pop_back();
						tmpBool.pop_back();
					}
				}
				j = 1;
				podzielone tmp2String = tmpString;
				doZrozniczkowania tmp2Bool = tmpBool;
				while (j < liczba_mnozen) {
					tmpString.push_back("+");
					tmpBool.push_back(false);
					tmp2Bool[size_t(j - 1)] = false;
					tmp2Bool[j] = true;
					for (int k = 0; k < tmp2String.size(); k++) {
						tmpString.push_back(tmp2String[k]);
						tmpBool.push_back(tmp2Bool[k]);
					}
					j++;
				}
				for (int k = 0; k < tmpString.size(); k++) {
					divided.push_back(tmpString[k]);
					checkToDerivative.push_back(tmpBool[k]);
				}
			}
			else if (skladowa[i] == '/'&&!bracket_counter) {
				
			}
			else if (skladowa[i] == 'l'||skladowa[i] == 's' || skladowa[i] == 'c'||skladowa[i]=='t') {

			}
		}
		dividing(skladowa.substr(1,skladowa.length()-2));
		return ;
	}
	string makeString(Ladder skladowe) { //funkcja laczaca policzone fragmenty wyrazenia z powrotem w format string, a nastepnie zwracajaca ten ciag znakow.
		string result{};
		for (int i = 0; i < skladowe.divided.size(); i++)result += skladowe.divided[i];
		return result;
	}
};

class derTable :public Ladder {//klasa definiujaca sposob obliczenia pochodnej
public:
	derTable() :Ladder() {}
	~derTable(){}
public:
	podzielone derivativeIt(podzielone fragment, doZrozniczkowania check) {
		for (auto i = 0; i < fragment.size(); i++) {
			if (check[i]) {

			}
		}
		return fragment;
	}
};

string derivative(string wyrazenie);
