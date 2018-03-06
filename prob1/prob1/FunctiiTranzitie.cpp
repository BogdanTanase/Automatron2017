#include "Tranzitie.h"
#include <iostream>
#include <fstream>
using namespace std;
 void Tranzitie::generare(int dimA, int dimQ) {
	this->dimA = dimA;
	this->dimQ = dimQ;
	int latime = dimA;
	int adacnime = dimQ ;
	matrice.resize(adacnime);
	for (int i = 0; i < adacnime; i++) {
		matrice[i].resize(latime); //pe 00 avem gol 
	}
	for (int i = 0; i < adacnime ; i++) {
		for (int j = 0; j < latime; j++) {
			int temp;
			cout << "Catre cate stari merge q[" <<i<< "] prin "<<j<<"?\n";
			cin >> temp;
			if (temp == 0) {
				matrice[i][j].push_back(-5);
			}
			else {
				cout << "Introduceti cele " << temp << "stari:\n";
				for (int k = 0; k < temp; k++) {
					int o;
					cin >> o;
					matrice[i][j].push_back(o);
				}
			}
		}
	}
}
 void Tranzitie::generare(int dimA, int dimQ, ifstream &f) {
	 this->dimA = dimA;
	 this->dimQ = dimQ;
	 int latime = dimA;
	 int adacnime = dimQ;
	 matrice.resize(adacnime);
	 for (int i = 0; i < adacnime; i++) {
		 matrice[i].resize(latime); //pe 00 avem gol 
	 }
	 for (int i = 0; i < adacnime; i++) {
		 for (int j = 0; j < latime; j++) {
			 int temp;
			 f >> temp;
			 if (temp == 0) {
				 matrice[i][j].push_back(-5);
			 }
			 else {
				 for (int k = 0; k < temp; k++) {
					 int o;
					 f >> o;
					 matrice[i][j].push_back(o);
				 }
			 }
		 }
	 }
 }
 int Tranzitie::tip() {
	 for (int i = 0; i < dimQ; i++) {
		 for (int j = 0; j < dimA; j++) {
			 if (matrice[i][j].size() > 1) {
				 return -1;
			 }
		 }
	 }
	 return 0;
 }
 int Tranzitie::getInt(int i, int j, int k) {
	 return matrice[i][j][k];
 }
 int Tranzitie::getSize(int i, int j) {
	 return matrice[i][j].size();
 }
 int Tranzitie::getDimA() {
	 return dimA;
 }
 int Tranzitie::getDimQ() {
	 return dimQ;
 }
