#include "Stare.h"
Stare::Stare() {
	nume = -2;
	stare = -2;
}
Stare::Stare(int a) {
	nume = a;
	stare = 0;
}
Stare::Stare(int a, int b) {
	nume = a;
	stare = b;
}
void Stare::setNume(int a) {
	nume = a;
}
void Stare::setStare(int a) {
	stare = a;
}
int Stare::getNume() {
	return nume;
}
int Stare::getStare() {
	return stare;
}
//noi
int Stare::getNrDin() {
	return din.size();
}
int Stare::getDin(int x) {
	for ( it = din.begin(); it!=din.end(); ++it) {
		if (x == 0) {
			return *it;
		}
		else {
			x--;
		}
	}
}
void Stare::addDin(int stare) {
	din.insert(stare);
}

bool Stare::isIn(int stare) {
	it = din.find(stare);
	if (it != din.end()) {
		return true;
	}
	return false;
}
void Stare::operator=(Stare b) {
	nume = b.nume;
	stare = b.stare;
	int t = b.getNrDin();
	for (int i = 0; i < t; i++) {
		din.insert(b.getDin(i));
	}
	tip = b.tip;
}
 bool operator ==(Stare a,Stare b) {
	 if (a.getNrDin() != b.getNrDin()) {
		 return false;
	 }
	 else {
		 if ( a.din != b.din ) {
			 return false;
		}
	 }
	return true;
}
 int Stare::getTip() {
	 return tip;
 }
 void Stare::setTip(int tip) {
	 this->tip = tip;
 }
 void Stare::removeDin(int x) {
	 din.erase(x);
 }