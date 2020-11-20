#include "Kit.h"
#include "Deque.h"
#include "Grhom.h"
#include "Grammaire.h"
//Grhom=GRammaire HOMogène. Scrute une grammaire homogène puis teste cette grammaire sur-le-champ ou génère son code équivalent en langage C.
//une grammaire est homogène ssi elle a les caractéristiques suivantes:
//  1° c'est une grammaire algébrique (une règle commence par S) dont les règles sont séparées par le symbole ";".
//  2° les non terminaux sont des majuscules dans [A..Z], et les terminaux des minuscules dans [a..z].
//  3° le symbole entre le membre gauche et le membre droit de chaque règle est le digramme insécable "->".
//	4° elle ne renferme que des règles homogènes, contenant uniqt des opérateurs ".", ou uniqt des opérateurs "+", ou aucun opérateur (règle terminale).
//	5° les opérandes entre les opérateurs "." ou "+" sont des majuscules.
//	6° les membres gauche et droit d'une règle terminale sont toujours de la forme F->f, ie le membre droit est le membre gauche écrit en minuscule.
//	7° les 2 règles A->a et B->b sont toujours présentes.
//	8° la récursivité à gauche est absente ——qu'elle soit directe ou indirecte (dans "P->Q.R;Q->S+P", P appelle P, c'est une récursivité indirecte).
//  9° dans une règle OU, eg T->P+Q, aucun mot engendré par P n'est un facteur gauche strict d'un mot engendré par Q (sinon, envisager "T->Q+P").
// NB: Pour obtenir aisément une grammaire homogène, donc sans mot vide, remplacer les expressions (E)* par (1+(E+)) et développer.
#define kuAttributEnTouT 10
#define kuAttributMaximaL (kuAttributEnTouT+kuAttributEnTouT) //nom de l'attribut puis sa valeur puis nom de l'attribut puis sa valeur… 
#define kuCaractereMaX kE2
#define k1FichieR kV
#define k1HomogenE kV
#define kuLettreMaX 26
#define kuRegleMaX kuLettreMaX
#define kuTermeMaX kE1
#define kuReglE (kuTermeMaX+1)
#define kuTypE (kuTermeMaX+2)
#define kuSymbolE (kuTermeMaX+3) //non terminal de la règle courante
FILE *fGramR;//nom du fichier (suffixe .c vital) destiné à recevoir le code généré qui explicite la grammaire homogène.
//char *skFICHIER="Grammaire.c";//reçoit le code C qui explicite la grammaire homogène compilée par bGrhomCompiler() 
//char *skFICHIER="";//reçoit le code C qui explicite la grammaire homogène compilée par bGrhomCompiler() 
char *skFICHIER="Code.c";
int bGrhomAmorceR;
int bGrhomCompileR;
enum eRegleTypE {rtAlphA,rtTerminalE,rtET,rtOU,rtOmegA};
const char kcSeparateuR=';';
int nPilE[1+kuRegleMaX][1+kuSymbolE];//chaque ligne décrit une règle de la grammaire homogène. Les lignes créées sont empilées donc consécutives. 
int nTablE[1+kuLettreMaX][1+kuSymbolE];//comme nPilE,mais la ligne dédiée à un non terminal est son rang ds l'alphabet: B est ligne 2, S ligne 19.
char *sTablE[1+kuLettreMaX];//liste des noms d'attributs
point ptTablE[1+kuLettreMaX];//liste des noms d'attributs
int bTablE[1+kuLettreMaX];//vrai ssi le pt de génération est basculant
char *sGrhoM;

