#include "Kit.h"
#include "Deque.h"
#include "Graphe.h"
#include "Couplage.h"
#include "Flot.h"
int aTablE[kuTableauLigneMax][kuTableauLigneMax];
//Ce module calcule un couplage maximal en temps O(S3) sur un graphe simple symétrique G (accès: pgG).
//Points pas clairs:cf ???
//L'algorithme génère des graphes G' successifs: G'(1),G'(2),etc où G'(p) est G contracté p fois, une fois par orbite créée.
//Variables de modules ——leur usage évite de créer les graphes successifs G'(i), ce qui réduit considérablt le temps d'exécution:
	int ukSommetMaX;//nombre de sommets de G,égal à pgG->nSommetEnTout, constant pendant la recherche de couplage.
	int sPseudoSommetMaX;//rang du plus grand sommet de G',égal à ukSommetMaX augmenté du nombre courant d'orbites créées.
	int alpha[kuGrapheSommetLim];//n° du 1er pseudo-sommet (dans l'ordre de formation des pseudo-sommets) ctenant sX, ou, à défaut, sX lui-même.
	int beta[kuGrapheSommetLim];//n° du 1er pseudo-sommet externe associé à sX, ou sX à défaut; il couvre sX.
	int marq[kuGrapheSommetLim];//nul si sX pair.Sinon,marq[sX]=n° vrai sommet i au bout de l'arête utilisée pr marquer k depuis j=beta[i]=beta[marq[k]]
	int couplaj[kuGrapheSommetLim];//couplaj[sX]=sY et couplaj[sY]=sX signifie que (sX,sY) est une arête du couplage; et nul si sX est non couplé.
	int s[kuGrapheSommetLim];//si k pseudo-sommet "impair",s[k]=l=vrai sommet ds k au bout de l'arête (fine) ayant permis de marquer k (pt de ctact).
							 //si k est un vrai sommet,ie beta[k]=k,on pose s[k]=k. Enfin,s[k]=0 ssi k est un pseudo-sommet pair.
	int arbralt[kuGrapheSommetLim];//ensemble Y des sommets de l'arbre alterné courant.
	int arbraltpair[kuGrapheSommetLim];//ensemble Y° des sommets pairs de l'arbre alterné courant.
	//NB Chaque sommet (vrai ou pseudo) figure au plus une fois dans une orbite et l'intersection de deux orbites qcq est vide.
	//NB Puisqu'une orbite contient au moins deux sommets, la somme "sommets + pseudo-sommets" est bornée par 3S/2 pr S sommets.
	//si k est un pseudo-sommet,couplaj[k] est le n° du vrai sommet i extrémité de l'arête du couplage incidente à k et non contenu dans k (p276).
	//un sommet est pair (resp. impair) s'il est ds l'arbre et si le chemin vers la racine (paire) a un nombre pair (resp. impair) d'arêtes.
const int kbTickeT=kF;//Le mode lent,ie sans ticket, égrène les arêtes en O(A2), vs O(S2) en mode rapide. En effet, grâce au module Ticket:
	//1° Chaque arête est scrutée au plus 2 fois. 2° La liste des sommets est initialisée en O(S2) puis accédée O(S2) fois en O(1), cf Ticket.h.
const int kbTicketVoiR=kV;
const int k1MemeSiNuL=kV;
int bAretE[kuGrapheArcLim];//dédié !kbTickeT,ie mode LENT.
int nlAreteChoiX;//cptH de cplexT, cf notO de Landau, pr cparer les performances de nAreteChoisirRapidE() et nAreteChoisirLenT() appelées selon kbTickeT 
int bCouplageAmorceR;//vrai ssi le présent module a été amorcé
void *pTickeT[kuGrapheSommetLim];//pointeurs sur les 1+pgG->nSommetEnTout listes de tickets indispensables au mode rapide (ie kbTickeT=kV)

int bCouplagePonderehOptimiseR(graf *pgG,int bMaximum,int bVoir,int bInterface[]);//O(S2A)
void CouplageCertifieR(graf *pgG);//O(A)
int bCouplageCompleT(graf *pgG);//O(S)
void CouplageCourtCircuiteR(graf *pgG);//O(A)
void CouplageSynthetiseR(graf *pgH,int bVoir);
void CouplageVoiR(char *sMessage,graf *pgG,int bMemeSiNul);
void CouplageVoiR2(char *sMessage,graf *pgG,int bMemeSiNul,int bPoids,int nPoidsMaximum);
void GrapheReduirE(graf *pgG);//O(A)
void OrbiteEclateR(graf *pgG);//O(S)
int sOrbiteEclaterUN(graf *pgG,int sOrbite);//O(S)
void OrbiteEclaterDEUX(graf *pgG,int sOrbite);//O(S)
void OrbiteEclaterTROIS(graf *pgG,int sOrbite,int sK1);//O(S)
int sSommetConfluenT(graf *pgG,int sRacine,int sIpair,int sJpair,int *pnLgDepuisIpair,int *pnLgDepuisJpair);//O(S)
void SommetConflueR(int sFourchePrim,int sIpair,int sJpair,int nEtapeMax);//O(nEtapeMax), dc O(S)
int nSommetInsatureH(graf *pgG,int *psRacine);//O(S)
int nSommetInsaturehNonMarqueH(graf *pgG);//O(S)
int bSommetMarqueH(graf *pgG,int sEnquis);//O(1)
int bSommetOrbitaL(graf *pgG,int sSommet);//O(1)
int bSommetOriginaL(graf *pgG,int sSommet);//O(1)
int bSommetPaiR(graf *pgG,int sEnquis);//O(1)
int bSommetSatureH(graf *pgG,int sEnquis);//O(1)
int sSommetSatureH(graf *pgG,int sAutreBout);//O(1)
void StructureVoiR(char *sMessage);

int wE(int N,int K,int X,int Y){
	int wE=(2*N+2-K)*X+(N-1+K)*Y;
	return(wE);
}//wE

int wCycle1(int N,int X,int Y){
	int wCycle1=2*N*X+N*Y;
	return(wCycle1);
}//wCycle1

int wCycle2(int N,int X){
	int wCycle2=4*N*X;
	return(wCycle2);
}//wCycle2

void ColonneEtudieR(int nbNiveau){
	//étudie le potentiel
	int K,X=100,Y=3*X-1;
	int N=nbNiveau;
	Appel0("ColonneEtudieR");
		d4(nbNiveau,N,X,Y);
		f(Y/(1.0*X));
		d2( wE(N,1,X,Y), wCycle1(N,X,Y) );
		d2( wE(N,1,X,Y), wE(N,2,X,Y) );
		Ligne();
		for (K=2;K<=N;K++)
			d3( K, K*wE(N,1,X,Y), wE(N,K,X,Y)+(K-1)*wCycle1(N,X,Y) );
		Ligne();
		for (K=2;K<=N;K++)
			d3( K, K*wE(N,1,X,Y), wE(N,K,X,Y)+(K-1)*wCycle2(N,X) );
	Appel1("ColonneEtudieR");
}//ColonneEtudieR

