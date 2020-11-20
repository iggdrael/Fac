#include "Kit.h"
#include "Graphe.h"
#include "Quiz.h"
#include "Tp2.h"
int bTp2AmorceR;//ie le module a effectivement été amorcé
int bTp2OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp3 est actuellement alloué

#define kuSommetLiM 100
int nDistancieR[kuSommetLiM][kuSommetLiM];

void DistancierRazeR();
void MangerAuPlusVitE(graf *pgG,int nCouleur[]);

void DistancierAfficheR(char *sQuoi,int nCoteh){
	//const int kuCarat=3;//nb de caractères par élément
	const int kuInfini=kE3;//plus petite distance assimilée une distance infinie.
	int uL,uC,nDistanceMax;
	Titrer(sQuoi);
	//nDistanceMax:=plus grande distance <kuInfini
		for (nDistanceMax=0,uL=1;uL<=nCoteh;uL++)
			for (uC=1;uC<=nCoteh;uC++)
				if ( bCroitStrict(0,nDistancieR[uL][uC],kuInfini) )
					nDistanceMax=ySup(nDistanceMax,nDistancieR[uL][uC]);
	int uCarat=1+ySup(1,nLog10(nDistanceMax));
	uCarat+=bPair(uCarat);
	//d2(nDistanceMax,uCarat);
	Assert2("DistancierAfficheR",uCarat>2,bImpair(uCarat));
	ModeCaractere(+1);
		for (printf("%s",sE(2+uCarat/2)),uC=1;uC<=nCoteh|| bPrint("");uC++)
			printf("%s%s%s",sE(uCarat/2),sEnt(uC),sE(uCarat/2));
		for (uL=1;uL<=nCoteh;uL++)
			for (printf("%s:",sEnt(uL)),uC=1;uC<=nCoteh || bPrint(sC3(sE(uCarat-2),":",sEnt(uL)));uC++)
				if ( bCroitStrict(0,nDistancieR[uL][uC],kuInfini) )
					printf("%s",sEntier(nDistancieR[uL][uC],uCarat));
				else printf("%s.",sE(uCarat-1));
		for (printf("%s",sE(2+uCarat/2)),uC=1;uC<=nCoteh|| bPrint("");uC++)
			printf("%s%s%s",sE(uCarat/2),sEnt(uC),sE(uCarat/2));
	ModeCaractere(-1);
}//DistancierAfficheR

void DistancierCalculeR(graf *pgG){
	int uL,uC,bCheminer,nCheminLgBof,nComplexitehBof,nbSommet=pgG->nSommetEnTout;
	Assert1("DistancierCalculeR",nbSommet<kuSommetLiM);
	DistancierRazeR(nbSommet);
	for (uL=1;uL<=nbSommet;uL++){
		bCheminer=bGrapheCheminerCourt(pgG,uL,uL,!k1Tas,!k1Afficher,&nCheminLgBof,&nComplexitehBof);//O(S2)
		for (uC=1;uC<=nbSommet;uC++)
			nDistancieR[uL][uC]=pgG->nVal[uC];//dc défini puisque uL≤nSommet<kuCotehLiM et uC≤nSommet<kuCotehLiM
	}
}//DistancierCalculeR

void DistancierRazeR(int nbSommet){
	for (int uL=1;uL<=nbSommet;uL++)
		for (int uC=1;uC<=nbSommet;uC++)
			nDistancieR[uL][uC]=0;
}//DistancierRazeR

void MangerAuPlusVitE(graf *pgG,int nCouleur[]){
	//détermine le chemin optimal à parcourir pour manger toutes les fleurs.
	int iAfficherAuPlus,nHamiltonien,nLongueur,nbSommet=pgG->nSommetEnTout;
	Assert3("QuizMangerAuPlusVite",nbSommet<kuSommetLiM,bGrapheConnexe(pgG),bGrapheSymetrique(pgG));
	//calcule et affiche la longueur du plus court chemin hamiltonien.
		pgG->nVal[0]=kuIntegerMax;
		nHamiltonien=nGrapheHamiltonien(pgG,k1Digraphe,!k1Circulaire,iAfficherAuPlus=-1);
		if ( nHamiltonien>0 && pgG->nVal[0]<kuIntegerMax ){
			Titrer("succès");
			ModeCaractere(+1);
				//VecteurVoir("pgG->nVal",pgG->nVal,1,nbSommet);
				nLongueur=pgG->nVal[0];
				pgG->nVal[0]=nbSommet;
				printf("Le chemin optimal est: %s. Sa longueur totale vaut %s.\n",sListe(pgG->nVal,')'),sPluriel(nLongueur,"mètre"));
			ModeCaractere(-1);
		}else printf("Aucun chemin hamiltonien n'a été trouvé.\n");
}//MangerAuPlusVitE