int bAffectationAnnoncE(const char *ksTexte,int nDebut,int nFin);
int nAttributEnTouT(int uRegle,int nTerme);
int iAttributEvaluE(int uRegle,int nCar,int nAttribut[]);
int iAttributEvalueR(int uRegle,int nDebut,int nFin,int nAttribut[],int bVoir);
int bAttributExprimeR(int uRegle,int nAttribut[]);
int nAttributFranchiR(const char *ksGrhom,int nFin,char cAttribut[],int *pnDebut);
int uAttributIndeX(int uRegle,char cNom);
char cAttributNoM(int uRegle,int nTerme,int uRang,int bVoir);
int mAttributPlacE(int uRegle,char cNom);
void AttributTabuleR(char cNom,char cAttribut[]);
int bAttributVerifieR(int nRegleEnTout);
void AttributVoiR(char *sQuoi,char cAttribut[]);
void AttributWoiR(char *sQuoi,int nAttribut[]);
void EcriS(char *szQuoi);
void EcriS0(int bFichier,char *szQuoi);
void EcriS1(int bFichier,char *szQuoi);
void EcriS3(char *sA,char *sB,char *sC);
void EcriS7(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
void EnteteGenereR(const char *ksGrAlgebrique,const char *ksGrHomogene,int nRegleRang[],int nRegleEnTout[2],char *sFichierCible);
void GrhomAfficheR(int bFichier,const char *ksGrAlgebrique,const char *ksGrHomogene,int nRegleEnTout[2]);
int bGrhomDecideR(int uRegle,char *sMot,int iDebut,int *piFin,int nAttribut[],int bVoir,int *pnAppelEnTout);
void GrhomExpliciteR(const char *ksGrAlgebrique,const char *ksGrohm,int nRegleEnTout[2],char *szFichierCible);
int bGrhomHomogenE(const char *ksGrohm,int nSeparateur[]);
int bGrhomPlausiblE(const char *ksGrohm,int nRegleEnTout);
void GrhomTabuleR(const char *ksGrohm,int nRegleEnTout,int bVoir);
char *scPilE(int nRegle,int nTerme);
int bRecursivitehGauchE(int uRegle);
void RecursivitehGaucheVoiR(char *sMessage,int uDito);
int bRegleDenonceR(int nRegle,const char *ksGrhom,int nDebut,int nFin);
int bRegleET(int nRegle,const char *ksGrhom,int nDebut,int nFin);
void RegleEtGenereR(int nRegle);
int bRegleOU(int nRegle,const char *ksGrhom,int nDebut,int nFin);
void RegleOuGenereR(int nRegle);
int bRegleTerminalE(int nRegle,const char *ksGrhom,int nDebut,int nFin,int *pnA,int *pnB);
void RegleTerminaleGenereR(int nRegle);
void TexteCompacteR(const char *ksNonCompact,char sCompact[1+kuCaractereMaX]);

int bAffectationAnnoncE(const char *ksTexte,int nDebut,int nFin){
	int bAnnonce=bMinuscule(ksTexte[nDebut]) && ksTexte[nDebut+1]=='=' && ksTexte[nDebut+2]!='=' && nDebut+2<=nFin;
	return(bAnnonce);
}//bAffectationAnnoncE

void AttributDispatcheR(int bEt,int uRegle0,int nAttribut0[],int uRegle1,int nTerme1,int nAttribut1[],int bVoir){
	//recopie, à une permutation près, les valeurs de nAttribut0[] fournies par nRegle0 ds le tableau nAttribut1[] de la nRegle1.
	int nAttributEnTout,mIndex1,uRang,iValeur1;
	//int bVoir=!bEt;
	char cNom1;
	//if (bVoir) AttributWoiR("AttributDispatcheR,rtOU:nAttribut1",nAttribut1);
	if (0 && bVoir) Appel0("AttributDispatcheR");
		if (bVoir) AttributWoiR("AttributDispatcheR:nAttribut1 AVANT",nAttribut1);
		//if (bVoir) AttributWoiR("AttributDispatcheR:nAttribut0",nAttribut0);
		//if (bVoir) {d3(uRegle0,uRegle1,uTerme1);m8;d(nAttributEnTouT(uRegle1,uTerme1));m9};
		nAttributEnTout=nAttributEnTouT(uRegle1,nTerme1);
		if (bVoir) d(nAttributEnTout);
		for (uRang=1;uRang<=nAttributEnTout;uRang++){
			if (bVoir) d3(uRegle1,nTerme1,uRang);
			cNom1=cAttributNoM(uRegle1,nTerme1,uRang,bVoir);
			iValeur1=nAttribut0[uRang+1];
			mIndex1=uAttributIndeX(uRegle1,cNom1);
			if (bVoir) cd2(cNom1,iValeur1,mIndex1);
			if (mIndex1>0){
				//if (bEt) {c(cNom1);dd(mIndex1,uRang);};
				nAttribut1[2*mIndex1-1]=cNom1;
				nAttribut1[2*mIndex1]=iValeur1;
			}
		}
		if (bVoir) AttributWoiR("AttributDispatcheR:nAttribut1 APRÈS",nAttribut1);
	if (0 && bVoir) Appel1("AttributDispatcheR");
}//AttributDispatcheR

void AttributAffecteR(int uRegle,int nDebut,int iValeur,int nAttribut[],int bVoir){
	int nRang=mAttributPlacE(uRegle,sGrhoM[nDebut]);
	nAttribut[2*nRang-1]=sGrhoM[nDebut];
	nAttribut[2*nRang]=iValeur;
	//AttributWoiR("AttributAffecteR APRÈS",nAttribut);
}//AttributAffecteR

int nAttributEnTouT(int uRegle,int nTerme){
	//rend le nom du paramètre uRang du terme nTerme de la règle uRegle
	char nEnTout;
	//s(sTablE[uRegle]);
	char *sListe=sItem(sTablE[uRegle],1+nTerme);
	//s(sListe);
	nEnTout=nChaineLg(sListe);
	//d(nEnTout);
	return(nEnTout);
}//nAttributEnTouT

int iAttributEvaluE(int uRegle,int nCar,int nAttribut[]){
	//rend la valeur numérique de (sGrhoM[nCar]) si c'est une variable, ou celle de sGrhoM[nCar] sinon.
	int iValeur=sGrhoM[nCar];
	Assert1("iAttributEvaluE",bMinuscule(iValeur) || bDecit(iValeur));
	if (bMinuscule(iValeur)){//contenant
		int nRang=mAttributPlacE(uRegle,iValeur);
		iValeur=nAttribut[2*nRang];//contenant
	}else iValeur=iValeur-'0';//contenu
	return(iValeur);
}//iAttributEvaluE

int iAttributEvalueR(int uRegle,int nDebut,int nFin,int nAttribut[],int bVoir){
	const char *ksOperateur="<=,>=,==,!=,+,-,*,/,<,>,%";//digrammes en tête pr avoir une chance d'être trouvés
	int nC,bDigramme,iDroit,iEvaluer,nItemRg;
	iEvaluer=iAttributEvaluE(uRegle,nDebut,nAttribut);
	for (nC=nDebut+1;nItemRg=nItemRang(sC0(sGrhoM[nC]),ksOperateur),nC<nFin;nC+=2){
		if (nItemRg>0){
			nC+=bDigramme=nItemRg<=4;//afin que nC+1 indexe le début du membre droit
			iDroit=iAttributEvaluE(uRegle,nC+1,nAttribut);
			switch(nItemRg){
				case  1: iEvaluer=iEvaluer<=iDroit;break;
				case  2: iEvaluer=iEvaluer>=iDroit;break;
				case  3: iEvaluer=iEvaluer==iDroit;break;
				case  4: iEvaluer=iEvaluer!=iDroit;break;

				case  5: iEvaluer=iEvaluer+iDroit;break;
				case  6: iEvaluer=iEvaluer-iDroit;break;
				case  7: iEvaluer=iEvaluer*iDroit;break;
				case  8: Assert1("iAttributEvalueR div0",iDroit);iEvaluer=iEvaluer/iDroit;break;
				case  9: iEvaluer=iEvaluer<iDroit;break;
				case 10: iEvaluer=iEvaluer>iDroit;break;
				case 11: Assert1("iAttributEvalueR pourcent",iDroit);iEvaluer=iEvaluer%iDroit;break;
				default:Assert1("iAttributEvalueR default",0);break;
			}
		}
	}
	return(iEvaluer);
}//iAttributEvalueR

int bAttributExprimeR(int uRegle,int nAttribut[]){
	int bVoir=0;
	int bExprimer=0,bAffectation,bComparaison,nC,nDebut,nFin,mFin,iValeur;
	bAffectation=bComparaison=0;
	bExprimer=1;
	for (nC=ptTablE[uRegle].h+1;nC<=ptTablE[uRegle].v;nC++){
		//(nDebut,nFin) délimite une expression
			nDebut=nC;nFin=ptTablE[uRegle].v;
			mFin=mChainePos(',',sChainon(sGrhoM,nDebut,nFin));
			if (mFin<0)
				mFin=mChainePos(')',sChainon(sGrhoM,nDebut,nFin));
			if (mFin>0)
				nFin=nDebut+mFin;
			bAffectation=bAffectationAnnoncE(sGrhoM,nDebut,nFin);
			iValeur=iAttributEvalueR(uRegle,nDebut+2*bAffectation,nFin,nAttribut,bVoir);//saute l'opérateur "=" si bAffectation
			if (bAffectation)
				AttributAffecteR(uRegle,nDebut,iValeur,nAttribut,bVoir);
			else bExprimer=!iValeur;//résultat booléen d'une comparaison
			nC=nFin;
	};
	return(bExprimer);
}//bAttributExprimeR

int bAttributFranchiR(const char *ksGrhom,int nButoir,char cAttribut[],int *pnDebut,int *pnParametreLg){
	//cAttribut:=pile prolongée des variables d'attributs depuis ksGrhom[*pnDebut]=='(' jsq la parenthèse fermante associée
	int bAffectation=1,nC,nD,nDebut,nFin,mFin,nParametreLg;
	//dds(*pnDebut,nButoir,sChainon(ksGrhom,*pnDebut,nButoir));
	Assert1("bAttributFranchiR",ksGrhom[*pnDebut]=='(');
	int mDroite=mChainePos(')',sChainon(ksGrhom,*pnDebut,nButoir));
	if (mDroite>0){
		for (nC=*pnDebut+1;nC<=*pnDebut+mDroite;nC++){
			//(nDebut,nFin) délimite une expression
				nDebut=nC;nFin=nDebut+mDroite;
				mFin=mChainePos(',',sChainon(ksGrhom,nDebut,nFin));
				if (mFin<0)
					mFin=mChainePos(')',sChainon(ksGrhom,nDebut,nFin));
				if (mFin>0)
					nFin=nDebut+mFin;
				//d2(nDebut,nFin);c(ksGrhom[nDebut]);
				//dds(nDebut,nFin,sG(sChainon(ksGrhom,nDebut,nFin)));cc(ksGrhom[nDebut],ksGrhom[nDebut+1]);
			bAffectation=bAffectationAnnoncE(ksGrhom,nDebut,nFin);
			//d3(bAffectation,nDebut,nFin);
			for (nD=nDebut;nD<=nFin;nD++)
				if (bMinuscule(ksGrhom[nD]))
					cAttribut[++cAttribut[0]]=ksGrhom[nD];
			nC=nFin;
		};
		nParametreLg=nFin-*pnDebut;
		*pnDebut=nFin+1;
	}else nParametreLg=0;
	*pnParametreLg=nParametreLg;
	return(bAffectation);
}//bAttributFranchiR

int nAttributFranchiR(const char *ksGrhom,int nFin,char cAttribut[],int *pnDebut){
	//franchit une suite de variables séparées par des virgules et rend le nb de caractères franchis
	int bButoir,nC,bMinus,bVirgule=1;
	nC=*pnDebut;
	do{
		nC++;
		bMinus=bMinuscule(ksGrhom[nC]);
		if (bMinus)
			cAttribut[++cAttribut[0]]=ksGrhom[nC];
		bVirgule=1-bVirgule;
		bButoir=bDans2(ksGrhom[nC],')',';');
	}while (!bButoir && nC<=nFin && ( (bVirgule)? ksGrhom[nC]==',' : bMinus ) );
	*pnDebut=nC;///pointe sur ')'
	int nFranchi=bButoir*(nC-*pnDebut);
	return(nFranchi);
}//nAttributFranchiR

int uAttributIndeX(int uRegle,char cNom){
	//rend le rang1 de cNom ds la règle uRegle, ou 0 si échec
	char *sListe=sTablE[uRegle];
	int nC,uIndex,nPile[1+26];
	//nPile:=liste de rang1s de tous les attributs cités ds uRegle
		for (nPile[0]=nC=0;nC<nChaineLg(sListe);nC++)
			if (bMinuscule(sListe[nC])){
				uIndex=sListe[nC]-'a'+1;
				Assert1("uAttributIndex",bCroit(1,uIndex,26));
				if ( !bVecteurContient(uIndex,nPile) )
					nPile[++nPile[0]]=uIndex;
			}
	uIndex=mVecteurContient(cNom-'a'+1,nPile,1,nPile[0]);
	return(uIndex);
}//uAttributIndeX

void AttributInitialiseR(int uRegle,int nAttribut[]){
	int mPlace;
	VecteurRaz(nAttribut,1+kuAttributMaximaL);
	for (int uMinuscule=1;uMinuscule<=26;uMinuscule++){
		char cNom=uMinuscule+'a'-1;
		mPlace=mAttributPlacE(uRegle,cNom);
		if (mPlace>0)
			nAttribut[2*mPlace-1]=cNom;
	}
	//AttributWoiR("nAttribut00",nAttribut);
}//AttributInitialiseR

char cAttributNoM(int uRegle,int nTerme,int uRang,int bVoir){
	//rend le nom du paramètre uRang du terme nTerme de la règle uRegle
	char cNom='@';
	if (bVoir) sd2(sTablE[uRegle],nTerme,uRang);
	char *sListe=sItem(sTablE[uRegle],1+nTerme);//pr être en rang 1
	if (bVoir) sd2(sListe,uRang,nChaineLg(sListe));
	if ( bCroit(1,uRang,nChaineLg(sListe)) )
		cNom=sListe[uRang-1];//accès en rang0
	if (bVoir) c(cNom);
	return(cNom);
}//cAttributNoM

int mAttributPlacE(int uRegle,char cNom){
	//rend le rang1 de cNom ds le terme nTerme de la règle uRegle, ou -1 si échec
	int nC,nLg,nRang,nPlace[1+26];
	Assert1("mAttributPlacE",bMinuscule(cNom));
	VecteurRazer(nPlace,1,26);
	char *sListe=sTablE[uRegle];
	//s(sListe);c(sListe[0]);
	for (nRang=nC=0,nLg=nChaineLg(sListe);nC<nLg;nC++)
		if ( bMinuscule(sListe[nC]) && nPlace[sListe[nC]-'a'+1]==0 )
			nPlace[sListe[nC]-'a'+1]=++nRang;
	//VecteurVoir("nPlace",nPlace,1,26);		
	//d2(uRegle,nTerme);s(sTablE[uRegle]);c(cNom);
	int mPlace=nPlace[cNom-'a'+1];
	//d(mPlace);
	return(mPlace);
}//mAttributPlacE

void AttributTabuleR(char cNom,char cAttribut[]){
	//donnée cAttribut:suite de $ avec après chaq $ la liste de variables éventuelle, eg : $ y $ $ zyz
	//résultat: sTablE[cNom-'A'+1]:=liste d'items qui décrivent les noms des attributs
	int nC,uT,nRegle=cNom-'A'+1;
	//cd(cNom,cAttribut[0]);d(nRegle);
	//AttributVoiR("AttributTabuleR",cAttribut);
	//if (nRegle==1) d2(nRegle,nRegle);
	sTablE[nRegle]=malloc(100);
	sTablE[nRegle][0]='\0';
	for (nC=0,uT=1;uT<=cAttribut[0];uT++)
		if (bMinuscule(cAttribut[uT]))
			sTablE[nRegle][nC++]=cAttribut[uT];
		else if ( bCroit(2,uT,cAttribut[0]) )
			sTablE[nRegle][nC++]=',';
	sTablE[nRegle][nC]='\0';
	if (0 && cNom=='A'){
		ds(nRegle,sTablE[nRegle]);
		c(cAttributNoM(1,1,1,!k1Voir));
		c(cAttributNoM(1,2,1,!k1Voir));
		c(cAttributNoM(1,3,1,!k1Voir));
		d(nAttributEnTouT(1,0));
		d(nAttributEnTouT(1,1));
		d(nAttributEnTouT(1,2));
	}
	//if (nRegle==1) s(sTablE[nRegle]);
}//AttributTabuleR

int bAttributValideR(int uRegle,int nParametre){
	int nC,nD,bDroit,nT,uR,nParam,bValide;
	int cSymbole=nPilE[nTablE[uRegle][kuReglE]][kuSymbolE];
	char cNom;
	//c(cSymbole);//s(sGrhoM);
	for (bValide=1,uR=0,bDroit=nC=nT=0;nC<=nChaineLg(sGrhoM);nC++){
		if ( !bDroit && bMajuscule(sGrhoM[nC]) ){
			cNom=sGrhoM[nC];
			//c(cNom);
		}
		if ( bFleche(sGrhoM,nC-1) )
			bDroit=1;
		if ( sGrhoM[nC]==';' )
			bDroit=0;
		//bc(bDroit,sGrhoM[nC]);
		if (bDroit && sGrhoM[nC]==cSymbole ){
			//cc(sGrhoM[nC],sGrhoM[nC+1]);
			if (sGrhoM[nC+1]=='('){
				for (nD=nC+2;sGrhoM[nD]!=')';nD++);
				nParam=(nD-nC)/2;
			}else nParam=0;
			//d2(nParametre,nParam);
			bValide=nParametre==nParam;
			if (!bValide){
				printf("%sErreur: %c, dans la règle %c, %s",sTab0(),cSymbole,cNom,sPluriel2("a",nParam,"paramètre"));
				printf(" alors que la règle %c est déclarée avec %s.\n",cSymbole,sPluriel(nParametre,"paramètre"));
			}
		}
	}
	return(bValide);
}//bAttributValideR

int bAttributVerifieR(int nRegleEnTout){
	//vérifie que tout non terminal en membre droit a le mm nbre de paramètres que sa déclarO en membre gauche
	int nParam,uR,bValide,nTermat;
	Tabuler(+1);
		for (bValide=uR=1;uR<=kuRegleMaX;uR++)
			if (sTablE[uR]!=NULL)
				if (!bAttributValideR(uR,nParam=nChaineLg(sItem(sTablE[uR],1))))
					bValide=0;
		if (bValide)
			for (uR=1;uR<=kuRegleMaX;uR++)
				if (sTablE[uR]!=NULL){//&& nTablE[uR][kuTypE]==rtET
					nTermat=nItem(sTablE[uR]);
					int bGenere=nPilE[nTablE[uR][kuReglE]][nTermat-1]=='@';
					//s(sChainon(sTablE[uR]));
					if (nTablE[uR][kuTypE]==rtET){//les variables en membre droit hors bGenere doivent être distinctes
						//sTablo:=règle amputée de bGenere
							int mVirgule=mChainePosition(sTablE[uR],',');
							char *sTablo=(bGenere) ? sChainon(sTablE[uR],0,mVirgule-1) : sTablE[uR];
						//sTablo:=sTablo \ variables éventuelles du membre gauche
							if (sTablE[uR][0]!=',')
								sTablo=sChainon(sTablo,1+mChainePos(',',sTablE[uR]),kE4);
						//les variable résiduelles doivent être distinctes;sinon,bValide:=0.
							char *sCopie=sChaineSubstituer(sTablo,",","");
							if (!bChaineDistincte(sCopie)){
								int cSymbole=nPilE[nTablE[uR][kuReglE]][kuSymbolE];
								printf("%sErreur: des variables distinctes sont attendues dans les règles en membre droit de la règle %c.\n",sTab0(),cSymbole);
								bValide=0;
							}
					}
				}
	Tabuler(-1);
	return(bValide);
}//bAttributVerifieR

void AttributVoiR(char *sQuoi,char cAttribut[]){
	int uT;
	for (printf("%s%s=",sQuoi,sDomaine(1,cAttribut[0])),uT=1;uT<=cAttribut[0] || bPrint("");uT++)
		printf("%c ",cAttribut[uT]);
}//AttributVoiR

void AttributWoiR(char *sQuoi,int nAttribut[]){
	//afffiche les doublets (nom de l'attribut,valeur de l'attribut) décrits ds nAttribut (1 case pr le nom, 1 pr la valeur)
	int uT;
	for (printf("%s%s >> ",sQuoi,sDomaine(1,nAttribut[0])),uT=1;uT<=nAttribut[0] || bPrint("");uT+=2)
		printf("%c=%d%s",nAttribut[uT],nAttribut[uT+1],(uT+1<nAttribut[0])? ",":".");
	//VecteurVoir("AttributWoiR",nAttribut,1,nAttribut[0]);
}//AttributWoiR

void EcriS(char *szQuoi){
	//printf("%s",szQuoi);
	fprintf(fGramR,"%s",szQuoi);
}//EcriS

void EcriS0(int bFichier,char *szQuoi){
	//comme EcriS1,mais avec un blanc final en moins
	if (bFichier)
		fprintf(fGramR,"%s",szQuoi);
	else printf("%s",szQuoi);
}//EcriS0

void EcriS1(int bFichier,char *szQuoi){
	//comme EcriS0,mais avec un blanc final en plus
	if (bFichier)
		fprintf(fGramR,"%s ",szQuoi);
	else printf("%s ",szQuoi);
}//EcriS1

void EcriS3(char *sA,char *sB,char *sC){
	EcriS(sC3(sA,sB,sC));
}//EcriS3

void EcriS7(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	EcriS(sC7(sA,sB,sC,sD,sE,sF,sG));
}//EcriS7

void EnteteGenereR(const char *ksGrAlgebrique,const char *ksGrHomogene,int nRegleRang[],int nRegleEnTout[],char *sFichierCible){
	//génère includes,variables de module,protos des règles (ds l'ordre nRegleRang[]),leur code et celui de sFichierCibleAMORCER,INITIALISER,TESTER.
	int uR;
	int mPoint=mChainePos('.',sFichierCible);
	int nFichierLg=strlen(sFichierCible);
	char *sRacine=malloc(1+nFichierLg);
		strcpy(sRacine,sFichierCible);
		Assert3("EnteteGenereR",mPoint>0,sFichierCible[mPoint+1]=='c',mPoint+2==nFichierLg);
		sRacine[mPoint]='\0';
		//générer les includes
			EcriS("#include \"Kit.h\"\n");
			EcriS3("#include \"",sRacine,".h\"\n");
		//générer les variables de module
			EcriS("char *sMOT;\n");
			EcriS3("int b",sRacine,"AmorceR=kF;\n");
		//générer en commentaire les règles des deux grammaires
			GrhomAfficheR(k1FichieR,ksGrAlgebrique,ksGrHomogene,nRegleEnTout);
		//générer tous les prototypes associés aux règles ——à 1 règle T on associe bijectivement 1 routine bT().
			for (uR=1;uR<=nRegleEnTout[1];uR++)
				EcriS(sC3("int b",scPilE(nRegleRang[uR],kuSymbolE),"(int iDebut,int *piFin);\n"));
			EcriS("\n");
		//générer le code de la routine sFichierCibleAMORCER.
			EcriS3("void ",sRacine,"AMORCER(){\n");
				EcriS3("    b",sRacine,"AmorceR=kV;\n");
			EcriS3("}//",sRacine,"AMORCER\n\n");
		//générer le code de la routine sFichierCibleINITIALISER.
			EcriS3("void ",sRacine,"INITIALISER(){\n");
				EcriS7("    Assert1(\"",sRacine,"INITIALISER\",b",sRacine,"AmorceR);","","\n");
			EcriS3("}//",sRacine,"INITIALISER\n\n");
		//générer le code de la routine GrammaireTesteR 
			EcriS3("void ",sRacine,"TesteR(char *sMot,int nLgMax){\n");
				EcriS("    int bEngendre,iFin,bSucces;\n");
				EcriS("    sMOT=sMot;\n");
				EcriS("    bSucces=bS(0,&iFin);\n");
				EcriS("    bEngendre=bSucces && nChaineLg(sMOT)==iFin;\n");
				EcriS("    if (bEngendre)\n");
				EcriS("        printf(\"%s: %s %s engendré par la grammaire décrite dans \\\"");
				EcriS(sFichierCible);
				EcriS("\\\".\\n\",(bEngendre)? \"SUCCES\": \"ECHEC \",sG(sMOT),sEst(bEngendre));\n");
				EcriS("    if (nChaineLg(sMot)<nLgMax){\n");
				EcriS3("        ",sRacine,"TesteR(sC2(sMot,\"a\"),nLgMax);\n");
				EcriS3("        ",sRacine,"TesteR(sC2(sMot,\"b\"),nLgMax);\n");
				EcriS("    }\n");
			EcriS3("}//",sRacine,"TesteR\n\n");
		//générer le code de la routine sFichierCibleTESTER qui appelle bS() et dit si sMOT est engendré par la grammaire.
			EcriS3("void ",sRacine,"TESTER(int iTest){\n");
				EcriS("    int bEngendre,iFin,bSucces;\n");
				EcriS7("    Assert1(\"",sRacine,"TESTER0\",b",sRacine,"AmorceR);","","\n");
				EcriS("    //sMOT:=mot à tester selon iTest\n");
				EcriS("        switch(iTest){\n");
				EcriS3("            case 0: ",sRacine,"TesteR(\"\",10);break;\n");
				EcriS("            case 1: sMOT=\"aab\";break;\n");
				EcriS("            case 2: sMOT=\"aaba\";break;\n");
				EcriS3("            default:Assert1(\"",sRacine,"TESTER1\",0);break;\n");
				EcriS("        }\n");
				EcriS("    if (iTest>0){\n");
				EcriS("        bSucces=bS(0,&iFin);\n");
				EcriS("        bEngendre=bSucces && nChaineLg(sMOT)==iFin;\n");
				EcriS("        printf(\"%s: %s %s engendré par la grammaire décrite dans \\\"");
				EcriS(sFichierCible);
				EcriS("\\\".\\n\",(bEngendre)? \"SUCCES\": \"ECHEC \",sG(sMOT),sEst(bEngendre));\n");
				EcriS("    }\n");
			EcriS3("}//",sRacine,"TESTER\n\n");
	free(sRacine);
}//EnteteGenereR


/*
void GrammaireTesteR(char *sMot,int nLgMax){
    int bEngendre,iFin,bSucces;
	sMOT=sMot;
	bSucces=bS(0,&iFin);
	bEngendre=bSucces && nChaineLg(sMOT)==iFin;
	if (bEngendre)
		printf("%s: %s %s engendré par la grammaire décrite dans \"Grammaire.c\".\n",(bEngendre)? "SUCCES": "ECHEC ",sG(sMOT),sEst(bEngendre));
	if(nChaineLg(sMot)<nLgMax){
		GrammaireTesteR(sC2(sMot,"a"),nLgMax);
		GrammaireTesteR(sC2(sMot,"b"),nLgMax);
	}
}

void GrammaireTESTER(int iTest){
    int bEngendre,iFin,bSucces;
    Assert1("GrammaireTESTER0",bGrammaireAmorceR);
    //sMOT:=mot à tester selon iTest
        switch(iTest){
            case 0: GrammaireTesteR("",6);break;
            case 1: sMOT="aabaab";break;
            case 2: sMOT="aaba";break;
            default:Assert1("GrammaireTESTER1",0);break;
        }
	if (iTest>0){
		bSucces=bS(0,&iFin);
		bEngendre=bSucces && nChaineLg(sMOT)==iFin;
		printf("%s: %s %s engendré par la grammaire décrite dans \"Grammaire.c\".\n",(bEngendre)? "SUCCES": "ECHEC ",sG(sMOT),sEst(bEngendre));
	}
}//GrammaireTESTER
*/

void GrammaireAfficheR(int cNiveau,int bFichier,const char *ksGrammaire,int nRegleEnTout){
	//selon bFichier,copie les grammaires sur la console ou dans le fichier fGramR. La grammaire homogène est affichée à partir de nPilE[][].
	int uC,nGrammaireLg,cPasse,bSeparateur,uRegle;
	Assert2("GrammaireAfficheR0",bGrhomAmorceR,!bFichier || bGrhomCompileR);//nPilE[][] est défini si bGrhomCompileR est vrai
		EcriS0(bFichier,sC5(sChoix(bFichier,"//",sTab0()),"Grammaire ",(cNiveau==0)? "algébrique ": "homogène ",sP(sPluriel(nRegleEnTout,"règle")),":\n"));
		Tabuler(+1);
			for (nGrammaireLg=nChaineLg(ksGrammaire),cPasse=0;cPasse<=1;cPasse++){
				for (uRegle=1,bSeparateur=kV,uC=0;uC<=nGrammaireLg;uC++){
					if (cPasse==1 && bSeparateur)
						if (cNiveau==0)
							EcriS1(bFichier,sC4(sTab0(),sChoix1(bFichier,"//")," ",sP(sC0('a'-1+uRegle))));//numérotation alphabétQ des règles
						else EcriS1(bFichier,sC4(sTab0(),sChoix1(bFichier,"//"),sE(1+uRegle<=10),sP(sEnt(uRegle))));//numérotO décimale
					bSeparateur=(ksGrammaire[uC]==kcSeparateuR);
					if (bSeparateur)
						uRegle++;
					if (cPasse==1)
						EcriS0(bFichier,sC0((bSeparateur)?'\n': ksGrammaire[uC]));
				}//for uC
				if (!bSeparateur && cPasse==1)
					EcriS0(bFichier,"\n");
			}//for cPasse
		Tabuler(-1);
	Assert1("GrammaireAfficheR1",uRegle==nRegleEnTout);
}//GrammaireAfficheR

void GrhomAfficheR(int bFichier,const char *ksGrAlgebrique,const char *ksGrHomogene,int nRegleEnTout[2]){
	//selon bFichier,copie les grammaires sur le moniteur ou dans le fichier fGramR. La grammaire homogène est affichée à partir de nPilE[][].
	Assert2("GrhomAfficheR1",bGrhomAmorceR,!bFichier || bGrhomCompileR);//nPilE[][] est défini si bGrhomCompileR est vrai
	if (!bFichier) Tabuler(+2);
	//grammaire algébrique
		GrammaireAfficheR(0,bFichier,ksGrAlgebrique,nRegleEnTout[0]);
	//grammaire homogène
		GrammaireAfficheR(1,bFichier,ksGrHomogene,nRegleEnTout[1]);
	if (!bFichier)
		printf("%sCes deux grammaires engendrent peut-être le même langage…\n",sTab0());
	if (!bFichier) Tabuler(-2);
}//GrhomAfficheR

void GrhomAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
	bGrhomAmorceR=kV;
}//GrhomAMORCER