void ColonneGenereR(int nbNiveau){
	//génère la description de la colonne ds un graphe
	int nArc,sX,sY,nOffset;
	graf *pgG;
	int nbSommetLigne1=2*nbNiveau+1;
	int nbSommetLigne2=2*nbSommetLigne1-1;
	int nbSommetEnTout=2*(nbSommetLigne1+nbSommetLigne2);
	Appel0("ColonneGenereR");
		d4(nbNiveau,nbSommetLigne1,nbSommetLigne2,nbSommetEnTout);
		GrapheCreer(nbSommetEnTout,&pgG);//génère nbSommetEnTout sommets et aucun arc 
		//décrire les lignes 1 et 4
			for (nArc=0;sX=4*nArc+1,sY=sX+4,nArc<2*nbNiveau;nArc++){
				GrapheArquer(pgG,sY,sX);//ligne 1
				GrapheArquer(pgG,sX+4-1,sY+4-1);//ligne 4
			}
		//décrire les lignes 2 et 3
			for (nOffset=4*nbSommetLigne1-1,nArc=0;sX=4*nArc,sY=nOffset+2*nArc,nArc<2*nbNiveau;nArc++){
				GrapheArquer(pgG,sX+2,sY+2);//ligne 2
				GrapheArquer(pgG,sY+2,sX+2+4);//ligne 2
				GrapheArquer(pgG,sY+3,sX+3);//ligne 3
				GrapheArquer(pgG,sX+3+4,sY+3);//ligne 3
			}
		//décrire les 2-cycles qui relient les lignes 1 et 2 d'une part, et les lignes 3 et 4 d'autre part
			for (int uLigne=1;uLigne<4;uLigne+=2)
				for (nArc=0;sX=4*nArc+uLigne,nArc<=2*nbNiveau;nArc++){
					if (nArc<2*nbNiveau) GrapheArquer(pgG,sX,sX+1);
					if (nArc>0) GrapheArquer(pgG,sX+1,sX);
				}
		//décrire les 2-cycles qui relient les lignes 2 et 3
			for (nOffset=4*nbSommetLigne1+1,nArc=0;sY=nOffset+2*nArc,nArc<2*nbNiveau;nArc++){
				GrapheArquer(pgG,sY,sY+1);
				GrapheArquer(pgG,sY+1,sY);
			}
		GrapheVoir("ColonneGenereR:pgG",pgG);
	Appel1("ColonneGenereR");
}//ColonneGenereR

void CouplageAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique a priori)
	bCouplageAmorceR=kV;
}//CouplageAMORCER

void CouplageCertifieR(graf *pgG){//O(A)
	//vérifie que le couplage courant de pgG a bien du sens sachant que pgG est réputé symétrique
	const int kbAuthentifier=kF;
	int bValide;
	int aK,sX,sY;
	int nSommet[1+1][1+pgG->nSommetEnTout];
	//GrapheVoir0("CouplageCertifieR",pgG,gpCouleur);
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
		nSommet[0][sX]=nSommet[1][sX]=0;
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			if (pgG->coulh[aK]>0) {
				nSommet[sX<sY][sX]++;
				nSommet[sX<sY][sY]++;
			}
		}
	if (kbAuthentifier) VecteurVoir("CouplageAuthentifieR0",nSommet[0],1,pgG->nSommetEnTout);//O(S)
	if (kbAuthentifier) VecteurVoir("CouplageAuthentifieR1",nSommet[1],1,pgG->nSommetEnTout);//O(S)
	//bValide:=pgG est symétrique et les arêtes du couplage spécifié par "pgG->coulh[aK]>0" sont effectivement disjointes
		bValide=bGrapheSymetrique(pgG);
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
			bValide=bValide && nSommet[0][sX]<=1 && nSommet[0][sX]==nSommet[1][sX];
	Assert1("CouplageCertifieR",bValide);
}//CouplageCertifieR

int bCouplageCompleT(graf *pgG){//O(S)
	int bComplet,nCouplage=0;
	for (int sX=1;sX<=pgG->nSommetEnTout;sX++)
		if (couplaj[sX])
			nCouplage++;
	bComplet=nCouplage==pgG->nSommetEnTout;
	return(bComplet);
}//bCouplageCompleT

int bCouplageOptimiser(graf *pgG,int bPonderer,int bMaximiserSinonMinimiser,int zdAfficher){
	//pgG->sPer[]:=le cplG qui,si bPonderer,maximise/minimise la somme des nCout[] des arcs du cplG et qui,sinon,maximise le nb de sommets couplés.
	const int kbVoir=0;
	int bBiparti,bCalculable,bParfait=kF,sX,bInterface[kuGrapheSommetLim];
	if (kbVoir) Appel0("bCouplageOptimiser");
		if (!(!bPonderer || bMaximiserSinonMinimiser)) d2(bPonderer,bMaximiserSinonMinimiser);
		Assert2("CouplageOptimiser1",bCouplageAmorceR,!bPonderer || bMaximiserSinonMinimiser);
		int bSymetrique=bGrapheSymetrique(pgG);
		if (bSymetrique){
			//bInterface[sX] soit vrai ssi sX peut être relié à la source ou à la trappe du réseau de transport créé dans bCouplagePonderehOptimiseR: 
				for (sX=1;sX<=pgG->nSommetEnTout;sX++){
					bInterface[sX]=pgG->aHed[sX]>0;//tt sommet est normalt ds l'interface à moins que l'appelant n'ait explicitt négativé des sommets.
					pgG->aHed[sX]=nAbs(pgG->aHed[sX]);//positive pgG->aHed[] afin que le code qui suit puisse être exécuté.
				}
			if (zdAfficher>1)
				printf("%sSi le graphe est biparti, le calcul du couplage maximal peut se ramener à un calcul de flot maximal.\n",flag);
			bBiparti=bGrapheBiparti(pgG,yInf(0,1-zdAfficher));
			if (kbVoir) d3(bPonderer,bBiparti,bMaximiserSinonMinimiser);
			bCalculable=!bPonderer && (zdAfficher==0) || bBiparti;
			if (1) bCalculable=bPonderer && bBiparti && bGrapheSymetrique(pgG);//algos de couplage sur pgG non biparti hors L3.
			if (bCalculable){
				if (bPonderer && bBiparti){
					ModeCaractere(+1);
						bParfait=bCouplagePonderehOptimiseR(pgG,bMaximiserSinonMinimiser,zdAfficher,bInterface);//O(S2A)
					ModeCaractere(-1);
				};//O(S3)
				if (0) VecteurCopier(couplaj,1,pgG->nSommetEnTout,pgG->sPer);
			}else if (zdAfficher && !bBiparti)
				printf("\tLe calcul du couplage maximal sur un graphe non biparti %s",nada);
		}else {printf("\tLe calcul du couplage maximal sur un graphe orienté %s",nada);
			printf("%sMais le couplage maximal est parfaitement défini sur le graphe non orienté associé.\n",flag);
		}
	if (kbVoir) Appel1("bCouplageOptimiser");
	return(bParfait);
}//bCouplageOptimiser

