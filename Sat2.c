#include "Kit.h"
#include "Graphe.h"
#include "Tds.h"
#include "Sat2.h"
int bSat2AmorceR;//ie le module a effectivement été amorcé
char cSaT;

char *sSat2SymbolE(char *sFormule,int uSomme,int cOperAd,int bCplmenter){
	//suppose 26 variables max
	char cCar=sItem(sFormule,uSomme)[2*cOperAd];
	if (bCplmenter)
		cCar=cCar-ySignePres(bMajuscule(cCar),'a'-'A');
	return(sC0(cCar));
}//sSat2SymbolE

char *sSat2SymbolE2(int inValeur,int bCplmenter){
	const int kbVariableAlphabetique=0;//"=1" suppose 26 variables max
	char *sCar;
	Assert1("sSat2SymbolE20",inValeur);
	if (kbVariableAlphabetique){
		Assert1("sSat2SymbolE21",abs(inValeur)<=26);//26 variables max
		if (!bCplmenter)
			sCar=sC0(cLettre( abs(inValeur)+26*(inValeur>0) ));
		else sCar=sC0(cLettre( abs(inValeur)+26*(inValeur<0) ));
	}else{
		if (bCplmenter==(inValeur<0))
			sCar=sC2("a",sEnt(abs(inValeur)) );
		else sCar=sC2("A",sEnt(abs(inValeur)) );
	}
	return(sCar);
}//sSat2SymbolE2

void Sat2AMORCER(){
	//amorce le présent module une fois pour toutes
	Assert1("Sat2AMORCER",!bSat2AmorceR);
	bSat2AmorceR=kV;
}//SimplexeAMORCER

int bSat2DecideR(graf *pgG,int sBarre[],int bVoir,int bInstance[]){
	//décide. Si vrai, rend ds bInstance[] un vecteur booléen de solutions à bInstance[0] éléments
	graf *pgK;
	int nSymboleEnTout=sBarre[0]=bInstance[0]=pgG->nSommetEnTout;
	int aK,sX,sY,bSatisfiable,nCFCenTout,nbVaut1,nb1;
	if (bVoir) GrapheVoir("Graphe d'implication pgG",pgG);
	Assert1("bSat2DecideR0",nSymboleEnTout==pgG->nSommetEnTout);//noté S ci-dessous
	if (bVoir) VecteurVoir1("sBarre",sBarre,1,nSymboleEnTout);
	//nCFCenTout=nGrapheComposanteFortementConnexe("",pgG);//O(SA)
	if (bVoir) d(nCFCenTout);
	//bSatisfiable:=chq CFC de pgG ctient une variable et sa négation 
		if (bVoir) VecteurVoir1("pgG->sPer",pgG->sPer,1,nSymboleEnTout);
		for (bSatisfiable=sX=1;sX<=nSymboleEnTout && bSatisfiable;sX++){//O(S)
			int cfcX=pgG->sPer[sX];
			int cfcXbarre=pgG->sPer[sBarre[sX]];
			//d4(sX,sBarre[sX],cfcX,cfcXbarre);
			bSatisfiable=bSatisfiable && cfcX!=cfcXbarre;
		}
	if (bSatisfiable){
			if (bVoir) GrapheVoir("Graphe original pgG",pgG);
		//pgK:=graphe de condensation
			GrapheCreer(-nCFCenTout,&pgK);
			//VecteurVoir0("sBarre",sBarre);
			for (sX=1;sX<=nSymboleEnTout;sX++)//O(S)
				for (aK=pgG->aHed[sX];sY=pgG->sSuk[aK],aK<pgG->aHed[sX+1];aK++)
					if ( pgG->sPer[sX]!=pgG->sPer[sY] )
						GrapheArquer1(pgK,pgG->sPer[sX],pgG->sPer[sY]);
			//VecteurVoir("pgG->sPer",pgG->sPer,1,pgG->nSommetEnTout);
			if (bVoir) GrapheVoir("Graphe de condensation pgK",pgK);
		//trier topologiqt les sommets de pgK, mm si pgK est vide
			bGrapheTrierTopologiquement(pgK,!k1Voir);//O(pgK.A);niveaux ds pgK->nVal[]
			if (bVoir) VecteurVoir("pgK->nVal",pgK->nVal,1,nCFCenTout);
		//empiler la valeur de chq variable, 0 ou 1, ds bInstance[]
			VecteurValuer(bInstance,1,nSymboleEnTout,-1);
			for (int uNiveauTopo=nCFCenTout;uNiveauTopo>0;uNiveauTopo--)//O(S*S*S);perfectB, mais négligB devant O(A2).
				for (int uCFC=1;uCFC<=nCFCenTout;uCFC++)//O(S*S);perfectB
					for (sX=1;sX<=nSymboleEnTout;sX++)//O(S)
						if (pgG->sPer[sX]==uCFC && pgK->nVal[uCFC]==uNiveauTopo && bInstance[sX]<0){
							bInstance[sX]=1;
							bInstance[sBarre[sX]]=0;
						}
		//afficher les noms des variables à 1, s'il y en a
			nbVaut1=yVecteurSomme(bInstance,1,nSymboleEnTout);
			if (bVoir && nbVaut1){
				for (printf("Cette formule est vraie si les variables suivantes valent 1: "),nb1=1,sX=1;sX<=nSymboleEnTout || bPrint("");sX++)
					if (bInstance[sX]){
						//printf("%c%s",cLettre(nSymbole[sX]),sEtc1(nb1++,nbVaut1));
						//bTdsPresent(cSaT,sC0(cCar=cCar-ySignePres(bMajuscule(cCar),'a'-'A')),&sX[cOperAd][1]);
						//d(sX);
						printf("%s%s",sTdsSymboleDepuisValeur(cSaT,sX),sEtc1(nb1++,nbVaut1));
						//printf("%4d: %s.\n",sX,sTdsSymboleDepuisValeur(cSaT,sX));
					}
			}else if (bVoir)
				printf("Cette formule est vraie si toutes les variables sont nulles.\n");
	}else if (bVoir) 
		printf("Cette formule n'a pas de solution.\n");
	return(bSatisfiable);
}//bSat2DecideR

