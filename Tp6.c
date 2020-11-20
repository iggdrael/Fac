#include "Kit.h"
#include "Graphe.h"
#include "Tp6.h"
int bTp6AmorceR;//ie le module a effectivement été amorcé

void Tp6AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp6AmorceR=kV;
}//Tp6AMORCER

void Tp6TESTER(int iTest){
	//teste le présent module
	Appel0(sC2("Tp6TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case 1:	break;
			default:Assert1("Tp6TESTER default",0);
		}
	Appel1(sC2("Tp6TESTER,test n°",sEnt(iTest)));
}//Tp6TESTER	