int bCouplageParfaire(graf *pgG,int bVoir){
	//vrai ssi il existe un couplage parfait ds pgG; rend le couplage parfait éventuel à coût minimum ds pgG->sPer 
	int bParfaire=0;
	int bInterface[1+pgG->nSommetEnTout];
	if (bVoir) Appel0("bCouplageParfaire");
		Assert1("bCouplageParfaire",bGrapheBiparti(pgG,!k1Afficher));
		VecteurRazer(bInterface,1,pgG->nSommetEnTout);
		for (int sX=1;sX<=pgG->nSommetEnTout;sX++)
			bInterface[sX]=pgG->aHed[sX]>0;
		GrapheSymetriser(pgG,gpCouleur+gpCout);
		//GrapheVoir0("pgG symétrisé",pgG,gpCouleur+gpCout);
		//d(pgG->nSommetEnTout);
		bParfaire=bCouplagePonderehOptimiseR(pgG,k1Maximiser,!k1Voir,bInterface);//O(S2A)
	//couplaj[] contient un couplage de poids maximal calculé sur pgG symétQ biparti pondéré par pgG->nCout[] et tel que aHed[sX]<0 ssi sX non connctB à source ou trappe
		//d(pgG->nSommetEnTout);
		VecteurCopier(couplaj,1,pgG->nSommetEnTout,pgG->sPer);
		//VecteurVoir("couplaj",couplaj,1,pgG->nSommetEnTout);
		if (0 || bVoir) CouplageVoiR2("bCP",pgG,k1MemeSiNuL,k1Poids,0);
		//d(pgG->nSommetEnTout);
		//VecteurVoir("pgG->sPer99",pgG->sPer,1,pgG->nSommetEnTout);
		if (0) for (int sX=1;sX<=pgG->nSommetEnTout;sX++)
				if (sX<pgG->sPer[sX]) printf("Couplaje: .%d.%d.\n",sX,pgG->sPer[sX]);
	if (bVoir) Appel1("bCouplageParfaire");
	return(bParfaire);
}//bCouplageParfaire

int bCouplageParfait(graf *pgG){
	int bParfait=bCouplageOptimiser(pgG,k1Poids,k1Maximum,!k1Afficher);//appelle bCouplagePonderehOptimiseR,juste ci-dessous, car pgG est biparti.
	return(bParfait);
}//bCouplageParfait

int bCouplageParfaiT(graf *pgG,int bVoir){
	GrapheSymetriser(pgG,!k1Voir);
	if (bVoir) GrapheVoir0("pgG symétrisé",pgG,gpCout);
	int bParfait=bCouplageParfait(pgG);
	return(bParfait);
}//bCouplageParfaiT

int bCouplagePonderehOptimiseR(graf *pgG,int bMaximum,int zdAfficher,int bInterface[]){//O(S2A)
	//rend dans couplaj[] un couplage de poids maximal calculé sur pgG symétQ biparti pondéré par pgG->nCout[] et tel que aHed[sX]<0 ssi sX non connctB à source ou trappe
	int nCout,nFlotObtenu,nFlotRequis;
	int cnFlotRequis[0+1];
	graf *pgH;
	int aK,sX,sY,sSource,sTrappe,bParfait,nPoidsMax,nPoidsMaximum;
	//Appel0("bCouplagePonderehOptimiseR");
		Assert2("bCouplagePonderehOptimiseR1",bGrapheSymetrique(pgG),bGrapheBiparti(pgG,!k1Afficher));
		if (zdAfficher>1) Flag(1);
		if (zdAfficher>1) printf("%sRecherche d'un couplage de poids %s:\n",sTab0(),(bMaximum)?"maximum":"minimum");
Tabuler(+1);
		//GrapheVoir3("bCouplagePonderehOptimiseR0",pgG);
		GrapheBipartir(pgG,k1Bipartir);//négative pgG->aHed[sX] ssi sX est un sommet de la partition X.
			sSource=pgG->nSommetEnTout+1;
			sTrappe=pgG->nSommetEnTout+2;
if (zdAfficher>0)
printf("%sConstruction d'un graphe de flot dipôlaire (de la source %s à la trappe %s) à %s…\n",sTab0(),sEnt(sSource),sEnt(sTrappe),sPluriel(pgG->nSommetEnTout+2,"sommet"));
			pgH=(graf *) malloc(sizeof(graf));
			//(pgH,sSource,sTrappe,nFlotRequis):=(le réseau de transport qui englobe pgG,la source,la trappe et le flot maximal théorique admissible.
				//d2(sSource,sTrappe);
				pgH->nSommetEnTout=pgG->nSommetEnTout+2;
				//if (zdAfficher>1) printf("%sUn dipôle est créé avec une source %s et une trappe %s.\n",sTab0(),sEnt(sSource),sEnt(sTrappe));
				if (zdAfficher>1) printf("%sUn arc relie chaque sommet de X, resp. Y, à la source, resp. la trappe. Les arcs de G sont conservés.\n",sTab0());
				//if (zdAfficher>1) printf("%sLa capacité maximale des arcs vaut 1 sur les arcs incidents à %s et %s, et l'infini ailleurs.\n",sTab0(),sEnt(sSource),sEnt(sTrappe));
				if (zdAfficher>1) printf("%sLa capacité maximale vaut 1 sur tous les arcs.\n",sTab0(),sEnt(sSource),sEnt(sTrappe));
		//sd("bCouplagePonderehOptimiseR",pgH->nSommetEnTout);
				Assert1("bCouplagePonderehOptimiseR5",pgH->nSommetEnTout<kuGrapheSommetLim);
				for (sX=0;sX<=pgH->nSommetEnTout+1;sX++)
					pgH->aHed[sX]=1;
				pgH->nArcEnTout=0;
				//nPoidsMax:=poids maximum rencontré sur un arc ou un autre de pgG:
					for (nPoidsMax=0,aK=1;aK<=pgG->nArcEnTout;aK++){
						Assert1("bCouplagePonderehOptimiseR7",pgG->nCout[aK]>=0);
						//sd("pgG->nCout[aK]",pgG->nCout[aK]);
						nPoidsMax=iSup(nPoidsMax,pgG->nCout[aK]);
					}
					if (0 && zdAfficher) d(nPoidsMax);
				nPoidsMaximum=(bMaximum) ? 0: nPoidsMax;
		//d(nPoidsMax);
					//relier dans pgH les sommets de X aux sommets de Y (comme dans pgG) 
				if (0 && zdAfficher) d(pgG->nArcEnTout);
						for (sX=1;sX<=pgG->nSommetEnTout;sX++)
							for (aK=abs(pgG->aHed[sX]);aK<abs(pgG->aHed[sX+1]);aK++){
								sY=pgG->sSuk[aK];
								if (sX<sY && pgG->aHed[sX]*pgG->aHed[sY]<0){
									nCout=(bMaximum)? pgG->nCout[aK]: nPoidsMaximum-pgG->nCout[aK];
									GrapheArquer3(pgH,sX,sY,knCapaNulle,kuCapaUnitaire,nCout);
									GrapheArquer3(pgH,sY,sX,knCapaNulle,kuCapaUnitaire,nCout);
								}
							}
					//relier sSource aux sommets de X, sTrappe à ceux de Y, et déduire le flot maximal admissible nFlotRequis:
						for (cnFlotRequis[0]=cnFlotRequis[1]=0,nCout=0,sX=1;sX<=pgG->nSommetEnTout;sX++){
							if (bInterface[sX]){
								//tee("sX,pgG->aHed[sX]<0",sX,pgG->aHed[sX]<0);
								//if (pgG->aHed[sX]>0) tee("sSource,sX",sSource,sX); else tee("sX,sTrappe",sX,sTrappe); 
								if (pgG->aHed[sX]>0)
									GrapheArquer3(pgH,sSource,sX,knCapaNulle,kuCapaUnitaire,nCout);
								else GrapheArquer3(pgH,sX,sTrappe,knCapaNulle,kuCapaUnitaire,nCout);
								cnFlotRequis[pgG->aHed[sX]>0]++;
							}
						}
						//d2(cnFlotRequis[0],cnFlotRequis[1]);
						nFlotRequis=iInf(cnFlotRequis[0],cnFlotRequis[1]);
				if (0 && zdAfficher) d(pgH->nArcEnTout);
		//sd("bCouplagePonderehOptimiseR",pgH->nArcEnTout);
		//printf("Arcs/Sommets: %s.\n",sRatio(pgH->nArcEnTout,pgH->nSommetEnTout));
				//NB ne pas symétriser pgH: la source doit rester une source et la trappe doit rester une trappe.
				GrapheInverser(pgH);
				if (!bMaximum)
					printf("Chaque poids P est remplacé ci-dessous par %d-P afin de maximiser plutôt que de minimiser.\n",nPoidsMaximum); 
//bVoir=kV;
				if (0)
					GrapheVoir3(sC2b("Réseau de transport conçu pour acheminer jusqu'à",sPluriel(nFlotRequis,"unité$ de flot")),pgH);
				if (zdAfficher>1){
					Tabuler(+1);
						GrapheVoir0(sC2(flag,"Graphe pour la recherche du couplage maximal"),pgH,gpCapaMax);
					Tabuler(-1);
				}
			Assert1("bCouplagePonderehOptimiseR45",bGrapheSimple(pgH));
if (0 && zdAfficher) t("Calcul du flot optimal..");
			nFlotObtenu=nFlotMaxCalculer(pgH,sSource,sTrappe,nFlotRequis,-zdAfficher,!k1Preciser);//O(S2A)
if (0 && zdAfficher) t("Mémorisation du couplage..");
			//sd("***************nFlotObtenu",nFlotObtenu);
			//couplaj[]:=arcs de pgG qui ont un flot non nul
				Assert3("bCouplagePonderehOptimiseR8",pgH->nSommetEnTout==pgG->nSommetEnTout+2,sSource==pgG->nSommetEnTout+1,sTrappe==pgG->nSommetEnTout+2);
				if (0 && zdAfficher) sd("pgG->nSommetEnTout",pgG->nSommetEnTout);
				CouplageSynthetiseR(pgH,zdAfficher);
			bParfait=(nFlotObtenu==nFlotRequis);
			//zdAfficher=kV;
			if (0 && zdAfficher)
				printf("Le couplage obtenu %s maximal: %d/%d.\n",sEst(bParfait),nFlotObtenu,nFlotRequis);
			if (0 && zdAfficher)
				CouplageVoiR2(sC2b("dans le couplage de poids",sChoix(bMaximum,"maximal","minimal")),pgH,k1MemeSiNuL,k1Poids,nPoidsMaximum);
		free(pgH);
		GrapheBipartir(pgG,!k1Bipartir);//dénégative pgG->aHed[]
Tabuler(-1);
		if (zdAfficher>1) Flag(0);
	//Appel1("bCouplagePonderehOptimiseR");
	return(bParfait);
}//bCouplagePonderehOptimiseR