int bSat2Decider(char *sFormule,int bVoir){
	//vrai ssi sFormule est satisfiable. sFormule,eg "a+B,A+b", est le produit de sommes binaires (a+B)(A+b) et "A" signifie "a barre". 1 lettre par variable.
	graf *pgG;
	int bDecider=0,cOperAd,nIndex,uSomme,uRang1,uRang2,sX[2][2];
	for (printf("Formule étudiée: "),uSomme=1;uSomme<=nItem(sFormule) || bPrint(".");uSomme++)
		printf("(%s)",sItem(sFormule,uSomme));
	//dérouter si sFormule n'est pas une formule valide pr SAT2
		for (uSomme=1;uSomme<=nItem(sFormule);uSomme++)
			Assert1("bSat2Decider",nChaineLg(sItem(sFormule,uSomme))==3);
		for (uSomme=1;uSomme<=nItem(sFormule);uSomme++){
			Assert1("bSat2Decider",sItem(sFormule,uSomme)[1]=='+');
			uRang1=nLettre(sItem(sFormule,uSomme)[0]);
			uRang2=nLettre(sItem(sFormule,uSomme)[2]);
			//d2(uRang1,uRang2);
			Assert2("bSat2Decider2",uRang1>0,uRang2>0);
		}
	bTdsAllouer(kV,&cSaT);
		//TDS:=chq symbole rcontré ds sFormule + le symbole cplémentR sachant que "A" signifie "a barre"
			for (nIndex=uSomme=1;uSomme<=nItem(sFormule);uSomme++)
				for (cOperAd=0;cOperAd<=1;cOperAd++){
					nIndex+=bTdsAjouterValuer(cSaT,sSat2SymbolE(sFormule,uSomme,cOperAd,0),nIndex);
					nIndex+=bTdsAjouterValuer(cSaT,sSat2SymbolE(sFormule,uSomme,cOperAd,1),nIndex);
				}
//bVoir=0;
		if (bVoir) TdsVoir(cSaT,"cSaT");
		int nSymboleEnTout=nTdsItem(cSaT);
		int sBarre[1+nSymboleEnTout];
		GrapheCreer(-nSymboleEnTout,&pgG);
			//pgG:=graphe d'implication associé aux sommes binaires non redondantes
				for (nIndex=uSomme=1;uSomme<=nItem(sFormule);uSomme++){
					for (cOperAd=0;cOperAd<=1;cOperAd++){
						bTdsPresent(cSaT,sSat2SymbolE(sFormule,uSomme,cOperAd,0),&sX[cOperAd][0]);
						bTdsPresent(cSaT,sSat2SymbolE(sFormule,uSomme,cOperAd,1),&sX[cOperAd][1]);
						sBarre[sX[cOperAd][0]]=sX[cOperAd][1];
						sBarre[sX[cOperAd][1]]=sX[cOperAd][0];
					}
					GrapheArquer1(pgG,sX[0][1],sX[1][0]);
					GrapheArquer1(pgG,sX[1][1],sX[0][0]);
				}
			//pgG->nPoids[0]=sBarre[0]=nSymboleEnTout;
			bDecider=bSat2DecideR(pgG,sBarre,bVoir,pgG->nPoids);
		GrapheCreer(0,&pgG);
	bTdsAllouer(kF,&cSaT);
	return(bDecider);
}//bSat2Decider

