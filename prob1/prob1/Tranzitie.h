#ifndef TRANZITIE_H
#define TRANZITIE_H
#include <vector>
#include <string>
using namespace std;
class Tranzitie {
protected:
	vector<vector<vector<int>>> matrice;
	int dimA;
	int dimQ;
public:
   void generare(int dimA, int dimQ);
   void generare(int dimA, int dimQ,ifstream &f);
   int tip(); // 0 == AFD , -1 = AFN
   int getInt(int i, int j, int k);
   int getDimQ();
   int getDimA();
   int getSize(int i, int j);
};
#endif