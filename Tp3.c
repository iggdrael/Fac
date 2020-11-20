#include "Kit.h"
#include "Graphe.h"
#include "Quiz.h"
#include "Tp3.h"
int bTp3AmorceR;//ie le module a effectivement été amorcé

#define kuHabitatMaX 8
int nHabitatioN[1+kuHabitatMaX][1+kuHabitatMaX];

void HabitationAfficheR(char *sQuoi,int nCoteh);
float fHabitationDistancE(int uHabitation1, int uHabitation2);
void HabitationLocaliseR(int uHabitation,int *puLigne,int *puColonne);
void HabitationPlaceR(int nHabitationEnTout);

void DagGenereR(int nbSommet,float fDensiteh,graf **ppgDag){
	//Génère un DAG non nécessrt dipôlaire de densité approximative fDensiteh contenant nbSommet sommets et des arcs tirés aléatoirt.
	Assert3("DagGenereR0",nbSommet>1,fDensiteh>=0,bCroit(0,fDensiteh,1));
	GrapheCreer(nbSommet,ppgDag);
		do{//répéter: ajouter un arc aléatoire (sX,sY) à condition qu'il n'existe pas déjà et ne crée pas de circuit
			int sX=uHasard(nbSommet);
			int sY=uHasard(nbSommet);
			if ( sX!=sY && !bGrapheArc(*ppgDag,sX,sY) ){
				GrapheArquer(*ppgDag,sX,sY);
				//d3(sX,sY,bGrapheCircuite(*ppgDag,!k1Afficher));
				if ( bGrapheCircuite(*ppgDag,!k1Afficher) )
					GrapheDesarquer(*ppgDag,sX,sY);
			}
		}while (fGrapheDensiteh(*ppgDag,k1Digraphe,!k1Afficher)<fDensiteh);
	Assert1("DagGenereR1",!bGrapheCircuite(*ppgDag,!k1Afficher) );
}//DagGenereR

void DagGenererTouT(int nbSommet,float fDensiteh,int uPoidsMax,graf **ppgDag,char sGraphe[]){
	//Génère un DAG dipôlaire de densité approximative fDensiteh contenant nbSommet sommets et des arcs tirés aléatoirt.
	Assert4("DagGenererTouT0",fDensiteh>=0,bCroit(0,fDensiteh,1),uPoidsMax>0,nbSommet>=3);//La polarisation crée 2 sommets et la…
	int sSource,sTrappe;										//…densité ds DagGenereR(nbSommet-2) est définie si nbSommet-2>1.
	DagGenereR(nbSommet-2,fDensiteh,ppgDag);
		GraphePolariser(*ppgDag,&sSource,&sTrappe);//car G n'est pas forcément connexe
		GraphePondererAleatoirement(*ppgDag,gpCout,uHasard(uPoidsMax));//gpCouleur est facultatif maintenant
		Assert1("Question14",(*ppgDag)->nSommetEnTout==nbSommet);
	const int kuChaineLgMax=kE3;
	//char sGraphe[1+kuChaineLgMax];
	GrapheChainer(*ppgDag,"",gpCout,kuChaineLgMax,sGraphe);//convertit pgG en chaîne.
}//DagGenererTouT

void HabitationAfficheR(char *sQuoi,int nCoteh){
	const int kuInfini=kE3;//plus petite distance assimilée une distance infinie.
	int uL,uC;
	Titrer(sQuoi);
	const int kuCarat=nDecit(kuInfini);//nb de caractères nécessaires pour afficher la valeur d'une case de nHabitatioN[][]
	Assert2("HabitationAfficheR",kuCarat>2,bImpair(kuCarat));
	ModeCaractere(+1);
		for (printf("%s",sE(2+kuCarat/2)),uC=1;uC<=nCoteh|| bPrint("");uC++)
			printf("%s%s%s",sE(kuCarat/2),sEnt(uC),sE(kuCarat/2));
		for (uL=1;uL<=nCoteh;uL++)
			for (printf("%s#",sEnt(uL)),uC=1;uC<=nCoteh || bPrint(sC3(sE(kuCarat-2)," ",sEnt(uL)));uC++)
				if ( bCroitStrict(0,nHabitatioN[uL][uC],kuInfini) )
					printf("%s",sEntier(nHabitatioN[uL][uC],kuCarat));
				else printf("%s.",sE(kuCarat-1));
		for (printf("%s",sE(2+kuCarat/2)),uC=1;uC<=nCoteh|| bPrint("");uC++)
			printf("%s%s%s",sE(kuCarat/2),sEnt(uC),sE(kuCarat/2));
	ModeCaractere(-1);
}//HabitationAfficheR