void GrhomCompiler(const char *ksGrammaireAlgebrique,const char *ksGrammaireHomogene){
	int bCompiler;
	int nRegleEnTout;
	bCompiler=bGrhomCompiler(ksGrammaireAlgebrique,ksGrammaireHomogene,k1Afficher,skFICHIER,&nRegleEnTout);
}//GrhomCompiler

int bGrhomCompiler(const char *ksGrammaireAlgebrique,const char *ksGrammaireHomogene,int bAfficher,char *szFichierCible,int *pnRegleEnTout){
	//vrai ssi ksGrammaireHomogene (règles ET,OU,Terminale entre ";",blancs facultatifs) est bien une grammaire homogène d'au plus kuRegleMaX règles.
	//Si oui,et si szFichierCible est non vide, le code en C qui explicite ksGrammaireHomogene est stocké dans szFichierCible.
	//Les R règles de ksGrammaireHomogene sont affichées au besoin et ce nombre R est copié dans pnRegleEnTout.
	//ksGrammaireAlgebrique est la grammaire algébrique reformulée dans ksGrammaireHomogene. 
	int bCompiler;
	int cPasse;//c comme couple; 0:grammaire algébrique 1:grammaire homogène
	int nSeparateur[1+kuRegleMaX];//indexe chaque kcSeparateuR situé dans la grammaire considérée;un kcSeparateuR final est ajouté au besoin.
	int nRegleEnTout[2];
	char sGrAlgebrique[1+kuCaractereMaX]; 
	char sGrHomogene[1+kuCaractereMaX]; 
	//Appel0("bGrhomCompiler");
		Assert3("bGrhomCompiler1",bGrhomAmorceR,nChaineLg(ksGrammaireAlgebrique)<kuCaractereMaX,nChaineLg(sGrHomogene)<kuCaractereMaX);
		TexteCompacteR(ksGrammaireAlgebrique,sGrAlgebrique);
		TexteCompacteR(ksGrammaireHomogene,sGrHomogene);
		//nSeparateur[]:=rang0 de chaque kcSeparateuR ds sGrAlgebrique ou sGrHomogene selon que cPasse=0 ou cPasse=1.
			for (cPasse=0;cPasse<=1;cPasse++){
				GhromSeparer((cPasse==0)? sGrAlgebrique: sGrHomogene,nSeparateur);
				nRegleEnTout[cPasse]=nSeparateur[0];
			}
		if (bAfficher)
			GrhomAfficheR(!k1FichieR,sGrAlgebrique,sGrHomogene,nRegleEnTout);
		bCompiler=bGrhomHomogenE(sGrHomogene,nSeparateur);//si succès, décrit aussi dans nPilE[][] la structure de la grammaire homogène
		if (bCompiler){
			GrhomTabuleR(sGrHomogene,nRegleEnTout[1],!k1Voir);//remplit la variable de module nTablE[][0]
			DequeAllouer(kuLettreMaX);
				bCompiler=bCompiler && !bRecursivitehGauchE('S'-'@');
			DequeAllouer(0);
		}
	Tabuler(+1);
		bGrhomCompileR=bCompiler;//AVANT GrhomAfficheR li+2;variable de module
		if ( bCompiler && nChaineLg(szFichierCible)>0 )//générer ds sFichierCible le code C qui explicite sGrHomogene
			GrhomExpliciteR(sGrAlgebrique,sGrHomogene,nRegleEnTout,szFichierCible);//qui utilise nPilE[][]
		*pnRegleEnTout=nRegleEnTout[1];//nombre total de règles strictes détectées dans sGrHomogene
		//b(bCompiler);
	//Appel1("bGrhomCompiler");
	Tabuler(-1);
	return(bCompiler);
}//bGrhomCompiler

