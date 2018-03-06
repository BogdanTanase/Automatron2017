#include <iostream>
#include <fstream>
#include "Automat.h"

using namespace std;

int main() {
	ifstream f("in.txt");
	ifstream g("temp.txt");
	Automat a1(f);
	string cuvant;
	int decizie = 1;
	while (decizie != 0 ) {
		cout << " ==========================================================\n";
		cout << " | Automatron2017 v3.7 by Tanase Bogdan                   |\n";
		cout << " ==========================================================\n ";
		cout << "-> Tipul automatului inserat este:" << a1.tip() << "\n";
		cout << " -> Introduceti cuvantul ce trebuie verificat...bip Bop bup\n";
		cout << " -> ";
		cin >> cuvant;
		if (a1.verifica(cuvant, 0, 0) == true) {
			cout << "\n -> Bup bop bib ... cuvantul este bun :D \n";
		}
		else {
			cout << "\n -> ERR:404 Cuvant not found \n";
		}
		cout << " -> Doriti sa: 1-incercati alt cuvant \n";
		cout << "               2-conversie a automatului in afd\n";
		cout << "               0-exit\n";
		cin >> decizie;
		if (decizie == 2) {
			a1.toAFD();
			Automat a2(g);
			while (decizie != 0  ) {
				cout << " ==========================================================\n";
				cout << " | Automatron2017 v3.7 by Tanase Bogdan                   |\n";
				cout << " ==========================================================\n ";
				cout << "-> Tipul automatului inserat este:" << a2.tip() << "\n";
				cout << " -> Introduceti cuvantul ce trebuie verificat...bip Bop bup\n";
				cout << " -> ";
				cin >> cuvant;
				if (a2.verifica(cuvant, 0, 0) == true) {
					cout << "\n -> Bup bop bib ... cuvantul este bun :D \n";
				}
				else {
					cout << "\n -> ERR:404 Cuvant not found \n";
				}
				cout << " -> Doriti sa: 1-incercati alt cuvant \n";
				cout << "               2-back to AFN \n";
				cout << "               0-exit\n";
				cin >> decizie;
				if (decizie == 2) {
					break;
				}
			}
		}
	}

	cout << " Va mai asteptam, o zi buna! :D\n";
	return 0;
}