void CouplageSynthetiseR(graf *pgH,int bVoir){//O(A)
	//Appel0("CouplageSynthetiseR");
	int nCouplage,nCouplageEnTout,aK,aL,sX,sY;
	//aTablE[sX][sY]:=index aK de l'arc (sX,sY)
		for (sX=1;sX<=pgH->nSommetEnTout;sX++)//O(A)
			for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++)
				aTablE[sX][sY=pgH->sSuk[aK]]=aK;
	//affecter couplaj[] efficact grâce à sTable et calculer nCouplageEnTout 
		for (VecteurRazer(couplaj,1,pgH->nSommetEnTout),nCouplageEnTout=0,sX=1;sX<=pgH->nSommetEnTout;sX++)//O(A)
			for (aK=pgH->aHed[sX];sY=pgH->sSuk[aK],aK<pgH->aHed[sX+1];aK++)
				if (sX<sY && bCroit(1,sX,pgH->nSommetEnTout-2) && bCroit(1,sY,pgH->nSommetEnTout-2)){
					aL=aTablE[sY][sX];
					Assert2("CouplageSynthetiseR2",pgH->nPhi[aK]<=1,pgH->nPhi[aL]<=1);//car solutO de pb de flot unitR
					if (pgH->nPhi[aK]!=pgH->nPhi[aL]){//car le bilan de 2 flux unitR sur 2 arcs tête-bêche est nul
						nCouplageEnTout++;
						Assert2("CouplageSynthetiseR2",couplaj[sY]==0,couplaj[sX]==0);
						couplaj[sY]=sX;couplaj[sX]=sY;
					}
				}
	if (bVoir){//afficher les nCouplageEnTout couplages
		ModeCaractere(+1);
			for (printf("\tLe couplage maximal a %s: {",sPluriel(nCouplageEnTout,"arête")),nCouplage=0,sX=1;sX<=pgH->nSommetEnTout || bPrint("}.");sX++)//O(A)
				for (aK=pgH->aHed[sX];sY=pgH->sSuk[aK],aK<pgH->aHed[sX+1];aK++)
					if (sX<sY && bCroit(1,sX,pgH->nSommetEnTout-2) && bCroit(1,sY,pgH->nSommetEnTout-2)){
						aL=aTablE[sY][sX];
						if (pgH->nPhi[aK]!=pgH->nPhi[aL])//car le bilan de 2 flux unitR sur 2 arcs tête-bêche est nul
							printf("%s%s",sCouple(sX,sY),(++nCouplage<nCouplageEnTout)?",":"");
					}
		ModeCaractere(-1);
	}
	//Appel1("CouplageSynthetiseR");
}//CouplageSynthetiseR