float fHabitationDistancE(int uHabitation1, int uHabitation2){
	int uC1,uC2,uL1,uL2;
	HabitationLocaliseR(uHabitation1,&uL1,&uC1);
	HabitationLocaliseR(uHabitation2,&uL2,&uC2);
	float fDistance=sqrt( nCarreh(uL2-uL1) + nCarreh(uC2-uC1) );
	return(fDistance);
}//fHabitationDistancE

void HabitationLocaliseR(int uHabitation,int *puLigne,int *puColonne){
	int uC,uL;
	for (*puLigne=*puColonne=0,uL=1;uL<=kuHabitatMaX;uL++)
		for (uC=1;uC<=kuHabitatMaX;uC++)
			if (nHabitatioN[uL][uC]==uHabitation){
				*puLigne=uL;
				*puColonne=uC;
			}
	Assert2("HabitationLocaliseR",*puLigne>0,*puColonne>0);
}//HabitationLocaliseR

void HabitationPlaceR(int nHabitationEnTout){
	Assert1("HabitationPlaceR",bCroit(1,nHabitationEnTout,kuHabitatMaX*kuHabitatMaX));
	int uC,uL,uM;
	//nHabitatioN[][]:=0
		for (uL=1;uL<=kuHabitatMaX;uL++)
			for (uC=1;uC<=kuHabitatMaX;uC++)
				nHabitatioN[uL][uC]=0;
	//placer nHabitationEnTout habitations ds nHabitatioN[][]
		for (uM=1;uM<=nHabitationEnTout;){
			uL=uHasard(kuHabitatMaX);
			uC=uHasard(kuHabitatMaX);
			if (!nHabitatioN[uL][uC])
				nHabitatioN[uL][uC]=uM++;
		}
	HabitationAfficheR(sC3b("Électrification des",sPluriel(nHabitationEnTout,"habitation"),"du hameau"),kuHabitatMaX);
}//HabitationPlaceR

void Tp3AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp3AmorceR=kV;
}//Tp3AMORCER

void Question1(int nbSommet,float fDensiteh,int uPoidsMax){
	graf *pgG;
	DagGenereR(nbSommet,fDensiteh,&pgG);
		GraphePondererAleatoirement(pgG,gpCout,uHasard(uPoidsMax));
	free(pgG);
}//Question1

void Question2(int nbSommet,float fDensiteh,int uPoidsMax){
	char sGraphe[kE3];
	graf *pgG;
	for (int uGraphe=1;uGraphe<=2;uGraphe++){
		DagGenererTouT(nbSommet,fDensiteh,uPoidsMax,&pgG,sGraphe);
			QuizRepondre(sGraphe,"ordo?");//-qOrdO n'est pas défini car chq arête est réprésentée par 2 arcs opposés dc un 2-circuit
		free(pgG);
	}
}//Question2

void Question3(int nbSommet,float fDensiteh,int uPoidsMax){
	char sGraphe[kE3];
	graf *pgG;
	DagGenererTouT(nbSommet,fDensiteh,uPoidsMax,&pgG,sGraphe);
		QuizRepondre(sGraphe,"qFloT?,qFloT,-qFloT?,-qFloT");
		QuizRepondre("AB1AC1AD1BE1CF1CG1DF1EH1FH1GH1","qFloT?");//flot signé
	free(pgG);
}//Question3

void Question4(int nbSommet,float fDensiteh,int uPoidsMax){
	char sGraphe[kE3];
	graf *pgG;
	for (int uGraphe=1;uGraphe<=1;uGraphe++){
		DagGenererTouT(nbSommet,fDensiteh,uPoidsMax,&pgG,sGraphe);
			QuizRepondre(sGraphe,"-qAcpMaX?");//non défini pr qAcpMaX qui est orienté 
		free(pgG);
	}
}//Question4

