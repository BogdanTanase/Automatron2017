#ifndef STARE_H
#define STARE_H
#include <set>
using namespace std;
class Stare {
private:
	int nume;  //q0 q1...0 1 
	set <int> din;
	set<int>::iterator it;
	int stare; // -1 initiala , 0 intermediara , 1 finala
	int tip; // 0 simplu 1 complex
public:
	Stare();
	Stare(int);
	Stare(int, int);
	void setNume(int);
	void setStare(int);
	int getNume();
	int getStare();
	//noi
	int getNrDin();
	int getDin(int);
	void addDin(int);
	void removeDin(int);
	friend	bool operator ==(Stare,Stare);
	void operator =(Stare);
	bool isIn(int);
	int getTip();
	void setTip(int);
};
#endif