void GrhomDecideR(char *ksGrammaireAlgebrique,char *ksGrammaireHomogene,char *sMot){
	//dit (printf) si sMot est engendré ou non par ksGrammaireHomogene censée expliciter ksGrammaireAlgebrique.
	#define ksFichierInexistant ""
	#define nDebutEgale0 0
	int nAppel=0;
	int bCompiler,bDecider,nFin,nRegleEnTout,aAttribut[5];
	//Appel0("GrhomDecideR");
		bCompiler=bGrhomCompiler(ksGrammaireAlgebrique,ksGrammaireHomogene,k1Voir,ksFichierInexistant,&nRegleEnTout);
		if (bCompiler){
			GrhomTabuleR(ksGrammaireHomogene,nRegleEnTout,!k1Voir);//remplit la variable de module nTablE[][0] 
			bDecider=bGrhomDecideR('S'-'@',sMot,nDebutEgale0,&nFin,aAttribut,!k1Voir,&nAppel) && (nFin==nChaineLg(sMot));//lit nTablE[][0]
			printf("%s: le mot %s %s engendré %s.\n",(bDecider)?"SUCCES":"ECHEC ",sG(sMot),sEst(bDecider),sP(sPluriel(nAppel,"appel$ en tout")));
		}
	//Appel1("GrhomDecideR");
}//GrhomDecideR