void CouplageTESTER(int iTest){
	//teste le présent module;La couleur associée à chaque arête vaut 1 si elle fait partie du couplage initial. Sinon,elle vaut 0.
	char kcBrexitt[]="AC0AF0AH0BD0BF0BJ0CE0CI0DG0DI0EF0EH0FG0GJ0HI0IJ0";
	char kcDeltoide[]="AB0AW0AX0BC0BJ0CD0CR0DE0DL0EF0EM0FG5GZ0HI0HP0HZ0IJ0IQ0JK0KL0KS0LM0MY0NO5NY0OP0PQ0QR0RS0ST0TW0TX0UV5UY0VZ0";
	char kcDomino1[]="AB0AD0BC0BE0CF0DE0EF0";//couplage initial vide
	char kcDomino2[]="AB0AD0BC1BE0CF0DE1EF0";//couplage initial: BC et DE
	char kcComplet4[]="AB0AC0AD0BC0BD0CD0";
	char kcComplet5[]="AB0AC0AD0AE0BC0BD0BE0CD0CE0DE0";
	char kcFaible[]="AB0AC0AG0AI0BC0BH0CD0DE0DI0EF0FG0GH0HI0";
	char kcGlobe[]="AB0AU0AV0BC0BJ0CD0DE0DQ0EF0EP0FG5GX0HI0HX0IJ0JK0KL0KS0LM0MW0NO5NW0OP0PQ0QR0RS0ST0TU0TV0UV0UY0VZ0Wa0Xb0";
	char kcHerschel[]="AC0AE0AF0BC0BG0BE0CH0CI0DH0DK0DI0DJ0EJ0EK0FH0FJ0GI0GK0";
	char kcHerschelFaux[]="AE0AI0BG0BK0CE0CH0DH0DK0EF0FG0FH0HJ0IJ0JK0";
	char kcLongrine8[]="AE0BG0CK0DI0EF0FB0FI1GH0HA0HK1IJ0JC0KL0LD0";
	char kcLongrine10[]="AE0BG0CM1DJ1EF0FB1GH0HI0IA2IM3FJ3JK0KL0LC0MN0ND0";
	char kcK221[]="AC1AD1BC1BD1";
	char kcK222[]="AC2AD1BC1BD1";
	char kcMutex[]="AC1BD1CF1DF1EA1EB1";//hexagone avec E en haut et F en bas 
	char kcPapillon[]="AB1AM1BC2BM1CD3CJ2DE4DI3EF4FD4FE4GH5HG5HI5IC3IG5JB2JK6LJ6KL6LK6MA1";
	int nOrdre,bParfait,nParfait,bMaximum=k1Maximum,bPonderer=k1Poids,bSymetriser=kV;
	graf *pgG;
	enum grType GrapheType;
	Assert1("CouplageTESTER",bCouplageAmorceR);
	iTest=60;//70 20 30
	Appel0(sC2("CouplageTESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case  0:	Titrer("kcFigure8aPage272 alias grOmega");
						GrapheCreer1(&pgG,grOmega,0,k1Creer);//Gondran et Minoux Eyrolles 37
						bPonderer=kF;
						break;
			case  1:	Titrer("kcDomino1");
						bGrapheGenerer(kcDomino1,gpCouleur,&pgG);
						break;
			case  2:	Titrer("kcDomino2");
						bGrapheGenerer(kcDomino2,gpCouleur,&pgG);
						break;
			case  3:	Titrer("kcComplet4");
						bGrapheGenerer(kcComplet4,gpCouleur,&pgG);
						break;
			case  4:	Titrer("kcComplet5");
						bGrapheGenerer(kcComplet5,gpCouleur,&pgG);
						break;
			case  6:	Titrer("kcFaible");
						bGrapheGenerer(kcFaible,gpCouleur,&pgG);
						break;
			case  5:	Titrer("kcHerschelFaux");
						bGrapheGenerer(kcHerschelFaux,gpCouleur,&pgG);
						break;
			case  7:	Titrer("kcHerschel");
						bGrapheGenerer(kcHerschel,gpCouleur,&pgG);//impair, dc reste 1 sommet non couplé
						break;
			case  8:	Titrer("kcBrexitt");
						bGrapheGenerer(kcBrexitt,gpCouleur,&pgG);
						break;
			case  9:	Titrer("kcDeltoide");
						bGrapheGenerer(kcDeltoide,gpCouleur,&pgG);
						break;
			case 10:	Titrer("kcGlobe");
						bGrapheGenerer(kcGlobe,gpCouleur,&pgG);
						break;
			case 11:	Titrer("kcK221");
						bGrapheGenerer(kcK221,gpCouleur,&pgG);
						VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);
						break;
			case 12:	Titrer("kcK222");
						bGrapheGenerer(kcK222,gpCouleur,&pgG);
						VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);
						break;
			case 13:	Titrer("kcPapillon");
						bGrapheGenerer(kcPapillon,gpCouleur,&pgG);
						VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);
						bPonderer=k1Ponderer;
						bSymetriser=kF;
						break;
			case 20:	Titrer("kcDomino1");
						bGrapheGenerer(kcDomino1,gpCouleur,&pgG);
						//GrapheSymetriser(pgG,!k1Voir);SURTOUT PAS pr nCouplageParfaitListeR (redondance ds les comptages)
						//GrapheArquer(pgG,3,2);
						GraphePonderer0(pgG,3);
						GrapheVoir0("pgG",pgG,gpCout);
						Assert1("CouplageTESTER20",nParfait==3);
						bParfait=bCouplageParfaiT(pgG,k1Voir);
						printf("Le couplage %s parfait.\n",sEst(bParfait));
						break;
			case 30:	Titrer("kcLongrine8");
						bGrapheGenerer(kcLongrine8,gpCouleur,&pgG);
						VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);
						GrapheVoir0("pgG",pgG,gpCout);
						Assert1("CouplageTESTER30",nParfait==5);
						printf("Le couplage %s parfait.\n",sEst(bParfait));
						break;
			case 40:	Titrer("kcLongrine10");
						bGrapheGenerer(kcLongrine10,gpCouleur,&pgG);
						GraphePonderer0(pgG,1);//tous les arcs
						GraphePonderer(pgG,6,10,gpCout,3);//arc (6,10) de poids 3
						GraphePonderer(pgG,9,13,gpCout,4);
						GrapheVoir0("pgG",pgG,gpCout);
						Assert1("CouplageTESTER40",nParfait==2);
						break;
			case 50:	Titrer("kcMutex");
						bGrapheGenerer(kcMutex,gpCouleur,&pgG);
						GraphePonderer0(pgG,1);//tous les arcs
						GrapheVoir0("pgG",pgG,gpCout);
						Assert1("CouplageTESTER50",nParfait==2);
						break;
			case 60:	Titrer("Couplage de graphes extraits de la collection grGraphe");
						printf("      NB: Choix des arêtes en mode %s, %s %s.\n\n",(kbTickeT)?  "RAPIDE": "LENT","donc",sAvec(kbTickeT,"le module Ticket"));
						for (int uG=grAlpha+1;uG<grOmega;uG++){
							Titrer(sC3("Graphe ",sGraphe(uG),":"));
							nOrdre=5*bDans5(uG,grC,grD,grK,grP,grS);
							GrapheCreer1(&pgG,uG,nOrdre,k1Creer);
								GrapheVoir("",pgG);
								VecteurRazer(pgG->coulh,1,pgG->nArcEnTout);
								GrapheSymetriser(pgG,gpCouleur+gpCout);
							GrapheCreer1(&pgG,uG,0,!k1Creer);
							//Ligne();
						}
						break;
			case 70:	Titrer("Membrane");
						ColonneGenereR(4);
						ColonneEtudieR(4);
						break;
			default:	Assert1("CouplageTESTER",0);
		}
		if (iTest<20){
			GrapheVoir1("Graphe généré avant symétrisation",pgG,kV);
			if (bSymetriser)
				GrapheSymetriser(pgG,gpCouleur+gpCout);
			GrapheVoir(sC3b("Graphe généré",sChoix(bSymetriser,"APRES","SANS"),"symétrisation"),pgG);
			//GrapheVoir1(kV,"Graphe généré après symétrisation",pgG);
			bCouplageOptimiser(pgG,bPonderer,bMaximum,!k1Afficher);
		}
	Appel1(sC2("CouplageTESTER,test n°",sEnt(iTest)));
}//CouplageTESTER	

