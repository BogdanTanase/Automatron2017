#ifndef AUTOMAT_H
#define AUTOMAT_H
#include <vector>
#include <string>
#include "Stare.h"
#include "Tranzitie.h"
using namespace std;
class Automat :public Tranzitie {
private:
	vector<Stare> Q;
	string A; // sigma1
	vector<int> F;
	Tranzitie T;
	int nrQ;
	int nrF;
	int nrA;
	int q0;
	string tipAutomat;
	
public:
	Automat();
	Automat(ifstream &f);
	string tip();
	bool inF(int q);
	bool verifica(string cuvant,int q,int poz);
	void afiseaza();
	void test();
	char getA(int);
	Stare getSt(int);
	void toAFD();
};
#endif