void Question5(int nbHabitation){
	const int kuEchelle=kE2;
	int aK,nTotal;
	graf *pgG;
	HabitationPlaceR(nbHabitation);
	GrapheCreer(nbHabitation,&pgG);
		//ajouter à pgG les arêtes du graphe complet qui décrit les distances entre les couples d'habitations
			for (int sX=1;sX<=nbHabitation;sX++)
				for (int sY=sX+1;sY<=nbHabitation;sY++)
					GrapheAreter0(pgG,sX,sY,gpCout,yArrondi(kuEchelle*fHabitationDistancE(sX,sY)));
		GrapheCouvrir(pgG,!k1Maximal,0,k1Afficher);
		//nTotal:=somme des coût des arêtes sélectionnées dans pgG->nVal et de coût pgG->nCout
			for (nTotal=0,aK=1;aK<=pgG->nArcEnTout;aK++)
				nTotal+=pgG->nVal[aK]*pgG->nCout[aK];
	GrapheCreer(0,&pgG);
	printf("Coût total du réseau électrique %s.\n",sEuro(nTotal*(1000.0/kuEchelle)+5000));
}//Question5

void Tp3TESTER(int iTest){
	//teste le présent module
	const int kbStop=1;
iTest=2;
	Appel0(sC2("Tp3TESTER,test n°",sEnt(iTest)));
		Titrer(sC2("Question n°",sEnt(iTest)));
		switch (iTest) {
		case  0://Dans ce TP, il faudra appeler chaque fois QuizRepondre() avec 2 paramètres:
				//	1° un graphe paramétré G(n), par exemple: "AB1BC2CD3DA4:AC1:BD4", les 2 derniers triplets décrivent 1'arc puis l'arête paramétrés.
				//	2° une suite de questions (liste au début de Quiz.c) groupées entre virgules dans 1 chaîne de caractères.
				// G(n) est décrit comme un graphe orienté. Pour convertir G(n) en graphe non orienté, commencer la question par un signe "-".
				//		NB:les poids des arcs ne peuvent pas être nuls ——ni même commencer par un "0" (1 ne s'écrit pas 01).
				// Toute question débute par le signe éventuel, suivi du paramètre n éventuel, du libellé de la question, et d'un "?" facultatif:
				//		exemple: "-0qTopO?" demande un tri topologique sur G"(0), donc non orienté.
				//		le "?" final demande plus d'infos (annoncées par ">>>"): affichage du graphe généré, circuit éventuel ou points importants. 
				// Pour qFloT, la question peut être complétée par ":" et une liste de paires sommet+capacité maximale:
				//		par exemple, 0qFloT:D7E4 limite le débit du sommet D à 7 unités et celui de E à 4 unités.
				// Pour qHaM0 et qHaM1, la question peut être complétée par ":" et un entier positif ou nul:
				//		par exemple, 0qHaM1:20 limite à 20 le nombre maximum de chaînes hamiltoniennes affichables.
				// Pour qPlanR, la question doit être complétée par "R:K" où R est une suite de réductions éventuelle et K est un K5 ou un K33:
				//		par exemple, "-0qPlanR:GF:FE:ABCDE" dit que réduire par GF puis par FE réduit G(n) à un sous-graphe ABCDE de type K5.
				QuizRepondre("AB1AE1AF1BC2BD2EC1EG1GC1FG1DH1CH1GH1","qFlot?,qFlot:B1?");//affiche des flots signés
				//QuizRepondre("AB1AE1AF1BC2BD2EC1EG1GC1FG1DH1CH1GH1","qFlot?,qFlot:B1C8?");//affiche des flots signés
				if (kbStop) break;
		case 1: Question1(8,0.2,9);//génère un DAG aléatoire
				if (kbStop) break;
		case 2: Question2(8,0.2,9);//génère un DAG aléatoire puis appelle qFloT
				if (kbStop) break;
		case 3: Question3(6,0.4,9);//génère un DAG aléatoire puis appelle qAcpMaX
				Question3(6,0.5,9);//génère un DAG aléatoire puis appelle qAcpMaXbreak;
				if (kbStop) break;
		case 4: Question4(6,0.4,9);//génère un DAG aléatoire puis appelle qAcpMaX
				Question4(6,0.5,9);//génère un DAG aléatoire puis appelle qAcpMaXbreak;
				if (kbStop) break;
		case 5: Question5(12);
				break;
		default: Assert1("Tp3TESTER.default",0);
	}
	Appel1(sC2("Tp3TESTER,test n°",sEnt(iTest)));
}//Tp3TESTER	