void CouplageVoiR(char *sMessage,graf *pgG,int bMemeSiNul){
	//affiche la liste de arêtes qui appartiennent au couplage courant de pgG
	const int knPoidsMaximumNul=0;
	CouplageVoiR2(sMessage,pgG,bMemeSiNul,knPoidsNul,knPoidsMaximumNul);
}//CouplageVoiR	

void CouplageVoiR2(char *sMessage,graf *pgG,int bMemeSiNul,int bPoids,int nPoidsMaximum){
	//affiche la liste de arêtes (avec leurs pondérations ssi bPoids) qui appartiennent au couplage courant de pgG
	int aK,sX,sY;
	int nCouple=0,cPasse,nPoids,nPoidsTotal,bPointer;
	//Appel0("CouplageVoiR2");
		for (bPointer=nPoidsTotal=nCouple=0,cPasse=0;cPasse<=1;cPasse++){
			for (sX=1;sX<=pgG->nSommetEnTout;sX++){
				//d(sX);
				if ( bSommetSatureH(pgG,sX) )
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
						sY=pgG->sSuk[aK];
						//d(sY);
						nPoids=(nPoidsMaximum>0)? nPoidsMaximum-pgG->nCout[aK]: pgG->nCout[aK];
						if ( sX<sY && couplaj[sY]==sX ){
							
							if (cPasse==0){
								nCouple++;
								nPoidsTotal+=nPoids;
							}else {printf(" %s",(bPoids)? sTriplet(sX,sY,nPoids): sCouple(sX,sY));bPointer=kV;}
						}
					}//for aK
			}
			if (!cPasse){
				if (!nCouple){
					if (bMemeSiNul)
						{printf("Aucun %s à afficher %s",(bPoids)? "triplet": "couple",sMessage);bPointer=kV;}
				}else {printf("      %s %s:",sPluriel(nCouple,(bPoids)? "triplet": "couple"),sMessage);bPointer=kV;}
			}
		}
		//printf("%sPoids total: %d%s%s",(bPointer)? ". ":"",nPoidsTotal,(!bPointer)? ". ":"",(bMemeSiNul || nCouple>0)? ".\n": "");
		printf("%s",(bMemeSiNul || nCouple>0)? ".\n": "");
	//Appel1("CouplageVoiR2");
}//CouplageVoiR2	

