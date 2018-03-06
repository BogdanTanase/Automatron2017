#include "Automat.h"
#include <iostream>
#include <fstream>
using namespace std;

Automat::Automat() {
	nrF = 0;
	cout << "Vom incepe sesiune de creare a automatului \n";
	cout << "Introduceti numarul de stari: ";
	cin >> nrQ;
	Q.resize(nrQ);
	cout << "\n Introduceti starile pe rand, urmate de cate un spatiu.\n";
	cout << "-1 == initiala , 0 == intermediara , 1 == finala \n";
	for (int i = 0; i < nrQ; i++) {
		cout << "Starea q[" << i << "] : ";
		int temp;
		cin >> temp;
		Q[i].setNume(i);
		Q[i].setStare(temp);
		cout << "\n";
	}
	cout << "Introduceti numarul de cuvinte din alfabet:\n";
	cin >> nrA;
	cout << "Introduceti alfabetul in ordine:\n";
	for (int i = 0; i < nrA; i++) {
		char cuvant;
		cin >> cuvant;
		A.push_back(cuvant);
	}
	q0 = 0;
	for (int i = 0; i < nrQ; i++) {
		if ( Q[i].getStare() == 1) {
			F.push_back(i);
			nrF++;
		}
	}
    T.generare(nrA, nrQ);
	if (T.tip() == 0) {
		tipAutomat = "AFD";
	}
	else {
		tipAutomat = "AFN";
	}
	/*
	nrA = 0;
	nrF = 0;
	nrQ = 0;
	q0 = 0;*/
}
Automat::Automat(ifstream &f) {
	nrF = 0;
	f >> nrQ;
	Q.resize(nrQ);
	for (int i = 0; i < nrQ; i++) {
		int temp;
		f >> temp;
		Q[i].setNume(i);
		Q[i].setStare(temp);
	}
	f >> nrA;
	for (int i = 0; i < nrA; i++) {
		char cuvant;
		f >> cuvant;
		A.push_back(cuvant);
	}
	q0 = 0;
	for (int i = 0; i < nrQ; i++) {
		if (Q[i].getStare() == 1) {
			F.push_back(i);
			nrF++;
		}
	}
	T.generare(nrA, nrQ,f);
	if (T.tip() == 0) {
		tipAutomat = "AFD";
	}
	else {
		tipAutomat = "AFN";
	}

}
string Automat::tip() {
	return tipAutomat;
}
bool Automat::inF(int q) {
	for (int i = 0; i < nrF; i++) {
		if (F[i] == q) {
			return true;
		}
	}
	return false;
}
bool Automat::verifica(string cuvant,int q ,int pozc) {
	if (cuvant.size() == pozc ){
		if ( inF(q)==true) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		char a = cuvant[pozc];
		int poz=nrA;
		for (int i = 0; i < nrA; i++) {
			if (A[i] == a) {
				poz = i;
				break;
			}
		}
		if (poz > nrA - 1) {
			return false;
		}
		if ( T.getInt(q,poz,0) == -5 ) {
			return false;
		}
		else {
			for (int p = 0; p < T.getSize(q,poz); p++) {
				if (verifica(cuvant, T.getInt(q, poz, p),pozc+1) == true) {
					return true;
					break;
				}
			}
		}
	}
}
void Automat::afiseaza() {
	for (int i = 0; i < T.getDimQ(); i++) {
		for (int j = 0; j < T.getDimA(); j++) {
			cout << T.getInt(i, j, 0) << " ";
		}
		cout << "\n";
	}
}
void Automat::test(){
	cout << "Vector de stari finale :";
	for (int i = 0; i < nrF; i++) {
		cout << F[i];
	}
}
Stare Automat::getSt(int i) {
	return Q[i];
}
char Automat::getA(int i) {
	return A[i];
}
void Automat::toAFD() {
	vector<Stare> qExt;
	vector<vector<int>> trExt;
	int contSt = nrQ;

	trExt.resize(nrQ);
	qExt.resize(nrQ);
	for (int i = 0; i < nrQ; i++) {
		trExt[i].resize(nrA);
	}//redimensionare pe ce era

	for (int i = 0; i < nrQ; i++) {
		qExt[i]=Q[i];
		qExt[i].setTip(0);
	}//am copiat nodurile anterioare

	for (int i = 0; i <nrQ; i++) {
		for (int j = 0; j < nrA; j++) {
			if ( T.getSize(i, j) == 1) {
				if (T.getInt(i, j, 0) == -5) {
					trExt[i][j] = -5;
				}
				else {
					trExt[i][j] = T.getInt(i, j, 0);
				}
			}
			else {
				Stare tmp(contSt);
				tmp.setTip(1);
				for (int k = 0; k < T.getSize(i, j); k++) {
					tmp.addDin(T.getInt(i, j, k));
				}
				bool test = true;
				for (int l = 0; l < contSt; l++) {
					if (qExt[l] == tmp) {
						test = false;
					}
				}
				if (test == true) {
					contSt++;
					qExt.resize(contSt);
					qExt[contSt - 1] = tmp;
					trExt.resize(contSt);
					trExt[contSt - 1].resize(nrA);
					trExt[i][j] = tmp.getNume();
				}
			}
		}
	}//aplatizare noduri+lateral noduri noi

	for (int i = nrQ; i < contSt; i++) {
		for (int j = 0; j < nrA; j++) {
			Stare tmp(contSt);
			tmp.setTip(1);
			bool test = false;
			for (int k = 0; k < qExt[i].getNrDin(); k++) {
				int unde = qExt[i].getDin(k);
				if (qExt[unde].getTip() == 0) {
					if (trExt[unde][j] != -5) {
						if (qExt[trExt[unde][j]].getTip() == 0) {
							tmp.addDin(trExt[unde][j]);
							test = true;
						}
						else {
							int cat = qExt[trExt[unde][j]].getNrDin();
							for (int p = 0; p < cat; p++) {
								tmp.addDin(qExt[trExt[unde][j]].getDin(p));
								test = true;
							}
						}
					}
				}
				else {
					for (int l = 0; l < qExt[qExt[i].getDin(k)].getNrDin(); l++) {
						if (trExt[qExt[qExt[i].getDin(k)].getDin(l)][j] != -5) {
							if (qExt[trExt[qExt[qExt[i].getDin(k)].getDin(l)][j]].getTip() == 0) {
								tmp.addDin(trExt[qExt[qExt[i].getDin(k)].getDin(l)][j]);
								test = true;
							}
							else {
								int cat = qExt[trExt[qExt[qExt[i].getDin(k)].getDin(l)][j]].getNrDin();
								for (int p = 0; p < cat; p++) {
									tmp.addDin(qExt[trExt[qExt[qExt[i].getDin(k)].getDin(l)][j]].getDin(p));
									test = true;
								}
							}
						}
					}
				}
			}
			if (test == false) {
				trExt[i][j] = -5;
			}
			else {
				if (tmp.getNrDin() == 1) {
					trExt[i][j] = tmp.getDin(0);
				}
				else {
					bool ok = true;
					for (int k = 0; k < contSt; k++) {
						if (qExt[k] == tmp) {
							ok = false;
						}
					}
					if (ok == true) {
						contSt++;
						qExt.resize(contSt);
						qExt[contSt - 1] = tmp;
						trExt.resize(contSt);
						trExt[contSt - 1].resize(nrA);
						trExt[i][j] = tmp.getNume();
					}
					else {
						for (int k = 0; k < contSt; k++) {
							if (qExt[k] == tmp) {
								trExt[i][j] = k;
							}
						}
					}
				}
			}
		}
	}

	//restul de noduri noi
	for (int i = 0; i < contSt; i++) {
		for (int j = 0; j < qExt[i].getNrDin(); j++) {
			if ( inF(qExt[i].getDin(j)) == true) {
				qExt[i].setStare(1);
			}
		}
	}//avem nodurile finale...yu..hu
	ofstream out("temp.txt");
	if (out.is_open()) {
		cout << " -> Conversie efectuata cu cucces! \n";
	}
	else {
		cout << " -> $@#$%^&*^%#@!@#$%%^^ Evident ceva a mers gresit\n";
	}
	out << contSt << endl;
	for (int i = 0; i < contSt; i++) {
		out << qExt[i].getStare() << " ";
	}
	out << endl;
	out << nrA << endl;
	for (int i = 0; i <nrA; i++) {
		out << A[i] <<" ";
	}
	out << endl;
	for (int i = 0; i < contSt; i++) {
		for (int j = 0; j < nrA; j++) {
			if (trExt[i][j] == -5) {
				out << 0 << " ";
			}
			else {
				out << 1 << " " << trExt[i][j] << " ";
			}
		}
		out << endl;
	}
	
}