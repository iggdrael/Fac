#include "Kit.h"
#include "Graphe.h"
#include "Tp1.h"
#include "Quiz.h"
int bTp1AmorceR;//ie ce module a effectivement été amorcé

void Tp1AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp1AmorceR=kV;
}//Tp1AMORCER

void Tp1TESTER(int iTest){
	//teste le présent module
	const int kbStop=0;
	Appel0(sC2("Tp1TESTER,test n°",sEnt(iTest)));
		iTest=0;
		char *sG21="AB1BC1CD1AD1BD1AC1";
		char *sG22="AB1BC1CD1AD1DB1AC1";
		char *sK4orienteh="AB1BC1CD1AD1BD1AC1";
		char *sK4nonOrienteh="AB1BA1AC1CA1AD1DA1BC1CB1BD1DB1CD1DC1";
		char *sK5plus="AB1BA1AC1CA1AD1DA1AE1EA1BC1CB1BD1DB1BE1EB1CD1DC1CE1EC1DE1ED1EF2FG2GA3";
		Titrer(sC2b("Question",sEnt(iTest)));
		switch (iTest) {
		case  0://Dans ce TP, il faudra appeler chaque fois QuizRepondre() avec 2 paramètres:
				//	1° un graphe paramétré G(n), par exemple: "AB1BC2CD3DA4", sachant que dans ce TP1, la valeur de n sera nulle.
				//	2° une suite de questions (liste au début de Quiz.c) groupées entre virgules dans 1 chaîne de caractères.
				// G(n) est décrit comme un graphe orienté. Pour convertir G(n) en graphe non orienté, commencer la question par un signe "-".
				//		NB:les poids des arcs ne peuvent pas être nuls ——ni même commencer par un "0" (1 ne s'écrit pas 01).
				// Toute question débute par le signe éventuel, suivi du paramètre n OBLIGATOIRE, du libellé de la question, et d'un "?" facultatif:
				//		exemple: "-0qTopO?" demande un tri topologique sur G"(0), donc non orienté.
				//		le "?" final demande plus d'infos (annoncées par ">>>"): affichage du graphe généré, circuit éventuel ou points importants. 
				// Pour qFloT, la question peut être complétée par ":" et une liste de paires sommet+capacité maximale:
				//		par exemple, 0qFloT:D7E4 limite le débit du sommet D à 7 unités et celui de E à 4 unités.
				// Pour qHaM0 et qHaM1, la question peut être complétée par ":" et un entier positif ou nul:
				//		par exemple, 0qHaM1:20 limite à 20 le nombre maximum de chaînes hamiltoniennes affichables.
				// Pour qPlanR, la question doit être complétée par "R:K" où R est une suite de réductions éventuelle et K est un K5 ou un K33:
				//		par exemple, "-0qPlanR:GF:FE:ABCDE" dit que réduire par GF puis par FE réduit G(n) à un sous-graphe ABCDE de type K5.
				QuizRepondre("AB1BC2CD3DE4","0TopO?,-0qTopO?,0qCoulH?");//"0TopO,-0qTopO"
				if (kbStop) break;
		case  1:QuizRepondre(sK4orienteh,"0qStrucT0,0qStrucT1,0qStrucT2,0qPilE0,0qPilE1,0qPilE2,0qFilE0,0qFilE1,0qFilE2,0qCC,0qCFC");
				if (kbStop) break;
		case  2:QuizRepondre(sG21,"0qCircuiT,0qTopO");
					QuizRepondre(sG22,"0qCircuiT,0qTopO");
				if (kbStop) break;
		case  3:QuizRepondre(sK5plus,"-0qEuleR?,0qHaM0:100,0qHaM1:100,-0qHaM0:100,-0qHaM1:100,-0qPlanR:GF:FE:ABCDE");//ou FG:GA
				//QuizRepondre(sK5plus,"-0qEuleR?,0qHaM0:100,0qHaM1:100,-0qHaM0:100,-0qHaM1:100,-0qPlanR:ABCDE");
				//QuizRepondre(sK5plus,"-0qEuleR?,0qHaM0,0qHaM1,-0qHaM0,-0qHaM1,-0qPlanR:FE:ABCDE");
				if (kbStop) break;
		case  4:QuizRepondre(sK4nonOrienteh,"0qCircuiT?,0qPilE2");//chercher ds Graphe.c les occurrences de sCirkwi
				if (kbStop) break;
		case  5:QuizRepondre(sK4nonOrienteh,"0qBipartI?");//voir CircuitImpairExhibeR() dans Graphe.c
				break;
		default: Assert1("Tp1TESTER: switch invalide",0);
		}
	Appel1(sC2("Tp1TESTER,test n°",sEnt(iTest)));
}//Tp1TESTER	