int bGrhomDecideR(int uRegle,char *sMot,int iDebut,int *piFin,int nAttribut[],int bVoir,int *pnAppelEnTout){
	//ssi sMot[iDebut,iFin] est engendré ou non par la gramR décrite ds nTablE[];pnAppelEnTout comptabilise les appels à cette routine.
	const int kuAppelMax=kE4;
	int bCalcul,bDecider=0,iDebute,iFinit,uT,uTermeMax,nType;
	Assert3("bGrhomDecideR1",bGrhomAmorceR,uRegle>0,*pnAppelEnTout<kuAppelMax);
	int nHerite[1+kuAttributMaximaL];
	*pnAppelEnTout+=1;
	uTermeMax=nTablE[uRegle][0];
	nType=nTablE[uRegle][kuTypE];
	Assert1("bGrhomDecideR2",uTermeMax>0);
	if (bVoir)
		printf("Règle %c de type ",'@'+uRegle);
	AttributInitialiseR(uRegle,nAttribut);
	switch (nType) {
		case  rtET:			for (bDecider=kV,iDebute=iDebut,nHerite[0]=0,uT=1;uT<=uTermeMax && bDecider;uT++){
								if (bVoir)
									printf("ET, appel du terme %d: la règle %c.\n",uT,nTablE[nTablE[uRegle][uT]][kuSymbolE]);
								bCalcul=nTablE[uRegle][uT]<=0;
								if (bDecider){
									if (!bCalcul){
										bDecider=bGrhomDecideR(nTablE[uRegle][uT],sMot,iDebute,&iFinit,nHerite,bVoir,pnAppelEnTout);
										//if (bDecider && uT==1) AttributWoiR("ISSI",nHerite);
										//if (bDecider && uT==2) AttributWoiR("ITTI",nHerite);
										if (bDecider) AttributDispatcheR(1,nTablE[uRegle][uT],nHerite,uRegle,uT,nAttribut,uT==10);
									}else bDecider=!bAttributExprimeR(uRegle,nAttribut);
								}
								iDebute=(bDecider)? iFinit : iDebut;
							}
							*piFin=(bDecider)? iFinit : iDebut;
							break;
		case  rtOU:			for (bDecider=kF,nHerite[0]=0,uT=1;uT<=uTermeMax && !bDecider;uT++){
								if (bVoir)
									printf("OU, appel du terme %d: la règle %c.\n",uT,nTablE[nTablE[uRegle][uT]][kuSymbolE]);
								bDecider=bGrhomDecideR(nTablE[uRegle][uT],sMot,iDebut,&iFinit,nHerite,bVoir,pnAppelEnTout);
								if (bDecider) AttributDispatcheR(0,nTablE[uRegle][uT],nHerite,uRegle,uT,nAttribut,!k1Voir);
							}
							*piFin=(bDecider)? iFinit : iDebut;
							break;
		case  rtTerminalE:	bDecider=(sMot[iDebut]==nTablE[uRegle][1]+'@');
							if (bVoir)
								printf("Terminale, sMot[%d] %s reconnu.\n",iDebut,sEst(bDecider));
							*piFin=(bDecider)? iDebut+1 : iDebut;
							if (bDecider)
								bBof=bAttributExprimeR(uRegle,nAttribut);
							break;
		default:			Assert1("bGrhomDecideR3",0);break;
	}
	return(bDecider);
}//bGrhomDecideR

void GrhomDecliner(const char *ksGrammaireAlgebrique,const char *ksGrammaireHomogene,int uMotLgMax,int zdAfficher){
	//liste tous les mots engendrés par ksGrammaireHomogene qui ont jusqu'à uMotLgMax caractères.
	int nAppel,nAppelMax,nAppelEnTout,nC;
	const int kuBase=2;
	int nBit,bCompiler,bDecliner,bDito,iFin;
	const int kuMotLgMax=20;
	char sMot[1+uMotLgMax];
	int nM,nMot,nMotEngendreh,nMotLg,nMotMax,nMotEnTout,aAttribut[1+kuAttributMaximaL];
	int nRegleEnTout;
	const int kuTab=2;
	Assert2("GrhomDecliner",bGrhomAmorceR,bCroitStrict(0,uMotLgMax,kuMotLgMax));//aucune grammaire homogène ne peut engendrer le mot vide
	Tabuler(+1);
	if (bCompiler=bGrhomCompiler(ksGrammaireAlgebrique,ksGrammaireHomogene,k1Voir,"",&nRegleEnTout)){
		GrhomTabuleR(ksGrammaireHomogene,nRegleEnTout,!k1Voir);
		bCompiler=bAttributVerifieR(nRegleEnTout);
	}
	if (bCompiler){
		printf("%sCette grammaire homogène engendre les mots suivants",sTab0());
		printf(" ––%s au maximum, alphabet {",sPluriel(uMotLgMax,"lettre"));
		for (nC=0;nC<kuBase;nC++)
			printf("%c%c",'a'+nC,(nC+1<kuBase)?',':'}');
		printf(":\n");
		for (nAppelMax=0,nAppelEnTout=0,nMotEngendreh=0,nMotEnTout=0,nMotLg=0;nMotLg<=uMotLgMax;nMotLg++){
			nMotMax=zPuissance(kuBase,nMotLg);
			sMot[nMotLg]='\0';
			for (bDito=kF,nMot=0;nMot<nMotMax;nMot++){
				for (nM=kuBase*nMot,nBit=0;nM=nM/kuBase,nBit<nMotLg;nBit++)
					sMot[nBit]='a'+ nM % kuBase;
				bDecliner=bGrhomDecideR('S'-'@',sMot,0,&iFin,aAttribut,!k1Voir,(nAppel=0,&nAppel)) && (iFin==nChaineLg(sMot));
				nAppelMax=iMax(nAppelMax,nAppel);
				nAppelEnTout+=nAppel;
				//printf("%s: le mot %s %s engendré.\n",(bDecliner)?"SUCCES":"ECHEC ",sG(sMot),sEst(bDecliner));
				nMotEngendreh+=bDecliner;
				if (bDecliner){
					printf("%s%2d: %s",sTab(1+kuTab),nMotEngendreh,sG(sMot));
					if (!bDito && nMotLg>1)//indiquer la nouvelle longueur nMotLg du mot engendré et des mots suivants
						printf(" %s %s\n",sE(uMotLgMax-nMotLg),sP(sPluriel(nMotLg,"lettre")));
					else Ligne();
					bDito=kV;
				}
			}//for nMot
			nMotEnTout+=nMotMax;
		}//for nMotLg
		if (nMotEngendreh<=0)
			printf("%s Aucun mot n'est engendré",sTab(kuTab));
		else printf("%s%s (sur %s mots testés)",sTab(kuTab),sPluriel(nMotEngendreh,"mot$ a$ été engendré$"),sEnt(nMotEnTout));
		if (zdAfficher>1){
			printf(" (pire cas pour décider un mot: %s).\n",sPluriel(nAppelMax,"dérivation"));//"décider": transitif, ce verbe signifie "porter un… 
			//…jugement sur", "arrêter une conclusion définitive sur" et donc ici, déterminer si, oui ou non, un mot est engendré par la grammaire.
			printf("%sNombre total de dérivations exécutées pour décliner tous les mots: %s.\n",sTab(kuTab),sEnt(nAppelEnTout));
		}else printf(".\n");
	} 
	Tabuler(-1);
//Appel1("GrhomDecideR");
}//GrhomDecliner

void GrhomExpliciteR(const char *ksGrAlgebrique,const char *ksGrHomogene,int nRegleEnTout[2],char *sFichierCible){
	//génère ds sFichierCible le code C qui décide si la variable de module sMOT est engendrée ou non par la sGrHomogene
	int nListe[1+kuRegleMaX];
	int nRang[1+kuRegleMaX];
	int uR,nRg;
	int iErreur;
	Appel0("GrhomExpliciteR");
		Assert4("GrhomExpliciteR0",bGrhomAmorceR,bGrhomCompileR,nRegleEnTout>0,nChaineLg(sFichierCible)>0);
		fGramR=fopen(sFichierCible,"w");
			Assert1("GrhomExpliciteR1",fGramR!=0);
			//nRang[]=rang des noms de routines classés par ordre alphabétique croissant ——afin de déclarer bA() avant bB(),lui-même avant bS(), etc.
				for (uR=1;uR<=nRegleEnTout[1];uR++)
					nListe[uR]=nPilE[uR][kuSymbolE];
				VecteurTrier2(nListe,1,nRegleEnTout[1],nRang);
				EnteteGenereR(ksGrAlgebrique,ksGrHomogene,nRang,nRegleEnTout,sFichierCible);
				for (uR=1;nRg=nRang[uR],uR<=nRegleEnTout[1];uR++)
					switch (nPilE[nRg][kuTypE]) {
						case  rtET:			RegleEtGenereR(nRg);break;
						case  rtOU:			RegleOuGenereR(nRg);break;
						case  rtTerminalE:	RegleTerminaleGenereR(nRg);break;
						default:			Assert1("GrhomExpliciteR",0);break;
					}
		iErreur=fclose(fGramR);
		Assert1("GrhomExpliciteR2",iErreur==0);
		printf("%sLe fichier %s contient maintenant la traduction de cette grammaire en langage C.\n",sTab(2),sG(sFichierCible));
	Appel1("GrhomExpliciteR");
}//GrhomExpliciteR

