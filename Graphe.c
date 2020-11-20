#include "Kit.h"
#include "Erreur.h"
#include "Deque.h"
#include "Foret.h"
#include "Graphe.h"
#include "Tas.h"
#include "Abe.h"
//cheminements
enum {echAlphA,echPlusCourT,echPlusLargE,echPlusLonG,echPlusCourtEnMoyennE,echArbreCouvranT,echOmegA};
//structure de données du graphe courant G
#define kbCourtSinonLong 1
#define k1BipartiR kV
char *sGenreDePoidS="≤,capamax,≥,capamin,ç,ouleur,©,coût,ƒ,phi,π,poids,:,pondération";
enum eGrapheCouleuR CouleurType;//pr accéder aux couleurs de Kit.h (cf enum CouleurType)
const int k1PerformanceCompareR=kV;

int bGrapheAmorceR;
int bGrapheCreeR;
int bGrapheBipartiR;
int bGrapheSimplE=kV;//kV pr un graphe simple, kF pour un multigraphe

void CoutInverseR(graf *pgG);
void DijkstraAvecOuSansTasCompareR();
int bGrapheArqueR(graf *pgG,int sOrigine,int sDestination,int nCouleur);
int bGrapheAttribuT(int iAttributOuPas);
void GrapheCheminE(graf *pgG,int sSource,int sTrappe,int bCheminer,int zdAfficher,int nMesure,int gcMode);
int bGrapheCheminE(graf *pgG,int sSource,int sTrappe);
int nGrapheChemineR (graf *pgG,int sSource,int sTrappe,int zdMode,int *pnComplexiteh);
void GrapheCheminerAuLargE (graf *pgG,int bSimuler,int sSource,int sTrappe);
int nGrapheCheminerAuLargE (graf *pgG,int bSimuler,int sSource,int sTrappe);
int bGrapheCheminerCourtTaS(graf *pgG,int sSource,int sTrappe,int bCheminAfficher,int *pnComplexiteh);//O(SlgS+A)
int nGrapheCheminerTaS (graf *pgG,int sSource,int sTrappe,int *pnComplexiteh);//O(S2)
void GrapheCompletCreerPondereR(int nSommet,graf **ppgG);
int nGrapheComposanteConnexE(graf *pgG);//O(A)
void GrapheCouvriR();
void GrapheCouvrirAffichE(graf *pgG,const int kidAfficher,const int kbArbreCouvrantDePoidsMaximum,const int knPoidsTotal);
void GrapheCouvrirAfficheR(char *sAlgorithme,graf *pgG);
int bGrapheCouvrirAutremenT(graf *pgG,int bArbreCouvrantDePoidsMaximum,int idAfficher,int nPoidsTotal0);
void GrapheCouvrirAvecKruskaL(graf *pgG,int idAfficher,int bPerformanceComparer);
int nGrapheCouvrirAvecKruskaL(graf *pgG,int bArbreCouvrantDePoidsMaximum,int bLogn,int bTas,int idAfficher,int *pnComplexiteh);
int nGrapheCouvrirAvecP(graf *pgG);
void GrapheCouvrirAvecPrimOuP(graf *pgG,int bPrim,int bAfficher,int bPerformanceComparer);
int nGrapheCouvrirAvecPriM(graf *pgG,int bArbreCouvrantDePoidsMaximum,int idAfficher);
void GrapheCouvrirUniqueAvecKruskaL(graf *pgG,int bArbreCouvrantDePoidsMaximum,int idAfficher);
int bGrapheEulerienArC(graf *pgG,int aK);
void GrapheEulerierInitialiseR(graf *pgG,int bDigraphe,int bVoir,int aNext[]);
int aGrapheEulerierNextArC(graf *pgG,int bDigraphe,int sX,int aNext[]);
void GraphePondererPareiL(graf *pgG);
void GrapheQuinconceR(graf *pgG,int bBipartir);
void GrapheSymetriqueCreerPondereR(int bDense,int nSommetEnTout,int nPoidsMax,graf **ppgG);
void GrapheSymetrizer(graf *pgG);
int bGrapheVidE(graf *pgG);

void ArcEmpileR(int sX,int sY,int nCouleur,int nPoids,char sFormule[],int nPonderation[]){
	int ipF=3*nPonderation[0];
	Assert2("ArcEmpileR",bCroit(0,nCouleur,9),nPoids>=0);
	sFormule[ipF++]=cLettre(sX);sFormule[ipF++]=cLettre(sY);sFormule[ipF++]='0'+nCouleur;
	nPonderation[++nPonderation[0]]=nPoids;
	//printf("ArcEmpileR: (%c,%c,ç%c,π%d).\n",cLettre(sX),cLettre(sY),'0'+nCouleur,nPonderation[nPonderation[0]]);
}//ArcEmpileR

void DijkstraAvecOuSansTasCompareR(){
	//effectue kuMesureMax mesures sur les deux algorithmes de Dijkstra, ie versions sans tas et avec tas, et affiche les résultats des mesures.
	#define kuFacteur 10
	#define kuMesureMax 9
	graf *pgG;
	int bAfficher=k1Afficher;
	int nArc,bCheminer,uM,nSommet,nCheminLg;
	const int ksSource=1;
	const int kuTab=4;
	int nComplexitehAvecTas[1+kuMesureMax];
	int nComplexitehSansTas[1+kuMesureMax];
	for (uM=1;uM<=kuMesureMax;uM++){
		nSommet=kuFacteur*uM;
		GrapheCompletCreerPondereR(nSommet,&pgG);
			//GrapheVoir0(sC4b("Graphe à",sPluriel(nSommet,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")),pgG);
			bCheminer=bGrapheCheminerCourt(pgG,ksSource,ksSource+1,!k1Tas,bAfficher,&nCheminLg,&nComplexitehSansTas[uM]);
			bCheminer=bGrapheCheminerCourt(pgG,ksSource,ksSource+1,k1Tas,bAfficher,&nCheminLg,&nComplexitehAvecTas[uM]);
		GrapheCreer(0,&pgG);
	}
	Ligne();
	Titrer(" Tableau comparatif des algorithmes de Dijkstra \"sans tas\" vs \"avec tas\" pour les plus courts chemins ");
	Ligne();
	printf("%sGraphe complet  Temps total d'exécution T    Rapport des temps    T/pire temps théorique\n",sTab(kuTab));
	printf("%s   (S,A)          Sans tas   Avec tas        Sans tas/Avec tas     Sans tas   Avec tas  \n",sTab(kuTab));
	for (uM=1;uM<=kuMesureMax;uM++){
		nSommet=kuFacteur*uM;
		nArc=(nSommet*(nSommet-1))/2;
		printf("%s  %s%s",sTab(kuTab),sCouple(nSommet,nArc),sE(10-nChaineLg(sCouple(nSommet,nArc))));
		printf("       %5d     %5d",nComplexitehSansTas[uM],nComplexitehAvecTas[uM]);
		printf("                 %5.2f",nComplexitehSansTas[uM]/(nComplexitehAvecTas[uM]*1.0));
		printf("            %5.2f",nComplexitehSansTas[uM]/(nSommet*nSommet*1.0));
		printf("      %5.2f",nComplexitehAvecTas[uM]/(nArc+nSommet*rLn(nSommet)));
		Ligne();
	}
	Ligne();
}//DijkstraAvecOuSansTasCompareR

int bGraphe(graf *pgG){//O(A)
	//vrai ssi les champs de gG décrivent effectivement un graphe quelconque ——pr les quatre champs nSommetEnTout,nArcEnTout,aHed et sSuk de gG.
	int bGraphe,aK,sX;
	Assert1("bGraphe",bGrapheAmorceR);
	bGraphe=(pgG->nSommetEnTout>=0) && (pgG->nArcEnTout>=0) && (pgG->aHed[1]==1);
	Assert1("bGraphe2",bGraphe);
	bGraphe=bGraphe && (pgG->aHed[pgG->nSommetEnTout+1]==pgG->nArcEnTout+1);
	Assert1("bGraphe3",bGraphe);
	if (bGraphe)
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			bGraphe=bGraphe && pgG->aHed[sX]<=pgG->aHed[sX+1];
	Assert1("bGraphe4",bGraphe);
	if (bGraphe)
		for (aK=1;aK<=pgG->nArcEnTout;aK++)
			bGraphe=bGraphe && bGrapheSommet(pgG,pgG->sSuk[aK]);
	Assert1("bGraphe5",bGraphe);
	return(bGraphe);//noter qu'un graphe qui vérifie bGraphe est un multigraphe;donc ce n'est pas nécessairement un graphe simple;
}//bGraphe

char *sGraphe(int tGrapheType){
	//rend le nom du graphe de type tGrapheType;cf GrapheNom en haut du .h
	enum grType GrapheType;
	Assert1("sGraphe",bCroitStrict(grAlpha,tGrapheType,grOmega));
	char *sGraphe=sItem(GrapheNom,1+tGrapheType);
	return(sGraphe);
}//sGraphe

void GrapheAMORCER(){
	//amorce le présent module une fois pour toutes
	bGrapheAmorceR=kV;
	//tee("GrapheAMORCER:kuGrapheSommetLim,kuGrapheArcLim",kuGrapheSommetLim,kuGrapheArcLim);
	Assert2("GrapheAMORCER",bFrontiere8(kuGrapheSommetLim),bFrontiere8(kuGrapheArcLim));
}//GrapheAMORCER

void GrapheAntisymetriser(graf *pgG){//O(A)
	//antisymétrise pgG en complétant les (X,Y) par les (Y,X) manquants de coûts et de couleur opposés. Reconduit pgG->coulh[] et pgG->nCout[] sur l'arc (Y,X) manquant.
	int bVoir=0;
	int aK,sX,sY;
	Assert2("GrapheAntisymetriser",bGrapheAmorceR,bGraphe(pgG));
	GrapheSymetriser(pgG,gpCouleur+gpCout);
	if (bVoir) GrapheVoir0("pgG AVANT",pgG,gpCouleur);
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];sY=pgG->sSuk[aK],aK<pgG->aHed[sX+1];aK++)
				if (sY<sX){
					pgG->nCout[aK]=-abs(pgG->nCout[aK]);
					pgG->coulh[aK]=-abs(pgG->coulh[aK]);
				};
	if (bVoir) GrapheVoir0("pgG APRÈS",pgG,gpCouleur);
	Assert1("GrapheAntisymetriser",bGrapheSimple(pgG));
}//GrapheAntisymetriser

int nGrapheApparier(int nGenreDePoids,graf **ppgG){
	//apparie les pondérations >1 identiques; eg, en remplaçant l'arc 2 (a,b,π5) et l'arc 7 (c,d,π5) par (a,b,π-7) (c,d,π-2),ie -7 et -2 sont des index négatifs sur l'arc apparié 
	Assert1("nGrapheApparier",bGrapheAttribuT(nGenreDePoids));
	int nAppariement,aK,sX,sY,iPoids;
	int nArc[1+(*ppgG)->nArcEnTout];
	int nAlterEgo[1+(*ppgG)->nArcEnTout];
	VecteurRaz(nArc,(*ppgG)->nArcEnTout);
	VecteurRaz(nAlterEgo,(*ppgG)->nArcEnTout);
	for (nAppariement=0,aK=1;aK<=(*ppgG)->nArcEnTout;aK++){
		iPoids=iGraphePoids(*ppgG,nGenreDePoids,aK);
		if (iPoids>1)
			if (!nArc[iPoids])
				nArc[iPoids]=aK;
			else if (nArc[iPoids]>0){
				nAlterEgo[aK]=nArc[iPoids];
				nAlterEgo[nArc[iPoids]]=aK;
				nAppariement++;
		}//résultat: nAlterEgo[1..5]: 3, 0, 1, 0, 0 si la donnée est: (1,3π9)  (1,5π1)  (2,4π9)  (2,6π1)  (3,4π1).
	}
	//VecteurVoir0("nAlterEgo",nAlterEgo);
	for (sX=1;sX<=(*ppgG)->nSommetEnTout;sX++)
		for (aK=(*ppgG)->aHed[sX];aK<(*ppgG)->aHed[sX+1];aK++)
			if (nAlterEgo[aK]>0)
				GraphePonderer(*ppgG,sX,sY=(*ppgG)->sSuk[aK],nGenreDePoids,-nAlterEgo[aK]);
	return(nAppariement);
}//nGrapheApparier

int bGrapheArc(graf *pgG,int sOrigine,int sDestination){//O(S)
	//vrai ssi (sOrigine,sDestination) est un arc de gG
	int bArc=kF,aK;
	//sd3("bGrapheArc",pgG->nSommetEnTout,sOrigine,sDestination);
	Assert1("bGrapheArc",bGraphe(pgG));
	if ( bGrapheSommet(pgG,sOrigine) && bGrapheSommet(pgG,sDestination) )
		for (aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
			if (pgG->sSuk[aK]==sDestination)
				bArc=kV;//l'arc est effectivement présent dans gG
	return(bArc);
}//bGrapheArc

int nGrapheArc(graf *pgG,int sOrigine,int sDestination){//O(S)
	//si (sOrigine,sDestination) est un arc de gG,rend le numéro de cet arc (ce numéro est utilisé pour indexer sSuk[1..]);sinon,rend 0.
	int nArc;
	int aK;
	Assert3("nGrapheArc",bGraphe(pgG),bGrapheSommet(pgG,sOrigine),bGrapheSommet(pgG,sDestination));
	for (nArc=0,aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
		if (pgG->sSuk[aK]==sDestination)
			nArc=aK;//l'arc est effectivement présent dans gG
	return(nArc);
}//nGrapheArc

char *sGrapheArc(graf *pgG,int aArcNumero){//O(S)
	//rend sous la forme d'un couple (sX,sY) les sommets sX et sY qui délimitent l'arc aArcNumero de pgG.
	char *sArc;
	int bEureka,sX;
	//Appel0("sGrapheArc");
		//tee("aArcNumero,pgG->nArcEnTout",aArcNumero,pgG->nArcEnTout);
		Assert2("sGrapheArc0",bGrapheSimple(pgG),bCroit(1,aArcNumero,pgG->nArcEnTout));
		for (bEureka=kF,sX=1;sX<=pgG->nSommetEnTout && !bEureka;sX++)
			if ( bCroit(pgG->aHed[sX],aArcNumero,pgG->aHed[sX+1]-1) ){
				sArc=sCouple(sX,pgG->sSuk[aArcNumero]);//l'arc est effectivement présent dans gG
				bEureka=kV;
			}
		Assert1("sGrapheArc1",bEureka);
		//sArc=sC2("Alpha","Beta");
	//Appel1("sGrapheArc");
	return(sArc);
}//sGrapheArc

void GrapheAreter(graf *pgG,int sOrigine,int sDestination){//O(A)
	//ajoute à pgG les arcs (sOrigine,sDestination) et (sDestination,sOrigine). Modifie les champs nArcEnTout, aHed et sSuk. Déroute si échec.
	Assert1("GrapheAreter",sOrigine!=sDestination);
	GrapheArquer(pgG,sOrigine,sDestination);
	GrapheArquer(pgG,sDestination,sOrigine);
}//GrapheAreter

void GrapheAreter0(graf *pgG,int sOrigine,int sDestination,int nGenreDePoids,int iPoidsSurArc){//O(A)
	//ajoute à pgG l'arête (sOrigine,sDestination) avec la pondération iPoidsSurArc ds le champ sépcifié par nGenreDePoids. Déroute si échec.
	Assert1("GrapheAreter0",bGrapheAttribuT(nGenreDePoids));
	GrapheArquer0(pgG,sOrigine,sDestination,nGenreDePoids,iPoidsSurArc);
	GrapheArquer0(pgG,sDestination,sOrigine,nGenreDePoids,iPoidsSurArc);
}//GrapheAreter0

void GrapheAreter1(graf *pgG,int sOrigine,int sDestination,int nCouleur){//O(A)
	//ajoute à pgG les arcs colorés (sOrigine,sDestination,nCouleur) et (sDestination,sOrigine,nCouleur). Déroute si échec.
	Assert1("GrapheAreter1",sOrigine!=sDestination);
	GrapheArquer0(pgG,sOrigine,sDestination,gpCouleur,nCouleur);
	GrapheArquer0(pgG,sDestination,sOrigine,gpCouleur,nCouleur);
}//GrapheAreter1

void GrapheAreter2(graf *pgG,int sOrigine,int sDestination,int nCouleurDirecte,int nCouleurInverse){//O(A)
	//ajoute à pgG les arcs colorés (sOrigine,sDestination,nCouleurDirecte) et (sDestination,sOrigine,nCouleurInverse). Déroute si échec.
	Assert1("GrapheAreter2",sOrigine!=sDestination);
	GrapheArquer0(pgG,sOrigine,sDestination,gpCouleur,nCouleurDirecte);
	GrapheArquer0(pgG,sDestination,sOrigine,gpCouleur,nCouleurInverse);
}//GrapheAreter2

void GrapheArquer(graf *pgG,int sOrigine,int sDestination){//O(A)
	//ajoute à pgG l'arc (sOrigine,sDestination). Modifie les champs nArcEnTout, aHed et sSuk. Déroute si échec.
	//d2(sOrigine,sDestination);
	int bArquer=bGrapheArqueR(pgG,sOrigine,sDestination,0);
	if (!bArquer){
		printf("Impossible d'ajouter l'arc(%d,%d) ——",sOrigine,sDestination);
		if (!bGrapheSommet(pgG,sOrigine)) printf("sommet origine inconnu.\n");
		if (!bGrapheSommet(pgG,sDestination)) printf("sommet destination inconnu.\n");
		if (bGrapheArc(pgG,sOrigine,sDestination)) printf("arc déjà présent.\n");
	}
	Assert1("GrapheArquer",bArquer);
}//GrapheArquer

int bGrapheArqueR(graf *pgG,int sOrigine,int sDestination,int nCouleur){//O(A)
	//ajoute l'arc (sOrigine,sDestination) à pgG; l'ajout modifie les champs nArcEnTout, aHed, sSuk, en plus de coulh.
	int bArquer,aK,sX;
	Assert3("bGrapheArqueR0 module non amorcé ou graphe non valide",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	Assert11("bGrapheArqueR1 origine non définie,sOrigine",bGrapheSommet(pgG,sOrigine),sOrigine );
	Assert11("bGrapheArqueR2 destination non définie,sDestination",bGrapheSommet(pgG,sDestination),sDestination);
	if (bGrapheSimplE && bGrapheArc(pgG,sOrigine,sDestination))
		sd2("bGrapheArqueR",sOrigine,sDestination);//pb: l'arc à ajouter figure déjà dans le graphe
	Assert1("bGrapheArqueR3 cet arc existe déjà",!bGrapheSimplE || !bGrapheArc(pgG,sOrigine,sDestination));//l'arc à créer existe déjà
	bArquer=bGrapheSommet(pgG,sOrigine) && bGrapheSommet(pgG,sDestination) && (!bGrapheSimplE || !bGrapheArc(pgG,sOrigine,sDestination));
	if (bArquer){
		Assert1("bGrapheArqueR4 trop d'arcs",pgG->nArcEnTout+1<kuGrapheArcLim);
		//faire une place au nouvel arc en décalant vers les index hauts les demi-tableaux qui décrivent les valeurs des arcs
			for (aK=pgG->nArcEnTout;aK>=pgG->aHed[sOrigine+1];aK--){
				pgG->sSuk[aK+1]=pgG->sSuk[aK];
				pgG->coulh[aK+1]=pgG->coulh[aK];
				pgG->nCapaMin[aK+1]=pgG->nCapaMin[aK];
				pgG->nCapaMax[aK+1]=pgG->nCapaMax[aK];
				pgG->nCout[aK+1]=pgG->nCout[aK];
				pgG->nPoids[aK+1]=pgG->nPoids[aK];
				pgG->nPhi[aK+1]=pgG->nPhi[aK];
			}
		//insérer le nouvel arc
			aK=pgG->aHed[sOrigine+1];
			pgG->sSuk[aK]=sDestination;
			for (sX=sOrigine;sX<=pgG->nSommetEnTout;sX++)
				pgG->aHed[sX+1]++;
			pgG->nArcEnTout++;
		//affecter pgG->coulh et razer les autres pondérations
			pgG->coulh[aK]=nCouleur;
			pgG->nCapaMin[aK]=0;
			pgG->nCapaMax[aK]=0;
			pgG->nCout[aK]=0;
			pgG->nPoids[aK]=0;
			pgG->nPhi[aK]=0;
	}
	Assert2("bGrapheArqueR9: bGraphe et bGrapheSimple",bGraphe(pgG),bGrapheSimple(pgG));
	return(bArquer);
}//bGrapheArqueR

void GrapheArquer0(graf *pgG,int sOrigine,int sDestination,int nGenreDePoids,int iPoidsSurArc){//O(A)
	//ajoute l'arc (sOrigine,sDestination) à pgG ——affecte les champs désignés par nGenreDePoids ainsi que nArcEnTout,aHed,sSuk. Déroute si échec.
	//if (sOrigine==12 && sDestination ==9) d4(145,sOrigine,sDestination,iPoidsSurArc);
	Assert1("GrapheArquer0",bGrapheAttribuT(nGenreDePoids));
	int bArquer=bGrapheArqueR(pgG,sOrigine,sDestination,0);
	Assert1("GrapheArquer01",bArquer);
	if (bArquer)
		GraphePonderer(pgG,sOrigine,sDestination,nGenreDePoids,iPoidsSurArc);
}//GrapheArquer0

void GrapheArquer1(graf *pgG,int sOrigine,int sDestination){//O(A)
	//ajoute à pgG l'arc (sOrigine,sDestination) si pas déjà là, en modifiant les champs nArcEnTout, aHed et sSuk.
	//d2(sOrigine,sDestination);
	bGrapheArqueR(pgG,sOrigine,sDestination,0);
}//GrapheArquer1

void GrapheArquer2(graf *pgG,int sOrigine,int sDestination,int nCouleurDirecte,int nCouleurInverse){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	//d3(sOrigine,sDestination,nCouleur);
	int bArquer1=bGrapheArqueR(pgG,sOrigine,sDestination,nCouleurDirecte);
	int bArquer2=bGrapheArqueR(pgG,sDestination,sOrigine,nCouleurInverse);
	Assert1("GrapheArquer2",bArquer1 && bArquer2);
}//GrapheArquer2

void GrapheArquer3(graf *pgG,int sOrigine,int sDestination,int nCapaMin,int nCapaMax,int nCout){//O(A)
	//ajoute effectivt l'arc (sOrigine,sDestination) à pgG ——affecte les champs nArcEnTout,aHed,sSuk,nCapaMax,nCapaMin,nCout. Déroute si échec.
	int aK;
	int bArquer=bGrapheArqueR(pgG,sOrigine,sDestination,0);
	if (bArquer){
		aK=nGrapheArc(pgG,sOrigine,sDestination);
		Assert1("GrapheArquer30",aK>0);
		pgG->nCapaMin[aK]=nCapaMin;
		pgG->nCapaMax[aK]=nCapaMax;
		pgG->nCout[aK]=nCout;
	}
	Assert1("GrapheArquer31",bArquer);
}//GrapheArquer3

void GrapheArquer4(graf *pgG,int sOrigine,int sDestination,int nCouleur,int nPoids){//O(A)
	//ajoute effectivt l'arc (sOrigine,sDestination) à pgG avec nCouleur et nPoids. Déroute si échec.
	//d4(sOrigine,sDestination,nCouleur,nPoids);
	int bArquer=bGrapheArqueR(pgG,sOrigine,sDestination,0);
	if (bArquer)
		GraphePonderer(pgG,sOrigine,sDestination,gpCouleur,nCouleur);
	if (bArquer)
		GraphePonderer(pgG,sOrigine,sDestination,gpPoids,nPoids);
	Assert1("GrapheArquer41",bArquer);
}//GrapheArquer3

void GrapheAttribueR(graf *pgSource,int aCible,int nGenreDePoids,graf *pgCible,int aSource){
	Assert1("GrapheAttribueR",bGrapheAttribuT(nGenreDePoids));
	if (nGenreDePoids & gpCapaMax) pgCible->nCapaMax[aCible]=pgSource->nCapaMax[aSource];
	if (nGenreDePoids & gpCapaMin) pgCible->nCapaMin[aCible]=pgSource->nCapaMin[aSource];
	if (nGenreDePoids & gpCouleur) pgCible->coulh[aCible]=pgSource->coulh[aSource];
	if (nGenreDePoids & gpCout) pgCible->nCout[aCible]=pgSource->nCout[aSource];
	if (nGenreDePoids & gpPhi) pgCible->nPhi[aCible]=pgSource->nPhi[aSource];
	if (nGenreDePoids & gpPoids) pgCible->nPoids[aCible]=pgSource->nPoids[aSource];
}//GrapheAttribueR

int bGrapheAttribuT(int iAttributOuPas){
	//vrai ssi iAttributOuPas est un attribut ou une somme d'attributs (qui sont des puissances de 2)
	int bAttribut=bCroit(2*gpAlpha,iAttributOuPas,2*gpZeta-1);
	return(bAttribut);
}//bGrapheAttribuT

void CircuitImpairExhibeR(graf *pgG,int sX0,int sY0){
	//affiche le circuit défini par l'arête (sX0,sY0) qui relie 2 "demi-circuits": l'un va de sX0 à un sommet commun sR;l'autre de sY0 à sR.
	const int kbVoir=0;
	int sX,sY,sR;
	int sCircuit[1+pgG->nSommetEnTout];
	if (kbVoir) Ligne();
	if (kbVoir) printf("Arête de départ: %s.\n",sCouple(sX0,sY0));
	if (kbVoir) VecteurVoir1("pgG->sPer",pgG->sPer,1,pgG->nSommetEnTout);
	DequeAllouer(pgG->nSommetEnTout);
		//empiler dans la deque le demi-circuit qui va de sX0 à sR inclus
			DequeEmpiler(sX=sX0);
			while (pgG->sPer[sX]!=sX)
				DequeEmpiler(sX=pgG->sPer[sX]);
			DequeEmpiler(sR=sX);
			if (kbVoir) printf("Sommet commun: %s.\n",sEnt(sR));
			if (kbVoir) DequeVoir(sC3b("du demi-circuit n°1,",sEnt(sR),"inclus"));
		//empiler dans sCircuit[] le demi-circuit qui va de sY0 à sR exclu
			sCircuit[0]=0;
			sY=sY0;
			while (pgG->sPer[sY]!=sY)
				sY=pgG->sPer[sCircuit[++sCircuit[0]]=sY];
			if (kbVoir) VecteurVoir0(sC3b("Pile du demi-circuit n°2,",sEnt(sR),"exclu"),sCircuit);
		//dépiler la deque et l'empiler dans sCircuit[]
			while (!bDequeVide())
				sCircuit[++sCircuit[0]]=sDequeDepiler();
		//empiler sY0 pr clore la liste des sommets du circuit
			sCircuit[++sCircuit[0]]=sY0;
	DequeAllouer(0);
	printf("%s",sListe(sCircuit,'('));
}//CircuitImpairExhibeR

int bGrapheBiparti(graf *pgG,int idAfficher){//O(A)
	//dit si pgG est biparti et rend la couleur de chaque sommet sX dans pgG->sPer[sX].
	int kbVoir=kF;
	enum {cIncolore,cNoir,cRouge};
	int bBiparti,uC,nCardinal,nItem,aK,sX,sY,sZ,sX0,sY0;
	graf *pgH;
	int nCouleur[1+pgG->nSommetEnTout];
	if (kbVoir) Appel0("bGrapheBiparti");
		Assert2("bGrapheBiparti",bGrapheAmorceR,bGraphe(pgG));
		bBiparti=bGrapheSimple(pgG);
		if (bBiparti){
			pgH=(graf *) malloc(sizeof(graf));
				//pgH:=copie symétrisée de pgG (l'algo ci-dessous requiert un graphe symétrique).
					GrapheDupliquer(pgG,&pgH);
					GrapheSymetriser(pgH,gpCouleur+gpCout);
				//bBiparti:=pgH est bicolorable
					DequeAllouer(pgH->nSommetEnTout);//raze;O(pgH->nSommetEnTout)
						VecteurValuer(nCouleur,1,pgH->nSommetEnTout,cIncolore);
						VecteurRazer(pgG->sPer,1,pgH->nSommetEnTout);
						for (bBiparti=kV,sZ=1;sZ<=pgH->nSommetEnTout;sZ++){
							if (nCouleur[sZ]==cIncolore){
								nCouleur[sZ]=cNoir;
								pgG->sPer[sZ]=sZ;//printf("L'autopère de %d est %d.\n",sZ,sZ);
								DequeEnfiler(sZ);
								if (kbVoir) VecteurVoir("nCouleur[] initial",&nCouleur[0],1,pgH->nSommetEnTout);
								while (nCardinal=nDequeCardinal(),nCardinal>0)
									for (uC=1;uC<=nCardinal;uC++){
										sX=sDequeDefiler();
										for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++){
											sY=pgH->sSuk[aK];
											if (nCouleur[sY]==cIncolore){
												nCouleur[sY]=(nCouleur[sX]==cNoir)? cRouge: cNoir;
												pgG->sPer[sY]=sX;//printf("Le père de %d est %d.\n",sY,sX);
												DequeEnfiler(sY);
												if (kbVoir) VecteurVoir("nCouleur[] général",&nCouleur[0],1,pgH->nSommetEnTout);
											} else if (nCouleur[sY]==nCouleur[sX]){//cycle impair
												bBiparti=kF;
												sX0=sX;sY0=sY;//permettra de retrouver le cycle impair
											}
										}
									}//for
							}//if
						}//for
					DequeAllouer(0);
			free(pgH);
		}
		if (idAfficher){
//b(idAfficher);
			printf("%s graphe %s biparti",(idAfficher<0)? sC3(flag, (bBiparti)? "Or":"Mais"," ce") : "\tCe",sEst(bBiparti));
			if (bBiparti){//afficher le résultat ainsi que la bipartition éventuelle
				if (abs(idAfficher)>1)
					printf(".\n%sSoit X l'ensemble des sommets rouges de la bicoloration et Y l'ensemble des sommets noirs. On obtient",flag);
				printf(":\n");
				for (nItem=0,sX=1;sX<=pgH->nSommetEnTout;sX++)
					nItem+=(nCouleur[sX]==cRouge);
				for (printf("\t%sX={",(idAfficher<0)? flag : "\t"),sX=1;sX<=pgH->nSommetEnTout || bPrint("}.");sX++)
					if (nCouleur[sX]==cRouge)
						printf("%s%s",sEnt(sX),(--nItem>0)? "," : "");
				for (nItem=0,sX=1;sX<=pgH->nSommetEnTout;sX++)
					nItem+=(nCouleur[sX]==cNoir);
				for (printf("\t%sY={",(idAfficher<0)? flag : "\t"),sX=1;sX<=pgH->nSommetEnTout || bPrint("}.");sX++)
					if (nCouleur[sX]==cNoir)
						printf("%s%s",sEnt(sX),(--nItem>0)? "," : "");
			}else if (1){
				if (idAfficher>1)
					printf (".\n%sIl contient un cycle impair: ",flag);
				if (idAfficher<0)
					printf (" car il contient un cycle impair: ");
				if (idAfficher<0 || idAfficher>1){
					CircuitImpairExhibeR(pgG,sX0,sY0);
					printf(".\n");
				}
			}else printf (" car il contient un cycle impair ——qui contient %s.\n",sCouple(sX0,sY0));
		}
	VecteurCopier(nCouleur,1,pgG->nSommetEnTout,pgG->sPer);
	if (kbVoir) Appel1("bGrapheBiparti");
	return(bBiparti);
}//bGrapheBiparti

int bGrapheBipartiOuAfficherCycleImpair(graf *pgG){//O(A)
	int bBiparti;
	int sConflit0,sConflit1;
	int uC,aK;
	int nCardinal;
	enum couleur {cIncolore,cNoir,cRouge};
	int sX,sY,sZ;
	int nCoulh[kuGrapheSommetLim];
	int sPere[kuGrapheSommetLim];
	Assert4("bGrapheBiparti",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),bGrapheSymetrique(pgG));
	DequeAllouer(pgG->nSommetEnTout);//raze;O(pgG->nSommetEnTout)
		//razer nPere[]
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				sPere[sX]=0;
		//décolorer tous les sommets du graphe
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				nCoulh[sX]=cIncolore;
		//(sConflit0,sConflit1),sPere[]:=(sommet en conflit avec sConflit1,sommet 1 en conflit avec sConflit0), sPere[sY]=sX si sY a été coloré grâce à sX.
			for (sConflit0=0,sConflit1=0,sZ=1;sZ<=pgG->nSommetEnTout;sZ++){
				if (nCoulh[sZ]==cIncolore){
					nCoulh[sZ]=cNoir;
					sPere[sZ]=sZ;
					DequeEnfiler(sZ);
					while (nCardinal=nDequeCardinal(),nCardinal>0)
						for (uC=1;uC<=nCardinal;uC++){
							sX=sDequeDefiler();
							for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
								sY=pgG->sSuk[aK];
								if (nCoulh[sY]==cIncolore){
									nCoulh[sY]=(nCoulh[sX]==cNoir)? cRouge: cNoir;
									sPere[sY]=sX;
									DequeEnfiler(sY);
								} else if (nCoulh[sY]==nCoulh[sX]){//cycle impair
									sConflit1=sX;sConflit0=sY;}
							}
						}//for
				}//while
			}//for
		//bBiparti:=pgG est bicolorable,ie aucun sommet n'est en conflit de couleur avec un sommet adjacent.
			bBiparti=(sConflit0==0);
		if (!bBiparti){
			//tee("sConflit0,sConflit1",sConflit0,sConflit1);
			printf("Un cycle impair a été détecté:");
			//enfiler les sommets qui ont permis de colorer sConflit0
				sX=sConflit0;
				while(sX!=sPere[sX]){
					DequeEnfiler(sX);//n'enfile rien si déjà enfilé
					sX=sPere[sX];
				}
			//afficher ces sommets
				for (nCardinal=nDequeCardinal(),uC=1;uC<=nCardinal;uC++)
					printf(" %d",sDequeDefiler());
	DequeAllouer(0);//fin du mode file;la Deque fonctionnant soit en mode pile soit en mode file,on ne peut mélanger les deux modes.
	DequeAllouer(pgG->nSommetEnTout);//début du mode pile
			//empiler les sommets qui ont permis de colorer sConflit1
				DequeEmpiler(sX=sConflit1);
				while(sX!=sPere[sX])
					DequeEmpiler(sX=sPere[sX]);
			//afficher ces sommets
				for (nCardinal=nDequeCardinal(),uC=1;uC<=nCardinal;uC++)
					printf(" %d",sDequeDepiler());
			printf(" %d.\n",sConflit0);//réaffiche sConflit0 afin de signifier qu'il s'agit bien d'un cycle, et non pas d'un chaîne.
		}
	DequeAllouer(0);
	return(bBiparti);
}//bGrapheBipartiOuAfficherCycleImpair

void GrapheBipartir(graf *pgG,int bBipartir){//O(A)
	//si bBipartir,négative dans pgG->aHed[] les sommets de l'ensemble X réputé biparti; sinon,dénégative pgG->aHed[].
	int bBiparti;
	int uC;
	int nCardinal;
	enum couleur {cIncolore,cNoir,cRouge};
	int aK,sX,sY,sZ;
	int nCouleur[kuGrapheSommetLim];
	int kbVoir=kF;
	if (kbVoir) Appel0("GrapheBipartir");
		FlipFlop("GrapheBipartir",bBipartir,&bGrapheBipartiR);
		if (bBipartir){
			Assert4("GrapheBipartir0",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),bGrapheSymetrique(pgG));
			//bBiparti,nCouleur[]:=pgG est bicolorable,nCouleur[sX]:cRouge/cNoir si sX appartient à X/à Y.
				DequeAllouer(pgG->nSommetEnTout);//raze;O(pgG->nSommetEnTout)
					//décolorer tous les sommets de pgH
						for (sX=1;sX<=pgG->nSommetEnTout;sX++)
							nCouleur[sX]=cIncolore;
					for (bBiparti=kV,sZ=1;sZ<=pgG->nSommetEnTout;sZ++){
						if (nCouleur[sZ]==cIncolore){
							nCouleur[sZ]=cNoir;
							DequeEnfiler(sZ);
							if (kbVoir) VecteurVoir("nCouleur[] initial",&nCouleur[0],1,pgG->nSommetEnTout);
							while (nCardinal=nDequeCardinal(),nCardinal>0)
								for (uC=1;uC<=nCardinal;uC++){
									sX=sDequeDefiler();
									for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
										sY=pgG->sSuk[aK];
										if (nCouleur[sY]==cIncolore){
											nCouleur[sY]=(nCouleur[sX]==cNoir)? cRouge: cNoir;//cRouge,cNoir est la couleur des sommets de X/de Y.
											DequeEnfiler(sY);
											if (kbVoir) VecteurVoir("nCouleur[] général",&nCouleur[0],1,pgG->nSommetEnTout);
										} else if (nCouleur[sY]==nCouleur[sX])//cycle impair
											bBiparti=kF;
									}
								}//for
						}//if
					}//for
				DequeAllouer(0);
			Assert1("GrapheBipartir2",bBiparti);//pgG est réputé biparti
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)//négative dans pgG->aHed[] les sommets de l'ensemble X colorés en cRouge
				pgG->aHed[sX]=iSignePres(nCouleur[sX]==cRouge,pgG->aHed[sX]);
			if (0){
				printf("Ensemble X obtenu:{");
					for (sX=1;sX<=pgG->nSommetEnTout;sX++)
						if (pgG->aHed[sX]<0)
							printf(" %d",sX);
				printf(" }.\n");
			}
	} else {for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				pgG->aHed[sX]=abs(pgG->aHed[sX]);
			Assert3("GrapheBipartir1",bGraphe(pgG),bGrapheSimple(pgG),bGrapheSymetrique(pgG));
	}
	if (kbVoir) Appel1("bGrapheBiparti");
}//GrapheBipartir

int bGrapheBipartition(graf *pgG,int sEnsembleX[],int sEnsembleY[]){//O(A)
	//vrai ssi les ensembles sEnsembleX[] et sEnsembleY[] constituent une bipartition de pgG;écrase pgG->nVal
	int bBipartition,uIndex,aK,sX,sY;
	//vérifier sEnsembleX et sEnsembleY sont définis 
		for (uIndex=1;uIndex<=sEnsembleX[0];uIndex++)
			Assert1("bGrapheBipartition:sEnsembleX non défini",bCroit(1,sEnsembleX[uIndex],pgG->nSommetEnTout));
		for (uIndex=1;uIndex<=sEnsembleY[0];uIndex++)
			Assert1("bGrapheBipartition:sEnsembleY non défini",bCroit(1,sEnsembleY[uIndex],pgG->nSommetEnTout));
	//vérifier que ces ensembles sont disjoints 
		VecteurRaz(pgG->nVal,pgG->nSommetEnTout);
		for (uIndex=1;uIndex<=sEnsembleX[0];uIndex++)
			pgG->nVal[sEnsembleX[uIndex]]++;
		for (uIndex=1;uIndex<=sEnsembleY[0];uIndex++)
			pgG->nVal[sEnsembleY[uIndex]]++;
		Assert1("bGrapheBipartition:ensembles non disjoints",yVecteurSup(pgG->nVal,1,pgG->nSommetEnTout)==1);
	//bBipartition:=ces ensembles constituent une bipartition de pgG 
		VecteurRaz(pgG->nVal,pgG->nSommetEnTout);
		for (uIndex=1;uIndex<=sEnsembleX[0];uIndex++)
			pgG->nVal[sEnsembleX[uIndex]]=+1;
		for (uIndex=1;uIndex<=sEnsembleY[0];uIndex++)
			pgG->nVal[sEnsembleY[uIndex]]=-1;
		for (bBipartition=sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				bBipartition=bBipartition && pgG->nVal[sX]!=pgG->nVal[sY=pgG->sSuk[aK]];
	return(bBipartition);
}//bGrapheBipartition

void GrapheBipartitionne(graf *pgG){//O(A)
	//X devient X' et X"=X+nSommet,contrairt à GrapheBipartitionner(). Altère uniqt pgG->nSommetEnTout,pgG->nArcEnTout,aHed et sSuk.
	int nArc;
	int aK;
	int nSommet;
	int kbVerifier=kF;
	int sX;
	Assert3("GrapheBipartitionne",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	if (kbVerifier) GrapheVoir("AVANT",pgG);
	nSommet=pgG->nSommetEnTout;
	nArc=pgG->nArcEnTout;
	//enfiler dans pgG->aHed[] nSommet nouveaux sommets X' devant les sommets X renommés nSommet+sX
		if (kbVerifier) VecteurVoir("aHed1",&pgG->aHed[0],1,nSommet+1);
		for (sX=nSommet;sX>=0;sX--)
			pgG->aHed[nSommet+sX+1]=nSommet+pgG->aHed[sX+1];//décale et donc translate les noms des sommets
		if (kbVerifier) VecteurVoir("aHed2",&pgG->aHed[0],1,2*nSommet+1);
		for (sX=nSommet;sX>0;sX--)
			pgG->aHed[sX]=sX;
		if (kbVerifier) VecteurVoir("aHed3",&pgG->aHed[0],1,2*nSommet+1);
	//enfiler dans pgG->sSuk[] un arc (X',X) pour chaque sommet X' créé
		if (kbVerifier) VecteurVoir("sSuk4",&pgG->sSuk[0],1,nArc);
		for (aK=nArc;aK>0;aK--)
			pgG->sSuk[aK+nSommet]=pgG->sSuk[aK];//décale et pointe vers les sommets 1..nSommet,lesquels sont maintenant les nouveaux sommets
		for (aK=1;aK<=nSommet;aK++)
			pgG->sSuk[aK]=nSommet+aK;//les nouveaux sommets 1..nSommet pointent vers les anciens,ie ceux renommés nSommet+sX
		if (kbVerifier) VecteurVoir("sSuk5",&pgG->sSuk[0],1,nArc+nSommet);
	pgG->nSommetEnTout+=nSommet;
	pgG->nArcEnTout+=nSommet;
	if (kbVerifier) GrapheVoir("APRES",pgG);
	/*if (0 && kbVerifier)
		GrapheSymetriser(pgG,gpCouleur+gpCout);*/
	Assert4("GrapheBipartitionne",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),bGrapheBiparti(pgG,!k1Afficher));
}//GrapheBipartitionne

void GrapheBipartitionner(graf *pgG){//O(A)
	//X devient X' et X"=X+1,contrairt à GrapheBipartitionne(). Altère uniqt pgG->nSommetEnTout,pgG->nArcEnTout,aHed et sSuk.
	int nArc;//dit autrement,X est remplacé par l'arc (2*X-1,2*X).
	int aK;
	int kbScruter=kF;
	int nSommet;
	int sX,sY;
	Assert3("GrapheBipartitionner1",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	if (kbScruter) Appel0("GrapheBipartitionner");
		if (kbScruter) GrapheVoir("AVANT",pgG);
		nSommet=pgG->nSommetEnTout;
		nArc=pgG->nArcEnTout;
		//ménager entre les listes de sommets successeurs dédiés à chaque sommet source 1 arc par nouveau sommet,en terminant par un nouvel arc en pgG->sSuk[1]. 
			if (kbScruter) VecteurVoir("sSuk4",&pgG->sSuk[0],1,nArc+nSommet);
			for (sX=nSommet;sX>0;sX--){
				for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX];aK--){
					sY=pgG->sSuk[aK];
					pgG->sSuk[aK+sX]=2*sY-1;
				}
				if (kbScruter) tee("aK,sX",aK,sX);
				pgG->sSuk[aK+sX]=2*sX;//nouvel arc,notamment en pgG->sSuk[1] puisque aK=0 quand sX=1.
			}
			if (kbScruter) VecteurVoir("sSuk5",&pgG->sSuk[0],1,nArc+nSommet);
		//interclasser les sommets originaux de sorte que X'=X+1 pour tout X
			if (kbScruter) VecteurVoir("aHed1",&pgG->aHed[0],1,nSommet+1);
			//d(2*nSommet+2);
			Assert1("GrapheBipartitionner3",2*nSommet+2<kuGrapheSommetLim);//pr li+3;sinon,ajouter un "if"
			for (sX=nSommet;sX>=0;sX--){
				pgG->aHed[2*sX+1]=pgG->aHed[sX+1]+sX;
				pgG->aHed[2*sX+2]=pgG->aHed[2*sX+1]+1;
			}
			if (kbScruter) VecteurVoir("aHed2",&pgG->aHed[0],1,2*nSommet+1);
			if (kbScruter) VecteurVoir("sSuk6",&pgG->sSuk[0],1,nArc+nSommet);
		pgG->nSommetEnTout+=nSommet;
		pgG->nArcEnTout+=nSommet;
		if (kbScruter) GrapheVoir("APRES",pgG);
		if (0 && kbScruter)
			GrapheSymetriser(pgG,gpCouleur+gpCout);
		Assert4("GrapheBipartitionner9",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),!kbScruter || bGrapheBiparti(pgG,!k1Afficher));
	if (kbScruter) Appel1("GrapheBipartitionner");
}//GrapheBipartitionner

void GrapheBoucler(graf *pgG,int sBoucle){
	GrapheSimple(0);
		GrapheArquer0(pgG,sBoucle,sBoucle,gpCouleur,1);
	GrapheSimple(1);
}//GrapheBoucler

//#define GrapheType {grAlpha,gr2Aile,gr2Diam,grC2,grC3,grC4,grC5,grC6,grC4b,grD2,grD3,grD4,grK2,grK3,grK4,grK5,grK6,grL4,grP2,grP3,grP4,grP5,grP6,grP7,grP8,grQ0,grQ1,grS2,grS3,grS4,grS5,grS6,grT,grT2,grW,grXor,grX,grXX,grXY,grOmega}
int nGrapheCardinal(int grGadget,int nGadgetTaille){
	//rend le nbre de sommets du graphe grGadget
	enum grType GrapheType;
	int nCardinal=1;//d
	if ( bDans1(grGadget,grB) ) nCardinal=9;
	if ( bDans4(grGadget,gr2Croix,gr2P,grT,grX) ) nCardinal=4;
	if ( bDans2(grGadget,grC,grXor) ) nCardinal=6;
	if ( bDans1(grGadget,grPt) ) nCardinal=10;
	if ( bDans1(grGadget,grY) ) nCardinal=6*nGadgetTaille;
	if ( bDans1(grGadget,grU) ) nCardinal=5;
	return(nCardinal);
}//nGrapheCardinal

void GrapheChaine(int sX,int sY,int bColorer,int nCouleur,int nPoids,const int kuChaineLgMax,char *sChaine,int *pipC){
	//empile ds sChaine la description de (sX,sY,nPoids éventuel,nCouleur). 
	int ipC=*pipC;
	const int kuDigitAuPlus=20;//pr décrire un poids
	int uD,nDigit,nP[1+kuDigitAuPlus];
	//d4(sX,sY,nCouleur,nPoids);
	Assert4("GrapheChaine0",sX>=0,sY>=0,nCouleur>=0,nPoids>=0);
	//ccc(cLettre(sX),cLettre(sY),'0'+nCouleur);d(nPoids);
	//empiler la desciption des extrémités de l'arc
		sChaine[ipC++]=cLettre(sX);
		sChaine[ipC++]=cLettre(sY);
	//empiler le poids éventuel
		if (nPoids>0){
			nDigit=nLog10(nPoids);
			for (uD=1;uD<=nDigit;nPoids/=10,uD++)
				nP[nDigit-uD+1]=nPoids%10;
			for (uD=1;uD<=nDigit;uD++)
				sChaine[ipC++]='0'+nP[uD];
		}
	if (bColorer)
		sChaine[ipC++]='0'+nCouleur;
	Assert1("GrapheChaine1",ipC<kuChaineLgMax);//il reste encore de la place ds sChaine
	*pipC=ipC;
}//GrapheChaine

void GrapheChainer(graf *pgG,const char *kszPoleItem,const int knGenreDePoids,const int kuChaineLgMax,char *sChaineDejaAlloueh){
	//traduit pgG en chaîne et ajoute les pôles éventuels si kszPoleItem n'est pas une chaîne vide. 
	//chaque arc est converti en quadruplet (sX,sY,nPoids éventuel+nCouleur) mm avec 0; ajoute les pondérO non nulles. 
	Assert1("GrapheChainer",bGrapheAttribuT(knGenreDePoids));
	const int kbMemeSiRetroaction= 1;
	int ipC,aK,uP,sX,sY,bEmpiler,uCouleur,nPoids,nbPole=nItem(kszPoleItem),bColorer=(knGenreDePoids & gpCouleur!=0);
	//d(nbPole);
	//GrapheVoir("KatriceChaineR",pgG);
	for (ipC=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
		for (aK=pgG->aHed[sX];sY=pgG->sSuk[aK],aK<pgG->aHed[sX+1];aK++){
			bEmpiler=!(sX==pgG->nSommetEnTout && sY==1);//supprime la rétroaction éventuelle
			if (kbMemeSiRetroaction || bEmpiler)
				GrapheChaine(sX,sY,bColorer,pgG->coulh[aK],iGraphePoids(pgG,knGenreDePoids,aK),kuChaineLgMax,sChaineDejaAlloueh,&ipC);
		}
	//si nbPole>0, ajouter une description automatQ des pôles ——que l'uH changera au besoin
		for (uCouleur=4,uP=1;uP<=nbPole;uP++)
			GrapheChaine(nLettre(sItem(kszPoleItem,uP)[0]),pgG->nSommetEnTout+uP,bColorer,uCouleur++,nPoids=0,kuChaineLgMax,sChaineDejaAlloueh,&ipC);
	sChaineDejaAlloueh[ipC++]='\0';
	Assert1("GrapheChainer1",ipC<kuChaineLgMax);//il reste encore de la place ds sChaine
	//s(sChaine);
}//GrapheChainer

void GrapheCheminE(graf *pgG,int sSource,int sTrappe,int bCheminer,int zdAfficher,int nMesure,int gcMode){
	//affiche s'il existe le chemin qui relie sSource à sTrappe,sa grandeur (ie une longueur ou une largeur,selon gcMode) et sa valeur nMesure.
	int aK,uS,sX,bLePlusLarge,bArbre;
	int nKm[1+pgG->nSommetEnTout];//coût de chaque arc du chemin à afficher
	Assert3("GrapheCheminE",bBool(bCheminer),pgG->sPer[sSource]==sSource,nMesure>=0);
	bArbre=gcMode==echArbreCouvranT;
	if (bCheminer){
		if (zdAfficher==1) Tabuler(+1);
		//d2(sSource,sTrappe);
		VecteurRazer(nKm,0,pgG->nSommetEnTout);
		if (bArbre)
			printf("%sArêtes de l'arbre couvrant: ",sTab0());
		else printf("%sChemin le plus %s du sommet %s au sommet %s: (",sTab0(),sItem4(gcMode,"court","large","long","court en moyenne"),sEnt2(sSource,0),sEnt2(sTrappe,0));
		//afficher sommet par sommet le chemin qui relie sSource à sTrappe ——en partant de sSource:
			if (!bArbre){
				DequeAllouer(pgG->nSommetEnTout);
					//empiler les sommets car ils jalonnent le chemin à afficher dans le sens inverse du sens requis pour l'affichage, et les coûts des arcs du chemin
						sX=sTrappe;
						While(pgG->nSommetEnTout);
						while ( bWhile("GrapheCheminE",pgG->sPer[sX]!=sX) ){
							DequeEmpiler(sX);
							aK=nGrapheArc(pgG,pgG->sPer[sX],sX);
							nKm[++nKm[0]]=pgG->nCout[aK];
							sX=pgG->sPer[sX];
						}
						DequeEmpiler(sX);
					//afficher les sommets en les dépilant: ils se présentent dans l'ordre requis pour l'affichage
						for (uS=nDequeCardinal();uS>0;uS--)
							printf("%s%s",sEnt2(sX=sDequeDepiler(),0),(uS>1)?",":"");
				DequeAllouer(0);
				printf(").\n");
			}else {
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					if (pgG->sPer[sX]!=sX){
						aK=nGrapheArc(pgG,pgG->sPer[sX],sX);
						nKm[++nKm[0]]=pgG->nCout[aK];
						printf("(%s,%s)",sEnt2(pgG->sPer[sX],0),sEnt2(sX,0));
						if (sX<pgG->nSommetEnTout)
							printf(",");
					}
				printf(".\n");
			}
		bLePlusLarge=gcMode==echPlusLargE;
		if (bArbre)
			printf("%sPoids total de l'arbre couvrant: ",sTab0());
		else printf("%s%s de ce chemin: ",sTab0(),sPhrase0((bLePlusLarge)? "largeur": "longueur"));
		if (nKm[0]>1){
			VecteurInverser(nKm,1,nKm[0]);//pr afficher le chemin en partant de sSource et non pas de sTrappe
			int bCaractere=bModeCaractere();
			if (bCaractere) ModeCaractere(-1);
				if (bLePlusLarge)
					printf("min%s = ",sListe(nKm,'('));
				else printf("%s = ",sListe(nKm,'+'));
			if (bCaractere) ModeCaractere(1);
		}
		printf("%s.\n",sPluriel(nMesure,"unité"));
		if (zdAfficher==1) Tabuler(-1);
	}else printf("    Il n'existe pas de chemin entre les sommets %d et %d.\n",sSource,sTrappe);
}//GrapheCheminE

int bGrapheCheminE(graf *pgG,int sSource,int sTrappe){
	//rend vrai ssi pgG->sPer[] décrit un chemin qui relie sSource à sTrappe.
	int bChemine;
	int nSommet;
	int sX,sY;
	for (bChemine=kF,sX=sTrappe,nSommet=0;nSommet<=pgG->nSommetEnTout;nSommet++){
		bChemine=bChemine || (sX==sSource);
		sY=pgG->sPer[sX];//facilite le débogage
		sX=sY;
	}
	return(bChemine);
}//bGrapheCheminE

int nGrapheChemineR(graf *pgG,int sSource,int sTrappe,int zdMode,int *pnComplexiteh){//O(S2)
	//remplit pgG->nVal[] avec les distances les plus courtes depuis sSource et rend la distance à sTrappe, (algo:Dijkstra sans tas);si bSimuler,affiche la simulation de l'algo.
	const int kbVoirPere=kF;
	const int kuLg=7;
	int bSimuler=zdMode>1;
	int kuInfini=(bSimuler)? 1e4-2: 1e5;
	int nDistanceParX,nD;//nD est la distance courante de sSource au sommet le plus proche de sSource
	int bFait[1+pgG->nSommetEnTout];
	int iSimulatO[1+pgG->nSommetEnTout];//dédié simulation
	int sProche=0,uSommet,aK,sX,sY,sZ;
	if (kbVoirPere) Appel0("nGrapheChemineR");
	*pnComplexiteh=0;
	//initialiser bFait[], pgG->nVal[] et pgG->sPer[].
		VecteurRaz(bFait,pgG->nSommetEnTout);
		VecteurRaz(pgG->nVal,pgG->nSommetEnTout);
		VecteurValuer(pgG->nVal,1,pgG->nSommetEnTout,kuInfini);
		if (bSimuler) VecteurRaz(iSimulatO,pgG->nSommetEnTout);
		if (bSimuler) VecteurValuer(iSimulatO,1,pgG->nSommetEnTout,kuInfini+ 1);
		VecteurRaz(pgG->sPer,pgG->nSommetEnTout);
	pgG->nVal[sSource]=0;//distance entre le sommet de départ et lui-même
	pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE()
	if (bSimuler){//lister les noms des sommets et la 1ère ligne de la simulation
		printf("%sSimulation de l'algo de cheminement de Dijkstra pour le calcul du chemin optimal de %s à %s:\n",sTab0(),sEnt(1),sEnt(pgG->nSommetEnTout));
		Tabuler(+1);
		for (ModeCaractere(+1),printf("%s ",sTab0()),sZ=1;sZ<=pgG->nSommetEnTout || (ModeCaractere(-1),bPrint(""));sZ++)
			printf("%s%s",sE(kuLg-1),sEnt2(sZ,0) );//noms des sommets
		for (ModeCaractere(+1),printf("%s ",sTab0()),ModeCaractere(-1),sZ=1;sZ<=pgG->nSommetEnTout || !bLigne();sZ++)
			printf("%s",(pgG->nVal[sZ]==kuInfini)? " infini" : sEnt2(pgG->nVal[sZ],kuLg));//ligne n°1
	}
	for (uSommet=1; uSommet<=pgG->nSommetEnTout; uSommet++) {
		//sProche:=numéro du sommet le plus proche de sSource, ou 0 si aucun nouveau sommet ne peut être atteint depuis sSource
			for (sProche=0,nD= kuInfini,sX=1; sX<=pgG->nSommetEnTout; sX++)
				if ((*pnComplexiteh)++,!bFait[sX] && nD>pgG->nVal[sX] )
					nD=pgG->nVal[sProche=sX];
		sX=sProche;
		//d(sProche);
		if (sX!=0) {//pour tout voisin sY de sX,rectifier nDist[sY] si passer par sX réduit la distance entre sSource et sY
			if (bSimuler)
				VecteurCopier0(pgG->nVal,iSimulatO);
			for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; (*pnComplexiteh)++,aK++) {
				sY=pgG->sSuk[aK];
				nDistanceParX=pgG->nVal[sX]+pgG->nCout[aK];
				//d4(sX,sY,nDistanceParX,pgG->nVal[sY]);
				if ( pgG->nVal[sY]>nDistanceParX ) {//passer par sX est plus court
					pgG->nVal[sY]=nDistanceParX;
					pgG->sPer[sY]=sX;//sX est situé sur le chemin optimal qui relie sY à sSource.
					//d2(sX,sY);
				}
			}//for (aK
			bFait[sX]=kV;
			if (bSimuler)//afficher le nom du sommet sProche élu et les seules distances qui ont changé
				for (ModeCaractere(+1),printf("%s%s",sTab0(),sEnt(sX)),ModeCaractere(-1),sZ=1;sZ<=pgG->nSommetEnTout || !bLigne();sZ++)
					if ( iSimulatO[sZ]!=pgG->nVal[sZ])
						printf("%s",(pgG->nVal[sZ]==kuInfini)? " infini" : sEnt2(pgG->nVal[sZ],kuLg));
					else printf("%s%c",sE(kuLg-1),'"');
		}
	}//for uSommet; à chaq tour, calculer sProche coûte O(S). Chaq arc étant accédé 1 fois au + ds "for aK",la cplexité au pire vaut sup( O(S*S),O(A) ), dc O(S2)
	if (bSimuler) ModeCaractere(-1);
	if (bSimuler) Tabuler(-1);
	Assert1("nGrapheChemineR99",*pnComplexiteh>0);
	if (kbVoirPere) VecteurVoir("sPer",pgG->sPer,1,pgG->nSommetEnTout);
	if (kbVoirPere) Appel1("nGrapheChemineR");
	return(pgG->nVal[sTrappe]);
}//nGrapheChemineR

int bGrapheCheminerAuLarge(graf *pgG,int sSource,int sTrappe,int zdAfficher){//O(S2)
	//calcule et affiche si bAfficher le plus large chemin de sSource à sTrappe, (algo:Dijkstra sans tas)
	int bChemine=0,nLargeur;
	Assert1("bGrapheCheminerAuLarge",bCroit(0,zdAfficher,2));
	//d3(sSource,sTrappe,tAfficher);
	nLargeur=nGrapheCheminerAuLargE(pgG,zdAfficher>1,sSource,sTrappe);
	bChemine=bGrapheCheminE(pgG,sSource,sTrappe);
	if (zdAfficher!=0)
		GrapheCheminE(pgG,sSource,sTrappe,bChemine,zdAfficher,nLargeur,echPlusLargE);
	return(bChemine);
}//bGrapheCheminerAuLarge

int nGrapheCheminerAuLargE(graf *pgG,int bSimuler,int sSource,int sTrappe){//O(S2)
	//calcule le plus large chemin de sSource à sTrappe, (algo:Dijkstra sans tas);le coût d'1 arc est la largeur de l'arc,eg la largeur minimale d'une route.
	#define kbCheminerAuLarge kF
	const int kuInfini=1e5;
	int bFait[1+pgG->nSommetEnTout],iLargeurNouvelle[1+pgG->nSommetEnTout];
	int mLargeurMax;//capacité maximale des chemins qui relient sSource au sommet le plus proche de sSource
	int mLargeur[1+pgG->nSommetEnTout];
	int aK,nLargeurParX,sProche=0,uSommet,sX,sY,sZ;
	if (kbCheminerAuLarge) Appel0("nGrapheCheminerAuLargE");
	//initialiser bFait[], mLargeur[],iLargeurNouvelle[], pgG->nVal[] et pgG->sPer[].
		VecteurRazer(bFait,1,pgG->nSommetEnTout);
		VecteurValuer(mLargeur,1,pgG->nSommetEnTout,-1);
		VecteurValuer(pgG->nVal,1,pgG->nSommetEnTout,kuInfini);
		VecteurRazer(iLargeurNouvelle,1,pgG->nSommetEnTout);//dédié simulation
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);
	iLargeurNouvelle[sSource]=mLargeur[sSource]=kuInfini;//largeur entre le sommet de départ et lui-même
	pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE()
	if (bSimuler)
		printf("Simulation de l'algo de cheminement de Dijkstra pour le calcul du chemin le plus large:\n");
	if (bSimuler)//lister les noms des sommets et initialiser iLargeurNouvelle[]
		for (printf("%s ",flag),sZ=1;sZ<=pgG->nSommetEnTout || !bLigne();sZ++)
			printf("%7s",sEnt2(sZ,0) );
	for (uSommet=1; uSommet<=pgG->nSommetEnTout; uSommet++) {
		if (bSimuler)//afficher le noms du sommet sProche élu et les seules distances qui ont changé
			for (printf("%s%s",flag,(sProche==0)? " ": sEnt2(sProche,0)),sZ=1;sZ<=pgG->nSommetEnTout || !bLigne();iLargeurNouvelle[sZ]=-1,sZ++)
				printf("%7s",(iLargeurNouvelle[sZ]==kuInfini)? "infini": (iLargeurNouvelle[sZ]>=0)? sEntier(iLargeurNouvelle[sZ],7) : "    ." );
		//sProche:=numéro du sommet situé sur la route la plus large qui mène à sSource, ou 0 si aucun nouveau sommet n'est trouvé)
			for (sProche=0,mLargeurMax=-1,sX=1; sX<=pgG->nSommetEnTout; sX++)
				if (!bFait[sX] && mLargeurMax<mLargeur[sX])
					mLargeurMax=mLargeur[sProche=sX];
		//d2(sProche,mLargeurMax);
		sX=sProche;
		if (sX!=0) {//pour tout voisin sY de sX,rectifier nDist[sY] si passer par sX permet de cheminer de sSource à sY par un chemin plus large
			for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; aK++) {
				sY=pgG->sSuk[aK];
				Assert1("GrapheCheminerAuLargE",bCroit(0,pgG->nCout[aK],kuInfini-1));//largeur de l'arc
				nLargeurParX=yMin(mLargeur[sX],pgG->nCout[aK]);
				if ( mLargeur[sY]<nLargeurParX ) {//la route qui relie sSource à sY ne passe pas par sX; elle est moins large que celle qui relie sSource à sY en passant par sX.
					iLargeurNouvelle[sY]=mLargeur[sY]=nLargeurParX;
					//VecteurVoir("iLargeurNouvelle",iLargeurNouvelle,1,pgG->nSommetEnTout);
					pgG->sPer[sY]=sX;//sX est situé sur le chemin le plus large qui relie sY à sSource.
					//d4(sY,sX,nLargeurParX,pgG->nCout[aK]);
				}
			}
			bFait[sX]=kV;
		}
	}//à chaque tour, calculer sProche coûte O(S). Chaque arc étant consulté 1 fois au plus dans "for aK",la complexité au pire vaut sup( O(S*S),O(A) ), dc O(S2)
	if (kbCheminerAuLarge) VecteurVoir("mLargeur",&mLargeur[0],1,pgG->nSommetEnTout);
	if (kbCheminerAuLarge) VecteurVoir("sPer",&pgG->sPer[0],1,pgG->nSommetEnTout);
	if (kbCheminerAuLarge) Appel1("nGrapheCheminerAuLargE");
	return(mLargeur[sTrappe]);
}//nGrapheCheminerAuLargE

int bGrapheCheminerCourt(graf *pgG,int sSource,int sTrappe,int bTas,int zdCheminAfficher,int *pnCheminLg,int *pnComplexiteh){//O(SlgS+A)
	//Algo plus court chemin, Dijkstra sans tas;distances élémentR dans pgG->nCout[].
	int bCheminerCourt=0,nCheminLg;
	Assert1("bGrapheCheminerCourt",bCroit(0,zdCheminAfficher,2));
	//GrapheVoir0("bGrapheCheminerCourt:pgG",pgG,gpCout);
	if (!bTas)
		nCheminLg=nGrapheChemineR(pgG,sSource,sTrappe,zdCheminAfficher,pnComplexiteh);
	else nCheminLg=nGrapheCheminerTaS(pgG,sSource,sTrappe,pnComplexiteh);
	//d(*pnComplexiteh);
	if (zdCheminAfficher>1) ModeCaractere(+1);
	bCheminerCourt=bGrapheCheminE(pgG,sSource,sTrappe);
	if (zdCheminAfficher)
		GrapheCheminE(pgG,sSource,sTrappe,bCheminerCourt,zdCheminAfficher,nCheminLg,echPlusCourT);
	if (zdCheminAfficher>1) ModeCaractere(-1);
	*pnCheminLg=nCheminLg;
	return(bCheminerCourt);
}//bGrapheCheminerCourt

int bGrapheCheminerCourtTaS(graf *pgG,int sSource,int sTrappe,int bCheminAfficher,int *pnComplexiteh){//O(S2)
	//Algo plus court chemin, Dijkstra AVEC tas;distances élémentR dans pgG->nCout[].
	int bCheminerCourt=0,nCheminLg;
	//Appel0("bGrapheCheminerCourtTaS");
		Assert1("bGrapheCheminerCourtTaS",bBool(bCheminAfficher));
		nCheminLg=nGrapheCheminerTaS(pgG,sSource,sTrappe,pnComplexiteh);
		bCheminerCourt=bGrapheCheminE(pgG,sSource,sTrappe);
		if (bCheminAfficher)
			GrapheCheminE(pgG,sSource,sTrappe,bCheminerCourt,bCheminAfficher,nCheminLg,echPlusCourT);
	//Appel1("bGrapheCheminerCourtTaS");
	return(bCheminerCourt);
}//bGrapheCheminerCourtTaS

int nGrapheCheminerLonG(graf *pgG,int sSource,int sTrappe,int zdAfficher){//O(A)
	//rend ds pgG->nVal[] la longueur du plus long chemin (qui équivaut à la date au plus tôt).
	const int kbVoir=kF;
	int uNiveau[1+pgG->nSommetEnTout],uSuivant[1+pgG->nSommetEnTout],iSimulatO[1+pgG->nSommetEnTout];
	int nDateParX,aK,sX,sY,sZ;
	int kuInfini=kE7;
	int sProche=0,bSimuler=zdAfficher>1;
	//Voir("%d",zdAfficher);
	int kuLg=7;
	if (kbVoir) Appel0("nGrapheCheminerLonG");
	//uNiveau[],uSuivant[]:=niveaux topologiques, suite des sommets triés par niveau;en 1er,car écrase pgG->nVal[]
		bGrapheTrierTopologiquement(pgG,!k1Afficher);//O(A);résultat dans pgG->nVal[]
		pgG->nVal[0]=pgG->nSommetEnTout;
		VecteurCopier(pgG->nVal,1,pgG->nSommetEnTout,uNiveau);
		VecteurTrier2(uNiveau,1,pgG->nSommetEnTout,uSuivant);//O(S)
	//initialiser pgG->nVal[] et pgG->sPer[].
		VecteurRazer(pgG->nVal,1,pgG->nSommetEnTout);//dates au plus tôt
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);
		pgG->nVal[sSource]=0;//distance entre le sommet de départ et lui-même
		pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE()
		if (bSimuler) VecteurRaz(iSimulatO,pgG->nSommetEnTout);
		if (bSimuler) VecteurValuer(iSimulatO,1,pgG->nSommetEnTout,kuInfini);
	//VecteurVoir("uNiveau",uNiveau,1,pgG->nSommetEnTout);
	//initialiser les successeurs de sSource
		for (aK=pgG->aHed[sSource]; aK<pgG->aHed[sSource+1]; aK++){//O(S)
			sY=pgG->sSuk[aK];
			pgG->nVal[sY]=pgG->nCout[aK];
			pgG->sPer[sY]=sSource;//sX est situé sur le chemin le plus critique qui relie sY à sSource.
		}
	//b(bSimuler);
	if (bSimuler){//lister les noms des sommets et la 1ère ligne de la simulation
		printf("%sSimulation de l'algo de cheminement de Dijkstra pour le calcul du chemin optimal de %s à %s:\n",sTab0(),sEnt(1),sEnt(pgG->nSommetEnTout));
		Tabuler(1);
		for (printf("%s ",sTab0()),sZ=1;sZ<=pgG->nSommetEnTout || bPrint("");sZ++)
			printf("%s%s",sE(kuLg-1),sEnt2(sZ,0) );//noms des sommets
	}
	for (int uSommet=1;uSommet<=pgG->nSommetEnTout; uSommet++) {//O(A)
		sProche=sX=uSuivant[uSommet];
		//pr tt voisin sY de sX, modifier pgG->nVal[sY] si passer par sX retarde la date au plus tôt de sY 
			for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; aK++) {
				sY=pgG->sSuk[aK];//pr info
				nDateParX=pgG->nVal[sX]+pgG->nCout[aK];
				if ( pgG->nVal[sY]<nDateParX ) {//pgG->nVal[sY] est moins tôt 
					pgG->nVal[sY]=nDateParX;
					pgG->sPer[sY]=sX;//sX est situé sur le chemin le plus critique qui relie sY à sSource.
				}
			}
		if (bSimuler)//afficher le nom du sommet sProche élu et les seules distances qui ont changé
			for (ModeCaractere(+1),printf("%s%s",sTab0(),sEnt(sProche)),ModeCaractere(-1),sZ=1;sZ<=pgG->nSommetEnTout || !bLigne();sZ++)
				if ( iSimulatO[sZ]!=pgG->nVal[sZ])
					printf("%s",(pgG->nVal[sZ]==kuInfini)? " infini" : sEnt2(pgG->nVal[sZ],kuLg));
				else printf("%s%c",sE(kuLg-1),'"');
		if (bSimuler)
			VecteurCopier0(pgG->nVal,iSimulatO);
	}
	if (bSimuler)
		Tabuler(-1);
	if (kbVoir) VecteurVoir1("sPer",&pgG->sPer[0],1,pgG->nSommetEnTout);
	if (kbVoir) Appel1("nGrapheCheminerLonG");
	return(pgG->nVal[sTrappe]);
}//nGrapheCheminerLonG

int bGrapheCheminerLong(graf *pgG,int sSource,int sTrappe,int zdCheminAfficher,int *pnComplexiteh){//O(S2)
	//vrai ssi un + long chemin de sSource à sTrappe est calculable ds pgG (pondérateur: gpCout).
	int bCheminerLong=kV,nCheminLg;
	if ( !bGrapheSymetrique(pgG) ){
		GrapheInverser(pgG);
		bCheminerLong=!bGrapheCircuite(pgG,!k1Afficher);
		if (bCheminerLong){
			nCheminLg=nGrapheCheminerLonG(pgG,sSource,sTrappe,zdCheminAfficher);
			bCheminerLong=bGrapheCheminE(pgG,sSource,sTrappe);
			if (zdCheminAfficher)
				GrapheCheminE(pgG,sSource,sTrappe,bCheminerLong,zdCheminAfficher,nCheminLg,echPlusLonG);
		}
		else if (zdCheminAfficher)
			printf("\t Le calcul du plus long chemin quand G contient un circuit %s",nada);
	}else if (zdCheminAfficher)
		printf("\t Le calcul du plus long chemin sur G non orienté (1 arête=2 arcs opposés=1 circuit) %s",nada);
	return(bCheminerLong);
}//bGrapheCheminerLong

int nGrapheCheminerTaS (graf *pgG,int sSource,int sTrappe,int *pnComplexiteh){//O(AlgS)
	//rend le plus court chemin qui relie sSource à sTrappe; distances élémentR dans pgG->nCout[]. Algo de plus court chemin exécuté: Dijkstra AVEC tas.
	const int kuInfini=kE6-1;//comme dans le Tas
	int nDist[1+pgG->nSommetEnTout];
	int nDistanceParX;//entier Naturel positif ou nul,donc préfixe "n".
	int bFait[1+pgG->nSommetEnTout];//b comme booléen
	int aK;//index d'Arc,donc préfixe "a".
	int sProche;//index de Sommet,donc préfixe "s".
	int uSommet;//entier naturel supérieur ou égal à Un,donc préfixe "u".
	int nActualisation,sX,sY;
	//bFait[], nDist[] et pgG->sPer[] soient initialisés.
		VecteurRazer(bFait,1,pgG->nSommetEnTout);
		VecteurValuer(nDist,1,pgG->nSommetEnTout,kuInfini);
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);
	*pnComplexiteh=3*pgG->nSommetEnTout;//coût initialisations
	TasAllouer(pgG->nSommetEnTout);
		//initialiser le tas (le coût total du module Tas, en terme de complexité algorithmique, sera ajouté en fin de routine grâce à nTasCout() 
			for (sX=1; sX<=pgG->nSommetEnTout; sX++)
				TasInsererValuer(sX,kuInfini);
			TasActualiser(sSource,0);
			//TasVoir("Tas après initialisation");
		nDist[sSource]=0;//distance entre le sommet de départ et lui-même
		pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE() chargé de cheminer sur le plus court chemin grâce à sPer[]
		for (nActualisation=0,uSommet=1; uSommet<=pgG->nSommetEnTout; (*pnComplexiteh)++, uSommet++) {//O(AlgS)
			//sProche:=numéro du sommet le plus proche de sSource, ou 0 si sSource ne mène à aucun nouveau sommet par un chemin quelconque)
				//TasVoir("Tas avant extraction");
				sProche=eTasExtraire();//O(lgS)
			sX=sProche;
			if (sX!=0) {
				for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; (*pnComplexiteh)++, aK++) {
					sY=pgG->sSuk[aK];//chaque arc (sX,sY) est examiné 1 fois (si accessible par un chemin depuis sSource)
					nDistanceParX=nDist[sX]+pgG->nCout[aK];
					if ( nDist[sY]>nDistanceParX ) {
						nDist[sY]=nDistanceParX;
						//d2(sY,nDistanceParX);
						//if (bVoir) d4(sX,sY,nDistanceParX,nModif);
						TasActualiser(sY,nDistanceParX);//O(lgS) pr chq arc (sX,sY) à actualiser
						nActualisation++;
						//TasVoir("Tas après TasActualiser");
						pgG->sPer[sY]=sX;
					}
				}
				bFait[sX]=kV;//ie l'opportunité de passer par sX pour atteindre au plus court un sommet de pgG depuis sSource a été exploitée.
			}
		}//chaque sProche est obtenu en O(lgS) et chaque arc est accédé 1 fois, soit une complexité au pire égale à sup( O(S*lS),O(AlgS) ), dc O(AlgS).
		//VecteurVoir("sPer",pgG->sPer,1,pgG->nSommetEnTout);
		(*pnComplexiteh)+=nTasCout();//coût total du tas entre 2 allocations, donc à ajouter juste avant TasAllouer(0) qui remet ce coût à 0.
		Assert1("nGrapheCheminerTaS99",*pnComplexiteh>0);
		//Ligne();s(sPluriel(nActualisation,"actualisation"));
	TasAllouer(0);
	return(nDist[sTrappe]);
}//nGrapheCheminerTaS

int bGrapheCircuite(graf *pgG,int bAfficher){//O(A)
	//vrai ssi pgG contient un circuit (algo de Marimont)
	int kbVoir=0;
	int nCard;//n comme Naturel,dc 0 ou plus
	int bCircuite=kF;
	int uE;//E comme Elément;u comme Un ou plus
	int aK;//a comme Arc
	int nMarque;
	int nMarq[1+pgG->nSommetEnTout],nPred[1+pgG->nSommetEnTout],nSucc[1+pgG->nSommetEnTout];
	int sX,sY;//s comme Sommet
	if (kbVoir) Appel0("bGrapheCircuite");
		//GrapheVoir0("bGrapheCircuite0:pgG",pgG,gpCout);
		Assert2("bGrapheCircuite1",bGrapheAmorceR,bCroit(1,pgG->nSommetEnTout,kuGrapheSommetLim));
		GrapheInverser(pgG);//VITAL
		if (pgG->nSommetEnTout>1){//algo de MARIMONT
			//nSucc[sX],nPred[sX] et nMarq[sX] soit le nombre total de successeurs,de prédécesseurs ainsi que la marque du sommet courant sX
				for (sX=1;sX<=pgG->nSommetEnTout;sX++){//O(S)
					nSucc[sX]=pgG->aHed[sX+1]-pgG->aHed[sX];
					nPred[sX]=pgG->aDeh[sX+1]-pgG->aDeh[sX];
					nMarq[sX]=0;//ie sX n'est pas marqué
					pgG->sPer[sX]=0;
					Assert2("bGrapheCircuite2",nSucc[sX]>=0,nPred[sX]>=0);
				}
			DequeAllouer(pgG->nSommetEnTout);//raze;O(nSommetEnTout)
				//enfiler les sommets sources (ie sans prédécesseurs) et trappes (ie sans successeurs) en les marquant avec nMarque égal à 1
					for (nMarque=1,sX=1;sX<=pgG->nSommetEnTout;sX++)
						if ( !nPred[sX] || !nSucc[sX] ){
							nMarq[sX]=nMarque;
							pgG->sPer[sX]=sX;
							DequeEnfiler(sX);//O(1)
						}
				While(pgG->nSommetEnTout);
				while (bWhile("bGrapheCircuite3",(nMarque++,nCard=nDequeCardinal())) ){//nDequeCardinal() est en O(1) et le while en O(A) ——justification en fin de while
					for (uE=1;uE<=nCard;uE++){//NB les appels à la deque ds ce for vont modifier nDequeCardinal() mais pas nCard évalué li-1 
						sX=sDequeDefiler();//O(1)/
						if (!nPred[sX])//si vrai,sX est une source;éliminer un arc (sX,sY),c'est retirer un prédécesseur de sY via "nPred[sY]--"
							for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){//O(degré sortant de sX)
								if (!nMarq[sY=pgG->sSuk[aK]]){
									nPred[sY]--;
									Assert1("bGrapheCircuite4",nPred[sY]>=0);
									if (!nPred[sY]){ //enfiler sY après l'avoir marqué;parce qu'il est marqué,il ne pourra être enfilé à nouveau
										nMarq[sY]=nMarque;
										pgG->sPer[sY]=sX;
										DequeEnfiler(sY);//O(1)
									}
								}
							}
						else for (aK=pgG->aDeh[sX];aK<pgG->aDeh[sX+1];aK++)//O(degré entrant de sX)
								if (!nMarq[sY=pgG->sKus[aK]]){
									nSucc[sY]--;
									Assert1("bGrapheCircuite5",nSucc[sY]>=0);
									if (!nSucc[sY]){ //enfiler sY après l'avoir marqué;parce qu'il est marqué,il ne pourra être enfilé à nouveau
										nMarq[sY]=nMarque;
										pgG->sPer[sY]=sX;
										DequeEnfiler(sY);//O(1)
									}
								}
					}//grâce à nMarq[],tt sommet est enfilé (et dc défilé) 1 fois Au plus, dc ses arcs examinés 1 fois Au plus,dc while est en O(A).
				}
			DequeAllouer(0);//O(1) Si vous ôtez cette ligne au vu du code de Deque,vous acceptez qu'une modification dudit code plante votre logiciel.
			//VecteurVoir("nMarq",nMarq,1,pgG->nSommetEnTout);
			for (bCircuite=0,sX=1; sX<=pgG->nSommetEnTout; sX++)//O(S);zéroter bCircuite ici initialise à l'évidence le bCircuite situé li+1 avant "||".
				bCircuite=bCircuite || !nMarq[sX];//quitter le for dès que bCircuite est vrai complique le code et n'améliore pas la borne O(A):mauvaise idée.
			}
		else bCircuite=kF;//redite,mais ainsi,li+1,bCircuite est à l'évidence valué; chercher sa valeur initiale ds les déclarations est inutile,dc gain de temps.
		if (bAfficher)
			printf("%sCe graphe %s circuit.\n",flag,(bCircuite)? "contient un" : "ne contient pas de");
	if (kbVoir) Appel1("bGrapheCircuite");
	return(bCircuite);//NB: cet algorithme décide l'existence d'un circuit en temps O(A) mais ne permet pas d'exhiber un quelconque circuit.
}//bGrapheCircuite

void GrapheCircuiterAuMieux(graf *pgG){
	//calcule et affiche un circuit de longueur moyenne minimale (moyennée sur le nombre d'arcs) dans pgG,réputé fortement connexe.
	const int kbAff = kF;
	const int kuPoidsInfini=kE4;
	int aK,nK,nK0,uK,aL,nMin,nPoidsTotal,sX,sY,sY0,sZ;
	float rMin,rMax,rMoyenne;
	int nSommet=pgG->nSommetEnTout;
	int nPoids[1+nSommet][1+nSommet];
	int sPere[1+nSommet][1+nSommet];
	Assert1("GrapheCircuiterEnMoyennE",bGrapheFortementConnexe(pgG));
	//les poids sont les couleurs du graphe
		for (aK=1;aK<=pgG->nArcEnTout;aK++)
			pgG->nPoids[aK]=pgG->coulh[aK];
	//nPoids[0][] soit initialisé
		GrapheInverser(pgG);//pr accéder en O(1) aux prédécesseurs
		for (sX=1;sX<=nSommet;sX++)
			nPoids[0][sX]=kuPoidsInfini;
		nPoids[0][1]=0;
		for (sY=1;sY<=nSommet;sY++)
			for (aL=pgG->aDeh[sY];aL<pgG->aDeh[sY+1];aL++){
				sX=pgG->sKus[aL];
				aK=pgG->aInv[aL];
				if (sX==1)
					nPoids[0][sY]=pgG->nPoids[aK];
			}//for aL
	//nPoids[1..nSommet][] et sPere[1..nSommet][] soient affectés:
		for (uK=1;uK<=nSommet;uK++)
			for (sY=1;sY<=nSommet;sY++){
				for (nMin=kuPoidsInfini,aL=pgG->aDeh[sY];aL<pgG->aDeh[sY+1];aL++){
					sX=pgG->sKus[aL];
					aK=pgG->aInv[aL];
					nPoidsTotal=nPoids[uK-1][sX]+pgG->nPoids[aK];
					if (nPoidsTotal<nMin){
						nMin=nPoidsTotal;
						sZ=sX;//pour sPere li+4
					}
				}//for aL
				nPoids[uK][sY]=nMin;
				sPere[uK][sY]=sZ;
			}
		if (kbAff) for (nK=0;nK<=nSommet;nK++)
			VecteurVoir(sC3("nSommet[",sEnt(nK),"]"),nPoids[nK],1,nSommet);
		if (kbAff) for (uK=1;uK<=nSommet;uK++)
			VecteurVoir(sC3("sPere[",sEnt(uK),"]"),sPere[uK],1,nSommet);
	//sY0,nK0:=index caractéristiques du circuit optimal
		for (rMin=kuPoidsInfini,sX=1;sX<=nSommet;sX++){
			for (sY=0,rMax=0.0,nK=0;nK<nSommet;nK++){
				rMoyenne=((nPoids[nSommet][sX]-nPoids[nK][sX])*1.0)/(nSommet-nK);
				if (rMoyenne>rMax){
					sY=sX;
					uK=nK;
					rMax=rMoyenne;
				}
			}
			if (rMax<rMin){
				sY0=sY;
				nK0=uK;
				rMin=rMax;
			}
		}
	//tr("rMin",rMin);
	//teee("moyenne de 1 pour sY0,nPoidsTotal0,nArc0",sY0,nPoidsTotal0,nArc0);
	//afficher le circuit optimal de longueur moyenne minimale:
		printf("Circuit optimal: ( ");
			for (uK=nSommet-1,sX=sPere[uK][sY0];uK>=nK0;printf("%d ",sX),uK--)
				sX=sPere[uK][sX];
		printf("), de longueur moyenne minimale égale à %.2f.\n",rMin);
}//GrapheCircuiterAuMieux

void GrapheCliquer(graf *pgG,int uCliqueTaille){
	//empile dans pgG une clique à uCliqueTaille sommets.
	int sX,sY;
	const int kbVerif = kF;
	Assert1("GrapheCliquer",uCliqueTaille>0);
	int nSommet=pgG->nSommetEnTout;
	//d(nSommet);
	for (sX=1;sX<=uCliqueTaille;sX++)
		pgG->aHed[nSommet+sX+1]=pgG->aHed[nSommet+sX];
	pgG->nSommetEnTout+=uCliqueTaille;
	if(kbVerif) d(pgG->nSommetEnTout);
	if(kbVerif) VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout+1);
	for (sX=nSommet+1;sX<=pgG->nSommetEnTout;sX++)
		for (sY=nSommet+1;sY<=pgG->nSommetEnTout;sY++)
			if (sX!=sY)
				GrapheArquer(pgG,sX,sY);
	if(kbVerif) VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout+1);
	if(kbVerif) VecteurVoir("pgG->sSuk",pgG->sSuk,1,pgG->nArcEnTout);
}//GrapheCliquer

void GrapheColorer(graf *pgG,int sOrigine,int sDestination,int nCouleur){
	//colore l'arc (sOrigine,sDestination) avec la nCouleur
	int aK;
	//d2(sOrigine,sDestination);
	Assert4("GrapheColorer0",bGrapheSommet(pgG,sOrigine), bGrapheSommet(pgG,sDestination), sOrigine!=sDestination, bCroit(0,nCouleur,knGrapheCouleurMax));
	for (aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++){
		if (pgG->sSuk[aK] == sDestination)
			pgG->coulh[aK]=nCouleur;
	}
}//GrapheColorer

int nGrapheColorier(graf *pgG,int zdAfficher) {//O(S2)
	//calcule, et affiche si zdAfficher, 1 colorO quasi-optimale des sommets et stocke le résultat ds pgG->nVal[]. 
	int bVoir=0;
	int aK,aL,sX,sY,uCouleur,uCouleurEnTout=0,mDegrehMax,nItem,nItemEnTout,sMax,uSommet,uSommetEnTout;
	Assert1("nGrapheColorier0",bGrapheSimple(pgG));
	if (bGrapheSymetrique(pgG)){
		graf *pgH=(graf *) malloc(sizeof(graf));
			GrapheDupliquer(pgG,&pgH);
			GrapheInverser(pgH);//O(A)
			GraphePondererTout(pgH,gpPoids,1);
			if (bVoir && zdAfficher) GrapheVoir0("pgH AVANT coloriage",pgH,gpPoids);
				DequeAllouer(uSommetEnTout=pgH->nSommetEnTout);//O(S)
					int sPile[1+uSommetEnTout];
					int nCouleur[1+uSommetEnTout],bColoris[1+uSommetEnTout],nDegreh[1+uSommetEnTout];
					//décstruire pgH virtuellt en empilant chq fois le sommet de + haut degré et en négativant ts ses arcs incidents
						for (uSommet=1;uSommet<=uSommetEnTout;uSommet++){//O(S2)
							//nDegreh[]:=degré virtuel de chq sommet; li+1, VecteurRaz coûte O(S)
								for (VecteurRaz(nDegreh,uSommetEnTout),sX=1;sX<=uSommetEnTout;sX++)
									for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++)
										nDegreh[sX]+=(pgH->nPoids[aK]>0);
								if (0 || bVoir) {ModeCaractere(0);VecteurVoir0("nDegreh",nDegreh);ModeCaractere(1);};
							//sMax:=sommet de + haut degré virtuel
								for (mDegrehMax=-1,sMax=0,sX=1;sX<=uSommetEnTout;sX++)//O(S)
									if (!bDequeContient(sX) && mDegrehMax<nDegreh[sX])//nécessrt vrai un jour vu mDegrehMax<0 et...
										mDegrehMax=nDegreh[sMax=sX];//...nDegreh[sX]≥0, dc un n° de sommet sera copié dans sMax.
							if (bVoir) d(sMax);
							///retirer virtuellt les arcs incidents à sMax en négativant leurs poids réputés non nuls
								for (aK=pgH->aHed[sMax];aK<pgH->aHed[sMax+1];aK++){
									if (pgH->nPoids[aK]>0) pgH->nPoids[aK]=-pgH->nPoids[aK];//arcs sortants
									aL=pgH->aInv[aK];
									if (pgH->nPoids[aL]>0) pgH->nPoids[aL]=-pgH->nPoids[aL];//arcs entrants
								}
							DequeEmpiler(sMax);
						}//for uSommet
					Assert1("nGrapheColorier55",iVecteurMax(pgH->nPoids,1,pgH->nArcEnTout)<0);//O(A) ts les poids ont été négativés
					if (bVoir && zdAfficher) DequeVoir("finale:");
					//recstruire pgH virtuellt; ds nCouleur[], attribuer à chq sommet une couleur distincte de celle de ses voisins 
						for (VecteurRaz(nCouleur,uSommetEnTout),uSommet=1;uSommet<=uSommetEnTout;uSommet++){//O(S2)
							//bColoris[]:=une coche par couleur utilisée par sommet adjacent à sX=sDequeDepiler()
								for (VecteurRaz(bColoris,uSommetEnTout),sX=sPile[uSommetEnTout-uSommet+1]=sDequeDepiler(),aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++)
									if (nCouleur[sY=pgH->sSuk[aK]]>0)//sY est dc un sommet déjà coloré
										bColoris[nCouleur[sY]]=1;
							//nCouleur[sX]:=une couleur que n'ont pas les voisins de sX
								for (sY=1;sY<=uSommetEnTout && !nCouleur[sX];sY++)//O(S)
									if (!bColoris[sY])
										nCouleur[sX]=sY;
							///restaurer virtuellt les arcs incidents à sX en restaurant leurs poids
								for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++){
									if (pgH->nPoids[aK]<0) pgH->nPoids[aK]=-pgH->nPoids[aK];//arcs sortants
									aL=pgH->aInv[aK];
									if (pgH->nPoids[aL]<0) pgH->nPoids[aL]=-pgH->nPoids[aL];//arcs entrants
								}
						}//for uSommet
						sPile[0]=uSommetEnTout;
				DequeAllouer(0);//O(1)
			if (bVoir && zdAfficher) GrapheVoir0("pgG APRÈS coloriage",pgG,gpPoids);
			uCouleurEnTout=iVecteurMax(nCouleur,1,uSommetEnTout);//O(S)
			if (zdAfficher)
				printf("\tLa coloration optimale des sommets du graphe peut être réalisée avec %s:\n",sPluriel(uCouleurEnTout,"couleur"));
			if (zdAfficher==2) printf("%sPile générée par l'heuristique, en commençant par le fond de pile: %s.\n",flag,sListe(sPile,'&'));
			if (zdAfficher)//afficher, couleur par couleur, la liste des variables qui ont la mm couleur ——grâce au tableau nCouleur[]
				for (uCouleur=1;uCouleur<=uCouleurEnTout;uCouleur++){
					nItemEnTout=nVecteurOccurrence(uCouleur,nCouleur,1,uSommetEnTout);//nb de sommets de couleur uCouleur, pr sEtc() li+3.
					for (printf("\t\tCouleur n°%d: ",uCouleur),nItem=0,sX=1;sX<=uSommetEnTout || bPrint(".");sX++)
						if (nCouleur[sX]==uCouleur)
							printf("%s%s",sEnt(sX),sEtc(++nItem,nItemEnTout));
				}
			VecteurCopier(nCouleur,1,uSommetEnTout,pgG->nVal);
			if (0 && zdAfficher==2){
				//ModeCaractere(0);
					Flag(1);
						VecteurVoir1("pgG->nVal",pgG->nVal,1,uSommetEnTout);
					Flag(0);
				//ModeCaractere(-1);
			}
		free(pgH);
	}else printf("\tLe calcul d'une coloration de sommets n'est pas défini sur un graphe orienté.\n");
	return(uCouleurEnTout);
}//nGrapheColorier

void GrapheCompletCreerPondereR(int nSommet,graf **ppgG){
	int aK,sX,sY;
	//appel: DijkstraAvecOuSansTasCompareR()
	//Appel0("GrapheCompletCreerPondereR");
		GrapheCreer(nSommet,ppgG);
		for (sX=1;sX<=nSommet;sX++)
			for (sY=1;sY<=nSommet;sY++)
				if (sX!=sY)
					GrapheArquer(*ppgG,sX,sY);
		//GrapheVoir(pgG,"Graphe complet créé",*ppgG);
		Assert1("GrapheCompletCreerPondereR1",bGrapheSimple(*ppgG));
		for (sX=1;sX<=nSommet;sX++)
			for (aK=(*ppgG)->aHed[sX];aK<(*ppgG)->aHed[sX+1];aK++){
				sY=(*ppgG)->sSuk[aK];
				(*ppgG)->nCout[aK]=kE4-sX-nSommet*sY;
			}
		Assert1("GrapheCompletCreerPondereR4",bGrapheSimple(*ppgG));
		//si nSommet=6, faire que les plus courts chemins passent par les arcs (1,6),(6,5),(5,4),(4,3),(3,2) et (2,1)
			for (sX=1;sX<=nSommet;sX++)
				for (aK=(*ppgG)->aHed[sX];aK<(*ppgG)->aHed[sX+1];aK++){
					sY=(*ppgG)->sSuk[aK];
					if (sY==sX-1 || sX==1 && sY==nSommet)
						(*ppgG)->nCout[aK]=sX;
				}
		Assert1("GrapheCompletCreerPondereR4",bGrapheSimple(*ppgG));
	//Appel1("GrapheCompletCreerPondereR");
}//GrapheCompletCreerPondereR

int nGrapheComposanteConnexE(graf *pgG){//O(A)
	//rend le nombre de composantes connexes du graphe non orienté associé à pgG et stocke le n° de composante ds pgG->sPer[] 
	int nCC[1+pgG->nSommetEnTout];//numéro de composante connexe
	int nCCcourante,nComposanteConnexe=0;
	graf *pgH;
	int aK,sX,sY,sZ,uS;
	pgH=(graf *) malloc(sizeof(graf));
		//pgH soit le graphe symétrique associé à pgH
			GrapheDupliquer(pgG,&pgH);//O(A)
			GrapheSymetriser(pgH,gpCouleur+gpCout);//O(A)
		VecteurRazer(nCC,1,pgG->nSommetEnTout);//O(S)
		DequeAllouer(pgG->nSommetEnTout);//O(1)
			for (nCCcourante=0,sZ=1;sZ<=pgG->nSommetEnTout;sZ++)//O(A)
				if (nCC[sZ]==0){//attribuer la composante connexe nCCcourante+1 à sZ et aux sommets atteints depuis sZ dans pgH symétrique 
					DequeEnfiler(sZ);//sZ n'est enfilé qu'une fois
					nCCcourante++;
					While(1+pgH->nSommetEnTout);
					while (bWhile("nGrapheComposanteConnexE",!bDequeVide())){
						for (uS=1;uS<=nDequeCardinal();uS++){
							sX=sDequeDefiler();
							nCC[sX]=nCCcourante;
							for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++){//les successeurs de sY ne sont passés en revue qu'une fois
								sY=pgH->sSuk[aK];
								if (nCC[sY]==0)//sY n'est enfilé qu'une fois
									DequeEnfiler(sY);
							}
						}//for uS
					}//while
				}//if
		DequeAllouer(0);//O(1)
	free(pgH);
	nComposanteConnexe=nCCcourante;
	//d(nComposanteConnexe);
	VecteurCopier(nCC,1,pgG->nSommetEnTout,pgG->sPer);//O(S)
	return(nComposanteConnexe);
}//nGrapheComposanteConnexE

int nGrapheComposanteConnexe(char *sQuoi,graf *pgG,int zdAfficher){//O(A)
	Assert2("nGrapheComposanteConnexe",bGrapheAmorceR,bGrapheSimple(pgG));
	int uCC,cPasse,nOccurrence,nCardinal,nComposante=0,sX;
	//int bVoir=nChaineLg(sQuoi)>0;
	nComposante=nGrapheComposanteConnexE(pgG);
	if (zdAfficher) printf("\t%s a %s: ",sQuoi,sPluriel(nComposante,"composante$ connexe$") );
	for (uCC=1;uCC<=nComposante;uCC++){
		if (zdAfficher) printf("{");
			for (cPasse=0;cPasse<=1;cPasse++){
				for (nOccurrence=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
					if (pgG->sPer[sX]==uCC){
						nOccurrence++;
						if (cPasse==1 && zdAfficher)
							printf("%s%s",sEnt(sX),(nOccurrence<nCardinal)? ",":"");
					}
				nCardinal=nOccurrence;
			}
		if (zdAfficher) printf("}");
		if (zdAfficher) printf("%s",sEtc1(uCC,nComposante));
	}
	if (zdAfficher) Ligne();
	if (zdAfficher>1)
		printf("%sLe graphe est toujours considéré non orienté.\n",flag);
	return(nComposante);
}//nGrapheComposanteConnexe

int nGrapheComposanteFortementConnexE(graf *pgFortementConnexe){//O(SA)
	//rend le nbre de composantes fortement connexes (CFC) de pgG et stocke dans pgG->sPer[] le numéro de CFC attribué à chq sommet. 
	int bAtteint[2][1+pgFortementConnexe->nSommetEnTout];
	int nCFC[1+pgFortementConnexe->nSommetEnTout];//numéro de composante fortement connexe attribué au sommet courant
	int nCFCcourante;
	int nComposanteFortementConnexe=0;
	graf *pgG=pgFortementConnexe;
	int aK,sX,sY,sZ,uS;
	int cPasse,bVoir = 0;
	Assert2("nGrapheComposanteFortementConnexE",bGrapheAmorceR,bGrapheSimple(pgG));
	GrapheInverser(pgG);//mm si déjà fait
	//GrapheScruter("Graphe inversé",pgG,+1,0);
	VecteurRazer(nCFC,1,pgG->nSommetEnTout);//O(S)
	DequeAllouer(1+pgG->nSommetEnTout);//O(1)
		for (nCFCcourante=0,sZ=1;sZ<=pgG->nSommetEnTout;sZ++)//S*sup(S,A),dc O(SA)
			if (nCFC[sZ]==0){//marquer parmi tous les sommets atteints depuis sZ dans pgG ceux qui mènent à sZ dans le graphe inversé de pgG
				//if (bVoir) d(sZ);
				VecteurRazer(bAtteint[0],1,pgG->nSommetEnTout);//O(S)
				VecteurRazer(bAtteint[1],1,pgG->nSommetEnTout);//O(S)
				for (cPasse=0;cPasse<=1;cPasse++){//cPasse=0: accès au graphe direct;cPasse=1: accès au graphe inversé (champs aDeh et sKus)
					DequeRazer(1+pgG->nSommetEnTout);
					DequeEnfiler(sZ);
					While(1+pgG->nSommetEnTout);
					while (bWhile("nGrapheComposanteFortementConnexE",!bDequeVide())){//O(A)
						for (uS=1;uS<=nDequeCardinal();uS++){
							sX=sDequeDefiler();
							bAtteint[cPasse][sX]=nCFCcourante+1;
							//if (bVoir) tee("cPasse,sX défilé",cPasse,sX);
							for (aK=(cPasse==0)? pgG->aHed[sX]: pgG->aDeh[sX];(cPasse==0)? aK<pgG->aHed[sX+1]: aK<pgG->aDeh[sX+1];aK++){
								sY=(cPasse==0)? pgG->sSuk[aK]: pgG->sKus[aK];
								if (!bAtteint[cPasse][sY])
									DequeEnfiler(sY);
							}
						}//for uS
					}//while
				}//for cPasse
			if (bVoir) VecteurVoir("bAtteint0",bAtteint[0],1,pgG->nSommetEnTout);
			if (bVoir) VecteurVoir("bAtteint1",bAtteint[1],1,pgG->nSommetEnTout);
			for (nCFCcourante++,sX=1;sX<=pgG->nSommetEnTout;sX++)
				if (bAtteint[0][sX] && bAtteint[1][sX])
					nCFC[sX]=nCFCcourante;
		}
	DequeAllouer(0);//O(1)
	if (bVoir) VecteurVoir("Numéro de composante attribuée à chaque sommet",nCFC,1,pgG->nSommetEnTout);
	VecteurCopier(nCFC,1,pgG->nSommetEnTout,pgG->sPer);
	nComposanteFortementConnexe=nCFCcourante;
	if (bVoir) d(nComposanteFortementConnexe);
	return(nComposanteFortementConnexe);
}//nGrapheComposanteFortementConnexE

int nGrapheComposanteFortementConnexe(char *sQuoi,graf *pgG,int zdAfficher){//O(A)
	int uCC,cPasse,nOccurrence,nCardinal,nComposante=nGrapheComposanteFortementConnexE(pgG),sX;
	//int bVoir=nChaineLg(sQuoi)>0;
	if (zdAfficher) printf("\t%s a %s: ",sQuoi,sPluriel(nComposante,"composante$ fortement connexe$") );
	for (uCC=1;uCC<=nComposante;uCC++){
		if (zdAfficher) printf("{");
			for (cPasse=0;cPasse<=1;cPasse++){
				for (nOccurrence=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
					if (pgG->sPer[sX]==uCC){
						nOccurrence++;
						if (cPasse==1 && zdAfficher)
							printf("%s%s",sEnt(sX),(nOccurrence<nCardinal)? ",":"");
					}
				nCardinal=nOccurrence;
			}
		if (zdAfficher) printf("}");
		if (zdAfficher) printf("%s",sEtc1(uCC,nComposante));
	}
	if (zdAfficher) Ligne();
	if (zdAfficher>1)
		printf("%sLe graphe est toujours considéré orienté.\n",flag);
	return(nComposante);
}//nGrapheComposanteFortementConnexe

void GrapheConnecter(graf *pgG,int bArete,int sOrigine,int sDestination){//O(A)
	//ajoute l'arête ou l'arc (sOrigine,sDestination) à pgG ——affecte les champs désignés par nGenreDePoids ainsi que nArcEnTout,aHed,sSuk. Déroute si échec.
	GrapheArquer(pgG,sOrigine,sDestination);
	if (bArete)
		GrapheArquer(pgG,sDestination,sOrigine);
}//GrapheConnecter

void GrapheConnecter0(graf *pgG,int bArete,int sOrigine,int sDestination,int nGenreDePoids,int iPoidsSurArc){//O(A)
	//ajoute l'arête ou l'arc (sOrigine,sDestination) à pgG ——affecte les champs désignés par nGenreDePoids ainsi que nArcEnTout,aHed,sSuk. Déroute si échec.
	Assert1("GrapheConnecter0",bGrapheAttribuT(nGenreDePoids));
	GrapheArquer0(pgG,sOrigine,sDestination,nGenreDePoids,iPoidsSurArc);
	if (bArete)
		GrapheArquer0(pgG,sDestination,sOrigine,nGenreDePoids,iPoidsSurArc);
}//GrapheConnecter0

void GrapheConnecter1(graf *pgG,int bArete,int sOrigine,int sDestination,int nCouleur){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	Assert1("GrapheConnecter1",sOrigine!=sDestination);
	GrapheConnecter0(pgG,bArete,sOrigine,sDestination,gpCouleur,nCouleur);
}//GrapheConnecter1

void GrapheConnecter2(graf *pgG,int sOrigine,int sDestination,int nCouleurDirecte,int nCouleurInverse){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	Assert1("GrapheConnecter2",sOrigine!=sDestination);
	GrapheArquer0(pgG,sOrigine,sDestination,gpCouleur,nCouleurDirecte);
	GrapheArquer0(pgG,sDestination,sOrigine,gpCouleur,nCouleurInverse);
}//GrapheConnecter2

void GrapheConnecterTout(graf *pgG,int sSource[],int sCible[],int nGenreDePoids,int nPoidsInitial){
	Assert1("GrapheConnecterTout",bGrapheAttribuT(nGenreDePoids));
	int iCouleur=nPoidsInitial;
	for (int uArc=1;uArc<=sSource[0];uArc++){
		if (bImpair(uArc)) iCouleur++;
		GrapheArquer0(pgG,sSource[uArc],sCible[uArc],nGenreDePoids,iCouleur);
	}
}//GrapheConnecterTout

int bGrapheConnexe(graf *pgG){//O(A)
	int nComposanteConnexe=nGrapheComposanteConnexE(pgG);
	return(nComposanteConnexe==1);
}//bGrapheConnexe

int nGrapheCouleur(graf *pgG,int sOrigine,int sDestination){//O(S)
	//rend la couleur réputée non nulle de l'arc(sOrigine,sDestination), ou 0 si arc inexistant
	int aK;
	int nCouleur;
	Assert4("nGrapheCouleur",bGrapheAmorceR,bGrapheSimple(pgG),bGrapheSommet(pgG,sOrigine),bGrapheSommet(pgG,sDestination));
	for (nCouleur=0,aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
		if (pgG->sSuk[aK]==sDestination)
			nCouleur=pgG->coulh[aK];
	return(nCouleur);
}//nGrapheCouleur

char *sGrapheCouple(graf *pgG,int sX,int sY,int nGenreDePoids){
	//affiche les arcs de pgG sous forme de triplets (origine,destination,pondérateurs) ——par exemple,GrapheVoir0("",pgG,gpCout+gpPhi) affichera les champs nCout et nPhi.
	Assert3("sGrapheCouple2",bGrapheAmorceR,pgG!=NULL,bGrapheAttribuT(nGenreDePoids));
	Assert3("sGrapheCouple3",bCroit(1,sX,pgG->nSommetEnTout),bCroit(1,sY,pgG->nSommetEnTout),nGenreDePoids>0);
	char *sCouple;
	int uLabel,uPuissance;
	int aK=nGrapheArc(pgG,sX,sY);//ùù
	for (uLabel=1,uPuissance=2*gpAlpha;uPuissance<=gpZeta;uPuissance=2*uPuissance,uLabel++)
		if (nGenreDePoids & uPuissance)
			sCouple=sP(sC5(sEnt(sX),",",sEnt(sY),sItem(sGenreDePoidS,2*uLabel-1),sPar3(iGraphePoids(pgG,nGenreDePoids & uPuissance,aK))));
	return(sCouple);
}//sGrapheCouple

void GrapheCouvriR(){
	#define kuSmax 6
	const int kuFacteurMultiplicatif=kE4;
	const int kuPoidsMaxBidon=kE5;
	const int k1Prim=kV;
	int nCoteX[1+kuSmax]={-1,1,2,2,3,3,1};
	int nCoteY[1+kuSmax]={-1,1,2,3,3,4,4};
	int nAretePoids,aK,sX,sY;
	graf *pgG;
	Appel0("GrapheCouvriR");
		GrapheSymetriqueCreerPondereR(k1Dense,kuSmax,kuPoidsMaxBidon,&pgG);//les poids affectés sont provisoires
		//poids(X,Y):=distance(X,Y) pr tout couple (X,Y) de sommets de pgG
			for (sX=1;sX<=kuSmax;sX++)
				for (sY=sX+1;sY<=kuSmax;sY++){
					nAretePoids=nRac( kuFacteurMultiplicatif*(nCarreh(nCoteX[sX]-nCoteX[sY])+nCarreh(nCoteY[sX]-nCoteY[sY])) );
					aK=nGrapheArc(pgG,sX,sY);
					pgG->nCout[aK]=nAretePoids;
					aK=nGrapheArc(pgG,sY,sX);
					pgG->nCout[aK]=nAretePoids;
				}
		GrapheVoir0("graphe complet pondéré à \"électrifier\"",pgG,gpCout);
		Assert1("GrapheCouvriR graphe symétrique attendu",bGrapheSymetrique(pgG));//indispensable pour appeler GrapheCouvrirAvecPrimOuP
		GrapheCouvrirAvecPrimOuP(pgG,!k1Prim,k1Afficher,!k1PerformanceCompareR);
		GrapheCouvrirAvecKruskaL(pgG,k1Afficher,!k1PerformanceCompareR);
	Appel1("GrapheCouvriR");
}//GrapheCouvriR

void GrapheCouvrir(graf *pgG,int bArbreCouvrantDePoidsMaximum,int tPerformanceComparer,int idAfficher){
	//pgG->sPer[]:=description d'un AcpM/m qui couvre pgG orienté ou non (poids ds pgG->nCout[]). Si tAfficher<0,calcule 1 ou 2 AcpM/m
	graf *pgSymetrique;
	if (idAfficher>=0){
		GrapheCreer(pgG->nSommetEnTout,&pgSymetrique);
			GrapheDupliquer(pgG,&pgSymetrique);
			GrapheSymetriser(pgSymetrique,gpCout);
			GrapheCouvrirAvecKruskaL(pgSymetrique,idAfficher,tPerformanceComparer);//O(AlgA+AlgS)
			if (bGrapheSymetrique(pgG))
				VecteurCopier(pgSymetrique->nVal,1,pgSymetrique->nArcEnTout,pgG->nVal);
		GrapheCreer(0,&pgSymetrique);
	}else if ( bGrapheSymetrique(pgG) )
		GrapheCouvrirUniqueAvecKruskaL(pgG,bArbreCouvrantDePoidsMaximum,idAfficher);//O(A2lgA+A2lgS)
	else printf("Le calcul d'une arborescence (graphe orienté) et non pas d'un arbre (graphe non orienté) %s",nada);
}//GrapheCouvrir

void GrapheCouvrirAffichE(graf *pgG,const int kidAfficher,const int kbArbreCouvrantDePoidsMaximum,const int knPoidsTotal){
	int cPasse,nItem,nItemEnTout,aK,sX,sY;
	int tAfficher=tSigne(kidAfficher);
	int bDetailler=abs(kidAfficher)>1;
	int nAretePrise=pgG->nSommetEnTout-1;//puisque c'est un arbre
	int nCout[1+nAretePrise];
	printf("%sArbre couvrant de poids %s",(tAfficher<0)? flag : "\t",(kbArbreCouvrantDePoidsMaximum) ? "maximal" : "minimal");
	if (bDetailler)
		printf(" n°%d",(tAfficher<0)? 2: 1);
	printf(" à %s ——1 arête = 1 triplet (sommet,sommet:poids):\n\t%s{",sPluriel(nAretePrise,"arête"),(tAfficher<0)? flag : "\t");
		for (nCout[0]=nItemEnTout=0,cPasse=0;cPasse<=1 || bPrint("}.");cPasse++)
			for (nItem=0,aK=1;aK<=pgG->nArcEnTout;aK++)
				if (pgG->nVal[aK]>0){
					nItem++;
					if (cPasse>0){
						sX=pgG->nPhi[aK];
						sY=pgG->sSuk[aK];
						nCout[++nCout[0]]=abs(pgG->nCout[aK]);//empile les coûts à lister li-3
						printf("(%s,%s:%d)%s",sEnt2(iInf(sX,sY),0),sEnt2(iSup(sX,sY),0),abs(pgG->nCout[aK]),(nItem<nItemEnTout)?",":"");	
					}else nItemEnTout++;
				}
	printf("\t%sPoids total de cet %s",(tAfficher<0)? flag : "\t",(kbArbreCouvrantDePoidsMaximum) ? "ACPMax" : "ACPmin");
	int bCaractere=bModeCaractere();
	if (bCaractere) ModeCaractere(-1);
		printf(": %s=%d.\n",sListe(nCout,'+'),knPoidsTotal);
	if (bCaractere) ModeCaractere(+1);
}//GrapheCouvrirAffichE

int bGrapheCouvrirAutremenT(graf *pgG,int bArbreCouvrantDePoidsMaximum,int idAfficher,int nPoidsTotal0){
	//vrai ssi il existe un autre arbre couvrant qui a le même poids;si oui,le décrit ds pgG->nVal.
	int bCouvrirAutrement=0,aK,aL,nCoutAvant,nPoidsTotal,sX,sY;
	int nValeur[1+pgG->nArcEnTout];
	VecteurCopier(pgG->nVal,1,pgG->nArcEnTout,nValeur);
	for (aK=1;aK<=pgG->nArcEnTout && !bCouvrirAutrement;aK++)
		if (nValeur[aK]>0){
			GrapheDelimiter(pgG,aK,&sX,&sY);
			aL=nGrapheArc(pgG,sY,sX);
			nCoutAvant=pgG->nCout[aK];
			pgG->nCout[aK]=pgG->nCout[aL]=(bArbreCouvrantDePoidsMaximum)? 0 : kuIntegerMax;
				nPoidsTotal=nGrapheCouvrirAvecKruskaL(pgG,bArbreCouvrantDePoidsMaximum,k1Logn,k1Tas,!k1Afficher,&nBof);//O(AlgA+AlgS)
				bCouvrirAutrement=(nPoidsTotal==nPoidsTotal0);
				if (bCouvrirAutrement)
					nPoidsTotal=nGrapheCouvrirAvecKruskaL(pgG,bArbreCouvrantDePoidsMaximum,k1Logn,k1Tas,-abs(idAfficher),&nBof);//O(AlgA+AlgS)
			pgG->nCout[aK]=pgG->nCout[aL]=nCoutAvant;
		}
	return(bCouvrirAutrement);
}//bGrapheCouvrirAutremenT

void GrapheCouvrirAvecKruskaL(graf *pgG,int idAfficher,int tPerformanceComparer){
	//affiche l'acpm sur pgG,réputé non orienté,acpm calculé selon tPerformanceComparer (poids ds pgG->nCout[]).
	const int kuModeMax=3;
	int nComplexiteh[1+kuModeMax],nLg[1+kuModeMax];
	int nLgMax,nMode,nPoidsTotal;
	//const int k1Abe=kV;
	Assert2("GrapheCouvrirAvecKruskaL",bTrit(tPerformanceComparer),1 || bGrapheSymetrique(pgG));
	//d(tPerformanceComparer);
	//Appel0("GrapheCouvrirAvecKruskaL");
		//4 arbres couvrants sont calculés: d'abord 2 arbres de poids minimal sans tas, puis 2 arbres de poids minimal avec tas
			VecteurRazer(nComplexiteh,0,kuModeMax);
			if (tPerformanceComparer>0){//comparer les caractéristiques de l'algorithme optimisé avec des variantes non optimisées ou de poids quelconque.
				nPoidsTotal=nGrapheCouvrirAvecKruskaL(pgG,!k1Maximum,!k1Logn,!k1Tas,idAfficher,&nComplexiteh[0]);//arbre couvrant n°1,aucune optimisation
				nPoidsTotal=nGrapheCouvrirAvecKruskaL(pgG,!k1Maximum,k1Logn,!k1Tas,idAfficher,&nComplexiteh[1]);//arbre couvrant n°2,hauteur des anti-arbres optimisée
				nPoidsTotal=nGrapheCouvrirAvecKruskaL(pgG,!k1Maximum,!k1Logn,k1Tas,idAfficher,&nComplexiteh[2]);//arbre couvrant n°3;utilise un minimier
			}
			if (tPerformanceComparer<0){
				nComplexiteh[3]=nGrapheCouvrirAvecPriM(pgG,!k1Maximum,idAfficher);//arbre couvrant n°4;algo le plus efficace sur un graphe dense
				if (1)
					GrapheCheminE(pgG,1,pgG->nSommetEnTout,kV,abs(idAfficher),pgG->sPer[0],echArbreCouvranT);
			}else nPoidsTotal=nGrapheCouvrirAvecKruskaL(pgG,!k1Maximum,k1Logn,k1Tas,idAfficher,&nComplexiteh[3]);//arbre couvrant n°4;algo le plus efficace sur un graphe dense
			//VecteurVoir("nComplexiteh",nComplexiteh,0,kuModeMax);
			if (tPerformanceComparer>0){
				Titrer("Comparaison des algorithmes de calcul d'acpm par la méthode de Kruskal");
				printf("%sOption    Forêt optimisée    Tas (minimier)    Durée du calcul\n",sTab(1));
				for (nLgMax=0,nMode=0;nMode<=kuModeMax;nMode++)
					nLgMax=iSup(nLgMax,nLg[nMode]=nChaineLg(sPar3(nComplexiteh[nMode])));
				//VecteurVoir("nLg",nLg,0,kuModeMax);d(nLgMax);
				for (nMode=0;nMode<=kuModeMax;nMode++)
printf("%s  %d           %s                 %s          %s%s\n",sTab(1),nMode,sOk(nMode%2),sOk(nMode/2),sE((15-nLgMax)/2+nLgMax-nLg[nMode]),sPar3(nComplexiteh[nMode]));
			}
	//Appel1("GrapheCouvrirAvecKruskaL");
}//GrapheCouvrirAvecKruskaL

int nGrapheCouvrirAvecKruskaL(graf *pgG,int bArbreCouvrantDePoidsMaximum,int bLogn,int bTas,int idAfficher,int *pnComplexiteh){
	//calcule et affiche un arbre couvrant (résultat ds pgG->nVal[]) de poids minimal (donnée ds pgG->nCout[]) en utilisant Kruskal. Rend une mesure de sa complexité.
	const int kbProlixe=0;
	int aArete,nComplexiteh=0,nPoidsFinal,bPoidsMaximal,aPremiere=0,nPoidsTotal;
	int nHauteur,nHauteurMax,nPoids,nPoids0,nVersus;
	int aK,aL,sX,sX1,sY,sY1,ccX,ccY;
	if (kbProlixe) Appel0("nGrapheCouvrirAvecKruskaL");
		Assert1("nGrapheCouvrirAvecKruskaL1",1 || bGrapheSymetrique(pgG));
		ForetINITIALISER(pgG->nSommetEnTout,bLogn);//O(S)
			if (bArbreCouvrantDePoidsMaximum) VecteurOpposer(pgG->nCout,1,pgG->nArcEnTout);//O(A)
				//GrapheVoir0("pgG pr Kruskal",pgG,gpCout);
				//razer arbre couvrant vu comme un sous-graphe de pgG identifié par un booléen à 1 ssi l'arc est ds l'arbre couvrant
					VecteurRazer(pgG->nVal,1,pgG->nArcEnTout);//O(A)
				//pgG->nPhi:=sommet origine de chaque arc
					for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
						for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
							pgG->nPhi[aK]=sX;
				int iMax=iVecteurMax(pgG->nCout,1,pgG->nArcEnTout);//O(A)
				int iMin=iVecteurMin(pgG->nCout,1,pgG->nArcEnTout);//O(A)
				bPoidsMaximal=!bCroit(0,iMin,iMax);
				if (bTas){
					TasINITIALISER();//O(1)
					TasAllouer(pgG->nArcEnTout);//O(A)
					for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(AlgA)
						for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
							TasInsererValuer(aK,pgG->nCout[aK]);
					//TasVoir("initialisation");
				} else {//tri non optimisé,eg tri par insertion.
					VecteurTrier(pgG->nCout,1,pgG->nArcEnTout);//O(AlgA)
					nComplexiteh=pgG->nArcEnTout*pgG->nArcEnTout;
					//sd("nComplexiteh par insertion",nComplexiteh);
				}
				if (kbProlixe) printf("Exécution de l'algorithme de Kruskal %s minimier et %s optimisation de la forêt:\n",sChoix(bTas,"avec","sans"),sChoix(bLogn,"avec","sans")); 
				for (nPoidsFinal=0,nPoids0=(bPoidsMaximal)? kE5: 0,aK=1;aK<=pgG->nArcEnTout;aK++){//O(AlgA+AlgS)
					//aArete=aAreteSuivante():
						//b(bTas);
						if (bTas){
							aArete=eTasExtraire();//O(lgA)
							//TasVoir("");
						} else aArete=aK;
					nPoids=abs(pgG->nCout[aArete]);
					//sd2("poids courant",nPoids,nPoids0);
					//b(bPoidsMaximal);
					Assert1("nGrapheCouvrirAvecKruskaL2",!bTas || ( (bPoidsMaximal)? nPoids0>=nPoids : nPoids0<=nPoids) );//vérifie que eTasExtraire() rend des arêtes successives de poids croissants
					nPoids0=nPoids;
					sX=pgG->nPhi[aArete];
					sY=pgG->sSuk[aArete];
					//d3(aArete,sX,sY);
					ccX=nForetComposante(sX);//O(lgS)
					ccY=nForetComposante(sY);//O(lgS)
					if (ccX!=ccY){
						//printf("    Arête (%d,%d) prise.\n",sX,sY);
						ForetFusionner(ccX,ccY);//O(lgS)
						//ForetVoir("fusion");
						pgG->nVal[aL=aArete]=1;//ajoute aArete à l'arbre couvrant
						sX1=sX;sY1=sY;
						if (!aPremiere)
							aPremiere=aArete;
					};
				}
				if (bTas)
					nComplexiteh+=nTasCout();//O(1)
				//d(nTasCout());
				if (bTas)
					TasAllouer(0);
			if (bArbreCouvrantDePoidsMaximum) VecteurOpposer(pgG->nCout,1,pgG->nArcEnTout);//O(A)
		ForetINITIALISER(0,bLogn);//O(1)
		//nPoidsTotal:=poids total des arêtes de l'arbre couvrant
			for (nPoidsTotal=0,aK=1;aK<=pgG->nArcEnTout;aK++)
				nPoidsTotal+=(pgG->nVal[aK]>0)*abs(pgG->nCout[aK]);
		//d2(0,nPoidsTotal);
		if (1 && idAfficher){//Afficher l'ACPM/m et son poids total
			GrapheCouvrirAffichE(pgG,idAfficher,bArbreCouvrantDePoidsMaximum,nPoidsTotal);
			nComplexiteh+=nForetComplexiteh(&nHauteur);
			nHauteurMax=mPoidsFort(pgG->nSommetEnTout);
			if (kbProlixe) printf("\tHauteur maximale théorique de la forêt équilibrée: %s. Hauteur maximale obtenue: %s.\n",sPar3(nHauteurMax),sPar3(nHauteur));
			nVersus=2*pgG->nArcEnTout*nHauteurMax;//soit, par arête, 4 appels à nForetComposante
			if (kbProlixe) printf("\t\t\tCumul itérations de nForetComposante() vs maximum théorique 2Alog2(S): %s vs %s.\n",sPar3(nComplexiteh),sPar3(nVersus));
		}
		//d2(1,nPoidsTotal);
		//d(nComplexiteh);
	if (kbProlixe) Appel1("nGrapheCouvrirAvecKruskaL");
	*pnComplexiteh=nComplexiteh;
	return(nPoidsTotal);
}//nGrapheCouvrirAvecKruskaL

void GrapheCouvrirAfficheR(char *sAlgorithme,graf *pgG){
	int nArete,nPoids,nPoidsTotal;
	int aK,sX,sY;
	nArete=pgG->nSommetEnTout-1;//vu bGrapheConnexe(pgG).
	printf("——— Résultat avec %s: un arbre couvrant de poids minimal à %s:\n     ",sAlgorithme,sPluriel(nArete,"arête"));
	//afficher les arêtes avec leurs poids respectifs ainsi que nPoidsTotal:
		for (nArete=0,nPoidsTotal=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				if (pgG->sPer[sY]==sX){//tout arc (X,Y) qui vérifie pgG->sPer[sY]==sX appartient à l'arbre couvrant
					nArete++;
					nPoids=pgG->nCout[aK];
					printf("(%d,%d:%d)%s",sX,sY,nPoids,(nArete+1<pgG->nSommetEnTout)?",":"");
					nPoidsTotal+=nPoids;
				}
			}
		printf(" ——poids total:%d.\n",nPoidsTotal);
}//GrapheCouvrirAfficheR

int nGrapheCouvrirAvecP(graf *pgG){//O(S2)
	//calcule un arbre couvrant (résultat ds pgG->sPer[]) de poids minimal (donnée ds pgG->nCout[]) en utilisant l'algo P vu en TD. Rend une mesure de sa complexité.
	const int kuInfini=kE4-1;
	const int kbVoir=kF;
	int nComplexiteh=0,nCoutMax,aK,sX,sY,uSommet;
	int nDist[1+pgG->nSommetEnTout];//nDist[sY] est la plus petite distance entre le sommet sY et l'arbre en cours de construction.
	if (kbVoir) Appel0("nGrapheCouvrirAvecP");
		//vérifier que kuInfini est bien une valeur supérieure à toute valeur du vecteur positif ou nul pgG->nCout[1..pgG->nSommetEnTout].
			for (nCoutMax=0,sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					nCoutMax=iSup(nCoutMax,pgG->nCout[aK]);
					Assert1("nGrapheCouvrirAvecP2",pgG->nCout[aK]>=0);
				}
			if (kbVoir) d(nCoutMax);
			Assert1("nGrapheCouvrirAvecP3",nCoutMax<kuInfini);
		sX=1;//existe vu pgG->nSommetEnTout>1.
		//nDist[sY]:=kuInfini pour tout sommet sY autre que sX,et nDist[sX]=0.
			VecteurValuer(nDist,1,pgG->nSommetEnTout,kuInfini);//O(S)
			nComplexiteh+=pgG->nSommetEnTout;
			nDist[sX]=0;
			if (kbVoir) VecteurVoir1("nDist",nDist,1,pgG->nSommetEnTout);
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);//O(S);superflu,mais facilite le débogage.
		nComplexiteh+=pgG->nSommetEnTout;
		pgG->sPer[sX]=-sX;//changera de signe après extraction du sommet considéré par eTasExtraire() (superflu,mais facilite le débogage).
		AbeAllouer(pgG->nSommetEnTout,kuInfini);//O(1)
			//Abe:=tous les couples (sX,nDist[sX])
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					AbeModifier(sX,nDist[sX]);//O(lgS)
			for (uSommet=1;uSommet<=pgG->nSommetEnTout;uSommet++){//O(S2)
				AbePropager();//O(S)
				if (kbVoir) AbeVoir("avant extraction");
				sX=eAbeExtraire();//O(1)
				pgG->sPer[sX]=abs(pgG->sPer[sX]);//donc positive strictt.
				if (kF || kbVoir) printf("Extraction du sommet n°%d.\n",sX);
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					sY=pgG->sSuk[aK];
					nComplexiteh+=1;
					if (nDist[sY]>pgG->nCout[aK] && pgG->sPer[sY]<=0){
						nDist[sY]=pgG->nCout[aK];
						AbeModifier(sY,nDist[sY]);//O(1)
						pgG->sPer[sY]=-sX;//pgG->sPer[sX] changera de signe après extraction du sommet considéré par eTasExtraire().
					}
				}//for aK
				//if (kbVoir) VecteurVoir1("pgG->sPer",pgG->sPer,1,pgG->nSommetEnTout);
			}//for uSommet
			nComplexiteh=nAbeCout();//ajoute le coût total des opérations effectuées sur l'abe entre les deux AbeAllouer().
		AbeAllouer(0,kuInfini);//O(1)
	if (kbVoir) Appel1("nGrapheCouvrirAvecP");
	return(nComplexiteh);
}//nGrapheCouvrirAvecP

int nGrapheCouvrirAvecPriM(graf *pgG,int bArbreCouvrantDePoidsMaximum,int tAfficher){//O(SlgS+AlgS)
	//calcule un arbre couvrant (résultat ds pgG->sPer[]) de poids minimal (donnée ds pgG->nCout[]) en utilisant Prim avec tas. Rend une mesure de sa complexité.
	const int kuInfini=kE3-1;
	const int kbVoir=kF;
	int nAreteTotalDansArbre,nComplexiteh=0,nCoutMax,aK,sX,sY,uSommet,nItem,nPoidsTotal;
	int nDist[1+pgG->nSommetEnTout];//nDist[sY] est la plus petite distance entre le sommet sY et l'arbre en cours de construction.
	if (kbVoir) Appel0("nGrapheCouvrirAvecPriM");
		Assert1("nGrapheCouvrirAvecPriM",bGrapheSymetrique(pgG));
		printf("Arbre couvrant de poids minimal (algo de PRIM avec minimier):\n");
		tAfficher=1;
		d2(bArbreCouvrantDePoidsMaximum,tAfficher);
		//vérifier que kuInfini est bien une valeur supérieure à toute valeur du vecteur positif ou nul pgG->nCout[1..pgG->nSommetEnTout].
			for (nCoutMax=0,sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					nCoutMax=iSup(nCoutMax,pgG->nCout[aK]);
					Assert1("nGrapheCouvrirAvecPriM2",pgG->nCout[aK]>=0);
				}
			if (kbVoir) d(nCoutMax);
			Assert1("nGrapheCouvrirAvecPriM3",nCoutMax<kuInfini);
		if (bArbreCouvrantDePoidsMaximum) VecteurOpposer(pgG->nCout,1,pgG->nArcEnTout);
		sX=1;//existe vu pgG->nSommetEnTout>1.
		//nDist[sY]:=coût kuInfini pour tout sommet sY autre que sX,et nDist[sX]=0.
			VecteurValuer(nDist,1,pgG->nSommetEnTout,kuInfini);//O(S)
			nComplexiteh+=pgG->nSommetEnTout;
			nDist[sX]=0;
			if (kbVoir) VecteurVoir1("nDist",nDist,1,pgG->nSommetEnTout);
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);//O(S);superflu,mais facilite le débogage.
		nComplexiteh+=pgG->nSommetEnTout;
		pgG->sPer[sX]=-sX;//changera de signe après extraction du sommet considéré par eTasExtraire() (superflu,mais facilite le débogage).
		TasINITIALISER();
		TasAllouer(pgG->nSommetEnTout);//O(1)
			//Tas:=tous les couples (sX,nDist[sX])
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					TasInsererValuer(sX,nDist[sX]);//O(lgS)
		//TasVoir("initialisation");
			for (uSommet=1;uSommet<=pgG->nSommetEnTout;uSommet++){//O(SlgS+AlgS)
				//VecteurVoir1("nDist",nDist,1,pgG->nSommetEnTout);
				if (kbVoir) TasVoir("avant extraction");
				sX=eTasExtraire();//O(lgS)
				//sd("sommet extrait",sX);
				pgG->sPer[sX]=abs(pgG->sPer[sX]);//change donc de signe et devient strictement positif.
				if (kbVoir) printf("Extraction du sommet n°%d.\n",sX);
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					sY=pgG->sSuk[aK];
					nComplexiteh+=1;
					if (nDist[sY]>pgG->nCout[aK] && pgG->sPer[sY]<=0){
						nDist[sY]=pgG->nCout[aK];
						//printf("actualisO du sommet %d avec le coût %d.\n",sY,nDist[sY]);
						TasActualiser(sY,nDist[sY]);//O(lgS)
						pgG->sPer[sY]=-sX;//pgG->sPer[sX] changera de signe après extraction du sommet considéré par eTasExtraire().
					}
				}//for aK
				if (kbVoir) VecteurVoir1("pgG->sPer",pgG->sPer,1,pgG->nSommetEnTout);
			}//for uSommet
			nComplexiteh+=nTasCout();//ajoute le coût total des opérations effectuées sur le tas entre les deux TasAllouer().
		TasAllouer(0);
		pgG->sPer[0]=yVecteurSomme(nDist,1,pgG->nSommetEnTout);
		if (kbVoir) d(nComplexiteh);
			if (1 && tAfficher){//Afficher l'arbre couvrant et son poids total
				//nAreteTotalDansArbre:=nb total d'arêtes de l'arbre couvrant
					for (nAreteTotalDansArbre=0,sX=1;sY=pgG->sPer[sX],sX<=pgG->nSommetEnTout;sX++)
						nAreteTotalDansArbre+=(sX!=sY);
				if (tAfficher<0) printf("\t");
				printf("Arbre couvrant %s de poids %s",(tAfficher<0)? "n°2": "n°1",(bArbreCouvrantDePoidsMaximum) ? "maximal" : "minimal");
				printf(" à %s. 1 arête = 1 triplet (sommet,sommet:poids):\n\t{",sPluriel(nAreteTotalDansArbre,"arête"));
				for (nItem=0,sX=1;sY=pgG->sPer[sX],sX<=pgG->nSommetEnTout || bPrint("}.");sX++)
					if (sY>0){
						aK=nGrapheArc(pgG,sX,sY);
						if (sX!=sY)
							printf("(%s,%s:%d)%s",sEnt2(iInf(sX,sY),0),sEnt2(iSup(sX,sY),0),abs(pgG->nCout[aK]),(++nItem<nAreteTotalDansArbre)?",":"");
					}
				//nPoidsTotal:=poids total des arêtes de l'arbre couvrant
					for (nPoidsTotal=0,sX=1;sY=pgG->sPer[sX],sX<=pgG->nSommetEnTout;sX++){
						aK=nGrapheArc(pgG,sX,sY);
						if (sX!=sY)
							nPoidsTotal+=abs(pgG->nCout[aK]);
					}
				printf("\tPoids total de l'arbre couvrant obtenu: %d.\n",nPoidsTotal);
			}
		if (bArbreCouvrantDePoidsMaximum) VecteurOpposer(pgG->nCout,1,pgG->nArcEnTout);
	if (kbVoir) Appel1("nGrapheCouvrirAvecPriM");
	return(nComplexiteh);
}//nGrapheCouvrirAvecPriM

void GrapheCouvrirAvecPrimOuP(graf *pgG,int bPrim,int bAfficher,int bPerformanceComparer){
	//le code de cette routine est à compléter ——en ajoutant notamment du code pris dans GrapheCouvrirAvecKruskaL.
	const int kuModeMaxi=2;
	int nComplexiteh[kuModeMaxi],nComplexitehMax[kuModeMaxi],nMode,nLgMax,nLg[kuModeMaxi];
	Assert3("GrapheCouvrirAvecPrimOuP",bGrapheSymetrique(pgG),bGrapheConnexe(pgG),pgG->nSommetEnTout>1);
	//nComplexiteh[0]=nComplexiteh[1]=0;
	if (bPrim || bPerformanceComparer){
		nComplexiteh[0]=nGrapheCouvrirAvecPriM(pgG,!k1Maximum,bAfficher);//O(SlgS+AlgS)
		if (bAfficher)
			GrapheCouvrirAfficheR("Prim",pgG);
	}
	if (!bPrim || bPerformanceComparer){
		nComplexiteh[1]=nGrapheCouvrirAvecP(pgG);//O(S2)
		if (bAfficher)
			GrapheCouvrirAfficheR("P",pgG);
	}
	if (bPerformanceComparer){
		//tee("nComplexiteh[0],nComplexiteh[1]",nComplexiteh[0],nComplexiteh[1]);
		Titrer("Comparaison des performances Prim vs P pour le calcul d'acpm");
		printf("%sOption    Prim (minimier)    P(abe)    Durée du calcul\n",sTab(1));
		for (nLgMax=0,nMode=0;nMode<kuModeMaxi;nMode++)
			nLgMax=iSup(nLgMax,nLg[nMode]=nChaineLg(sPar3(nComplexiteh[nMode])));
		//VecteurVoir("nLg",nLg,0,1);d(nLgMax);
		for (nMode=0;nMode<kuModeMaxi;nMode++)
			printf("%s  %d           %s             %s      %s%s\n",sTab(1),nMode,sOk(nMode%2==0),sOk(nMode%2),sE((15-nLgMax)/2+nLgMax-nLg[nMode]),sPar3(nComplexiteh[nMode]));
		nComplexitehMax[0]=pgG->nArcEnTout*nLog2(pgG->nSommetEnTout);
		nComplexitehMax[1]=pgG->nSommetEnTout*pgG->nSommetEnTout;
		printf("Gains sur le pire cas: SlgS/Prim=%s et S2/P=%s. Facteur de vitesse gagné sur Prim par le challenger P: %s.\n",
			sDiv(nComplexitehMax[0],nComplexiteh[0]),sDiv(nComplexitehMax[1],nComplexiteh[1]),sDiv(nComplexiteh[0],nComplexiteh[1]));
	}
}//GrapheCouvrirAvecPrimOuP

void GrapheCouvrirUniqueAvecKruskaL(graf *pgG,int bArbreCouvrantDePoidsMaximum,int idAfficher){//O(AlgA+AlgS)
	//affiche 0, 1 ou 2 ACPM/m selon que, respectivt, pgG est non connexe, il y a 1 arbre couvrant, il y en a plusieurs.
	int aK,nAretePrise,nPoidsTotal,bUnique,bForet;
	//Appel0("GrapheCouvrirUniqueAvecKruskaL");
		nPoidsTotal=nGrapheCouvrirAvecKruskaL(pgG,bArbreCouvrantDePoidsMaximum,k1Logn,k1Tas,abs(idAfficher),&nBof);//O(AlgA+AlgS)
		int bDetailler=abs(idAfficher)>1;
		if (bDetailler){
			//nAretePrise:=poids total des arêtes de la couverture
				for (nAretePrise=0,aK=1;aK<=pgG->nArcEnTout;aK++)
					nAretePrise+=(pgG->nVal[aK]>0);
			bForet=(nAretePrise<pgG->nSommetEnTout-1);
			if (!bForet){
				bUnique=!bGrapheCouvrirAutremenT(pgG,bArbreCouvrantDePoidsMaximum,idAfficher,nPoidsTotal);//qui décrit ds pgG->nVal un autre arbre éventuel
				printf("%s%s%s %s unique.\n",flag,(bUnique)? "L'":"Donc l'",(bArbreCouvrantDePoidsMaximum) ? "ACPM" : "ACPm",sEst(bUnique));
			}else printf("\tIl n'y a pas d'arbre couvrant (mais une forêt).\n");
		}
	//Appel1("GrapheCouvrirUniqueAvecKruskaL");
}//GrapheCouvrirUniqueAvecKruskaL

void GrapheCreer(int nSommet,graf **ppgG){
	//si nSommet>0, alloue un espace pour pgG;si nSommet est nul,libère l'espace.
	//FlipFlop("GrapheCreer",iSommet!=0,&bGrapheCreeR);//ie tout graphe alloué doit être désalloué via GrapheCreer(0,…) avant une nouvelle allocation. 
	Assert12("GrapheCreer1,nSommet,kuGrapheSommetLim",bCroit(0,nSommet,kuGrapheSommetLim-1),nSommet,kuGrapheSommetLim);
	if (nSommet>0){
		*ppgG=(graf *) malloc(sizeof(graf));
		(*ppgG)->nSommetEnTout=nSommet;
		(*ppgG)->nArcEnTout=0;
		for (int sX=1;sX<=(*ppgG)->nSommetEnTout+1;sX++)
			(*ppgG)->aHed[sX]=1;//dc un graphe simple avec (*ppgG)->nSommetEnTout sommets et aucun arc.
		VecteurValuer((*ppgG)->aHed,1,(*ppgG)->nSommetEnTout+1,1);
		Assert1("GrapheCreer2",bGrapheSimple(*ppgG));
	}
	else free(*ppgG);
}//GrapheCreer

void GrapheCreer0(graf **ppgG,int bCreer){
	//crée un graphe vide, ie sans sommets ni arcs.
	//FlipFlop("GrapheCreer0",bCreer,&bGrapheCreeR);//ie tout graphe alloué doit être désalloué via GrapheCreer0(0,…) avant une nouvelle allocation. 
	if (bCreer){
		*ppgG=(graf *) malloc(sizeof(graf));
		(*ppgG)->nSommetEnTout=0;
		(*ppgG)->nArcEnTout=0;
		(*ppgG)->aHed[1]=1;
	}else {free(*ppgG);*ppgG=NULL;}
}//GrapheCreer0

void GrapheCreer1(graf **ppgG,int grGadget,int nGadgetTaille,int bCreer){
	//si bCreer,crée le graphe de nom grGadget (alloue l'espace mémoire puis ajoute ts les arcs); sinon,restitue le graphe alloué
	//NB Les graphes générés ne sont pas, en général, symétriques; Pour les symétriser,appeler GrapheSymetriser(pgG) après la création. 
	graf *pgG;
	enum grType GrapheType;
	int sX,sX0,sX1,sY,sY0,sY1,uG,muPas;
	char ks2Aile[]="AC2BD3CE1DF1EG2FH2GF3HE3GA1HB1";//2 papillons à 4 sommets
	char ksB[]="AD1AE1002BC1BF1003CG1003DH1002EF1EG101EI2FH101FI3GH1GI3HI2";//NB les coins du quadripôle SONT les sommets A,B,C et D.
	char ks2Croix[]="AD1BC1";//entrées A, B, sorties C,D.
	char ks2Diam[]="AE2BE3EF1FC2FD3GA8GB8CH9DH9";
	char ks2P[]="AB2CD2";//entrées A, B, sorties C,D.

 	//char ksE2[]="AC1BA1BD1CB1DC1";
	//char ksE3[]="AD1BF1CE1DC1DF1EB1ED1FA1FE1";//échafaudage en dipôle. Triangles externes et internes circulaires
	char ksE2[]="AC1BA1BD1CB1CD1";
	char ksE3[]="AD1BF1CE1DC1DF1EB1ED1EF1FA1";//échafaudage en dipôle. Triangles externes et internes circulaires
	char ksH[]="AC1BA1BD1CB1CD1";//bidon

	char ksFigure8aPage272[]="AB0AC0BC1BE0CD0DE1DG0EF0FG1FH0";//Gondran et Minoux Eyrolles 37 pour tester les couplages qcq
	char ksPrisme[]="AB1AE1BA1BE1CD1CF1DC1DF1EA1EB1EF1FC1FD1";//NB les coins du quadripôle SONT les sommets A,B,C et D.
	char ksPt[]="AB1AJ2BC1BF2CD1CG2DE1DH2EA1EI2FH3FI3GI3GJ3HJ3";
	char ksT[]="AB1AC1BA1BD1CD1DC1";//NB les coins du quadripôle SONT les sommets A,B,C et D.
	char ksT2[]="AB1AC1BA1BD1CB1CD1DA1DC1";//NB les coins du quadripôle SONT les sommets A,B,C et D.
	//char ksT2[]="AB4AC4BA4BD4CB4CD4DA4DC4";//NB les coins du quadripôle SONT les sommets A,B,C et D.
	char ksU[]="AB2AC1AE2BD1BE1CE1CD2DE2";//carré sans cycle. NB les coins du quadripôle SONT les sommets A,B,C et D.
	char ksX[]="AC1BD1CB2DA2";//NB 1 papillon; entrées A, B, sorties C,D.
	char ksQ0[]="AE2BE2EC2ED2";//NB 1 croix orientée; entrées A, B, sorties C,D.
	char ksQ1[]="AE2BE2EF3FC2FD2";//NB 1 croix étirée au centre; entrées A, B, sorties C,D.
	
	//char ksXX[]="AE2BF2CH3DG5EB8EG9FA7FH9GC6HD4";//NB les coins du quadripôle sont les sommets A,B,C et D.
	char ksXor[]="AC1BD1CF2DF2EA3EB3FE4";//NB domino,exclusion mutuelle; entrées A et B, sorties C et D.
	char ksXX[]="AC2BD2CB2CE3DA2DF3EG2FH2GF2HE2";//NB les coins du quadripôle NE SONT PAS les sommets A,B,C et D.
	char ksXY[]="AE1BF1BE2AF2EG3FH3CG1DH1CH2DG2";//NB entrées A, B, sorties C,D.
	char ksW[]="AC2AD2AE2BC2BD2BE2CA2DB2EC2ED2";//NB entrées A, B, sorties C,D.

	GrapheCreer0(ppgG,bCreer);//oui,mm pr grXX,tant pis
	if (bCreer){
		pgG=*ppgG;
		switch (grGadget) {
			case gr2Aile:
				bGrapheGenerer(ks2Aile,gpCouleur,ppgG);
			break;
			case grB:
				bGrapheGenerer(ksB,gpPoids+gpCouleur,ppgG);
				if (0) GrapheVoir1("Graphe géneré",*ppgG,k1Couleur);
			break;
			case gr2Croix:
				bGrapheGenerer(ks2Croix,gpCouleur,ppgG);
			break;
			case gr2Diam:
				bGrapheGenerer(ks2Diam,gpCouleur,ppgG);
			break;
			case gr2P:
				bGrapheGenerer(ks2P,gpCouleur,ppgG);
			break;
			case grC:	//C comme Cycle: Cn est un cycle à n sommets
				GrapheSommer(pgG,nGadgetTaille);
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					GrapheArquer0(pgG,sX,uModulo1(sX+1,pgG->nSommetEnTout),gpCouleur,coVert);
			break;
			case grC4b:	//C4 + 1 arc (2,4)
				GrapheSommer(pgG,4);
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					GrapheArquer0(pgG,sX,uModulo1(sX+1,pgG->nSommetEnTout),gpCouleur,coVert);
				GrapheArquer0(pgG,2,4,gpCouleur,coVert);
			break;
			case grD:	//peigne à Dn dents
				GrapheSommer(pgG,2*(nGadgetTaille));
				for (sX=1;sX<=pgG->nSommetEnTout/2-1;sX++)
					GrapheArquer0(pgG,2*sX-1,2*sX+1,gpCouleur,coVert);//base du peigne=sommets impairs
				for (sX=1;sX<=pgG->nSommetEnTout/2;sX++)
					GrapheArquer0(pgG,2*sX-1,2*sX+0,gpCouleur,coVert);//dents du peigne, de sommets impair à sommet suivant
			break;
			case grE2:
				bGrapheGenerer(ksE2,gpCouleur,ppgG);
			break;
			case grE3:
				bGrapheGenerer(ksE3,gpCouleur,ppgG);
			break;
			case grH:
				bGrapheGenerer(ksH,gpCouleur,ppgG);
			break;
			case grK://K comme Kuratowski: Kn généré est un graphe ORIENTÉ à n sommets ——dc à symétriser le cas échéant
				GrapheSommer(pgG,nGadgetTaille);
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (sY=1;sY<=pgG->nSommetEnTout;sY++)
						if (sX<sY)
							GrapheArquer0(pgG,sX,sY,gpCouleur,coVert);
			break;
			case grL4:	//C3 + 1 arc (3,4)
				GrapheSommer(pgG,4);
				GrapheArquer0(pgG,1,2,gpCouleur,coVert);
				GrapheArquer0(pgG,2,3,gpCouleur,coVert);
				GrapheArquer0(pgG,3,1,gpCouleur,coVert);
				GrapheArquer0(pgG,3,4,gpCouleur,coVert);
			break;
			case grP://P comme Path: Pn est un chemin à n sommets
				//d(nGadgetTaille);
				GrapheSommer(pgG,nGadgetTaille);
				for (sX=1;sX<pgG->nSommetEnTout;sX++)
					GrapheArquer0(pgG,sX,sX+1,gpCouleur,1);
				//GrapheVoir("pgG après création",pgG);
			break;
			case grPt://graphe de Petersen (pentagone ABCDE relié une étoile FGHIJ)
				bGrapheGenerer(ksPt,gpCouleur,ppgG);
			break;
			case grPtr://P comme Prisme triangulaire
				bGrapheGenerer(ksPrisme,gpCouleur,ppgG);
			break;
			case grQ0:
				bGrapheGenerer(ksQ0,gpCouleur,ppgG);
			break;
			case grQ1:
				bGrapheGenerer(ksQ1,gpCouleur,ppgG);
			break;
			case grS://S comme Star: Sn est une étoile à n extrémités (1 sommet central)
				GrapheSommer(pgG,nGadgetTaille);
				for (sX=2;sX<=pgG->nSommetEnTout;sX++)
					GrapheArquer0(pgG,1,sX,gpCouleur,coVert);
			break;
			case grT://tambour: 1 disque haut sous forme de cycle à 2 sommets relié à un disque bas identique
				bGrapheGenerer(ksT,gpCouleur,ppgG);
			break;
			case grT2://grT plus deux arcs qui se croisent et vont du disque bas vers le disque haut
				bGrapheGenerer(ksT2,gpCouleur,ppgG);
			break;
			case grU: //carré sans cycle.
				bGrapheGenerer(ksU,gpCouleur,ppgG);
			break;
			case grW: //diabolo intriqué dans un huit
				bGrapheGenerer(ksW,gpCouleur,ppgG);
			break;
			case grXor: //1 exclusion mutuelle: (5,1),(1,3),(3,6),(5,2),(2,4),(4,6),(5,6).
				bGrapheGenerer(ksXor,gpCouleur,ppgG);
			break;
			case grX: //10 en chiffres romains ——1 X entre 2 barres horizontales, et 2 sommets par barre.
				bGrapheGenerer(ksX,gpCouleur,ppgG);
			break;
			case grXX: //20 en chiffres romains ——2 X entre 2 barres horizontales, et 4 sommets par barre.
				bGrapheGenerer(ksXX,gpCouleur,ppgG);
			break;
			case grXY: //grXX à une renumérotation des sommets près
				bGrapheGenerer(ksXY,gpCouleur,ppgG);
			break;
			case grY://échelle formée avec nGadgetTaille gadgets grX étendus (ie à 6 sommets), + 1 paire d'arcs entre 2 grX.
				GrapheSommer(pgG,nGrapheCardinal(grGadget,nGadgetTaille));
				for (sX=1,sY=2,muPas=uG=1;uG<=nGadgetTaille;uG++){//juxtaposer les grX numérotés en boustrophédon
					sX0=sX;sY0=sY;
					GrapheArquer0(pgG,sX,sX1=sX+2+muPas,gpCouleur,coRouge);sX=sX1;
					GrapheArquer0(pgG,sY,sY1=sY+2-muPas,gpCouleur,coRouge);sY=sY1;
					muPas=-muPas;//d3(1,sX,sY);
					GrapheArquer0(pgG,sX,sX1=sX+2+muPas,gpCouleur,coBleu);sX=sX1;
					GrapheArquer0(pgG,sY,sY1=sY+2-muPas,gpCouleur,coBleu);sY=sY1;
					muPas=-muPas;//d3(2,sX,sY);
					//ajouter les diagonales
						GrapheArquer0(pgG,sY,sX0,gpCouleur,coVert);
						GrapheArquer0(pgG,sX,sY0,gpCouleur,coVert);
					if (uG<nGadgetTaille){//ajouter 1 paire d'arcs
						GrapheArquer0(pgG,sX,sX1=sX+2+muPas,gpCouleur,coJaune);sX=sX1;
						GrapheArquer0(pgG,sY,sY1=sY+2-muPas,gpCouleur,coJaune);sY=sY1;
						muPas=-muPas;//d3(3,sX,sY);
					}
				}
			break;
			case grOmega://Gondran et Minoux Eyrolles 37 pr tester les couplages qcq (ctient nott des triangles imbriqués)
				bGrapheGenerer(ksFigure8aPage272,gpCouleur,ppgG);
			break;
			default:Assert1("GrapheCreer1: numéro de graphe inconnu (cf GrapheType)",0);
		}//switch (nGraphe)
	};
}//GrapheCreer1

void GrapheCreer2(graf **ppgG,int nSommet,int nArc,int nArcOrigine[],int nArcDestination[]){
	//crée un graphe simple à nSommet sommets et nArc arcs listés dans nArcOrigine[] et nArcDestination[];déroute en cas de problème.
	int sDestination;
	int aK;
	int sOrigine;
	Assert4("GrapheCreer20",nSommet>=0, nArc>=0, nArcOrigine!=NULL, nArcDestination!=NULL);
	GrapheCreer(nSommet,ppgG);//crée un graphe à nSommet sommets et aucun arc
	//Ajouter tous les arcs aK spécifiés par nArcOrigine[aK] et nArcDestination[aK] et dérouter si un ajout est impossible:
		for (aK=1;aK<=nArc;aK++){
			sOrigine=nArcOrigine[aK];
			sDestination=nArcDestination[aK];
			//tee("création de l'arc",sOrigine,sDestination);
			GrapheArquer(*ppgG,sOrigine,sDestination);//actualise notamment pgG->nArcEnTout;déroute si l'arc ne peut être créé.
		}
	Assert1("GrapheCreer22",bGrapheSimple(*ppgG));
}//GrapheCreer2

int nGrapheCycle2(graf *pgG){
	//rend le nombre de cycles de longueur 2  ds pgG
	int nCycle2=0,sX,sY,aK;
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			if ( sX<sY && nGrapheArc(pgG,sY,sX) )
				nCycle2++;
		}
	//d(nCycle2);
	return(nCycle2);
}//nGrapheCycle2

void GrapheDecolorer(graf *pgG,graf **ppgC){//O(A)
	//trsforme pgG coloré en graphe sans couleur *ppgC équivalent à pgG au sens des couvertures de cycles;données: tt arc aK a un…
	//…pgG->coulh[aK]>0 et un pgG->nPoids[aK]≥0; tt sommet sX a un poids pgG->nVal[sX] ≥0/<0 si traverser sX est obligatR/facultF et…
	//…pour finir,effectue ppgC->nVal[]:=nGadget[] courant afin que l'appelant retrouve en O(1) la correspondance entre ppgC et pgG.
	const int bVoir=0;
	const int kbSimplifier=1;//la descriptO des sommets obligatR à 2 couleurs est réduite à un dipôle.
	int uC,uK,aK,aL,sX,sY,sZ,ipPlot,sSource,sCible,nbKoulh,iKoulhMin,iKoulhMax,nbSommet;
	int nCoulh[1+pgG->nSommetEnTout],nDegreh[1+pgG->nSommetEnTout],nGadget[1+1+pgG->nSommetEnTout];//1er sommet du gadget courant
	int bDipoler[1+pgG->nSommetEnTout];
	Assert1("GrapheDecolorer: poids incorrect",iVecteurMin(pgG->nPoids,1,pgG->nArcEnTout)>=0);
	if (0) GrapheVoir0("pgG",pgG,gpCouleur+gpPoids);
	if (bVoir) VecteurVoir1("pgG-nVal",pgG->nVal,1,pgG->nSommetEnTout);
	GrapheInverser(pgG);
	//nDegreh[]:=degré de chq sommet (entrant + sortant)
		//sd("degré du sommet 44",nGrapheDegreh(pgG,44,0));
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){//O(S)
			nDegreh[sX]=nGrapheDegreh(pgG,sX,0);
			if (nDegreh[sX]==0)	sd("degré nul",sX);
		}
		int nDegrehMin=iVecteurMin(nDegreh,1,pgG->nSommetEnTout);
		if (0) VecteurVoir1("nDegreh",nDegreh,1,pgG->nSommetEnTout);
		Assert11("GrapheDecolorer: nDegreh nul,nDegrehMin",nDegrehMin>0,nDegrehMin);//z mais généralt pertinent
	//nbKoulh:=nbre de couleurs présentes ds pgG->coulh[]
		Marner0(&iKoulhMin,&iKoulhMax);
		for (aK=1;aK<=pgG->nArcEnTout;aK++)//O(A)
			Marner(pgG->coulh[aK],&iKoulhMin,&iKoulhMax);
		Assert1("GrapheDecolorer: couleur incorrecte",iKoulhMin>0);
		nbKoulh=iKoulhMax-iKoulhMin+1;
		int nKoulLim=nFrontiere8((1+nbKoulh)*sizeof(int));
		//d4(iKoulhMin,iKoulhMax,1+nbKoulh,nKoulLim);
	int nOffset[1+pgG->nSommetEnTout][nKoulLim];//sommet du gadget courant qui reçoit la couleur
	//nCoulh[],nOffset[][]:=nb de couleurs par sommet, et rg1 du sommet qui reçoit la couleur courante
		int bKoul[1+nbKoulh];//vecteur des couleurs présentes autour du sommet courant sX ci-après
		for (VecteurRaz(nCoulh,nbKoulh),bKoul[0]=nbKoulh,sX=1;sX<=pgG->nSommetEnTout;sX++){//O(A)
			//bKoul[C]:=la couleur C figure ds un arc incident à sX
				VecteurRaz(bKoul,bKoul[0]);
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					bKoul[pgG->coulh[aK]]=1;
				for (aL=pgG->aDeh[sX];aL<pgG->aDeh[sX+1];aL++)
					bKoul[pgG->coulh[pgG->aInv[aL]]]=1;
			nCoulh[sX]=yVecteurSomme(bKoul,1,nbKoulh);
			VecteurRazer(nOffset[sX],1,nbKoulh);
			if (0 && bVoir) VecteurVoir(sC2("bKoul",sC(sEnt(sX))),bKoul,1,nbKoulh);
			for (ipPlot=uK=1;uK<=nbKoulh;uK++)
				if (bKoul[uK])
					nOffset[sX][uK]=ipPlot++;
			if (bVoir) VecteurVoir(sC2("nOffset",sC(sEnt(sX))),nOffset[sX],1,nbKoulh);
		}
		if (0) VecteurVoir1("nCoulh",nCoulh,1,pgG->nSommetEnTout);
if (1) VecteurVoir5("nDegreh,nCoulh",nDegreh,nCoulh,1,pgG->nSommetEnTout);//affiche les 2 vecteurs, 1 par ligne.
	//bDipoler[]:=la descriptO du sommet courant devra être réduite à un dipôle
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
			bDipoler[sX]=kbSimplifier && pgG->nVal[sX]>=0 && nCoulh[sX]==2;
		//if (1) VecteurVoir1("bDipoler",bDipoler,1,pgG->nSommetEnTout);
	//nGadget:=1er sommet du gadget courant de rang 0
		for (nGadget[1]=sX=1;sX<=pgG->nSommetEnTout;sX++){//O(S)
			int nbPole=( (bDipoler[sX])? nCoulh[sX] : 2+nCoulh[sX]+nCoulh[sX] );
			//d2(sX,nbPole);
			nGadget[sX+1]=nGadget[sX]+nbPole;
			//if (bDans3(sX,25,26,27)) d3(sX,nCoulh[sX],nbPole);
		}
		if (1 || bVoir) VecteurVoir1("nGadget",nGadget,1,pgG->nSommetEnTout+1);
	nbSommet=nGadget[1+pgG->nSommetEnTout]-1;//nbSommet:=nbre de sommets requis pr *ppgC
	//d2(nbSommet,pgG->nArcEnTout);
	//générer ppgC
		if (bVoir) d(nbSommet);
		GrapheCreer(nbSommet,ppgC);
		//générer les gadgets
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
				if (!bDipoler[sX]){//ajouter les arcs qui décrivent K2n, n étant le nbre de couleurs, et n arcs à suivre.
					if (pgG->nVal[sX]<=0)//fond obligatoire;sX ne sera pas traversé ssi le fond est sélectionné.
						GrapheArquer4(*ppgC,nGadget[sX],nGadget[sX]+1,0,100);
					for (uC=1;uC<=nCoulh[sX];uC++){//O(C(sX)) 1 couleur implique l'existence d'1 arc, dc somO bornée par A
						//d2(sX,uC);
						GrapheArquer4(*ppgC,nGadget[sX]+0,nGadget[sX]+1+uC,0,100);//sommet 0 du fond vers précouleurs
						GrapheArquer4(*ppgC,nGadget[sX]+1,nGadget[sX]+1+uC,0,100);//sommet 1 du fond vers précouleurs
						GrapheArquer4(*ppgC,nGadget[sX]+1+uC,nGadget[sX]+1+uC+nCoulh[sX],0,100);//précouleur vers couleur
					}
				}//else aucun arc à ajouter puisque traverser sX est obligatoire
		//relier les gadgets entre eux conformément aux couleurs spécifiées ds pgG
			for (sX=1;sX<=pgG->nSommetEnTout;sX++){//O(A)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					sY=pgG->sSuk[aK];
					sSource=nGadget[sX+1]-nOffset[sX][pgG->coulh[aK]];
					sCible=nGadget[sY+1]-nOffset[sY][pgG->coulh[aK]];
					//d5(sX,sY,aK,sSource,sCible);
					//d2(nOffset[sX][pgG->coulh[aK]],nOffset[sY][pgG->coulh[aK]]);d4(sX,sY,sSource,sCible);
					GrapheArquer4(*ppgC,sSource,sCible,pgG->coulh[aK],pgG->nPoids[aK]);//couleur vers couleur pgG->nPoids[aK]
					//GrapheArquer4(*ppgC,sSource,sCible,pgG->coulh[aK],knPoidsNul);//couleur vers couleur
				}
			}
	//ppgC->nVal[]:=nGadget[] courant:
		for (sX=1,sZ=1;sZ<=(*ppgC)->nSommetEnTout;sZ++){//O(S)
			if (nGadget[sX+1]<=sZ)
				sX++;
			(*ppgC)->nVal[sZ]=sX;
		}
		//d(pgG->nSommetEnTout);
		//VecteurVoir("(*ppgC)->nVal",(*ppgC)->nVal,1,(*ppgC)->nSommetEnTout);
	if (bVoir) GrapheVoir0("pppC",*ppgC,gpPoids);
}//GrapheDecolorer

void GrapheDecrire(graf *pgG){
	//rend un graphe connexe à à pgG->nSommetEnTout sommets (qui est donc une donnée) obtenu en empilant quelques arcs choisis.
	int uArc,uArcMax,aK,sX,sY;
	int bSucc[1+pgG->nSommetEnTout];
	//Appel0("GrapheDecrire");
		Assert2("GrapheDecrire",bGrapheAmorceR,bCroit(1,pgG->nSommetEnTout,kuGrapheSommetLim-1));
		//préparer d'abord un graphe à 1 sommet et aucun arc et faciliter le débogage en razant autant que possible aHed[] et sSuk[]
			pgG->aHed[0]=0;//zèle
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				pgG->aHed[sX]=0;
			pgG->aHed[1]=1;
			for (aK=1;sX<=pgG->nSommetEnTout;aK++)
				pgG->sSuk[aK]=0;
		//lier chaque sommet sX à plusieurs autres sommets, jusqu'à,si possible,sX autres sommets:
			for (pgG->nArcEnTout=0,sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (sY=1;sY<=pgG->nSommetEnTout;sY++)
					bSucc[sY]=kF;//ie sY n'est pas un successeur de sX 
				pgG->aHed[sX+1]=pgG->aHed[sX];
				sY=sX;
				uArcMax=3*sX;
				for (uArc=1;uArc<=uArcMax;uArc++){
					sY=uModulo1(sY+uArcMax,pgG->nSommetEnTout);//tente un sommet successeur sY
					if ( (sY!=sX) && !bSucc[sY] ){//le sommet successeur sY a du sens pour sX et c'est effectivement un nouveau successeur
						pgG->nArcEnTout++;
						pgG->sSuk[aK=pgG->nArcEnTout]=sY;
						pgG->nCapaMax[aK]=1;
						pgG->nCout[aK]=1;
						pgG->aHed[sX+1]++;
						bSucc[sY]=kV;
					}
				}
			}
		//GrapheInverser(pgG);//affecte en O(A) les tableaux aDeh[] et sKus[] qui décrivent le graphe inverse du graphe défini par aHed[] et aSuK[]
		Assert1("GrapheDecrire",bGrapheSimple(pgG));
	//Appel1("GrapheDecrire");
}//GrapheDecrire

void GrapheDedoubler(int sDedoublota,int nGenreDePoids,graf **ppgG){//O(A)
	//dédouble le sommet sDedoublota
	Assert2("GrapheDedoubler",bCroit(1,sDedoublota,(*ppgG)->nSommetEnTout),bGrapheAttribuT(nGenreDePoids));
	int bVoir=0;
	int nArcat,nCopiota,aK,sX,nDecalage;
	if (bVoir) GrapheVoir0("*ppgG AVANT dédoublement",*ppgG,gpCout);
		Assert1("GrapheDedoubler0",bGrapheSimple(*ppgG));
		GrapheSommer(*ppgG,1);
		int sSommetEnSus=(*ppgG)->nSommetEnTout;
		//tout arc qui part de sDedoublota part aussi de sSommetEnSus
			nCopiota=(*ppgG)->aHed[sDedoublota+1]-(*ppgG)->aHed[sDedoublota];
			if (bVoir) d3(sDedoublota,sSommetEnSus,nCopiota);
			for (nArcat=(*ppgG)->nArcEnTout,aK=(*ppgG)->aHed[sDedoublota];aK<(*ppgG)->aHed[sDedoublota+1];aK++){
				(*ppgG)->sSuk[++nArcat]=(*ppgG)->sSuk[aK];
				GrapheAttribueR(*ppgG,nArcat,nGenreDePoids,*ppgG,aK);
			}
			(*ppgG)->nArcEnTout=nArcat;
			(*ppgG)->aHed[(*ppgG)->nSommetEnTout+1]=nArcat+1;
		if (bVoir) GrapheScruter("tout arc qui part de sDedoublota recopié au bout",*ppgG,+1,!k1Detailler);
		Assert1("GrapheDedoubler1",bGrapheSimple(*ppgG));
		//tout arc qui part de sDedoublota est supprimé, sauf le premier
			nDecalage=nCopiota-1;
			if (bVoir) d3(nCopiota,nDecalage,nArcat);
			for (aK=(*ppgG)->aHed[sDedoublota+1];aK<=(*ppgG)->nArcEnTout;aK++){
				(*ppgG)->sSuk[aK-nDecalage]=(*ppgG)->sSuk[aK];
				GrapheAttribueR(*ppgG,aK-nDecalage,nGenreDePoids,*ppgG,aK);
			}
			for (sX=sDedoublota+1;sX<=(*ppgG)->nSommetEnTout+1;sX++)
				(*ppgG)->aHed[sX]=(*ppgG)->aHed[sX]-nDecalage;
			(*ppgG)->nArcEnTout=(*ppgG)->nArcEnTout-nDecalage;
			if (bVoir) d2((*ppgG)->nArcEnTout,(*ppgG)->aHed[(*ppgG)->nSommetEnTout+1]);
		if (bVoir) GrapheScruter("tout arc qui sort de sDedoublota est supprimé (sauf 1)",*ppgG,+1,!k1Detailler);
		//un arc unique part de sSommet à destination de sSommetEnSus
			aK=(*ppgG)->aHed[sDedoublota];
			(*ppgG)->sSuk[aK]=sSommetEnSus;
		Assert1("GrapheDedoubler2",bGrapheSimple(*ppgG));
	Assert1("GrapheDedoubler1",bGrapheSimple(*ppgG));
	if (bVoir) GrapheVoir0("ppgG APRES dédoublement",*ppgG,gpCout);
}//GrapheDedoubler

int nGrapheDegreh(graf *pgG,int sSommet,int tMode){//O(A)
	//tMode= -1: degré entrant, 0: entrant+sortant, +1: sortant.
	int aK,nDegreh,nEntrant,nSortant;
	Assert3("nGrapheDegreh",bGrapheSimple(pgG),bGrapheSommet(pgG,sSommet),bTrit(tMode) );
	if (tMode>=0)
		for (nEntrant=0,aK=1;aK<=pgG->nArcEnTout;aK++)
			if (sSommet==pgG->sSuk[aK])
				nEntrant++;
	nSortant=pgG->aHed[sSommet+1]-pgG->aHed[sSommet];
	if (tMode<0) nDegreh=nEntrant;
	if (tMode==0) nDegreh=nEntrant+nSortant;
	if (tMode>0) nDegreh=nSortant;
	return(nDegreh);
}//nGrapheDegreh

void GrapheDegrer(graf *pgG,int tMode){//O(SA)
	//pgG->nVal[sX]=degré de sX; tMode= -1: degré entrant, 0: entrant+sortant, +1: sortant.
	Assert2("nGrapheDegreh",bGrapheSimple(pgG),bTrit(tMode) );
	for (int sX=1;sX<=pgG->nSommetEnTout;sX++)
		pgG->nVal[sX]=nGrapheDegreh(pgG,sX,tMode);
}//GrapheDegrer

void GrapheDelimiter(graf *pgG,int uArcIndex,int *psOrigine,int *psDestination){//O(A)
	//rend les sommets qui délimitent l'arc de rang1 uArcIndex dans pgG;déroute si uArcIndex n'est pas l'index d'un arc de pgG.
	int aK,sX;
	Assert3("GrapheDelimiteR1",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	//d2(uArcIndex,pgG->nArcEnTout);
	Assert1("GrapheDelimiteR2",bCroit(1,uArcIndex,pgG->nArcEnTout));
		for (*psOrigine=0,*psDestination=0,sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				if (aK==uArcIndex){
					*psOrigine=sX;
					*psDestination=pgG->sSuk[aK];
				}
		}
	Assert2("GrapheDelimiteR3",*psOrigine>0,*psDestination>0);
}//GrapheDelimiter

void GrapheDerouler(graf *pgPatron,int bCirculaire,graf *pgG){
	//déroule pgPatron ds pgG supposé alloué.
	const int bInfo=kF;
	int nArcInterEtage,uColonne0,uColonne1,uEntresol,sX,sY;
	int nbSommet=pgPatron->nSommetEnTout;
	if (bInfo) Appel0("GrapheDerouler");
		//if (bInfo) d4(nbSommet,pgG->nSommetEnTout,nSelecteurSommetEnTout,udPas);
		if (bInfo) GrapheVoir0("Graphe pas encore déroulé",pgG,gpCouleur);
		//relier les étages entre eux
			for (nArcInterEtage=0,uEntresol=1;uEntresol<nbSommet+bCirculaire;uEntresol++)
				for (uColonne0=1;uColonne0<=nbSommet;uColonne0++){
					sX=1+(uEntresol-1)*nbSommet+(uColonne0-1);
					for (uColonne1=1;uColonne1<=nbSommet;uColonne1++)
						if ( bGrapheArc(pgPatron,uColonne0,uColonne1) ){
								sY=1+(uEntresol)*nbSommet+(uColonne1-1);
					//d5(nbSommet,uColonne0,uColonne1,sX,sY);
								if (bCirculaire)
									sY=uModulo1(sY,nbSommet*nbSommet);
								if (bInfo) d2(sX,sY);
								GrapheArquer0(pgG,sX,sY,gpCouleur,uColonne1);//couleur de la colonne atteinte
								nArcInterEtage++;
							}
				}
		if (bInfo) GrapheVoir0("Graphe déroulé",pgG,gpCouleur);
	if (bInfo) Appel1("GrapheDerouler");
}//GrapheDerouler

void GrapheDeplier(graf *pgG){
	//transforme pgG=(S,A) de façon à obtenir un dag à S*S sommets: à chaque arc (sX,sY) de pgG,on associe S-1 arcs (sXi,sYj) avec 1≤i<S et j=i+1. 
	const int bVoir=kF;
	int uEtage,aK,aKlim,sX;
	if (bVoir) Appel0("GrapheDeplier");
		Assert3("GrapheDeplier1",bGrapheAmorceR,pgG->nSommetEnTout>0,bGrapheSimple(pgG));
		Assert2("GrapheDeplier2",pgG->nSommetEnTout*pgG->nSommetEnTout<kuGrapheSommetLim,pgG->nArcEnTout*(pgG->nSommetEnTout-1)<kuGrapheArcLim);
		//affecter pgG->sSuk[]: chague arc relie un sommet source de l'étage uEtage à un sommet cible de l'étage uEtage+1 (uEtage=1 ssi 1er étage):
			for (uEtage=pgG->nSommetEnTout-1;uEtage>=1;uEtage--)
				for (aK=pgG->nArcEnTout;aK>=1;aK--)
					pgG->sSuk[aK+(uEtage-1)*pgG->nArcEnTout]=pgG->sSuk[aK]+uEtage*pgG->nSommetEnTout;
		//affecter pgG->aHed[] hors dernier étage: chague sommet source n'a pour successeurs que des sommets situés à l'étage suivant:
			for (uEtage=2;uEtage<=pgG->nSommetEnTout-1;uEtage++)
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					pgG->aHed[sX+(uEtage-1)*pgG->nSommetEnTout]=pgG->aHed[sX+(uEtage-2)*pgG->nSommetEnTout]+pgG->nArcEnTout;
		//affecter pgG->aHed[] pour le dernier étage: les sommets du dernier étage n'ont aucun successeur
			aKlim=pgG->nArcEnTout*(pgG->nSommetEnTout-1)+1;
			if (bVoir) d(pgG->nSommetEnTout*pgG->nSommetEnTout);
			if (bVoir) d(aKlim);
			if (bVoir) VecteurVoir("pgG->aHed AVANT",pgG->aHed,1,pgG->nSommetEnTout*pgG->nSommetEnTout+1);
			if (bVoir) VecteurVoir("pgG->sSuk AVANT",pgG->sSuk,1,aKlim);
			for (sX=pgG->nSommetEnTout;sX>=1;sX--)
				pgG->aHed[(pgG->nSommetEnTout-1)*pgG->nSommetEnTout+sX]=aKlim;
			pgG->aHed[pgG->nSommetEnTout*pgG->nSommetEnTout+1]=aKlim;
		//affecter pgG->nArcEnTout et pgG->nSommetEnTout
			pgG->nArcEnTout=aKlim-1;
			pgG->nSommetEnTout=pgG->nSommetEnTout*pgG->nSommetEnTout;
		if (bVoir) VecteurVoir("pgG->aHed APRES",pgG->aHed,1,pgG->nSommetEnTout+1);
		if (bVoir) VecteurVoir("pgG->sSuk APRES",pgG->sSuk,1,aKlim);
		Assert2("GrapheDeplier3",bGrapheSimple(pgG),!bGrapheCircuite(pgG,!k1Afficher));
	if (bVoir) Appel1("GrapheDeplier");
}//GrapheDeplier

float fGrapheDensiteh(graf *pgSimple,int bDigraphe,int zdAfficher){
	//rend densité du graphe simple pgSimple orienté ou non,ou -1 si non défini.
	//Si non orienté, 2 arcs opposés représentent 1 arête et le calcul de la densité s'effectue sur un graphe qui n'a que des arcs.
	Assert2("fGrapheDensiteh0",bGrapheSimple(pgSimple),bBool(bDigraphe));
	int nSommetEnTout=pgSimple->nSommetEnTout,nbArcSiGrapheComplet,bSymetrique=bGrapheSymetrique(pgSimple);
	const float kfDensitehNonDefinie=-1.0;
	float fDensiteh;
	if (bDigraphe || bSymetrique){//la densité en mode non orienté n'a pas de sens si non symétriq.
		nbArcSiGrapheComplet=nSommetEnTout*(nSommetEnTout-1);//que pgSimple soit orienté ou non.
		fDensiteh=(pgSimple->nSommetEnTout>1)? pgSimple->nArcEnTout*1.0/nbArcSiGrapheComplet : kfDensitehNonDefinie;
	}else fDensiteh=kfDensitehNonDefinie;
	Assert1("fGrapheDensiteh9",fabs(fDensiteh)<=1.0 || fDensiteh==kfDensitehNonDefinie);
	if (zdAfficher>0)
		printf("\tLa densité du graphe %s vaut %s.\n",sNiet(!bSymetrique,"orienté"),sReel(fDensiteh));
	if (zdAfficher>1)
		if (fDensiteh>=0){
			if (bDigraphe)
				printf("%sC'est la valeur du rapport Arc/ArcMax avec ArcMax=S*(S-1)",flag);
			else printf("%sC'est la valeur du rapport Arete/AreteMax avec Arete=Arc/2 et AreteMax=S*(S-1)/2",flag);
			printf(", soit %d/(%d*%d).\n",pgSimple->nArcEnTout,nSommetEnTout,nSommetEnTout-1);
		}else printf("%sEn effet, elle est non définie.\n",flag);
	return(fDensiteh);//Testez la densité de K4 orienté, puis non orienté. C'est facile à vérifier, et éclairant.
}//fGrapheDensiteh

int bGrapheDesareter(graf *pgG,int sExtremiteh0,int sExtremiteh1){//O(A)
	//retire de pgG l'arête (sExtremiteh0,sExtremiteh1) s'il existe;rend vrai ssi l'arête a pu être retirée ——donc elle existait à l'appel de la routine. 
	Assert2("bGrapheDesareter0",bGrapheAmorceR,bGraphe(pgG));
	int bDesareter=bGrapheSommet(pgG,sExtremiteh0) && bGrapheSommet(pgG,sExtremiteh1);
	bDesareter=bDesareter && bGrapheDesarquer(pgG,sExtremiteh0,sExtremiteh1);
	bDesareter=bDesareter && bGrapheDesarquer(pgG,sExtremiteh1,sExtremiteh0);
	Assert2("bGrapheDesareter1",bGraphe(pgG),bBool(bDesareter));
	return(bDesareter);
}//bGrapheDesareter

void GrapheDesarquer(graf *pgG,int sOrigine,int sDestination){//O(A)
	//d2(sOrigine,sDestination);
	int bDesarquer=bGrapheDesarquer(pgG,sOrigine,sDestination);
	Assert1("GrapheDesarquer UN",bDesarquer);
}//GrapheDesarquer

int bGrapheDesarquer(graf *pgG,int sOrigine,int sDestination){//O(A)
	//retire de pgG l'arc (sOrigine,sDestination) s'il existe;rend vrai ssi l'arc a pu être retiré ——donc il existait à l'appel de la routine. 
	int aK,aL,sX;
	Assert2("bGrapheDesarquer0",bGrapheAmorceR,bGraphe(pgG));
	int bDesarquer=bGrapheSommet(pgG,sOrigine) && bGrapheSommet(pgG,sDestination);
	if (bDesarquer){
		//aL soit l'index de l'arc (sOrigine,sDestination) dans sSuk[], ou 0 si non défini.
			for (aL=0,aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
				if (pgG->sSuk[aK]==sDestination)
					aL=aK;//unique vu Assert3(bGrapheDesarquer0,…,bGrapheSimple(pgG));
		bDesarquer=(aL>0);
	}
	if (bDesarquer){//l'arc (sOrigine,sDestination) existe bien dans pgG et son index dans sSuk[] est aL.
		//retirer l'arc de rang1 aL crée un trou en sSuk[aL]; le combler en tassant à gauche les éléments de sSuk situés au-delà de sSuk[aL]: 
			for (aK=aL;aK<pgG->nArcEnTout;aK++){
				pgG->sSuk[aK]=pgG->sSuk[aK+1];
				pgG->nCapaMin[aK]=pgG->nCapaMin[aK+1];
				pgG->nCapaMax[aK]=pgG->nCapaMax[aK+1];
				pgG->coulh[aK]=pgG->coulh[aK+1];
				pgG->nCout[aK]=pgG->nCout[aK+1];
				pgG->nPoids[aK]=pgG->nPoids[aK+1];
			}
			pgG->sSuk[pgG->nArcEnTout]=0;
		//décrémenter tous les éléments de aHed[] situés après pgG->aHed[sOrigine] pour pouvoir accéder aux éléments de sSuk[] qui ont été décalés:
			for (sX=sOrigine;sX<=pgG->nSommetEnTout;sX++)
				pgG->aHed[sX+1]--;
		pgG->nArcEnTout--;
	}
	Assert2("bGrapheDesarquer1",bGraphe(pgG),bBool(bDesarquer));
	return(bDesarquer);
}//bGrapheDesarquer

void GrapheDesarquerTout(graf *pgG,int sAccroche){
	//retire de pgG tous les arcs éventuels incidents à sAccroche (ne fait rien si aucun arc de pgG n'a sAccroche pour origine ou destination).
	int bIncidence,nIncidence0,nIncidence1;
	int aK,sX,sY;
	Assert3("GrapheDesarquerTout1",bGrapheAmorceR,bGraphe(pgG),bGrapheSommet(pgG,sAccroche));
	//retirer ts les arcs éventuels qui ont pour origine sAccroche
		nIncidence0=0;
		While(pgG->nSommetEnTout);
		do {
			for (bIncidence=kF,aK=pgG->aHed[sAccroche];aK<pgG->aHed[sAccroche+1]; aK++){
				sY=pgG->sSuk[aK];
				bIncidence=bGrapheDesarquer(pgG,sAccroche,sY) || bIncidence;
			}
			nIncidence0++;
		} while (bWhile("GrapheDesarquerTout11",bIncidence));
	Assert3("GrapheDesarquerTout2",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	//retirer ts les arcs éventuels qui ont pour destination sAccroche
		nIncidence1=0;
		While(pgG->nSommetEnTout);
		do {
			for (bIncidence=kF,sX=1; sX<=pgG->nSommetEnTout; sX++)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1]; aK++){
					sY=pgG->sSuk[aK];
					if (sY==sAccroche){
						bIncidence=bGrapheDesarquer(pgG,sX,sAccroche) || bIncidence;
					}
				}//for aK
			nIncidence1++;
		} while (bWhile("GrapheDesarquerTout22",bIncidence));
	Assert2("GrapheDesarquerTout3",bGrapheAmorceR,bGraphe(pgG));
}//GrapheDesarquerTout

void GrapheDupliquer(graf *pgOriginal,graf **ppgCopie){
	int aK;
	int sX;
	Assert3("GrapheDupliquer0",bGrapheAmorceR,bGraphe(pgOriginal),ppgCopie!=NULL);
	(*ppgCopie)->nSommetEnTout=pgOriginal->nSommetEnTout;
	(*ppgCopie)->nArcEnTout=pgOriginal->nArcEnTout;
	for (sX=1;sX<=pgOriginal->nSommetEnTout+1;sX++){
		(*ppgCopie)->aHed[sX]=pgOriginal->aHed[sX];//dont aHed[pgOriginal->nSommetEnTout+1]
		(*ppgCopie)->aDeh[sX]=pgOriginal->aDeh[sX];//dont aDeh[pgOriginal->nSommetEnTout+1]
		(*ppgCopie)->sPer[sX]=pgOriginal->sPer[sX];
	}
	for (aK=1;aK<=pgOriginal->nArcEnTout;aK++){
		(*ppgCopie)->sSuk[aK]=pgOriginal->sSuk[aK];
		(*ppgCopie)->sKus[aK]=pgOriginal->sKus[aK];
		(*ppgCopie)->aInv[aK]=pgOriginal->aInv[aK];
		(*ppgCopie)->nCapaMax[aK]=pgOriginal->nCapaMax[aK];
		(*ppgCopie)->nCapaMin[aK]=pgOriginal->nCapaMin[aK];
		(*ppgCopie)->nCout[aK]=pgOriginal->nCout[aK];
		(*ppgCopie)->nPoids[aK]=pgOriginal->nPoids[aK];
		(*ppgCopie)->aArcTo[aK]=pgOriginal->aArcTo[aK];
		(*ppgCopie)->nVal[aK]=pgOriginal->nVal[aK];
		(*ppgCopie)->coulh[aK]=pgOriginal->coulh[aK];
	}
	Assert2("GrapheDupliquer1",bGrapheAmorceR,bGraphe(*ppgCopie));
}//GrapheDupliquer

void GrapheEmpiler(graf *pgEmpilota,int nGenreDePoids,graf *pgG){
	//empile sur pgG une occurrence de pgEmpilota, les sommets de pgEmpilota étant renumérotés.
	Assert1("GrapheEmpiler",bGrapheAttribuT(nGenreDePoids));
	int aK,aL,sX,sY;
	int nOffset=pgG->nSommetEnTout;
	GrapheSommer(pgG,pgEmpilota->nSommetEnTout);
	for (sX=1;sX<=pgEmpilota->nSommetEnTout;sX++)
		for (aK=pgEmpilota->aHed[sX];aK<pgEmpilota->aHed[sX+1];aK++){
			sY=pgEmpilota->sSuk[aK];
			GrapheArquer(pgG,nOffset+sX,nOffset+sY);
			aL=nGrapheArc(pgG,nOffset+sX,nOffset+sY);
			GrapheAttribueR(pgEmpilota,aK,nGenreDePoids,pgG,aL);
		}
}//GrapheEmpiler

void GrapheEtoiler(graf *pgG,int uEtoile,int nBrancheParEtoile){
	//empile sur pgG uEtoile composantes connexes. Chacune est une étoile. Traite aussi le cas limite: une étoile avec 0 branche.
	int uB,uE;
	Assert2("GrapheEtoiler",uEtoile>0,nBrancheParEtoile>=0);
	int uSommetParEtoile=1+nBrancheParEtoile;
	int nSommet=pgG->nSommetEnTout;
	//d(pgG->nSommetEnTout+uEtoile*uSommetParEtoile);
	Assert1("GrapheEtoiler aHed",pgG->nSommetEnTout+uEtoile*uSommetParEtoile<kuGrapheSommetLim);
	for (uE=1;uE<=uEtoile*uSommetParEtoile;uE++)
		pgG->aHed[nSommet+uE+1]=pgG->aHed[nSommet+uE];
	pgG->nSommetEnTout+=uEtoile*uSommetParEtoile;
	Assert1("GrapheEtoiler sSuk",pgG->nArcEnTout+uEtoile*uSommetParEtoile<kuGrapheArcLim);
	for (uE=1;uE<=uEtoile;uE++)
		for (uB=1;uB<=nBrancheParEtoile;uB++)
			GrapheArquer(pgG,nSommet+uSommetParEtoile*(uE-1)+1,nSommet+uSommetParEtoile*(uE-1)+1+uB);
}//GrapheEtoiler

int bGrapheEulerien(graf *pgG,int bDigraphe,int szSource,int szTrappe,int bAfficher){
	//vrai ssi pgG admet un parcours eulérien ouvert de szSource à szTrappe ≠0 et distincts, ou fermé si szSource=szTrappe=0. Ignore les arcs de coulh ≠0.
	Assert2("bGrapheEulerien0",bBool(bDigraphe),bBool(bAfficher) );
	int nDegreh[2][1+pgG->nSommetEnTout],sImpair[1+2];
	int bEulerien=0,bEquilibreh,nImpair,nImpairEnTout,aK,aL,sX;
	Appel0("bGrapheEulerien");
	Assert3("bGrapheEulerien1",bGrapheAmorceR,pgG->nSommetEnTout>0,(szSource==0)==(szTrappe==0));//"source existe" <=> "trappe existe"
	GrapheInverser(pgG);//O(A); nott pr calculer nDegreh[0] sur digraphe
	//if (bDigraphe) 
	//Assert11("bGrapheEulerien00,bDigraphe",!bDigraphe,bDigraphe);//bridé pr le moment
	if (!bDigraphe){
		Assert2("bGrapheEulerien148",pgG->aDeh[1]>0,bGrapheSymetrique(pgG));
		if (szSource!=0)
			Assert3("bGrapheEulerien3",szSource!=szTrappe,bGrapheSommet(pgG,szSource),bGrapheSommet(pgG,szTrappe));
		if ( bGrapheConnexe(pgG) ){
			//nDegreh[0/1][sX]:=degré entrant/sortant du sommet sX pour tout sX
				VecteurRazer(nDegreh[0],1,pgG->nSommetEnTout);
				VecteurRazer(nDegreh[1],1,pgG->nSommetEnTout);
				for (sX=1;sX<=pgG->nSommetEnTout;sX++){
					//nDegreh[1][sX]+=degré sortant de sX,ie le nb de successeurs de sX
						for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
							if ( bGrapheEulerienArC(pgG,aK) )
								nDegreh[1][pgG->sSuk[aK]]++;
					//nDegreh[0][sX]+=degré entrant de sX,ie le nb de prédécesseurs de sX
						for (aL=pgG->aDeh[sX];aL<pgG->aDeh[sX+1];aL++)
							if ( bGrapheEulerienArC(pgG,aL) )
								nDegreh[0][pgG->sKus[aL]]++;
				}
				if (0){
					ModeCaractere(-1);
						VecteurVoir("nDegreh[0]",nDegreh[0],1,pgG->nSommetEnTout);
						VecteurVoir("nDegreh[1]",nDegreh[1],1,pgG->nSommetEnTout);
					ModeCaractere(+1);
				}
			//nImpairEnTout:=nb de sommets de degré total impair
				for (nImpairEnTout=0,sX=1;sX<=pgG->nSommetEnTout;sX++){
					int bImpair=(nDegreh[0][sX]+nDegreh[1][sX])%(2*(1+!bDigraphe))!=0;//1 arête = 2 arcs, d'où 1+!bDigraphe.
					nImpairEnTout+=bImpair;
					if (bImpair && nImpairEnTout<=2)
						sImpair[nImpairEnTout]=sX;
				}
			if (bDigraphe){
				if (szSource!=0){
					for (bEquilibreh=1,sX=1;sX<=pgG->nSommetEnTout && bEquilibreh;sX++){
						if (sX!=szSource && sX!=szTrappe)
							bEquilibreh=nDegreh[0][sX]==nDegreh[1][sX];
						else if (sX==szSource)
							bEquilibreh=nDegreh[1][sX]==nDegreh[0][sX]+1;
						else bEquilibreh=nDegreh[0][sX]==nDegreh[1][sX]+1;
					}
				}else for (bEquilibreh=1,sX=1;sX<=pgG->nSommetEnTout && bEquilibreh;sX++)
						if (nDegreh[0][sX]!=nDegreh[1][sX])
							bEquilibreh=nDegreh[0][sX]==nDegreh[1][sX];
				//d(bEquilibreh);
				bEulerien=bEquilibreh;
			}else if (bGrapheSymetrique(pgG))
				if (szSource!=0){
					for (bEulerien=1,sX=1;sX<=pgG->nSommetEnTout && bEulerien;sX++)
						if (sX!=szSource && sX!=szTrappe)
							bEulerien=bEulerien && bPair(nDegreh[0][sX]+nDegreh[1][sX]);
				}else bEulerien=nImpairEnTout<=2;
			//d4(szSource,szTrappe,nImpairEnTout,bEulerien);
			if (bAfficher){
				printf("\tCe graphe %s eulérien car ",sEst(bEulerien));
				if (!bEulerien){
					printf( (bDigraphe)? "ses sommets ne sont pas équilibrés: " : "il a plus de 2 sommets impairs: ");
					for (nImpair=0,sX=1;sX<=pgG->nSommetEnTout || bPrint(" sont impairs.");sX++)
						if ((nDegreh[0][sX]+nDegreh[1][sX])%4!=0)
							printf("%s%s",sEnt(sX),sEtc(++nImpair,nImpairEnTout));
				}else if (nImpairEnTout==2)
					printf("il a exactement 2 sommets de degré impair: %s et %s.\n",sEnt(sImpair[1]),sEnt(sImpair[2]));
				else printf("tous ses sommets sont de degré pair.\n");
			}
		}else if (bAfficher) printf("\tCe graphe n'est pas eulérien car il n'est pas connexe.\n");
	}else printf("Le parcours eulérien d'un digraphe %s",nada);
	Appel1("bGrapheEulerien");
	return(bEulerien);
}//bGrapheEulerien

int bGrapheEulerienArC(graf *pgG,int aK){
	//dédié bGrapheEulerien & GrapheEulerieR
	const int kbCensurer=0;
	int bArc=!kbCensurer || pgG->coulh[aK]==0;
	return(bArc);
}//bGrapheEulerienArC

void GrapheEulerieR(graf *pgG,int bDigraphe,int szSource,int szTrappe,int bAfficher){
	//rend dans pgG->nVal un parcours eulérien qui va de szSource à szTrappe ——donc fermé ssi szSource=szTrappe. rend faux ssi impossible;
	const int kbVoir=0;
	int nSommat,nGreffe=0,nMalloc=0,nPasse;
	int aNext[kuGrapheSommetLim];
	int aK,sX,sY;
	typedef struct{
		int	 sVertex;
		void *pLien;
	}cellule,*pcellule;
	cellule *pcListe,*pcGreffe,*pcInsert,*pcSuivant,*pcPrecedent;
	if (kbVoir) Appel0("GrapheEulerieR");
		Assert1("GrapheEulerieR178",bDigraphe || bGrapheSymetrique(pgG));
		GrapheEulerierInitialiseR(pgG,bDigraphe,kbVoir,aNext);
		//pcListe contienne une liste de cellules; chaque cellule mémorise le sommet courant rencontré lors de l'exploration du graphe.
			pcListe=malloc(sizeof(cellule));nMalloc++;pcListe->sVertex=(szSource)? szSource : 1;pcListe->pLien=NULL;
		//pcInsert pointe dans pcListe la cellule courante après laquelle le prochain parcours sera inséré.
			pcInsert=pcListe;
			if (kbVoir) d2(szSource,pcListe->sVertex);
			nSommat=1;//nombre courant d'occurrences de sommets rencontrés jusqu'ici ds le parcours
		//aNext[sX] indexe un arc sortant non encore exploré d'origine sX; cet arc existe aussi longtemps que aNext[sX]<pgG->aHed[sX+1].
			nPasse=0;//nbre d'itérations ds la boucle principale ci-dessous
			While(pgG->nArcEnTout+pgG->nSommetEnTout);
			do{//si un sX dans pcInsert a des arcs non encore explorés,explorer ce sommet et greffer le parcours obtenu sur le parcours principal:
				sX=pcInsert->sVertex;
				if (bDigraphe)
					aK=aNext[sX];
				else aK=aGrapheEulerierNextArC(pgG,bDigraphe,sX,aNext);
				if (kbVoir) d4(++nPasse,sX,aK,pgG->aHed[sX+1]);
				if (bDigraphe) sY=sX;//superflu si non orienté
				if (aK<pgG->aHed[sX+1] && bGrapheEulerienArC(pgG,aK) ){//un arcs sortant non encore exploré a été détecté
					if (kbVoir) printf("Exploration à partir d'un nouvel arc sortant du sommet %s.\n",sEnt(sX));
					//partir du sommet sX et traverser un maximum d'arcs non encore explorés
						pcGreffe=NULL;
						nGreffe++;if (kbVoir) printf("greffe n°%d:\n",nGreffe);
						While(1+pgG->nArcEnTout);
						do {
							if (bDigraphe){
								aNext[sY]++;
								sY=pgG->sSuk[aK];
							}else {
								sY=pgG->aArcTo[aK];
								//d2(aK,sY);
							}
							if (kbVoir) printf("\tsY=%d ",sY);
							pcSuivant=malloc(sizeof(cellule));nMalloc++;
							pcSuivant->sVertex=sY;
							if (pcGreffe==NULL)
								pcGreffe=pcSuivant;
							else pcPrecedent->pLien=pcSuivant;
							pcPrecedent=pcSuivant;
							nSommat++;
							if (!bDigraphe) pgG->aArcTo[aK]=0;//superflu si orienté
							if (!bDigraphe) pgG->aArcTo[pgG->aInv[aK]]=0;//superflu si orienté
							//aK=aGrapheEulerierNextArC(pgG,sY,aNext);
							if (bDigraphe)
								aK=aNext[sY];
							else aK=aGrapheEulerierNextArC(pgG,bDigraphe,sY,aNext);
							if (kbVoir) d3(sY,aK,pgG->aHed[sY+1]);
						}while( bWhile("GrapheEulerieR1",aK!=pgG->aHed[sY+1]) );
					if (kbVoir) printf(".\n");
					//greffer le parcours secondaire
						pcSuivant->pLien=pcInsert->pLien;//la cellule qui suit la dernière cellule du parcours secondaire pcSuivant est la cellule pcInsert->pLien.
						pcInsert->pLien=(pcellule) pcGreffe;//la première cellule de la liste secondaire
				}else pcInsert=pcInsert->pLien;
			}while ( bWhile("GrapheEulerieR2",pcInsert!=NULL) );
			//d2(nSommat,pgG->nArcEnTout);
			//Assert1("GrapheEulerieR245",nSommat==1+pgG->nArcEnTout/(2-bDigraphe));//les arcs de pgG non symétrisé ont bien été exploités TOUS et exactement une fois
		//pgG->nVal[]:=copie des 1+pgG->nArcEnTout sommets stockés dans la liste chaînée accessible depuis la cellule pcListe:
			pcInsert=pcListe;
			VecteurRazer(pgG->nVal,1,nSommat);
			for (aK=1;aK<=nSommat;aK++){
				pgG->nVal[aK]=pcInsert->sVertex;
				pcSuivant=pcInsert->pLien;
				free(pcInsert);nMalloc--;
				pcInsert=pcSuivant;
			}
			Assert1("GrapheEulerieR4",pcInsert==NULL);
		//d(nSommat);
		pgG->nVal[0]=nSommat;
		if (bAfficher)
			VecteurVoir0("Le parcours eulérien ci-dessous est stocké ds pgG->nVal",pgG->nVal);
		//vérifier que toute cellule allouée a été restituée
			Assert11("GrapheEulerieR:nMalloc non nul,nMalloc",nMalloc==0,nMalloc);
			pgG->nVal[0]=pgG->nArcEnTout/(2-bDigraphe);
	if (kbVoir) Appel1("GrapheEulerieR");
}//GrapheEulerieR

int bGrapheEulerier(graf *pgG,int bDigraphe,int szSource,int szTrappe){
	//si défini, pgG->nVal[]:= parcours eulérien ouvert de szSource à szTrappe ≠0 et distincts, ou fermé si szSource=szTrappe=0. Ignore les arcs de coulh ≠0.
	int bVoir=0;
	int bEulerier,bFermeh;
	Assert4("bGrapheEulerier1",bGrapheAmorceR,bBool(bDigraphe),pgG->nSommetEnTout>0,(szSource==0)==(szTrappe==0));//"source existe" <=> "trappe existe"
	if (szSource!=0) Assert2("bGrapheEulerier2",bGrapheSommet(pgG,szSource),bGrapheSommet(pgG,szTrappe));
	if (!bDigraphe)
		GrapheSymetriser(pgG,gpCouleur+gpCout);
	GrapheInverser(pgG);
	bEulerier=bGrapheEulerien(pgG,bDigraphe,szSource,szTrappe,0 && bVoir);//appelle GrapheInverser
	bFermeh=bEgal3(szSource,szTrappe,0);
	if (bVoir) 
		printf("Ce graphe %s un parcours eulérien %s défini par une séquence d'%ss.\n",sOui(bEulerier,"admet"),sChoix(bFermeh,"fermé","ouvert"),sChoix(bDigraphe,"arc","arête"));
	if (bEulerier)
		GrapheEulerieR(pgG,bDigraphe,szSource,szTrappe,bVoir);
	if (bEulerier && bVoir) VecteurVoir0("bGrapheEulerier:pgG->nVal",pgG->nVal);
	Assert1("bGrapheEulerier9",!bEulerier || pgG->nVal[0]);
	return(bEulerier);
}//bGrapheEulerier

void GrapheEulerierInitialiseR(graf *pgG,int bDigraphe,int bVoir,int aNext[]){
	int aK,sX,sY;
	if (!bDigraphe){
		VecteurCopier(pgG->aHed,1,pgG->nSommetEnTout,aNext);
		VecteurRaz(pgG->aArcTo,pgG->nArcEnTout);
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//bcle superflue si le graphe est orienté
			for (aK=pgG->aHed[sX];sY=pgG->sSuk[aK],aK<pgG->aHed[sX+1];aK++)
				if ( sX<sY ){
					pgG->aArcTo[aNext[sX]]=sY;
					pgG->aArcTo[aNext[sY]]=sX;
					pgG->aInv[aNext[sX]]=aNext[sY];
					pgG->aInv[aNext[sY]]=aNext[sX];
					aNext[sX]++;aNext[sY]++;
				}
	}
	VecteurCopier(pgG->aHed,1,pgG->nSommetEnTout,aNext);
	if (bVoir) VecteurVoir1("aNext",aNext,1,pgG->nSommetEnTout);
}//GrapheEulerierInitialiseR

int aGrapheEulerierNextArC(graf *pgG,int bDigraphe,int sX,int aNext[]){
	//rend l'arc suivant sortant de sX
	int bVoir=0;
	if (bVoir) d6(bDigraphe,sX,aNext[sX],pgG->aHed[sX+1],pgG->aArcTo[aNext[sX]],bGrapheEulerienArC(pgG,aNext[sX]));
	if (!bDigraphe)//les arêtes étant implémentées par 2 arcs opposés, si l'un de ces arcs a été exploité, sauter l'arc opposé,et cela concerne…
		while( aNext[sX]<pgG->aHed[sX+1] && (pgG->aArcTo[aNext[sX]]==0 || !bGrapheEulerienArC(pgG,aNext[sX])) ){//…ttes les arêtes incidentes à sX.
			aNext[sX]++;
			if (bVoir) d5(sX,aNext[sX],pgG->aHed[sX+1],pgG->aArcTo[aNext[sX]],bGrapheEulerienArC(pgG,aNext[sX]));
		}
	int aSuivant=aNext[sX];
	Assert1("aGrapheEulerierNextArC",bGrapheEulerienArC(pgG,aSuivant) || aSuivant==pgG->aHed[sX+1] );
	return(aSuivant);
}//aGrapheEulerierNextArC

void GrapheExplorer(graf *pgG,int bLargeurSinonProfondeur,int tMode,int mtAfficher){//O(A)
	//explore pgG en bLargeurSinonProfondeur d'abord;pgG->nVal:=bMarque (tMode=0) ou nVisite (tMode<0), selon bVisiteSinonMarquage.pgG->sPer:=pères (tMode>0).
	const int kbVoir=(mtAfficher==2);
	const char *ksTableau="nVisite,bMarque,sPer";
	int udMode=2+tMode,nV=0,sX,sX0=1,sY,sZ;
	int bCircuitDetecter=mtAfficher>1;
	int sCirkwi[1+pgG->nSommetEnTout],bMarque[1+pgG->nSommetEnTout],aNext[1+pgG->nSommetEnTout],nVisite[1+pgG->nSommetEnTout];
	if (kbVoir) Appel0(sC3b("GrapheExplorer() en mode",(bLargeurSinonProfondeur)?"largeur":"profondeur","d'abord"));
		Assert6("GrapheExplorer",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),bBool(bLargeurSinonProfondeur),bTrit(tMode),bCroit(-1,mtAfficher,2));
			VecteurCopier(pgG->aHed,1,pgG->nSommetEnTout,aNext);
			if (tMode==0) VecteurRazer(bMarque,1,pgG->nSommetEnTout);
			if (tMode<0) VecteurRazer(nVisite,1,pgG->nSommetEnTout);
			if (tMode>0) VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);
			if (tMode==0) bMarque[sX0]=kV;
			if (tMode<0) nVisite[sX0]=++nV;
			if (tMode>0) pgG->sPer[sX0]=sX0;
			sCirkwi[0]=0;//index de pile de la pile sCirkwi[1…]
			DequeAllouer(pgG->nSommetEnTout);
				if (bLargeurSinonProfondeur) DequeEnfiler(sX0);else DequeEmpiler(sX0);
				if (kbVoir) printf("%sLe sommet %s est %s en premier. ",flag,sEnt(sX0),(bLargeurSinonProfondeur)? "enfilé":"empilé");
				do{//explorer le graphe depuis le sommet de la deque
					if (kbVoir) DequeVoir("courante");
					sX=sDequeSommet();//lit le sommet de pile ou la tête de file; la deque reste intacte.
					if (kbVoir) printf("%s%s, %s, est lu. ",flag,sEnt(sX),(bLargeurSinonProfondeur)? "en tête de file" : "le sommet de pile");
					if (aNext[sX]<pgG->aHed[sX+1]){
						sY=pgG->sSuk[aNext[sX]];
						if ( !bLargeurSinonProfondeur && bCircuitDetecter && bDequeContient(sY) ){ 
							sZ=sX0;//sX0 reste au fond de la pile
							sCirkwi[sCirkwi[0]=1]=sY;//écrase un éventuel circuit précédemment empilé
							do//ajouter la pile courante à sCirkwi[]={sY}
								sZ=sCirkwi[++sCirkwi[0]]=sDequeSuivant(sZ);
							while (sZ!=sY);//vrai un jour puisque bDequeContient(sY) est vrai li-5
						}
						if (tMode==0 && !bMarque[sY] || tMode<0 && !nVisite[sY] || tMode>0 && !pgG->sPer[sY]){
							if (tMode==0) bMarque[sY]=kV;
							if (tMode<0) nVisite[sY]=++nV;
							if (tMode>0) pgG->sPer[sY]=sX;
							if (bLargeurSinonProfondeur) DequeEnfiler(sY);else DequeEmpiler(sY);
							if (kbVoir) printf("%s%s est %s. ",flag,sEnt(sY),(bLargeurSinonProfondeur)? "enfilé":"empilé");
						}
						aNext[sX]++;//n'altère donc pas pgG->aHed[]
					}else {//extraire sX maintenant que tous ses successeurs ont été explorés
						sZ=(bLargeurSinonProfondeur)? sDequeDefiler(): sDequeDepiler();
						Assert1("GrapheExplorerZX",sZ==sX);//logique
						if (kbVoir) printf("%s%s est %s. ",flag,sEnt(sX),(bLargeurSinonProfondeur)? "défilé":"dépilé");
					}
				}while (!bDequeVide());
			DequeAllouer(0);
		if (mtAfficher){
			if (kbVoir) Ligne();
			printf("\tParcours en %s d'abord avec %s[]:\n",(bLargeurSinonProfondeur)?"largeur":"profondeur",sItem(ksTableau,udMode));
			Tabuler(+2);
				if (tMode==0) VecteurVoir1(sItem(ksTableau,udMode),bMarque,1,pgG->nSommetEnTout);
				if (tMode<0) VecteurVoir1(sItem(ksTableau,udMode),nVisite,1,pgG->nSommetEnTout);
				if (tMode>0) VecteurVoir1(sItem(ksTableau,udMode),pgG->sPer,1,pgG->nSommetEnTout);
				if (mtAfficher>1 && tMode==0)
					printf("%sLes sommets %s tous été explorés.\n",flag,sPas("ont",yVecteurSomme(bMarque,1,pgG->nSommetEnTout)<pgG->nSommetEnTout));
				if (bCircuitDetecter)
					if (!bLargeurSinonProfondeur){
						printf("%s%s",flag,sPhrase0(sPluriel5(sCirkwi[0]>0,"circuit$ $a$ été détecté$",!k1Feminin)));
						if (sCirkwi[0])
							printf(": %s.\n",sListe(sCirkwi,'('));
						else printf(" ——mais peut-être qu'aucun chemin ne va de %s à un circuit.\n",sEnt(1));
					}
				else printf("%sLes parcours en largeur d'abord ne permettent pas de détecter les circuits.\n",flag);
			Tabuler(-2);
		}
		if (tMode==0) VecteurCopier(bMarque,1,pgG->nSommetEnTout,pgG->nVal);
		if (tMode<0) VecteurCopier(nVisite,1,pgG->nSommetEnTout,pgG->nVal);
	if (kbVoir) Appel1(sC3b("GrapheExplorer() en mode",(bLargeurSinonProfondeur)?"largeur":"profondeur","d'abord"));
}//GrapheExplorer

void GrapheFormuler(graf *pgG,int kuFormuleLim,char sFormule[]){
	//convertit le graphe en liste d'arcs colorés exprimée sous forme littérale
	int aK,sX,sY;
	int nPoids[kuFormuleLim];
	Assert2("GrapheFormuler",pgG->nSommetEnTout<=kuAlphaNumerique,3*pgG->nArcEnTout+1<kuFormuleLim);//3 caractères/arc + EOT
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		for (aK=pgG->aHed[sX];sY=pgG->sSuk[aK],aK<pgG->aHed[sX+1];aK++)
			ArcEmpileR(sX,sY,pgG->coulh[aK],pgG->nPoids[aK],sFormule,nPoids);
	sFormule[3*nPoids[0]]='\0';
	//s(sFormule);
}//GrapheFormuler

void GrapheFormulerTout(graf *pgG,int kuListeLim,char sListe[],int bFacultatif[],int nPoids[],int szAccroche0,int szAccroche1){
	//cvertit pgG en liste d'arcs colorés pondérés exprimée littéralt en sautant les bcles; coche celles-ci ds bFacultatif;
	int aK,sX,sY,sPole1,sPole2,nCouleur;
	//d2(3*pgG->nArcEnTout+1,kuListeLim);
	Assert2("GrapheFormulerTout",pgG->nSommetEnTout<=kuAlphaNumerique,3*pgG->nArcEnTout+1<kuListeLim);//[A-Za-z], 3 caractR/arc + EOT
	for (VecteurRaz(bFacultatif,pgG->nSommetEnTout),nPoids[0]=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
		for (aK=pgG->aHed[sX];sY=pgG->sSuk[aK],aK<pgG->aHed[sX+1];aK++)
			if (sX!=sY)
				ArcEmpileR(sX,sY,pgG->coulh[aK],pgG->nPoids[aK],sListe,nPoids);
			else bFacultatif[sX]=1;
	if ( bCroit(1,szAccroche0,szAccroche1-1) )//former un dipôle avec (zAccroche0,szAccroche1)
		ArcEmpileR(sPole1=szAccroche0,sPole2=szAccroche1,nCouleur=5,knPoidsNul,sListe,nPoids);
	//d(3*nPoids[0]);
	sListe[3*nPoids[0]]='\0';
	//s(sListe);
	//VecteurVoir("nPoids",nPoids,1,nPoids[0]);
}//GrapheFormulerTout

int bGrapheFortementConnexe(graf *pgG){//O(SA)
	int nComposanteFortementConnexe=nGrapheComposanteFortementConnexE(pgG);
	return(nComposanteFortementConnexe==1);
}//bGrapheFortementConnexe

void GrapheGadgeter(graf *pgG,int grGadget,int nGadgetTaille,int sGadgetAncre){
	//ajoute à pgG les arcs décrits ds grGadget en trslatant leurs sommets de sGadgetAncre-1
	const int bInfo=kF;
	int aK,sX,sY;
	graf *pgGadget;
	if (bInfo) Appel0("GrapheGadgeter");
		Assert2("nGrapheGadgeter",bGrapheQuadripole(grGadget),bGrapheSommet(pgG,sGadgetAncre));
		GrapheCreer1(&pgGadget,grGadget,nGadgetTaille,k1Creer);
		//ajouter les arcs décrits ds grGadget sachant que les sommets internes au quadripôle sont déjà alloués
			for (sX=1;sX<=pgGadget->nSommetEnTout;sX++)
				for (aK=pgGadget->aHed[sX];sY=pgGadget->sSuk[aK],aK<pgGadget->aHed[sX+1];aK++){
					//if (bInfo) d6(1234,nOffset,sX,nOffset+sX,nOffset+sY,uArcValeur);
					if (bInfo) d4(sGadgetAncre-1+sX,sGadgetAncre-1+sY,pgGadget->coulh[aK],pgGadget->nPoids[aK]);
					GrapheArquer4(pgG,sGadgetAncre-1+sX,sGadgetAncre-1+sY,pgGadget->coulh[aK],pgGadget->nPoids[aK]);
				}
		if (bInfo) GrapheVoir0(sC2b("pgGadget",sGraphe(grGadget)),pgGadget,gpCouleur);
	if (bInfo) Appel1("GrapheGadgeter");
}//GrapheGadgeter

int bGrapheGenerer(char kcArc[],int nGenreDePoids,graf **ppgG){
	//Alloue et rend ppgG défini par les triplets d'arcs pondérés (origine,destination,couleur et poids≥0),eg kcArc="AB2019AC0Bz25".
	const int kbVoir=0;
	const int kbSommetConsecutifs=1;
	const int kuLettreEnTout=kuAlphabet+kuAlphabet;//domaine de bLettre()
	const int kuPlusieursSeuil=10;
	int uArc,nArcEnTout,cBout,nC,uChaineLg,nCouleur,sDestination,sOrigine,bPoids,nPoids,nPonderation,bPremier,uS,uSommetRg,nSommetMax=0;
	uChaineLg=nChaineLg(kcArc);
	int nArc0[1+uChaineLg];//NB sommet origine de l'arc
	int nArc1[1+uChaineLg];//NB sommet destination de l'arc
	int bAbsent[1+kuLettreEnTout],bPresent[1+kuLettreEnTout];
	char cSommet;
	if (kbVoir) s(kcArc);
	int bGenre=bDans5(nGenreDePoids,gpCouleur,gpCouleur+gpPoids,gpCouleur+gpCout,gpCout,gpPoids);
	Assert1("bGrapheGenerer",bGenre);
	int bGenerer=kV;
	ErreurDenoncer(bLettre(kcArc[0]),eGrafSommet,0,&bGenerer);
	if (bGenerer){
	//nSommet:=nb sommets distincts cités ds kcArc censé être une suite (origine,destination,poids) de 2+p caractères, avec p caractR pr le poids,p>0 qcq.
		//nArcEnTout,nbOccurrence[sX],bPresent[sX]:=nb arcs, nb références à un sommet sX du graphe, sa présence, chaq sommet étant nommé par une lettre
			for (VecteurRazer(bPresent,1,kuLettreEnTout),nArcEnTout=nC=0;nC<uChaineLg && bGenerer;nC++){
				ErreurDenoncer(bLettreOuChiffre(kcArc[nC]),eGrafSymbole,nC,&bGenerer);
				if (bGenerer && bLettre(kcArc[nC]))
					for (nArcEnTout++,nC++,cBout=0;cBout<=1;cBout++){
						cSommet=kcArc[nC-1+cBout];//-1 vu nC++ initial
						ErreurDenoncer(bLettre(cSommet),eGrafSommet,nC-1+cBout,&bGenerer);
						if (bGenerer){
							uSommetRg=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
							bPresent[uSommetRg]=1;
							nSommetMax=iSup(nSommetMax,uSommetRg);
							if (cBout==1)
								ErreurDenoncer(bDecit(kcArc[nC+1]),eGrafPoids,nC+1,&bGenerer);
						};
					}
			}
		if (bGenerer && nSommetMax>0){
			if (kbVoir) VecteurVoir("bPresent",bPresent,1,kuLettreEnTout);
			Assert1("bGrapheGenerer76",nArcEnTout>0);
			if (kbSommetConsecutifs){//si un sommet manque dans nbOccurrence, les sommets sont épars
				//VecteurVoir("nbOccurrence",nbOccurrence,1,nSommet);
				int bEpars=iVecteurMin(bPresent,1,nSommetMax)>0;
				if (!bEpars) {
					int sPremier,sDernier;
					for (bAbsent[0]=0,bPremier=sDernier=uS=1;uS<=nSommetMax;uS++)//dc prise
						if (!bPresent[uS])
							bAbsent[++bAbsent[0]]=uS;
						else if (bPremier){
							sPremier=sDernier=uS;
							bPremier=kF;
						}else sDernier=uS;
					bAbsent[0]=yInf(bAbsent[0],kuPlusieursSeuil);
					//d2(sPremier,sDernier);
					Ligne();
					ModeCaractere(+1);
Titrer(sC7("Si les sommets vont de ",sLettre(sPremier)," à ",sLettre(sDernier),", alors ",sPluriel6(bAbsent[0],"sommet$ a$ été omis: ",!k1Feminin,kuPlusieursSeuil),sListe(bAbsent,' ')));
					ModeCaractere(-1);
					ErreurDenoncer(bEpars,eGrafEpars,uChaineLg,&bGenerer);
				}
				//b(bGenerer);
			}
		}
	};
	if (bGenerer)//nArc0[],nArc1[]:=sommets origine,destinO listés ds cArc[]
		for (uArc=0,nArc0[0]=nArc1[0]=nArcEnTout,nC=0;cSommet=kcArc[nC],nC<uChaineLg;nC++)
			if ( bLettre(cSommet) ){
				nArc0[++uArc]=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
				cSommet=kcArc[++nC];
				nArc1[uArc]=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
			}
	if (bGenerer){//ppgG := graphe à nSommet sommets et uArcEnTout arcs d'origine nArc0[] et de destination nArc1[]
		if (kbVoir) VecteurVoir5("nArc0,nArc1",nArc0,nArc1,1,nArcEnTout);
		//d(nSommet);
		GrapheCreer(nSommetMax,ppgG);//0 arc
		for (uArc=1;uArc<=nArcEnTout;uArc++){
			if ( bGrapheArc(*ppgG,nArc0[uArc],nArc1[uArc]) ){
				ErreurDenoncer(0,eGrafDito,3*uArc-1,&bGenerer);//lieu imprécis si poids >9
			}else if (nArc0[uArc]==nArc1[uArc]){
				ErreurDenoncer(0,eGrafBcle,3*uArc-1,&bGenerer);//lieu imprécis si poids >9
			}else GrapheArquer0(*ppgG,nArc0[uArc],nArc1[uArc],gpPoids,uArc);//gpPoids=uArc par défaut
		}
	}
	if (bGenerer)//pondérer selon nGenreDePoids chaque arc de ppgG avec le poids (gpCouleur ou gpPoids ou…) spécifié dans kcArc[]:
		for (nC=0;nPonderation=0,nC<uChaineLg;nC++){
			cSommet=kcArc[nC];
			sOrigine=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
			cSommet=kcArc[++nC];
			sDestination=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
			//if (kbVoir) d2(sOrigine,sDestination);
			do{
				bPoids=bChiffre(kcArc[nC+1]);
				if ( bPoids )
					nPonderation=nPonderation*10+kcArc[++nC]-'0';
			}while (bPoids);
			Assert1("GrapheGenerer7", nPonderation>=0);
			if (kbVoir) s(sC7("arc (",sEnt(sOrigine),",",sEnt(sDestination),",",sEnt(nPonderation),")"));
			nCouleur=nPonderation;
			nPoids=nPonderation;
			if (0) d4(sOrigine,sDestination,nCouleur,nPoids);
			if (bDans2(nGenreDePoids,gpCouleur+gpCout,gpCouleur+gpPoids) ){
			//nPonderation est la concaténation de nPoids éventuel, puis nCouleur, lequel occupe tjrs 1 digit
				nCouleur=nPonderation%10;//1 décit
				nPoids=nPonderation/10;//n'importe quelle quantité ≥ 0
			};
			if (nGenreDePoids & gpCouleur)
				GraphePonderer(*ppgG,sOrigine,sDestination,gpCouleur,nCouleur);
			if (nGenreDePoids & gpCout)
				GraphePonderer(*ppgG,sOrigine,sDestination,gpCout,nPoids);
			if (nGenreDePoids & gpPoids)
				GraphePonderer(*ppgG,sOrigine,sDestination,gpPoids,nPoids);
		}
	if (bGenerer && kbVoir) GrapheVoir0("bGrapheGenerer:*ppgG",*ppgG,nGenreDePoids);
	return(bGenerer);
}//bGrapheGenerer

char *sGrapheHamiltonieN(int nOccurrence,int bDigraphe,int bParcoursFermeh,int *pbFeminin){
	//rend "chemin hamiltonienne", "2 chaînes hamiltoniennes", etc.
	char *ksParcours="chaîne,cycle,chemin,circuit";
	const int kuChaine=1;
	int uItem=1+nBase4(bDigraphe,bParcoursFermeh);
	*pbFeminin=(uItem==kuChaine);
	char *sHamiltonien=sC4(sItem(ksParcours,uItem),"$ hamiltonien",(*pbFeminin)?"ne":"","$");
	if (nOccurrence>0)
		sHamiltonien=sPluriel(nOccurrence,sHamiltonien);
	else sHamiltonien=sChaineSubstituer(sHamiltonien,"$","");
	return(sHamiltonien);
}//sGrapheHamiltonieN

void GrapheHamiltonieN(graf *pgG,int bDigraphe,int bDoublon,const int kmAfficherAuPlus,int nHamMax,int bDebug,int *pnHamiltonien,int *pnLongueur){//(O//2**N)
	//inventorie les parcours hamiltoniens; si pgG en contient un,incrémente pnHamiltonien; affiche au plus |kmAfficherAuPlus| parcours.
	const int kbEntier=1-bDebug;
	const int kbListe=1-bDebug;
	const int kbPhrase=1-bDebug;
	const int kbPile=1-bDebug;
	int bHamiltonien=kF,bFeminin,bUnSeulSuffit,aK,sX,sY,uP,uDigit=nLog10(nHamMax);
	//d(*pnHamiltonien);
	//printf("nHamMax=%d.\n",nHamMax);printf("uDigit=%d.\n",uDigit);
	for (bUnSeulSuffit=(kmAfficherAuPlus==1),sX=sDequeSommet(),aK=pgG->aHed[sX];sY=pgG->sSuk[aK],aK<pgG->aHed[sX+1];aK++)
		if (!bDequeContient(sY)){
			DequeEmpiler(sY);
				(*pnLongueur)+=pgG->nCout[aK];
				if (nDequeCardinal()==pgG->nSommetEnTout){
					bHamiltonien=(!bDoublon || bGrapheArc(pgG,sY,sDequeFond()));
					if (bHamiltonien && (*pnHamiltonien)<abs(kmAfficherAuPlus) ){
						int nPile[1+pgG->nSommetEnTout+bDoublon+16*(1-kbPile)];/**///16
						DequePileCopier(nPile);
						if (kmAfficherAuPlus>=0){
							if (!bUnSeulSuffit) printf("\t");
							if (kbPhrase)
								printf("\t%s",sPhrase0(sGrapheHamiltonieN(0,bDigraphe!=bDoublon,bDoublon,&bFeminin)));
							else printf("parcours hamiltonien:");
							if (kbEntier){
								if (bUnSeulSuffit)
									printf(" trouvé%s: ",(bFeminin)?"e":"");
								else printf(" n°%s: ",sEntier(*pnHamiltonien+1,uDigit));
							};
						}
						VecteurInverser(nPile,1,nPile[0]); 
						if (bDoublon)
							nPile[1]=nPile[nPile[0]];
						if (kmAfficherAuPlus>=0){
							if (!kbListe){
								for (printf("("),uP=1;uP<=nPile[0] || bPrint(")");uP++)
									printf("%d,",nPile[uP]);
							}else printf("%s.\n",sListe(nPile,'('));
						}
						if (kmAfficherAuPlus<0 && (pgG->nVal[0]>*pnLongueur)){
							VecteurCopier(nPile,1,pgG->nSommetEnTout,pgG->nVal);
							pgG->nVal[0]=*pnLongueur;
						}
					}
					(*pnHamiltonien)+=bHamiltonien;
				}else GrapheHamiltonieN(pgG,bDigraphe,bDoublon,kmAfficherAuPlus,nHamMax,bDebug,pnHamiltonien,pnLongueur);
				(*pnLongueur)-=pgG->nCout[aK];
			DequeDepiler();
		};
}//GrapheHamiltonieN

int nGrapheHamiltonien(graf *pgG,int bDigraphe,int bParcoursFermeh,const int kmAfficherAuPlus){//(O//2**N)
	//rend le nb de parcours hamiltoniens fermés ou non. Si nAfficherAuPlus>0,,affiche Au plus kmAfficherAuPlus parcours. Enfin, si…
	//kmAfficherAuPlus<0 et pgG->nVal[0]=kuIntegerMax, rend ds pgG->nVal[1…] le plus petit parcours hamiltonien et ds pgG->nVal[0] sa longueur totale.
	const int kbVoir=0;  
	const int kbDebug=0;
	const int ksFondDePile=1;  
	int nHamiltonien=0,nHamMax,nLongueur,bFeminin,sFondDePile,cPasse,aK,aL,aM,sX,sY,sZ,sT,bDoublon;
	graf *pgCopie;
	Assert1("nGrapheHamiltonien",bGrapheSimple(pgG));
	if (kbVoir) bb(bParcoursFermeh,bDigraphe);
	if (kbVoir) GrapheVoir("nGrapheHamiltonien.pgG",pgG);
	if (pgG->nSommetEnTout>1)
		if ( bGrapheConnexe(pgG) )
			for (nHamMax=cPasse=0;cPasse<=1;cPasse++){//la passe 0 calcule nHamiltonien
				if (cPasse>0 && nHamiltonien>1){
					if (!kbDebug){
						if (kmAfficherAuPlus>=0)
							printf("\tCe graphe contient %s",sGrapheHamiltonieN(nHamiltonien,bDigraphe,bParcoursFermeh,&bFeminin));
						nHamMax=iInf(nHamiltonien,abs(kmAfficherAuPlus));
						if (kmAfficherAuPlus>=0){
							if (nHamiltonien>kmAfficherAuPlus && nHamMax>0)
								printf(", voici %s:",(kmAfficherAuPlus==1)? "le premier" : sC3b("les",sPar3(kmAfficherAuPlus),"premiers"));
							else printf("%c",(nHamiltonien<=kmAfficherAuPlus)? ':' : '.');
						}
					}else printf("\tCe graphe contient les parcours suivants:");
					if (kmAfficherAuPlus>=0) Ligne();
				}
				int bChaine=!bDigraphe && !bParcoursFermeh;
				int nLimite=(!bParcoursFermeh)? pgG->nSommetEnTout : ksFondDePile;//printf("nLimite=%d.\n",nLimite);
				if (bDigraphe){
					nLimite=(bParcoursFermeh)? ksFondDePile : pgG->nSommetEnTout;
					for (nHamiltonien=nLongueur=0,sFondDePile=1;sFondDePile<=nLimite;sFondDePile++){
						DequeAllouer(pgG->nSommetEnTout);
							DequeEmpiler(sFondDePile);
							GrapheHamiltonieN(pgG,bDigraphe,bDoublon=0,kmAfficherAuPlus*cPasse,nHamMax,kbDebug,&nHamiltonien,&nLongueur);
						DequeAllouer(0);
					}
				};
				if (!bDigraphe && bParcoursFermeh){
					//2 arcs = 1 arête, et 2 parcours orientés identQ au sens de parcours près = 1 parcours non orienté.
					//pour éviter ces redondances lors de l'inventaire, le sommet A de la copie de pgG est transformé en (A',A").
					GrapheCreer0(&pgCopie,k1Creer);
						GrapheDupliquer(pgG,&pgCopie);
						pgCopie->nVal[0]=pgG->nVal[0];
						GrapheDedoubler(1,gpCouleur,&pgCopie);
						for (nHamiltonien=nLongueur=0,sFondDePile=pgCopie->nSommetEnTout;sFondDePile<=pgCopie->nSommetEnTout;sFondDePile++){
							DequeAllouer(pgCopie->nSommetEnTout);
								DequeEmpiler(sFondDePile);
								GrapheHamiltonieN(pgCopie,!bDigraphe,bDoublon=1,kmAfficherAuPlus*cPasse,nHamMax,kbDebug,&nHamiltonien,&nLongueur);
							DequeAllouer(0);
						}
						VecteurCopier(pgCopie->nVal,1,pgG->nSommetEnTout,pgG->nVal);
					GrapheCreer0(&pgCopie,!k1Creer);
				};
				if (!bDigraphe && !bParcoursFermeh){
					for (nHamiltonien=nLongueur=0,sFondDePile=ksFondDePile;sFondDePile<=nLimite;sFondDePile++){
							GrapheCreer0(&pgCopie,k1Creer);
					//2 arcs = 1 arête, et 2 parcours orientés identQ au sens de parcours près = 1 parcours non orienté.
					//pour éviter ces redondances lors de l'inventaire, on inventorie successivement les graphes tels que:
					//1 arc unique a pr origine sFondDePile et 1 arc unique a pr extrémité sFondDePile
							for (aK=pgG->aHed[sFondDePile];sY=pgG->sSuk[aK],aK<pgG->aHed[sFondDePile+1];aK++){
								int aDebut=(bChaine)? 1 : pgG->aHed[sFondDePile];
								int aFin=(bChaine)? 2 : pgG->aHed[sY];
								//d2(aDebut,aFin);
								for (aL=aDebut;sZ=pgG->sSuk[aL],aL<aFin;aL++)
									if (1 || bChaine /*|| sY<sZ*/){
										//if (cPasse>0) printf("sY=%d sZ=%d.\n",sY,sZ);
										GrapheDupliquer(pgG,&pgCopie);
										if (!bDigraphe){//symétriser puis conserver uniqt 1 arc sortant et 1 arc entrant: (1,sY) et (sZ,1).
											GrapheSymetriser(pgCopie,gpPoids);
											for (aM=pgCopie->aHed[sFondDePile+1]-1;sT=pgCopie->sSuk[aM],aM>=pgCopie->aHed[sFondDePile];aM--)
												if (sT!=sY)
													GrapheDesarquer(pgCopie,sFondDePile,sT);
											for (sX=1;sX<=pgCopie->nSommetEnTout;sX++)
												for (aM=pgCopie->aHed[sX+1]-1;sT=pgCopie->sSuk[aM],aM>=pgCopie->aHed[sX];aM--)
													if (sT==sFondDePile && (sX!=sZ) )
														GrapheDesarquer(pgCopie,sX,sFondDePile);
										}
										if (kbVoir && cPasse>0) GrapheVoir0(sC2("pgCopie",(cPasse==0)? "0":"1"),pgCopie,gpPoids);
										pgCopie->nVal[0]=pgG->nVal[0];
										DequeAllouer(pgCopie->nSommetEnTout);
											DequeEmpiler(sFondDePile);
											GrapheHamiltonieN(pgCopie,bDigraphe,bDoublon=0,kmAfficherAuPlus*cPasse,nHamMax,kbDebug,&nHamiltonien,&nLongueur);
										DequeAllouer(0);
									}
							}
							VecteurCopier(pgCopie->nVal,1,pgG->nSommetEnTout,pgG->nVal);
							GrapheCreer0(&pgCopie,!k1Creer);
						}
				};
			}
		else if (kmAfficherAuPlus>0)
			printf("\tCe graphe est non connexe, donc non hamiltonien. ");
//d2(nHamiltonien,kmAfficherAuPlus);
	if (kmAfficherAuPlus>0 && !nHamiltonien)
		if (!kbDebug)
			printf("Il n'y a pas de %s.\n",sGrapheHamiltonieN(0,bDigraphe,bParcoursFermeh,&bFeminin));
		else printf("Il n'y a pas de parcours.\n");
	if (0 && kmAfficherAuPlus>0)
		printf("\t#######Pour info, fin de l'affichage des parcours hamiltoniens.\n");
	return(nHamiltonien);
}//nGrapheHamiltonien

void GrapheInverser(graf *pgG){//O(A)
	//affecte aDeh[],sKus[] qui décrivent le graphe inverse de pgG,et aInv[] qui donne l'index aK=pgG->aInv[aL] de l'arc inverse de l'arc d'index aL.
	const int kbDisert = kF;
	int aK,aL;
	int nPred[1+pgG->nSommetEnTout];
	int sX,sY,sZ;
	Assert1("GrapheInverser",bGrapheAmorceR);
	//sd("GrapheInverser",pgG->nSommetEnTout);
	//nPred[sY]:=degré entrant du sommet sY
		VecteurRazer(nPred,1,pgG->nSommetEnTout);//O(S)
		for (aK=1;aK<=pgG->nArcEnTout;aK++){//O(A)
			sY=pgG->sSuk[aK];
			nPred[sY]++;
		}
		//VecteurVoir("nPred",nPred,1,pgG->nSommetEnTout);
	//aDeh[sX]:=1+nombre total d'arcs qui auront pour extrémité les sommets 1 à sX (inclus)
		pgG->aDeh[0]=1;//technique
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
			pgG->aDeh[sX]=pgG->aDeh[sX-1]+nPred[sX];
		pgG->aDeh[pgG->nSommetEnTout+1]=pgG->nArcEnTout+1;
		pgG->aDeh[0]=0;
		//VecteurVoir("aDeH0",pgG->aDeh,1,pgG->nSommetEnTout+1);
	//sKus[] et aInv[] soient affectés
		VecteurRazer(pgG->aInv,1,pgG->nArcEnTout);//O(A)
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				Assert1("GrapheInverser1",sY>0);
				pgG->aDeh[sY]--;
				aL=pgG->aDeh[sY];
				Assert1("GrapheInverser2",aL>0);
				pgG->sKus[aL]=sX;
				pgG->aInv[aL]=aK;//dc aK est l'index de l'arc (sX,sY) dans sSuk[] et aL est l'index de (sY,sX) dans sKus[].
			}
	if (kbDisert) GrapheScruter("Graphe Inversé",pgG,+1,!k1Detailler);
	if (kbDisert) Titrer("vérifications");
	//vérifier que pgG->aInv permet de passer du graphe inverse au graphe direct
		for (sZ=1;sZ<=pgG->nSommetEnTout;sZ++)//O(A)
			for (aL=pgG->aDeh[sZ];aL<pgG->aDeh[sZ+1];aL++){
				sX=pgG->sKus[aL];
				aK=pgG->aInv[aL];//aL donne aK ——mais en général aK ne donne pas aL
				sY=pgG->sSuk[aK];
				Assert2("GrapheInverser4",sY==sZ,pgG->sSuk[pgG->aInv[aL]]==sZ);
			}
	if (kbDisert)//constater que pgG->aInv NE PERMET PAS DE PASSER DU GRAPHE DIRECT AU GRAPHE INVERSE (sauf exception très rare)
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				aL=pgG->aInv[aK];
				sZ=pgG->sKus[aL];
				d3(sX,sY,sZ);
				d2(aK,aL);
				Assert1("GrapheInverser9",sX==sZ);//plante le plus souvent quelque part
			}
}//GrapheInverser

int bGrapheNonPlanaire(graf *pgG,char *sReductionPuisK5ouK33,int bAfficher){//O(S3)
	//vrai ssi sReductionPuisK5ouK33 décrit un ensemble de réductions puis un K5ouK33 qui est bien dans pgG;altère pgG.
	//si sReductionPuisK5ouK33 est "AB:AI:GF:ACEGJ", la réduction AB, par exemple, est valide ssi pgG contient une arête (A,B).
	//si sReductionPuisK5ouK33 est "FE:ABCDE", l'appelant veut mettre en évidence K5=ABCDE en faisant glisser F vers E.
	//Attention: la réduction FE supprime F après déplacement de F vers E alors que la réduction EF supprime E.
	int bVoir=0;
	int mCoupe,bDigraphe,bNonPlanaire=0,bK33,sListe[1+6],bCoche[1+pgG->nSommetEnTout],bVivant[1+pgG->nSommetEnTout];
	int aK,sVit,sTue,sX,sZ,uR,nReduction,uS,uT,bValide,nLg=nChaineLg(sReductionPuisK5ouK33);
	char sMiroir[1+nLg];
	if (bVoir) Appel0("bGrapheNonPlanaire");
	Tabuler(+1);
		int bCaractere=bModeCaractere();
		if (bVoir && bCaractere) ModeCaractere(0);
		bNonPlanaire=1;
		ErreurDeclarer(bGrapheSymetrique(pgG),ePlnrSym,0,&bValide);
		if (bValide){//sReductionPuisK5ouK33 est suffixé par K5 ou K33
			ChaineCopier0(sReductionPuisK5ouK33,sMiroir);
			ChaineInverser(sMiroir);
			mCoupe=mChainePos(':',sMiroir);
			ErreurDeclarer(bDans2(mCoupe,5,6) || bDans2(nLg,5,6),ePlnrK5K33,0,&bValide);
			bK33=mCoupe==6 || nChaineLg(sReductionPuisK5ouK33)==6;
			if (bValide)
				for (sX=1;sX<=5+bK33;sX++)
					ErreurDeclarer(bGrapheSommet(pgG,nLettre(sReductionPuisK5ouK33[nLg-sX])),ePlnrSommet,nLg-sX,&bValide);
		};
		if (bValide)//chq réduction est terminée par un ":" placé correctt
			for (uR=2;uR<=nLg-5-bK33;uR+=3)
				ErreurDeclarer(sReductionPuisK5ouK33[uR]==':',ePlnrReduc,uR-1,&bValide);
		if (bValide)//entre les ":" il y a des sommets valides
			for (uR=1;uR<=nLg-5-bK33;uR+=3){
				ErreurDeclarer(bGrapheSommet(pgG,nLettre(sReductionPuisK5ouK33[uR-1])),ePlnrReduc,uR-1,&bValide);
				ErreurDeclarer(bGrapheSommet(pgG,nLettre(sReductionPuisK5ouK33[uR])),ePlnrReduc,uR-0,&bValide);
			}
		if (bValide){
			nReduction=(nLg-5)/3;//K5 prend 5 caractR,K33 en prend 6 et 5=6 a une parité près
			if (bAfficher)
				if (nReduction>0)
					printf("%s{%s} ",sTab(1),sChaine0(sReductionPuisK5ouK33,iSup(0,nReduction*3-1)));
				else printf("%sL'étude des liens entre les sommets de {%s} ",sTab(1),sChaineEclate(sReductionPuisK5ouK33,','));
			if (bVoir) sd(sReductionPuisK5ouK33,nReduction);
			//Effectuer sur pgG toutes les réductions demandées en s'assurant grâce à bVivant[] qu'elles sont distinctes
				//ModeCaractere(-1);
					for (VecteurValuer(bVivant,1,pgG->nSommetEnTout,kV),uR=1;uR<=nReduction && bValide;uR++){
						sTue=sReductionPuisK5ouK33[3*(uR-1)+0]-'@';//1er sommet de la réduction courante
						sVit=sReductionPuisK5ouK33[3*(uR-1)+1]-'@';//2nd sommet de la réduction courante
						if (bVoir) s2(sC0('@'+sVit),sC0('@'+sTue));
						bValide=bGrapheSommet(pgG,sVit) && bVivant[sVit] && bGrapheSommet(pgG,sTue) && bVivant[sTue];
						if (bValide){
							//bCoche[]:=sommets successeurs de sTue, distincts de sVit et non liés à sVit
								for (VecteurRaz(bCoche,pgG->nSommetEnTout),aK=pgG->aHed[sTue];sZ=pgG->sSuk[aK],aK<pgG->aHed[sTue+1];aK++)
									if (sZ!=sVit && !nGrapheArc(pgG,sVit,sZ) && !nGrapheArc(pgG,sZ,sVit))
										bCoche[sZ]++;
								if (bVoir) VecteurVoir0("bCoche",bCoche);
							//ajouter une arête (sVit,sZ) si sZ est coché et si (sTue,sZ) existe
								for (sZ=1;sZ<=pgG->nSommetEnTout;sZ++)
									if (bCoche[sZ])
										GrapheAreter(pgG,sVit,sZ);//O(S2)
							bVivant[sTue]=kF;
						}
					}
					if (bVoir) VecteurVoir("bVivant",bVivant,1,pgG->nSommetEnTout);
				ModeCaractere(+1);
			if (bVoir) GrapheVoir("pgG",pgG);
			bK33=bPair(nChaineLg(sReductionPuisK5ouK33)-3*nReduction);
			bValide=bValide && yVecteurSomme(bVivant,1,pgG->nSommetEnTout)==5+bK33;
			if (bVoir) sd2(sReductionPuisK5ouK33,nChaineLg(sReductionPuisK5ouK33),bK33);
			VecteurRaz(sListe,5+bK33);//K5 est défini avec 5 sommets,K33 avec 6
			for (uS=1;uS<=5+bK33;uS++)//K5 est défini avec 5 sommets,K33 avec 6
				sListe[uS]=sReductionPuisK5ouK33[3*nReduction+uS-1]-'@';
			if (bVoir) VecteurVoir0("sListe",sListe);
			bValide=bValide && bVecteurDistinct(sListe,1,5+bK33,k1NonNul);
			if (bValide){
				if (!bK33){
					for (uS=1;uS<=5;uS++)//bNonPlanaire:=sListe décrit bien un K5 de pgG avec les seuls sommets encore vivants
						for (bNonPlanaire=bNonPlanaire && bVivant[uS],uT=uS+1;uT<=5;uT++){
							bNonPlanaire=bNonPlanaire && bVivant[uT] && bGrapheArc(pgG,sListe[uS],sListe[uT]);
							if (bVoir) d5(uS,uT,sListe[uS],sListe[uT],bNonPlanaire);
						}
				}else for (uS=1;uS<=3;uS++)//bNonPlanaire:=sListe est bien un K33 de pgG avec les seuls sommets encore vivants
						for (bNonPlanaire=bNonPlanaire && bVivant[uS],uT=3+1;uT<=6;uT++){
							bNonPlanaire=bNonPlanaire && bVivant[uT] && bGrapheArc(pgG,sListe[uS],sListe[uT]);
							if (bVoir) d5(uS,uT,sListe[uS],sListe[uT],bNonPlanaire);
						}
			}else bNonPlanaire=0;
			if (bAfficher) printf("%s le graphe à %s",(bNonPlanaire)? "réduit bien":"ne réduit pas",(bNonPlanaire)?"" : "un sous-graphe ");
			if (bAfficher) printf("%s de type %s.\n",sChainon1(sReductionPuisK5ouK33,nReduction*3),(bK33)? "K33":"K5");
		} 
		else ErreurAfficherTout(sReductionPuisK5ouK33);
		if (bAfficher){
			if (!bDigraphe) printf("La démonstration %s convaincante",sEst(bNonPlanaire));
			if (!bDigraphe) printf("%s.\n",(bNonPlanaire)? ": CE GRAPHE EST NON PLANAIRE" : "");
		}
		if (bVoir && bCaractere) ModeCaractere(1);
	Tabuler(-1);
	if (bVoir) Appel1("bGrapheNonPlanaire");
	return(bNonPlanaire);
}//bGrapheNonPlanaire

void GrapheOrdonnanceR(graf *pgG,int sSource,int zdAfficher){//O(A)
	//rend la date au plus tot pour chaque sommet sX ds pgG->nVal[sX]
	const int kbVoir=kF;
	int uNiveau[1+pgG->nSommetEnTout],uSuivant[1+pgG->nSommetEnTout];
	int nDateParX,aK,sX,sY;
	if (kbVoir) Appel0("GrapheOrdonnanceR");
	int tAfficher=(abs(zdAfficher)>1)*ySignePres(sSource!=1,k1Afficher);
	//uNiveau[],uSuivant[]:=niveaux topologiques, suite des sommets triés par niveau;en 1er,car écrase pgG->nVal[]
		bGrapheTrierTopologiquement(pgG,tAfficher);//O(A);résultat dans pgG->nVal[]
		VecteurCopier(pgG->nVal,1,pgG->nSommetEnTout,uNiveau);
		VecteurTrier2(uNiveau,1,pgG->nSommetEnTout,uSuivant);//O(S)
	//initialiser pgG->nVal[] et pgG->sPer[].
		VecteurRazer(pgG->nVal,1,pgG->nSommetEnTout);//dates au plus tôt
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);
		pgG->nVal[sSource]=0;//distance entre le sommet de départ et lui-même
		pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE()
	//initialiser les successeurs de sSource
		for (aK=pgG->aHed[sSource]; aK<pgG->aHed[sSource+1]; aK++)//O(S)
			pgG->nVal[pgG->sSuk[aK]]=pgG->nCout[aK];
	//VecteurVoir("uNiveau",uNiveau,1,pgG->nSommetEnTout);
	for (int uSommet=1;uSommet<=pgG->nSommetEnTout; uSommet++) {//O(A)
		sX=uSuivant[uSommet];
		//pr tt voisin sY de sX, modifier pgG->nVal[sY] si passer par sX retarde la date au plus tôt de sY 
			for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; aK++) {
				sY=pgG->sSuk[aK];//pr info
				nDateParX=pgG->nVal[sX]+pgG->nCout[aK];
				if ( pgG->nVal[sY]<nDateParX ) {//pgG->nVal[sY] est moins tôt 
					pgG->nVal[sY]=nDateParX;
					pgG->sPer[sY]=sX;//sX est situé sur le chemin le plus critique qui relie sY à sSource.
				}
			}
	}
	if (kbVoir) VecteurVoir("sPer",&pgG->sPer[0],1,pgG->nSommetEnTout);
	if (kbVoir) Appel1("GrapheOrdonnanceR");
}//GrapheOrdonnanceR

void CheminCritiqueEnumereR(graf *pgG,int sSource,int sTrappe,int nDateAuPlusTot,int ipPile,int sPile[],int nEffectif,int *pnCumul){
	//si nEffectif est nul,rend ds pnCumul le nb de chemins;sinon, affiche les nEffectif chemins;utilise sPile pr empiler les sommets depuis sSource, et ipPile réputé initialisé à 1.
	char *sChemin;
	int bCritique,nCumul,uP,sX,sY,aK;
	if (ipPile==1)
		*pnCumul=0;
	//d2(nEffectif,nLog10(nEffectif));
	if (!pgG->nVal[sSource])
		sPile[ipPile]=sSource;
		if (sSource!=sTrappe){
			for (int aK=pgG->aHed[sSource];aK<pgG->aHed[sSource+1];aK++)
				if (!pgG->nVal[pgG->sSuk[aK]])
					CheminCritiqueEnumereR(pgG,pgG->sSuk[aK],sTrappe,nDateAuPlusTot,ipPile+1,sPile,nEffectif,pnCumul);
		}else {
			for (sPile[0]=nCumul=0,sX=sPile[1],uP=2;sPile[0]++,sY=sPile[uP],uP<=ipPile;sX=sY,uP++)
				nCumul+=pgG->nCout[aK=nGrapheArc(pgG,sX,sY)];
			bCritique=(nCumul==nDateAuPlusTot);
			if (bCritique){
				(*pnCumul)++;
				if (nEffectif){
					if (nEffectif>1)
						sChemin=sC4(sTab0(),flag,"Chemin n°",sEnt2(*pnCumul,nLog10(nEffectif)));
					else sChemin=sC1(" chemin critique");
					ModeCaractere(+1);
						printf("%s: %s.\n",sChemin,sListe(sPile,'(') );
					ModeCaractere(-1);
				}
			}
		}
}//CheminCritiqueEnumereR

int bGrapheOrdonnancer(graf *pgG,int bStrict,int zdAfficher){//O(A)
	//ordonnanct, strict potentiel-tâches avec des arcs sortants de mm cout si bStrict;rend les marges ds pgG->nVal[]
	const int bVoir=kF;
	const int kuCheminCritiqueLim=10;
	int nCoutBasique,aK,bOrdonnancer=1,cPole,bPotentielTache,nbSource=0,sSource,nbTrappe=0,sTrappe,sX,sY;
	int dtTot[1+pgG->nSommetEnTout],dtTard[1+pgG->nSommetEnTout],nPred[1+pgG->nSommetEnTout];
	int nbCheminCritique,ipPile,iPile[1+pgG->nSommetEnTout];//pile des sommets qui jalonnent les chemins critiques
	graf *pgH;
	if (bVoir) Appel0("GrapheOrdonnancer");
		int bConnexe=bGrapheConnexe(pgG);
		int bCircuite=bGrapheCircuite(pgG,!k1Afficher);
		if (bConnexe && !bCircuite){
			//bPotentielTache:=pr chque sommet sX de pgG, ts les arcs d'origine sX ont mm poids
				for (bPotentielTache=kV,sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (nCoutBasique=pgG->nCout[pgG->aHed[sX]],aK=pgG->aHed[sX]+1;aK<pgG->aHed[sX+1];aK++){
						bPotentielTache=bPotentielTache && pgG->nCout[aK]==nCoutBasique;
						if (!bPotentielTache && bStrict) printf("pas potentiel-tâche au sommet %d.\n",sX);
					}
			if (0)
				Assert1("bGrapheOrdonnancer type potentiel-tâche attendu",bPotentielTache);
			GrapheCreer(pgG->nSommetEnTout,&pgH);
				//pgH:=graphe symétrique de pgG
					for (sX=1;sX<=pgG->nSommetEnTout;sX++)
						for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
							GrapheArquer0(pgH,sY=pgG->sSuk[aK],sX,gpCout,pgG->nCout[aK]);
					Assert2("bGrapheOrdonnancer graphe symétrique erroné",pgG->nSommetEnTout==pgH->nSommetEnTout,pgG->nArcEnTout==pgH->nArcEnTout);
				//sSource,sTrappe soient les sommets du dipôle réputé unique qui circonscrit les tâches à ordonnancer
					for (nbSource=nbTrappe=cPole=0;cPole<=1;cPole++){
						graf *pgP=(cPole)? pgH:pgG;
						for (sX=1;sX<=pgP->nSommetEnTout;sX++)
							nPred[sX]=pgP->aHed[sX+1]-pgP->aHed[sX];
						//VecteurVoir("nPred",nPred,1,pgP->nSommetEnTout);
						for (sX=1;sX<=pgP->nSommetEnTout;sX++)
							if (nPred[sX]==0){
								if (cPole) nbTrappe++; else nbSource++;
								if (cPole) sSource=sX; else sTrappe=sX;
							}
					}
					//if (!(nbSource==1 && nbTrappe==1)) (nbSource,nbTrappe);
					Assert22("bGrapheOrdonnancer dipôle attendu,nbSource,nbTrappe",nbSource==1,nbTrappe==1,nbSource,nbTrappe);
				//dtTot:=dates au plus tôt
					GrapheOrdonnanceR(pgG,sSource,zdAfficher);//O(A)
					VecteurCopier(pgG->nVal,1,pgG->nSommetEnTout,dtTot);
				//dtTard:=dates au plus tard
					GrapheOrdonnanceR(pgH,sTrappe,zdAfficher);//O(A)
					for (sX=1;sX<=pgG->nSommetEnTout;sX++)
						dtTard[sX]=dtTot[sTrappe]-pgH->nVal[sX];
				//pgG->nVal[]:=marges
					for (sX=1;sX<=pgG->nSommetEnTout;sX++)
						pgG->nVal[sX]=dtTard[sX]-dtTot[sX];
				Assert1("bGrapheOrdonnancer marge positive attendue",yVecteurInf(pgG->nVal,1,pgG->nSommetEnTout)>=0);
				if (zdAfficher>1)
					printf("%sOrdonnancement du graphe orienté sans circuit %sc'est donc un DAG:\n",sE(4),flag);
				else if (zdAfficher)
					printf("%sOrdonnancement du DAG:\n",sE(4));
				if (zdAfficher>0) Flag(0);
					//afficher les dates au plus tôt du graphe direct et du graphe symétriq, les dates au plus tard, les marges, et citer les tâches critiques
						Tabuler(2);
							for (printf("%stâche    date au plus tôt    idem/graphe inverse    date au plus tard    marge    tâche critique\n",sTab0()),sX=1;sX<=pgG->nSommetEnTout;sX++)
								printf("%s  %s%15d  %20d%20d%16d%13s\n",sTab0(),sEnt2(sX,0),dtTot[sX],pgH->nVal[sX],dtTard[sX],pgG->nVal[sX],sChoix1(!pgG->nVal[sX],sEnt2(sX,0)));
						Tabuler(-2);
				if (zdAfficher>0) Flag(1);
			GrapheCreer(0,&pgH);
			//afficher le nombre et la liste des chemins critiques
				Tabuler(1);
					ModeCaractere(+1);
						CheminCritiqueEnumereR(pgG,sSource,sTrappe,dtTot[sTrappe],ipPile=1,iPile,0,&nbCheminCritique);
						if (zdAfficher>1){
							if (nbCheminCritique>1)
								printf("%sIl y a %s%s\n",sTab0(),sPluriel(nbCheminCritique,"chemin$ critique$"),(nbCheminCritique<10)? ":":".");
							else printf("%sIl y a %d",sTab0(),nbCheminCritique);
							Flag(0);
								if (nbCheminCritique<kuCheminCritiqueLim)
									CheminCritiqueEnumereR(pgG,sSource,sTrappe,dtTot[sTrappe],ipPile=1,iPile,nbCheminCritique,&nBof);
							Flag(1);
						};
						if (zdAfficher==1){
							Flag(0);
								printf("%sIl y a %s%s\n",sTab0(),sPluriel(nbCheminCritique,"chemin$ critique$"),".");
							Flag(1);
						};
					ModeCaractere(-1);
				Tabuler(-1);
		}else if (bCircuite)
			printf("\tL'ordonnancement est impossible car le graphe contient un circuit.\n");
		else if (!bConnexe)
			printf("\tL'ordonnancement est possible mais pas implémenté.\n");
	if (bVoir) Appel1("bGrapheOrdonnancer");
	Flag(0);
	bOrdonnancer=0;
	return(bOrdonnancer);
}//bGrapheOrdonnancer

int iGraphePoids(graf *pgG,int nGenreDePoids,int nArc){
	int iPoids;
	Assert2("iGraphePoids",bCroit(1,nArc,pgG->nArcEnTout),bGrapheAttribuT(nGenreDePoids));
	if (nGenreDePoids & gpCapaMax) iPoids=pgG->nCapaMax[nArc];
	if (nGenreDePoids & gpCapaMin) iPoids=pgG->nCapaMin[nArc];
	if (nGenreDePoids & gpCouleur) iPoids=pgG->coulh[nArc];
	if (nGenreDePoids & gpCout) iPoids=pgG->nCout[nArc];
	if (nGenreDePoids & gpPhi) iPoids=pgG->nPhi[nArc];
	if (nGenreDePoids & gpPoids) iPoids=pgG->nPoids[nArc];
	if (nGenreDePoids & gpZeta) iPoids=pgG->nCout[nArc];//comme gpCout
	return(iPoids);
}//iGraphePoids

void GraphePolariser(graf *pgG,int *psSource,int *psTrappe){//O(A)
	//rend 1 ds *psSource et pgG->nSommetEnTout+2 ds *psTrappe après incrémentation des sommets du graphe original puis…
	//	…transforme pgG en dipôle en ajoutant à pgG une source/trappe reliée à ts les sommets sans prédécesseurs/successeurs.
	const int knCouleurNulle=0;//couleurs des arcs reliés aux pôles.
	int bArquer=kV,bCircuite,aK,sX,sPremier=1+1,sDernier=pgG->nSommetEnTout+1;
	int nPred[kuGrapheSommetLim];
	Assert2("GraphePolariser0",bGrapheSimple(pgG),pgG->nSommetEnTout+3<kuGrapheSommetLim);//+3 pr ajout source et trapppe
	bCircuite=bGrapheCircuite(pgG,!k1Afficher);
	GrapheTranslater(pgG,+1);//le sommet 1 devient le sommet 2, etc.
	*psSource=1;
	*psTrappe=++pgG->nSommetEnTout;
	pgG->aHed[pgG->nSommetEnTout+1]=pgG->aHed[pgG->nSommetEnTout];
	Assert1("GraphePolariser1",bGrapheSimple(pgG));
	//nPred[]:=nb de prédécesseurs de chq sommet hors source et trappe
		for (VecteurRazer(nPred,sPremier,sDernier),sX=sPremier;sX<=sDernier;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				nPred[pgG->sSuk[aK]]++;
		//VecteurVoir1("nPred",nPred,sPremier,sDernier);
	//sSource soit reliée à ts les sommets sans prédécesseurs
		for (bArquer=kV,sX=sPremier;sX<=sDernier;sX++)
			bArquer=bArquer && (nPred[sX]!=0 || bGrapheArqueR(pgG,*psSource,sX,knCouleurNulle));
	//sTrappe soit reliée à ts les sommets sans successeurs
		for (sX=sPremier;sX<=sDernier;sX++)
			bArquer=bArquer && ( (pgG->aHed[sX]<pgG->aHed[sX+1]) || bGrapheArqueR(pgG,sX,*psTrappe,knCouleurNulle) );
	Assert3("GraphePolariser2",bArquer,bGrapheSimple(pgG),bCircuite||!bGrapheCircuite(pgG,!k1Afficher));//pas de circuit créé
}//GraphePolariser

void GraphePonderer(graf *pgG,int sOrigine,int sDestination,int nGenreDePoids,int iPoidsSurArc){//O(A)
	//affecte uniqt le champ désigné par nGenreDePoids. Déroute si (sOrigine,sDestination) n'est pas un arc de  pgG.
	Assert1("GraphePonderer",bGrapheAttribuT(nGenreDePoids));
	int aK=nGrapheArc(pgG,sOrigine,sDestination);
	Assert1("GraphePonderer0",aK>0);
	if (nGenreDePoids & gpCapaMax) pgG->nCapaMax[aK]=iPoidsSurArc;
	if (nGenreDePoids & gpCapaMin) pgG->nCapaMin[aK]=iPoidsSurArc;
	if (nGenreDePoids & gpCouleur) pgG->coulh[aK]=iPoidsSurArc;
	if (nGenreDePoids & gpCout) pgG->nCout[aK]=iPoidsSurArc;
	if (nGenreDePoids & gpPhi) pgG->nPhi[aK]=iPoidsSurArc;
	if (nGenreDePoids & gpPoids) pgG->nPoids[aK]=iPoidsSurArc;
}//GraphePonderer

void GraphePonderer0(graf *pgG,int nArcCout){//O(A)
	//initialise pgG->nCout[aK] avec nArcCout.
	Assert1("GraphePonderer0",nArcCout>=0);
	for (int aK=1;aK<=pgG->nArcEnTout;aK++)
		pgG->nCout[aK]=nArcCout;
}//GraphePonderer0

void GraphePonderer1(graf *pgG,int nArcPoids){//O(A)
	//initialise le champ nPoids de (sX,sY) avec nArcPoids*sX+sY.
	Assert1("GraphePonderer1",nArcPoids>0);
	int aK,sX,sY;
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			pgG->nPoids[aK]=nArcPoids*sX+sY;
		}
}//GraphePonderer1

void GraphePonderer2(graf *pgG,int uCapaMax,int uCoutMax){//O(A)
	//initialise les champs nCapaMax et nCout de pgG avec des valeurs aléatoires dans [1..uCapaMax] et [1..uCoutMax], unitaires si uCapaMax ou uCoutMax=1.
	Assert2("GraphePonderer2",uCapaMax>0,uCoutMax>0);
	for (int aK=1;aK<=pgG->nArcEnTout;aK++){
		pgG->nCapaMax[aK]=uHasard(uCapaMax);//ds [1..uCapaMax]
		pgG->nCout[aK]=uHasard(uCoutMax);
	}
}//GraphePonderer2

void GraphePonderer3(graf *pgG,int uCapaMin,int uCapaMax,int uCoutMax){//O(A)
	//initialise les champs nCapaMin, nCapaMax, et nCout avec des valeurs aléatoires dans [1..uCapaMax],etc, unitaires si uCapaMax,etc,=1.
	Assert3("GraphePonderer3",uCapaMin>0,uCapaMax>0,uCoutMax>0);
	int aK;
	//d3(uCapaMin,uCapaMax,uCoutMax);
	for (aK=1;aK<=pgG->nArcEnTout;aK++){
		pgG->nCapaMin[aK]=uHasard(uCapaMin);
		pgG->nCapaMax[aK]=uHasard(uCapaMax);//ds [1..uCapaMax]
		pgG->nCout[aK]=uHasard(uCoutMax);
	}
}//GraphePonderer3

void GraphePonderer5(graf *pgG,int sOrigine,int sDestination,int nCapaMin,int nCapaMax,int nCoutMax){//O(A)
	//initialise les champs nCapaMin, nCapaMax, et nCout avec les valeurs positives ou nulles spécifiées uCapaMin,uCapaMax et uCoutMax.
	Assert3("GraphePonderer50",nCapaMin>=0,nCapaMax>=0,nCoutMax>=0);
	//tee("sOrigine,sDestination",sOrigine,sDestination);
	int aK=nGrapheArc(pgG,sOrigine,sDestination);
	Assert1("GraphePonderer51",aK>0);
	pgG->nCapaMin[aK]=nCapaMin;
	pgG->nCapaMax[aK]=nCapaMax;
	pgG->nCout[aK]=nCoutMax;
}//GraphePonderer5

void GraphePondererAleatoirement(graf *pgG,int nGenreDePoids,int uBorneMax){//O(A)
	//initialise le ou les pondérateurs de pgG avec des valeurs aléatoires prises dans [1..uBorneMax].
	int sOrigine,sDestination;
	Assert1("GraphePondererAleatoirement",bGrapheAttribuT(nGenreDePoids));
	for (int aK=1;aK<=pgG->nArcEnTout;aK++){
		GrapheDelimiter(pgG,aK,&sOrigine,&sDestination);
		GraphePonderer(pgG,sOrigine,sDestination,nGenreDePoids,uHasard(uBorneMax));
	}
}//GraphePondererAleatoirement

void GraphePondererDistinctement(graf *pgG,int iOffset){//O(A)
	//initialise le cout des arcs (sX,sY) avec des valeurs distinctes en commençant par iOffset>=0 pr le 1er arc rencontré ou -1 si iOffset<0
	int aK,iCout,nCout;
	int nOffset=abs(iOffset);
	for (nCout=(iOffset>=0)? nOffset: 1,aK=1;aK<=pgG->nArcEnTout;aK++){
		iCout=(iOffset>=0)? nCout: -aK;
		//d2(aK,iCout);
		if (pgG->nCout[aK]==0)
			pgG->nCout[aK]=iCout;
		if (pgG->nCout[aK]>0 && iOffset>0)
			pgG->nCout[aK]=iCout;
		nCout+=1;
	}
}//GraphePondererDistinctement

void GraphePondererPareiL(graf *pgG){//O(A)
	//pgG->nCout[(X,Y)]=pgG->nCout[(Y,X)]=Sup(pgG->nCout[(X,Y)],pgG->nCout[(Y,X)]).
	int aK,sX,sY;
	int nMatrice[1+pgG->nSommetEnTout][1+pgG->nSommetEnTout];//N.B. NE PAS L'INITIALISER CAR CELA COUTERAIT O(S2), PLUS CHER QUE O(A) si pgG non dense.
	Assert1("GraphePondererPareiL",bGrapheSymetrique(pgG));
	//VecteurVoir("gG->nCout[aK]",pgG->nCout,1,pgG->nArcEnTout);
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		VecteurRazer(nMatrice[sX],1,pgG->nSommetEnTout);
	if (0) for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		VecteurVoir("nMatrice[sX]",nMatrice[sX],1,pgG->nSommetEnTout);
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			nMatrice[sY][sX]=nMatrice[sX][sY]=iSup(pgG->nCout[aK],nMatrice[sX][sY]);
		}
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			pgG->nCout[aK]=nMatrice[sX][sY];
		}
	//VecteurVoir("gG->nCout[aK]",pgG->nCout,1,pgG->nArcEnTout);
}//GraphePondererPareiL

void GraphePondererTout(graf *pgG,int nGenreDePoids,int iPoidsSurArc){
	Assert1("GraphePondererTout",bGrapheAttribuT(nGenreDePoids));
	int sOrigine,sDestination;
	for (int aK=1;aK<=pgG->nArcEnTout;aK++){
		GrapheDelimiter(pgG,aK,&sOrigine,&sDestination);
		GraphePonderer(pgG,sOrigine,sDestination,nGenreDePoids,iPoidsSurArc);
	}
}//GraphePondererTout

void GrapheRenumeroter(graf **ppgG,int sSommetAvant,int sSommetApres){//O(A)
	//retire tous les liens attachés à sSommetAvant et les attache à sSommetApres qui doit être de degré nul.
	const int bInfo=kF;
	int aK,nDegreh1,sX,ipPile;
	int sCopille[1+(*ppgG)->nSommetEnTout];
	Assert4("GrapheRenumeroter",bGrapheSommet(*ppgG,sSommetAvant),bGrapheSommet(*ppgG,sSommetApres),bGrapheSimple(*ppgG),nGrapheDegreh(*ppgG,sSommetApres,0)==0);
	if (bInfo) GrapheScruter("AVANT",*ppgG,+1,!k1Detailler);
	//tt arc qui arrive en sSommetAvant arrive dorénavant en sSommetApres
		for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++)
			if ( (*ppgG)->sSuk[aK]==sSommetAvant )
				(*ppgG)->sSuk[aK]=sSommetApres;
		Assert1("GrapheRenumeroter 1",bGrapheSimple(*ppgG) );
	nDegreh1=(*ppgG)->aHed[sSommetAvant+1]-(*ppgG)->aHed[sSommetAvant];
	if (bInfo) d2(1,nDegreh1);
	//tt arc qui part de sSommetAvant part dorénavant de sSommetApres
		//empiler les futurs successeurs de sSommetApres
			for (ipPile=0,aK=(*ppgG)->aHed[sSommetAvant];aK<(*ppgG)->aHed[sSommetAvant+1];aK++)
				sCopille[ipPile++]=(*ppgG)->sSuk[aK];
		//supprimer les nDegreh1 successeurs de sSommetAvant
			for (aK=(*ppgG)->aHed[sSommetAvant+1];aK<=(*ppgG)->nArcEnTout;aK++)
				(*ppgG)->sSuk[aK-nDegreh1]=(*ppgG)->sSuk[aK];
			for (sX=sSommetAvant+1;sX<=(*ppgG)->nSommetEnTout+1;sX++)
				(*ppgG)->aHed[sX]=(*ppgG)->aHed[sX]-nDegreh1; 
		//créer un espace de taille nDegreh1 pour les successeurs de sSommetApres
			for (aK=(*ppgG)->nArcEnTout;aK>=(*ppgG)->aHed[sSommetApres+1];aK--)
				(*ppgG)->sSuk[aK+nDegreh1]=(*ppgG)->sSuk[aK];
			for (sX=sSommetApres+1;sX<=(*ppgG)->nSommetEnTout+1;sX++)
				(*ppgG)->aHed[sX]=(*ppgG)->aHed[sX]+nDegreh1; 
		//loger la pile ds l'espace en question
			for (aK=(*ppgG)->aHed[sSommetApres];aK<(*ppgG)->aHed[sSommetApres]+nDegreh1;aK++)
				(*ppgG)->sSuk[aK]=sCopille[--ipPile];
		Assert1("GrapheRenumeroter 2",bGrapheSimple(*ppgG));
		if (bInfo) d( (*ppgG)->nArcEnTout);
	if (bInfo) GrapheScruter("APRES",*ppgG,+1,!k1Detailler);
		if (bInfo) d2(2,nGrapheDegreh(*ppgG,sSommetAvant,0));
		Assert1("GrapheRenumeroter 3",bGrapheSimple(*ppgG) );
		Assert1("GrapheRenumeroter 4",nGrapheDegreh(*ppgG,sSommetAvant,0)==0);
}//GrapheRenumeroter

void GrapheRenumeroterTout(int sListe[],graf *pgG){
	//prend en donnée la liste des futurs numéros de sommets de ppgG et remplace chaque arc (sX,couleur,sY) de ppgG par (sListe[sX],couleur,sListe[sY]) 
	int bVoir=0;
	graf *pgCopie;
	Assert1("GrapheRenumerote",sListe[0]==pgG->nSommetEnTout);
	GrapheCreer0(&pgCopie,k1Creer);
		GrapheDupliquer(pgG,&pgCopie);
		for (int sX=pgG->nSommetEnTout;sX>0;sX--)
			GrapheDesarquerTout(pgG,sX);
		if (bVoir) GrapheVoir("QuatriceRenumeroteR:pgG désarqué",pgG);
			for (int sX=1;sX<=pgCopie->nSommetEnTout;sX++)
				for (int aK=pgCopie->aHed[sX];aK<pgCopie->aHed[sX+1];aK++){
					int sY=pgCopie->sSuk[aK];
					int sZ=sListe[sX];
					int sT=sListe[sY];
					GrapheArquer0(pgG,sZ,sT,gpCouleur,pgCopie->coulh[aK]);
				}
		if (bVoir) GrapheVoir("QuatriceRenumeroteR:pgG renuméroté",pgG);
	GrapheCreer0(&pgCopie,!k1Creer);
}//GrapheRenumeroterTout

int bGrapheQuadripole(int nTypeDeMotif){
	enum grType GrapheType;
	int bQuadripole=bDans9(nTypeDeMotif,grB,gr2Croix,grQ0,grQ1,grU,grW,grX,grXX,grY);
	return(bQuadripole);
}//bGrapheQuadripole

int nGrapheQuadripoler(graf *pgSansGadget,int grGadget,int nGadgetTaille,int bCroiser,int bTout,int nGenreDePoids,graf **ppgAvecGadget){
	//ppgAvecGadget:= à chq sX tq pgG->nVal[sX]>0 on associe (sX+0,sX+1,sX+n-1,sX+n),avec entrée et sortie selon grGadget;rend nb sommets par motif.
	const int bInfo=kF;
	int nDigit,aK,sX,sY,sXprim,sYprim,uArcValeur,nMotif,sPoint,uMultipleDe10,nbQuadripole,nbSommetEnTout,nbSommetParGadget,nOffset;
	graf *pgGadget;
	enum grType GrapheType;
	if (bInfo) Appel0("nGrapheQuadripoler");
		Assert2("nGrapheQuadripoler",bGrapheQuadripole(grGadget),bGrapheAttribuT(nGenreDePoids));
		if (0 || bInfo) GrapheVoir0("pgG ORIGINAL",pgSansGadget,nGenreDePoids);
	GrapheCreer1(&pgGadget,grGadget,nGadgetTaille,k1Creer);
			if (bInfo) GrapheVoir0(sC2b("pgGadget",sGraphe(grGadget)),pgGadget,nGenreDePoids);
			nbSommetParGadget=pgGadget->nSommetEnTout;
			//d(nbSommetParGadget);
			nbSommetEnTout=pgSansGadget->nSommetEnTout;
			nbQuadripole=(bTout)? nbSommetEnTout : yVecteurSomme(pgSansGadget->nVal,1,nbSommetEnTout);
			GrapheCreer0(ppgAvecGadget,k1Creer);
			GrapheSommer(*ppgAvecGadget,(nbSommetEnTout-nbQuadripole)+(nbQuadripole*nbSommetParGadget) );
			//ajouter les arcs internes aux motifs
				nDigit=nLog10(1+(*ppgAvecGadget)->nSommetEnTout);
				uMultipleDe10=zPuissance(10,nDigit);
				if (!bTout)
					VecteurVoir1("pgSansGadget",pgSansGadget->nVal,1,pgSansGadget->nSommetEnTout);
				for (nMotif=0,sPoint=1;sPoint<=nbSommetEnTout;sPoint++)
					if (bTout || pgSansGadget->nVal[sPoint]>0)
						for (nMotif++,sX=1;sX<=nbSommetParGadget;sX++)
							for (aK=pgGadget->aHed[sX];aK<pgGadget->aHed[sX+1];aK++){
								sY=pgGadget->sSuk[aK];
								sXprim=nbSommetParGadget*(nMotif-1)+sX;
								sYprim=nbSommetParGadget*(nMotif-1)+sY;
								uArcValeur=uMultipleDe10*nMotif+sX;
								uArcValeur=pgGadget->coulh[aK];
								//uArcValeur=(200+sXprim+1)/2;//dc diag de mm poids pr grX
								if (bInfo) d7(1234,nMotif,sX,sY,sXprim,sYprim,uArcValeur);
								GrapheArquer0(*ppgAvecGadget,sXprim,sYprim,nGenreDePoids,uArcValeur);
							}
			//ajouter les arcs noirs externes aux motifs: la valeur de l'arc associé à pgG[aK=(sX,sY)] est celle de pgG->coulh[aK]
				nOffset=(grGadget==grU)? 2 : 0;
				if (bInfo) d2(bCroiser,nOffset);
				for (sX=1;sX<=nbSommetEnTout;sX++)
					for (aK=pgSansGadget->aHed[sX];aK<pgSansGadget->aHed[sX+1];aK++){
						sY=pgSansGadget->sSuk[aK];
						sXprim=nbSommetParGadget*(sX-1)+nbSommetParGadget-2+bCroiser;//si bCroiser, sortie D ds la diagonale de A.
						sYprim=nbSommetParGadget*(sY-1)+1;//entrée A.
						if (bInfo) d6(5678,sX,sY,sXprim,sYprim,pgSansGadget->coulh[aK]);
						//d(pgSansGadget->coulh[aK]);
						GrapheArquer0(*ppgAvecGadget,sXprim,sYprim,nGenreDePoids,pgSansGadget->coulh[aK]);
					}
		GrapheCreer1(&pgGadget,grGadget,nGadgetTaille,!k1Creer);
	if (bInfo) Appel1("nGrapheQuadripoler");
	return(nbSommetParGadget);
}//nGrapheQuadripoler

void GrapheQuinconceR(graf *pgG,int bBipartir){
	//déroule pgG en quinconce de façon à obtenir un dag puis,si bBipartir,dédouble chaq sommet en lui attribuant 2 numéros de sommets csécutifs.
	const int kbQuinconcer=kF;
	int bDesarquer;
	int nOffset;
	int bQuinconce;
	int uCoteh,nEtage,aK,sX,sY;
	if (kbQuinconcer) Appel0("GrapheQuinconceR");
	Assert1("GrapheQuinconceR1",bGrapheSimple(pgG));
	uCoteh=pgG->nSommetEnTout;//côté du graphe étagé à venir
	GrapheDeplier(pgG);
	Assert1("GrapheQuinconceR2",bGrapheSimple(pgG));
	//supprimer les arcs hors quinconce
		for (nEtage=uCoteh,sX=pgG->nSommetEnTout;sX>=1;sX--){
			bQuinconce=(bPair(nEtage)==bPair(sX));
			if (sX==1)
				Assert1("bQuinconce",bQuinconce);
			for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX];aK--){
				if (!bQuinconce){
					sY=pgG->sSuk[aK];
					bDesarquer=bGrapheDesarquer(pgG,sX,sY);
					Assert1("GrapheQuinconceR",bDesarquer);
				}
			}
			if ((sX-1) % uCoteh==0)
				nEtage--;
		}
		if (kbQuinconcer) VecteurVoir("aHed4",&pgG->aHed[0],1,pgG->nSommetEnTout);
		if (kbQuinconcer) VecteurVoir("sSuk4",&pgG->sSuk[0],1,pgG->nArcEnTout+pgG->nSommetEnTout/2);
		if (kbQuinconcer) GrapheVoir("Graphe biparti quinconcé",pgG);
	Assert1("GrapheQuinconceR3",bGrapheSimple(pgG));
	if (bBipartir){//réaffecter les sommets hors quinconce;le sommet 1 dédoublé devient 1 et 2;mais à l'étage suivant,le sommet n devient n-1 et n. 
		//insérer dans pgG->sSuk[] 1 arc par sommet hors quinconce ——de façon à ajouter 1 arc en pgG->sSuk[1] et en prendre acte dans pgG->aHed[]. 
			Assert1("GrapheQuinconceR4",pgG->nArcEnTout+pgG->nSommetEnTout<kuGrapheArcLim);
			for (sX=pgG->nSommetEnTout;sX>=1;sX-=2)
				for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX-1];aK--){
					sY=pgG->sSuk[aK];
					pgG->sSuk[aK+sX/2]=-sY;//décale les arcs et en profite pour les marquer négativement (exploité plus bas, et pour deboguer)
				}
			for (nOffset=0,nEtage=0,sX=1;sX<=pgG->nSommetEnTout+1;sX++){
				if (bQuinconce=(bPair(nEtage)==bPair(sX)))
					nOffset++;
				pgG->aHed[sX]+=nOffset;
				if ((sX-1) % uCoteh==0)
					nEtage++;
			}
			pgG->nArcEnTout+=nOffset;
			if (kbQuinconcer) VecteurVoir("aHed5",&pgG->aHed[0],1,pgG->nSommetEnTout);
			if (kbQuinconcer) VecteurVoir("sSuk5",&pgG->sSuk[0],1,pgG->nArcEnTout);
			if (kbQuinconcer) GrapheVoir("Graphe biparti quinconcé TRANSITOIRE",pgG);
		//actualiser la cible de chaque arc: l'arc origine d'un sommet dédoublé cible le sommet suivant;l'arc destination cible un sommet positif. 
			for (nEtage=uCoteh,sX=pgG->nSommetEnTout;sX>=1;sX--){
				bQuinconce=(bPair(nEtage)==bPair(sX));
				for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX];aK--){
					sY=pgG->sSuk[aK];
					if (sY<0)//cet arc original doit cibler maintenant le sommet origine de chaque sommet bipartitionné
						pgG->sSuk[aK]=bPair(nEtage)? -sY : -sY-1;//cible le bon sommet positif.
					else pgG->sSuk[aK]=sX+1;//logique car le sommet 1 est devenu 1 et 2;à l'étage suivant, n est devenu n-1 et n
				}
				if ((sX-1) % uCoteh==0)
					nEtage--;
			}
		if (kbQuinconcer) VecteurVoir("aHed6",&pgG->aHed[0],1,pgG->nSommetEnTout);
		if (kbQuinconcer) VecteurVoir("sSuk6",&pgG->sSuk[0],1,pgG->nArcEnTout);
		if (kbQuinconcer) GrapheVoir("Graphe biparti quinconcé FINAL",pgG);
	}//Le plus souvent,le graphe obtenu n'est pas connexe. 
	Assert2("GrapheQuinconceR2",bGrapheSimple(pgG),!bBipartir || bGrapheBiparti(pgG,!k1Afficher));//Si bBipartir,aucun sommet n'est isolé.
	if (kbQuinconcer) Appel1("GrapheQuinconceR");
}//GrapheQuinconceR

void GrapheQuintesser(graf *pgG,int nSommet){
	//génère un graphe déroulé bipari en quiconce puis l'étoile et connecte les étoiles amont et aval à chaque colonne;
	#define kbQuintesser kF
	int uB,uE,nPaire,sX,sYamont,sYaval;
	int bDesarquer;
	int aK,aL;
	int nSommet0;
	if (kbQuintesser) Appel0("GrapheQuintesser");
	if (kbQuintesser) d(nSommet);
	GrapheCliquer(pgG,nSommet);
	if (0){
		if (nSommet==3)
			bDesarquer=bGrapheDesarquer(pgG,2,3) && bGrapheDesarquer(pgG,3,2);
		if (nSommet==4)
			bDesarquer=bGrapheDesarquer(pgG,2,3) && bGrapheDesarquer(pgG,2,4);
	}
	GrapheVoir("Graphe cliqué",pgG);
	GrapheBipartitionner(pgG);
	GrapheVoir("Graphe cliqué biparti",pgG);
	GrapheQuinconceR(pgG,k1BipartiR);
	//refermer le chemin diagonal pour obtenir un circuit
		GrapheArquer(pgG,1,pgG->nSommetEnTout);
	GrapheVoir("Graphe cliqué biparti quinconcé et bipartitionné",pgG);
	nSommet0=pgG->nSommetEnTout;
	int nEtoile=4*nSommet;
	if (kbQuintesser) d(nEtoile);
	int uBrancheParEtoile=nSommet;
	int nSommetParEtoile=1+uBrancheParEtoile;
	if (kbQuintesser) d(uBrancheParEtoile);
	GrapheEtoiler(pgG,nEtoile,uBrancheParEtoile);
	GrapheVoir("Graphe cliqué biparti quinconcé bipartitionné et étoilé",pgG);
	if (kbQuintesser) d(nSommet0);
	//connecter les étoiles au reste du graphe
		for (uE=1;uE<=nEtoile/2;uE++){
			sYamont=nSommet0+2*(uE-1)*nSommetParEtoile+1;//centre étoile amont
			sYaval=sYamont+nSommetParEtoile;//centre étoile aval
			if (kbQuintesser) printf("Centres des étoiles amont et aval:%d,%d.\n",sYamont,sYaval);
			for (sX=2*(uE-1)+1,uB=1;sYamont++,sYaval++,uB<=uBrancheParEtoile;uB++){
				if (kbQuintesser) printf("arc sX,Centre amont:       (%2d,%2d)\n",sX,sYamont);
				if (kbQuintesser) printf("arc sX,Centre aval:       (%2d,%2d)\n",sX+1,sYaval);
				GrapheArquer(pgG,sX,sYamont);
				GrapheArquer(pgG,sX+1,sYaval);
				sX+=4*nSommet;
			}
		}
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		pgG->aDeh[sX]=0;
	for (nPaire=0,uE=1;uE<=nEtoile/2;uE++){
		sYamont=nSommet0+2*(uE-1)*nSommetParEtoile+1;
		sYaval=sYamont+nSommetParEtoile;
		pgG->aDeh[sYamont]=sYaval;pgG->aDeh[sYaval]=sYamont;nPaire++;
		if (kbQuintesser) printf("Couple %s\n",sCouple(sYamont,sYaval));
		if (kbQuintesser) sd("étoile0",sYamont);
		for (sX=2*(uE-1)+1,uB=1;sYamont++,sYaval++,uB<=uBrancheParEtoile;uB++){
			//if (kbQuintesser) printf("arc sX,sYamont:       (%2d,%2d)\n",sX,sYamont);
			//if (kbQuintesser) printf("arc sX,sYaval:       (%2d,%2d)\n",sX+1,sYaval);
			aK=nGrapheArc(pgG,sX,sYamont);
			aL=nGrapheArc(pgG,sX+1,sYaval);
			pgG->aDeh[sX]=sX+1;pgG->aDeh[sX+1]=sX;nPaire++;
			if (kbQuintesser) printf("Couple %s\n",sCouple(sX,sX+1));
			pgG->aDeh[sYamont]=sYaval;pgG->aDeh[sYaval]=sYamont;nPaire++;
			if (kbQuintesser) printf("Couple %s\n",sCouple(sYamont,sYaval));
			sX+=4*nSommet;
		}
	}
	teee("nEtoile,uBrancheParEtoile+1,nPaire",nEtoile,uBrancheParEtoile+1,nPaire);
	Assert1("GrapheQuintesser",sYaval=pgG->nSommetEnTout);
	if (kbQuintesser) Appel1("GrapheQuintesser");
}//GrapheQuintesser

void GrapheRetourner(graf *pgG,int bRetourner,graf **ppgH){
	//si bRetourner,alloue et rend le graphe inverse de pgG;sinon,restitue pgH
	int sX,sY;
	if (bRetourner){
		GrapheCreer(pgG->nSommetEnTout,ppgH);
			//pgH:=graphe symétrique de pgG
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
						GrapheArquer0(*ppgH,sY=pgG->sSuk[aK],sX,gpCout,pgG->nCout[aK]);
				Assert2("GrapheRetourner",pgG->nSommetEnTout==(*ppgH)->nSommetEnTout,pgG->nArcEnTout==(*ppgH)->nArcEnTout);
	}else GrapheCreer(0,ppgH);
}//GrapheRetourner

void GrapheScruter(char *sQuoi,graf *pgG,int tMode,int bDetailler){
	//affiche selon tMode les champs aHed,aDeh,sSuk,sKus de pgG. Si non kbBrut, affiche aInv et liste les arcs à la place de sSuk et sKus.
	const int kbBrut=0;
	int aK,sX;
	Assert5("GrapheVoir",bGrapheAmorceR,sQuoi!=0,bTrit(tMode),bBool(kbBrut),bBool(bDetailler));
	printf("%s%c(%s et %s):\n",sQuoi,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"));
	GrapheInverser(pgG);
	int bCaractere=bModeCaractere();
	if (bCaractere) ModeCaractere(0);
		Tabuler(1);
			if (pgG->nArcEnTout>0){
				if (tMode>0){//graphe direct seul
					VecteurVoir1("aHed ",pgG->aHed,0,pgG->nSommetEnTout+1);//Ligne();
					VecteurVoir1("sSuk ",pgG->sSuk,1,pgG->nArcEnTout);
					if (bDetailler)
						printf("%sNB: aHed est indexé par des sommets et contient des arcs. C'est l'inverse pour sSuk.\n",flag);
				}else if (tMode<0){//graphe inverse seul
					VecteurVoir1("aDeh ",pgG->aDeh,0,pgG->nSommetEnTout+1);//Ligne();
					VecteurVoir1("sKus ",pgG->sKus,1,pgG->nArcEnTout);
					if (bDetailler)
						printf("%sNB: aDeh est indexé par des sommets et contient des arcs. C'est l'inverse pour sKus.\n",flag);
				}else if (kbBrut){//graphes direct et inverse
					VecteurVoir5("aHed ,aDeh ",pgG->aHed,pgG->aDeh,0,pgG->nSommetEnTout+1);//Ligne();
					VecteurVoir5("sSuk ,sKus ",pgG->sSuk,pgG->sKus,1,pgG->nArcEnTout);
					if (bDetailler)
						printf("%sNB: aHed et aDeh sont indexés par des sommets et contiennent des arcs. C'est l'inverse pour sSuk et sKus.\n",flag);
				}else {//graphes direct et inverse + aInv, et des listes d'arcs remplacent sSuk et sKus.
					for (printf("%saHed:",sTab0()),sX=1;sX<=pgG->nSommetEnTout || bPrint(".");sX++)
						printf("  (%2d,%2d)",sX,pgG->aHed[sX]);
					for (printf("%saDeh:",sTab0()),sX=1;sX<=pgG->nSommetEnTout || bPrint(".");sX++)
						printf("  (%2d,%2d)",sX,pgG->aDeh[sX]);
					for (printf("%ssSuk:",sTab0()),sX=1;sX<=pgG->nSommetEnTout || bPrint(".");sX++)
						for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
							printf("  (%2d,%2d)",sX,pgG->sSuk[aK]);
					for (printf("%ssKus:",sTab0()),sX=1;sX<=pgG->nSommetEnTout || bPrint(".");sX++)
						for (aK=pgG->aDeh[sX];aK<pgG->aDeh[sX+1];aK++)
							printf("  (%2d,%2d)",sX,pgG->sKus[aK]);
					for (printf("%saInv:",sTab0()),aK=1;aK<=pgG->nArcEnTout || bPrint(".");aK++)
						printf("  (%2d,%2d)",aK,pgG->aInv[aK]);
					Tabuler(-2);
				}
			}else printf(" Aucun arc.\n");
		Tabuler(-1);
	if (bCaractere) ModeCaractere(-1);
}//GrapheScruter

void GrapheSimple(int bBoucleInterdite){
	//active ou désactive le contrôle de la présence de boucles dans les graphes.
	Assert1("GrapheSimple",bBool(bBoucleInterdite));
	bGrapheSimplE=bBoucleInterdite;//si vrai, tt graphe qui ctient une boucle est dénoncé.
}//GrapheSimple

int bGrapheSimple(graf *pgG){
	//ni boucle,ni plus d'un arc d'un sommet origine à un sommet destination
	int aK,sX,sY;
	int bSimple;
	int nSucc[1+pgG->nSommetEnTout];
	Assert2("bGrapheSimple",bGrapheAmorceR,bGraphe(pgG));
	if (bGrapheSimplE)
		for (bSimple=sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (sY=1;sY<=pgG->nSommetEnTout;sY++)
				nSucc[sY]=0;
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				if (sX==sY)
					bSimple=kF;
				if ( !bGrapheSommet(pgG,sY) || (++nSucc[sY]>1) )
					bSimple=kF;
			}
		}
	else bSimple=1;
	return(bSimple);
}//bGrapheSimple

void GrapheSommer(graf *pgG,int inEmpilerSinonDepiler){
	//si inEmpilerSinonDepiler>0,empile inEmpilerSinonDepiler sommets;si <0,élimine ts les arcs liés aux sommets et les dépile (n° pgG->nSommetEnTout) puis dépile ce sommet
	int uS;
	Assert2("GrapheSommer1",bGrapheAmorceR,bGrapheSimple(pgG));
	//d(inEmpilerSinonDepiler);
	if (inEmpilerSinonDepiler!=0)
		if (inEmpilerSinonDepiler>0) {
			Assert1("GrapheSommer2",pgG->nSommetEnTout+inEmpilerSinonDepiler<kuGrapheSommetLim);
			for (uS=1;uS<=inEmpilerSinonDepiler;uS++){
				pgG->aHed[pgG->nSommetEnTout+2]=pgG->aHed[pgG->nSommetEnTout+1];//crée les nouveaux sommets,sans arcs incidents.
				(pgG->nSommetEnTout)+=1;
			}//d(pgG->nSommetEnTout);
		}
		else {
			Assert1("GrapheSommer3",pgG->nSommetEnTout>-inEmpilerSinonDepiler);
			for (uS=1;uS<=-inEmpilerSinonDepiler;uS++){
				GrapheDesarquerTout(pgG, pgG->nSommetEnTout);//dépile le dernier sommet
				pgG->aHed[pgG->nSommetEnTout+1]=0;
				(pgG->nSommetEnTout)--;
			}
		}
	Assert2("GrapheSommer4",bGraphe(pgG),bGrapheSimple(pgG));
}//GrapheSommer

int bGrapheSommet(graf *pgG,int sSommet){
	int bGrapheSommet=bCroit(1,sSommet,pgG->nSommetEnTout);
	return(bGrapheSommet);
}//bGrapheSommet

int bGrapheSymetrique(graf *pgG){//O(A)
	//à tout arc (X,Y) présent dans pgG correspond dans pgG un arc inverse (Y,X)
	graf *pgH;
	int bSymetrique;
	Assert2("bGrapheSymetrique",bGrapheAmorceR,bGraphe(pgG));
	pgH=(graf *) malloc(sizeof(graf));
		GrapheDupliquer(pgG,&pgH);//O(A)
		//GrapheVoir("pgH",pgH);
		GrapheSymetriser(pgH,gpCouleur+gpCout);//O(A)
		bSymetrique=(pgG->nArcEnTout==pgH->nArcEnTout);
	free(pgH);
	//Assert1("bGrapheSymetrique1",bSymetrique);
	return(bSymetrique);
}//bGrapheSymetrique

void GrapheSymetriqueCreerPondereR(int bDense,int nSommetEnTout,int uPoidsMax,graf **ppgG){
	//alloue et rend un graphe symétrique "intéressant" à nSommetEnTout sommets,pondéré aléatoirement de 1 à uPoidsMax ——champ (*ppgG)->nCout. 
	int aK,aL;
	int sX,sY;
	//Appel0("GrapheSymetriqueCreerPondereR");
		Assert2("GrapheSymetriqueCreerPondereR",uPoidsMax>0,bCroitStrict(0,nSommetEnTout,kuGrapheSommetLim));
		if (bDense)
			GrapheCompletCreerPondereR(nSommetEnTout,ppgG);
		else GrapheCreer(nSommetEnTout,ppgG);
			//GrapheVoir("AVANT symétrisation",pgG);
			GrapheSymetriser(*ppgG,gpCouleur+gpCout);
			//GrapheVoir("APRES symétrisation",pgG);
			if (0){
				t("Extrémités des arêtes");
				for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++)
					printf("%4d",(*ppgG)->sSuk[aK]);
				printf("\n");
				for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++)
					printf("%4d",(*ppgG)->sKus[aK]);
				printf("\n");
			}
			GrapheInverser(*ppgG);
			//initialiser les poids pgG->nCout[aK] et compléter la correspondance aK->sX,sY via pgG->nPhi[aK]=sX en plus de pgG->sSuk[aK]=sY
				for (sX=1;sX<=(*ppgG)->nSommetEnTout;sX++)
					for (aK=(*ppgG)->aHed[sX];aK<(*ppgG)->aHed[sX+1];aK++){
						sY=(*ppgG)->sSuk[aK];
						aL=(*ppgG)->aInv[aK];
						Assert1("GrapheSymetriqueCreerPondereR2",(*ppgG)->sSuk[aL]==sX); 
						(*ppgG)->nPhi[aK]=sX;
						Assert1("GrapheSymetriqueCreerPondereR3",(*ppgG)->sSuk[(*ppgG)->aInv[aK]]==(*ppgG)->nPhi[aK]);//donc nPhi est d'une certaine façon superflu
						(*ppgG)->nCout[aK]=uHasard(uPoidsMax);
						//teeee("arête et poids X Y",aK,pgG->nCout[aK],sX,sY);
					}
				GraphePondererPareiL(*ppgG);//O(A);le poids des arcs (X,Y) et (Y,X) est maintenant identique.
			//GrapheVoir0("——— Donnée: un graphe non orienté",*ppgG);
				if (0) for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++){
					d(aK);
					Assert1("GrapheSymetriqueCreerPondereR8",(*ppgG)->nPhi[aK]>0);
				}
	//Appel1("GrapheSymetriqueCreerPondereR");
}//GrapheSymetriqueCreerPondereR

void GrapheSymetriser(graf *pgG,int nGenreDePoids){//O(A)
	//symétrise pgG en complétant les (X,Y) par les (Y,X) manquants. Si nGenreDePoids non nul,recopie le pondérateur en question de (X,Y) vers (Y,X).
	int aK,aL,aM;//aM est l'index de pile qui progresse sur pgG->sSuk[],cf pgG->sSuk[++aM]
	graf *pgH;
	int nCumul[1+pgG->nSommetEnTout];
	int bPred[1+pgG->nSommetEnTout];
	int bSucc[1+pgG->nSommetEnTout];
	int sX,sZ;
	Assert3("GrapheSymetriser",bGrapheAmorceR,bGraphe(pgG),bGrapheAttribuT(nGenreDePoids));
	pgH=(graf *) malloc(sizeof(graf));
		GrapheDupliquer(pgG,&pgH);//O(A)
		GrapheInverser(pgH);//O(A)
		//GrapheVoir1("pgG",pgG,k1Couleur);GrapheVoir1("pgH",pgH,k1Couleur);
		//pgG->sSuk[],pgG->coulh[],nCumul[]:= les arcs de pgG symétrisé, ses couleurs, le cumul des arcs empilés sommet par sommet.
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
				bPred[sX]=bSucc[sX]=kF;
//GrapheVoir1("pgH",pgH,k1Couleur);
			for (aM=0,sX=1;sX<=pgH->nSommetEnTout;sX++){//O(A): les 3 aK et les 3 aL ci-dessous visitent 6 fois la totalité des arcs de pgH 
				//bSucc[] / bPred[]:=coche des sommets successeurs de sX dans pgH / des sommets prédécesseurs de sX dans pgH:
					for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++)//au total,cet aK aura indexé 1 fois chacun des arcs de pgH.
						bSucc[pgH->sSuk[aK]]=kV;
					for (aL=pgH->aDeh[sX];aL<pgH->aDeh[sX+1];aL++)//au total,cet aL aura indexé 1 fois chacun des arcs de pgH.
						bPred[pgH->sKus[aL]]=kV;
					//VecteurVoir("nSucc",nSucc,1,pgG->nSommetEnTout);VecteurVoir("nPred",nPred,1,pgG->nSommetEnTout);
				//empiler dans pgG les sommets de bSucc union bPred,ie tous ceux de pgH->sSuk[],plus ceux cochés dans bPred mais pas dans bSucc:
					for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++){//au total,cet aK aura passé en revue 1 fois la totalité des arcs de pgH
						Assert1("GrapheSymetriser1",aM+1<kuGrapheArcLim);
						pgG->sSuk[++aM]=pgH->sSuk[aK];//empile ds pgG
						pgG->nCapaMax[aM]=pgH->nCapaMax[aK];
						pgG->nCapaMin[aM]=pgH->nCapaMin[aK];
						pgG->coulh[aM]=pgH->coulh[aK];
						pgG->nCout[aM]=pgH->nCout[aK];
						pgG->nPoids[aM]=pgH->nPoids[aK];
						//d2(1,aM);
					}//for (aK
					for (aL=pgH->aDeh[sX];aL<pgH->aDeh[sX+1];aL++){//au total,cet aL aura indexé 1 fois chacun des arcs de pgH.
						sZ=pgH->sKus[aL];
						if (bPred[sZ] && !bSucc[sZ]){//ajouter l'arc manquant aL:
							Assert1("GrapheSymetriser2",aM+1<kuGrapheArcLim);
							pgG->sSuk[++aM]=sZ;
						//d2(2,aM);
							pgG->nCapaMax[aM]=0;
							pgG->nCapaMin[aM]=0;
							pgG->coulh[aM]=0;//la couleur de l'arc aL est celle de l'arc inverse de aL.
							pgG->nCout[aM]=0;
							pgG->nPoids[aM]=0;
							
							aK=pgH->aInv[aL];
							//GrapheAttribueR(pgH,aK,nGenreDePoids,pgG,aM);//NE CONVIENT PAS
							if (nGenreDePoids & gpCapaMax) pgG->nCapaMax[aM]=pgH->nCapaMax[aK];
							if (nGenreDePoids & gpCapaMin) pgG->nCapaMin[aM]=pgH->nCapaMin[aK];
							if (nGenreDePoids & gpCouleur) pgG->coulh[aM]=pgH->coulh[aK];//la couleur de l'arc aL est celle de l'arc inverse de aL.
							if (nGenreDePoids & gpCout) pgG->nCout[aM]=pgH->nCout[aK];
							if (nGenreDePoids & gpPhi) pgG->nPhi[aM]=pgH->nPhi[aK];
							if (nGenreDePoids & gpPoids) pgG->nPoids[aM]=pgH->nPoids[aK];
						}//if (bPred[sZ] && !bSucc[sZ]
					}
				nCumul[sX]=aM;
				//bSucc[] / bPred[]:=décoche des sommets successeurs de sX dans pgH / des sommets prédécesseurs de sX dans pgH:
					for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++)//au total,cet aK aura indexé 1 fois chacun des arcs de pgH.
						bSucc[pgH->sSuk[aK]]=kF;
					for (aL=pgH->aDeh[sX];aL<pgH->aDeh[sX+1];aL++)//au total,cet aL aura indexé 1 fois chacun des arcs de pgH.
						bPred[pgH->sKus[aL]]=kF;
			}
	free(pgH);
	//pgG->aHed[]:=nouveaux index fonctions de nCumul[]
		for (pgG->aHed[1]=sX=1;sX<=pgG->nSommetEnTout;sX++)//oui, pgG->aHed[1] valait déjà 1.
			pgG->aHed[sX+1]=nCumul[sX]+1;
	//pgG->nSommetEnTout est déjà correct: symétriser le graphe ne modifie pas le nombre de ses sommets.
	pgG->nArcEnTout=nCumul[pgG->nSommetEnTout];
	Assert1("GrapheSymetriser",bGrapheSimple(pgG));
	//GrapheVoir1("pgG symétrisé",pgG,k1Couleur);
}//GrapheSymetriser

void GrapheTESTER(int iTest){
	const int k1Prim=kV;
	const int ksSource=1;
	int bkAfficher=1;
	int nArcOrigine[]=    {0,   1,2,3,3,2};
	int nArcDestination[]={0,   2,3,1,2,1};
	int nGraphe,nPoidsMax;
	char kcTriominoComplet[]="AB1BC1BG1CD1CF7DE1EF1FG1GH1HA9";//1 composante connexe et 1 composante fortement connexe
	char kcTriominoIncomplet[]="AB1BG1CD1CF7DE1EF1FG1GH1HA9";//1 composante connexe et 5 composantes fortement connexes
	int bBiparti,bCheminer,bCircuit,bEulerien,aK;
	graf *pgG,*pgH;
	int bSimple;
	int nSommet,uSommet;
	int nComplexiteh;
	enum grType GrapheType;
	// GrapheType {grAlpha,grL4,grC4b,grC2,grC3,grC4,grC5,grC6,grK2,grK3,grK4,grK5,grK6,grP2,grP3,grP4,grP5,grP6,grP7,grP8,grS2,grS3,grS4,grS5,grS6,grOmega}
	Appel0(sC2("GrapheTESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case 0:	bGrapheGenerer("AB2345AC0BC25CD34",gpCout,&pgG);//ùù
					GrapheVoir0("pgG",pgG,gpCapaMax+gpCout+gpPhi+gpZeta);
					s(sGrapheCouple(pgG,2,3,gpCout));
					break;
			case 1: GrapheCreer(1,&pgG);
					GrapheDecrire( (pgG->nSommetEnTout=8,pgG) );
					bSimple=bGrapheSimple(pgG);
					printf( "Le graphe à %s %s simple.\n",sPluriel(pgG->nSommetEnTout,"sommet"),sPas("est",!bSimple) );
					GrapheCreer(0,&pgG);
					break;
			case 2: GrapheCreer(1,&pgG);
					GrapheDecrire( (pgG->nSommetEnTout=2,pgG) );
					GrapheSymetriser(pgG,gpCouleur+gpCout);
					GrapheVoir("graphe eulérien non orienté",pgG);
					GrapheInverser(pgG);
					bEulerien=bGrapheEulerien(pgG,!k1Digraphe,0,0,!k1Afficher);
					printf( "Le graphe à %s %s eulérien.\n",sPluriel(pgG->nSommetEnTout,"sommet"),sPas("est",!bEulerien) );
					bEulerien=bEulerien && bGrapheEulerier(pgG,!k1Digraphe,1,1);
					GrapheCreer(0,&pgG);
					break;
			case 3: GrapheSymetriqueCreerPondereR(k1Dense,50,nPoidsMax=9,&pgG);
						GrapheVoir0("——— Donnée: un graphe non orienté",pgG,gpCout);
						GrapheCouvrirAvecPrimOuP(pgG,k1Prim,k1Afficher,k1PerformanceCompareR);
					GrapheCreer(0,&pgG);
					break;
			case 4: GrapheSymetriqueCreerPondereR(!k1Dense,50,nPoidsMax=9,&pgG);
						GrapheVoir0("——— Donnée: un graphe non orienté",pgG,gpCout);
						GrapheCouvrirAvecKruskaL(pgG,k1Afficher,k1PerformanceCompareR);
					GrapheCreer(0,&pgG);
					break;
			case 5: GrapheCouvriR();
					break;
			case 6: if (0) for (uSommet=1;uSommet<10;uSommet++){
						GrapheCreer(uSommet,&pgG);
							GrapheVoir(sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")),pgG);
							bCheminer=bGrapheCheminerCourt(pgG,ksSource,pgG->nSommetEnTout,!k1Tas,bkAfficher,&nBof,&nComplexiteh);
							if (!bkAfficher)
								printf("Il %s un chemin.\n",sPas("y a vraiment",!bCheminer));
						GrapheCreer(0,&pgG);
					}
					if (0) for (uSommet=10;uSommet<=10;uSommet++){
						GrapheCreer(uSommet,&pgG);
							GrapheArquer(pgG, 1, 4);
							bGrapheDesarquer(pgG, 4, 2);
							GrapheVoir(sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")),pgG);
							bCheminer=bGrapheCheminerLong(pgG,ksSource,pgG->nSommetEnTout,bkAfficher,&nComplexiteh);
							if (!bkAfficher)
								printf("Il %s un chemin.\n",sPas("y a vraiment",!bCheminer));
						GrapheCreer(0,&pgG);
					}
					if (0) for (uSommet=3;uSommet<10;uSommet++){
						GrapheCreer(uSommet, &pgG);
							GrapheInverser(pgG);
							GrapheVoir2(sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")),pgG);
							bCircuit=bGrapheCircuite(pgG,!k1Afficher);
							t(sC3bp("Il",sUn("y a",bCircuit),"circuit"));
						GrapheCreer(0,&pgG);
					}
					if (0){
						GrapheCreer(4,&pgG);
							GrapheDeplier(pgG);
							GrapheVoir(sC4b("Le graphe étagé a",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")),pgG);
						GrapheCreer(0,&pgG);
					}
					if (1){
						GrapheCreer(6,&pgG);
							GrapheSymetriser(pgG,gpCouleur+gpCout);
							GraphePondererAleatoirement(pgG,gpCout,5);
							GrapheVoir0("Graphe de largeur",pgG,gpCout);
							bCircuit=bGrapheCheminerAuLarge(pgG,1,6,kV);//***********
						GrapheCreer(0,&pgG);
					}
					if (0){
						GrapheCreer(3,&pgG);
							GrapheSymetriser(pgG,gpCouleur+gpCout);
							bBiparti=bGrapheBipartiOuAfficherCycleImpair(pgG);
							GrapheVoir(sC3b("Le graphe ci-dessous",sEst(bBiparti),"biparti"),pgG);
						GrapheCreer(0,&pgG);
						GrapheCreer(4,&pgG);
							GrapheSymetriser(pgG,gpCouleur+gpCout);
							bBiparti=bGrapheBipartiOuAfficherCycleImpair(pgG);
							GrapheVoir(sC3b("Le graphe ci-dessous",sEst(bBiparti),"biparti"),pgG);
						GrapheCreer(0,&pgG);
						GrapheCreer(6,&pgG);
							GrapheSymetriser(pgG,gpCouleur+gpCout);
							bBiparti=bGrapheBipartiOuAfficherCycleImpair(pgG);
							GrapheVoir(sC3b("Le graphe ci-dessous",sEst(bBiparti),"biparti"),pgG);
						GrapheCreer(0,&pgG);
					}
					break;
					if (0){
						GrapheCreer(3,&pgG);
							GrapheVoir("Graphe original",pgG);
							GrapheBipartitionner(pgG);
							GrapheVoir("Graphe biparti résultant",pgG);
						GrapheCreer(0,&pgG);
						GrapheCreer(4,&pgG);
							GrapheVoir("Graphe original",pgG);
							GrapheBipartitionner(pgG);
							GrapheVoir("Graphe biparti résultant",pgG);
						GrapheCreer(0,&pgG);
						GrapheCreer(6,&pgG);
							GrapheVoir("Graphe original",pgG);
							GrapheBipartitionner(pgG);
							GrapheVoir("Graphe biparti résultant",pgG);
						GrapheCreer(0,&pgG);
					}
					break;
			case 7:	{//GrapheQuinconceR & GrapheEtoiler
						GrapheCreer2(&pgG,3,5,&nArcOrigine[0],&nArcDestination[0]);
							GrapheVoir("Graphe original",pgG);
							GrapheBipartitionner(pgG);
							GrapheVoir("Graphe biparti résultant",pgG);
							GrapheQuinconceR(pgG,k1BipartiR);
							GrapheVoir("Graphe biparti quinconcé et bipartitionné",pgG);
							GrapheEtoiler(pgG,2,3);
							GrapheVoir("Graphe biparti quinconcé et bipartitionné et étoilé 2*3",pgG);
						GrapheCreer(0,&pgG);
					}
					break;
			case 8:	{//GrapheCliquer
						GrapheCreer2(&pgG,3,5,&nArcOrigine[0],&nArcDestination[0]);
							GrapheVoir("Graphe original",pgG);
							GrapheCliquer(pgG,4);
							GrapheVoir("Graphe original cliqué",pgG);
						GrapheCreer(0,&pgG);
					}
					break;
			case 11:{//GrapheQuintesser
						GrapheCreer0(&pgG,kV);
							GrapheQuintesser(pgG,nSommet=3);
							GrapheVoir("Graphe quiné",pgG);
						GrapheCreer0(&pgG,kF);
					}
					break;
			case 13:	DijkstraAvecOuSansTasCompareR();
					break;
			case 15:	GrapheCreer(4,&pgG);
						GrapheColorer(pgG,1,2,1);
						GrapheColorer(pgG,2,4,2);
						GrapheColorer(pgG,3,2,3);
						GrapheColorer(pgG,3,1,4);
						GrapheColorer(pgG,3,4,5);
						GrapheVoir1("Graphe original",pgG,k1Couleur);
						bBof=bGrapheSymetrique(pgG);
						Assert1("GrapheTESTER90",!bBof);
						GrapheSymetriser(pgG,gpCouleur+gpCout);
						GrapheVoir1("Graphe symétrisé",pgG,k1Couleur);
						bBof=bGrapheSymetrique(pgG);
						Assert1("GrapheTESTER91",bBof);
					GrapheCreer(0,&pgG);
					break;
			case 20:	bGrapheGenerer(kcTriominoIncomplet,gpCouleur,&pgG);
						for (aK=1;aK<=pgG->nArcEnTout;aK++)
							pgG->nCout[aK]=pgG->coulh[aK];
						GrapheCircuiterAuMieux(pgG);
						break;
			case 30:	bGrapheGenerer(kcTriominoComplet,gpCouleur,&pgG);
						for (aK=1;aK<=pgG->nArcEnTout;aK++)
							pgG->nCout[aK]=pgG->coulh[aK];
						GrapheCircuiterAuMieux(pgG);
						break;
			case 40:
					Titrer("test des types de graphe générées");
					for (nGraphe=grAlpha+1;nGraphe<grOmega;nGraphe++){
						GrapheCreer1(&pgG,nGraphe,0,k1Creer);
							GrapheVoir(sGraphe(nGraphe),pgG);
						GrapheCreer0(&pgG,kF);
					}
					break;
			case 41:
					Titrer("test de nGrapheQuadripoler");
					GrapheCreer1(&pgG,grK,3,k1Creer);
						GrapheVoir(sGraphe(grK),pgG);
						nBof=nGrapheQuadripoler(pgG,grQ0,0,!k1Croiser,k1Tout,gpCouleur,&pgH);
						GrapheVoir(sC2b(sGraphe(grK),"quadripolé"),pgH);
					GrapheCreer1(&pgG,grK,3,!k1Creer);
					break;
			case 42:
					Titrer("test de GrapheRenumeroter");
					GrapheCreer1(&pgG,grK,3,k1Creer);
						GrapheSommer(pgG,1);
						GrapheVoir(sGraphe(grK),pgG);
						d2(1,nGrapheDegreh(pgG,1,0));
						GrapheRenumeroter(&pgG,1,4);
						GrapheVoir(sC2b(sGraphe(grK),"renumeroté"),pgG);
						d2(2,nGrapheDegreh(pgG,1,0));
						GrapheRenumeroter(&pgG,4,1);
						d2(3,nGrapheDegreh(pgG,1,0));
						GrapheVoir(sC2b(sGraphe(grK),"renumeroté"),pgG);
					GrapheCreer1(&pgG,grK,3,!k1Creer);
					break;
			default:break;
		}
	Appel1(sC2("GrapheTESTER,test n°",sEnt(iTest)));
}//GrapheTESTER

void GrapheTitreR(graf *pgG,char *sMessage){
	const int kuIndentation=1;
	printf("%s%c(%s, %s, densité %.2f):\n%s",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"),fGrapheDensiteh(pgG,1,!k1Voir),sTab(kuIndentation));
}

void GrapheTranslater(graf *pgG,int nOffset){
	//renumérote tous les sommets de pgG: le sommet n°sX sera renuméroté sX+nOffset.
	int aK,sX;
	Assert1("GrapheTranslater",nOffset>=0);
	if (nOffset>0){
		//d2(uOffset,pgG->nSommetEnTout);
		//VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout+1);
		GrapheSommer(pgG,nOffset);
		//d2(uOffset,pgG->nSommetEnTout);
		for (sX=pgG->nSommetEnTout+1;sX>nOffset;sX--)
			pgG->aHed[sX]=pgG->aHed[sX-nOffset];
		for (sX=nOffset;sX>0;sX--)
			pgG->aHed[sX]=1;
		//VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout+1);
		for (aK=1;aK<=pgG->nArcEnTout;aK++)
			pgG->sSuk[aK]+=nOffset;
	}
}//GrapheTranslater

int bGrapheTrierTopologiquement(graf *pgG,int idAfficher){//O(A)
	//effectue un tri topologique et stocke les niveaux des sommets ds pgG->nVal
	const int kbVoir=0;
	int nNiveau[1+pgG->nSommetEnTout];
	int nPred[1+pgG->nSommetEnTout];
	int uCardinal,uS,aK,sX,sY,nNivo=0;
	//GrapheVoir("bGrapheTrierTopologiquement",pgG);
	Assert1("bGrapheTrierTopologiquement",bGrapheSimple(pgG));
	//nPred[sY]:=degré entrant du sommet sY
		VecteurRazer(nPred,1,pgG->nSommetEnTout);//O(S)
		for (aK=1;aK<=pgG->nArcEnTout;aK++)//O(A)
			nPred[sY=pgG->sSuk[aK]]++;
	DequeAllouer(pgG->nSommetEnTout);
		VecteurRazer(nNiveau,1,pgG->nSommetEnTout);//O(S)
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			if (!nPred[sX]) DequeEnfiler(sX);
		if (kbVoir) VecteurVoir("nPred",nPred,1,pgG->nSommetEnTout);
		while (!bDequeVide())//O(A)
			for (nNivo++,uCardinal=nDequeCardinal(),uS=1;uS<=uCardinal;uS++){
				sX=sDequeDefiler();
				nNiveau[sX]=nNivo;
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					nPred[sY=pgG->sSuk[aK]]--;
					Assert1("GrapheTrier8",nPred[sY]>=0);
					if (!nPred[sY])
						DequeEnfiler(sY);
				}
			}
		if (kbVoir || idAfficher){
			if (idAfficher)
				printf("\t%sTri topologique des sommets du graphe %s:\n",sTab0(),(idAfficher>=0)? "direct": "inverse");
			for (printf("\t\tSommet:"),sX=1;sX<=pgG->nSommetEnTout || bPrint("");sX++)
				printf("%3s",sEnt(sX));
			for (printf("\t\tNiveau:"),nNivo=1;nNivo<=pgG->nSommetEnTout || bPrint(".");nNivo++)
				printf("%3d",nNiveau[nNivo]);
		}
		VecteurCopier(nNiveau,1,pgG->nSommetEnTout,pgG->nVal);
		//VecteurVoir("pgG->nVal",pgG->nVal,1,pgG->nSommetEnTout);
	DequeAllouer(0);
	int nOccurrence=nVecteurOccurrence(0,pgG->nVal,1,pgG->nSommetEnTout);
	int bTrierTopologiquement=nOccurrence==0;
	if (abs(idAfficher)>1){
		printf("%s %s niveau nul ",flag,(bTrierTopologiquement)? "L'absence de" : "La présence d'un");
		printf("signifie que le graphe %s circuit.\n",(bTrierTopologiquement)? "est sans" : "contient un");
	}return(bTrierTopologiquement);
}//bGrapheTrierTopologiquement

int bGrapheVidE(graf *pgG){
	int bVide;
	Assert2("bGrapheVidE0",bGrapheAmorceR,bGraphe(pgG));
	bVide=(pgG->nSommetEnTout==0);
	if (bVide)
		Assert1("bGrapheVidE1",pgG->nArcEnTout==0);//sinon,savoir pourquoi
	return(bVide);
}//bGrapheVidE

void GrapheVoir(char *sMessage,graf *pgG){
	//énumère les arcs de pgG sous la forme de couples (origine,destination),à raison de kuArcParLigne arcs par ligne
	const int kuArcParLigne=10;
	const int kuIndentation=1;
	int aK,sX,sY;
	Assert2("GrapheVoir",bGrapheAmorceR,sMessage!=0);
	//Appel0("GrapheVoir");
		GrapheTitreR(pgG,sMessage);
		if (pgG->nArcEnTout>0){
			for (printf("%s",sTab0()),sX=1;sX<=pgG->nSommetEnTout;sX++)
				for (aK=pgG->aHed[sX];sY=pgG->sSuk[aK],aK<pgG->aHed[sX+1];aK++){
					if (pgG->nSommetEnTout<kE2 && pgG->nArcEnTout<kE2)
						printf("  (%2s,%2s)",sEnt(sX),sEnt(sY));
					else printf("  (%3s,%3s)",sEnt(sX),sEnt(sY));
					if (aK % kuArcParLigne==0 && aK<pgG->nArcEnTout)
						printf("\n%s",(aK<pgG->nArcEnTout)? sTab(kuIndentation) : "");
				}
		} else printf(" Aucun arc");
		printf(".\n");
	//Appel1("GrapheVoir");
}//GrapheVoir

void GrapheVoir0(char *sMessage,graf *pgG,int nGenreDePoids){
	//affiche les arcs de pgG sous forme de triplets (origine,destination,pondérateurs) ——par exemple,GrapheVoir0(pgG,gpCout+gpPhi) affichera les champs nCout et nPhi.
	const int kuArcParLigne=10;
	int aK,nItemLgMax,uLabel,uPuissance,cPasse,sX,sY;
	char *sArc;//ùù
	//Appel0("GrapheVoir0");
		//d(nGenreDePoids);
		Assert4("GrapheVoir",bGrapheAmorceR,pgG!=NULL,sMessage!=0,bGrapheAttribuT(nGenreDePoids));
		printf("%s de densité %.2f à %s et %s par triplets (sommet,sommet",sMessage,fGrapheDensiteh(pgG,1,!k1Voir),sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel((pgG->nArcEnTout), "arc$ spécifié$"));
			for (uLabel=1,uPuissance=2*gpAlpha;uPuissance<=gpZeta;uPuissance=2*uPuissance,uLabel++)
				if (nGenreDePoids & uPuissance)
					printf("%s%s%s",(uPuissance<gpZeta)? ",":"",sItem(sGenreDePoidS,2*uLabel-1),sItem(sGenreDePoidS,2*uLabel-0));
		printf("):");
		if (pgG->nArcEnTout>0)
			for (nItemLgMax=cPasse=0;cPasse<=1;cPasse++)
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
						if (cPasse && aK%kuArcParLigne==1)
							printf("\n%s",sTab0());
						sArc=sC4("  (",sEnt(sX),",",sEnt(sY=pgG->sSuk[aK]));
						for (uLabel=1,uPuissance=2*gpAlpha;uPuissance<=gpZeta;uPuissance=2*uPuissance,uLabel+=2)
							if (nGenreDePoids & uPuissance){
								//d(pgG->nCout[aK]);
								sArc=sC3(sArc,sItem(sGenreDePoidS,uLabel),sPar3(iGraphePoids(pgG,nGenreDePoids & uPuissance,aK)));
							}
						nItemLgMax=iSup(nItemLgMax,nChaineLg(sArc));
						if (cPasse)
							printf("%s)%s",sArc,(aK<pgG->nArcEnTout)? sE(nItemLgMax-nChaineLg(sArc)) : "");
					}
		else printf(" CE GRAPHE NE CONTIENT À CET INSTANT AUCUN ARC");
		printf(".\n");
	//Appel1("GrapheVoir0");
}//GrapheVoir0

void GrapheVoir00(char *sMessage,graf *pgG,int nGenreDePoids){
	//comme GrapheVoir0, mais les numéros de sommets sont remplacés par des lettres (A pour 1, etc)
	Assert1("GrapheVoir00",bGrapheAttribuT(nGenreDePoids));
	ModeCaractere(+1);
		GrapheVoir0(sMessage,pgG,nGenreDePoids);
	ModeCaractere(-1);
}//GrapheVoir00

void GrapheVoir1(char *sMessage,graf *pgG,int bDontCouleur){
	//énumère les arcs de gG sous la forme de couples (origine,destination,couleur)
	const int kbLitteral=bModeCaractere();
	int aK,sX,sY;
	//Appel0("GrapheVoir1");
		Assert2("GrapheVoir",bGrapheAmorceR,sMessage!=0);
		//printf("%s%c(%s et %s):\n   ",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"));
		GrapheTitreR(pgG,sMessage);
		if (pgG->nArcEnTout>0){
			for (sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (aK=pgG->aHed[sX];sY=pgG->sSuk[aK],aK<pgG->aHed[sX+1];aK++){
					if (kbLitteral){
						//printf(" (%d,%d,%c)",sX,sY,cCouleur(pgG->coulh[aK]));
						if (bDontCouleur)
							printf(" (%c,%c,%c)",cLettre(sX),cLettre(sY),cCoul(pgG->coulh[aK]));
						else printf(" (%c,%c)",cLettre(sX),cLettre(sY));
					} else if (bDontCouleur)
						printf(" (%d,%d,%c)",sX,sY,cCoul(pgG->coulh[aK]));
					else printf(" (%c,%c)",cLettre(sX),cLettre(sY));
				}
				//printf("\n");
			}
		} else printf(" Aucun arc");
		bPrint(".");
	//Appel1("GrapheVoir1");
}//GrapheVoir1

void GrapheVoir10(char *sMessage,graf *pgG,int nGenreDePoids){
	//comme GrapheVoir1, mais les numéros de sommets sont remplacés par des lettres (A pour 1, etc)
	Assert1("GrapheVoir10",bGrapheAttribuT(nGenreDePoids));
	ModeCaractere(+1);
		GrapheVoir1(sMessage,pgG,nGenreDePoids);
	ModeCaractere(-1);
}//GrapheVoir10

void GrapheVoir11(char *sMessage,graf *pgG){
	//GrapheVoir10 dédié couleurs;les numéros de sommets sont remplacés par des lettres (A pour 1, etc) et les couleurs par l'initiale du nom de la couleur
	ModeCaractere(+1);
		GrapheVoir1(sMessage,pgG,gpCouleur);
	ModeCaractere(-1);
}//GrapheVoir11

void GrapheVoir2(char *sMessage,graf *pgG){
	//énumère les arcs de gG et de son graphe inverse sous la forme de couples (origine,destination)
	//Appel0("GrapheVoir2");
		Assert2("GrapheVoir2",bGrapheAmorceR,sMessage!=0);
		//printf("%s%c(%s et %s):\n",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"));
		GrapheTitreR(pgG,sMessage);
		printf(" direct:");
		if (pgG->nArcEnTout>0){
			for (int sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					printf("  (%s,%s",sEnt(sX),sEnt(pgG->sSuk[aK]));
				//printf("\n");
			}
		} else printf(" Aucun arc");
		printf(" inverse:");
		if (pgG->nArcEnTout>0){
			for (int sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (int aK=pgG->aDeh[sX];aK<pgG->aDeh[sX+1];aK++)
					printf("  (%s,%s",sEnt(sX),sEnt(pgG->sSuk[aK]));
				//printf("\n");
			}
		} else printf(" Aucun arc");
		bPrint(".");
	//Appel1("GrapheVoir2");
}//GrapheVoir2

void GrapheVoir3(char *sMessage,graf *pgG){
	//énumère les arcs de gG sous la forme de couples (origine,destination,capamin) puis (origine,destination,capamax) puis (origine,destination,cout)
	#define kbArc 1
	//Appel0("GrapheVoir3");
		Assert2("GrapheVoir3",bGrapheAmorceR,sMessage!=0);
		//GrapheVoir2(pgG,sMessage);
		printf("%s%c(%s et %s):   ",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"));
		printf("\n -capa min:");
		if (pgG->nArcEnTout>0){
			for (int sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					if (kbArc || sX<pgG->sSuk[aK])
						printf("  (%s,%s:%d)",sEnt(sX),sEnt(pgG->sSuk[aK]),pgG->nCapaMin[aK]);
				//printf("\n");
			}
		} else printf(" Aucun arc");
		printf(".\n -capa max:");
		if (pgG->nArcEnTout>0){
			for (int sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					if (kbArc || sX<pgG->sSuk[aK])
						printf("  (%s,%s:%3d)",sEnt(sX),sEnt(pgG->sSuk[aK]),pgG->nCapaMax[aK]);
				//printf("\n");
			}
		} else printf(" Aucun arc");
		printf(".\n -cout arc:");
		if (pgG->nArcEnTout>0){
			for (int sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (int aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					if (kbArc || sX<pgG->sSuk[aK])
						printf("  (%s,%s:%3d)",sEnt(sX),sEnt(pgG->sSuk[aK]),pgG->nCout[aK]);
				//printf("\n");
			}
		} else printf(" Aucun arc");
		bPrint(".");
	//Appel1("GrapheVoir3");
}//GrapheVoir3

void GrapheWoir(char *sMessage,graf *pgG){
	ModeCaractere(+1);
		GrapheVoir(sMessage,pgG);
	ModeCaractere(-1);
}//GrapheWoir

void GrapheWoir0(char *sMessage,graf *pgG,int nGenreDePoids){
	Assert1("GrapheWoir0",bGrapheAttribuT(nGenreDePoids));
	ModeCaractere(+1);
		GrapheVoir0(sMessage,pgG,nGenreDePoids);
	ModeCaractere(-1);
}//GrapheWoir0

void GrapheWoir00(char *sMessage,graf *pgG,int nGenreDePoids){
	Assert1("GrapheWoir00",bGrapheAttribuT(nGenreDePoids));
	ModeCaractere(+1);
		GrapheVoir00(sMessage,pgG,nGenreDePoids);
	ModeCaractere(-1);
}//GrapheWoir00

void GrapheWoir1(char *sMessage,graf *pgG,int bDontCouleur){
	ModeCaractere(+1);
		GrapheVoir00(sMessage,pgG,bDontCouleur);
	ModeCaractere(-1);
}//GrapheWoir1

void GrapheWoir10(char *sMessage,graf *pgG,int nGenreDePoids){
	Assert1("GrapheWoir10",bGrapheAttribuT(nGenreDePoids));
	ModeCaractere(+1);
		GrapheVoir10(sMessage,pgG,nGenreDePoids);
	ModeCaractere(-1);
}//GrapheWoir10

void GrapheWoir11(char *sMessage,graf *pgG){
	ModeCaractere(+1);
		GrapheVoir11(sMessage,pgG);
	ModeCaractere(-1);
}//GrapheWoir11

void GrapheWoir2(char *sMessage,graf *pgG){
	ModeCaractere(+1);
		GrapheVoir2(sMessage,pgG);
	ModeCaractere(-1);
}//GrapheWoir2

void GrapheWoir3(char *sMessage,graf *pgG){
	ModeCaractere(+1);
		GrapheVoir3(sMessage,pgG);
	ModeCaractere(-1);
}//GrapheWoir3


