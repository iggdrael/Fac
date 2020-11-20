#include "Kit.h"
#include "Graphe.h"
#include "Tp5.h"
int bTp5AmorceR;//ie le module a effectivement été amorcé

void Tp5AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp5AmorceR=kV;
}//Tp5AMORCER

void Tp5TESTER(int iTest){
	//teste le présent module
	Appel0(sC2("Tp5TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case 1:	break;
			default:Assert1("Tp5TESTER default",0);
		}
	Appel1(sC2("Tp5TESTER,test n°",sEnt(iTest)));
}//Tp5TESTER	