int bGrhomHomogenE(const char *ksGrohm,int nSeparateur[]){
	//vrai ssi ksGrohm décrit une liste point-virgulée de règles homogènes contenant A->a et B->b et ayant des membres gauches distincts, dont S.
	int nA=0,nB=0;//+1 sur nA ssi A->a est une règle de la grammaire homogène
	int nDebut,nFin,bHomogene,uR,nRegleEnTout;
	Assert1("bGrhomHomogenE",bGrhomAmorceR);
	sGrhoM=malloc(1+nChaineLg(ksGrohm));
	ChaineCopier0(ksGrohm,sGrhoM);
	//bHomogene:=chaque règle est soit une règle ET soit une règle OU soit une règle terminale.
		for (bHomogene=kV,nRegleEnTout=nSeparateur[0],nDebut=0,uR=1;uR<=nRegleEnTout;uR++){
			nFin=nSeparateur[uR+0]-1;
			ptTablE[uR].v=ptTablE[uR].h=bTablE[uR]=0;
bHomogene=bHomogene && (bRegleET(uR,ksGrohm,nDebut,nFin) || bRegleOU(uR,ksGrohm,nDebut,nFin) || bRegleTerminalE(uR,ksGrohm,nDebut,nFin,&nA,&nB) || bRegleDenonceR(uR,ksGrohm,nDebut,nFin));
//d4(nRegleEnTout,bHomogene,nA,nB);
			nDebut=nFin+2;
		};
	//les règle terminales contiennent au moins les règles A->a et B->b.
		//d2(nA,nB);
		if (bHomogene && !(nA==1 && nB==1))
			printf("ANOMALIE: il manque %s.\n",sPluriel(nA==0+nB==0,"règle$ terminale$"));
//b(bHomogene);
	//les membres gauches des règles sont distincts deux à deux et S est un membre gauche.
		bHomogene=bHomogene && bGrhomPlausiblE(ksGrohm,nSeparateur[0]);
	printf("%sLa seconde grammaire %s homogène.\n",sTab0(),(bHomogene)?"est effectivement":"n'est pas");
	//VecteurVoir("bTablE",bTablE,1,26);
	return(bHomogene);
}//bGrhomHomogenE

int bGrhomPlausiblE(const char *ksGrohm,int nRegleEnTout){
	//vrai ssi les membres gauches sont des majuscules distinctes 2 à 2, la règle S est présente, et les membres droits non terminaux sont définis.
	int uL,nLettre,bPlausible,uR,uT,uTermeMax;
	int nMajuscule[1+kuLettreMaX];//comptabilise les occurrences des majuscules situées en membre gauche de règle
	Assert1("bGrhomPlausiblE0",bGrhomAmorceR);
	//Appel0("bGrhomPlausiblE");
		//bPlausible & nMajuscule[X] :=les membres gauches sont des majuscules distinctes 2 à 2 & nb occurrences de X en membre gauche
			bPlausible=kV;
			for (uL=1;uL<=kuLettreMaX;uL++)
				nMajuscule[uL]=0;
			for (uR=1;uR<=nRegleEnTout;uR++){
				nLettre=nPilE[uR][kuSymbolE]-'@';
				//d(uR);c(nPilE[uR][kuSymbolE]);
				if (!bCroit(1,nLettre,kuLettreMaX))
					printf("ANOMALIE: la règle %c commence par un symbole \"%c\" inconnu.\n",'@'+uR,nLettre);
				bPlausible=bPlausible && bCroit(1,nLettre,kuLettreMaX);
				nMajuscule[nLettre]+=1;
			}
			//VecteurVoir("nMajuscule",&nMajuscule[0],1,kuLettreMaX);
		//bPlausible &&= tout membre gauche de règle est cité au plus une fois.
		if (bPlausible)
			for (uL=1;uL<=kuLettreMaX;uL++){
				if (nMajuscule[uL]>1){
					printf("ANOMALIE: la règle \"%c\" est déclarée %d fois.\n",'@'+uL,nMajuscule[uL]);
					bPlausible=kF;
				}
			}
		//bPlausible &&= la règle S est présente
		if (bPlausible)
			if (nMajuscule['S'-'@']!=1){
				printf("ANOMALIE: la règle S manque.\n");
				bPlausible=kF;
			}
		//bPlausible &&= tout membre droit de règle non terminale est défini: c'est bien le membre gauche d'une règle.
		if (bPlausible)
			for (uR=1;uR<=nRegleEnTout;uR++)
				if ( bDans2(nPilE[uR][kuTypE],rtET,rtOU) )
					for (uTermeMax=nPilE[uR][0],uT=1;uT<=uTermeMax;uT++){
						int bDollarValide=bDans2(nPilE[uR][uT],'$','@') && nPilE[uR][kuTypE]==rtET;
						if (!bDollarValide){
							nLettre=nPilE[uR][uT]-'@';
							if (nMajuscule[nLettre]!=1)
								printf("ANOMALIE: la règle %d invoque un symbole \"%c\" qui n'est pas un nom de règle.\n",uR,nPilE[uR][uT]);
							bPlausible=bPlausible && nMajuscule[nLettre]==1;
						}
					}
	//Appel1("bGrhomPlausiblE");
	//b(bPlausible);
	return(bPlausible);
}//bGrhomPlausiblE

void GhromSeparer(const char *ksGrammaire,int nSeparateur[]){
	int uC;//indexe le caractère courant de la grammaire considérée
	int nGrammaireLg;
	int nRegle,bSeparateur;
	VecteurRazer(nSeparateur,0,kuRegleMaX);
	nGrammaireLg=nChaineLg(ksGrammaire);
	for (nRegle=0,nSeparateur[1]=-2,uC=1;uC<=nGrammaireLg;uC++){
		bSeparateur=(ksGrammaire[uC]==kcSeparateuR);
		if (bSeparateur){
			Assert1("GhromSeparer2",nRegle<kuRegleMaX);
			nSeparateur[++nRegle]=uC;
		};
	}
	if (nSeparateur[nRegle]<nGrammaireLg){
		Assert1("GhromSeparer3",nRegle<kuRegleMaX);
		nSeparateur[++nRegle]=nGrammaireLg;
	}
	Assert1("GhromSeparer4",nRegle<kuRegleMaX);
	nSeparateur[nRegle+1]=nGrammaireLg;
	Assert1("GhromSeparer5",nRegle>=0);//nombre total de règles strictes détectées dans la grammaire considérée.
	nSeparateur[0]=nRegle;//AVANT appel li+2
	//VecteurVoir("nSeparateur",nSeparateur,1,nRegle);
}//GhromSeparer

void GrhomTableVoiR(const char *ksGrohm,int bVoir){
	//affiche ksGrohm et nTablE[][].
	int uL,nT;
	if (bVoir){
		printf("Tabulation (type en colonne 1,membre gauche en dernière colonne) de la…\n");
		t(sC3b(sTab(1),"…grammaire homogène",sG(ksGrohm)));
		for (uL=1;uL<=kuLettreMaX;uL++)
			for (printf("%s(%c) ",sTab(2),'@'+uL),nT=0;nT<=kuTypE || printf("   (%s)",sEntier0(uL,2)) && !bLigne();nT++)
				printf("%3d",nTablE[uL][nT]);
	}
}//GrhomTableVoiR

void GrhomTabuleR(const char *ksGrohm,int nRegleEnTout,int bVoir){
	//remplit nTablE[]. La règle de nom N de nPilE est renommée N-'@' dans nTablE. L'offset '@' transforme la règle A en règle 1 dans nTablE[].
	int uL,uR,uRegle,nT,nTermeMax;
	for (uL=1;uL<=kuLettreMaX;uL++)
		for (nT=0;nT<=kuTermeMaX;nT++)
			nTablE[uL][nT]=0;
	for (uR=1;uR<=nRegleEnTout;uR++){
		uRegle=nPilE[uR][kuSymbolE]-'@';//la règle A sera la règle 1 dans nTablE[]
		nTablE[uRegle][kuTypE]=nPilE[uR][kuTypE];//type en fin de ligne
		nTablE[uRegle][kuSymbolE]=nPilE[uR][kuSymbolE];//stocke le nom quasiment au bout de la ligne nTablE[uRegle]
		nTablE[uRegle][kuReglE]=uR;
		nTablE[uRegle][0]=nPilE[uR][0];//stocke le nb de termes en tête de ligne
		for (nTermeMax=nPilE[uR][0],nT=1;nT<=nTermeMax;nT++)
			nTablE[uRegle][nT]=nPilE[uR][nT]-'@';//tte référence à un nom de règle devient une référence au n° de la ligne ctenant cette règle.
	}
	GrhomTableVoiR(ksGrohm,bVoir);
}//GrhomTabuleR