int bSat2Decider1(int inFormule[],int bVoir,int iInstance[]){
	//vrai ssi inFormule[] décrit une formule F satisfiable. Chq terme F(i) est la somme des opérandes iGauche[i] et iDroite[i].
	//tte valeur >0/<0 ds iGauche[] ou iDroite[] désigne une variable directe/cplémentée. Toute valeur nulle est ignorée.
	int bDecider1=0,nIndex,uOperande,sX[2][2],cOperAd,iValeur;
	char *sInstance;
	graf *pgG;
	Assert11("bSat2Decider1,inFormule[0]",inFormule[0]>0 && bPair(inFormule[0]),inFormule[0]);
	//if (bVoir) VecteurVoir5("iGauche,iDroite",iGauche,iDroite,1,iGauche[0]);
	if (0 && bVoir) printf("%s.\n",sPluriel(inFormule[0]/2,"sommes"));
	bTdsAllouer(kV,&cSaT);
		//TDS:=chq symbole rcontré ds (iGauche,iDroite) + le symbole complémentR associé
			for (nIndex=uOperande=1;uOperande<=inFormule[0];uOperande+=2)
				for (cOperAd=0;iValeur=(cOperAd==0)? inFormule[uOperande+0] : inFormule[uOperande+1],cOperAd<=1;cOperAd++)
					if (iValeur) {//iValeur=1 désigne la variable A, -1 désigne la variable cplémentR a.
						nIndex+=bTdsAjouterValuer(cSaT,sSat2SymbolE2(iValeur,0),nIndex);
						nIndex+=bTdsAjouterValuer(cSaT,sSat2SymbolE2(iValeur,1),nIndex);
					}
			if (0 && bVoir) TdsVoir(cSaT,"cSaT");
		int nSymboleEnTout=nIndex-1;
		Assert1("bSat2Decider1568",bPair(nSymboleEnTout));//?
		if (bVoir) printf("%s en tout, ie sous forme directe et sous forme complémentaire.\n",sPluriel(nSymboleEnTout,"variable$"));
		int sBarre[1+nSymboleEnTout];//associe au rg1 de chaq variable (directe ou cplémentR) le rg1 de la variable cplémentR.
		GrapheCreer(-nSymboleEnTout,&pgG);
			//pgG:=graphe d'implication associé aux sommes binaires non redondantes
				for (nIndex=uOperande=1;uOperande<=inFormule[0];uOperande+=2){
					for (cOperAd=0;iValeur=(cOperAd==0)? inFormule[uOperande+0] : inFormule[uOperande+1],cOperAd<=1;cOperAd++)
						if (iValeur){
							bTdsPresent(cSaT,sSat2SymbolE2(iValeur,0),&sX[cOperAd][0]);
							bTdsPresent(cSaT,sSat2SymbolE2(iValeur,1),&sX[cOperAd][1]) ;
							sBarre[sX[cOperAd][0]]=sX[cOperAd][1];
							sBarre[sX[cOperAd][1]]=sX[cOperAd][0];
						}
					if (iValeur){
						GrapheArquer1(pgG,sX[0][1],sX[1][0]);
						GrapheArquer1(pgG,sX[1][1],sX[0][0]);
					}
				}
			//iInstance[0]=sBarre[0]=nSymboleEnTout;
			Assert1("bSat2Decider145",pgG->nSommetEnTout==nSymboleEnTout);
			bDecider1=bSat2DecideR(pgG,sBarre,bVoir,iInstance);
			//VecteurVoir1("nInstance0",nInstance,1,nInstance[0]);
			for (int nVar=1;nVar<=iInstance[0];nVar++)
				if (iInstance[nVar]){
					sInstance=sTdsSymboleDepuisValeur(cSaT,nVar);
					iInstance[nVar]=ySignePres(bMajuscule(sInstance[0]),yEntier(sChainon1(sInstance,1)) );
				}
			//VecteurVoir1("nInstance1",nInstance,1,nInstance[0]);
		GrapheCreer(0,&pgG);
	bTdsAllouer(kF,&cSaT);
	return(bDecider1);
}//bSat2Decider1

