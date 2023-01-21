#include "main.h"

void loop() {
	char check = 't';
	string czytaj = "";

	while (check == 't') {
		system("cls");
		std::cout << "Podaj wyrazenie:\n";
		getline(std::cin, czytaj);
		if (czytaj == "")getline(std::cin, czytaj);

		zdanie do_policzenia(czytaj);

		if (do_policzenia.checkWyrazenie()) {
			do_policzenia.simplify();
			//do_policzenia.setWyrazenie(derivative(do_policzenia.getWyrazenie()));
			std::cout << "\nWyliczona pochodna:\n" << do_policzenia.getWyrazenie();
		}
		//std::cout << do_policzenia.getWyrazenie();
		std::cout << "\n\nCzy chcesz podac nowe wyrazenie? (t/n) ";
		std::cin >> check;

		if (check == 'n' || check == 'N') break;

		check = 't';
		czytaj = "";
	}

	system("cls");
	std::cout << "Zamykanie programu...";
	_sleep(1000);
	return;
}