void GrhomTESTER(int iTest){
	//teste le présent module
	int nLettreMax;
	int nRegleEnTout=0;
	int bCompiler;
	if (iTest>=0){
		Appel0(sC2("GrhomTESTER,test n°",sEnt(iTest)));
			iTest=2;//20
			Assert1("GrhomTESTER",bGrhomAmorceR);
				switch (iTest) {
					case 100:	s(sItem(",x,y,z",2));break;
					case  0:	//L0=aa+ab
								GrhomCompiler("S->Aa+Ab;A->a","S->A.U;U->A+B;A->a;B->b");
								break;
					case  1:	//L1=b
								//GrhomDecliner("S->B+B","S->B;A->a;B->b",nLettreMax=4,!k1Afficher);//**********
								GrhomCompiler("S->B+B","S->B+B;B->b;A->a");
								break;
					case  2:	//L2=a+b
								GrhomDecliner("S->A+B","S->A+B;A->a;B->b",nLettreMax=4,!k1Afficher);//Liste tous les mots engendrés de longueur <=4
								break;
					case  3:	//L1=(a+)b
								GrhomDecliner("S->P.B;P->A.P+B","S->P.B;P->Q+A;Q->A.P;A->a;B->b",nLettreMax=6,!k1Afficher);
								break;
					case  4:	//L1=(a+)b(a+)
								GrhomDecliner("S->P.b.P;P->aP+a","S->P.B.P;P->Q+A;Q->A.P;A->a;B->b",nLettreMax=6,!k1Afficher);
								break;
					case  5:	//L1=anbn,n>0
								GrhomDecliner("S->A.S.B+A.B","S->P+Q;P->A.S.B;Q->A.B;A->a;B->b",nLettreMax=6,!k1Afficher);
								break;
					case  6:	//L1=anb2n,n>1
								GrhomDecliner("S->A.S.B.B+A.B","S->P+Q;P->A.S.B;Q->A.B;A->a;B->b",nLettreMax=8,!k1Afficher);
								break;
					case  7:	//L1=a+b+c+d
								GrhomDecliner("S->A+B+C+D;A->a;B->b;C->c;D->d","S->A+B+C+D;A->a;B->b;C->c;D->d",nLettreMax=5,!k1Afficher);
								break;
					case  8:	//L1=anc+b2nd+,n>=0
								GrhomDecliner("S->P.Q;P->A.P.B+R;R->C.R+C;Q->D.Q+D",
									"S->P.Q;P->W+R;W->A.P.B;R->T+C;T->C.R;Q->U+D;U->D.Q;A->a;B->b;C->c;D->d",nLettreMax=10,!k1Afficher);
								break;
					case  9:	//L1=anb2n,n>0 + a2pb*,p>0
								//L1=(a**2p)b+,p>0 + (a**2p),p>0 + a**(2q)a.b.b.b**(4q),q>0
								GrhomDecliner("S->U+V+W;U->A.A.E;E->U+K;K->B.K+B;V->A.A.V+L;L->A.A;W->A.W.B.B+M;M->A.B.B;A->a;B->b",
										"S->U+V+W;U->A.A.E;E->U+K;K->Y+B;Y->B.K;V->Z+L;Z->A.A.V;L->A.A;W->C+M;C->A.W.B.B;M->A.B.B;A->a;B->b",nLettreMax=10,!k1Afficher);
								break;
					case 10:	//L1={mots non vides qui ont autant de a que de b ******* A TERMINER *******}
								GrhomDecliner("S->A.S.B.S + B.S.A.S + A.S.B + B.S.A + A.B + B.A;A->a;B->b",
											"S->G+H+J+K+L+M;G->A.S.B.S;H->B.S.A.S; J-> A . S.   B ; K->B.S.A;L->A.B;M->B.A;A->a;B->b",nLettreMax=6,!k1Afficher);
								break;
					case 11:	//génère le fichier qui décrit la grammaire ci-dessous
bCompiler=bGrhomCompiler("S->A.S.B+A.B","S->P+Q;P->A.S.B;Q->A.B;A->a;B->b",k1Afficher,"Grammaire.c",&nRegleEnTout);
								break;
					case 12:	//génère le fichier qui décrit la grammaire (a*).a^m.b^n.a^m.b^n ci-dessous
bCompiler=bGrhomCompiler("S-> K.Q;K->A.K.A+Q;Q->B.Q+B","S-> K.Q;K->P+Q;P->A.K.A;Q->U+B;U->B.Q;A->a;B->b",k1Afficher,"Grammaire.c",&nRegleEnTout);
								break;
					case 20:
								GrhomDecliner("S->L.S+S;L->a+b","S->T(x).$(x);T(z)->U(z)+L(z);U(x)->L(y).T(z).$(x,y,z);L(u)->A(u)+B(u);A(x)->a.$(x);B(y)->b.$(y)",nLettreMax=2,!k1Afficher);
								break;
					case 21:
								GrhomDecliner("S->a+b","S->A(x).B(y).(z==0);A(x)->a.(x=3);B(y)->b.(z=2+3,y=z+1)",nLettreMax=2,!k1Afficher);
								break;
					case 22:
								GrhomDecliner("S->a+b","S->A(x).B.(x==3);A(x)->a.(x=3);B(y)->b.(z=2+3,y=z+1)",nLettreMax=2,!k1Afficher);
								break;
					case 23:
								GrhomDecliner("S->a+b","S->A(x).B(y).(x==3);A(x)->a.(x=3);B(y)->b.(z=2+3,y=z+1)",nLettreMax=2,!k1Afficher);
								break;
					default:break;
				}
		Appel1(sC2("GrhomTESTER,test n°",sEnt(iTest)));
	}else GrammaireTESTER(-iTest);
}//GrhomTESTER

char *scPilE(int nRegle,int nTerme){
	int nSymbole=nPilE[nRegle][nTerme];
	char *sResultat=sC0(nSymbole);
	return(sResultat);
}//scPilE

int bRecursivitehGauchE(int uRegle){
	//vrai ssi nTablE[][] permet un appel récursif à gauche
	int bGauche=kF;
	int uT,nTerme,uTermeMax,nType;
	Assert1("bRecursivitehGauchE",bCroit(1,uRegle,kuLettreMaX));
	nType=nTablE[uRegle][kuTypE];
	//printf("Regle,Type et cardinal %c (%d) h=%d.\n",'@'+uRegle,nType,nDequeCardinal());
	//d(uRegle);
	bGauche=bDequeContient(uRegle);
	if (!bGauche){
		DequeEmpiler(uRegle);
		//DequeScruter("bRecursivitehGauchE");
		switch (nType) {
			case  rtET:			nTerme=nTablE[uRegle][1];
								bGauche=bGauche || bRecursivitehGauchE(nTerme);
								sDequeDepiler();
								//DequeVoir("rtET");
								break;
			case  rtOU:			for (uTermeMax=nTablE[uRegle][0],uT=1;uT<=uTermeMax;uT++){
									nTerme=nTablE[uRegle][uT];
									bGauche=bGauche || bRecursivitehGauchE(nTerme);
								}
								sDequeDepiler();
								//DequeVoir("rtOU");
								break;
			case  rtTerminalE:	//DequeVoir("rtTerminalE0");
									sDequeDepiler();
								//DequeVoir("rtTerminalE1");
								break;
			default:			sDequeDepiler();
								//DequeVoir("default");
								break;
		}
	} else RecursivitehGaucheVoiR(" ANOMALIE DÉTECTÉE: récursivité à gauche ",uRegle);
	return(bGauche);
}//bRecursivitehGauchE

void RecursivitehGaucheVoiR(char *sMessage,int uDito){//O(nCardMaX)
	int nCardinal,uS;
	int nFile[1+kuLettreMaX];
	printf("%s%s",sTab(2),sMessage);
	//DequeScruter("AVANT");
	//afficher la pile élément par élément depuis le fond de pile en dépilant temporairement la deque
		for (nCardinal=nDequeCardinal(),uS=nCardinal;uS>=1;uS--)
			nFile[uS]=sDequeDepiler();
		for (uS=1;uS<=nCardinal;uS++)
			printf("%c,",'@'+nFile[uS]);
	printf("%c.\n",'@'+uDito);
	//reconstituer la deque
		for (uS=1;uS<=nCardinal;uS++)
			DequeEmpiler(nFile[uS]);
	//DequeScruter("APRES");
}//RecursivitehGaucheVoiR

int bRegleDenonceR(int nRegle,const char *ksGrhom,int nDebut,int nFin){
	//rend faux;règle bidon destinée à émettre un message d'erreur
	printf("ANOMALIE: la règle %d est non homogène: \"%s\".\n",nRegle,sChainon(ksGrhom,nDebut,nFin));
	return(kF);
}//bRegleDenonceR

int bRegleET(int nRegle,const char *ksGrhom,int nDebut,int nFin){
	//majuscule->majuscule.majuscule.majuscule
	const char kcOperateur='.';
	int bAttribut,uC,nD=nDebut,nLg,bEt,nParametreLg=0,bRegle,nTerme;
	char cAttribut[1+kuAttributMaximaL];
	//VecteurRazer(cAttribut,0,1+kuAttributMaximaL);
	bAttribut=ksGrhom[nD+1]=='(';
	bRegle=(nD<=nFin) && bMajuscule(ksGrhom[nD++]);
	cAttribut[0]=0;
	cAttribut[++cAttribut[0]]='$';
	if (bAttribut){
		nParametreLg=nAttributFranchiR(ksGrhom,nFin,cAttribut,&nD);
	}else nD--;
	bEt=bRegle && bFleche(ksGrhom,nD);
	if (bEt){
		for (nTerme=0,uC=nD+3;uC<=nFin && bEt;uC++){
			if (bMajuscule(ksGrhom[uC]) || ksGrhom[uC]=='$'){
				Assert1("bRegleEt1",nTerme<kuTermeMaX);
				nPilE[nRegle][++nTerme]=ksGrhom[uC];//dont le $
				cAttribut[++cAttribut[0]]='$';
				if (ksGrhom[uC+1]=='('){
					bEt=ksGrhom[++uC]=='(';
					nLg=nAttributFranchiR(ksGrhom,nFin,cAttribut,&uC);
				} 
			}else if (ksGrhom[uC]=='('){
				//s(sChainon(ksGrhom,uC,nFin));
				Assert1("bRegleET2",nTerme<kuTermeMaX);
				nPilE[nRegle][++nTerme]='@';
				cAttribut[++cAttribut[0]]='$';
				bEt=ksGrhom[uC]=='(';
				ptTablE[ksGrhom[nDebut]-'A'+1].h=uC;
				bAttributFranchiR(ksGrhom,nFin,cAttribut,&uC,&nLg);
				ptTablE[ksGrhom[nDebut]-'A'+1].v=uC-1;
				//d2(nParametreLg,nLg);
				bEt=nParametreLg<nLg;
				uC+=nLg;
				//d(uC);
			}else bEt=(ksGrhom[uC]==kcOperateur || ksGrhom[uC]==';');
		}
		nPilE[nRegle][kuTypE]=rtET;
		nPilE[nRegle][0]=nTerme;
		nPilE[nRegle][kuSymbolE]=ksGrhom[nDebut];
		if (bEt){
			//s(sChainon(ksGrhom,nDebut,nFin));
			//AttributVoiR("nmAttributET",cAttribut);
			//bTablE[ksGrhom[nDebut]-'A'+1]=bAffectation;
			AttributTabuleR(ksGrhom[nDebut],cAttribut);
		}
	}
	//b(bEt);
	return(bEt);
}//bRegleET