int bSat2Decider2(int inGauche[],int inDroite[],int bVoir,int iInstance[]){
	//vrai ssi (inGauche[],inDroite[]) décrit une formule F satisfiable. Chq terme F(i) est la somme des opérandes iGauche[i] et iDroite[i].
	int uE,nF,inFormule[1+2*inGauche[0]];
	for (nF=0,uE=1;uE<=inGauche[0];uE++){
		inFormule[++nF]=inGauche[uE];
		inFormule[++nF]=inDroite[uE];
	}
	inFormule[0]=nF;
	int bDecider2=bSat2Decider1(inFormule,bVoir,iInstance);
	return(bDecider2);
}//bSat2Decider2

void Sat2TESTER(int iTest){
	//teste le présent module
	int bVoir=0;
	int nGauche[]={11, 1, 1, 2, 2, 3, 1, 2, 3, 4, 5, 6};
	int nDroite[]={11, 3,-4,-4,-5,-5,-6,-6,-6, 7, 7, 7};
	int nInstance[100];
	Assert1("Sat2TESTER",bSat2AmorceR);
	iTest=7;
	Appel0(sC2("Sat2TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case 0:	bSat2Decider("a+a,A+A",bVoir);
					break;
			case 1:	bSat2Decider("a+B,c+d",bVoir);
					break;
			case 2:	bSat2Decider("a+B,A+b",bVoir);
					break;
			case 3:	bSat2Decider("A+A,A+A",bVoir);
					break;
			case 4:	bSat2Decider("A+A",bVoir);
					break;
			case 5:	bSat2Decider("a+a,a+B,c+d,A+A",bVoir);
					break;
			case 6:	bSat2Decider("a+c,a+D,b+D,b+E,c+E,a+F,b+F,c+F,d+g,e+g,f+g",bVoir=1);
					break;
			case 7:	bSat2Decider2(nGauche,nDroite,bVoir,nInstance);
					break;
			default:
				Assert1("Sat2TESTER",0);
				break;
		}
	Appel1(sC2("Sat2TESTER,test n°",sEnt(iTest)));
}//Sat2TESTER	