void GrapheReduirE(graf *pgG){//O(A)
	//supprime virtuellt ts les sommets du couplage et ts les sommets de degré libre nul
	const int bVoir=kF;
	int aK,sX,sY,nOccurrence0,nOccurrence1;
	int nDegreh[1+pgG->nSommetEnTout];
	int nIndex[1+pgG->nSommetEnTout];
	if (bVoir) Appel0("GrapheReduirE");
		//t("      RÉDUCTION du graphe et POURSUITE");
		VecteurIndexer(nIndex,1,pgG->nSommetEnTout);
		if (bVoir) VecteurVoir("nIndex         ",nIndex,1,pgG->nSommetEnTout);
		if (bVoir) VecteurVoir("couplaj   AVANT",couplaj,1,pgG->nSommetEnTout);
		if (bVoir) VecteurVoir("pgG->sPer AVANT",pgG->sPer,1,pgG->nSommetEnTout);
		nOccurrence0=nVecteurOccurrence(0,pgG->sPer,1,pgG->nSommetEnTout);
//NB on peut fare mieux en calculant 1 fois pr toutes les degrés et en décrémentant ceux-ci à chaq nouveau couplage
		//supprimer virtuellt ts les sommets du couplage
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				if (couplaj[sX])
					pgG->sPer[sX]=0;
		//nDegreh[sX]:= degré libbre de sX
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				for (nDegreh[sX]=0,aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					if (sY=pgG->sSuk[aK],pgG->sPer[sY])
						nDegreh[sX]++;
		//supprimer virtuellt ts les sommets isolés au sens de nDegreh[]
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				if (nDegreh[sX]==0)
					pgG->sPer[sX]=0;
		if (bVoir) VecteurVoir("pgG->sPer APRES",pgG->sPer,1,pgG->nSommetEnTout);
		nOccurrence1=nVecteurOccurrence(0,pgG->sPer,1,pgG->nSommetEnTout);
		//if (bVoir) d2(nOccurrence0,nOccurrence1);
		Assert1("GrapheReduirE1",nOccurrence1>nOccurrence0);//dc le volume du graphe diminue strictement
	if (bVoir) Appel1("GrapheReduirE");
}//GrapheReduirE

void OrbiteEclateR(graf *pgG){//O(S) car les orbites sont disjointes, la somme de leurs nb de sommets ne peut excéder S
	int sK1,sOrbite;
	for (sOrbite=sPseudoSommetMaX;sOrbite>pgG->nSommetEnTout;sOrbite--){//∑ O(3o) où o est la taille de l'orbite courante
		sK1=sOrbiteEclaterUN(pgG,sOrbite);//O(o) où o est la taille de l'orbite courante en nb de sommets
		if (marq[sK1]!=0)
			OrbiteEclaterDEUX(pgG,sOrbite);//O(o) où o est la taille de l'orbite courante en nb de sommets
		else ;//le couplage sur G' est cpatible avec le couplage de l'orbite.
		OrbiteEclaterTROIS(pgG,sOrbite,sK1);//O(o) où o est la taille de l'orbite courante en nb de sommets
		//sPseudoSommetMaX--;superflu puisque ArbreAlternehEnracineR réinitialisera sPseudoSommetMaX à pgG->nSommetEnTout
		//StructureVoiR(sC2b("après éclatement de l'orbite",sEnt(sOrbite)));
	}
}//OrbiteEclateR

int sOrbiteEclaterUN(graf *pgG,int sOrbite){//O(S)
	//vérifie la cpatBT du cplG sur G' avec le couplG de sOrbite et rend sExtremiteh1, extrémité ds l'orbite sOrbite de l'arête du cplG de G'.
	int sExtremiteh0,sExtremiteh1;
	//Appel0("sOrbiteEclaterUN");
		Assert1("sOrbiteEclaterUN1",bSommetOrbitaL(pgG,sOrbite));//O(1)
		sExtremiteh0=couplaj[sOrbite];
		//sExtremiteh1 soit l'extrémité de l'arête du couplG de G' ds l'orbite de nom sOrbite.
			sExtremiteh1=couplaj[sExtremiteh0];
			While(pgG->nSommetEnTout);
			while (bWhile("sOrbiteEclaterUN 3",alpha[sExtremiteh1]!=sOrbite))
				sExtremiteh1=alpha[sExtremiteh1];
		//printf("Extrémité de l'orbite %d: le sommet %d.\n",sOrbite,sExtremiteh1);
	//Appel1("sOrbiteEclaterUN");
	return(sExtremiteh1);
}//sOrbiteEclaterUN

void OrbiteEclaterDEUX(graf *pgG,int sOrbite){//O(S)
	//modifie alpha et beta pour revenir à la plus récente situation antérieure à la création de l'orbite sOrbite.
	int sJ,sJ1,sJ2,sJ3,sJ4;
	const int kuA=1,kuB=2,kuC=3;
	int bOrbite,nEtat,nTour;
	//Appel0("OrbiteEclaterDEUX");
		Assert1("OrbiteEclaterDEUX",bSommetOrbitaL(pgG,sOrbite));//O(1)
		//alpha soit actualisé
			for (sJ=1;sJ<=sPseudoSommetMaX;sJ++)//O(S)
				if (alpha[sJ]==sOrbite)
					alpha[sJ]=sJ;
		if (0)
			{VecteurVoir("alpha",alpha,1,sPseudoSommetMaX);VecteurVoir(" beta",beta,1,sPseudoSommetMaX);}
		//beta soit actualisé
			for (nTour=0,sJ=1;sJ<=pgG->nSommetEnTout;nTour++,sJ++){//O(S)
				bOrbite=beta[sJ]==sOrbite;
				//Assert1("OrbiteEclaterDEUX",bOrbite);
				if (bOrbite){
					sJ1=sJ;
					While(pgG->nSommetEnTout);
					do{
						nTour++;
						nEtat=kuA;
						sJ2=alpha[sJ1];
						if (sJ2!=sJ1){
							if (beta[sJ2]!=sOrbite)
								nEtat=kuB;
							else sJ1=sJ2;
						}else nEtat=kuC;
					}while ( bWhile("OrbiteEclaterDEUX 1",nEtat==kuA) );
					if (nEtat==kuC) {
						beta[sJ2]=sJ2;
						sJ3=sJ2;
					}else {
						sJ3=sJ1;
						beta[sJ3]=beta[sJ2];
					}
					sJ4=sJ;
				}
				While(pgG->nSommetEnTout);
				while (bWhile("OrbiteEclaterDEUX 2",sJ4!=sJ3)){
					nTour++;
					beta[sJ4]=beta[sJ3];
					sJ4=alpha[sJ4];
				}
			}//for
			Assert1("OrbiteEclaterDEUX 3",nTour<=(5*pgG->nSommetEnTout)/2);
		//beta soit actualisé
			/*for(sJ=1;sJ<=pgG->nSommetEnTout;sJ++){
				bOrbite=beta[sJ]==sOrbite;
				//Assert1("OrbiteEclaterDEUX",bOrbite);
				if (bOrbite)
					sJ1=sJ;
				else goto D;
			A:	sJ2=alpha[sJ1];
				if (sJ2==sJ1){
					beta[sJ2]=sJ2;
					sJ3=sJ2;
					goto C;
				}else {
					if (beta[sJ2]!=sOrbite)
						goto B;
					else sJ1=sJ2; goto A;
				}
			B:	sJ3=sJ1;
				beta[sJ3]=beta[sJ2];
			C:	sJ4=sJ;
			D: if (sJ4!=sJ3){
					beta[sJ4]=beta[sJ3];
					sJ4=alpha[sJ4];
					goto D;
				}
			}*/
	//Appel1("OrbiteEclaterDEUX");
}//OrbiteEclaterDEUX

void OrbiteEclaterTROIS(graf *pgG,int sOrbite,int sK1){//O(S)
	//change le couplage et les marques sur la chaîne paire entre sK1 et l'ancienne racine de l'orbite sOrbite
	int sK0,sK2,sKprim2,sK3,sKprim3,sK4,sKprim4,sK5;
	int sL,sLprim,sL1;
	int bPoursuivre;
	//Appel0("OrbiteEclaterTROIS");
	Assert1("OrbiteEclaterTROIS",bSommetOrbitaL(pgG,sOrbite));//O(1)
		sL=marq[sK1];sLprim=beta[sL];sL1=s[sK1];sK0=couplaj[sOrbite];
		sKprim2=sK1;
		While(pgG->nSommetEnTout);
		do{
			sK3=couplaj[sKprim2];marq[sKprim2]=sK3;couplaj[sKprim2]=sK0;
			sKprim3=beta[sK3];sK4=marq[sKprim3];sKprim4=beta[sK4];
			sK2=couplaj[sKprim3];s[sKprim2]=sK2;
			if (sKprim2==sK1){
				s[sKprim2]=0;
			}
			marq[sKprim3]=sK2;couplaj[sKprim3]=sK4;sK5=s[sKprim3];//ligne entière ici ou dans le if qui précède ???
			s[sKprim3]=sK3;
			bPoursuivre=(marq[sKprim4]!=0);
			if (bPoursuivre){
				sKprim2=sKprim4;sK0=sK5;
			}
		}while (bWhile("OrbiteEclaterTROIS",bPoursuivre));
		/*if (marq[sKprim4]==0) goto B;
		else sKprim2=sKprim4;sK0=sK5;goto A;*/
	/*B:*/	marq[sK1]=0;
		couplaj[sKprim4]=sK5;
	//Appel1("OrbiteEclaterTROIS");
}//OrbiteEclaterTROIS

int sSommetConfluenT(graf *pgG,int sRacine,int sIpair,int sJpair,int *pnLgDepuisIpair,int *pnLgDepuisJpair){//O(pgG->nSommetEnTout)
	int sConfluent,sImpair,sPair,sRacinePrim;
	int sIprim,sJprim;
	int bDito,bRacine,nEtape;
	//Deux chaines alternées relient sIprim d'une part et sJprim d'autre part à la racine sRacinePrim=beta[sRacinePaire].
	//ces chaines alternées ont un premier pseudo-sommet commun sConfluent dans G'. On remonte simultanément les deux chaînes alternées.
	//Le premier sommet rencontré pour la deuxième fois est nécessairement sConfluent.
	Assert3("sSommetConfluenT0",bSommetPaiR(pgG,sRacine),bSommetPaiR(pgG,sIpair),bSommetPaiR(pgG,sJpair));
	sIprim=beta[sIpair];
	sJprim=beta[sJpair];
	sRacinePrim=beta[sRacine];
	sConfluent=0;//d
	DequeAllouer(sPseudoSommetMaX);
		//confluer depuis sIprim vers la racine sachant que précédent(sPair)=beta[marq[sImpair]] et précédent(sImpair)=beta[couplaj[sPair]]:
			sPair=sIprim;
			do{
				//sd("sPair empilé",sPair);
				DequeEmpiler(sPair);
				bRacine=(sPair==sRacinePrim);
				if (!bRacine){
					Assert1("sSommetConfluenT4",couplaj[sPair]>0);
					sImpair=beta[couplaj[sPair]];//beta[couplaj] puisque sPair est pair.
					sPair=beta[marq[sImpair]];   //beta[marq] puisque sImpair est impair.
				}
			}while(!bRacine);
			*pnLgDepuisIpair=nDequeCardinal();
		//confluer depuis sJprim vers la racine sachant que précédent(sPair)=beta[marq[sImpair]] et précédent(sImpair)=beta[couplaj[sPair]]:
			sPair=sJprim;
			nEtape=0;
			do{
				//sd("sPair enquis",sPair);
				bDito=bDequeContient(sPair);
				nEtape++;
				if (!bDito){
					Assert1("sSommetConfluenT5",couplaj[sPair]>0);
					sImpair=beta[couplaj[sPair]];//beta[couplaj] puisque sPair est pair.
					sPair=beta[marq[sImpair]];   //beta[marq] puisque sImpair est impair.
				}else sConfluent=sPair;
			}while(!bDito);
			*pnLgDepuisJpair=nEtape;
	DequeAllouer(0);
	//sd("sSommetConfluenT",sConfluent);
	Assert4("sSommetConfluenT9",sConfluent>0,bSommetPaiR(pgG,sConfluent),bCroit(1,*pnLgDepuisIpair,pgG->nSommetEnTout),bCroit(1,*pnLgDepuisJpair,pgG->nSommetEnTout));
	return(sConfluent);//sConfluent est bien la copie du dernier sPair=beta[marq[sImpair]]
}//sSommetConfluenT

void SommetConflueR(int sFourchePrim,int sIpair,int sJpair,int nEtapeMax){//O(pgG->nSommetEnTout)
	//remonte dans Gprim de sIpair à sFourchePrim en actualisant alpha[],marq[],s[] et arbraltpair[]
	int sKprim1,sK1,sK2,sKprim2,sKprim3,sK4,sKprim4;
	sK1=sJpair;sKprim1=beta[sJpair];
	sK2=sIpair;sKprim2=beta[sIpair];//sK2 alias sIpair est le point de départ
	if (sKprim2!=sFourchePrim){
		While(nEtapeMax);
		do{ Assert1("SommetConflueR1",couplaj[sKprim2]>0);
//si k est un pseudo-sommet,couplaj[k] est le n° du vrai sommet i extrémité de l'arête du couplage incidente à k et non contenu dans k (p276).
			sKprim3=beta[couplaj[sKprim2]];//beta[couplaj] puisque sKprim2 est pair. Adéquat mm si sKprim2 est un pseudo-sommet, vu li-1.
			sK4=marq[sKprim3];//beta[marq] puisque sKprim3 est impair; la valeur intermédiaire sK4 permettra de progresser vers la racine.
			sKprim4=beta[sK4];
			Assert1("SommetConflueR2",sK1>0);
			//sKprim2 devient un sommet impair, vu sK1!=0.
	marq[sKprim2]=sK1;//sK1 est le vrai sommet extrémité de l'arête utilisée pour marquer sKprim2 à partir de j. j=beta[sK1]=beta[marq[k]]
				s[sKprim2]=sK2;//si k est pseudo-sommet marqué "impair",s[k]=l est le vrai sommet extrémT ds k de l'arête (fine) ayant permis de marquer k (point de contact).
			alpha[sKprim2]=alpha[sKprim3]=sPseudoSommetMaX;//sKprim2 et sKprim3 sont englobés par sPseudoSommetMaX.
			arbraltpair[sKprim3]=1;//sKprim3 change de statut:il devient pair.
			//progresser d'un pas vers la racine
				sKprim1=sKprim3;sK1=s[sKprim3];sKprim2=sKprim4;sK2=sK4;//sK2 alias sK4 est le nouveau point de départ
		} while ( bWhile("SommetConflueR while",sKprim2!=sFourchePrim) );
	}else alpha[sKprim2]=sPseudoSommetMaX;
}//SommetConflueR

int nSommetInsatureH(graf *pgG,int *psRacine){//O(S)
	int nSommetInsatureh,sX;
	for (nSommetInsatureh=0,sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
		if (!bSommetSatureH(pgG,sX) && pgG->sPer[sX]>0){//O(1)
			if (nSommetInsatureh==0)
				*psRacine=sX;
			nSommetInsatureh++;
		}
	return(nSommetInsatureh);
}//nSommetInsatureH

int nSommetInsaturehNonMarqueH(graf *pgG){//O(S)
	int nSommetInsaturehNonMarqueh,sX;
	for (nSommetInsaturehNonMarqueh=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
		if (!bSommetSatureH(pgG,sX) && !bSommetMarqueH(pgG,sX)){//O(1) et O(1)
			nSommetInsaturehNonMarqueh++;
		}
	return(nSommetInsaturehNonMarqueh);
}//nSommetInsaturehNonMarqueH

int bSommetMarqueH(graf *pgG,int sEnquis){//O(1)
	int bMarqueh=kF;
	Assert1("bSommetMarqueH",bCroit(1,sEnquis,sPseudoSommetMaX));
	bMarqueh=(arbralt[sEnquis]==1);
	return(bMarqueh);
}//bSommetMarqueH

int bSommetOrbitaL(graf *pgG,int sSommet){//O(1)
	//sommet ajout au graphe original
	int bOrbital;
	bOrbital=bCroit(pgG->nSommetEnTout+1,sSommet,sPseudoSommetMaX);
	return(bOrbital);
}//bSommetOrbitaL

int bSommetOriginaL(graf *pgG,int sSommet){//O(1)
	//sommet du graphe original
	int bVrai;
	bVrai=bCroit(1,sSommet,pgG->nSommetEnTout);
	return(bVrai);
}//bSommetOriginaL

int bSommetPaiR(graf *pgG,int sEnquis){//O(1)
	//sEnquis est dans arbraltpair
	if (!bCroit(1,sEnquis,sPseudoSommetMaX))
		sd("Dans bSommetPaiR sEnquis",sEnquis);
	Assert1("bSommetPaiR",bCroit(1,sEnquis,sPseudoSommetMaX));
	int bPair=(arbralt[sEnquis]==1) && (arbraltpair[sEnquis]==1);
	return(bPair);
}//bSommetPaiR

int bSommetSatureH(graf *pgG,int sEnquis){//O(1)
	//sEnquis est bien un sommet de pgG situé à une extrémité d'une arête du couplage
	int bSatureh;
	if (!bCroit(1,sEnquis,pgG->nSommetEnTout))
		sd("bSommetSatureH:sEnquis",sEnquis);
	Assert1("bSommetSatureH",bCroit(1,sEnquis,pgG->nSommetEnTout));
	bSatureh=couplaj[sEnquis]>0;
	return(bSatureh);
}//bSommetSatureH

int sSommetSatureH(graf *pgG,int sAutreBout){//O(1)
	//rend le sommet situé à une extrémité d'une arête du couplage autre que sAutreBout
	int sSatureh;
	Assert2("sSommetSatureH0",bCroit(1,sAutreBout,pgG->nSommetEnTout),couplaj[sAutreBout]>0);
	sSatureh=couplaj[sAutreBout];
	Assert1("sSommetSatureH1",sSatureh>0);
	return(sSatureh);
}//sSommetSatureH

void StructureVoiR(char *sMessage){
	if (1){
		t(sMessage);
		VecteurVoir("++++++ marq",marq,1,sPseudoSommetMaX);
		VecteurVoir("+++++ alpha",alpha,1,sPseudoSommetMaX);
		VecteurVoir("++++++ beta",beta,1,sPseudoSommetMaX);
		VecteurVoir("+++ couplaj",couplaj,1,sPseudoSommetMaX);
		VecteurVoir("++++ arbralt",arbralt,1,sPseudoSommetMaX);
		VecteurVoir(" arbraltpair",arbraltpair,1,sPseudoSommetMaX);
		//VecteurVoir("+++++++++ s",s,1,sPseudoSommetMaX);
	}
}//StructureVoiR