void RegleEtGenereR(int nRegle){
	int uT;
	int nTermeMax=nPilE[nRegle][0];
	EcriS3("int b",scPilE(nRegle,kuSymbolE),"(int iDebut,int *piFin){\n");
		//recopier en commentaire le libellé de la règle
			EcriS3("    //",scPilE(nRegle,kuSymbolE),"->");
			for (uT=1;uT<=nTermeMax;uT++){
				EcriS(scPilE(nRegle,uT));
				if (uT<nTermeMax)
					EcriS(".");
			}
			EcriS("\n");
		//déclarer les variables locales autres que bSucces
			for (EcriS("    int iA=iDebut,"),uT=1;uT<=nTermeMax;uT++){
				EcriS3("i",sC0('@'+uT+1),"");//commence avec iB
				EcriS((uT<nTermeMax)? ",":";\n");
			}
		EcriS("    int bSucces=");
		for (uT=1;uT<=nTermeMax;uT++){
			EcriS7("b",scPilE(nRegle,uT),"(i",sC0('@'+uT),",&i",sC0('@'+uT+1),")");
			if (uT<nTermeMax)
				EcriS(" && ");
		}
		EcriS(";\n");
		EcriS3("    *piFin=(bSucces)?i",sC0('@'+nTermeMax+1),":iDebut;\n");
		EcriS("    return(bSucces);\n");
	EcriS3("}//b",scPilE(nRegle,kuSymbolE),"\n\n");
}//RegleEtGenereR

int bRegleOU(int nRegle,const char *ksGrhom,int nDebut,int nFin){
	//majuscule->majuscule+majuscule+majuscule; si jeu d'attributs, les jeux sont tous identQ
	const char kcOperateur='+';
	int bAttribut,uC,nD=nDebut,nLg,bOu,nParametreLg=0,bRegle,nTerme;
	bAttribut=ksGrhom[nD+1]=='(';
	char cAttribut[1+kuAttributMaximaL];
	//ds(1,sChainon(ksGrhom,nDebut,nFin));
	bRegle=(nD<=nFin) && bMajuscule(ksGrhom[nD++]);
	cAttribut[0]=0;
	cAttribut[++cAttribut[0]]=0;
	if (bAttribut)
		nParametreLg=nAttributFranchiR(ksGrhom,nFin,cAttribut,&nD);
	else nD--;
	bOu=bRegle && bFleche(ksGrhom,nD);
	if (bOu){
		for (nTerme=0,uC=nD+3;uC<=nFin;uC++){
			if (bMajuscule(ksGrhom[uC])){
				Assert1("bRegleOU1",nTerme<kuTermeMaX);
				nPilE[nRegle][++nTerme]=ksGrhom[uC];
				if (bAttribut){
					cAttribut[++cAttribut[0]]=nTerme;
					bOu=bOu && ksGrhom[++uC]=='(';
					nLg=nAttributFranchiR(ksGrhom,nFin,cAttribut,&uC);
					bOu=bOu && (nParametreLg==nLg);
				}
			}else bOu=bOu && (ksGrhom[uC]==kcOperateur || ksGrhom[uC]==';');
		}
		//sd("****************************bOU:nTerme",nTerme);
		//bb(bOu,bOu);
		nPilE[nRegle][kuTypE]=rtOU;
		nPilE[nRegle][0]=nTerme;
		nPilE[nRegle][kuSymbolE]=ksGrhom[nDebut];
		if (bOu){
			//s(sChainon(ksGrhom,nDebut,nFin));
			//AttributVoiR("nmAttributOU",cAttribut);
			AttributTabuleR(ksGrhom[nDebut],cAttribut);
		}
	}
	return(bOu);
}//bRegleOU

void RegleOuGenereR(int nRegle){
	int uT;
	int nTermeMax=nPilE[nRegle][0];
	EcriS3("int b",scPilE(nRegle,kuSymbolE),"(int iDebut,int *piFin){\n");
		//rappel de la règle
			EcriS3("    //",scPilE(nRegle,kuSymbolE),"->");
			for (uT=1;uT<=nTermeMax;uT++){
				EcriS(scPilE(nRegle,uT));
				if (uT<nTermeMax)
					EcriS("+");
			}
			EcriS("\n");
		//code interne
			EcriS("    int iFin;\n");
			EcriS("    int bSucces=");
			for (uT=1;uT<=nTermeMax;uT++){
				EcriS3("b",scPilE(nRegle,uT),"(iDebut,&iFin)");
				if (uT<nTermeMax)
					EcriS(" || ");
			}
			EcriS(";\n");
			EcriS("    *piFin=(bSucces)?iFin:iDebut;\n");
			EcriS("    return(bSucces);\n");
	EcriS3("}//b",scPilE(nRegle,kuSymbolE),"\n\n");
}//RegleOuGenereR

int bRegleTerminalE(int nRegle,const char *ksGrhom,int nDebut,int nFin,int *pnA,int *pnB){
	//majuscule->minuscule et ce sont les mêmes lettres à la casse près; pbA passe à 1 si A->a est rencontré;idem pour pbB.
	int bAffectation=1,bAttribut,uC,nD=nDebut,nLg,nParametreLg=0,bRegle,nTerme,bTerminale;
	char cAttribut[1+kuAttributMaximaL];
	int nA=*pnA;nA+=(ksGrhom[nDebut]=='A');*pnA=nA;
	int nB=*pnB;nB+=(ksGrhom[nDebut]=='B');*pnB=nB;
	bAttribut=ksGrhom[nD+1]=='(';
	bRegle=(nD<=nFin) && bMajuscule(ksGrhom[nD++]);
	if (bRegle){
		cAttribut[0]=0;
		cAttribut[++cAttribut[0]]='$';
		if (bAttribut)
			nParametreLg=nAttributFranchiR(ksGrhom,nFin,cAttribut,&nD);
		else nD--;
	}
	bTerminale=bRegle && bFleche(ksGrhom,nD);// && bMinuscule(ksGrhom[nFin]) && (ksGrhom[nDebut]+0x20==ksGrhom[nFin]);
	if (bTerminale)
		for (nTerme=0,uC=nD+3;uC<=nFin && bTerminale;uC++){
			if (bMinuscule(ksGrhom[uC]) || ksGrhom[uC]=='$'){
				Assert1("bRegleTerminalE1",nTerme<kuTermeMaX);
				nPilE[nRegle][++nTerme]=ksGrhom[uC];
				cAttribut[++cAttribut[0]]='$';
				if (ksGrhom[uC+1]=='('){
					bTerminale=ksGrhom[++uC]=='(';
					nLg=nAttributFranchiR(ksGrhom,nFin,cAttribut,&uC);
					bTerminale=nParametreLg==nLg;
				} 
			}else if (ksGrhom[uC]=='('){
				Assert1("bRegleTerminalE2",nTerme<kuTermeMaX);
				nPilE[nRegle][++nTerme]='$';
				cAttribut[++cAttribut[0]]='$';
				bTerminale=ksGrhom[uC]=='(';
				ptTablE[ksGrhom[nDebut]-'A'+1].h=uC;
				bAffectation=bAttributFranchiR(ksGrhom,nFin,cAttribut,&uC,&nLg);
				ptTablE[ksGrhom[nDebut]-'A'+1].v=uC-1;
				bTerminale=nParametreLg<nLg;
				uC+=nLg;
			}else bTerminale=(ksGrhom[uC]=='.' || ksGrhom[uC]==';');
		}
		if (bTerminale){
			bTablE[ksGrhom[nDebut]-'A'+1]=bAffectation;
			AttributTabuleR(ksGrhom[nDebut],cAttribut);
		}
	nPilE[nRegle][kuTypE]=rtTerminalE;
	nPilE[nRegle][0]=nTerme;
	nPilE[nRegle][kuSymbolE]=ksGrhom[nDebut];
	//cd(nPilE[nRegle][kuSymbolE],nRegle);
	return(bTerminale);
}//bRegleTerminalE

void RegleTerminaleGenereR(int nRegle){
	EcriS3("int b",scPilE(nRegle,kuSymbolE),"(int iDebut,int *piFin){\n");
		//recopier en commentaire le libellé de la règle
			EcriS3("    //",scPilE(nRegle,kuSymbolE),"->");
			EcriS(scPilE(nRegle,1));
			EcriS("\n");
		EcriS3("    int bSucces = sMOT[iDebut]=='",scPilE(nRegle,1),"';\n");
		EcriS("    *piFin = (bSucces) ? iDebut+1 : iDebut;\n");
		EcriS("    return(bSucces);\n");
	EcriS3("}//b",scPilE(nRegle,kuSymbolE),"\n\n");
}//RegleTerminaleGenereR

void TexteCompacteR(const char *ksNonCompact,char sCompact[1+kuCaractereMaX]){
	//sCompact:=sNonCompact sans blancs
	int uC,uD;
	for (uC=uD=0;uC<nChaineLg(ksNonCompact);uC++)
		if (ksNonCompact[uC]!=' ')
			sCompact[uD++]=ksNonCompact[uC];
	sCompact[uD]='\0';
}//TexteCompacteR


