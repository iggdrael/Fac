#include "Kit.h"
#include "Graphe.h"
#include "Tp4.h"
int bTp4AmorceR;//ie le module a effectivement été amorcé

void Tp4AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp4AmorceR=kV;
}//Tp4AMORCER

void Tp4TESTER(int iTest){
	//teste le présent module
	Appel0(sC2("Tp4TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case 1:	break;
			default:Assert1("Tp4TESTER default",0);
		}
	Appel1(sC2("Tp4TESTER,test n°",sEnt(iTest)));
}//Tp4TESTER	