void QuizlandGenereR(int nbSommet,float fDensiteh,int uPoidsMax){
	//Génère un graphe qui décrit le quizland, colorie ses fleurs, puis calcue le parcours qui permet de les manger par la racine au plus vite.
	const int kbVoir=0;
	int nCouleurEnTout,sX,sY;
	int nCouleur[1+nbSommet],bPris[1+nbSommet];
	graf *pgG;
	GrapheCreer(nbSommet,&pgG);
		//générer un graphe connexe aléatoire à nbSommet sommets de densité ≥ fDensiteh, avec des arcs de poids aléatoire ds [1,uPoidsMax].
			VecteurRazer(bPris,1,nbSommet);
			do{//répéter: tirer au hasard 2 sommets X et Y et ajouter l'arête (X:Y) si elle n'existe pas déjà jsq obtenir le graphe demandé
				sX=uHasard(nbSommet);
				sY=uHasard(nbSommet);
				if (sX!=sY && !bGrapheArc(pgG,sX,sY)){
					GrapheAreter0(pgG,sX,sY,gpCout,uHasard(uPoidsMax));//crée une arête (sX:sY) de poids uHasard(uPoidsMax).
					bPris[sX]=bPris[sY]=1;
				}
				//VecteurVoir("bPris",bPris,1,nbSommet);
			}while (fGrapheDensiteh(pgG,!k1Digraphe,!k1Afficher)<fDensiteh || yVecteurSomme(bPris,1,nbSommet)<nbSommet);
			Assert2("QuizLandGenereR",bGrapheConnexe(pgG),bGrapheSymetrique(pgG));
			if (0) f(fGrapheDensiteh(pgG,k1Digraphe,!k1Afficher));
			GrapheVoir00("pgG APRÈS",pgG,gpCout);//densité fDensiteh
		//colorier le champ de quizfleurs avec le plus petit nombre de couleurs
			nCouleurEnTout=nGrapheColorier(pgG,!k1Afficher);
			if (kbVoir) GrapheVoir00("pgG APRÈS coloriage",pgG,gpCout);//densité fDensiteh
			VecteurCopier(pgG->nVal,0,nbSommet,nCouleur);
			nCouleur[0]=nbSommet;
			if (kbVoir) VecteurVoir0("nCouleur",nCouleur);
			d(nCouleurEnTout);
		//calculer et afficher le distancier
			DistancierCalculeR(pgG);
			DistancierAfficheR("Distancier des sommets de même couleur",nbSommet);
		MangerAuPlusVitE(pgG,nCouleur);
	GrapheCreer(0,&pgG);
}//QuizlandGenereR

void Tp2AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp2AmorceR=kV;
	bTp2OuverT=kF;
}//Tp2AMORCER

void Tp2TESTER(int iTest){
	//teste le présent module
	const int kbStop=0;
	Appel0(sC2("Tp2TESTER,test n°",sEnt(iTest)));
	iTest=0;
	switch (iTest) {
		case 0:		QuizRepondre("AB4BC4CD7DE4EC2DG1FG4","0qCourT?,0qCourT,-0qCourT?,-0qCourT");if (kbStop) break;
		case 1:		QuizRepondre("AB4BC4CD7DE4EF2DF1FG4","0qLargE?,0qLargE,-0qLargE?,-0qLargE");if (kbStop) break;
		case 2:		QuizRepondre("AB4BC4CD7DE4EF2DF1FG4GE2","0qLonG?,0qLonG,-0qLonG?,-0qLonG");if (kbStop) break;
		case 3:		QuizlandGenereR(5,0.3,9);if (kbStop) break;
		break;
		default:	Assert1("Tp2TESTER default",0);
	}
	Appel1(sC2("Tp2TESTER,test n°",sEnt(iTest)));
}//Tp2TESTER	

