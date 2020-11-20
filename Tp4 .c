#include "Kit.h"
#include "Cfg.h"
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
			case 11:	bCfgLineaireAhDroite("S->aT; T->1", 1);
						CfgReconnaitre("S->aT; T->1", 1);//L11=b;break
			case 12:	//L12=mots de 2 lettres sauf le mot bb;
			case 13:	//L13=mots qui n'ont pas de a
			case 14:	//L14=mots de 3 lettres ou plus
			case 15:	//L15=mots qcq sauf le mot bb;
			case 21:	//L21=b
			case 22:	//L22=b+(a+b)(a+b)
			case 23:	//L23=a(a+).b
			case 24:	//L24=(a+).(b^n).(a+b)*, n>0;
			//Question 3: comme sur le sujet du TP4
																	break;

			default:Assert1("Tp4TESTER default",0);
		}
	Appel1(sC2("Tp4TESTER,test n°",sEnt(iTest)));
}//Tp4TESTER
