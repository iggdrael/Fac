#include "Kit.h"
//012345678901234567890123456789012345678901234567890123456789
#define kuAppelMaX 63
#define kcEchappemenT1 -61
#define kcEchappemenT2 -59
#define kuEntier23SizE 23 //touche pas à 23
#define kuPtrEnToutParEspacE k2E14 //k2E14 touche pas;nb total de chaînes allouées par demi-espace 
#define kuModeChiffreMaX 100
#define kuPileMaX 256
#define kuWhileMaX 5 //nb max de while imbriqués (si des appels récursifs imbriquent un grand nombre de while, augmenter sensiblement cette valeur)
//constantes et variables:
int bActiveR=0;
char *sAlphabetMajusculE="A,À,Â,Ä,B,C,Ç,D,E,É,È,Ê,Ë,F,G,H,I,Î,Ï,J,K,L,M,N,Ñ,O,Ô,Ö,P,Q,R,S,T,U,Ù,Ü,V,W,X,Y,Ÿ,Z";
char *sAlphabetMinusculE="a,à,â,ä,b,c,ç,d,e,é,è,ê,ë,f,g,h,i,î,ï,j,k,l,m,n,ñ,o,o,ö,p,q,r,s,t,u,u,ü,v,w,x,y,ÿ,z";
int bAppeL[1+kuAppelMaX];//dédié au contrôle des appels de routines Appel0() et Appel1()
int nAppeL=0;//initialisation vitale ici car KitAmorcer n'a pas encore été appelé à l'appel de Appel0() en tête de main();dédié Appel0() et Appel1()
const int kuAppelActiF=kV;
const int kuAppelIndentatioN=4;
char cChaineGarniR;//caractère de remplissage (espace blanc par défaut) utilisé dans les routines sChaine0,sChaine1 et sChaine2.
int iEntierPilE[1+kuPileMaX];
int ipEntierPilE;//index sur iEntierPilE 
float fEpsiloN;
char kcExtensioN='\303';
int bFlaG=0;
int bKitAmorceR;//ie le module a bien été amorcé

#define kuMallocEspaceEnTouT 4 //pr MallocGerer
int nMallocEspaceEnTouT=0;//accu
const int kbMallocGardE=1;
int spMalloC=0;//n° espace courant
int ipMalloC[kuMallocEspaceEnTouT];//nb de pointeurs alloués ds l'espace courant
long yptrMalloC[kuMallocEspaceEnTouT][kuPtrEnToutParEspacE];//table des pointeurs
int muModeCaracterE[1+kuModeCaractereMax];
int icModeCaracterE[1+kuModeCaractereMax];
int ipModeCaracterE;
int muModeChiffrE3[1+kuModeChiffreMaX];
int ipModeChiffrE3=0;
int uPremieR[1+kuPremierRgMax];
int nTabulatioN=0;
int uTitreLargeurPairE=126;
int ipWhilE=0;//index de pile dédié While() et bWhile()
long zWhilE[1+kuWhileMaX];

//prototypes de TOUTES les routines privées,ci-dessous,en .c,puisque le .h doit être réservé aux prototypes sde routines publiques appelées effectivement depuis l'extérieur. 
void AsserT(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6);
void AsserT0(char *sContexte,int bAssertion,int nParametre);
int bChaineAbregE(char sTexteOriginal[]);
void ChaineAbregeR(char sTexte[],int nLargeurHorsTout);
void ChaineCopierTesteR();
void ChronoTesteR();
int bConsonnE2(const char *ksTexte,int *pnCodeCaractereRg0);
int bLettrE2(const char *ksTexte,int *pnCodeCaractereRg0);
void ListeTesteR();
char *sMalloC(int nOctat);
void MallocGereR(char *sMalloc);//technique,gère les malloc et les free des chaînes de caractères et d'entiers littéraux
void MallocGereR0();//initialise leurs gestion
void PremierAmorceR();
int bVirgulhE(char cCaractere);
int bVoyellE2(const char *ksTexte,int *pnCodeCaractereRg0);

void t(char *sTexte){
	assert(sTexte!=0);
	printf("%s.\n",sTexte);
}//t

void tb(char *sTexte,int bBooleen){
	printf("%s:%s.\n",sTexte,(bBooleen!=0)?"vrai":"faux");
}//tb

void tc(char *sTexte,char cCaractere){
	printf("%s:'%c'.\n",sTexte,cCaractere);
}//tc

void te(char *sTexte,long yEntier1){
	printf("%s:%li.\n",sTexte,yEntier1);
}//te

void tee(char *sTexte,long yEntier1,long yEntier2){
	printf("%s:%li, %ld.\n",sTexte,yEntier1,yEntier2);
}//tee

void teee(char *sTexte,long yEntier1,long yEntier2,long yEntier3){
	printf("%s:%li, %li, %li.\n",sTexte,yEntier1,yEntier2,yEntier3);
}//teee

void teeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4){
	printf("%s:%li, %li, %li, %li.\n",sTexte,yEntier1,yEntier2,yEntier3,yEntier4);
}//teeee

void teeeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4,long yEntier5){
	printf("%s:%li, %li, %li, %li, %li.\n",sTexte,yEntier1,yEntier2,yEntier3,yEntier4,yEntier5);
}//teeeee

void teeeeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4,long yEntier5,long yEntier6){
	printf("%s:%li, %li, %li, %li, %li, %li.\n",sTexte,yEntier1,yEntier2,yEntier3,yEntier4,yEntier5,yEntier6);
}//teeeeee

void tq(char *sTexte,q qRationnel){
	//affiche sTexte puis qRationnel: tq("qA",qA) affiche "eA:2/3" si qA vaut 2/3.
	printf("%s:%s.\n",sTexte,sQ(qRationnel));
}//tq

void tr(char *sTexte,double dReel1){
	printf("%s:%lf.\n",sTexte,dReel1);//ou %8.3lf pr 8 caractères en tout et 3 décimales
}//tr

void tri(char *sTexte,ri rComplexe){
	//affiche sTexte puis rComplexe: tri("riA",riA) affiche "eA:2+i" si eA vaut 2+i.
	printf("%s:%s.\n",sTexte,sK(rComplexe));
}//tri

void trr(char *sTexte,double dReel1,double dReel2){
	printf("%s:%lf, %lf.\n",sTexte,dReel1,dReel2);
}//trr

void trrr(char *sTexte,double dReel1,double dReel2,double dReel3){
	printf("%s:%lf, %lf, %lf.\n",sTexte,dReel1,dReel2,dReel3);
}//trrr

void tt(char *sTexte1,char *sTexte2){
	Assert2("Routine tt",sTexte1!=0,sTexte2!=0);
	printf("%s, %s.\n",sTexte1,sTexte2);
}//tt

void ttt(char *sTexte1,char *sTexte2,char *sTexte3){
	Assert3("Routine ttt",sTexte1!=0,sTexte2!=0,sTexte3!=0);
	printf("%s, %s, %s.\n",sTexte1,sTexte2,sTexte3);
}//ttt

void tttt(char *sTexte1,char *sTexte2,char *sTexte3,char *sTexte4){
	Assert4("Routine tttt",sTexte1!=0,sTexte2!=0,sTexte3!=0,sTexte4!=0);
	printf("%s, %s, %s, %s.\n",sTexte1,sTexte2,sTexte3,sTexte4);
}//tttt

void ttttt(char *sTexte1,char *sTexte2,char *sTexte3,char *sTexte4,char *sTexte5){
	Assert5("Routine sssss",sTexte1!=0,sTexte2!=0,sTexte3!=0,sTexte4!=0,sTexte5!=0);
	printf("%s, %s, %s, %s, %s.\n",sTexte1,sTexte2,sTexte3,sTexte4,sTexte5);
}//ttttt

char *sA(char *sEntreAccolade){
	//rend sEntreAccolade précédé de "{" et suivi de "}"
	const int kuUnDelimiteur=1;
	assert(sEntreAccolade!=0);	
	char *sA=sMalloC(kuUnDelimiteur+nChaineLg(sEntreAccolade)+kuUnDelimiteur);
		strcpy(sA,sC3("{",sEntreAccolade,"}"));
	MallocGereR(sA);
	return(sA);
}//sA

void AsserT(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6){
	//contrôle les assertions fournies en paramètres et indique toutes celles qui ne sont pas vérifiées
	int bAssertion=bAssertion1 && bAssertion2 && bAssertion3 && bAssertion4 && bAssertion5 && bAssertion6;
	if (!bAssertion){//si une assertion est fausse,afficher sContexte et le numéro de cette assertion ——afin de faciliter le débogage ultérieur.
		AsserT0(sContexte,bAssertion1,1); 
		AsserT0(sContexte,bAssertion2,2); 
		AsserT0(sContexte,bAssertion3,3);
		AsserT0(sContexte,bAssertion4,4);
		AsserT0(sContexte,bAssertion5,5);
		AsserT0(sContexte,bAssertion6,6);
	}
	assert(bAssertion);//si bAssertion est vrai,indolore;sinon,affiche un message système qui ne vous sera d'aucune utilité puis stoppe l'exécution.
}//AsserT

void AsserT0(char *sContexte,int bAssertion,int nParametre){
	if (!bAssertion){
		printf("    *** Assertion fausse (expression booléenne n°%d)",nParametre);
		if (nChaineLg(sContexte)>0)
			printf(" dans \"%s\"",sContexte);
		printf(".\n");
	}
}//AsserT0

void Assert1(char *sContexte,int bAssertion1){
	AsserT(sContexte,bAssertion1,kV,kV,kV,kV,kV);
}//Assert1

void Assert11(char *sContexte,int bAssertion1,int iValeur1){
	//si bAssertion1 est faux, affiche sa valeur iValeur1 puis déroute;sinon,ne fait rien.
	if (!bAssertion1)
		printf("\t %s=%d est refusé:",sItem(sContexte,2),iValeur1);
	AsserT(sItem(sContexte,1),bAssertion1,kV,kV,kV,kV,kV);
}//Assert11

void Assert12(char *sContexte,int bAssertion1,int iValeur1,int iValeur2){
	//si bAssertion1 est faux, affiche iValeur1 et iValeur2 puis déroute;sinon,ne fait rien.
	if (!bAssertion1)
		printf("\t (%s=%d,%s=%d) est refusé:",sItem(sContexte,2),iValeur1,sItem(sContexte,3),iValeur2);
	AsserT(sItem(sContexte,1),bAssertion1,kV,kV,kV,kV,kV);
}//Assert12

void Assert2(char *sContexte,int bAssertion1,int bAssertion2){
	AsserT(sContexte,bAssertion1,bAssertion2,kV,kV,kV,kV);
}//Assert2

void Assert21(char *sContexte,int bAssertion1,int bAssertion2,int iValeur){
	if (!bAssertion1 || !bAssertion2)
		printf("\t %s=%d est refusé:",sItem(sContexte,2),iValeur);
	AsserT(sItem(sContexte,1),bAssertion1,bAssertion2,kV,kV,kV,kV);
}//Assert22

void Assert22(char *sContexte,int bAssertion1,int bAssertion2,int iValeur1,int iValeur2){
	if (!bAssertion1 || !bAssertion2)
		printf("\t %s=%d ou %s=%d est refusé:",sItem(sContexte,2),iValeur1,sItem(sContexte,3),iValeur2);
	AsserT(sItem(sContexte,1),bAssertion1,bAssertion2,kV,kV,kV,kV);
}//Assert22

void Assert3(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,kV,kV,kV);
}//Assert3

void Assert4(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,kV,kV);
}//Assert4

void Assert5(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,kV);
}//Assert5

void Assert6(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,bAssertion6);
}//Assert6

float fAbs(float fReel){
	//rend la valeur absolue de fReel
	float fAbs;
	if (fReel>=0.0)
		fAbs=fReel;
	else fAbs=-fReel;
	return(fAbs);
}//fAbs

int nAbs(int iEntier){
	//rend la valeur absolue positive de iEntier ou déroute si iEntier est trop négatif;cache la fonction abs
	int nAbs;
	Assert1("nAbs0",iEntier!=kiIntegerMin);
	nAbs=abs(iEntier);//>=0 ssi iEntier!=kiIntegerMin
	Assert1("nAbs1",nAbs>=0);
	return(nAbs);
}//nAbs

long zAbs(long yEntier){
	//rend la valeur absolue positive ou déroute si yEntier est trop négatif;cache la fonction labs
	long zAbs;
	Assert1("zAbs0",yEntier!=kyLongintMin);
	zAbs=labs(yEntier);//>=0 ssi yEntier!=kyLongintMin
	Assert1("zAbs1",zAbs>=0);
	return(zAbs);
}//zAbs

q qAdd(q qA,q qB){
	//somme de deux rationnels
	q qAdd;
	int xPgcd;
	Assert2("qAdd1",qA.den>0,qB.den>0);
	qAdd.num=qA.num*qB.den+qB.num*qA.den;
	qAdd.den=qA.den*qB.den;
	if (qAdd.num!=0){
		xPgcd=zPgcd(abs(qAdd.num),qAdd.den);
		qAdd.den/=xPgcd;
		qAdd.num/=xPgcd;
	} else qAdd.den=1;
	Assert1("qAdd2",qA.den>0);
	return(qAdd);
}//qAdd

ri riAdd(ri riA,ri riB){
	//somme de deux nombres complexes
	ri riAdd;
	riAdd.r=riA.r+riB.r;
	riAdd.i=riA.i+riB.i;
	return(riAdd);
}//riAdd

ri riAff(float fReel,float fImaginaire){
	//rend le nombre complexe dReel+i.dImaginaire
	ri riAff;
	riAff.r=fReel;
	riAff.i=fImaginaire;
	return(riAff);
}//riAff

int bAffichable(char cUnCaractere){
	int nLg=nChaineLg(sC0(cUnCaractere));
	int bAffichable=(nLg>0) && ( isprint(cUnCaractere) || isspace(cUnCaractere) );
	//bAffichable=bAffichable || bChaineEgale(sC0(cUnCaractere),"°");
	//if (!bAffichable) s(sG(sC0(cUnCaractere)));
	return(bAffichable);
}//bAffichable

void Appel0(char *sMessage){
	//affiche sMessage s'il est non vide;sinon,affiche "Exécution en cours...". Puis passe à la ligne. Vérifie le parenthésage des appels.
	Assert2("Appel0a",sMessage!=0,nAppeL<kuAppelMaX);
	FlipFlop("Appel0b",1,&bAppeL[++nAppeL]);//vérifie que Appel0() ne suit pas un Appel0(), ie il y a 1 Appel1() entre eux
	if (kuAppelActiF){
		if (strlen(sMessage)==0)
			printf("Exécution en cours...\n");
		else printf("%s%s: tâche en cours...\n",sE(nAppeL*kuAppelIndentatioN),sMessage);//modifier kuAppelIndentatioN au besoin
	}
	//printf("Appel0 n°%d.\n",nAppeL);
}//Appel0

void Appel1(char *sMessage){
	//affiche sMessage s'il est non vide;sinon,affiche "Exécution terminée.". Puis passe à la ligne. Vérifie le parenthésage des appels.
	int nMessageLg=strlen(sMessage);
	Assert2("Appel1a",sMessage!=0,nAppeL>0);
	FlipFlop("Appel1b",0,&bAppeL[nAppeL]);//vérifie que Appel1() ne suit pas un Appel1(), ie il y a 1 Appel0() entre eux
	if (kuAppelActiF)
		if (nMessageLg==0){
			if (0) printf("Changements d'espace effectués: %d.\n",nMallocEspaceEnTouT);
			printf("Exécution terminée");
			int nPtrEnTout=nMallocEspaceEnTouT*kuPtrEnToutParEspacE+ipMalloC[spMalloC];
			if (1 && nMallocEspaceEnTouT>=0)
				printf(" après %s allocations de pointeurs et %s de %d pointeurs",sPar3(nPtrEnTout),sPluriel0(nMallocEspaceEnTouT,"changement$ d'espace$"),kuPtrEnToutParEspacE);
			printf(".\n");
			//if (kbMallocGardE) printf("N.B. kbMallocGardE est actif.\n");
		} else printf("%s%s: tâche terminée.\n",sE(nAppeL*kuAppelIndentatioN),sMessage);//modifier kuAppelIndentatioN au besoin
	nAppeL--;
	Assert1("Appel1c",nAppeL>=0);
	if (!nMessageLg){
		Assert1("Appel1: Appel0 et Appel1 ne sont pas correctement parenthésés",nAppeL==0);//ie Appel0() et Appel1() sont correctement parenthésés
		Assert1("Appel1 while",ipWhilE>=0);//si ok,il y a bien 1° un appel à While() avant chaque while/do while et 2° un appel à bWhile() dans ladite boucle
	}
	//printf("Appel1 n°%d.\n",nAppeL);
}//Appel1

float fArrondemi(double dNombre){
	//rend un réel R tel que 2*R est l'entier le plus proche de 2*dNombre  
	Assert1("fArrondemi",fabs(dNombre)<kxLongintMax);//on peut faire mieux
	long yArrondemi=yArrondi( (dNombre>=0.0)? 2*dNombre+0.25: 2*dNombre-0.25 );
	float fArrondemi=yArrondemi/2.0;
	//f2(dNombre,fArrondemi);
	return(fArrondemi);
}//fArrondemi

long yArrondi(double dNombre){
	int bValide=fabs(dNombre)<kxLongintMax;
	if (!bValide) df(kxLongintMax,dNombre);
	Assert1("yArrondi",bValide);//on peut faire mieux
	long yArrondi=(dNombre>=0.0)? (long) (dNombre+0.5): (long) (dNombre-0.5);
	return(yArrondi);
}//yArrondi

int bAscii(char cUnCaractere){
	//mm code que bAfichable
	int nLg=nChaineLg(sC0(cUnCaractere));
	int bAscii=(nLg>0) && ( isprint(cUnCaractere) || isspace(cUnCaractere) );
	//bAffichable=bAffichable || bChaineEgale(sC0(cUnCaractere),"°");
	//if (!bAffichable) s(sG(sC0(cUnCaractere)));
	return(bAscii);
}//bAscii

char *sAvec(int bAvecSinonSans,char *sQuoi){
	char *sAvec=sC2b(sChoix(bAvecSinonSans,"avec","sans"),sQuoi);
	return(sAvec);
}//sAvec

void Base10(int nDizaineUniteh,int *pnDizaine,int *pnUniteh){
	//inverse de Base10 ci-dessous
	Assert1("Base10",bCroit(0,nDizaineUniteh,99));
	*pnDizaine=nDizaineUniteh/10;
	*pnUniteh=nDizaineUniteh%10;
}//Base10

int nBase10(int nDizaine,int nUniteh){
	//rend 10*nDizaine+nUniteh
	Assert2("nBase10",bDecit(nUniteh),bDecit(nUniteh));
	int nBase10=10*nDizaine+nUniteh;
	return(nBase10);
}//nBase10

void Base16(int nABCD,int *pbA,int *pbB,int *pbC,int *pbD){
	//inverse de Base16 ci-dessous
	Assert1("Base16",bCroit(0,nABCD,15));
	int nReste=nABCD;
	*pbD=bImpair(nReste);nReste=nReste/2;
	*pbC=bImpair(nReste);nReste=nReste/2;
	*pbB=bImpair(nReste);nReste=nReste/2;
	*pbA=bImpair(nReste);nReste=nReste/2;
}//Base16

int nBase16(int bA,int bB,int bC,int bD){
	//rend 8*bA+4*bB+2*bC+bD
	Assert4("nBase16",bBool(bA),bBool(bB),bBool(bC),bBool(bD));
	int nBase16=4*nBase4(bA,bB)+nBase4(bC,bD);
	return(nBase16);
}//nBase16

int nBase4(int bA,int bB){
	Assert2("nBase4",bBool(bA),bBool(bB));
	int nBase4=2*bA+bB;
	return(nBase4);
}//nBase4

int bBit(char cCaractere){
	int bBit=(cCaractere=='0') || (cCaractere=='1');
	assert(bBit==0 || bBit==1);
	return(bBit);
}//bBit

int bBool(long yEntier){
	int bBool=(yEntier==0) || (yEntier==1);
	assert(bBool==0 || bBool==1);
	return(bBool);
}//bBool

int iBorner(int iBorneInf,int iValeur,int iBorneSup){
	//rend iValeur si iBorneInf≤iValeur≤iBorneSup, ou la borne la plus proche de iValeur
	Assert1("iBorner",iBorneInf<=iBorneSup);
	int iBorner=iValeur;
	iBorner=iSup(iBorneInf,iBorner);
	iBorner=iInf(iBorner,iBorneSup);
	return(iBorner);
}//iBorner

long yBorner(long yBorneInf,long yValeur,long yBorneSup){
	//rend yValeur si yBorneInf≤yValeur≤yBorneSup, ou la borne la plus proche de yValeur
	Assert1("yBorner",yBorneInf<=yBorneSup);
	long yBorner=yValeur;
	yBorner=ySup(yBorneInf,yBorner);
	yBorner=yInf(yBorner,yBorneSup);
	return(yBorner);
}//yBorner

char *sBool(long yValeur){
	//rend en clair la valeur booléenne de yValeur
	if (yValeur)
		return("VRAI");
	else return("faux");
}//sBool

int bByte(long yEntier){
	int bByte=bCroit(0,yEntier,kuByteMax);
	return(bByte);
}//bByte

char *sC(const char *sEntreCrochet){
	//rend sEntreCrochet précédé de "[" et suivi de "]"
	const int kuUnDelimiteur=1;
	assert(sEntreCrochet!=0);	
	char *sC=sMalloC(kuUnDelimiteur+nChaineLg(sEntreCrochet)+kuUnDelimiteur);
		strcpy(sC,sC3("[",sEntreCrochet,"]"));
	//char *sC=sC3("[",sEntreCrochet,"]");
	return(sC);
}//sC

char *sC0(const char  cImprimableOuEspace){
	//convertit cImprimableOuEspace en string;cA est censé être soit un caractère imprimable (pas de lettre accentuée) soit un espace.
	char *sCaractere=sMalloC(2);//2 octets si stray
		//Assert1("sC",bAffichable(cImprimableOuEspace) );//dont: espace,saut page,fin ligne,retour chariot,tabulation.
		sCaractere[0]=cImprimableOuEspace;
		sCaractere[1]='\0';
		//int bAffichable=isprint(sCaractere[0]) || isspace(sCaractere[0]);//ne pas appeler bAffichable() qui appelle sC0()
		//if (!bAffichable) printf("@@@ iEntier(sCaractere)=%d.\n",iEntier(sCaractere));
		//Assert1("sC0",bAffichable);//dont: espace,saut page,fin ligne,retour chariot,tabulation.*/
	MallocGereR(sCaractere);
	return(sCaractere);
}//sC0

char *sC02(char cBase,int iOffset){//DESUET
	//convertit cBase+iOffset en string;la somme est censée être soit un caractère imprimable (pas de lettre accentuée) soit un espace.
	char *sCaractere=sMalloC(1);
		sCaractere[0]=cBase+iOffset;
		sCaractere[1]='\0';
		Assert1("sC02",bAffichable(sCaractere[0]));//dont: espace,saut page,fin ligne,retour chariot,tabulation.
	MallocGereR(sCaractere);
	return(sCaractere);
}//sC02

char *sC1(const char *sNonNull){
	//rend sNonNull après avoir vérifié que sNonNull n'est pas pointeur NULL
	assert(sNonNull!=NULL);
	char *sCopie=sMalloC(nChaineLg(sNonNull));
	ChaineCopier0(sNonNull,sCopie);
	MallocGereR(sCopie);
	return(sCopie);
}//sC1

char *sC1p(const char *sA){
	//concatène sA et "."
	assert(sA!=0);
	char *sAccu=sC2(sA,".");
	return(sAccu);
}//sC1p

char *sC2(const char *sA,const char *sB){
	//concatène sA et sB
	Assert2("routine sC2",sA!=0,sB!=0);
	int nRequis=nChaineLg(sA)+nChaineLg(sB);
	char *sAccu=sMalloC(nRequis);
		strcpy(sAccu,sA);
		strcat(sAccu,sB);
	MallocGereR(sAccu);
	return(sAccu);
}//sC2

char *sC2b(const char *sA,const char *sB){
	//concatène sA à sB,avec un blanc intercalé si sA et sB sont de longueur non nulle
	Assert2("routine sC2b",sA!=0,sB!=0);
	int bBlancEnSus=(nChaineLg(sA)>0) && (nChaineLg(sB)>0);
	int nRequis=nChaineLg(sA)+bBlancEnSus+nChaineLg(sB);
	assert(nRequis>=0);
	char *sAccu=sMalloC(nRequis);
		strcpy(sAccu,sA);
		if (bBlancEnSus)
			strcat(sAccu," ");
		strcat(sAccu,sB);
	MallocGereR(sAccu);
	return(sAccu);
}//sC2b

char *sC2bp(const char *sA,const char *sB){
	//concatène sA,sB et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC2b(sA,sB),".");//sC2b vérifie que sA et sB sont définis
	return(sAccu);
}//sC3bp

char *sC2p(const char *sA,const char *sB){
	//concatène sA,sB et "."
	char *sAccu=sC2(sC2(sA,sB),".");//sC2 vérifie que sA et sB sont définis
	return(sAccu);
}//sC2p

char *sC2v(const char *sA,const char *sB){
	//concatène sA à sB,avec une virgule intercalée si sA et sB sont de longueur non nulle
	int bVirguleEnSus,nRequis;
	char *sAccu;
	Assert2("routine sC2v",sA!=0,sB!=0);
	nRequis=nChaineLg(sA)+nChaineLg(sB);
	assert(nRequis>=0);
	bVirguleEnSus=(nChaineLg(sA)>0) && (nChaineLg(sB)>0);
	if (bVirguleEnSus)
		nRequis++;
	sAccu=sMalloC(nRequis);
		strcpy(sAccu,sA);
		if (bVirguleEnSus)
			strcat(sAccu,",");
		strcat(sAccu,sB);
	MallocGereR(sAccu);
	return(sAccu);
}//sC2v

char *sC3(const char *sA,const char *sB,const char *sC){
	//concatène sA,sB et sC
	char *sAccu=sC2(sC2(sA,sB),sC);//sC2 vérifie que les arguments sont définis
	return(sAccu);
}//sC3

char *sC3b(const char *sA,const char *sB,const char *sC){
	//concatène sA,sB et sC en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC2b(sA,sB),sC);//sC2 vérifie que les arguments sont définis
	return(sAccu);
}//sC3b

char *sC3bp(const char *sA,const char *sB,const char *sC){
	//concatène sA,sB,sC et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC3b(sA,sB,sC),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC3bp

char *sC3p(const char *sA,const char *sB,const char *sC){
	//concatène sA,sB,sC et "."
	char *sAccu=sC4(sA,sB,sC, ".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC3p

char *sC3v(const char *sA,const char *sB,const char *sC){
	//concatène sA,sB et sC en séparant les données de longueur non nulle par des virgules
	char *sAccu=sC2v(sC2v(sA,sB),sC);//sC2 vérifie que les arguments sont définis
	return(sAccu);
}//sC3v

char *sC4(const char *sA,const char *sB,const char *sC,const char *sD){
	//concatène sA,sB,sC et sD
	char *sAccu=sC2(sC3(sA,sB,sC),sD);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4

char *sC4b(const char *sA,const char *sB,const char *sC,const char *sD){
	//concatène sA,sB,sC et sD en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC3b(sA,sB,sC),sD);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4b

char *sC4bp(const char *sA,const char *sB,const char *sC,const char *sD){
	//concatène sA,sB,sC,sD et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC4b(sA,sB,sC,sD),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4bp

char *sC4p(const char *sA,const char *sB,const char *sC,const char *sD){
	//concatène sA,sB,sC,sD et "."
	char *sAccu=sC2(sC4(sA,sB,sC,sD),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4p

char *sC4v(const char *sA,const char *sB,const char *sC,const char *sD){
	//concatène sA,sB,sC et sD en séparant les données de longueur non nulle par des virgules
	char *sAccu=sC2v(sC2v(sA,sB),sC2v(sC,sD));//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4v

char *sC5(const char *sA,const char *sB,const char *sC,const char *sD,const char *sE){
	//concatène sA,sB,sC,sD et sE
	char *sAccu=sC2(sC4(sA,sB,sC,sD),sE);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5

char *sC5b(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE){
	//concatène sA,sB,sC,sD et sE en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC4b(sA,sB,sC,sD),sE);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5b

char *sC5bp(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE){
	//concatène sA,sB,sC,sD,sE et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC5b(sA,sB,sC,sD,sE),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5bp

char *sC5p(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE){
	//concatène sA,sB,sC,sD,sE,sF et "."
	char *sAccu=sC2(sC5(sA,sB,sC,sD,sE),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5p

char *sC5v(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE){
	//concatène sA,sB,sC,sD et sE en séparant les données de longueur non nulle par des virgules
	char *sAccu=sC2v(sC2v(sA,sB),sC3v(sC,sD,sE));//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5v

char *sC6(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF){
	//concatène sA,sB,sC,sD,sE et sF
	char *sAccu=sC2(sC5(sA,sB,sC,sD,sE),sF);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6

char *sC6b(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF){
	//concatène sA,sB,sC,sD,sE et sF en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC5b(sA,sB,sC,sD,sE),sF);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6b

char *sC6bp(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF){
	//concatène sA,sB,sC,sD,sE,sF et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC6b(sA,sB,sC,sD,sE,sF),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6bp

char *sC6p(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF){
	//concatène sA,sB,sC,sD,sE,sF et "."
	char *sAccu=sC2(sC6(sA,sB,sC,sD,sE,sF),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6p

char *sC6v(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF){
	//concatène sA,sB,sC,sD,sE et sF en séparant les données de longueur non nulle par des virgules
	char *sAccu=sC2v(sC4v(sA,sB,sC,sD),sC2v(sE,sF));//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6v

char *sC7(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG){
	//concatène sA,sB,sC,sD,sE,sF et sG
	char *sAccu=sC2(sC6(sA,sB,sC,sD,sE,sF),sG);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7

char *sC7b(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG){
	//concatène sA,sB,sC,sD,sE,sF et sG en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC6b(sA,sB,sC,sD,sE,sF),sG);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7b

char *sC7bp(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG){
	//concatène sA,sB,sC,sD,sE,sF,sG et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC7b(sA,sB,sC,sD,sE,sF,sG),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7bp

char *sC7p(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG){
	//concatène sA,sB,sC,sD,sE,sF,sG et "."
	char *sAccu=sC2(sC7(sA,sB,sC,sD,sE,sF,sG),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7p

char *sC8(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG et sH
	char *sAccu=sC2(sC7(sA,sB,sC,sD,sE,sF,sG),sH);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8

char *sC8b(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG et sH en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC7b(sA,sB,sC,sD,sE,sF,sG),sH);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8b

char *sC8bp(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC8b(sA,sB,sC,sD,sE,sF,sG,sH),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8bp

char *sC8p(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH et "."
	char *sAccu=sC2(sC8(sA,sB,sC,sD,sE,sF,sG,sH),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8p

char *sC9(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH,const char  *sI){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH et sI
	char *sAccu=sC2(sC8(sA,sB,sC,sD,sE,sF,sG,sH),sI);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC9

char *sC9b(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH,const char  *sI){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH et sI en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC8b(sA,sB,sC,sD,sE,sF,sG,sH),sI);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC9b

char *sC9bp(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH,const char  *sI){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH,sI et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC9b(sA,sB,sC,sD,sE,sF,sG,sH,sI),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC9bp

char *sC9p(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH,const char  *sI){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH,sI et "."
	char *sAccu=sC2(sC9(sA,sB,sC,sD,sE,sF,sG,sH,sI),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC9p

int nCaractere(const char *ksTexte){
	//rend le nbre de caractères et blancs de ksTexte contrairt à strlen() et nChaineLg() qui renvoient le nbre de CODES caractères:strlen("à")=2.
	int nC,nCaractere=0;
	//Appel0("nCaractere");
		assert(ksTexte!=0);
		for (nC=0;nC<nChaineLg(ksTexte);nCaractere++,nC++)
			if ( !bAscii(ksTexte[nC]) )
				nC++;
		assert(nCaractere>=0);
	//Appel1("nCaractere");
	return(nCaractere);
}//nCaractere

void CaractereEchanger(char *pCar0,char *pCar1){
	char cCar;
	cCar=*pCar0;
	*pCar0=*pCar1;
	*pCar1=cCar;
}//CaractereEchanger

int bCarreh(int iValeur){
	int bCarreh=iValeur>=0 && nRac(iValeur)*nRac(iValeur)==iValeur;
	return(bCarreh);
}//bCarreh

int nCarreh(int iValeur){
	int nCarreh=iValeur*iValeur;
	Assert1("nCarreh",nCarreh>=0);
	return(nCarreh);
}//nCarreh


int nCas16(int bA,int bB,int bC,int bD){
	//rend 8*bA+4*bB+2*bC+bD dans 0..15,soit 16 cas
	Assert4("nCas16",bBool(bA),bBool(bB),bBool(bC),bBool(bD));
	int nCas16=8*bA+4*bB+2*bC+bD;
	return(nCas16);
}//nCas16

int nCas4(int bA,int bB){
	//rend 2*bA+bB dans 0..3,soit 4 cas
	Assert2("nCas4",bBool(bA),bBool(bB));
	int nCas4=2*bA+bB;
	return(nCas4);
}//nCas4

int nCas8(int bA,int bB,int bC){
	//rend 4*bA+2*bB+bC dans 0..7,soit 8 cas
	Assert3("nCas8",bBool(bA),bBool(bB),bBool(bC));
	int nCas8=4*bA+2*bB+bC;
	return(nCas8);
}//nCas8

char *sChainage(int nFois,char *sMotif){
	//rend sMotif dupliqué nFois
	char *sChainage;
	sChainage=sC1("");
	for (int uF=1;uF<=nFois;uF++)
		sChainage=sC2(sChainage,sMotif);
	return(sChainage);
}//sChainage

float fChaine(char *sChaine){
	//convertit sChaine en réel de type float;cache la fonction système atof()
	float fChaine;
	fChaine=atof(sChaine);
	//f(fChaine);
	return(fChaine);
}//fChaine

int iChaine(char *sChaine){
	//convertit sChaine en entier de type int;cache la fonction système atoi()
	int iChaine;
	iChaine=atoi(sChaine);
	//d(iChaine);
	return(iChaine);
}//iChaine

char *sChaine(char cCaractere){
	//convertit cCaractere en char *;synonyme de sC0()
	return(sC0(cCaractere));
}//sChaine

char *sChaine0(const char *ksTexte,int nLargeurHorsTout){
	//rend ksTexte cadré à droite sur nLargeurHorsTout caractères. Tronque la fin de ksTexte si trop grand.
	Assert11("sChaine0,nLargeurHorsTout",0<=nLargeurHorsTout,nLargeurHorsTout);
	char *sChen;
	int nBlanc,nC,nK,nCarLim,nOffset,nTexteLg;;
	nTexteLg=nCaractere(ksTexte);
	int nExtension=nChaineLg(ksTexte)-nTexteLg;
	sChen=sMalloC(nLargeurHorsTout+nExtension);
		nCarLim=iInf(nLargeurHorsTout,nTexteLg);
		nOffset=nLargeurHorsTout-nCarLim;
		for (nBlanc=0;nBlanc<nOffset;nBlanc++)
			sChen[nBlanc]=cChaineGarniR;
		for (nC=nK=0;nK<nCarLim;nC++,nK++){
			sChen[nOffset+nC]=ksTexte[nC];
			if (!bAscii(ksTexte[nC]))
				sChen[nOffset+(++nC)]=ksTexte[nC];
		}
		sChen[nOffset+nC]='\0';
	MallocGereR(sChen);
	if (nCaractere(sChen)!=nLargeurHorsTout)
		printf("ksTexte=%s et nLargeurHorsTout=%d et sChaine0=%s.\n",sG(ksTexte),nLargeurHorsTout,sG(sChen));
	Assert1("sChaine0 final",nCaractere(sChen)==nLargeurHorsTout);//? sinon,nChaineLg,tant pis
	return(sChen);
}//sChaine0

char *sChaine1(const char *ksTexte,int nLargeurHorsTout){
	//rend ksTexte cadré à gauche sur nLargeurHorsTout caractères. Tronque la fin de ksTexte si trop grand.
	Assert11("sChaine1,nLargeurHorsTout",0<=nLargeurHorsTout,nLargeurHorsTout);
	char *sChen;
	int nBlanc,nC,nK,nCarLim,nExtension,nTexteLg;
	nTexteLg=nCaractere(ksTexte);
	nExtension=nChaineLg(ksTexte)-nTexteLg;
	sChen=sMalloC(nLargeurHorsTout+nExtension);
		nCarLim=iInf(nLargeurHorsTout,nTexteLg);
		for (nC=nK=0;nK<nCarLim;nC++,nK++){
			sChen[nC]=ksTexte[nC];
			if (!bAscii(ksTexte[nC]))
				sChen[++nC]=ksTexte[nC];
		}
		for (nBlanc=0;nBlanc<nLargeurHorsTout-nCarLim;nBlanc++)
			sChen[nC+nBlanc]=cChaineGarniR;
		sChen[nC+nLargeurHorsTout-nCarLim]='\0';
	MallocGereR(sChen);
	if (nCaractere(sChen)!=nLargeurHorsTout)
		printf("ksTexte=%s et nLargeurHorsTout=%d et sChaine1=%s.\n",sG(ksTexte),nLargeurHorsTout,sG(sChen));
	Assert1("sChaine1 final",nCaractere(sChen)==nLargeurHorsTout);//? sinon,nChaineLg,tant pis
	return(sChen);
}//sChaine1

char *sChaine2(const char *ksTexte,int nLargeurHorsTout){
	//rend nLargeurHorsTout caractères contenant sTexte centré et entouré de blancs.
	Assert11("sChaine2,nLargeurHorsTout",0<=nLargeurHorsTout,nLargeurHorsTout);
	char *sChen;
	int nBlanc,nC,nK,nCarLim,nExtension,nMarge0,nMarge1,nTexteLg;
	nTexteLg=nCaractere(ksTexte);
	nExtension=nChaineLg(ksTexte)-nTexteLg;
	sChen=sMalloC(nLargeurHorsTout+nExtension);
		nCarLim=iInf(nLargeurHorsTout,nTexteLg);
		nMarge0=iSup(0,nLargeurHorsTout-nTexteLg)/2;
		for (nBlanc=0;nBlanc<nMarge0;nBlanc++)
			sChen[nBlanc]=cChaineGarniR;
		for (nC=nK=0;nK<nCarLim;nC++,nK++){
			sChen[nMarge0+nC]=ksTexte[nC];
			if (!bAscii(ksTexte[nC]))
				sChen[nMarge0+(++nC)]=ksTexte[nC];
		}
		nMarge1=nLargeurHorsTout-nCarLim-nMarge0;
		for (nBlanc=0;nBlanc<nMarge1;nBlanc++)
			sChen[nMarge0+nC+nBlanc]=cChaineGarniR;
		sChen[nMarge0+nC+nMarge1]='\0';
	MallocGereR(sChen);
	//s(ksTexte);for (nC=0;nC<nLargeurHorsTout+nExtension;nC++) if (sChen[nC]==' ') sChen[nC]='.';s(sChen);
	if (nCaractere(sChen)!=nLargeurHorsTout)
		printf("ksTexte=%s et nLargeurHorsTout=%d et sChen=%s.\n",sG(ksTexte),nLargeurHorsTout,sG(sChen));
	Assert1("sChaine2 final",nCaractere(sChen)==nLargeurHorsTout);//? sinon,nChaineLg,tant pis
	return(sChen);
}//sChaine2

char *sChainoN(const char *ksChaine,const int kiDebutInclus,const int kiFinIncluse){
	char *sChen;
	int nC,nD,nK,cPasse,nRequis;
	int iDebutInclus=yInf(kiDebutInclus,nCaractere(ksChaine));
	int iFinIncluse=yInf(kiFinIncluse,nCaractere(ksChaine));
	if ( bCroit(0,iDebutInclus,iFinIncluse) ){
	//sd2(ksChaine,iDebutInclus,iFinIncluse);
		for (cPasse=0;cPasse<=1;cPasse++){
			//if (cPasse==1) d(nRequis);
			if (cPasse==1) sChen=sMalloC(nRequis);
			for (nC=nD=nK=0;nK<nCaractere(ksChaine);nK++,nC++){
				if ( bCroit(iDebutInclus,nK,iFinIncluse) ){
					if (cPasse==1) sChen[nD++]=ksChaine[nC];
					if (!bAscii(ksChaine[nC])){
						nC++;
						if (cPasse==1) sChen[nD++]=ksChaine[nC];
					}
				}else if (!bAscii(ksChaine[nC]))
					nC++;
			}
			if (cPasse==1) sChen[nD]='\0';
			nRequis=nC;
		}
	}else {sChen=sMalloC(0);sChen[0]='\0';}
	MallocGereR(sChen);
	//sd2(sChen,iDebutInclus,iFinIncluse);
	return(sChen);
}//sChainoN

char *sChaine3(const char *ksTexte,int nLargeurHorsTout){
	//rend sTexte cadré à droite sur nLargeurHorsTout caractères. Abrège sTexte si trop grand.
	const char kcBref='!';
	Assert1("sChaine3",0<=nLargeurHorsTout);
	char *sChen;
	if (nLargeurHorsTout>0){
		int nC,nK,nCarMax,nTexteLg,nCopieLg;
		char sCopie[1+nChaineLg(ksTexte)];
		ChaineCopier0(ksTexte,sCopie);
		ChaineAbregeR(sCopie,nLargeurHorsTout);
		nCopieLg=nCaractere(sCopie);
		nCarMax=iInf(nLargeurHorsTout,nCopieLg);
		nTexteLg=nCaractere(ksTexte);
		if (nLargeurHorsTout==1)
			sChen=sC0(kcBref);
		else if (nCopieLg>nCarMax){
			sChen=sC3(sChainoN(ksTexte,0,nCarMax/2-1-bPair(nCarMax)),sC0(kcBref),sChainoN(ksTexte,nTexteLg-nCarMax/2,nTexteLg-1));
			Assert1("sChaine30 final",nCaractere(sChen)==nLargeurHorsTout);
		}else {
			int nExtension=nChaineLg(ksTexte)-nTexteLg;
			int nOffset=nLargeurHorsTout-nCarMax;
			sChen=sMalloC(nLargeurHorsTout+nExtension);
				for (nC=0;nC<nOffset;nC++)
					sChen[nC]=cChaineGarniR;
				for (nC=nK=0;nK<nCarMax;nK++,nC++){
					sChen[nOffset+nC]=sCopie[nC];
					if (!bAscii(sCopie[nC]))
						sChen[nOffset+(++nC)]=sCopie[nC];
				}
				sChen[nOffset+nC]='\0';
			MallocGereR(sChen);
		}
	}else sChen=sVide();
	Assert1("sChaine3 final",nCaractere(sChen)==nLargeurHorsTout);
	return(sChen);
}//sChaine3

int bChaineAbregE(char sTexteOriginal[]){
	//retire si possible un son voyelle de sTexteOriginal supposé SANS SIGNE DIACRITIQUE;rend vrai ssi succès
	int bAbrege,nC,nFin,mPos,uItem,nLg=nChaineLg(sTexteOriginal);
	char *sSonVoyelle="on,ain,ien,oin,oeu,eui,an,en,in,un,eu,a,e,i,o,u,y";//par ordre de suppression
	mPos=mItemPosition(sSonVoyelle,sTexteOriginal,&uItem);
	bAbrege=mPos>=0;
	//ds(0,sTexteOriginal);
	if (bAbrege){
		nFin=mPos+nChaineLg(sItem(sSonVoyelle,uItem));
		for (nC=0;nC<nLg;nC++){
			sTexteOriginal[mPos+nC]=sTexteOriginal[nFin+nC];
			if (!bAscii(sTexteOriginal[nFin+nC]))
				sTexteOriginal[mPos+(++nC)]=sTexteOriginal[nFin+nC];
			if (nFin+nC>nLg)//le '\0' vient d'être copié
				break;
		}
	}
	//ds(1,sTexteOriginal);
	return(bAbrege);
}//bChaineAbregE

void ChaineAbregeR(char sTexte[],int uLargeurHorsTout){
	int bAbreger=1;
	Assert1("ChaineAbregeR",uLargeurHorsTout>0);
	while (nCaractere(sTexte)>uLargeurHorsTout && bAbreger)
		bAbreger=bChaineAbregE(sTexte);
}//ChaineAbregeR

char *sChaineCopie(const char *ksSource){
	char *sCopie=sMalloC(nChaineLg(ksSource));
		ChaineCopier0(ksSource,sCopie);
	MallocGereR(sCopie);
	return(sCopie);
}//sChaineCopie

void ChaineCopier(const char *ksSource,int nSourceLg,char *sCible){
	//dédié strcpy avec contrôle espace disponible
	Assert1("ChaineCopier", bCroit(0,nSourceLg,nChaineLg(ksSource)) );
	for (int nC=0;nC<nSourceLg;nC++)
		sCible[nC]=ksSource[nC];
	sCible[nSourceLg]='\0';
}//ChaineCopier

void ChaineCopier0(const char *sSource,char *sCible){
	ChaineCopier(sSource,nChaineLg(sSource),sCible);
}//ChaineCopier0

void ChaineCopierTesteR(){
	char *sA;char acA[5]={'A','B','C','D','\0'};
	char *sB;char acB[1]={'\0'};
	Appel0("ChaineCopierTesteR");
		sA=sMalloC(5);
		ChaineCopier(acA,nChaineLg(acA),sA);
		s(sA);
		sB=sMalloC(1);
		ChaineCopier(acB,nChaineLg(acB),sB);
		s(sB);
	Appel1("ChaineCopierTesteR");
}//ChaineCopierTesteR

int bChaineDistincte(const char *ksTexte){
	int nC,nD,bDistincte=1;
	int nTexteLg=nChaineLg(ksTexte);
	for (nC=0;nC<nTexteLg-1;nC++)
		for (nD=nC+1;nD<nTexteLg;nD++)
			if (ksTexte[nC]==ksTexte[nD])
				bDistincte=0;
	return(bDistincte);
}//bChaineDistincte

char *sChaineEclate(char sTexteOriginal[],char cSeparateur){
	//rend les caractères de sTexteOriginal en intercalant par des cSeparateur.
	int nC,nLg=nChaineLg(sTexteOriginal);
	char *sTexteEclateh=sMalloC(2*nLg);
	for (nC=0;nC<nLg;nC++){
		sTexteEclateh[2*nC]=sTexteOriginal[nC];
		sTexteEclateh[2*nC+1]=(nC<nLg-1)? cSeparateur : '\0';
	}
	MallocGereR(sTexteEclateh);
	return(sTexteEclateh);
}//sChaineEclate

int bChaineEgale(char *sA,char *sB){
	int nC;
	int bEgale=nChaineLg(sA)==nChaineLg(sB);
	if (bEgale)
		for (nC=0;nC<nChaineLg(sA);nC++)
			bEgale=bEgale && sA[nC]==sB[nC];
	return(bEgale);
}//bChaineEgale

char *sChaineEtale(char *sChaine,int nEspaceEntreCaractere){
	//interpose nEspaceEntreCaractere blancs entre 2 caractères consécutifs de sChaine
	int nC,nD,uE;
	int nCarat;
	char *sEtale;
	int nRequis;
	//ss("sChaineEtale",sG(sChaine));
	Assert1("sChaineEtale 0",nEspaceEntreCaractere>=0);//chaque caractère est codé sur 1 ou 2 codes caractères (2 caractères pour un "é")
	nCarat=nChaineLg(sChaine);//compte aussi les kcExtensioN
	nRequis=(nCarat>0)? nCarat+nEspaceEntreCaractere*(nCarat-1): nCarat;//dc en excès:suppose 2 codes caractères par caractère
	//d3(nCarat,nCaractere(sChaine),nRequis);
	sEtale=sMalloC(nRequis);
		for (nD=0,nC=0;nC<nCarat;nC++){
			sEtale[nD++]=sChaine[nC];
			if (sChaine[nC]!=kcExtensioN)
				for (uE=1;nC+1<nCarat && uE<=nEspaceEntreCaractere;uE++)
					sEtale[nD++]=' ';
		}
		sEtale[nD]='\0';
		//d2(nD,nRequis);
		Assert1("sChaineEtale 1",nD<nRequis);
	MallocGereR(sEtale);
	return(sEtale);
}//sChaineEtale
 
char *sChaineEtale1(char *sChaine){
	return(sChaineEtale(sChaine,1));
}//sChaineEtale1

char *sChaineEtale2(char *sChaine){
	return(sChaineEtale(sChaine,2));
}//sChaineEtale2

void ChaineGarnir(char cImprimable){
	//change le caractère de remplissage utilisé dans les routines sChaine0,sChaine1 et sChaine2.
	Assert1("ChaineGarnir",bAffichable(cImprimable) );
	cChaineGarniR=cImprimable;
}//ChaineGarnir

void ChaineInverser(char *sChaine){
	//modifie sur place sChaine: "mais" donne "siam".
	int nLg=nChaineLg(sChaine);
	for (int nCar=0;nCar<nLg/2;nCar++)
		CaractereEchanger(&sChaine[nCar],&sChaine[nLg-1-nCar]);
}//ChaineInverser

int nChaineLg(const char *sTexte){
	//strlen(sTexte) dans [0..kuIntegerMax];supprime le message d'erreur du compilateur C qui exige une conversion explicite unsigned int -> int
	unsigned int uiLg=strlen(sTexte);
	Assert1("nChaineLg1",uiLg<=kuIntegerMax);
	int nLg=(int) uiLg;
	Assert1("nChaineLg2",nLg>=0);
	return(nLg);
}//nChaineLg

int mChainePos(char cQuoi,char *sDansQuoi){
	//rend le rang0 de cQuoi dans sDansQuoi, ou -1 si échec
	int nC;
	int mPos=-1;
	for (nC=0;nC<nChaineLg(sDansQuoi) && (mPos<0); nC++)
		if (cQuoi==sDansQuoi[nC])
			mPos=nC;
	return mPos;
}//mChainePos

int mChainePosition(const char *ksTexte,char cEnquis){
	//rend le rang10 du dernier caractère de ksTexte égal à cEnquis;rend 0 si échec.
	int nC,mPosition;
	for (mPosition=-1,nC=0;nC<nChaineLg(ksTexte);nC++)
		if ( ksTexte[nC]==cEnquis )
			mPosition=nC;
	return(mPosition);
}//mChainePosition

char *sChaineSubstituer(char *sChaine,char *sAvant,char *sApres){
	int mPos,nLg=nChaineLg(sChaine);
	int nOccurrence=nChainonEnTout(sAvant,sChaine);
	//d(nOccurrence);
	int iEcart=nOccurrence*(nChaineLg(sApres)-nChaineLg(sAvant));
	char *sSubstitut=sE(1+nLg+ySup(0,iEcart));//évite de gérer un sMalloC
	ChaineCopier(sChaine,nLg,sSubstitut);
	while ((mPos=mChainonPos(sAvant,sSubstitut))>=0){
		//m1 s(sSubstitut);d(mPos);s(sChainon0(sSubstitut,mPos-1));s(sApres);
		//s(sChainon1(sSubstitut,mPos+nChaineLg(sAvant)))
		sSubstitut=sC3(sChainon0(sSubstitut,mPos-1),sApres,sChainon(sSubstitut,mPos+nChaineLg(sAvant),nLg));
	}
	return(sSubstitut);
}//sChaineSubstituer

char *sChainon(const char *ksChaine,const int kiDebutInclus,const int kiFinIncluse){
	//rend ksChaine[kiDebutInclus,kiFinIncluse],ou une chaîne vide si non défini;kiFinIncluse peut dépasser la longueur de ksChaine
	int nC,nRequis;
	//d2(kiDebutInclus,kiFinIncluse);
	int iDebutInclus=yInf(kiDebutInclus,nChaineLg(ksChaine));
	int iFinIncluse=yInf(kiFinIncluse,nChaineLg(ksChaine));
	//d2(iDebutInclus,iFinIncluse);
	char *sChainon;
	if ( bCroit(0,iDebutInclus,iFinIncluse) )
		nRequis=iMax(0,iInf(iFinIncluse-iDebutInclus+1,nChaineLg(ksChaine)));
	else nRequis=0;
	sChainon=sMalloC(nRequis);
		for (nC=0;nC<nRequis;nC++)
			sChainon[nC]=ksChaine[iDebutInclus+nC];
		sChainon[nRequis]='\0';
	MallocGereR(sChainon);
	return sChainon;
}//sChainon
 
char *sChainon0(const char *sChaine,const int iFinIncluse){
	return sChainon(sChaine,0,iFinIncluse);
}//sChainon0

char *sChainon1(const char *sChaine,const int iDebutInclus){
	return sChainon(sChaine,iDebutInclus,nChaineLg(sChaine)-1);
}//sChainon1

int nChainonEnTout(char *sSousChaine,char *sChaine){
	//rend le nombre d'occurrences de sSousChaine dans sChaine
	int nLg=nChaineLg(sSousChaine);
	int nC,nChainonEnTout;
	for (nChainonEnTout=nC=0; nC<nChaineLg(sChaine)-nLg+1; nC++){
		if ( bChaineEgale(sSousChaine,sChainon(sChaine,nC,nC+nLg-1)) ){
			nChainonEnTout++;
			nC+=nLg-1;
		}
	}
	return nChainonEnTout;
}//nChainonEnTout

int mChainonPos(char *sSousChaine,char *sChaine){
	//rend le plus petit rang0 de sSousChaine dans sChaine, ou -1 si échec
	int nC;
	int nLg=nChaineLg(sSousChaine);
	int mPos=-1;
	for (nC=0; nC<nChaineLg(sChaine)-nLg+1 && (mPos<0); nC++){
		//ss(sSousChaine,sChainon(sChaine,nC,nC+nLg-1));
		if ( bChaineEgale(sSousChaine,sChainon(sChaine,nC,nC+nLg-1)) )
			mPos=nC;
	}
	return(mPos);
}//mChainonPos

int bChiffre(char cCaractere){
	//cCaractere est un chiffre décimal
	int bChiffre=bDecit(cCaractere);
	return(bChiffre);
}//bChiffre

char *sChoix(int bOptionSinonAlternative,char *sOption,char *sAlternative){
	//rend sOption si bOptionSinonAlternative est vrai; sinon,rend sAlternative.
	int nRequis;
	Assert2("sCoix",sOption!=0,sAlternative!=0);
	nRequis = bOptionSinonAlternative? nChaineLg(sOption) : nChaineLg(sAlternative);
	char *sCopie=sMalloC(nRequis);
		if (bOptionSinonAlternative)
			strcpy(sCopie,sOption);
		else strcpy(sCopie,sAlternative);
	MallocGereR(sCopie);
	return(sCopie);
}//sChoix

char *sChoix0(int bOption,char *sOption){
	//rend sOption si bOption est vrai;sinon,rend une chaîne vide. Synonyme: sChoix1()
	int nRequis;
	assert(sOption!=0);
	nRequis = bOption? nChaineLg(sOption) : 0;
	char *sCopie=sMalloC(nRequis);
		if (bOption)
			strcpy(sCopie,sOption);
		sCopie[nRequis]='\0';
	MallocGereR(sCopie);
	return(sCopie);
}//sChoix0

char *sChoix1(int bOption,char *sOption){
	//rend sOption si bOption est vrai;sinon,rend une chaîne vide. Synonyme: sChoix0()
	int nRequis;
	assert(sOption!=0);
	nRequis = bOption? nChaineLg(sOption) : 0;
	char *sCopie=sMalloC(nRequis);
		if (bOption)
			strcpy(sCopie,sOption);
		sCopie[nRequis]='\0';
	MallocGereR(sCopie);
	return(sCopie);
}//sChoix1

int nChoix2(int bCondition1,int bCondition2){
	//rend i si bCondition i est vérifiée, et 0 sinon
	int nChoix=0;
	if (bCondition1) nChoix=1;
	if (bCondition2) nChoix=2;
	return(nChoix);
}//nChoix3

int nChoix3(int bCondition1,int bCondition2,int bCondition3){
	//rend i si bCondition i est vérifiée, et 0 sinon
	int nChoix=0;
	if (bCondition1) nChoix=1;
	if (bCondition2) nChoix=2;
	if (bCondition3) nChoix=3;
	return(nChoix);
}//nChoix3

int nChoix4(int bCondition1,int bCondition2,int bCondition3,int bCondition4){
	//rend i si bCondition i est vérifiée, et 0 sinon
	int nChoix=0;
	if (bCondition1) nChoix=1;
	if (bCondition2) nChoix=2;
	if (bCondition3) nChoix=3;
	if (bCondition4) nChoix=4;
	return(nChoix);
}//nChoix3

void ChronoTesteR(){
	long zP,zQ;
	int nT;
	Appel0("ChronoTesteR");
		nT=nChrono(kV);
			for (zP=1;zP<kE4;zP++)
				zQ++;
		nT=nChrono(kF);
		printf("Durée exécution: %d.\n",nT);
	Appel1("ChronoTesteR");
}//ChronoTesteR

void Chrono(int bDemarrer,int *pnDuree){
	//pr chronométrer une exécution,l'encadrer avec Chrono(kV,&nT) et Chrono(kF,&nT); nT final donne la durée de l'exécution.
	if (bDemarrer) printf("Chronométrage en cours…\n");
	*pnDuree=nChrono(bDemarrer);
	if (!bDemarrer) printf("Chronométrage terminé.\n");
}//Chrono

int nChrono(int bDemarrer){
	//pr chronométrer une exécution,l'encadrer avec nT=nChrono(kV) et nT=nChrono(kF); nT final donne la durée de l'exécution.
	static int bChronoDemarrer=kF;
	static long zChronoDemarrer;
	FlipFlop("nChrono",bDemarrer,&bChronoDemarrer);
	int nChrono=0;
	if (bDemarrer)
		zChronoDemarrer=clock();
	else nChrono=clock()-zChronoDemarrer;
	//if (!bDemarrer) ld2(clock(),zChronoDemarrer);
	return(nChrono);
}//nChrono

long zChrono(int bDemarrer){
	//pr chronométrer une exécution,l'encadrer avec zT=zChrono(kV) et zT=nChrono(kF); zT final donne la durée de l'exécution.
	static int bChronoDemarrer=kF;
	static long zChronoDemarrer;
	FlipFlop("zChrono",bDemarrer,&bChronoDemarrer);
	long zChrono=0;
	if (bDemarrer)
		zChronoDemarrer=clock();
	else zChrono=clock()-zChronoDemarrer;
	return(zChrono);
}//zChrono

long zCnp(int nN,int nP){
	//rend le nombre de façons de prendre nP éléments parmi nN, ou 0 si non défini. 
	long zCnp=(nP>0 && nN>=nP)? xFact(nN)/( xFact(nP)*xFact(nN-nP) ) : 0;
	Assert1("zCnp",zCnp>=0);
	return(zCnp);
}//zCnp

int iComparateur(char *sComparateur){
	//rend parmi {<,≤,=,>,≥} le symbole de rang iRang.
	//s(sComparateur);
	int uItem=nItemPos("<,<=,=,>=,>,<>",sComparateur);
	//d(uItem);
	Assert1("iComparateur",uItem>0);
	return uItem-3;
}//iComparateur

char *sComparateur(int iRang){
	//rend parmi {<,≤,=,>,≥} le symbole de rang iRang.
	Assert1("sComparateur",bCroit(-2,iRang,+3));
	char *sComparateur=sItem("<,<=,=,>=,>,<>",3+iRang);
	return sComparateur;
}//sComparateur

void Confirmer(char *sMessage){
	char cCar;
	printf("%s Valider SVP (touche entrée)",sMessage);
	scanf("%c",&cCar);
	printf(" La validation a été enregistrée.\n");
}//Confirmer

int bConsonnE2(const char *ksTexte,int *pnCodeCaractereRg0){
	//ksTexte[*pnCodeCaractereRg0] ou Chaine[*pnCodeCaractereRg0..*pnCodeCaractereRg0+1] code une consonne;si vrai et 2 codes, passe au code suivant
	int nCar;
	char cCode;
    #define knConsonne1LiM 21
    #define knConsonne2LiM 04
	int nConsonne1[knConsonne1LiM]={64,65,66,67,69,70,71,73,74,75,76,77,79,80,81,82,83,85,86,87,89};//consonnes sans signe diacritique
	int nConsonne2[knConsonne2LiM]={79,89,111,121};//ççÑñ";
	int bConsonne2=0;
	Assert2("bConsonnE2a",ksTexte!=0,pnCodeCaractereRg0!=0);
	Assert1("bConsonnE2b",bCroit(0,2,nChaineLg(ksTexte)));
	Assert1("bConsonnE2c",bCroit(0,*pnCodeCaractereRg0,nChaineLg(ksTexte)));
	cCode=ksTexte[*pnCodeCaractereRg0];
	bConsonne2=isalpha(cCode);//consonne ou voyelle sans signe diacritique (accents,cédille,tilde...)
	if (bConsonne2){//consonne?
		assert(0);//ie code actuellt non exécuté vu le contexte des appels à bConsonnE2()
		for (bConsonne2=0,nCar=0; nCar<knConsonne1LiM; nCar++)
			bConsonne2=bConsonne2||(cCode==-nConsonne1[nCar]);
		}
	else if (*pnCodeCaractereRg0<nChaineLg(ksTexte)) {//l'accès à sTexte[nCodeCaractereRg+1] est valide
		if (cCode==kcEchappemenT1){
			cCode=ksTexte[*pnCodeCaractereRg0+1];
			for (nCar=0; nCar<knConsonne2LiM; nCar++)
				bConsonne2=bConsonne2||(cCode==-nConsonne2[nCar]);
			if (bConsonne2)
				(*pnCodeCaractereRg0)++;
		}
	}
	return(bConsonne2);
}//bConsonnE2

int bCopremier(int iA,int iB){
	//vrai ssi iA et iB sont premiers entre eux
	int bCopremier;
	Assert1("bCopremier",bKitAmorceR);
	bCopremier=zPgcd(iA,iB)==1;
	return(bCopremier);
}//bCopremier;

char cCoul(int ctCouleur){
	//convertit ctCouleur en caractère correspondant au type énuméré eCouleurType	
//#define CouleurType { coAlpha  ,coVert   ,coRouge  ,coBleu   ,coJaune  ,coOrange ,coViolet ,coNoir   ,coGris   ,coFacultF,coOmega   }
	char cCouleur[]={'z','v','r','b','j','o','w','n','g','f','s'};//zéro,vert,rouge,bleu,jaune,f=facultatif
	enum eKitCouleur CouleurType;
	Assert11("cCouleur,ctCouleur",bCroitStrict(coAlpha,ctCouleur,coOmega),ctCouleur);
	return(cCouleur[ctCouleur]);
}//cCoul

char *sCouple(long yEntierA,long yEntierB){
	//rend la chaîne "(yEntierA,yEntierB)"	
	char *sCouple=sMalloC(1+kuEntier23SizE+1+kuEntier23SizE+1);
		ChaineCopier0(sC5("(",sEnt(yEntierA),",",sEnt(yEntierB),")"),sCouple);
	MallocGereR(sCouple);
	return(sCouple);
}//sCouple

char *sCouple2(long yEntierA,long yEntierB){
	//rend la chaîne "(yEntierA,yEntierB)"	
	char *sCouple=sMalloC(1+kuEntier23SizE+1+kuEntier23SizE+1);
		ChaineCopier0(sC5("(",sEnt0(yEntierA,2),",",sEnt0(yEntierB,2),")"),sCouple);
	MallocGereR(sCouple);
	return(sCouple);
}//sCouple2

char *sCrochet(long yEntierA,long yEntierB){
	//rend la chaîne "[yEntierA,yEntierB]"	
	char *sCrochet=sMalloC(1+kuEntier23SizE+1+kuEntier23SizE+1);
		ChaineCopier0(sC5("[",sEnt(yEntierA),",",sEnt(yEntierB),"]"),sCrochet);
	MallocGereR(sCrochet);
	return(sCrochet);
}//sCrochet

char *sCrochet1(long yEntier){
	//rend "[yEntier]"	
	char *sCrochet1=sMalloC(1+kuEntier23SizE+1+kuEntier23SizE+1);
		ChaineCopier0(sC3("[",sEnt(yEntier),"]"),sCrochet1);
	MallocGereR(sCrochet1);
	return(sCrochet1);
}//sCrochet1

char *sCrochet2(long yEntierA,long yEntierB){
	//rend la chaîne "[yEntierA,yEntierB]";comme sCrochet.	
	char *sCrochet2=sMalloC(1+kuEntier23SizE+1+kuEntier23SizE+1);
		ChaineCopier0(sC5("[",sEnt(yEntierA),",",sEnt(yEntierB),"]"),sCrochet2);
	MallocGereR(sCrochet2);
	return(sCrochet2);
}//sCrochet2

char *sCrochet3(long yEntierA,long yEntierB,long yEntierC){
	//rend la chaîne "[yEntierA,yEntierB,yEntierC]"	
	char *sCrochet3=sMalloC(1+kuEntier23SizE+1+kuEntier23SizE+1+kuEntier23SizE+1);
		ChaineCopier0(sC7("[",sEnt(yEntierA),",",sEnt(yEntierB),",",sEnt(yEntierC),"]"),sCrochet3);
	MallocGereR(sCrochet3);
	return(sCrochet3);
}//sCrochet3

void Croissant(double dMinInclus,double dDedans,double dMaxInclus){
	if (!bCroissant(dMinInclus,dDedans,dMaxInclus))
		printf("BUG ds bCroissant():%lf≤%lf≤%lf est FAUX\n",dMinInclus,dDedans,dMaxInclus);
	assert(bCroissant(dMinInclus,dDedans,dMaxInclus));
}//Croissant

int bCroissant(double dMinInclus,double dDedans,double dMaxInclus){
	int bCroissant=(dMinInclus<=dDedans) && (dDedans<=dMaxInclus);
	return(bCroissant);
}//bCroissant

int bCroissantStrict(double dMinExclu,double dDedans,double dMaxExclu){
	int bCroissantStrict=(dMinExclu<dDedans) && (dDedans<dMaxExclu);
	return(bCroissantStrict);
}//bCroissantStrict

void CroissantStrict(double dMinExclu,double dDedans,double dMaxExclu){
	if (!bCroissantStrict(dMinExclu,dDedans,dMaxExclu))
		printf("BUG ds bCroissantStrict():%lf<%lf<%lf est FAUX\n",dMinExclu,dDedans,dMaxExclu);
	assert(bCroissantStrict(dMinExclu,dDedans,dMaxExclu));
}//CroissantStrict

int bCroit(long yMinInclus,long yDedans,long yMaxInclus){
	int bCroit=(yMinInclus<=yDedans) && (yDedans<=yMaxInclus);
	return(bCroit);
}//bCroit

int bCroit4(long yA,long yB,long yC,long yD){//rend yA≤yB≤yC≤yD
	int bCroit4=bCroit(yA,yB,yC) && (yC<=yD);
	return(bCroit4);
}//bCroit4

int bCroitStrict6(long yA,long yB,long yC,long yD,long yE,long yF){//rend yA<yB<yC...<yF
	int bCroitStrict6=bCroitStrict4(yA,yB,yC,yD) && bCroitStrict(yD,yE,yF);
	return(bCroitStrict6);
}//bCroitStrict6

int bCroitStrict8(long yA,long yB,long yC,long yD,long yE,long yF,long yG,long yH){//rend yA<yB<yC...<yH
	int bCroitStrict8=bCroitStrict4(yA,yB,yC,yD) && (yD<yE) && bCroitStrict4(yE,yF,yG,yH);
	return(bCroitStrict8);
}//bCroitStrict8

int bCroitStrict(long yMinExclu,long yDedans,long yMaxExclu){
	int bCroitStrict=(yMinExclu<yDedans) && (yDedans<yMaxExclu);
	return(bCroitStrict);
}//bCroit

int bCroitStrict4(long yA,long yB,long yC,long yD){//rend yA<yB<yC<yD
	int bCroitStrict4=bCroitStrict(yA,yB,yC) && (yC<yD);
	return(bCroitStrict4);
}//bCroitStrict4

int iCube(int iValeur){
	int iCube=iValeur*iValeur*iValeur;
	return(iCube);
}//iCube

char *sD1(char *sA,int iIndex){
	//renvoie sA[iIndex]
	return(sC2(sA,sC(sPar3(iIndex))));
}//sD1

char *sD2(char *sA,int iIndexMin,int iIndexMax){
	//renvoie sA[iIndexMin,iIndexMax]
	return( sC2(sA,sC(sC2v(sPar3(iIndexMin),sPar3(iIndexMax)))) );
}//sD2

int bDans1(int iQuoi,int iValeur){
	//pr prolonger bDans2 et suivants
	int bDans1=(iQuoi==iValeur);
	return(bDans1);
}//bDans1

int bDans2(int iQuoi,int iValeurA,int iValeurB){
	int bDans2=(iQuoi==iValeurA) || (iQuoi==iValeurB);
	return(bDans2);
}//bDans2

int bDans3(int iQuoi,int iValeurA,int iValeurB,int iValeurC){
	int bDans3=(iQuoi==iValeurA) || (iQuoi==iValeurB) || (iQuoi==iValeurC);
	return(bDans3);
}//bDans3

int bDans4(int iQuoi,int iValeurA,int iValeurB,int iValeurC,int iValeurD){
	int bDans4=(iQuoi==iValeurA) || (iQuoi==iValeurB) || (iQuoi==iValeurC) || (iQuoi==iValeurD);
	return(bDans4);
}//bDans4

int bDans5(int iQuoi,int iValeurA,int iValeurB,int iValeurC,int iValeurD,int iValeurE){
	int bDans5=(iQuoi==iValeurA) || (iQuoi==iValeurB) || (iQuoi==iValeurC) || (iQuoi==iValeurD) || (iQuoi==iValeurE);
	return(bDans5);
}//bDans5

int bDans6(int iQuoi,int iValeurA,int iValeurB,int iValeurC,int iValeurD,int iValeurE,int iValeurF){
	int bDans6=(iQuoi==iValeurA) || (iQuoi==iValeurB) || (iQuoi==iValeurC) || (iQuoi==iValeurD) || (iQuoi==iValeurE) || (iQuoi==iValeurF);
	return(bDans6);
}//bDans6

int bDans7(int iQuoi,int iValeurA,int iValeurB,int iValeurC,int iValeurD,int iValeurE,int iValeurF,int iValeurG){
	int bDans7=(iQuoi==iValeurA) || (iQuoi==iValeurB) || (iQuoi==iValeurC) || (iQuoi==iValeurD) || (iQuoi==iValeurE) || (iQuoi==iValeurF) || (iQuoi==iValeurG);
	return(bDans7);
}//bDans7

int bDans8(int iQuoi,int iValeurA,int iValeurB,int iValeurC,int iValeurD,int iValeurE,int iValeurF,int iValeurG,int iValeurH){
	int bDans8=(iQuoi==iValeurA) || (iQuoi==iValeurB) || (iQuoi==iValeurC) || (iQuoi==iValeurD) || (iQuoi==iValeurE) || (iQuoi==iValeurF) || (iQuoi==iValeurG) || (iQuoi==iValeurH);
	return(bDans8);
}//bDans8

int bDans9(int iQuoi,int iValeurA,int iValeurB,int iValeurC,int iValeurD,int iValeurE,int iValeurF,int iValeurG,int iValeurH,int iValeurI){
	int bDans9=(iQuoi==iValeurA) || (iQuoi==iValeurB) || (iQuoi==iValeurC) || (iQuoi==iValeurD) || (iQuoi==iValeurE) || (iQuoi==iValeurF) || (iQuoi==iValeurG) || (iQuoi==iValeurH) || (iQuoi==iValeurI);
	return(bDans9);
}//bDans8

char *sDateEnClair(int nQuantieme,int nMois,int nAnnee){
	//années 1900 à 2100
	int nJour;
	char *sEnClair;
	char *sSemaine="dimanche,lundi,mardi,mercredi,jeudi,vendredi,samedi";
	char *sMois="janvier,février,mars,avril,mai,juin,juillet,août,septembre,octobre,novembre,décembre";
	nJour=nJourSemaine(nQuantieme,nMois,nAnnee);
	sEnClair=sC8(sItem(sSemaine,nJour)," ",sEnt(nQuantieme),(nQuantieme==1)?"er":""," ",sItem(sMois,nMois)," ",sEnt(nAnnee));
	return(sEnClair);
}//sDateEnClair

int bDecimal(int iEntier){
	//iEntier est un chiffre décimal
	int bDecimal=bCroit(0,iEntier,9);
	return(bDecimal);
}//bDecimal

int bDecit(char cCaractere){
	//cCaractere est un chiffre décimal;cache la fonction isdigit()
	int bDecit=isdigit(cCaractere);
	return(bDecit);
}//bDecit

int nDecit(int iValeur){
	//rend l'encombrement de iValeur, en nombre de caractères à afficher
	int nDecit,nValeur=abs(iValeur);
	nDecit=(nValeur>9)? nLog10(nValeur-1) : 1;
	nDecit+=iValeur<0;
	return(nDecit);
}//nDecit

char *sDire(int bAffirmation,char *sVerbePuisBlancPuisQqch){
	//rend sVerbePuisBlancPuisQqch,ou nié si !bAffirmation: sDire(0,"est rouge")="n'est pas rouge".
	enum {diAlpha,diN,diNe,diPas,diOmega};
	char *sLexique="n',ne ,pas ";
	const int kuNeLg=iSup(nChaineLg(sItem(sLexique,diN)),nChaineLg(sItem(sLexique,diNe)));//"n'" ou "ne ", dc 3 ds le pire cas
	const int kuPasLg=nChaineLg(sItem(sLexique,diPas));
	int mBlancPos;
	char sNon[1+kuNeLg];
	char cBlanc=' ';
	char *sDire=sMalloC(kuNeLg+nChaineLg(sVerbePuisBlancPuisQqch)+kuPasLg);
		mBlancPos=mChainePos(cBlanc,sVerbePuisBlancPuisQqch);
		Assert1("sDire: un blanc est attendu après le verbe",mBlancPos>0);
		if (!bAffirmation){
			strcpy(sNon,sItem(sLexique,(bVoyelle(sVerbePuisBlancPuisQqch,0))? diN : diNe ) );
			strcpy(sDire,sNon);
			strcat(sDire,sChainon0(sVerbePuisBlancPuisQqch,mBlancPos));
			strcat(sDire,sItem(sLexique,diPas));
			strcat(sDire,sChainon1(sVerbePuisBlancPuisQqch,mBlancPos+1));
		} else strcpy(sDire,sVerbePuisBlancPuisQqch);
	MallocGereR(sDire);
	return(sDire);
}//sDire

char *sDire1(int bAffirmation,char *sVerbePuisUnOuUnePuisQqch){
	//rend sVerbePuisUnOuUnePuisQqch,ou nié si !bAffirmation: sDire1(0,"a une couleur")="n'a pas de couleur".
	char *sLexique="n',ne ,pas de ,e";
	enum {diAlpha,diN,diNe,diPas,diFeminin,diOmega};
	const int kuNeLg=iSup(nChaineLg(sItem(sLexique,diN)),nChaineLg(sItem(sLexique,diNe)));//"n'" ou "ne ", dc 3 ds le pire cas
	const int kuPasDeLg=nChaineLg(sItem(sLexique,diPas));
	int bFeminin,mUnPos;
	char sNon[1+kuNeLg];
	char *sUn=" un";
	char *sDire1=sMalloC(kuNeLg+nChaineLg(sVerbePuisUnOuUnePuisQqch)+kuPasDeLg);
		mUnPos=mChainonPos(sUn,sVerbePuisUnOuUnePuisQqch);
		Assert1("sDire1: <un> ou <une> est attendu après le verbe",mUnPos>0);
		if (!bAffirmation){
			strcpy(sNon,sItem(sLexique,(bVoyelle(sVerbePuisUnOuUnePuisQqch,0))? diN : diNe ) );
			strcpy(sDire1,sNon);
			strcat(sDire1,sChainon0(sVerbePuisUnOuUnePuisQqch,mUnPos));
			strcat(sDire1,sItem(sLexique,diPas));
			bFeminin=mChainonPos(sItem(sLexique,diFeminin),sChainon1(sVerbePuisUnOuUnePuisQqch,mUnPos))==nChaineLg(sUn);
			strcat(sDire1,sChainon1(sVerbePuisUnOuUnePuisQqch,mUnPos+nChaineLg(sUn)+bFeminin+1));
		} else strcpy(sDire1,sVerbePuisUnOuUnePuisQqch);
	MallocGereR(sDire1);
	return(sDire1);
}//sDire1

int bDistinct3(long yA,long yB,long yC){
	int bDistinct3= yA!=yB && yA!=yC && yB!=yC;
	return(bDistinct3);
}//bDistinct3

int bDistinct4(long yA,long yB,long yC,long yD){
	int bDistinct4= yA!=yB && yA!=yC && yA!=yD;
	bDistinct4=bDistinct4 && yB!=yC && yB!=yD;
	bDistinct4=bDistinct4 && yC!=yD;
	return(bDistinct4);
}//bDistinct4

double dDiv(int nNumerateur,int nDenominateur){
	//rend la division de nNumerateur/nDenominateur.
	Assert1("dDiv",nDenominateur);
	double dDiv=nNumerateur/(1.0*nDenominateur);
	return(dDiv);
}//dDiv

float fDiv(int nNumerateur,int nDenominateur){
	//rend la division de nNumerateur/nDenominateur.
	Assert1("fDiv",nDenominateur);
	float fDiv=nNumerateur/(1.0*nDenominateur);
	return(fDiv);
}//fDiv

q qDiv(q qA,q qB){
	//division de deux rationnels:qA/qB
	q qInverse;
	q qDiv;
	Assert3("qDiv",qA.den>0,qB.den>0,qB.num!=0);
	qInverse.den=qB.num;
	qInverse.num=qB.den;
	qDiv=qMul(qA,qInverse);
	return(qDiv);
}//qDiv

char *sDiv(int nNumerateur,int nDenominateur){
	//rend la division de nNumerateur/nDenominateur avec deux décimales.
	const int kuRequis=20;
	const int kbVirguler=0;
	int uC;
	char *sDiv=sMalloC(kuRequis);
		sDiv[0]='\0';
		if (nDenominateur==0)
			if (nNumerateur==0)
				strcat(sDiv,"indéterminé");
			else strcat(sDiv,"infini");
		else sprintf(sDiv,"%.2f",nNumerateur/(nDenominateur*1.0));
		if (kbVirguler)//remplacer le point par une virgule
			for (uC=1;uC<=nChaineLg(sDiv);uC++)
				if (sDiv[uC]=='.')
					sDiv[uC]=',';
	MallocGereR(sDiv);
	return(sDiv);
}//sDiv

char *sDomaine(long yEntierA,long yEntierB){
	//rend la chaîne "[yEntierA..yEntierB]"	
	char *sDomaine=sMalloC(1+kuEntier23SizE+2+kuEntier23SizE+1);
		strcpy(sDomaine,sC5("[",sPar3(yEntierA),"..",sPar3(yEntierB),"]"));
	MallocGereR(sDomaine);
	return(sDomaine);
}//sDomaine

float fEcartType(float fListe[]){
	//rend la moyenne arithmétique des entiers stockés dans fListe[0..fListe[0]]
	int uIndex;
	float fEcartType,fSomme,fMoyenne=fEsperance(fListe);
	Assert1("fEsperance",fListe[0]>0);
	//fSomme:=somme de carrés des écarts
		for (fSomme=0.0,uIndex=1;uIndex<=fListe[0];uIndex++)
			fSomme+=(fListe[uIndex]-fMoyenne)*(fListe[uIndex]-fMoyenne);
	fEcartType=sqrt(fSomme/fListe[0]);
	return(fEcartType);
}//fEcartType

int bEgal3(long yA,long yB,long yC){
	int bEgal3=(yA==yB && yB==yC);
	return(bEgal3);
}//bEgal3

char *sE(int iEspace){
	//rend sup(0,iEspace) blancs consécutifs
	char *sE=sFois(iSup(0,iEspace),' ');//sFois a appelé MallocGereR()
	return(sE);
}//sE

char *sEnt(long yEntier){
	//convertit yEntier en chaîne de chiffres décimaux, ou en code caractere si bModeCaractere().
	int bCaractere=bModeCaractere() && bCroit(1,yEntier,kuModeCaractereMax);
	int bPar3=!bCaractere && bModeChiffre();
	int bAllouer=bCaractere || !bPar3;
	char *sEnt;
	//if (!bAllouer) bb(bAllouer,bPar3);
	if (bAllouer) sEnt=sMalloC((bCaractere)? 1 : kuEntier23SizE);//23+1=24 octets
		if (bCaractere){//convertir l'entier en un caractère pris ds la séquence de rang1 A-Za-z…
			Assert1("sEnt",bCroit(1,yEntier,kuModeCaractereMax));
			int iEntier=icModeCaracterE[yEntier];
			char cEntier='@'+iEntier;
			sprintf(sEnt,"%c",cEntier);
		}else if (bPar3)
			sEnt=sPar3(yEntier);//alloue et appelle lui-mm MallocGereR sur un bloc dont la taille peut dépasser celle du sMalloC ci-dessus
		else sprintf(sEnt,"%ld",yEntier);//yEntier tient forcément ds sEnt vu allocation généreuse: kuEntier23SizE octets alloués là où 21 suffisent.
	if (bAllouer) MallocGereR(sEnt);
	return(sEnt);
}//sEnt

char *sEnt0(long yValeur,int nCaractere){
	//rend yValeur cadré à droite sur nCaractere caractères puis remplace les blancs à gauche par des zéros
	Assert1("sEnt0",nCaractere>0); 
	int nEntLg=nChaineLg(sEnt(yValeur));
	return(sC2(sZ(iSup(0,nCaractere-nEntLg)),sEnt(yValeur)));
}//sEnt2

char *sEnt00(long yValeur,int nCaractere,int nMargeDroite){
	//sEnt0(yValeur,nCaractere-nMargeDroite) suivi de nMargeDroite blancs à droite
	Assert2("sEnt00",nCaractere>0,nMargeDroite>=0); 
	return(sC2(sEnt0(yValeur,nCaractere-nMargeDroite),sE(nMargeDroite)));
}//sEnt00

char *sEnt1(long yValeur,int nCaractere){
	//rend yValeur cadré à droite sur nCaractere caractères
	Assert1("sEnt1",nCaractere>0); 
	int nEntLg=nChaineLg(sEnt(yValeur));
	return(sC2(sE(iSup(0,nCaractere-nEntLg)),sEnt(yValeur)));
}//sEnt1

char *sEnt10(long yValeur,int nCaractere,int nMargeDroite){
	//sEnt1(yValeur,nCaractere-nMargeDroite) suivi de nMargeDroite blancs à droite
	Assert2("sEnt10",nCaractere>0,nMargeDroite>=0); 
	return(sC2(sEnt1(yValeur,nCaractere-nMargeDroite),sE(nMargeDroite)));
}//sEnt10

char *sEnt2(long yEntier,int nCaractere){
	//convertit yEntier en caractère (1 donne A) ou en chaîne de chiffres décimaux groupée par paquets de 3 décits et cadre à droite.
	char *sEnt2=(nCaractere>0)? sEnt3(yEntier,nCaractere): sEnt(yEntier);
	return(sEnt2);
}//sEnt2

char *sEnt3(long yEntier,int nCaractere){
	//convertit yEntier en chaîne de chiffres décimaux groupée par paquets de 3 décits et cadre à droite.
	//s(sPar3(yEntier));
	char *sEnt3=sChaine0(sPar3(yEntier),nCaractere);
	return(sEnt3);
}//sEnt3

char *sEnt30(long yEntier,int nCaractere){
	//convertit yEntier en chaîne de chiffres décimaux groupée par paquets de 3 décits, cadre à droite puis zérote les blancs à gauche.
	int nC,nEntierLg,nZeroLg;
	char *sEnt03,*sEnt30,*sZero;
	sEnt03=sPar3(yEntier);
	nEntierLg=nChaineLg(sEnt03);
	sZero=sZ(nCaractere);
	if ( !nModulo(nEntierLg-3,4) )
		sZero=sC2(sZero,"0");
	nZeroLg=nChaineLg(sZero);
	sZero=sChainon1(sZero,nZeroLg-nCaractere);
	sEnt30=sC2(sChainon1(sZero,nEntierLg),sEnt03);
	for (nC=0;nC<nCaractere-nEntierLg;nC++)
		if (!nModulo(nCaractere-nC,4))
			sEnt30[nC]=' ';
	//sd3(sEnt30,nChaineLg(sEnt30),nCaractere,yEntier);
	//Assert1("sEnt30",nChaineLg(sEnt30)==nCaractere);
	return(sEnt30);
}//sEnt30

int bEntier(double dNombre){
	//vrai ssi dNombre est assimilable à un entier de type longint
	long yNombre=yArrondi(dNombre);
	int bEntier=bReelEgal(yNombre*1.0,dNombre);
	return(bEntier);
}//bEntier

int iEntier(char *sEntierAvecOuSansSigne){//convertit sEntierAvecOuSansSigne en entier
	long yEnt=yEntier(sEntierAvecOuSansSigne);
	int bValide=bCroit(kiIntegerMin,yEnt,kuIntegerMax);
	//printf("sEntierAvecOuSansSigne=%s,",sEntierAvecOuSansSigne);printf("yEnt=%ld,",yEnt);printf(",bValide=%d.\n",bValide);
	int mEntier=(bValide)? yEnt : kiIntegerMin;
	return(mEntier);
}//iEntier

long yEntier(char *sEntierAvecOuSansSigne){
	//blancs non significatifs avant l'entier, et signe facultatif.
	const int kuBaseDix=10;
	int nC,nDebut,bBlanc,nDecit,mEntier,bSigne,bValide;
	int nCarMax=nChaineLg(sEntierAvecOuSansSigne);
	for (bBlanc=1,bSigne=0,nDebut=nC=0;nC<nCarMax && bBlanc;nC++){
		bBlanc=sEntierAvecOuSansSigne[nC]==' ';
		bSigne=(sEntierAvecOuSansSigne[nC]=='+') || (sEntierAvecOuSansSigne[nC]=='-');
		if (bSigne)
			nDebut=nC;
	}
	for (bValide=1,mEntier=0,nC=nDebut;nC+bSigne<nCarMax;nC++){
		if (sEntierAvecOuSansSigne[nC+bSigne]!=' '){
			nDecit=sEntierAvecOuSansSigne[nC+bSigne]-'0';
			bValide=bValide && bCroit(0,nDecit,kuBaseDix-1);
			mEntier=mEntier*kuBaseDix+nDecit;
		}
		//d4(nDecit,uBase,bValide,mEntier);
	}
	mEntier=ySignePres(sEntierAvecOuSansSigne[nDebut]=='-',mEntier);
	if (!bValide)
		return(kyLongintMin);
	return(mEntier);
}//yEntier

char *sEntier(long yEntier,int nCaractere){
	//convertit yEntier en chaîne de nCaractere chiffres décimaux,quitte à ajouter des blancs à gauche et à tronquer si trop de chiffres.
	Assert1("sEntier",bCroit(0,nCaractere,kuEntier23SizE));
	char *sEntier=sMalloC(kuEntier23SizE);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
		sprintf(sEntier,"%23ld",yEntier);
		//cadrer à droite sur nCaractere caractères.
			int nOffset=(23+1)-nCaractere-1;//écart=différence des sizeof; et -1 pr indexer en rang0
			for (int nC=0;nC<nCaractere;nC++)
				sEntier[nC]=sEntier[nOffset+nC];
			sEntier[nCaractere]='\0';
	if (0) for (int nC=0;nC<nCaractere;nC++)
		if (!isdigit(sEntier[nC]))
			sEntier[nC]='.';//remplace les blancs mais aussi le signe "-" éventuel.
	MallocGereR(sEntier);
	return(sEntier);
}//sEntier

char *sEntier0(long yEntier,int nCaractere){
	//convertit yEntier en chaîne de nCaractere chiffres décimaux exactement,quitte à ajouter des zéros à gauche et à tronquer si trop de chiffres.
	Assert1("sEntier0",bCroit(0,nCaractere,kuEntier23SizE));
	//printf("@@@ APPEL de sEntier0.\n",sEntier0);/**/
	char *sEntier0=(nCaractere>0)? sEntier(yEntier,nCaractere) : sEnt(yEntier);//rend une suite de décits précédés de blancs et d'un signe "-" éventuels
	for (int nC=0;nC<nCaractere;nC++)
		if (!isdigit(sEntier0[nC]))
			sEntier0[nC]='0';//remplace les blancs mais aussi le signe "-" éventuel.
	if (yEntier<0)
		sEntier0[0]='-';
	return(sEntier0);
}//sEntier0

char *sEntier1(long yEntier,int nCaractere){
	//convertit yEntier en chaîne sPar3 centrée de nCaractere chiffres décimaux exactement.
	Assert1("sEntier1",bCroit(0,nCaractere,kuEntier23SizE));
	int nC,nMarge;
	char *sEnt3=sPar3(yEntier);
	char *sEntier1;
	//d(nCaractere);tt("sEnt3",sEnt3);
	nMarge=(nCaractere-nChaineLg(sEnt3))/2;
	//d(nMarge);
	sEntier1=sE(nCaractere);//d
	for (nC=0;nC<nChaineLg(sEnt3);nC++)
		sEntier1[nMarge+nC]=sEnt3[nC];
	return(sEntier1);
}//sEntier1

char *sEntier2(long yEntier){
	//convertit yEntier en chaîne de 2 chiffres décimaux: 24 donne "24", -5 donne "-5".
	char *sEntier2=sMalloC(kuEntier23SizE);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
		sprintf(sEntier2,"%2ld",yEntier);//yEntier tient forcément ds sEntier2 vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	MallocGereR(sEntier2);
	return(sEntier2);
}//sEntier2

char *sEntier3(long yEntier){
	//convertit yEntier en chaîne de 3 chiffres décimaux: 24 donne "24", -5 donne "-5".
	char *sEntier3=sMalloC(kuEntier23SizE);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
		sprintf(sEntier3,"%2ld",yEntier);//yEntier tient forcément ds sEntier3 vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	MallocGereR(sEntier3);
	return(sEntier3);
}//sEntier3

char *sEntierCourt(int iPoids){
	//traduit iPoids en chaîne de caractR concise (dédiée expresO algébrQ): "" pour +1, "-" pour -1, le reste est normal.
	char *sBref=sMalloC(1+kuEntier23SizE);
	char sPoids[1+kuEntier23SizE];
	int nC=0,uP,nPoids=abs(iPoids);
	sBref[nC++]=(iPoids<0)? '-': '+';//signe présent par défaut
	if (abs(iPoids)!=1)
		for (sprintf(sPoids,"%d",nPoids),uP=0;uP<nChaineLg(sPoids);uP++)
			sBref[nC++]=sPoids[uP];
	sBref[nC]='\0';
	return(sBref);
}//sEntierCourt

void EntierDepiler(int *piA){
	Assert1("EntierDepiler",ipEntierPilE>0);
	//d(ipEntierPilE-1);
	*piA=iEntierPilE[--ipEntierPilE];
}//EntierDepiler

void EntierDepiler2(int *piA,int *piB){
	EntierDepiler(piA);EntierDepiler(piB);
}//EntierDepiler2

void EntierDepiler3(int *piA,int *piB,int *piC){
	EntierDepiler2(piA,piB);EntierDepiler(piC);
}//EntierDepiler3

void EntierDepiler4(int *piA,int *piB,int *piC,int *piD){
	EntierDepiler2(piA,piB);EntierDepiler2(piC,piD);
}//EntierDepiler4

void EntierDepilerTout(){
	//vide (dc initialise) la pile courante
	ipEntierPilE=0;
}//EntierDepilerTout

void EntierEchanger(int *piA,int *piB){
	int iC;
	Assert2("EntierEchanger",piA!=0,piB!=0);
	iC=*piA;
	*piA=*piB;
	*piB=iC;
}//EntierEchanger

void EntierEmpiler(int iA){
	Assert1("EntierEmpiler",ipEntierPilE<kuPileMaX);
	//d(ipEntierPilE);
	iEntierPilE[ipEntierPilE++]=iA;
}//EntierEmpiler

void EntierEmpiler2(int iA,int iB){
	EntierEmpiler(iA);EntierEmpiler(iB);
}//EntierEmpiler2

void EntierEmpiler3(int iA,int iB,int iC){
	EntierEmpiler2(iA,iB);EntierEmpiler(iC);
}//EntierEmpiler3

void EntierEmpiler4(int iA,int iB,int iC,int iD){
	EntierEmpiler2(iA,iB);EntierEmpiler2(iC,iD);
}//EntierEmpiler4

char *sEntierEnClair(int iEntier,int bPremiere){
	//traduit en clair iEntier destiné à une expression algébrQ
	char *sEntierEnClair;
	if (iEntier!=-1){
		int muSigne=(bPremiere && iEntier>0)? 0 : tSigne(iEntier);
		int iCoeff=(iEntier!=+1)? iEntier : 0;
		sEntierEnClair=sC2( (muSigne)? sSigne(muSigne) : "",(iCoeff)? sEnt(abs(iCoeff)) : "");
	}else sEntierEnClair=sC0('-');
	return(sEntierEnClair);
}//sEntierEnClair

int nEntierEnTout(){
	return(ipEntierPilE);
}//nEntierEnTout

/*
char *sEntierSigne(long yEntier){
	// "+5" ou "-5" ou " 0"; "12345"
	char *sEnt=sMalloC(kuEntier23SizE);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
		sprintf(sEnt,"%+ld",yEntier);//yEntier tient forcément ds sEnt vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	MallocGereR(sEnt);
	return(sEnt);
}//sEntierSigne
*/
char *sEntierSigneh(long yPoids){
	//rend "+5" ou "-5" ou "0"; "12 345"
	char *sEntierSigneh=sC2(sSigne(yPoids),sEnt(zAbs(yPoids)));
	//s(sEntierSigneh);
	return(sEntierSigneh);
}//sEntierSigneh

void EntyerEchanger(long *pyA,long *pyB){
	long yC;
	Assert2("EntierEchanger",pyA!=0,pyB!=0);
	yC=*pyA;
	*pyA=*pyB;
	*pyB=yC;
}//EntyerEchanger

float fEsperance(float fListe[]){
	//rend la moyenne arithmétique des entiers stockés dans fListe[0..fListe[0]]
	int uIndex;
	float fSomme,fEsperance;
	Assert1("fEsperance",fListe[0]>0);
	for (fSomme=0.0,uIndex=1;uIndex<=fListe[0];uIndex++)
		fSomme+=fListe[uIndex];
	fEsperance=fSomme/fListe[0];
	return(fEsperance);
}//fEsperance

char *sEst(int bAssertion){
	//rend "est" tel quel,ou négativé avec "n'"..."pas" si bAssertion est faux 
	#define kuEstLg 3//"est"
	#define kuNestPasLg 9//"n'est pas"
	char *sEst=sMalloC( (bAssertion)? kuEstLg : kuNestPasLg );
		if (bAssertion)
			strcpy(sEst,"est");
		else strcpy(sEst,"n'est pas");
	//s(sEst);printf("@@@ char *sEst(int bAssertion) a été exécuté.\n");
	MallocGereR(sEst);
	return(sEst);
}//sEst

char *sEtc(int iGauche,int iDroit){
	//pr lister des résultats, eg "Arcs du couplage: (A,E), (B,F), (C,D), (G,J) et (H,I)".
	return(sEtc3(iGauche,iDroit,", "," et ",""));
}//sEtc

char *sEtc1(int iGauche,int iDroit){
	//pr lister des résultats, eg "Arcs du couplage: (A,E), (B,F), (C,D), (G,J) et (H,I).".
	return(sEtc3(iGauche,iDroit,", "," et ","."));
}//sEtc1

char *sEtc3(int iGauche,int iDroit,char * sAvant,char *sPenultieme,char *sDernier){
	//pr lister des résultats, eg "Arcs du couplage: (A,E), (B,F), (C,D), (G,J) et (H,I)".
	//d2(iGauche,iDroit);
	if (iGauche+1<iDroit) return(sAvant);
	if (iGauche+0<iDroit) return(sPenultieme);
	else return(sDernier);
}//sEtc3

char *sEuro(float fReel){
	//convertit fReel en chaîne de caractères avec euros et centimes d'euros: sEuro(23.5) rend "23€50".
	char *sEuro=sEuro1(fReel,30);
	int mPos=mChainePos(' ',sEuro);
	sEuro=sChainon(sEuro,0,mPos-1);
	return(sEuro);
}//sEur0

char *sEuro0(float fReel,int nCaractereEnTout){
	//convertit fReel en prix cadré à droite sur nCaractereEnTout caractères: sEuro0(0.5,6) rend "  0€50".
	int mPointPos;
	char *sEuro0=sReel0(fReel,nCaractereEnTout);
		mPointPos=mChainePos('.',sEuro0);
		Assert1("sEuro0",mPointPos>0);
		sEuro0=sC3(sChainon0(sEuro0,mPointPos-1),"€",sChainon(sEuro0,mPointPos+1,nChaineLg(sEuro0)-1));
		//printf("sEuro0 cadré à droite:%s.\n",sG(sEuro0));
	MallocGereR(sEuro0);
	return(sEuro0);
}//sEuro0

char *sEuro1(float fReel,int nCaractereEnTout){
	//convertit fReel en prix cadré à gauche sur nCaractereEnTout caractères: sEuro1(0.5,6) rend "0€50  ".
	int mPointPos;
	char *sEuro1=sReel1(fReel,nCaractereEnTout);
		mPointPos=mChainePos('.',sEuro1);
		Assert1("sEuro1",mPointPos>0);
		sEuro1=sC3(sChainon0(sEuro1,mPointPos-1),"€",sChainon(sEuro1,mPointPos+1,nChaineLg(sEuro1)-1));
		//printf("sEuro1 cadré à gauche:%s.\n",sG(sEuro1));
	MallocGereR(sEuro1);
	return(sEuro1);
}//sEuro1

char *sEuro2(float fReel,int nCaractereEnTout){
	//convertit fReel en prix centré sur nCaractereEnTout caractères: sEuro2(0.5,6) rend " 0€50 ".
	int mPointPos;
	char *sEuro2=sReel2(fReel,nCaractereEnTout);
		mPointPos=mChainePos('.',sEuro2);
		Assert1("sEuro2",mPointPos>0);
		sEuro2=sC3(sChainon0(sEuro2,mPointPos-1),"€",sChainon(sEuro2,mPointPos+1,nChaineLg(sEuro2)-1));
		//printf("sEuro2 centré:%s.\n",sG(sEuro2));
	MallocGereR(sEuro2);
	return(sEuro2);
}//sEuro2

long xFact(int nN){
	//rend la factorielle de l'entier naturel nN
	long xFact=1;
	Assert1("xFact0",nN>=0);
	for (int uTour=1;uTour<=nN;uTour++)
		xFact*=uTour;
	if (!(xFact>0)) ld2(nN,xFact);
	Assert1("xFact1",xFact>0);
	return(xFact);//dc 1 si nN=0
}//xFact

long zFactModulo(int nN,int nModulo){
	//rend la factorielle de l'entier naturel nN
	long zFactModulo=1;
	Assert1("zFactModulo",nN>=0);
	for (int uTour=1;uTour<=nN;uTour++)
		zFactModulo=zModulo(zFactModulo*uTour,nModulo);
	zFactModulo=zModulo(zFactModulo,nModulo);
	return(zFactModulo);
}//zFactModulo

int bFaux(int iEntier){
	//rend la constante entière kV (vrai) si iEntier==0 et la constante kF (faux) sinon
	int bFaux=(iEntier==0) ? 1 : 0;
	return(bFaux);
}//bFaux

//FlipFlop,placé en tête d'une routine R(bMode,…),permet de vérifier que les appels successifs à R sont: R(true,…),R(false,…),R(true,…),R(false,…),etc.
//Le paramère pbAvant est censé être déclaré soit en variable de module soit en static dans R(), et être initialisé une fois pour toutes à false.
void FlipFlop(char* sContexte,int bApres,int *pbAvant){
	//si bApres≠*pbAvant,mémorise bApres dans pbAvant;sinon,déroute après avoir affiché sContexte.
	Assert1(sContexte,bApres!=*pbAvant);
	*pbAvant=bApres;
}//FlipFlop

long zFib(int nIndex){//fonction de Fibonacci définie par F(n)=F(n-1)+F(n-2) avec F(1)=F(2)=1, n>0
	#define kuFibMax 70 //plante au-delà
	long zFib=0;
	double rPhi,rPhiBarre,rFib;
	Assert1("zFib1",bCroit(0,nIndex,kuFibMax));
	rPhi=((long) 1.0+sqrtl( (long) 5.0))/ (long)2.0;
	rPhiBarre=((long) 1.0-sqrtl((long) 5.0))/(long) 2.0;
	rFib=(powl(rPhi,nIndex)-powl(rPhiBarre,nIndex))/sqrtl((long) 5.0);
	//printf("rFib(%d)=%lf....",nIndex,rFib);
	zFib=truncl(rFib);
	//zFib=(long) (round(0.1+rFib));
	//printf("rFib(%d)=%s vs %s.\n",nIndex,sPar3(zFib),sPar3(kuIntegerMax));
	//printf("rFib(%d)=%s\n",nIndex,sPar3(zFib));
	Assert1("zFib2",zFib>=0);
	return(zFib);
}//zFib

void FibCronometreR(){
	long xF,zT;
	for (int N=1;N<=70;N++){
		zT=nChrono(1);
			xF=zFib(N);//O(log(N))
		zT=nChrono(0);
		printf("%20ld %20ld\n",xF,zT);
	}
}//FibCronometreR

void Flag(int bFlag){
	bFlaG=bFlag;
}//Flag

int bFlag(){
	return(bFlaG);
}//bFlag

int bFleche(const char *ksChaine,int nDebutExclu){
	int bFleche=nDebutExclu>=0 && ksChaine[nDebutExclu+1]=='-' && ksChaine[nDebutExclu+2]=='>';
	return(bFleche);
}//bFleche

char *sFois(int nFois,char cMotif){
	//juxtapose nFois cMotif
	char *sFwa;
	Assert2("sFois",nFois>=0,bAffichable(cMotif));//implique 1 code caractère par caractère,dc cMotif ne peut coder un "é" car il est occupe 2 codes caractères.
	char sFois[1+nFois];
	for (int nF=0;nF<nFois;nF++)
		sFois[nF]=cMotif;
	sFois[nFois]='\0';
	sFwa=sMalloC(nFois);
		//printf("nChaineLg(sFois)=%d et nFois=%d.\n",nChaineLg(sFois),nFois);
		ChaineCopier(sFois,nFois,sFwa);
	MallocGereR(sFwa);
	Assert1("sFois",nChaineLg(sFwa)==nFois);
	return(sFwa);
}//sFois

int bFrontiere16(long zSizeOf){
	//vrai ssi zSizeOf est aligné sur une frontière de 16 octets
	Assert1("bFrontiere16",zSizeOf>=0);
	int bFrontiere16=(zSizeOf%16==0);
	return(bFrontiere16);
}//bFrontiere16

int nFrontiere16(long zSizeOf){
	//rend le plus petit entier ≥ zSizeOf aligné sur une frontière de 16 octets
	Assert1("nFrontiere160",zSizeOf>=0);
	int nFrontiere16=zSizeOf;
	if (zSizeOf%16)
		nFrontiere16+=16-zSizeOf%16;
	Assert1("bFrontiere161",nFrontiere16);
	return(nFrontiere16);
}//nFrontiere16

int bFrontiere4(long zSizeOf){
	//vrai ssi zSizeOf est aligné sur une frontière de 4 octets
	Assert1("bFrontiere4",zSizeOf>=0);
	int bFrontiere4=(zSizeOf%4==0);
	return(bFrontiere4);
}//bFrontiere4

int nFrontiere4(long zSizeOf){
	//rend le plus petit entier ≥ zSizeOf aligné sur une frontière de 4 octets
	Assert1("nFrontiere40",zSizeOf>=0);
	int nFrontiere4=zSizeOf;
	if (zSizeOf%4)
		nFrontiere4+=4-zSizeOf%4;
	Assert1("bFrontiere41",nFrontiere4);
	return(nFrontiere4);
}//nFrontiere4

int bFrontiere8(long zSizeOf){
	//vrai ssi zSizeOf est aligné sur une frontière de 8 octets
	Assert1("bFrontiere8",zSizeOf>=0);
	int bFrontiere8=(zSizeOf%8==0);
	return(bFrontiere8);
}//bFrontiere8

int nFrontiere8(long zSizeOf){
	//rend le plus petit entier ≥ zSizeOf aligné sur une frontière de 8 octets
	Assert1("nFrontiere80",zSizeOf>=0);
	int nFrontiere8=zSizeOf;
	if (zSizeOf%8)
		nFrontiere8+=8-zSizeOf%8;
	Assert1("bFrontiere81",nFrontiere8);
	return(nFrontiere8);
}//nFrontiere8

char *sG(const char* sTexte){
	// rend sTexte entre deux guillemets
	return(sC3(sC0('"'),sTexte,sC0('"')));
}//sG

int nHasard(int uBorneLim){
	//rend un nombre pseudo-aléatoire ds [0..uBorneLim[, donc borne supérieure exclue.
	int nHasard;
	Assert1("nHasard1",bCroit(1,uBorneLim,kuIntegerMax-1));
	nHasard=rand()%uBorneLim;
	Assert1("nHasard2",bCroit(0,nHasard,uBorneLim-1));
	return(nHasard);
}//nHasard

int uHasard(int uBorneMax){
	//rend un nombre pseudo-aléatoire ds [1..nBorneMax], donc borne supérieure incluse.
	int uHasard;
	Assert1("uHasard1",bCroit(1,uBorneMax,kuIntegerMax));
	uHasard=1+rand()%uBorneMax;
	Assert1("uHasard2",bCroit(1,uHasard,uBorneMax));
	return(uHasard);
}//uHasard

void Hasarder(int iGerme){
	//Si iGerme=0, ne fait rien. Sinon: 1er terme de la suite de nbres pseudo-aléatoires:= (iGerme>0) ?  clock() : iGerme.
	if (iGerme>0)
		srand(clock());///pr générer une suite pseudo-aléatoire; un nouvel appel avec le mm iGerme donnera une autre suite.
	else if (iGerme<0)
		srand(iGerme);//pr générer une nouvelle suite; un nouvel appel avec le mm iGerme donnera la mm suite.
}//Hasarder

int bImpair(int iEntier){
	int bImpair=bVrai(iEntier%2);
	assert(bBool(bImpair));
	return (bImpair);
}//bImpair

int bInteger(long yEntier){
	int bInteger=bCroit(kiIntegerMin,yEntier,kuIntegerMax);
	return (bInteger);
}//bInteger

double rInf(double dA,double dB){
	//rend inf(dA,dB)
	double rInf=(dA<dB)?dA:dB;
	return(rInf);
}//rInf

int iInf(int iA,int iB){
	//rend inf(iA,iB);identique à iMin(iA,iB).
	int iInf=(iA>iB)?iB:iA;
	return(iInf);
}//iInf

int iInf3(int iA,int iB,int iC){
	int iInf3=iInf(iA,iInf(iB,iC));
	return(iInf3);
}//iInf3

long yInf(long yA,long yB){
	//rend inf(yA,yB);identique à yMin(yA,yB)
	long yInf=(yA>yB)?yB:yA;
	return(yInf);
}//yInf

long yInf3(long yA,long yB,long yC){
	long yInf3=yInf(yA,yInf(yB,yC));
	return(yInf3);
}//yInf3

q qInv(q qA){
	//inverse du rationnel
	q qInv;
	Assert2("qInv",qA.num>0,qA.den>0);
	qInv.num=qA.den;
	qInv.den=qA.num;
	return(qInv);
}//qInv

int nItem(const char *ksItemVirguleItemVirguleItem){
	//rend le nb total d'items (éventuellement vides);nItem(alpha,b,c)=3;nItem(a)=1;nItem(a,,c)=3.nItem(,a)=2 .nItem(a,)=1.nItem(,a,)=2;
	int nC,nClim,nItem=0;
	nClim=nChaineLg(ksItemVirguleItemVirguleItem);//ie les virgules éventuelles placées aux extrémités de la chaîne sont ignorées
	//t(sG(ksItemVirguleItemVirguleItem));
	if (nClim>0)
		for (nItem=1,nC=0;nC<nClim-1;nC++)
			if (bVirgulhE(ksItemVirguleItemVirguleItem[nC]))
				nItem++;
	//printf("nItem(%s)=%d.\n",sG(ksItemVirguleItemVirguleItem),uItem);
	Assert1("nItem",nItem>=0);
	return(nItem);
}//nItem

char *sItem(const char *ksItemVirguleItemVirguleItem,int uItemRang){
	//rend l'item de rang uItemRang ou une chaîne vide si cet item n'existe pas. sItem("a,b,c",1)="a". sItem("a,b,c",5)="". sItem("a,,c",2)="".
	const int kbBlancSauter=1;
	int nC,nClim,nDebutInclus=0,nFinExclue=0;
	int nItemEnTout,nVirguleRang,nRequis;
	char *sItem;
	//sd(sG(ksItemVirguleItemVirguleItem),uItemRang);
	nItemEnTout=nItem(ksItemVirguleItemVirguleItem);
	//d(nItemEnTout);
	if (bCroit(1,uItemRang,nItemEnTout))
		for (nClim=nChaineLg(ksItemVirguleItemVirguleItem),nDebutInclus=0,nFinExclue=nClim,nVirguleRang=0,nC=0;nC<nClim;nC++)
			if (bVirgulhE(ksItemVirguleItemVirguleItem[nC])){
				nVirguleRang++;
				if (nVirguleRang==uItemRang-1)
					nDebutInclus=nC+1;
				if (nVirguleRang==uItemRang+0)
					nFinExclue=nC;
			};
	if (kbBlancSauter)//laisser de côté les blancs consécutifs situés au début de l'item
		while (ksItemVirguleItemVirguleItem[nDebutInclus]==' ')
			nDebutInclus++;
	nRequis=iSup(0,nFinExclue-nDebutInclus);
	sItem=sMalloC(nRequis);
		for (nC=0;nC<nRequis;nC++)
			sItem[nC]=ksItemVirguleItemVirguleItem[nDebutInclus+nC];
		sItem[nRequis]='\0';
	MallocGereR(sItem);
	return(sItem);
}//sItem

char *sItem0(const char *ksItemVirguleItemVirguleItem,int nItemRang){
	//rend l'item de rang nItemRang ou une chaîne vide si cet item n'existe pas. sItem("a,b,c",0)="a".
	char *sItem0=sItem(ksItemVirguleItemVirguleItem,nItemRang+1);
	return(sItem0);
}//sItem0

char *sItem4(int uItem,char* sItem1,char* sItem2,char* sItem3,char* sItem4){
	char *sItem;
	switch (uItem) {
		case 1:	sItem=sItem1; break;
		case 2:	sItem=sItem2; break;
		case 3:	sItem=sItem3; break;
		case 4:	sItem=sItem4; break;
		default: sItem="";
	}
	return(sItem);
}//sItem4

char *sItem6(int uItem,char* sItem1,char* sItem2,char* sItem3,char* sItem4,char* sItem5,char* sItem6){
	char *sItem;
	switch (uItem) {
		case 1:	sItem=sItem1; break;
		case 2:	sItem=sItem2; break;
		case 3:	sItem=sItem3; break;
		case 4:	sItem=sItem4; break;
		case 5:	sItem=sItem5; break;
		case 6:	sItem=sItem6; break;
		default: sItem="";
	}
	return(sItem);
}//sItem6

char *sItem8(int uItem,char* sItem1,char* sItem2,char* sItem3,char* sItem4,char* sItem5,char* sItem6,char* sItem7,char* sItem8){
	char *sItem;
	switch (uItem) {
		case 1:	sItem=sItem1; break;
		case 2:	sItem=sItem2; break;
		case 3:	sItem=sItem3; break;
		case 4:	sItem=sItem4; break;
		case 5:	sItem=sItem5; break;
		case 6:	sItem=sItem6; break;
		case 7:	sItem=sItem7; break;
		case 8:	sItem=sItem8; break;
		default: sItem="";
	}
	return(sItem);
}//sItem8

int nItemPos(const char *ksItemListe,char *sItemEnquis){
	//rend le numéro (rang1) du 1er item de ksItemListe qui est identique à sItemEnquis;rend 0 si échec.
	int uItem,nPos;
	for (nPos=0,uItem=1;uItem<=nItem(ksItemListe) && nPos==0;uItem++)
		if ( bChaineEgale(sItem(ksItemListe,uItem),sItemEnquis) )
			nPos=uItem;
	return(nPos);
}//nItemPos

int mItemPosition(const char *ksItemListe,char *sOu,int *puItem){
	//rend le rg0 du 1er caractR du 1er item de ksItemListe qui figure ds sOu, et le rg1 de cet item ds *puItem;rend -1 si échec.
	int uItem, mPosition=-1;
	for (mPosition=-1,uItem=1;uItem<=nItem(ksItemListe) && mPosition<0;uItem++){
		mPosition=mChainonPos(sItem(ksItemListe,uItem),sOu);
		if (mPosition>=0)
			*puItem=uItem;
	}
	return(mPosition);
}//mItemPosition

int nItemRang(char *sQuoi,const char *ksItemVirguleItemVirguleItem){
	//rend le rang1 de sQuoi dans ksItemVirguleItemVirguleItem: nItemRang("deux","un,deux,trois")=2. Rend 0 si sQuoi n'est pas un item.
	int nRang,uItem;
	int nPareil,nQuoiLg;
	int nQ,nC,nClim,nVirguleRg;
	//int bActif=bActiveR;
	//if (bActiveR) s2(sQuoi,ksItemVirguleItemVirguleItem);
	nQuoiLg=nChaineLg(sQuoi);
	nClim=nChaineLg(ksItemVirguleItemVirguleItem);
	if (nQuoiLg>0){
		for (uItem=1,nRang=nQ=nPareil=nC=0;nC<nClim && nRang==0;nC++){
			if (bVirgulhE(ksItemVirguleItemVirguleItem[nC])){
				if (nC>0){
					if (nRang==0 && nPareil==nQuoiLg)
						nRang=uItem;
					uItem++;
					//d3(nC,nPareil,uItem);
					nPareil=0;nQ=0;
				}
			} else if (sQuoi[nQ++]==ksItemVirguleItemVirguleItem[nC])
				nPareil++;
		}
		if (nRang==0 && nPareil==nQuoiLg)
			nRang=uItem;
	} else {//rang de la première chaine vide éventuelle
		for (nRang=0,uItem=1,nVirguleRg=0,nC=1;nC<nClim && nRang==0;nC++)
			if (bVirgulhE(ksItemVirguleItemVirguleItem[nC])){
				if (nRang==0 && nVirguleRg==nC-1)
					nRang=uItem;
				//d3(nC,nPareil,uItem);
				nVirguleRg=nC;
				uItem++;
			}
		//d(nRang);
		if (nRang==0 && nClim>1 && bVirgulhE(ksItemVirguleItemVirguleItem[0]) && bVirgulhE(ksItemVirguleItemVirguleItem[1]))
			nRang=1;
		if (nRang==0 && nClim>1 && bVirgulhE(ksItemVirguleItemVirguleItem[nClim-2]) && bVirgulhE(ksItemVirguleItemVirguleItem[nClim-1]))
			nRang=uItem;
	}
	Assert1("nRang",nRang>=0);
	return(nRang);
}//nItemRang

/*s(sJhms(kE3));
s(sJhms(60*kE3));
s(sJhms(3600*kE3));
sd(sJhms(24*3600*kE3),24*3600*kE3);
sd(sJhms(2*24*3600*kE3),2*24*3600*kE3);*/

char *sJhms(long zUnitehDeTemps){
	//convertit zUnitehDeTemps en jours, heures, minutes et secondes
	const int kuUniteh=kE6;//empirique
	//ld(zUnitehDeTemps);	
	Assert1("sJhms",zUnitehDeTemps>=0);
	int nSeconde,nMinute,nHeure,nJour;
	long zReste=zUnitehDeTemps/kuUniteh;
	nSeconde=zReste%60;
	zReste=(zReste-nSeconde)/60;
	nMinute=zReste%60;
	zReste=(zReste-nMinute)/60;
	nHeure=zReste%24;
	zReste=(zReste-nHeure)/24;
	nJour=zReste;
	return(sC5(sChoix1(nJour>0,sC2(sEnt(nJour),"j")),sChoix1(nHeure>0,sC2(sEnt(nHeure),"h")),sChoix1(nMinute>0,sC2(sEnt(nMinute),"m")),sEnt(nSeconde),"s"));
}//sJhms

int nJourSemaine(int nQuantieme,int nMois,int nAnnee){
	//années 1900 à 2100 incluses
	int bBissextile,nCentime,bDate,nDecalAn,nJourSemaine;
	int nDecalCumul[1+12]={-1,     0, 3, 3,     6, 1, 4,     6, 2, 5,     0, 3, 5};
	int nJourEnTout[1+12]={-1,    31,28,31,    30,31,30,    31,31,30,    31,30,31};
	//d3(nQuantieme,nMois,nAnnee);
	Assert3("nJourSemaine0",bCroit(1,nQuantieme,31),bCroit(1,nMois,12),bCroit(1900,nAnnee,2100));
	nCentime=nAnnee%100;
	bBissextile=(nCentime!=0)? (nCentime%4==0) : (nAnnee/100==20);
	//d2(nAnnee,bBissextile);
	bDate=nQuantieme<=nJourEnTout[nMois] || (bBissextile && nQuantieme==29 && nMois==2);
	Assert1("nJourSemaine1",bDate);
	nDecalAn=(nAnnee-1900)+(nAnnee-1900)/4;
	//d2(nDecalAn,nDecalCumul[nMois]);
	nJourSemaine=nQuantieme+nDecalCumul[nMois]+nDecalAn-(bBissextile && nMois<=2);
	nJourSemaine=1+nJourSemaine%7;
	Assert1("nJourSemaine2",bCroit(1,nJourSemaine,7));
	return(nJourSemaine);
}//nJourSemaine

char *sK(ri rComplexe){
	//convertit le nombre complexe rComplexe à coefficients réels en chaîne de caractères: sK((2.5,1.7)) rend "2.5+1.7i".
	const int kuRequis=31;
	char *sK=sMalloC(kuRequis);
		if (!bReelEgal(rComplexe.r,0)){
			if (!bReelEgal(rComplexe.i,0))
				sprintf(sK,"%.2f%c%.2fi",rComplexe.r,(rComplexe.i>0)?'+':'-',fAbs(rComplexe.i));
			else if (bReelEgal(rComplexe.i,1))
				sprintf(sK,"%.2f%ci",rComplexe.r,(rComplexe.i>0)?'+':'-');
			else if (bReelEgal(yArrondi(rComplexe.r),rComplexe.r))
				sprintf(sK,"%ld",yArrondi(rComplexe.r));
			else sprintf(sK,"%.2f",rComplexe.r);
		}else if (bReelEgal(rComplexe.i,1.0))
			sK=sC0('i');
		else if (bReelEgal(rComplexe.i,-1.0))
			sK=sC2("-",sC0('i'));
		else if (!bReelEgal(rComplexe.i,0.0))
			if (bReelEgal(yArrondi(rComplexe.i),rComplexe.i))
				sprintf(sK,"%c%ldi",(rComplexe.i>0)?'+':'-',zAbs(yArrondi(rComplexe.i)));
			else sprintf(sK,"%c%.2fi",(rComplexe.i>0)?'+':'-',fAbs(rComplexe.i));
		else sK=sC0('0');
	MallocGereR(sK);
	return(sK);
}//sK

char *sK3(ri rComplexe){
	//idem sK en groupant les décits par paquets de 3.
	char *sK;
		if (abs(rComplexe.r)!=0){
			if (abs(rComplexe.i)>1)
				//sprintf(sK,"%d%c%di",rComplexe.r,(rComplexe.i>0)?'+':'-',abs(rComplexe.i));
				sK=sC3(sPar3(rComplexe.r),(rComplexe.i>0)?"+":"-",sPar3(abs(rComplexe.i)));
			else if (abs(rComplexe.i)==1)
				//sprintf(sK,"%d%ci",rComplexe.r,(rComplexe.i>0)?'+':'-');
				sK=sC3(sPar3(rComplexe.r),(rComplexe.i>0)?"+":"-","i");
			else //sprintf(sK,"%d",rComplexe.r);
				sK=sPar3(rComplexe.r);
		}else if (abs(rComplexe.i)!=0){
			if (abs(rComplexe.i)>1)
				//sprintf(sK,"%c%di",(rComplexe.i>0)?'+':'-',abs(rComplexe.i));
				sK=sC3((rComplexe.i>0)?"+":"-",sPar3(abs(rComplexe.i)),"i");
			else //sprintf(sK,"%d%ci",rComplexe.r,(rComplexe.i>0)?'+':'-');
				sK=sC2((rComplexe.i>0)?"k+":"k-","i");
		} else //sprintf(sK,"0");
			sK=sC0('0');
	return(sK);
}//sK3

void KitActiver(int bActiver){//pr déboguer
	Assert1("KitActiver",bBool(bActiver));
	bActiveR=bActiver;
}//KitActiver

void KitAMORCER(){
	//amorce le présent module une fois pour toutes
	//NB ne toucher ni à nAppeL ni à bAppeL[] utilisés avant l'amorçage;
	assert(nAppeL==1);//dédié Appel0() et Appel1();vérifie que Appel0() a bien été exécuté 1 fois ——Appel0("") est censé débuter le main().
	assert(CLOCKS_PER_SEC==kE6);
	assert(kuEntier23SizE==23);//touche pas
	assert(strlen("à")>1);//ATTENTION: strlen("à")==2 et strlen("a")==1. strlen() ne compte plus des caractères mais des codes caractères,d'où le 2.
	MallocGereR0();
	fEpsiloN=kdEpsilon;
	//mode caractere
		VecteurRaz(muModeCaracterE,kuModeCaractereMax);
		ipModeCaracterE=1;
	//mode chiffre
		VecteurRaz(muModeChiffrE3,kuModeChiffreMaX);
		ipModeChiffrE3=1;
	PremierAmorceR();
	cChaineGarniR=' ';
	//conversion des chiffres en caractères, en commençant par les majuscules
		VecteurIndexer(icModeCaracterE,1,kuModeCaractereMax);
	if (0) for (int uC=1;uC<=kuModeCaractereMax;uC++)
			printf("%d",icModeCaracterE[uC]);
	bKitAmorceR=kV;
}//KitAMORCER

void KitTESTER(int iTest){
	q qA,qB,qC,qD;
	//char *sQuoi;
	int nIndex=0;
	long yIndex;
	int uFois,iItem;
	int nT[1+10];
	int iVecteur[6]={0,9,3,7,2,6};
	int nRang[6]={0,0,0,0,0,0};
	char sContrainte[20]="Caintrainte";
	#define kuConsonneEnTout 44
	#define kuVoyelleEnTout 47
	Appel0(sC2("KitTESTER,test n°",sEnt(iTest)));
		char *skConsonne="çÇñÑbcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
		char *skVoyelle="ÃãaeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸ";
		char *skLettre="çÇñÑbcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZÃãaeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸ";
		switch (iTest) {
			case  1:	printf("Le graphe %s un circuit\n",sPas("contient",1)); break;
			case  2:	printf("Le graphe %s un circuit\n",sPas("contient",0)); break;
			case  3:	printf("Il %s circuit\n",sUn("y a",1)); break;
			case  4:	printf("Il %s boucle\n",sUne("y a",0)); break;
			case  5:	VecteurVoir("iVecteur AVANT le tri",&iVecteur[0],1,5);
						//VecteurTrier(&iVecteur[0],1,5);
						VecteurTrierVite(iVecteur,1,5);
						VecteurVoir("iVecteur APRES le tri",&iVecteur[0],1,5);
						break;
			case  6:	VecteurVoir("iVecteur AVANT le tri",&iVecteur[0],1,5);
						VecteurTrier2(&iVecteur[0],1,5,&nRang[0]);
						VecteurVoir("iVecteur APRES le tri",&iVecteur[0],1,5);
						VecteurVoir("nRang APRES le tri",&nRang[0],1,5);
						break;
			case  9:	printf("%s.\n",sDateEnClair( 1, 1,1900));
						printf("%s.\n",sDateEnClair( 1, 1,1907));
						printf("%s.\n",sDateEnClair( 1, 1,1963));
						printf("%s.\n",sDateEnClair( 1, 1,2000));
						printf("%s.\n",sDateEnClair(15, 2,2016));
						printf("%s.\n",sDateEnClair(15, 2,2017));
						printf("%s.\n",sDateEnClair( 8, 4,2017));
						printf("%s.\n",sDateEnClair( 9, 4,2017));
						printf("%s.\n",sDateEnClair(10, 4,2017));
						break;
			case 10:	printf("test des fonctions de concaténation:\n");
			case 11:	printf("11AVANT%sAPRES\n",sC1("a"));
			case 12:	printf("12AVANT%sAPRES\n",sC2("b","c"));
			case 13:	printf("13AVANT%sAPRES\n",sC2b("d","e"));
			case 14:	printf("14AVANT%sAPRES\n",sC2b("f",""));
			case 15:	printf("15AVANT%sAPRES\n",sC2b("","g"));
			case 16:	printf("16AVANT%sAPRES\n",sC2b("",""));
			case 17:	printf("17AVANT%sAPRES\n",sC2bp("",""));
			case 18:	printf("18AVANT%sAPRES\n",sC1p(sC2bp("h", "i")));
			case 19:	printf("19AVANT%sAPRES\n",sC7bp("1","2","3","4","5","6","7"));break;

			case 20:	d(nItem(""));
						d(nItem("a"));
						d(nItem("a,b"));
						printf("nb item:%d.\n",nItem("salut,bonjour,bonsoir"));
						printf("nb item:%d.\n",nItem("salut,,bonjour,bonsoir"));
						printf("nb item:%d.\n",nItem(",salut,,bonjour,bonsoir"));
						printf("nb item:%d.\n",nItem(",salut,,bonjour,bonsoir,"));
						printf("nb item:%d.\n",nItem(",,,"));
						printf("nb item:%d.\n",nItem(""));
						for (iItem=-1;iItem<=4;iItem++)
							printf("item n°%d:\"%s\".\n",iItem,sItem("salut,bonjour,bonsoir",iItem));
						for (iItem=1;iItem<=4;iItem++){
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),"bon,bonjour,bonsoir",nItemRang(sItem("bon,bonjour,bonsoir",iItem),"bon,bonjour,bonsoir"));
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir",nItemRang(sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir"));
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),",,bon,bonjour,bonsoir",nItemRang(sItem("bon,bonjour,bonsoir",iItem),",,bon,bonjour,bonsoir"));
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),"bon,bonsoir,,hello",nItemRang(sItem("bon,bonjour,bonsoir",iItem),"bon,bonsoir,,hello"));
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir,",nItemRang(sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir,"));
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),"bon,bonjour,bonsoir,,",nItemRang(sItem("bon,bonjour,bonsoir",iItem),"bon,bonjour,bonsoir,,"));
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir,,",nItemRang(sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir,,"));
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir,",nItemRang(sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir,"));
						}
printf("nItemRang1(\"%s\",\"%s\")=%d.\n","bonjour","bonjour",nItemRang("bonjour","bonjour"));
printf("nItemRang2(\"%s\",\"%s\")=%d.\n","","",nItemRang("",""));
printf("nItemRang2(\"%s\",\"%s\")=%d.\n","",",",nItemRang("",","));
printf("nItemRang2(\"%s\",\"%s\")=%d.\n","",",,",nItemRang("",",,"));
						break;
			case 21:	ChronoTesteR();break;
			case 22:	Voir("%5.2f %s %d %s.\n",3.14,"mètres,soit environ",3,"mètres");break;
			case 23:	t("12345678");
						t(sReel0(3.14,8));
						t(sReel1(3.14,8));
						t(sReel2(3.14,8));
						t(sG("12345678"));
						t(sG(sEuro0(3.14,8)));
						t(sG(sEuro1(3.14,8)));
						t(sG(sEuro2(3.14,8)));
						break;
			case 24:	t("case 24");
						int iVecteur[10];
						VecteurIndexer(iVecteur,5,9);
						VecteurVoir("AVANT VecteurInverser",iVecteur,5,9);
						VecteurInverser(iVecteur,5,9);
						VecteurVoir("APRES VecteurInverser",iVecteur,5,9);
						break;
			case 25:	printf("%s\n",sG(sChainon("salut",1,5)));
						printf("%s\n",sG(sChainon("salut",2,4)));
						printf("%s\n",sG(sChainon("salut",2,2)));
						printf("%s\n",sG(sChainon("salut",4,2)));
						printf("%s\n",sG(sChainon0("salut",8)));
						printf("%s\n",sG(sChainon0("salut",0)));
						printf("%s\n",sG(sChainon("salut",4,4)));
						//printf("%s\n",sG(sChainon("salut",-4,-2)));//déclenche les assertions 
						break;
			case 26:	printf("%s\n",sG(sChaineEtale("élémentäirÉhauÿcañonÊ",2)));
						break;
			case 28:	printf("\t%s.\n",sPluriel(3,"élément$ détecté$"));
						printf("\t%s.\n",sPluriel(1,"élément$ détecté$"));
						printf("\t%s.\n",sPluriel(0,"élément$ détecté$"));
						break;
			case 30:	printf("\t%s.\n",sPluriel4(0,"élément$ $a$ été détecté$",!k1Feminin));
						printf("\t%s.\n",sPluriel4(1,"élément$ $a$ été détecté$",!k1Feminin));
						printf("\t%s.\n",sPluriel4(2,"élément$ $a$ été détecté$",!k1Feminin));
						printf("\t%s.\n",sPluriel4(0,"cible$ $a$ été détectée$",k1Feminin));
						printf("\t%s.\n",sPluriel4(1,"cible$ $a$ été détectée$",k1Feminin));
						printf("\t%s.\n",sPluriel4(2,"cible$ $a$ été détectée$",k1Feminin));
						printf("\t%s.\n",sPluriel4(2,"cible$ $va$ être détectée$",k1Feminin));
						printf("\t%s.\n",sPluriel4(2,"cible$ $doit$ être détectée$",k1Feminin));
						printf("\t%s.\n",sPluriel4(2,"cible$ $existe$",k1Feminin));
						printf("\t%s.\n",sPluriel4(0,"cible$ $existe$",k1Feminin));
						break;
			case 32:	printf("Il %s.\n",sDire(1,"voit rouge"));
						printf("Il %s.\n",sDire(0,"voit rouge"));
						printf("Il %s rouge.\n",sDire1(1,"voit un poisson"));
						printf("Il %s rouge.\n",sDire1(0,"voit un poisson"));
						printf("Il %s rouge.\n",sDire1(1,"voit une truite"));
						printf("Il %s rouge.\n",sDire1(0,"voit une truite"));
						break;
			case 33:	s(sMajusculer("à maçon à cañon âäéèêëîïöüÿ."));
						break;
			case 35:	assert(nChaineLg("étagé")>6);break;//e aigu occupe 2 codes caractères,vu nChaineLg()
			case 38:	for (int nLg=16; nLg>=0 ; nLg--)
							printf("sChaine0(%d): %s.\n",nLg,sG(sChaine0("Bonjour",nLg)));
						for (int nLg=16; nLg>=0 ; nLg--)
							printf("sChaine0(%d): %s.\n",nLg,sG(sChaine0("Épaté",nLg)));
						//break;
			case 39:	for (int nLg=16; nLg>=0 ; nLg--)
							printf("sChaine1(%d): %s.\n",nLg,sG(sChaine1("Bonjour",nLg)));
						for (int nLg=16; nLg>=0 ; nLg--)
							printf("sChaine1(%d): %s.\n",nLg,sG(sChaine1("Épaté",nLg)));
						//break;
			case 40:	for (int nLg=16; nLg>=0 ; nLg--)
							printf("sChaine2(%d): %s.\n",nLg,sG(sChaine2("Bonjour",nLg)));
						for (int nLg=16; nLg>=0 ; nLg--)
							printf("sChaine2(%d): %s.\n",nLg,sG(sChaine2("Épaté",nLg)));
						break;
			case 41:	for (int uLg=16;uLg>=0;uLg--){
							//printf("%s. (%s cadrés à droite sur %s).\n",sG(sChaine3("Bonjour",uLg)),sPluriel(nCaractere("Bonjour"),"caractère"),sPluriel(uLg,"caractère"));
							//printf("%s. (%s cadrés à droite sur %s).\n",sG(sChaine3("Banzai",uLg)),sPluriel(nCaractere("Banzai"),"caractère"),sPluriel(uLg,"caractère"));
							printf("%s. (%s cadrés à droite sur %s).\n",sG(sChaine3("ÉpaBanzaité",uLg)),sPluriel(nCaractere("ÉpaBanzaité"),"caractère"),sPluriel(uLg,"caractère"));
						}
						break;
			case 42:	ChaineAbregeR(sContrainte,8);s(sContrainte);
						ChaineAbregeR(sContrainte,6);s(sContrainte);
						break;
			case 45:	//s(sChainon("$Chaine$ brute$",0,0));
						//s(sChainon("$Chaine$ brute$",1,1));
						//d(nChainonEnTout("$","$Chaine$ brute$"));
						s(sChaineSubstituer("$Chaine$ brute$","$",""));
						break;
			case 46:	ChaineCopierTesteR();
						break;
			case 47:	s(sEnt(+1234));
						s(sEnt(-1234));
						ModeChiffre(1);
							s(sEnt(+1234));
							s(sEnt(-1234));
						ModeChiffre(0);
						ModeCaractere(+1);
							s(sEnt(12));
							s(sEnt(123));
							
						ModeCaractere(-1);
						break;
			case 48:	s(sEntierEnClair(+5,1));
						s(sEntierEnClair(-5,1));
						s(sEntierEnClair(+5,0));
						s(sEntierEnClair(-5,0));
						s(sEntierEnClair(+1,1));
						s(sEntierEnClair(-1,1));
						s(sEntierEnClair(+1,0));
						s(sEntierEnClair(-1,0));
						s(sEntierEnClair(+0,1));
						s(sEntierEnClair(-0,0));
						break;
			case 49:	ListeTesteR();break;
			case 50:	Assert1("test 50",nCaractere(skVoyelle)==kuVoyelleEnTout);break;
			case 51:	Assert1("test 51",nCaractere(skConsonne)==kuConsonneEnTout);break;
			case 52:	Assert1("test 52",nCaractere(skLettre)==kuVoyelleEnTout+kuConsonneEnTout);break;
			case 54:	d(nCaractere("ABBE"));d(nCaractere("abbé"));d(nCaractere("bébé"));d(nCaractere("ébété"));
						d4(nChaineLg("ABBE"),nChaineLg("abbé"),nChaineLg("bébé"),nChaineLg("ébété"));
						break;
			case 55:	for (nIndex=0;nIndex<kuVoyelleEnTout;nIndex++)
							printf("test de bVoyellE2[%d] %d\n",nIndex,bVoyellE2("aeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸã",&nIndex));break;
			case 60:	for (uFois=1;uFois<10;uFois++)
							printf("Tirage aléatoire dans [0..3]: %d.\n",nHasard(3));
						for (uFois=1;uFois<10;uFois++)
							printf("Tirage aléatoire dans [1..4]: %d.\n",uHasard(4));
						break;
			case 61:	zBof=zPgcd(60,32);
						zBof=zPgcd(170,153);
						zBof=zPpcm(60,32);
						zBof=zPpcm(170,153);
						break;
			case 62:	yIndex=-4;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						yIndex=-169;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						yIndex=-1234;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						for (yIndex=1;yIndex<kE16;yIndex*=13)
							printf("%ld=%s\n",yIndex,sPar3(yIndex));
						for (yIndex=1;yIndex<kE16;yIndex*=13)
							printf("%ld=%s\n",-yIndex,sPar3(-yIndex));
						yIndex=kxLongintMax;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						yIndex=kyLongintMin+1;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						break;
			case 65:	printf("Nombres premiers inférieurs à 100:");
						for (uFois=1;uFois<100;uFois++)
							if (bPremier(uFois))
								printf(" %d",uFois);
						printf(".\n");
						break;
			case 70:	Titrer("salut");
						Titrer("");
						Titrer("solo");
						break;
			case 80:	printf("Texte: %s.\n",sFois(4,'z'));
						break;
			case 90:	for (uFois=1;uFois<10;uFois++)
							nT[uFois]=5;
						MemIntRaz(nT,10);
						break;
			case 92:	qA.num=1;qA.den=2;qB.num=1;qB.den=3;qC.num=2;qC.den=1;
						tq("qA",qA);tq("qB",qB);tq("qC",qC);
						qD=qOpp(qA);tq("qD opp -A",qD);
						qD=qAdd(qA,qB);tq("qD A+B",qD);
						qD=qSub(qA,qB);tq("qD A-B",qD);
						qD=qAdd(qAdd(qA,qB),qSub(qA,qB));tq("qD (A+B)+(A-B)",qD);
						qD=qMul(qA,qB);tq("qD A*B",qD);
						qD=qDiv(qA,qB);tq("qD A/B",qD);
						qD=qDiv(qMul(qA,qB),qDiv(qA,qB));tq("qD (A*B)/(A/B)",qD);
						qD=qInv(qDiv(qMul(qA,qB),qDiv(qA,qB)));tq("qD (A/B)/(A*B)",qD);
						qD=qSub(qA,qA);tq("qD A-A",qD);
						break;
			case 95:	for (nIndex=0;nIndex<=50;nIndex++)
							printf("zFib(%d)=%ld\n",nIndex,zFib(nIndex));
						break;
			case 99:	FibCronometreR();break;
			default:
				break;
		}
	Appel1(sC2("KitTESTER,test n°",sEnt(iTest)));
}//KitTESTER

int bLettre(char cCaractere){
	//cCaractere est une lettre sans signe diacritique (ie sans accent,cédille,tilde…);cache la fonction isalpha()
	int bLettre=isalpha(cCaractere);
	return(bLettre);
}//bLettre

char cLettre(int iLettre){
	//rend le symbole alphanumQ de rang1 iLettre: "A" pour 1,"B" pour 2,…, "a" pr 27, prolongé par "0" pr 53,…, "9" pr 62.
	const char kcCaractereInconnu='?';
	char cAlphaNumerique[]="@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	char cLettre;
	//sd("cLettre",iLettre);
	//Assert1("cLettre",bCroit(1,iLettre,kuAlphaNumerique));
	cLettre=(bCroit(1,iLettre,kuAlphaNumerique)) ? cAlphaNumerique[iLettre] : kcCaractereInconnu;
	//printf("cLettre VAUT %c.\n",cLettre);
	return(cLettre);
}//cLettre

int nLettre(char cCaractere){
	//donne le rang1 de cCaractere: 1 pour "A",2 pour "B", etc, 27 pour "a", etc. Rend 0 si échec.
	//printf("Routine nLettre: la donnée est le caractère \"%c\".\n",cCaractere);
	int nLettre=0;
	if ( bCroit('A',cCaractere,'Z') )
		nLettre=cCaractere-'A'+1;
	else if ( bCroit('a',cCaractere,'z') )
		nLettre=kuAlphabet+cCaractere-'a'+1;
	Assert1("nLettre",nLettre>=0);
	return(nLettre);
}//nLettre

char *sLettre(int iLettre){
	//rend le symbole alphanumQ de rang1 iLettre: "A" pour 1,"B" pour 2,…, "a" pr 27, prolongé par "0" pr 53,…, "9" pr 62.
	return(sC0(cLettre(iLettre)));
}//sLettre

int bLettrE2(const char *ksTexte,int *pnCodeCaractereRg0){
	//ksTexte[*pnCodeCaractereRg0] ou Chaine[*pnCodeCaractereRg0..*pnCodeCaractereRg0+1] code une consonne;si vrai et 2 codes, passe au code suivant
	char cCode;
	int bLettrE2=0;
	assert(ksTexte!=0);
	Assert1("bLettrE2",bCroit(0,*pnCodeCaractereRg0,nChaineLg(ksTexte)));
	cCode=ksTexte[*pnCodeCaractereRg0];
	bLettrE2=isalpha(cCode);//vrai si consonnes ou voyelles sans signe diacritique (accent,cédille,tilde...)
	if ( !bLettrE2 && (*pnCodeCaractereRg0<nChaineLg(ksTexte)) ) {//l'accès à sTexte[nCodeCaractereRg+1] est valide
		bLettrE2=bVoyellE2(ksTexte,pnCodeCaractereRg0) || bConsonnE2(ksTexte,pnCodeCaractereRg0);
	}
	return(bLettrE2);
}//bLettrE2

int bLettreOuChiffre(char cCaractere){
	//cCaractere est une lettre sans signe diacritique (accent,cédille,tilde...);cache la fonction isalpha() ou un décit
	int bLettreOuChiffre=isalpha(cCaractere) || isdigit(cCaractere);
	return(bLettreOuChiffre);
}//bLettreOuChiffre

void Ligne(){
	printf("\n");
}//Ligne

int bLigne(){
	Ligne();
	return(1);
}//bLigne

int bLigne0(char *sLigneFin){
	printf("%s\n",sLigneFin);
	return(1);
}//bLigne0

int bLigne1(char *sLigneFin){
	printf("%s.\n",sLigneFin);
	return(1);
}//bLigne1

void Ligner(int nLigneBlancheEnTout){
	for (int uL=1;uL<=nLigneBlancheEnTout;uL++)
		Ligne();
}//Ligner

void LigneSauter(int nLigneEnTout){
	for (int uL=1;uL<=nLigneEnTout || !bLigne();uL++)
		printf("\n",uL);
}//LigneSauter

char *sListe(int iListe[],char cSeparateur){
	//rend "(2,5,6)" si iListe=[3,2,5,6] et cSeparateur est un parenthéseur. Intercale des blancs si bBlanc ci-dessous.
	char *sResultat;
	if (iListe[0]>=1){
		Assert2("sListe",yVecteurInf(iListe,1,iListe[0])>-kE5,yVecteurSup(iListe,1,iListe[0])<+kE6);
		char *sConnecteur="et,ou";
		int nIndex=2*(cSeparateur=='|')+(cSeparateur=='&');
		int bBlanc=nIndex>0 || bDans4(cSeparateur,' ',')',']','}');//vu char=int
		char *sDelimiteur=sC2(sC0( (cSeparateur=='+')? cSeparateur : ','),sE(bBlanc) );//Donc "+", "," ou ", ".
		Assert1("sListe79",nChaineLg(sDelimiteur)<=2);
		int nOctetMax=iListe[0]*sizeof(long) + 4 ;//+4 pr les délimiteurs ouvrant et sortant
		//d(nOctetMax);
		Assert1("sListe40",nOctetMax>4);
		char *sListe=sMalloC(nOctetMax);
			sListe[0]=sListe[1]=sListe[2]=sListe[3]='\0';//raze les 4 premiers octets tjrs alloués; 8 octets pr "-99 999,"
			for (int uE=1;uE<=iListe[0];uE++){
				int bDelimiter=(cSeparateur!='+' || uE<iListe[0] && iListe[uE+1]>=0);
				//d(uE);b(bDelimiter);
				if (bDelimiter)
					sprintf(sListe,"%s%s%s",sListe,sEnt(iListe[uE]),(uE+1<iListe[0])? sDelimiteur : ((uE<iListe[0])? sChoix(nIndex>0,sC3(" ",sItem(sConnecteur,nIndex),sE(bBlanc)),sDelimiteur) : ""));
				else sprintf(sListe,"%s%s%s",sListe,sEnt(iListe[uE]),(uE+1<iListe[0])? "" : ((uE<iListe[0])? sChoix(nIndex>0,sC3(" ",sItem(sConnecteur,nIndex),sE(bBlanc)),"") : ""));
			}
			Assert1("sListe45",nChaineLg(sListe)<nOctetMax);//vérifie a posteriori que le sMalloC était amplement dimensionné.
			if ( bDans2(cSeparateur,'(',')') ) sResultat=sP(sListe);
			else if ( bDans2(cSeparateur,'[',']') ) sResultat=sC(sListe);
			else if ( bDans2(cSeparateur,'{','}') ) sResultat=sA(sListe);
			else sResultat=sC1(sListe);//copie sListe et gère un nouveau sMalloC
		MallocGereR(sListe);
	}else sResultat=sVide();
	return(sResultat);
}//sListe

void ListeTesteR(){
	int iListe[]={4,-2,8,-3,-9};
	printf("%s.\n",sListe(iListe,'+') );
}//ListeTesteR

float rLn(float rN){
	//logarithme népérien
	float rLn=log(rN);
	return(rLn);
}//rLn

int nLog10(long yValeur){
	//nombre de symboles requis pour coder |yValeur| en base 10,signe compris. (Attention: 3 symboles pour coder 100 en base 10)
	int nLog10;
	long yV;
	yV=labs(yValeur);
	Assert1("nLog10",yV>=0);
	nLog10=(yValeur<=0);//1 signe pr le signe moins
	while (yV>0){
		yV=yV/10;
		nLog10++;
	}
	return(nLog10);
}//nLog10

double rLog10(double rN){
	//logarithme en base 10
	double rLog=log10(rN);
	return(rLog);
}//rLog10

int nLog2(long yValeur){
	//nombre de symboles requis pour coder yValeur en complément à 2. (Attention: 4 symboles pour coder 8 en base 2: 1000)
	int nLog2;
	long yV;
	yV=labs(yValeur);
	Assert1("nLog2",yV>=0);
	nLog2=(yValeur<=0);//1 signe pr le signe moins
	while (yV>0){
		yV=yV/2;
		nLog2++;
	}
	return(nLog2);
}//nLog2

double rLog2(double rN){
	//logarithme en base 2
	double rLog2=log2(rN);
	return(rLog2);
}//rLog2

int bMajuscule(char cCaractere){
	//cCaractere est une lettre majuscule sans signe diacritique (accent,cédille,tilde...);cache la fonction isupper()
	int bMajuscule=isupper(cCaractere);
	return(bMajuscule);
}//bMajuscule

char *sMajuscule(char *sCaractere){
	//rend la majuscule qui correspond à sCaractere 
	int uCar,nPlace;
	char *sMajuscule;
	int nItemEnTout=nItem(sAlphabetMinusculE);
	for (nPlace=0,uCar=1;uCar<=nItemEnTout && nPlace==0;uCar++)
		if (bChaineEgale(sCaractere,sItem(sAlphabetMinusculE,uCar)))
			nPlace=uCar;
	sMajuscule=(nPlace==0)? sC1(sCaractere) : sItem(sAlphabetMajusculE,nPlace);
	return(sMajuscule);
}//sMajuscule

char *sMajusculer(char *sTexte){
	//rend sTexte entièrement majusculé
	int nC,nRang,nTexteLg=nChaineLg(sTexte);//ATTENTION: strlen("à")==2 et strlen("a")==1,dc nTexteLg>nb de symboles si spéciaux. 
	char *sMajusculer=sVide();
	//s(sTexte);
		for (nC=0;nC<nTexteLg;nC++){
			int bExtension=sTexte[nC]==kcExtensioN;
			nRang=nItemRang(sChainon(sTexte,nC,nC),sAlphabetMinusculE);
			sMajusculer=sC2(sMajusculer,sMajuscule(sChainon(sTexte,nC,nC+bExtension)));
			nC+=bExtension;
		}
	//s(sMajusculer);
	return(sMajusculer);
}//sMajusculer

char *sMalloC(int nOctat){//ne pas confondre avec calloc(nbBloc,nbBlocTaille) qui raze nbBloc*nbBlocTaille octets
	const int knMallocGarde=8*1;	//garde sur chq malloc
	const int kuAntiSlashZero=1;	//encombrt du caractère "\0" qui délimite les chaînes de caractères
	assert(nOctat>=0);
	int nSize=nOctat+kuAntiSlashZero;
	if (kbMallocGardE){
		nSize=nFrontiere8(nSize+knMallocGarde);
		assert(nSize%8==0);
	}
	char *sMalloc=malloc(nOctat+kuAntiSlashZero);
	return(sMalloc);
}//sMalloC

void MallocGereR(char *sMalloc){
	//empile l'allocO de sMalloc sur l'Espace Courant EC; Si cette allocO sature l'EC, libère l'-espace le + ancien.
	const int kbVoir=0;
	const int kbConfirmer=0;
	const int kbDeboguer=0;//à 1 pr afficher ttes les chn (présentes ds le dernier espace) qui ont été restituées avant plantG
	const int kbDebug=kbDeboguer && kbConfirmer;
	int nAlloc,zsEspaceSuivant,nLibereh;
	char *sAlloc;
	assert(sMalloc);
	yptrMalloC[spMalloC][ipMalloC[spMalloC]++]=(long) sMalloc;
	if (ipMalloC[spMalloC]>=kuPtrEnToutParEspacE){
		if (kbVoir) printf("ipMalloC[%d]=%d et kuPtrEnToutParEspacE=%d.\n",spMalloC,ipMalloC[spMalloC],kuPtrEnToutParEspacE);
		assert(ipMalloC[spMalloC]==kuPtrEnToutParEspacE);
		if (kbConfirmer)
			Confirmer("*** Changement d'espace de chaînes de caractères");
		zsEspaceSuivant=(spMalloC+1)%kuMallocEspaceEnTouT;
		if (kbVoir) printf("Espace courant n°%d=[0,%d[.",spMalloC,kuPtrEnToutParEspacE);
		if (kbVoir) printf("Espace suivant n°%d=[0,%d[.\n",zsEspaceSuivant,ipMalloC[zsEspaceSuivant]);
		assert(bDans2(ipMalloC[zsEspaceSuivant],0,kuPtrEnToutParEspacE));//0 si le nouvel espace est utilisé pour la 1ère fois
		for (nLibereh=nAlloc=0;nAlloc<ipMalloC[zsEspaceSuivant];nAlloc++){
			sAlloc=(char *) yptrMalloC[zsEspaceSuivant][nAlloc];
			if (kbDebug && sAlloc!=0) printf("<%s>.\n",sAlloc);
			if (sAlloc!=NULL){
				nLibereh++;
				free(sAlloc);//restitue, ou plante!
				sAlloc=NULL;//force le plantage si erreur de conception
			}
		}
		assert(bDans2(nLibereh,0,kuPtrEnToutParEspacE));
		for (nAlloc=0;nAlloc<kuPtrEnToutParEspacE;nAlloc++)
			yptrMalloC[zsEspaceSuivant][nAlloc]=0;
		if (kbVoir) printf("L'espace suivant n°%d a été libéré et razé. Il contenait %d pointeurs.\n",zsEspaceSuivant,nLibereh);
		spMalloC=zsEspaceSuivant;
		ipMalloC[spMalloC]=0;//premier index valide sur le nouvel espace courant  
		if (kbConfirmer)
			printf("*** Changement d'espace %d terminé.\n",spMalloC);
		nMallocEspaceEnTouT++;//pr info
	}
}//MallocGereR

void MallocGereR0(){
	//raze ipMalloC[] et le 1er espace dédié pointeurs sur les chaînes de caractR et entiers littéraux
	const int knEspaceInitial=0;
	assert(kuMallocEspaceEnTouT%2==0);//nb d'espaces utilisés en rouleau pour gérer automatiqt les allocations mémoire.
	assert(kuMallocEspaceEnTouT>2);//les chaines récentes peuvent être à cheval sur 2 espaces consécutifs.
	VecteurRazer(ipMalloC,0,kuMallocEspaceEnTouT-1);
	for (int nPointeur=0;nPointeur<kuPtrEnToutParEspacE;nPointeur++)
		yptrMalloC[knEspaceInitial][nPointeur]=0;
}//MallocGereR0

void Marner(int iValeur,int *piMin,int *piMax){
	*piMin=iInf(*piMin,iValeur);
	*piMax=iSup(*piMax,iValeur);
}//Marner

void Marner0(int *piMin,int *piMax){
	*piMin=kuIntegerMax;
	*piMax=kiIntegerMin;
}//Marner0

int iMax(int iA,int iB){
	//rend max(iA,iB);identique à iSup(iA,iB).
	int iMax=(iA<iB)?iB:iA;
	return(iMax);
}//iMax

double rMax(double dA,double dB){
	//rend sup(dA,dB)
	double rMax=(dA>dB)?dA:dB;
	return(rMax);
}//rMax

long yMax(long yA,long yB){
	//rend max(yA,yB);identique à ySup(yA,yB)
	long yMax=(yA>yB)?yA:yB;
	return(yMax);
}//yMax

void MemIntRaz(int piMemOrigine[],int nItemEnTout){
	Assert2("MemIntRaz",piMemOrigine!=0,nItemEnTout>=0);
	MemIntValuer(piMemOrigine,nItemEnTout,0);
}//MemIntRaz

void MemIntValuer(int piMemOrigine[],int nItemEnTout,int iValeur){
	int nItem;
	Assert2("MemIntValuer",piMemOrigine!=0,nItemEnTout>=0);
	for (nItem=0; nItem<nItemEnTout; nItem++){
		piMemOrigine[nItem]=iValeur;
	}
}//MemIntValuer

void MemLongRaz(int pyMemOrigine[],int nItemEnTout){
	Assert2("MemLongRaz",pyMemOrigine!=0,nItemEnTout>=0);
	MemLongValuer(pyMemOrigine,nItemEnTout,0);
}//MemLongRaz

void MemLongValuer(int pyMemOrigine[],int nItemEnTout,long yValeur){
	int nItem;
	Assert2("MemLongValuer",pyMemOrigine!=0,nItemEnTout>=0);
	for (nItem=0; nItem<nItemEnTout; nItem++){
		pyMemOrigine[nItem]=yValeur;
	}
}//MemLongValuer

int iMin(int iA,int iB){
	//rend min(iA,iB);identique à iInf(iA,iB).
	int iMin=(iA>iB)?iB:iA;
	return(iMin);
}//iMin

double rMin(double dA,double dB){
	//rend inf(dA,dB)
	double rMin=(dA<dB)?dA:dB;
	return(rMin);
}//rMin

long yMin(long yA,long yB){
	//rend min(yA,yB);identique à yInf(yA,yB)
	long yMin=(yA>yB)?yB:yA;
	return(yMin);
}//yMin

int bMinuscule(char cCaractere){
	//cCaractere est une lettre minuscule signe diacritique (accent,cédille,tilde...);cache la fonction islower()
	int bMinuscule=islower(cCaractere);
	return(bMinuscule);
}//bMinuscule

char *sMinuscule(char *sCaractere){
	//rend la minuscule qui correspond à sCaractere 
	int uCar,nPlace;
	char *sMinuscule;
	int nItemEnTout=nItem(sAlphabetMajusculE);
	for (nPlace=0,uCar=1;uCar<=nItemEnTout && nPlace==0;uCar++)
		if (bChaineEgale(sCaractere,sItem(sAlphabetMajusculE,uCar)))
			nPlace=uCar;
	sMinuscule=(nPlace==0)? sCaractere : sItem(sAlphabetMinusculE,nPlace);
	return(sMinuscule);
}//sMinuscule

int bModeCaractere(){
	return(muModeCaracterE[ipModeCaracterE]);
}//bModeCaractere

void ModeCaractere(int tMode){
	Assert22("ModeCaractere,tMode,ipModeCaracterE",bTrit(tMode),ipModeCaracterE+1<kuModeCaractereMax,tMode,ipModeCaracterE);
	if (tMode>=0){
		muModeCaracterE[++ipModeCaracterE]=tMode;
	}else ipModeCaracterE=iSup(1,ipModeCaracterE-1);
	//d(ipModeCaracterE);
}//ModeCaractere

void ModeCaracteriser(int cListe[]){
	//si cListe[0]>0, renomme les index avec la cListe;sinon,reprend l'ordre alphabétique usuel
	if (cListe[0]>0)
		VecteurCopier(cListe,0,cListe[0],icModeCaracterE);
	else VecteurIndexer(icModeCaracterE,1,kuModeCaractereMax);
}//ModeCaracteriser

void ModeChiffre(int tMode){
	Assert2("ModeChiffre",bTrit(tMode),ipModeChiffrE3+1<kuModeChiffreMaX);
	//printf("0: muModeChiffrE3[%d]=%d.\n",ipModeChiffrE3,muModeChiffrE3[ipModeChiffrE3]);
	if (tMode>=0){
		muModeChiffrE3[++ipModeChiffrE3]=tMode;
	}else ipModeChiffrE3=iSup(1,ipModeChiffrE3-1);
	//printf("1: muModeChiffrE3[%d]=%d.\n",ipModeChiffrE3,muModeChiffrE3[ipModeChiffrE3]);
}//ModeChiffre

int bModeChiffre(){
	//vrai ssi les entiers sont affichés par paquets de 3 décits via sPar3().
	//printf("2:%d.\n",ipModeChiffrE3);
	int bChiffre=muModeChiffrE3[ipModeChiffrE3]>0;
	return(bChiffre);
}//bModeChiffre

int iModulo(long yDividende,int uDiviseur){
	//rend |yDividende|%uDiviseur muliplié par le signe de iDividende 
	int iModulo;
	Assert1("iModulo0",uDiviseur>0);
	iModulo=ySignePres( yDividende<0,nModulo(labs(yDividende),uDiviseur) );
	Assert1("iModulo1",bCroit(0,abs(iModulo),uDiviseur-1)) ;
	return(iModulo);
}//iModulo

int nModulo(long yDividende,int uDiviseur){
	//rend le modulo POSITIF de yDividende,ie tel que 0≤modulo<uDiviseur 
	int nModulo,bNegatif;
	long xDividende;
	Assert1("nModulo0",uDiviseur>0);
	bNegatif=yDividende<0;
	xDividende=labs(yDividende);
	nModulo=xDividende%uDiviseur;
	if (bNegatif && nModulo>0)
		nModulo=uDiviseur-nModulo;
	//ld3(xDividende,uDiviseur,nModulo);
	Assert1("nModulo1",bCroit(0,nModulo,uDiviseur-1));
	return(nModulo);
}//nModulo

long zModulo(long yDividende,long xDiviseur){
	//rend le modulo POSITIF de yDividende,ie tel que 0≤modulo<xDiviseur 
	int bNegatif;
	long xDividende,zModulo;
	Assert1("zModulo0",xDiviseur>0);
	bNegatif=yDividende<0;
	xDividende=labs(yDividende);
	zModulo=xDividende%xDiviseur;
	if (bNegatif && zModulo>0)
		zModulo=xDiviseur-zModulo;
	//ld3(xDividende,xDiviseur,zModulo);
	Assert1("zModulo1",bCroit(0,zModulo,xDiviseur-1));
	return(zModulo);
}//zModulo

int uModulo1(long zDividende,int uDiviseur){
	//rend le modulo standard à ceci près que le résultat 0 éventuel est remplacé par uDiviseur: uModulo1(12,4)=4 
	int nModulo;
	Assert2("uModulo1a",zDividende>=0,uDiviseur>0);
	nModulo=zDividende%uDiviseur;
	if (nModulo==0)
		nModulo=uDiviseur;
	if (0) ld3(zDividende,uDiviseur,nModulo);
	Assert1("uModulo1b",bCroit(1,nModulo,uDiviseur));
	return(nModulo);
}//uModulo1

q qMul(q qA,q qB){
	//produit de deux rationnels
	q qMul;
	int xPgcd;
	Assert2("qMul",qA.den>0,qB.den>0);
	qMul.num=qA.num*qB.num;
	qMul.den=qA.den*qB.den;
	xPgcd=zPgcd(abs(qMul.num),abs(qMul.den));
	qMul.num/=xPgcd;
	qMul.den/=xPgcd;
	return(qMul);
}//qMul

ri riMul(ri riA,ri riB){
	//produit de deux nombres complexes
	ri riMul;
	riMul.r=riA.r*riB.r-riA.i*riB.i;
	riMul.i=riA.r*riB.i+riA.i*riB.r;
	return(riMul);
}//riMul

char *sNbre(int bFormatEntier,float fValeur){
	char *sNbre=sE(10);
	if (bFormatEntier)
		sprintf(sNbre,"%ld",yArrondi(fValeur));
	else sprintf(sNbre,"%.2f",fValeur);
	return(sNbre);
}//sNbre

char *sNbre1(int bFormatEntier,float fValeur,int nCaractereEnTout){
	//cadre fValeur à droite sur nCaractereEnTout caractères
	char *sNbre1=sE(nCaractereEnTout);
	if (bFormatEntier)
		sprintf(sNbre1,"%ld",yArrondi(fValeur));
	else sprintf(sNbre1,"%.2f",fValeur);
	sNbre1=sChaine1(sC2(sE(nCaractereEnTout),sNbre1),nCaractereEnTout);
	return(sNbre1);
}//sNbre1

char *sNiet(int bOui,char *sQuoi){
	//rend sQuoi, ou "non" suivi de sQuoi si bOui est faux
	char *sNiet=sC2b(sChoix(bOui,"","non"),sQuoi);
	return(sNiet);
}//sNiet

char *sNon(int bNegativer,char *sVerbe){
	//rend sVerbe, encadré avec "ne" et "pas" si bNegativer.
	#define kuNeLg 3//"n'" ou "ne "
	#define kuPasLg 4//" pas"
	char *sNon=sMalloC(kuNeLg+nChaineLg(sVerbe)+kuPasLg);
		if ( bNegativer ){
			strcpy(sNon,sChoix(bVoyelle(sVerbe,0),"n'","ne "));
			strcat(sNon,sVerbe);
			strcat(sNon, " pas");
		}
		else strcpy(sNon,sVerbe);
	MallocGereR(sNon);
	return(sNon);
}//sNon

int bNul(double dNombre){
	//vrai ssi la donnée est assimilable à 0.0
	int bNul;
	double dPositif;
	dPositif=dNombre;
	if (dPositif<0.0)
		dPositif=-dPositif;
	if (dPositif<=fEpsiloN)
		bNul=kV;
	else bNul=kF;
	return(bNul);
}//bNul

int briNul(ri riA){
	int bZero=bNul(riA.r) && bNul(riA.i);
	return(bZero);
}//briNul

q qOpp(q qA){
	//opposé d'un rationnel
	q qOpp;
	qOpp.num=-qA.num;
	qOpp.den=qA.den;
	return(qOpp);
}//qOpp

ri riOpp(ri riA){
	//opposé d'un complexe
	ri riOpp;
	riOpp.r=-riA.r;
	riOpp.i=-riA.i;
	return(riOpp);
}//riOpp

char *sOk(int bOui){
	//rend "OUI" ou "non" selon bOui 
	#define kuOuiOuNonLg 3
	char *sOk=sMalloC(kuOuiOuNonLg);
		sOk[0]='\0';
		strcat(sOk,(bOui)? "OUI": "non");
	MallocGereR(sOk);
	return(sOk);
}//sOk

char *sOui(int bPositiver,char *sVerbe){
	//rend sVerbe, encadré avec "ne" et "pas" si bPositiver est faux.
	#define kuNeLg 3//"n'" ou "ne "
	#define kuPasLg 4//" pas"
	char *sOui=sMalloC(kuNeLg+nChaineLg(sVerbe)+kuPasLg);
		if ( !bPositiver ){
			strcpy(sOui,sChoix(bVoyelle(sVerbe,0),"n'","ne "));
			strcat(sOui,sVerbe);
			strcat(sOui, " pas");
		}
		else strcpy(sOui,sVerbe);
	MallocGereR(sOui);
	return(sOui);
}//sOui

int bPair(int iEntier){
	int bPair=bFaux(iEntier%2);
	assert(bBool(bPair));
	return (bPair);
}//bPair

char *sP(char *sEntreParenthese){
	//rend sEntreParenthese précédé de "(" et suivi de ")"
	const int kuUnDelimiteur=1;
	assert(sEntreParenthese!=0);	
	char *sP=sMalloC(kuUnDelimiteur+nChaineLg(sEntreParenthese)+kuUnDelimiteur);
		strcpy(sP,sC3("(",sEntreParenthese,")"));
	//char *sP=sC3("(",sEntreParenthese,")");
	return(sP);
}//sP

char *sP1(char *sA,int iIndex){
	//renvoie sA(iIndex)
	return(sC2(sA,sP(sPar3(iIndex))));
}//sD1

char *sP2(char *sA,int iIndexMin,int iIndexMax){
	//renvoie sA(iIndexMin,iIndexMax)
	return( sC2(sA,sP(sC2v(sPar3(iIndexMin),sPar3(iIndexMax)))) );
}//sD2

char *sPar3(long yEntier){
	//convertit yEntier en chaîne dans laquelle les groupes de 3 chiffres sont séparés par des kcSeparateur qui sont des blancs,eg 12 345.
	int uC,nChiffre,nD,nDecit,nCar;
	char kcSeparateur=' ';
	char *sP3;
	long zEntier;
	int bSigne;
	if (yEntier!=kyLongintMin){
		sP3=sMalloC(63);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
			bSigne=(yEntier<0);
			zEntier=zAbs(yEntier);//défini vu yEntier!=kyLongintMin
			sprintf(sP3,"%ld",zEntier);//yEntier tient forcément ds sP3 vu allocation généreuse: 4 octets alloués là où 21 bits suffisent.
			nChiffre=nChaineLg(sP3);
			nDecit=nChiffre+(nChiffre-1)/3;
			nCar=0;
			sP3[bSigne+nDecit]='\0';
			for (nD=bSigne+nDecit,uC=1;uC<=nChiffre;uC++){
				sP3[--nD]='0'+zEntier%10;
				if (nD>=bSigne && (uC%3==0))
					sP3[--nD]=kcSeparateur;
				zEntier=zEntier/10;
				nCar++;
			}
			Assert2("sPar3",zEntier==0,nD+1>=bSigne);
			if (bSigne)
				sP3[0]='-';
		MallocGereR(sP3);
	} else {//fabriquer sPar3(kyLongintMin) à partir de sPar3(kxLongintMax)
		Assert1("sPar3 sPar3 sPar3",0);
		sP3=sPar3(kxLongintMax);
		Assert1("sPar3 pour kyLongintMin",sP3[nChaineLg(sP3)-1]=='7');//dc li+1 a du sens: pas de retenue à propager.
		sP3[nChaineLg(sP3)-1]+=1;//en complément à 2, le plus petit nombre négatif est, en valeur absolue, le plus grand positif + 1.
		sP3=sC2("-",sP3);
	}
	return(sP3);
}//sPar3

char *sPas(char *sVerbe,int bNegativer){
	//rend sVerbe tel quel,ou négativé avec "ne"..."pas" si bNegativer 
	#define kuNeLg 3//"n'" ou "ne "
	#define kuPasLg 4//" pas"
	char *sPas=sMalloC(kuNeLg+nChaineLg(sVerbe)+kuPasLg);
		if (bNegativer){
			strcpy(sPas,sChoix(bVoyelle(sVerbe,0),"n'","ne "));
			strcat(sPas,sVerbe);
			strcat(sPas, " pas");
		}
		else strcpy(sPas,sVerbe);
	MallocGereR(sPas);
	return(sPas);
}//sPas

void Pause(){//suspend l'exécution et attend une frappe clavier minimale
	char cCar;
	printf(" Pause affichage... valider SVP (touche entrée) ou stopper l'exécution en tapant autre chose ");
	scanf("%c",&cCar);
	if (cCar!='\n')
		Stop(1);
	//printf("\n");
}//Pause

int nbPermutation(int uDistinct[]){
	//rend le nb de permutations d'éléments dénombré ds la liste uDistinct[] censée ctenir des entiers non nuls distincts 
	int dE,nbPermutation;
	Assert1("nPermutation",bVecteurDistinct(uDistinct,1,uDistinct[0],k1NonNul));
	for (nbPermutation=0,dE=1;dE<=uDistinct[0];dE++)
		if (uDistinct[dE]>uDistinct[uModulo1(dE+1,uDistinct[0])])
			nbPermutation++;
	return(nbPermutation);
}//nbPermutation

long xPgcd(long xA,long xB){//O(lg(Sup(xA,xB)))
	//rend le Plus Grand Commun Diviseur de xA et xB;en O(lg(Sup(xA,xB))) prouvé par Lamé en 1844 cf PLI Schrijver p54
	const int bVoir=0;
	long xPgcd;
	long xGrand,xPetit,zReste;
	Assert2("xPgcd1",xA>0,xB>0);
		xGrand=ySup(xA,xB);
		xPetit=yInf(xA,xB);
		while (xPgcd=xPetit,zReste=xGrand % xPetit,zReste>0){
			if (bVoir) d3(xPgcd,xGrand,xB);
			xGrand=xPetit;
			xPetit=zReste;
		};
		if (bVoir) printf("Le pgcd de %ld et %ld vaut %ld.\n",xA,xB,xPgcd);
		Assert3("zPgcd9", xPgcd>0, xPgcd>0 && xA % xPgcd==0, xPgcd>0 && xB % xPgcd==0);
	return(xPgcd);
}//xPgcd

long zPgcd(long yA,long yB){//O(lg(Sup(|yA|,|yB|)))
	//rend le Plus Grand Commun Diviseur de yA et yB;en O(lg(Sup(|yA|,|yB|))) prouvé par Lamé en 1844 cf PLI Schrijver p54
	long zPgcd,zA=labs(yA),zB=labs(yB);
	Assert4("zPgcd1",yA!=kyLongintMin,yB!=kyLongintMin,zA>=0,zB>=0);//>=0 puisque yA!=kyLongintMin et yB!=kyLongintMin
	zPgcd=(zA>0 && zB>0)? xPgcd(zA,zB): 0;
	return(zPgcd);
}//zPgcd

char *sPhrase0(char *sTexte){
	//rend sTexte avec 1ère lettre majusculée;n'ajoute pas de point final contrairt à sPhrase1
	//tt("sPhrase0Avant:",sG(sTexte));
	int nRang=0;
	int nTexteLg=nChaineLg(sTexte);
	bBof=bLettrE2(sTexte,&nRang);//ajoute k-1 à nRang si le premier caractère est codé sur k codes caractères.
	char *sDebut=sChainon0(sTexte,nRang);
	char *sPhrase0=sC2(sMajuscule(sDebut),sChainon(sTexte,nRang+1,nTexteLg));
	//tt("sPhrase0Apres:",sPhrase);
	return(sPhrase0);
}//sPhrase0

char *sPhrase1(char *sTexte){
	//rend sTexte avec 1ère lettre majusculée et un point final si pas déjà là
	//tt("sPhrase1Avant:",sG(sTexte));
	int nRang=0;
	int nTexteLg=nChaineLg(sTexte);
	int bPointDejaLa=bChaineEgale(sChainon(sTexte,nTexteLg-1,nTexteLg-1),".");
	bBof=bLettrE2(sTexte,&nRang);//ajoute k-1 à nRang si le premier caractère est codé sur k codes caractères.
	char *sDebut=sChainon0(sTexte,nRang);
	char *sPhrase1=sC3(sMajuscule(sDebut),sChainon(sTexte,nRang+1,nTexteLg),bPointDejaLa ? "":".");
	//tt("sPhrase1Apres:",sPhrase1);
	return(sPhrase1);
}//sPhrase1

char *sPhrase2(char *sTexte){
	//rend sTexte entièrement majusculé et ajoute un point final si pas déjà là
	int nTexteLg=nChaineLg(sTexte);
	//ss("sPhrase2Avant:",sG(sTexte));
	int bPointDejaLa=bChaineEgale(sChainon(sTexte,nTexteLg-1,nTexteLg-1),".");
	char *sP2=sC2(sMajusculer(sTexte),bPointDejaLa ? "":".");
	return(sP2);
}//sPhrase2

long yPlafond(double rN){
	double yPlafond=ceil(rN);
	return(yPlafond);
}//yPlafond

long yPlancher(double rN){
	double yPlancher=floor(rN);
	return(yPlancher);
}//yPlancher

char *sPluriel(long zEffectif,char *sSingulier){
	//(3,"fruit") rend "3 fruits" et (3,"fruit$ rouge$") rend "3 fruits rouges";(3,"a$ vu") rend "3 ont vu".
	int nC,nD,nLg,mPosition;
	char *sPluriel;
	Assert2("sPluriel",zEffectif>=0,sSingulier!=0);
	sPluriel=sC2b(sPar3(zEffectif),sSingulier);
	//"a" au pluriel = "ont"
		mPosition=mChainonPos(" a$",sPluriel);
		if (mPosition>=0 && zEffectif>1)
			sPluriel=sC3b(sChainon0(sPluriel,mPosition-1),"ont",sChainon1(sPluriel,mPosition+4));
	nLg=nChaineLg(sPluriel);
	mPosition=mChainePos('$',sPluriel);
	if (mPosition>=0){//si zEffectif>1,remplacer les '$' par des 's';sinon, retirer ts les '$'.
		if (zEffectif>1){
			while (mPosition=mChainePos('$',sPluriel),mPosition>=0)
				sPluriel[mPosition]=(bChaineEgale(sChainon(sPluriel,mPosition-2,mPosition-1),"au"))? 'x' : 's';
		} else {
			for (nD=0,nC=0;nC<nLg;nC++)
				if (sPluriel[nC]!='$')
					sPluriel[nD++]=sPluriel[nC];
			sPluriel[nD++]='\0';
		}
	}else if (zEffectif>1 && sPluriel[nLg-1]!='s')
		sPluriel=sC2(sPluriel,sC0( (bChaineEgale(sChainon(sPluriel,mPosition-2,mPosition-1),"au"))? 'x' : 's') );
	return(sPluriel);//rend "3 s" si (nCardinal=3 et sSingulier est la chaîne vide)
}//sPluriel

char *sPluriel0(long zEffectif,char *sSingulier){
	//comme sPluriel mais (0,"fruit") rend "aucun fruit".
	char *sPluriel0=sPluriel1(zEffectif,sSingulier,!k1Feminin);
	return(sPluriel0);
}//sPluriel0

char *sPluriel1(long zEffectif,char *sSingulier,int bFeminin){
	//comme sPluriel mais (0,"fruit",!k1Feminin) rend "aucun fruit" et (0,"pomme",k1Feminin) rend "aucune pomme".
	char *sPluriel1;
	Assert2("sPluriel0",zEffectif>=0,sSingulier!=0);
	sPluriel1=sPluriel(zEffectif,sSingulier);
	if (zEffectif==0)
		sPluriel1=sC2b((bFeminin)?"aucune": "aucun",sChainon(sPluriel1,2,nChaineLg(sPluriel1)));
	return(sPluriel1);//rend "3 s" si (nCardinal=3 et sSingulier est la chaîne vide)
}//sPluriel1

char *sPluriel2(char *sVerbe,long zEffectif,char *sSingulier){
	//("a",0,"fruit") rend "n'a aucun fruit".
	char *sPluriel2=sPluriel3(sVerbe,zEffectif,sSingulier,!k1Feminin);
	return(sPluriel2);//rend "3 s" si (nCardinal=3 et sSingulier est la chaîne vide)
}//sPluriel2

char *sPluriel3(char *sVerbe,long zEffectif,char *sSingulier,int bFeminin){
	//("a",0,"pomme",k1Feminin) rend "n'a aucune pomme".
	char *sPluriel3;
	Assert2("sPluriel3",zEffectif>=0,sSingulier!=0);
	sPluriel3=sPluriel(zEffectif,sSingulier);
	if (zEffectif==0)
		sPluriel3=sC2b((bFeminin)?"aucune": "aucun",sChainon(sPluriel3,2,nChaineLg(sPluriel3)));
	sPluriel3=sC4((zEffectif==0) ? sChoix(bVoyelle(sVerbe,0),"n'","ne ") : "",sVerbe," ",sPluriel3);
	return(sPluriel3);//rend "3 s" si (nCardinal=3 et sSingulier est la chaîne vide)
}//sPluriel3

char *sPluriel4(long zEffectif,char *sSingulier,int bFeminin){
	//sPluriel étendu au verbe encadré par des $: (2,"chemin$ $existe$",0) rend "2 chemins existent".
	char *sConjug0="a,doit,est,fait,va";
	char *sConjug1="ont,doivent,sont,font,vont";
	char *sPluriel4;
	int mVerbe0=mChainonPos(" $",sSingulier);
	if (mVerbe0>0){
		char *sAvant=sChainon0(sSingulier,mVerbe0-1);
		char *sApres=sChainon1(sSingulier,mVerbe0+1);
		int mVerbe1=mChainonPos("$ ",sApres);
		char *sVerbe0=sChainon0(sApres,mVerbe1);
		sApres=sChainon1(sSingulier,mVerbe0+1+nChaineLg(sVerbe0)+1);
		if (zEffectif==0){//"$a$" donne "n'a"
			int bVoyel=bVoyelle(sChainon1(sSingulier,mVerbe0+2),0);
			sVerbe0=sChainon(sVerbe0,1,nChaineLg(sVerbe0)-2);
			sPluriel4=sPluriel1(zEffectif,sC3(sAvant,sChoix(bVoyel," n'"," ne "),sC2b(sVerbe0,sApres)),bFeminin);
		}else if (zEffectif>1){//"$a$" donne "ont"
			sVerbe0=sChainon(sVerbe0,1,nChaineLg(sVerbe0)-2);
			int nRang=nItemRang(sVerbe0,sConjug0);
			sPluriel4=sPluriel1(zEffectif,sC3b(sAvant,(nRang>0)?sItem(sConjug1,nRang):sC2(sVerbe0,"nt"),sApres),bFeminin);
		}else sPluriel4=sPluriel1(zEffectif,sC3b(sAvant,sVerbe0,sApres),bFeminin);
	}else sPluriel4=sPluriel1(zEffectif,sSingulier,bFeminin);
	return(sPluriel4);
}//sPluriel4

char *sPluriel5(long zEffectif,char *sSingulier,int bFeminin){
	char *sPluriel5=sPluriel4(zEffectif,sSingulier,bFeminin);
	if (zEffectif==1)
		sPluriel5=sChaineSubstituer(sPluriel5,"1","un");
	return(sPluriel5);
}//sPluriel5

char *sPluriel6(long zEffectif,char *sSingulier,int bFeminin,int dPlusieursSeuil){
	//comme sPluriel5 à ceci près que si zEffectif atteint uPlusieursSeuil, zEffectif est remplacé par "plusieurs"
	Assert1("sPluriel6",dPlusieursSeuil>1);//sinon, conflit avec zEffectif==1 ds sPluriel5.
	char *sPluriel6=sPluriel5(zEffectif,sSingulier,bFeminin);
	if (zEffectif>=dPlusieursSeuil)
		sPluriel6=sChaineSubstituer(sPluriel6,sPar3(zEffectif),"plusieurs");
	return(sPluriel6);
}//sPluriel6

int mPoidsFort(long yEntier){
	//rend le bit de poids fort de yEntier,eg 3 si yEntier=13 puisque 13 s'écrit 1101 en base 2;rend -1 si non défini
	int yE,mPoidsFort;
	mPoidsFort=-1;
	if (yEntier>0){
		yE=yEntier;
		while (yE>0){
			yE=yE/2;
			mPoidsFort++;
		}
	}
	Assert1("mPoidsFort",bCroit(-1,mPoidsFort,63));
	return(mPoidsFort);
}//mPoidsFort

char *sPourcent(int nNumerateur,int nDenominateur){//voir aussi sSurcout
	//rend (100*nNumerateur)/nDenominateur.
	Assert1("sPourcent: dénomisateur nul",nDenominateur);
	char *sPourcent=sC2(sDiv(100*nNumerateur,nDenominateur),"%");
	return(sPourcent);
}//sPourcent

long zPpcm(long xA,long xB){
	//rend le Plus Petit Commun Multiple de xA et xB strictement positifs
	long zPpcm=0;
	//tee("xA,xB",xA,xB);
	Assert3("zPpcm1",bKitAmorceR,xA>0,xB>0);
	zPpcm=(xA*xB)/zPgcd(xA,xB);
	//printf("Le ppcm de %ld et %ld vaut %ld.\n",xA,xB,zPpcm);
	Assert1("zPpcm2",zPpcm>0);
	return(zPpcm);
}//zPpcm

int bPremier(int iNombre){//O(rac(iNombre))
	//vrai ssi iNombre est supérieur à 1 et n'est divisible que par lui-même et par 1
	int uN;
	int bPremier;
	Assert1("bPremier",bKitAmorceR);
	bPremier=iNombre>1;
	if (bPremier)//nRac(iNombre) est calculable
		for (uN=nRac(iNombre);uN>1;uN--)
			bPremier=bPremier && iNombre%uN!=0;
	return(bPremier);
}//bPremier;

int nPremier(int nRangDuNombrePremier){
	//rend le nombre premier de rang1 nRangDuNombrePremier. Puisque le 1er nombre premier est 2,ie nPremier(1)=2, nPremier(2)=3, nPremier(3)=5...
	int nPremier;
	if (!bCroit(1,nRangDuNombrePremier,kuPremierRgMax))
		d2(nRangDuNombrePremier,kuPremierRgMax);
	Assert2("nPremier",bKitAmorceR,bCroit(1,nRangDuNombrePremier,kuPremierRgMax));
	nPremier=uPremieR[nRangDuNombrePremier];
	return(nPremier);
}//nPremier;

void PremierAmorceR(){
	//remplit une fois pour toutes le tableau uPremieR[] avec les kuPremierMax 1ers nombres premiers 
	int uE,uFois,uMultiple,ipPremier;
	int bVoir=kF;
	#define knPremierUltime 3*kE5 //le dernier nbre premier est 224 737.
	int nPremier[1+knPremierUltime];
	//remplir nPremier[] avec les entiers consécutifs depuis 2 et rayer les multiples de chaq entier (algo dit du "crible d'Eratosthène")
		for (uE=2;uE<=knPremierUltime;uE++)
			nPremier[uE]=uE;
		if (bVoir) VecteurVoir("nPremier",&nPremier[0],1,knPremierUltime);//entiers consécutifs depuis 1
		for (uFois=2;uFois<=knPremierUltime;uFois++){
			uMultiple=uFois+uFois;//si uFois=2, le 1er multiple à rayer est 4 qui est bien le 1er multiple de 2 strictement supérieur à 2
			while (uMultiple<knPremierUltime){
				nPremier[uMultiple]=0;
				uMultiple=uMultiple+uFois;
			};
		}
		if (bVoir) VecteurVoir("nPremier",&nPremier[0],1,knPremierUltime);
	//uPremieR[] soit la copie des kuPremierMax nombres non nuls qui figurent dans le tableau nPremier[] 
		for (ipPremier=0,uE=1;uE<=knPremierUltime && ipPremier<kuPremierRgMax;uE++)
			if (nPremier[uE]!=0)
				uPremieR[++ipPremier]=nPremier[uE];
		if (bVoir) sd("ipPremier",ipPremier);
		if (bVoir) VecteurVoir("uPremieR",&uPremieR[0],1,kuPremierRgMax);
	Assert2("PremierAmorceR",uPremieR[1]==2,uPremieR[kuPremierRgMax]>uPremieR[1]);
	//VecteurVoir("uPremieR",uPremieR,1,kuPremierRgMax);
}//PremierAmorceR

void Print(char *sPrint){
	bBof=bPrint(sPrint);
}//Print

int bPrint(char *sPrint){
	//affiche sPrint suivi de "\n" et rend faux ——permet d'afficher sPrint en fin de boucle For: for (nC=1;nC<5 || bPrint(".");nC++) printf("%d ",nC)…
	printf("%s\n",sPrint);										//…affiche "1 2 3 4 5" terminé par un point et passe à la ligne (contrairt à bPrint0).
	return(kF);
}//bPrint

int bPrint0(char *sPrint){
	//affiche sPrint et rend faux ——permet d'afficher sPrint en fin de boucle For: for (nC=1;nC<5 || bPrint(".");nC++) printf("%d ",nC)…
	printf("%s",sPrint);					//…affiche "1 2 3 4 5" terminé par un point (et ne passe pas à la ligne,contrairt à bPrint).
	return(kF);
}//bPrint0

int nPuissance(int iOperande,int nExposant){
	int nPuissance;
	Assert2("nPuissance1",nExposant>=0,iOperande!=0 || nExposant!=0);
	nPuissance=yPuissance(iOperande,nExposant);
	//sd("zPuissssssssance",nPuissance);
	Assert1("nPuissance2",nPuissance>=0);
	return(nPuissance);
}//nPuissance;

long yPuissance(long yOperande,int iExposant){
	long yPuissance,yPuissance0;
	int uE,nExposant=abs(iExposant);
	//d2(yOperande,nExposant);
	Assert2("yPuissance",nExposant>=0,yOperande!=0 || iExposant!=0);
	yPuissance0=pow(yOperande,nExposant);
	for (yPuissance=1,uE=1;uE<=nExposant;uE++)
		yPuissance=yPuissance*yOperande;
	if (iExposant<0 && bImpair(iExposant))
		yPuissance=-yPuissance;
	//Assert1("yPuissance9",yPuissance==yPuissance0);
	//printf("yPuissssssssance %ld vs %lf.\n",yPuissance,pow(yOperande,nExposant));
	return(yPuissance);
}//yPuissance;

long zPuissance(long yOperande,int nExposant){
	long zPuissance;
	Assert2("zPuissance1",nExposant>=0,yOperande!=0 || nExposant!=0);
	zPuissance=yPuissance(yOperande,nExposant);
	//sd("zPuissssssssance",zPuissance);
	Assert1("zPuissance2",zPuissance>=0);
	return(zPuissance);
}//zPuissance;

int bPuissanceDe10(long yOperande){
	//yOperande est une puissance de 10.
	int bPuissanceDe10;
	long zPuissance=1;
	if (yOperande>0)
		while (10*zPuissance<=yOperande)
			zPuissance*=10; 
	bPuissanceDe10=(yOperande==zPuissance);
	Assert1("bPuissanceDe10",!bPuissanceDe10 || yOperande>0);
	return(bPuissanceDe10);
}//bPuissanceDe10

int bPuissanceDe2(long yOperande){
	//yOperande est une puissance de 2.
	int bPuissanceDe2;
	long zPuissance=1;
	if (yOperande>0)
		while (2*zPuissance<=yOperande)
			zPuissance*=2; 
	bPuissanceDe2=(yOperande==zPuissance);
	return(bPuissanceDe2);
}//bPuissanceDe2

int nPuissanceModulo(int iOperande,int nExposant,int nModulo){//O(log(nExposant))
	//rend yOperande **nExposant) % uModulo
	int nPuissanceModulo=zPuissanceModulo(iOperande,nExposant,nModulo);
	return(nPuissanceModulo);
}//nPuissanceModulo

long zPuissanceModulo(long yOperande,long zExposant,long xModulo){//O(log(zExposant))
	//rend yOperande **nExposant) % uModulo
	const int kbTester=kF;
	int uE,uN;
	long xN,zOperande,zExposantBis,zPuissanceModulo0,zPuissanceModulo1;
	if (kbTester) ld3(yOperande,zExposant,xModulo);
	Assert2("zPuissanceModulo2",zExposant>=0,xModulo>0);
	int nExposantLog2=1+log2(1+zExposant);
	if (kbTester) d(nExposantLog2);
	long zBit[1+nExposantLog2],zPuissance[1+nExposantLog2];
	zOperande=yOperande%xModulo;
	//algo en O(log(nExposant))
		for (zExposantBis=zExposant,zPuissance[0]=1,zPuissance[1] = zOperande % xModulo,xN=2;zExposantBis>0;zExposantBis=zExposantBis/2,xN++){
			zPuissance[xN]=(zPuissance[xN-1]*zPuissance[xN-1]) % xModulo;
			Assert1("zPuissanceModulo calcul de modulo invalide",zPuissance[xN]>=0);
		}
		VekteurRazer(zBit,0,nExposantLog2);
		for (zExposantBis=zExposant,uN=1;zExposantBis>0;zExposantBis=zExposantBis/2,uN++)
			zBit[uN]=zExposantBis%2;
		//if (kbTester) VekteurVoir5("nPuissance",zPuissance,"zBit",zBit,0,nExposantLog2);
		if (kbTester) VekteurVoir("zBit",zBit,0,nExposantLog2);
		if (kbTester) VekteurVoir("zPuissance",zPuissance,0,nExposantLog2);
		for (zPuissanceModulo1=1,uE=1;uE<=nExposantLog2;uE++)
			if (zBit[uE]){
				zPuissanceModulo1=(zPuissanceModulo1*zPuissance[uE]) % xModulo;
				if (kbTester) ld2(uE,zPuissanceModulo1);
			}
	if (kbTester){
		for (zPuissanceModulo0=xN=1;xN<=zExposant;xN++)//algo en O(zExposant)
			zPuissanceModulo0=(zPuissanceModulo0*zOperande) % xModulo;
		ld2(zPuissanceModulo0,zPuissanceModulo1);
		Assert1("zPuissanceModulo9",zPuissanceModulo0==zPuissanceModulo1);
	}
	return(zPuissanceModulo1);
}//zPuissanceModulo

char *sQ(q qRationnel){
	//convertit qRationnel en chaîne de caractères: sQ(1/2) rend "1/2" et sQ(2/1) rend "2".
	const int kuRequis=31;
	char *sQ=sMalloC(kuRequis);
		if (qRationnel.den!=1){
			sprintf(sQ,"%d/%d",qRationnel.num,qRationnel.den);
		}else sprintf(sQ,"%d",qRationnel.num);
	MallocGereR(sQ);
	return(sQ);
}//sQ

int nRac(long zEntier){
	//rend le plus grand entier inférieur ou égal à la racine carrée de zEntier —— ie plancher(zEntier**0.5).
	long zRac,xRac;
	Assert1("nRac",zEntier>=0);
	for (zRac=0,xRac=1;xRac*xRac<=zEntier;xRac++)
		zRac=xRac;
	return(zRac);
}//nRac

ri riRac(int uRacineEnTout,int nRang){
	//rend la racine de l'unité de rang nRang
	Assert1("riRac",bCroit(0,nRang,uRacineEnTout-1));
	ri riRac;
	float rdAngle=(nRang*2*kPi)/uRacineEnTout;
	//f(rdAngle);
	riRac.r=cos(rdAngle);
	riRac.i=sin(rdAngle);
	//f2(riRac.r,riRac.i);
	return(riRac);
}//riRac

char *sRatio(long yNumerateur,long yDenominateur){
	//convertit yNumerateur/yDenominateur en chaîne de caractères: sRatio(6,5) rend "1.20".
	Assert1("sRatio: dénominateur nul",yDenominateur);
	const int kuRequis=31;
	char *sRatio=sMalloC(kuRequis);
		//printf("%ld/%ld=%5.2f.\n",yNumerateur,yDenominateur,yNumerateur/(1.0*yDenominateur));
		sprintf(sRatio,"%.2f",yNumerateur/(1.0*yDenominateur));
	MallocGereR(sRatio);
	//s(sRatio);
	return(sRatio);
}//sRatio

int bReelEgal(float fA,float fB){
	int bEgal=(fabs(fA-fB)<fEpsiloN);
	return(bEgal);
}//bReelEgal

int bReelEgal0(float fA,float fB,int mPuissanceDe10){
	//comme bReelEgal, en remplaçant fEpsiloN ci-dessus par 10**(mPuissanceDe10)
	Assert1("bReelEgal0",bCroitStrict(0,-mPuissanceDe10,13));
	int bEgal0=fabs(fA-fB)<powf(10,mPuissanceDe10);
	return(bEgal0);
}//bReelEgal0

void ReelEgaliser(int nDecimale){
	//fEpsiloN:=1/10**nDecimale
	Assert1("ReelEgaliser",nDecimale>=0);
	fEpsiloN=(nDecimale>0)? 1.0/zPuissance(10,nDecimale) : kdEpsilon;
}//ReelEgaliser

char *sReel(float fReel){
	//convertit fReel en chaîne de caractères: sReel(0.5) rend "0.50".
	const int kuRequis=31;
	char *sR=sMalloC(kuRequis);
		sprintf(sR,"%.2f",fReel);
	MallocGereR(sR);
	return(sR);
}//sReel

char *sReel0(float fReel,int nCaractereEnTout){
	//convertit fReel en chaîne de caractères cadrée à droite sur nCaractereEnTout caractères: sReel0(0.5,6) rend "0.50  ".
	const int kuRequis=31;
	char *sReel0=sMalloC(kuRequis);
		sprintf(sReel0,"%.2f",fReel);
		f(fReel);printf("sReel0 brute:%s.\n",sG(sReel0));
		sReel0=sChaine0(sReel0,nCaractereEnTout);
		printf("sReel0 cadrée à gauche:%s.\n",sG(sReel0));
	MallocGereR(sReel0);
	return(sReel0);
}//sReel0

char *sReel1(float fReel,int nCaractereEnTout){
	//convertit fReel en chaîne de caractères cadrée à gauche sur nCaractereEnTout caractères: sReel1(0.5,6) rend " 0.50 ".
	const int kuRequis=31;
	char *sReel1=sMalloC(kuRequis);
		sprintf(sReel1,"%.2f",fReel);
		//f(fReel);printf("sReel1 brute:%s.\n",sG(sReel1));
		sReel1=sChaine1(sReel1,nCaractereEnTout);
		//printf("sReel1 cadrée à gauche:%s.\n",sG(sReel1));
	MallocGereR(sReel1);
	return(sReel1);
}//sReel1

char *sReel2(float fReel,int nCaractereEnTout){
	//convertit fReel en chaîne de caractères centrée sur nCaractereEnTout caractères: sReel2(0.5,6) rend " 0.50 ".
	const int kuRequis=31;
	char *sReel2=sMalloC(kuRequis);
		sprintf(sReel2,"%.2f",fReel);
		//f(fReel);printf("sReel2 brute:%s.\n",sG(sReel2));
		sReel2=sChaine2(sReel2,nCaractereEnTout);
		//printf("sReel2 centrée:%s.\n",sG(sReel2));
	MallocGereR(sReel2);
	return(sReel2);
}//sReel2

char *sReel3(float fReel,int nCaractereEnTout){
	//convertit fReel en chaîne de caractères centrée sur nCaractereEnTout caractères: sReel3(0.5,6) rend " 0.50000 ".
	const int kuRequis=31;
	char *sReel3=sMalloC(kuRequis);
		sprintf(sReel3,"%.5f",fReel);
		//f(fReel);printf("sReel2 brute:%s.\n",sG(sReel2));
		sReel3=sChaine2(sReel3,nCaractereEnTout);
		//printf("sReel3 centrée:%s.\n",sG(sReel2));
	MallocGereR(sReel3);
	return(sReel3);
}//sReel3

char *sReel4(float fReel,int nCaractereEnTout){
	//convertit fReel en chaîne de caractères cadrée à droite sur nCaractereEnTout caractères: sReel3(34.5,6) rend "    34".
	char *sReel4=sEnt3(yPlancher(fReel),nCaractereEnTout);
	return(sReel4);
}//sReel4

void ReelEchanger(double *pdA,double *pdB){
	double dC;
	Assert2("ReelEchanger",pdA!=0,pdB!=0);
	dC=*pdA;
	*pdA=*pdB;
	*pdB=dC;
}//ReelEchanger

int bReelNul(float fValeur){
	int bNul=(fabs(fValeur)<fEpsiloN);
	return(bNul);
}//bReelNul

int bReelUn(float fValeur){
	int bUn=(fabs(fValeur-1.0)<fEpsiloN);
	return(bUn);
}//bReelUn

void Regler(int iFormat){
	//affiche une règle de longueur maximale imprimable sans troncature (124 caractères);sature la page 1 si bPageSaturer
	const int kuCaractereEnTout=124;//nb total de caractères imprimables sur une même ligne
	Assert1("Regler",abs(iFormat)==70);
	const int kuLigneVierge=73;//60
	LigneSauter(kuLigneVierge);
	for (int uC=1;uC<=kuCaractereEnTout || !bLigne();uC++)//décits consécutifs,1 majuscule ts les 10 car., et '@' terminal
		printf("%c",(uC<kuCaractereEnTout)? ( (uC%10==0)? '@'+uC/10 : 0x30+uC%10) : '@');
	LigneSauter((iFormat>0) ? 1 : 100);
/*
123456789A123456789B123456789C123456789D123456789E123456789F123456789G123456789H123456789I123456789J123456789K123456789L123@
*/
}//Regler

int bVirgulhE(char cCaractere){
	//int bVirgulhE=cCaractere==',' || cCaractere==';';
	int bVirgulhE=cCaractere==',';
	return (bVirgulhE);
}

char cSigne(long yEntier){
	//"+" ou "-" ou " " selon que yEntier est soit positif ou nul, soit négatif.
	char cSigne=(yEntier>=0)? '+':'-';
	return(cSigne);
}//cSigne

char *sSigne(long yEntier){
	char *sSigne=sChoix(yEntier>=0,"+","-");
	return(sSigne);
}//sSigne

int tSigne(int iValeur){
	//rend +1 si iValeur>0,-1 si iValeur<0, et 0 sinon.
	int tSigne=0;
	if (iValeur>0)
		tSigne=+1;
	if (iValeur<0)
		tSigne=-1;
	return(tSigne);
}//tSigne

char *sSigneEnClair(long yEntier){
	char *sSigneEnClair=sChoix(yEntier>=0,sChoix(yEntier>0,"positif","nul"),"négatif");
	return(sSigneEnClair);
}//sSigneEnClair

float fSignePres(int bSigneInverser,float fValeur){
	//si bSigneInverser est vrai,rend -fValeur;sinon,rend +fValeur.
	float fSignePres;
	fSignePres=(bSigneInverser)? -fValeur: fValeur;
	return(fSignePres);
}//fSignePres

int iSignePres(int bSigneInverser,int iValeur){
	//si bSigneInverser est vrai,rend -iValeur;sinon,rend +iValeur.
	int iSignePres;
	iSignePres=(bSigneInverser)? -iValeur: iValeur;
	return(iSignePres);
}//iSignePres

long ySignePres(int bSigneInverser,long yValeur){
	//si bSigneInverser est vrai,rend -yValeur;sinon,rend +yValeur.
	long ySignePres;
	ySignePres=(bSigneInverser)? -yValeur: yValeur;
	return(ySignePres);
}//ySignePres

int nSommePuissance(int uEntierMax,int uExposant){
	//rend la somme des puissances d'ordre uExposant des entiers consécutifs de 1 à uEntierMax 
	Assert2("nEntierCumul",uEntierMax>0,bCroit(1,uExposant,2));
	int nSomme;
	if (uExposant==1)
		nSomme=(uEntierMax*(uEntierMax+1))/2;
	if (uExposant==2)
		nSomme=(uEntierMax*(uEntierMax+1)*(2*uEntierMax+1))/6;
	return(nSomme);
}//nSommePuissance

void Stop(int byMassacre){
	Assert1("Stop",bByte(byMassacre));
	printf("Arrêt de l'exécution, exit %d.\n",byMassacre);
	exit(byMassacre);//affiche le paramètre de exit() puis arrête l'exécution. Cache la fonction système exit().
}//Stop

q qSub(q qA,q qB){
	//différence de deux rationnels
	q qSub;
	qSub=qAdd(qA,qOpp(qB));
	return(qSub);
}//qSub

ri riSub(ri riA,ri riB){
	//différence de deux nombres complexes
	ri riSub;
	riSub.r=riA.r-riB.r;
	riSub.i=riA.i-riB.i;
	return(riSub);
}//riSub

char *sSucces(int bSuccesSinonEchec){
	//rend "succès" ou "échec" selon bSuccesSinonEchec 
	#define kuSuccesSinonEchecLg 6
	char *sSucces=sMalloC( kuSuccesSinonEchecLg);
		Assert2("sSucces",nChaineLg("succès")==6,nChaineLg("succès")==6);
		sSucces[0]='\0';
		strcat(sSucces,(bSuccesSinonEchec)? "succès": "échec");
	MallocGereR(sSucces);
	return(sSucces);
}//sSucces

int iSup(int iA,int iB){
	//rend sup(iA,iB);identique à iMax(iA,iB).
	int iSup=(iA<iB)?iB:iA;
	return(iSup);
}//iSup

int iSup3(int iA,int iB,int iC){
	int iSup3=iSup(iA,iSup(iB,iC));
	return(iSup3);
}//iSup3

int iSup4(int iA,int iB,int iC,int iD){
	int iSup4=iSup(iA,iSup3(iB,iC,iD));
	return(iSup4);
}//iSup4

double rSup(double dA,double dB){
	//rend sup(dA,dB)
	double rSup=(dA>dB)?dA:dB;
	return(rSup);
}//rSup

long ySup(long yA,long yB){
	//rend sup(yA,yB);identique à yMax(yA,yB)
	long ySup=(yA>yB)?yA:yB;
	return(ySup);
}//ySup

char *sSurcout(int uNumerateur,int uDenominateur){//voir aussi sPourcent
	//rend en pourcentage l'accroissement relatif (uNumerateur-nDenominateur)/nDenominateur.
	Assert12("sSurcout non défini ou négatif,uNumerateur,uDenominateur",bCroit(1,uDenominateur,uNumerateur),uNumerateur,uDenominateur);
	char *sSurcout=sC2(sDiv(100*(uNumerateur-uDenominateur),uDenominateur),"%");
	return(sSurcout);
}//sSurcout

int iSwitch3(int iCas,int iValeur1,int iValeur2,int iValeurParDefaut){
	//rend iValeur1 si iCas=1, iValeur2 2 si iCas=2, et iValeurParDefaut sinon.
	int iSwitch3;
	switch (iCas){
		case  1:	iSwitch3=iValeur1;break;
		case  2:	iSwitch3=iValeur2;break;
		default:	iSwitch3=iValeurParDefaut;
	}
	return(iSwitch3);
}//iSwitch3

char *sTab(int nIndentation){
	//rend kuTabulationLargeur*nIndentation caractères blancs consécutifs
	const int kuTabulationLargeur=4;
	Assert1("sTab",nIndentation>=0);
	int uRequis=kuTabulationLargeur*nIndentation;
	char *sIndentation=sMalloC(uRequis);
		strcpy(sIndentation,sE(uRequis));
	MallocGereR(sIndentation);
	return(sIndentation);
}//sTab

char *sTab0(){
	//rend kuTabulationLargeur*nIndentation caractères blancs consécutifs
	if ( bFlag() )
		return sC2(sTab(nTabulatioN),flag);
	else return sTab(nTabulatioN);
}//sTab0

void TableauVoir(char *sNom,int iQuelTableau[kuTableauLigneMax][kuTableauLigneMax],int nIndexMin1,int nIndexMax1,int nIndexMin2,int nIndexMax2){
	//affiche iQuelTableau[nIndexMin1..nIndexMax1][nIndexMin2..nIndexMax2],dc bornes incluses
	const int uPas=3;//1 par défaut;si plus grand, affiche en mode "étalé" en intercalant des sauts de (uPas-1) lignes
	const int kuCaractereParItem=2*uPas;
	Assert4("iQuelTableau",sNom!=0,iQuelTableau!=0,bCroit4(0,nIndexMin1,nIndexMax1,kuTableauLigneMax),bCroit4(0,nIndexMin2,nIndexMax2,kuTableauLigneMax));
	printf("%s col: ",sNom);
	for (int nE=nIndexMin1;nE<=nIndexMax1;nE++)
		printf("%s°",sEntier(nE,kuCaractereParItem));
	Ligner(uPas);
	for (int nE=nIndexMin1;nE<=nIndexMax1;nE++){
		VecteurVoir3(sC2(sNom,sC(sEntier(nE,2))),iQuelTableau[nE],nIndexMin2,nIndexMax2,kuCaractereParItem);
		Ligner(uPas-1);
	}
}//iQuelTableau

int nTabulation(){
	return(nTabulatioN);
}//nTabulation

void Tabuler(int iTabulation){
	if (iTabulation)
		nTabulatioN=iSup(0,nTabulatioN+iTabulation);
	else iTabulation=0;
}//Tabuler

void Titrer(char *sTitre){
	//affiche sTitre au centre d'une ligne de uTitreLargeurPairE caractères garnie par défaut de caractères '*'
	Titrer2(sTitre,'*');
}//Titrer

void Titrer0(int nTitreLargeur){
	//affiche sTitre étalé au centre d'une ligne de uTitreLargeurPairE caractères garnie par défaut de caractères '*'
	if (nTitreLargeur<=0)
		uTitreLargeurPairE=100;
	else uTitreLargeurPairE=nTitreLargeur+bImpair(nTitreLargeur);
	uTitreLargeurPairE=yBorner(80,uTitreLargeurPairE,200);
}//Titrer0

void Titrer1(char *sTitre){
	//affiche sTitre étalé au centre d'une ligne de uTitreLargeurPairE caractères garnie par défaut de caractères '*'
	Titrer2(sChaineEtale1(sTitre),'*');
}//Titrer1

void Titrer2(char *sTitre,char cMotif){
	//affiche sTitre au centre d'une ligne de uTitreLargeurPairE caractères garnie de caractères cMotif
	const int kuUnBlanc=1;
	assert(sTitre!=0);//pas Assert
	int nTitreLg0=yInf(uTitreLargeurPairE-2,nChaineLg(sTitre));
	int nTitreLg1=yInf(uTitreLargeurPairE-2,nCaractere(sTitre));
	assert(nTitreLg1<uTitreLargeurPairE && uTitreLargeurPairE%2==0);
	int nMotifDeChaqueCoteh=(uTitreLargeurPairE-kuUnBlanc-nTitreLg1-kuUnBlanc)/2;//oui,division entière
	int bUnMotifEnSus=bImpair(nTitreLg1);//pour ajouter un cMotif chaque fois que la longueur du titre est impaire
	assert(nMotifDeChaqueCoteh+kuUnBlanc+nTitreLg1+kuUnBlanc+nMotifDeChaqueCoteh+bUnMotifEnSus==uTitreLargeurPairE);//pas Assert
	printf("%s %s %s\n",sFois(nMotifDeChaqueCoteh,cMotif),sPhrase0(sChainon(sTitre,0,nTitreLg0-1)),sFois(nMotifDeChaqueCoteh+bUnMotifEnSus,cMotif));
}//Titrer

char *sTriplet(long yEntierA,long yEntierB,long yEntierC){
	//rend la chaîne "(yEntierA,yEntierB,yEntierC)"	
	char *sTriplet=sMalloC(1+kuEntier23SizE+1+kuEntier23SizE+1+kuEntier23SizE+1);
		strcpy(sTriplet,sC7("(",sEnt(yEntierA),",",sEnt(yEntierB),",",sEnt(yEntierC),")"));
	MallocGereR(sTriplet);
	return(sTriplet);
}//sTriplet

int bTrit(int tVariable){
	//vrai ssi tVariable est un trit à valeur dans {-1,0,+1}
	int tTrit=bCroit(-1,tVariable,+1);
	return(tTrit);
}//bTrit

ri riUn(){
	ri riUn;
	riUn.r=1.0;
	riUn.i=0.0;
	return(riUn);
}//riUn

char *sUn(char *sVerbe,int bUn){
	//si bUn,rend sVerbe suivi de "un";sinon,encadre sVerbe avec "ne" et "aucun".
	return(sUnOuUne(sVerbe,bUn,!k1Feminin));
}//sUn

char *sUnOuUne(char *sVerbe,int bUn,int bFeminin){
	//si bUn,rend sVerbe suivi de "un" ou "une";sinon,encadre sVerbe avec "ne" et "aucun" ou "aucune".
	const int kuNegationEtBlancLgMax= 4;
	Assert2("sUn",sVerbe!=0,bBool(bUn));
	char *sUnOuUne=sMalloC(nChaineLg(sVerbe)+iMax(nChaineLg("un"),nChaineLg("pas de"))+bFeminin+kuNegationEtBlancLgMax);
		if (!bUn){
			strcpy(sUnOuUne,sChoix(bVoyelle(sVerbe,0),"n'","ne "));
			strcat(sUnOuUne,sVerbe);
		}
		else strcpy(sUnOuUne,sVerbe);
		strcat(sUnOuUne," ");
		switch (nCas4(bUn,bFeminin)){
			case 0:	strcat(sUnOuUne,"pas de");break;//strcat(sUnOuUne,"aucun");break;
			case 1:	strcat(sUnOuUne,"pas de");break;//strcat(sUnOuUne,"aucune");break;
			case 2:	strcat(sUnOuUne,"un");break;
			case 3:	strcat(sUnOuUne,"une");break;
		}
	MallocGereR(sUnOuUne);
	return(sUnOuUne);
}//sUnOuUne

char *sUne(char *sVerbe,int bUne){
	//si bUn,rend sVerbe suivi de "une";sinon,encadre sVerbe avec "ne" et "aucune".
	return(sUnOuUne(sVerbe,bUne,k1Feminin));
}//sUne

void VecteurAdditionner(int iVecteurA[],int iVecteurB[],int nIndexMin,int nIndexMax,int iSomme[]){
	//iSomme =iVecteurA+iVecteurB; iVecteurA[0] ctient le nb d'éléments
	Assert4("VecteurAdditionner",iVecteurA!=0,iVecteurB!=0,iSomme!=0,bCroit(0,nIndexMin,nIndexMax));
	for (int nK=nIndexMin;nK<=nIndexMax;nK++)
		iSomme[nK]=iVecteurA[nK]+iVecteurB[nK];
}//VecteurAdditionner

void VecteurAdditionner0(int iVecteurA[],int iVecteurB[],int iSomme[]){
	//iSomme =iVecteurA+iVecteurB; iVecteurA[0] ctient le nb d'éléments
	Assert4("VecteurAdditionner0",iVecteurA!=0,iVecteurB!=0,iSomme!=0,iVecteurA[0]==iVecteurB[0]);
	for (int nK=1;nK<=iVecteurA[0];nK++)
		iSomme[nK]=iVecteurA[nK]+iVecteurB[nK];
	iSomme[0]=iVecteurA[0];
}//VecteurAdditionner0

void VecteurAdditionnerReel(double dVecteurA[],double dVecteurB[],double dSomme[]){
	//dSomme =dVecteurA+dVecteurB; dVecteurA[0] ctient le nb d'éléments
	Assert4("VecteurAdditionnerReel",dVecteurA!=0,dVecteurB!=0,dSomme!=0,dVecteurA[0]==dVecteurB[0]);
	for (int nK=1;nK<=dVecteurA[0];nK++)
		dSomme[nK]=dVecteurA[nK]+dVecteurB[nK];
	dSomme[0]=dVecteurA[0];
}//VecteurAdditionnerReel

void VecteurAffecter(int iVecteur[],int nIndexMin,int nIndexMax,int iValeurAffectee){
	int nE;
	Assert2("VecteurAffecter",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nE=nIndexMin;nE<=nIndexMax;nE++)
		iVecteur[nE]=iValeurAffectee;
}//VecteurAffecter

void VecteurAjouter(int iVecteurA[],int nIndexMin,int nIndexMax,int iAjout){
	//ajoute iAjout à iVecteurA[nIndexMin..nIndexMax]
	int nK;
	//d3(iVecteurA!=0,bCroit(0,nIndexMin,nIndexMax),iAjout);
	Assert2("VecteurAjouter",iVecteurA!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<=nIndexMax;nK++)
		iVecteurA[nK]+=iAjout;
}//VecteurAjouter

void VecteurAjouter0(int iVecteurA[],int iAjout){
	//ajoute iAjout à iVecteurA[1..iVecteurA[0]]
	VecteurAjouter(iVecteurA,1,iVecteurA[0],iAjout);
}//VecteurAjouter0

void VecteurComplementer(int bVecteur[],int nIndexMin,int nIndexMax){
	//bVecteur[nIndexMin..nIndexMax] := 1 - bVecteur[nIndexMin..nIndexMax] 
	Assert2("VecteurComplementer",bVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (int nK=nIndexMin;nK<=nIndexMax;nK++)
		bVecteur[nK]=1-bVecteur[nK];
}//VecteurComplementer

void VecteurCompleter(int iVecteur[],int nIndexPris,int nIndexMax){
	//stocke ds iVecteur]nIndexPris..nIndexMax] les entiers csécutifs croissants autres que ceux déjà présents
	Appel0("VecteurCompleter");
		Assert2("VecteurCompleter",iVecteur!=0,bCroit(0,nIndexPris,nIndexMax));
		int iCopie[1+nIndexMax];
		int uPris;
		VecteurIndexer(iCopie,1,nIndexMax);
		for (uPris=1;uPris<=nIndexPris;uPris++)
			iCopie[iVecteur[uPris]]=0;
		uPris=nIndexPris;
		for (int nK=1;nK<=nIndexMax;nK++)
			if (iCopie[nK])
				iVecteur[++uPris]=nK;
		VecteurVoir("iVecteur",iVecteur,1,nIndexMax);
	Appel1("VecteurCompleter");
}//VecteurOpposer

int bVecteurContient(int nEnquis,int iVecteur[]){
	int nCardinal=iVecteur[0];
	//nEnquis dans iVecteur[1..nCardinal] 
	int bContient=(1<=nCardinal) && mVecteurContient(nEnquis,iVecteur,1,nCardinal)>=0;
	return(bContient);
}//bVecteurContient

int nVecteurContient(int nEnquis,int iVecteur[],int nIndexMin,int nIndexMax){
	//rend le nombre d'occurrences de nEnquis dans iVecteur[nIndexMin..nIndexMax]
	int nE,nContient;
	Assert2("nVecteurContient",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax) );
	for (nContient=0,nE=nIndexMin;nE<=nIndexMax;nE++)
		nContient+=(nEnquis==iVecteur[nE]);
	return(nContient);
}//nVecteurContient

int mVecteurContient(int nEnquis,int iVecteur[],int nIndexMin,int nIndexMax){
	//rend le rang 0 ou 1 de nEnquis dans iVecteur[nIndexMin..nIndexMax],ou -1 si nEnquis n'est pas dans iVecteur[nIndexMin..nIndexMax] 
	int nE;
	int mContient=-1;
	Assert2("mVecteurContient",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax) );
	for (nE=nIndexMin;nE<=nIndexMax && (mContient<0);nE++)
		if (nEnquis==iVecteur[nE])
			 mContient=nE;
	return(mContient);
}//mVecteurContient

int bVecteurContient1(int nEnquis,int nCardinal,int iVecteur[]){
	//nEnquis dans iVecteur[1..nCardinal] 
	int bContient1=(1<=nCardinal) && mVecteurContient(nEnquis,iVecteur,1,nCardinal)>=0;
	return(bContient1);
}//bVecteurContient1

void VecteurCopier(int iVecteurA[],int nIndexMin,int nIndexMax,int iVecteurB[]){
	//iVecteurB[nIndexMin..nIndexMax] := iVecteurA[nIndexMin..nIndexMax] 
	int nK;
	//d3(iVecteurA!=0,iVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	Assert3("VecteurCopier",iVecteurA!=0,iVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<=nIndexMax;nK++)
		iVecteurB[nK]=iVecteurA[nK];
}//VecteurCopier

void VecteurCopier0(int iVecteurA[],int iVecteurB[]){
	//iVecteurB[0..iVecteurA[0]] := iVecteurA[0..iVecteurA[0]]
	int nIndexMax=iVecteurA[0];
	Assert1("VecteurCopier0",nIndexMax>0);
	VecteurCopier(iVecteurA,0,nIndexMax,iVecteurB);
}//VecteurCopier0

void VecteurCopierReel(double dVecteurA[],int nIndexMin,int nIndexMax,double dVecteurB[]){
	//dVecteurB[nIndexMin..nIndexMax] := dVecteurA[nIndexMin..nIndexMax] 
	int nK;
	//d3(dVecteurA!=0,dVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	Assert3("VecteurCopierReel",dVecteurA!=0,dVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<=nIndexMax;nK++)
		dVecteurB[nK]=dVecteurA[nK];
}//VecteurCopierReel

void VecteurCopierReel0(double dVecteurA[],double dVecteurB[]){
	//dVecteurB[0..dVecteurA[0]] := dVecteurA[0..dVecteurA[0]]
	int nIndexMax=dVecteurA[0];
	Assert1("VecteurCopierReel0",nIndexMax>0);
	VecteurCopierReel(dVecteurA,0,nIndexMax,dVecteurB);
}//VecteurCopierReel0

int bVecteurCroit(int iVecteur[],int nIndexMin,int nIndexMax,int bOrdreStrict){//O(N)
	//les éléments de iVecteur[nIndexMin..nIndexMax] sont en ordre croissant au sens strict ssi bStrict
	int bCroissant,nK;
	Assert2("bVecteurCroit",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (bCroissant=1,nK=nIndexMin;nK<nIndexMax;nK++)
		bCroissant = bCroissant && iVecteur[nK]<=iVecteur[nK+1]-bOrdreStrict;
	return(bCroissant);
}//bVecteurCroit

void VecteurCumuler(int iVecteur[],int nIndexMin,int nIndexMax){
	//ajoute iVecteur[nK-1] à iVecteurA[nK] pr nIndexMin<nK≤nIndexMax
	//d2(iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	Assert2("VecteurCumuler",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (int nK=nIndexMin+1;nK<=nIndexMax;nK++)
		iVecteur[nK]+=iVecteur[nK-1];
}//VecteurCumuler

void VecteurCumuler0(int iVecteur[]){
	//dans iVecteur[1..iVecteur[0]],ajoute iVecteur[nK-1] à iVecteur[nK]
	//d2(iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	Assert1("VecteurCumuler0",iVecteur!=0);
	VecteurCumuler(iVecteur,1,iVecteur[0]);
}//VecteurCumuler0

void VecteurDecaler(int iVecteur[],int nIndexMin,int nIndexMax,int iDecalage){
	//décale iVecteur[nIndexMin,nIndexMax] de iDecalage cases;les cases cibles sont supposées exister
	Assert2("VecteurDecaler",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	if (iDecalage>0)
		for (nE=nIndexMax;nE>=nIndexMin;nE--)
			iVecteur[nE+iDecalage]=iVecteur[nE];
	if (iDecalage<0)
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			iVecteur[nE+iDecalage]=iVecteur[nE];
}//VecteurDecaler

int bVecteurDistinct(int iVecteur[],int nIndexMin,int nIndexMax,int bNonNul){
	//les éléments de iVecteur[nIndexMin,nIndexMax] sont tous distincts;si bNonNul,seuls les éléments non nuls doivent être distincts
	int bDistinct,nE,uE,ipIndex;
	int bVoir=kF;
	Assert2("bVecteurDistinct",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int iElement[1+nIndexMax-nIndexMin];
	//empiler ds iElement ts les éléments de pmA (seult ceux non nuls si bNonNul)
		for (iElement[0]=0,ipIndex=0,uE=nIndexMin;uE<=nIndexMax;uE++)
			if (!bNonNul || iVecteur[uE]!=0)
				iElement[++ipIndex]=iVecteur[uE];
	VecteurTrier(iElement,1,ipIndex);
	//if (bVoir) VecteurVoir("bDistinct AVANT",iVecteur,nIndexMin,nIndexMax);
	//if (bVoir) VecteurVoir("bDistinct APRES",iElement,1,ipIndex);
	for (bDistinct=kV,nE=0;nE<ipIndex;nE++)
		if (iElement[nE]==iElement[nE+1]){
			if (0 && bVoir) d2(iElement[nE],iElement[nE+1]);
			bDistinct=0;
		}
	if (bVoir && !bDistinct) VecteurVoir("iElement",iElement,1,ipIndex);
	return(bDistinct);
}//bVecteurDistinct

int nVecteurDoublet(int iVecteur[],int nIndexMin,int nIndexMax){//O(N)
	//rend le nombre de paires d'éléments consécutifs de iVecteur[nIndexMin..nIndexMax] qui sont égaux
	int nDoublet,nK;
	Assert2("nVecteurDoublet",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nDoublet=0,nK=nIndexMin;nK<nIndexMax;nK++)
		nDoublet += iVecteur[nK]==iVecteur[nK+1];
	return(nDoublet);
}//nVecteurDoublet

int nVecteurDoublon(int iVecteur[],int nIndexMin,int nIndexMax){//O(N*N)
	//rend la plus petite distance deux éléments identiques de iVecteur[nIndexMin..nIndexMax]
	int nDoublon,nK,nL;
	Assert2("nVecteurDoublon",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nDoublon=kuIntegerMax,nK=nIndexMin;nK<nIndexMax;nK++)
		for (nL=nK+1;nL<=nIndexMax;nL++)
			if (iVecteur[nK]==iVecteur[nL]){
				nDoublon=iInf(nDoublon,nL-nK);
				//d5(nK,nL,iVecteur[nK],iVecteur[nL],nDoublon);
			}
	if (nDoublon==kuIntegerMax)
		nDoublon=0;
	return(nDoublon);
}//nVecteurDoublon

int nVecteurEcreter(int iVecteur[],int nIndexMin,int nIndexMax,int iPlancherMin,int iPlafondMax){
	//remplace iVecteur[X] par iPlancherMin ou iPlafondMax si iVecteur[X] est hors [iPlancherMin..iPlafondMax];rend le nombre d'éléments écrêtés. 
	int nK,nEcreter;
	Assert3("nVecteurEcreter",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax),iPlancherMin<=iPlafondMax);
	for (nEcreter=0,nK=nIndexMin;nK<=nIndexMax;nK++)
		if ( !bCroit(iPlancherMin,iVecteur[nK],iPlafondMax) ){
			iVecteur[nK]=iBorner(iPlancherMin,iVecteur[nK],iPlafondMax);
			nEcreter++;
		}
	return(nEcreter);
}//nVecteurEcreter

int bVecteurEgal(int iVecteurA[],int iVecteurB[],int nIndexMin,int nIndexMax){
	//vrai sssi iVecteurA[nIndexMin..nIndexMax] = iVecteurB[nIndexMin..nIndexMax] 
	int nK,bEgal;
	Assert3("bVecteurEgal",iVecteurA!=0,iVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	for (bEgal=kV,nK=nIndexMin;nK<=nIndexMax;nK++)
		bEgal=bEgal && iVecteurA[nK]==iVecteurB[nK];
	return(bEgal);
}//bVecteurEgal

void VecteurEtendre(int iVecteur[],int nIndexMin,int nIndexMax,long yVecteur[]){
	//convertit le vecteur d'integer en vecteur de longint 
	Assert3("VecteurEtendre",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax),yVecteur!=0);
	for (int uE=nIndexMin;uE<=nIndexMax;uE++)
		yVecteur[uE]=iVecteur[uE];
}//VecteurEtendre

void VecteurFusionneR(int iVecteur[],int nIndexMin,int nMilieu,int nIndexMax){//O(nIndexMax-nIndexMin)
	//fusionne iVecteur[nIndexMin..nMilieu] et iQuelVecteur[nMilieu+1,nIndexMax];ordre croissant
	int iK,iL,iP;
	int iCopie[1+nIndexMax];
	//printf("fusion %s %s.\n",sDomaine(nIndexMin,nMilieu),sDomaine(nMilieu+1,nIndexMax) );
	VecteurCopier(iVecteur,nIndexMin,nIndexMax,iCopie);
	//VecteurVoir("AVANT fusion",iCopie,nIndexMin,nIndexMax);
	//VecteurRazer(iVecteur,nIndexMin,nIndexMax);
	iK=nIndexMin;
	iL=nMilieu+1;
	iP=nIndexMin-1;
	while (++iP<=nIndexMax){
		if (iK>nMilieu)
			iVecteur[iP]=iCopie[iL++];
		else if (iL>nIndexMax)
			iVecteur[iP]=iCopie[iK++];
		else if (iCopie[iK]<iCopie[iL]){
			iVecteur[iP]=iCopie[iK++];
		} else iVecteur[iP]=iCopie[iL++];
		//VecteurVoir("APRÈS while",iVecteur,nIndexMin,nIndexMax);
	}
	//VecteurVoir("APRÈS fusion",iVecteur,nIndexMin,nIndexMax);
}//VecteurFusionneR

void VecteurHasarder0(int iVecteur[],int nIndexMin,int nIndexMax,int nValeurMaximale){
	//iVecteur[]:=nHasard(nValeurMaximale);
	Assert3("VecteurHasarder0",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax),nValeurMaximale>=0);
	for (int nE=nIndexMin;nE<=nIndexMax;nE++)
		iVecteur[nE]=nHasard(nValeurMaximale);
}//VecteurHasarder0

void VecteurHasarder1(int iVecteur[],int nIndexMin,int nIndexMax,int uValeurMaximale){
	//iVecteur[]:=uHasard(uValeurMaximale);
	Assert3("VecteurHasarder1",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax),uValeurMaximale>=1);
	for (int nE=nIndexMin;nE<=nIndexMax;nE++)
		iVecteur[nE]=uHasard(uValeurMaximale);
}//VecteurHasarder1

void VecteurIndexer(int iVecteur[],int nIndexMin,int nIndexMax){
	int nE;
	Assert2("VecteurIndexer",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nE=nIndexMin;nE<=nIndexMax;nE++)
		iVecteur[nE]=nE;
}//VecteurIndexer

long yVecteurInf(int iVecteur[],int nIndexMin,int nIndexMax){
	Assert2("yVecteurInf",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	long yInf;
	for (yInf=kxLongintMax,nE=nIndexMin;nE<=nIndexMax;nE++)
		yInf=yMin(yInf,iVecteur[nE]);
	return(yInf);
}//yVecteurInf

void VecteurInverser(int iVecteur[],int nIndexMin,int nIndexMax){
	//iVecteur[nIndexMin..nIndexMax] := iVecteur[nIndexMax..nIndexMin] 
	Assert2("VecteurInverser",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int iCopie[1+nIndexMax];
	VecteurCopier(iVecteur,nIndexMin,nIndexMax,iCopie);
	for (int nE=0;nE<=nIndexMax-nIndexMin;nE++)
		iVecteur[nIndexMin+nE]=iCopie[nIndexMax-nE];
}//VecteurInverser

int iVecteurMax(int iVecteur[],int nIndexMin,int nIndexMax){
	//rend la plus grande valeur contenue dans iVecteur[nIndexMin..nIndexMax],eg 9 si iVecteur=(1,6,1,6,6,9,8). 
	int uE,iMax;
	Assert2("iVecteurMax",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax) );
	for (iMax=iVecteur[nIndexMin],uE=nIndexMin;uE<=nIndexMax;uE++)
		iMax=iSup(iMax,iVecteur[uE]);
	return(iMax);
}//iVecteurMax

int iVecteurMin(int iVecteur[],int nIndexMin,int nIndexMax){
	//rend la plus petite valeur contenue dans iVecteur[nIndexMin..nIndexMax],eg 1 si iVecteur=(5,6,1,6,6,9,8). 
	int uE,iMin;
	Assert2("iVecteurMin",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax) );
	for (iMin=iVecteur[nIndexMin],uE=nIndexMin;uE<=nIndexMax;uE++)
		iMin=iInf(iMin,iVecteur[uE]);
	return(iMin);
}//iVecteurMin

void VecteurMultiplier(int iVecteurA[],int nIndexMin,int nIndexMax,int iMultiplicande){
	//multiplie iVecteurA[nIndexMin..nIndexMax] par iMultiplicande
	//d3(iVecteurA!=0,bCroit(0,nIndexMin,nIndexMax),iAjout);
	Assert2("VecteurMultiplier",iVecteurA!=0,bCroit(0,nIndexMin,nIndexMax));
	for (int nK=nIndexMin;nK<=nIndexMax;nK++)
		iVecteurA[nK]*=iMultiplicande;
}//VecteurMultiplier

void VecteurMultiplier0(int iVecteurA[],int iMultiplicande){
	//multiplie iVecteurA[1..iVecteurA[0]] par iMultiplicande
	VecteurMultiplier(iVecteurA,1,iVecteurA[0],iMultiplicande);
}//VecteurMultiplier0

void VecteurMultiplierReel(double dVecteurA[],int nIndexMin,int nIndexMax,double dMultiplicande){
	//multiplie dVecteurA[nIndexMin..nIndexMax] par dMultiplicande
	//d3(dVecteurA!=0,bCroit(0,nIndexMin,nIndexMax),dMultiplicande);
	Assert2("VecteurMultiplierReel",dVecteurA!=0,bCroit(0,nIndexMin,nIndexMax));
	for (int nK=nIndexMin;nK<=nIndexMax;nK++)
		dVecteurA[nK]*=dMultiplicande;
}//VecteurMultiplierReel

void VecteurMultiplierReel0(double dVecteurA[],double dMultiplicande){
	//multiplie dVecteurA[1..dVecteurA[0]] par dMultiplicande
	VecteurMultiplierReel(dVecteurA,1,dVecteurA[0],dMultiplicande);
}//VecteurMultiplierReel0

float fVecteurNorme(int iVecteur[]){
	//rend la norme euclidienne de iVecteur[0] élts
	float fNorme;
	for (int uE=1;uE<=iVecteur[0];uE++)
		fNorme+=iVecteur[uE]*iVecteur[uE];
	fNorme=sqrt(fNorme);
	return(fNorme);
}//fVecteurNorme

double dVecteurNorme(double dVecteur[]){
	//rend la norme euclidienne de iVecteur[0] élts
	double dNorme;
	for (int uE=1;uE<=dVecteur[0];uE++)
		dNorme+=dVecteur[uE]*dVecteur[uE];
	dNorme=sqrt(dNorme);
	return(dNorme);
}//dVecteurNorme

int bVecteurNul(int iVecteur[],int nIndexMin,int nIndexMax){
	//iVecteur[nIndexMin..nIndexMax] est nul partout 
	int uE;
	int bNul;
	Assert1("bVecteurNul",bCroit(0,nIndexMin,nIndexMax));
	for (bNul=kV,uE=nIndexMin;uE<=nIndexMax;uE++)
		if (iVecteur[uE]!=0)
			 bNul=kF;
	return(bNul);
}//bVecteurNul

int nVecteurOccurrence(int nEnquis,int iVecteur[],int nIndexMin,int nIndexMax){
	//rend le nombre d'occurrences de nEnquis dans iVecteur[nIndexMin..nIndexMax] ——dont 0 si l'intervalle est vide. 
	int uE,nOccurrence;
	Assert1("nVecteurOccurrence",iVecteur!=0 );
	for (nOccurrence=0,uE=nIndexMin;uE<=nIndexMax;uE++)
		nOccurrence += nEnquis==iVecteur[uE];
	return(nOccurrence);
}//nVecteurOccurrence

int nVecteurOccurrenceMax(int iVecteur[],int nIndexMin,int nIndexMax){
	//rend le nombre d'occurrences maximal d'un élément de iVecteur[nIndexMin..nIndexMax],eg 3 si iVecteur=(1,6,1,6,6,9,8). 
	int uE,nOccurrenceMax;
	Assert2("nVecteurOccurrenceMax",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax) );
	for (nOccurrenceMax=0,uE=nIndexMin;uE<=nIndexMax;uE++)
		nOccurrenceMax=iSup(nOccurrenceMax,nVecteurOccurrence(iVecteur[uE],iVecteur,nIndexMin,nIndexMax) );
	return(nOccurrenceMax);
}//nVecteurOccurrenceMax

void VecteurOpposer(int iVecteur[],int nIndexMin,int nIndexMax){
	//iVecteur[nIndexMin..nIndexMax] := - iVecteur[nIndexMin..nIndexMax] 
	Assert2("VecteurOpposer",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (int nK=nIndexMin;nK<=nIndexMax;nK++)
		iVecteur[nK]=-iVecteur[nK];
}//VecteurOpposer

int bVecteurPremier(int iVecteur[],int nIndexMin,int nIndexMax){
	int uE,bPrem;
	Assert2("bVecteurPremier",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax) );
	for (bPrem=1,uE=nIndexMin;uE<=nIndexMax && bPrem;uE++)
		bPrem=bPremier(iVecteur[uE]);
	return(bPrem);
}//bVecteurPremier

long yVecteurProduit(int iVecteur[],int nIndexMin,int nIndexMax){
	Assert2("yVecteurProduit",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	long yProduit;
	//d2(nIndexMin,nIndexMax);
	for (yProduit=1,nE=nIndexMin;nE<=nIndexMax;nE++)
		yProduit*=iVecteur[nE];
	return(yProduit);
}//yVecteurProduit

long yVecteurProduitScalaire(int iVecteurA[],int iVecteurB[]){
	//rend le produit scalaire de iVecteurA[1..N] par iVecteurB[1..N] ds lequel N est iVecteurA[0] 
	Assert1("yVecteurProduitScalaire",iVecteurA[0]==iVecteurB[0]);
	int uE;
	long yProduitScalaire;
	for (yProduitScalaire=0,uE=1;uE<=iVecteurA[0];uE++)
		yProduitScalaire+=iVecteurA[uE]*iVecteurB[uE];
	return(yProduitScalaire);
}//yVecteurProduitScalaire

double dVecteurProduitScalaire(double dVecteurA[],double dVecteurB[]){
	//rend le produit scalaire de dVecteurA[1..N] par dVecteurB[1..N] ds lequel N est dVecteurA[0] 
	Assert1("dVecteurProduitScalaire",dVecteurA[0]==dVecteurB[0]);
	int uE;
	double dProduitScalaire;
	for (dProduitScalaire=0,uE=1;uE<=dVecteurA[0];uE++)
		dProduitScalaire+=dVecteurA[uE]*dVecteurB[uE];
	return(dProduitScalaire);
}//dVecteurProduitScalaire

void VecteurRaz(int iVecteur[],int nIndexMax){
	//annule iVecteur[1..nIndexMax] et stocke nIndexMax ds iVecteur[0]
	VecteurRazer(iVecteur,0,nIndexMax);
	iVecteur[0]=ySup(0,nIndexMax);
}//VecteurRaz

void VecteurRazer(int iVecteur[],int nIndexMin,int nIndexMax){
	if ( bCroit(0,nIndexMin,nIndexMax) )
		for (int nE=nIndexMin;nE<=nIndexMax;nE++)
			iVecteur[nE]=0;
}//VecteurRazer

int bVecteurSemblable(int iVecteurA[],int iVecteurB[],int nIndexMin,int nIndexMax){
	//vrai sssi iVecteurB[nIndexMin..nIndexMax] est une copie désordonnée de iVecteurA[nIndexMin..nIndexMax] 
	int nK,bSemblable;
	int iVecteurAbis[1+nIndexMax];
	int iVecteurBbis[1+nIndexMax];
	Assert3("bVecteurIdentique",iVecteurA!=0,iVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	VecteurCopier(iVecteurA,nIndexMin,nIndexMax,iVecteurAbis);
	VecteurCopier(iVecteurB,nIndexMin,nIndexMax,iVecteurBbis);
	VecteurTrier(iVecteurAbis,nIndexMin,nIndexMax);
	VecteurTrier(iVecteurBbis,nIndexMin,nIndexMax);
	for (bSemblable=kV,nK=nIndexMin;nK<=nIndexMax;nK++)
		bSemblable=bSemblable && iVecteurAbis[nK]==iVecteurBbis[nK];
	return(bSemblable);
}//bVecteurSemblable

long yVecteurSomme(int iVecteur[],int nIndexMin,int nIndexMax){
	Assert2("yVecteurSomme",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	long ySomme;
	//d2(nIndexMin,nIndexMax);
	for (ySomme=0,nE=nIndexMin;nE<=nIndexMax;nE++)
		ySomme+=iVecteur[nE];
	return(ySomme);
}//yVecteurSomme

long yVecteurSommeAlterneh(int yVecteur[],int nIndexMin,int nIndexMax){
	//rend V[nIndexMin]-V[nIndexMin+1]+V[nIndexMin+2],etc jusqu'à V[nIndexMax].
	Assert2("yVecteurSommeAlterneh",yVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE,muSigne;
	long ySomme;
	//d2(nIndexMin,nIndexMax);
	for (muSigne=1,ySomme=0,nE=nIndexMin;nE<=nIndexMax;nE++){
		ySomme+=muSigne*yVecteur[nE];
		muSigne=-muSigne;//change le signe
	}
	return(ySomme);
}//yVecteurSommeAlterneh

void VecteurSoustraire(int iVecteurA[],int iVecteurB[],int nIndexMin,int nIndexMax,int iDifference[]){
	//iDifference[nIndexMin..nIndexMax] =iVecteurA+iVecteurB
	Assert4("VecteurSoustraire",iVecteurA!=0,iVecteurB!=0,iDifference!=0,bCroit(0,nIndexMin,nIndexMax));
	for (int nK=nIndexMin;nK<=nIndexMax;nK++)
		iDifference[nK]=iVecteurA[nK]-iVecteurB[nK];
}//VecteurSoustraire

void VecteurSoustraire0(int iVecteurA[],int iVecteurB[],int iDifference[]){
	//iDifference[0..iVecteurA[0]] =iVecteurA+iVecteurB; iVecteurA[0] ctient le nb d'éléments
	Assert4("VecteurSoustraire",iVecteurA!=0,iVecteurB!=0,iDifference!=0,iVecteurA[0]==iVecteurB[0]);
	for (int nK=1;nK<=iVecteurA[0];nK++)
		iDifference[nK]=iVecteurA[nK]-iVecteurB[nK];
	iDifference[0]=iVecteurA[0];
}//VecteurSoustraire0

void VecteurSoustraireReel(double dVecteurA[],double dVecteurB[],double dDifference[]){
	//iDifference =iVecteurA+iVecteurB; iVecteurA[0] ctient le nb d'éléments
	Assert4("VecteurSoustraireReel",dVecteurA!=0,dVecteurB!=0,dDifference!=0,dVecteurA[0]==dVecteurB[0]);
	for (int nK=1;nK<=dVecteurA[0];nK++)
		dDifference[nK]=dVecteurA[nK]-dVecteurB[nK];
	dDifference[0]=dVecteurA[0];
}//VecteurSoustraireReel

void VecteurSubstituer(int iVecteur[],int nIndexMin,int nIndexMax,int iAvant,int iApres){
	Assert1("VecteurSubstituer",iVecteur!=0);
	for (int nK=nIndexMin;nK<=nIndexMax;nK++)
		if (iVecteur[nK]==iAvant)
			iVecteur[nK]=iApres;
}//VecteurSubstituer

long yVecteurSup(int iVecteur[],int nIndexMin,int nIndexMax){
	Assert2("yVecteurSup",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	long ySup;
	//d2(nIndexMin,nIndexMax);
	for (ySup=kyLongintMin,nE=nIndexMin;nE<=nIndexMax;nE++){
		ySup=yMax(ySup,iVecteur[nE]);
		//ld(ySup);
	}
	return(ySup);
}//yVecteurSup

void VecteurTasser(int iVecteur[],int nIndexMin,int nIndexMax){
	//tasse les éléments à gauche en supprimant les zéros et complète les cases de droite avec des zéros
	int uApres,uAvant;
	for (uApres=nIndexMin,uAvant=nIndexMin;uAvant<=nIndexMax;uAvant++)
		if (iVecteur[uAvant])
			iVecteur[uApres++]=iVecteur[uAvant];
	for (uAvant=uApres;uAvant<=nIndexMax;uAvant++)
		iVecteur[uApres++]=0;
}//VecteurTasser

void VecteurTasser0(int iVecteur[]){
	//tasse les éléments à gauche en supprimant les zéros SANS compléter les cases de droite avec des zéros
	int uApres,uAvant;
	for (uApres=0,uAvant=1;uAvant<=iVecteur[0];uAvant++)
		if (iVecteur[uAvant])
			iVecteur[++uApres]=iVecteur[uAvant];
	iVecteur[0]=uApres;
}//VecteurTasser0

void VecteurTrier(int iQuelVecteur[],int nIndexMin,int nIndexMax){//O(N*N)
	//trie iQuelVecteur[nIndexMin..nIndexMax] par ordre croissant
	int nK,nL,nMin,nPlace;
	Assert2("VecteurTrier0 paramètres appel",iQuelVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<nIndexMax;nK++){
		for (nMin=iQuelVecteur[nPlace=nK],nL=nK+1;nL<=nIndexMax;nL++)
			if (nMin>iQuelVecteur[nL])
				nMin=iQuelVecteur[nPlace=nL];
		//teee("nK,nPlace,nMin",nK,nPlace,nMin);
		EntierEchanger(&iQuelVecteur[nK],&iQuelVecteur[nPlace]);
	}
}//VecteurTrier

void VecteurTrier2(int iQuelVecteur[],int nIndexMin,int nIndexMax,int nIndex[]){
	//trie iQuelVecteur[nIndexMin..nIndexMax] par ordre croissant et rend dans nIndex les nouveaux index des éléments après le tri. 
	int nK,nL,nMin,nPlace;
	if (!bCroit(0,nIndexMin,nIndexMax)) d2(nIndexMin,nIndexMax);
	Assert2("VecteurTrier2",iQuelVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<=nIndexMax;nK++)
		nIndex[nK]=nK;
	for (nK=nIndexMin;nK<nIndexMax;nK++){
		for (nMin=iQuelVecteur[nPlace=nK],nL=nK+1;nL<=nIndexMax;nL++)
			if (nMin>iQuelVecteur[nL])
				nMin=iQuelVecteur[nPlace=nL];
		//teee("nK,nPlace,nMin",nK,nPlace,nMin);
		EntierEchanger(&iQuelVecteur[nK],&iQuelVecteur[nPlace]);
		EntierEchanger(&nIndex[nK],&nIndex[nPlace]);
	}
	nIndex[0]=iQuelVecteur[0];
}//VecteurTrier2

void VecteurTrierCompacter(int iQuelVecteur[]){//O(N*N)
	//trie iQuelVecteur[1..iQuelVecteur[0]] puis tasse à gauche en supprimant les élts redondants;actualise iQuelVecteur[0].
	int nK,nL;
	VecteurTrier(iQuelVecteur,1,iQuelVecteur[0]);
	for (nK=1,nL=nK+1;nL<=iQuelVecteur[0];nL++)
		if (iQuelVecteur[nL-1]<iQuelVecteur[nL])
			iQuelVecteur[++nK]=iQuelVecteur[nL];
	iQuelVecteur[0]=nK;
}//VecteurTrierCompacter

void VecteurTrierVite(int iQuelVecteur[],int nIndexMin,int nIndexMax){//O(N*logN)
	//trie iQuelVecteur[nIndexMin..nIndexMax] par ordre croissant
	int nMilieu=(nIndexMin+nIndexMax)/2;
	if (nIndexMin<nIndexMax){
		//printf("%s tri de iQuelVecteur%s\n",sTab(nNiveau),sDomaine(nIndexMin,nIndexMax));
		VecteurTrierVite(iQuelVecteur,nIndexMin,nMilieu);
		VecteurTrierVite(iQuelVecteur,nMilieu+1,nIndexMax);
		VecteurFusionneR(iQuelVecteur,nIndexMin,nMilieu,nIndexMax);
		//VecteurVoir("iQuelVecteur",iQuelVecteur,nIndexMin,nIndexMax);
	}
}//VecteurTrierVite

void VecteurValuer(int iVecteur[],int nIndexMin,int nIndexMax,int iValeur){
	Assert2("VecteurValuer",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (int nE=nIndexMin;nE<=nIndexMax;nE++)
		iVecteur[nE]=iValeur;
}//VecteurValuer

void VecteurViser(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax){
	int nIndex;
	Assert4("VecteurVisionner",sNom!=0,iQuelVecteur!=0,nIndexMin>=0,nIndexMax>=0);
	for (printf("%s: ",sNom),nIndex=nIndexMin;nIndex<=nIndexMax || bPrint("");nIndex++)
		printf("%d%c",iQuelVecteur[nIndex], (nIndex<nIndexMax)? ',':'.');
}//VecteurViser

void VecteurViser0(char *sNom,int iQuelVecteur[]){
	VecteurViser(sNom,iQuelVecteur,1,iQuelVecteur[0]);
}//VecteurViser

void VecteurVisionner(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax,int bSensInverse){
	//affiche le contenu brut de iQuelVecteur[nIndexMin..nIndexMax],dc bornes incluses
	Assert4("VecteurVisionner",sNom!=0,iQuelVecteur!=0,nIndexMin>=0,nIndexMax>=0);
	printf("%s%s%s: ",sTab0(),sNom,sCrochet(nIndexMin,nIndexMax));
		if (bCroit(0,nIndexMin,nIndexMax) ){
			if (bSensInverse)
				for (int nE=nIndexMax;nE>=nIndexMin;nE--){
					printf("%d%s",iQuelVecteur[nE],(nE!=nIndexMin)? ", ":".");
				}
			else for (int nE=nIndexMin;nE<=nIndexMax;nE++){
				printf("%d%s",iQuelVecteur[nE],(nE!=nIndexMax)? ", ":".");
			}
		}else printf("%s est un domaine vide.",sDomaine(nIndexMin,nIndexMax));
	printf("\n");
}//VecteurVisionner

void VecteurVoir0(char *sNom,int iQuelVecteur[]){
	//affiche iQuelVecteur[1..iQuelVecteur[0]],dc bornes incluses
	const int kuElementParLigne=30;//pris en compte si bAlaLigne est vrai li+1.
	int bAlaLigne=0;//pour sauter à la ligne après affichage de kuElementParLigne données 
	int bPar3=0;//groupe les chiffres par paquets de 3 décits
	int nAffiche,nE,nLargeurMax;
	Assert2("VecteurVoir0",sNom!=0,iQuelVecteur!=0);
	printf("%s%s%s%s: ",sTab0(),sNom,sDomaine(1,iQuelVecteur[0]),sChoix0(bAlaLigne && iQuelVecteur[0]>kuElementParLigne,sC3b(" à raison de",sPar3(kuElementParLigne),"items par ligne")));
		if ( iQuelVecteur[0]>0 ){
			//nLargeurMax:=encombrement maximal,en caractères, d'un index ou d'un élt du segment iQuelVecteur[nIndexMin..nIndexMax]:
				if (!bModeCaractere()){
					for (nLargeurMax=nChaineLg(sEnt(iQuelVecteur[0])),nE=1;nE<=iQuelVecteur[0];nE++)
						nLargeurMax=iSup(nLargeurMax,nChaineLg((bPar3)? sPar3(iQuelVecteur[nE]): sEnt(iQuelVecteur[nE])));
				}else nLargeurMax=0;
		//nLargeurMax=3;
			if (bAlaLigne)
				printf("\n\t\t");
			for (nAffiche=0,nE=1;nAffiche++,nE<=iQuelVecteur[0];nE++){
				//printf("%s%c ",sEnt3(iQuelVecteur[nE],nLargeurMax),(nE<iQuelVecteur[0])?',':'.');
				printf("%s%s",(bPar3)? sEnt2(iQuelVecteur[nE],nLargeurMax) : sEnt(iQuelVecteur[nE]) ,(nE<iQuelVecteur[0])?", ":".");
				if (bAlaLigne && nAffiche%kuElementParLigne==0 && nE<iQuelVecteur[0])
					printf("\n\t\t");
			}
		}else printf("il n'y a aucun élément dans le domaine %s.",sDomaine(1,iQuelVecteur[0]));
	printf("\n");
}//VecteurVoir0

void VecteurVoir(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche iQuelVecteur[nIndexMin..nIndexMax],dc bornes incluses
	const int kuElementParLigne=25;
	int kuMarge=8*0;
	int bPar3=bModeChiffre(),bAlaLigne=0;
	int nAffiche,nE,nLargeurMax;
	Assert4("VecteurVoir",sNom!=0,iQuelVecteur!=0,nIndexMin>=0,nIndexMax>=0);
	//printf("%s%s: ",sTab0(),sNom);
	ModeCaractere(0);
		printf("%s%s%s: ",sTab0(),sNom,sDomaine(nIndexMin,nIndexMax));
	ModeCaractere(-1);
		if (bCroit(0,nIndexMin,nIndexMax) ){
			//nLargeurMax:=encombrement maximal,en caractères, d'un élément du segment iQuelVecteur[nIndexMin..nIndexMax] ou de nIndexMin..nIndexMax:
				if (!bModeCaractere()){
					for (nLargeurMax=nChaineLg(sEnt(nIndexMax)),nE=nIndexMin;nE<=nIndexMax;nE++)
						nLargeurMax=iSup(nLargeurMax,nChaineLg((bPar3)? sPar3(iQuelVecteur[nE]): sEnt(iQuelVecteur[nE])));
				}else nLargeurMax=0;//pr que le mode caractère se manifeste
//nLargeurMax=2;
			if (bAlaLigne)
				Ligne();
			for (nAffiche=0,nE=nIndexMin,printf("%s",sE(kuMarge));nAffiche++,nE<=nIndexMax;nE++){
				printf("%s%s",(bPar3)? sEnt2(iQuelVecteur[nE],nLargeurMax) : sEnt(iQuelVecteur[nE]) ,(nE<nIndexMax)? ",":".");
				if (bAlaLigne && nAffiche%kuElementParLigne==0)
					Ligne();
			}
		}else printf("%s est un domaine vide.",sDomaine(nIndexMin,nIndexMax));
	printf("\n");
}//VecteurVoir

void VecteurVoir1(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche ligne 1 les index nIndexMin..nIndexMax puis, ligne 2, iQuelVecteur[nIndexMin..nIndexMax] ——dc nIndexMax-nIndexMin+1 élts.
	const char kcSeparateur=' ';//ou autre chose
	int bPar3=bModeChiffre();
	char tcIndex[]="index";//ou autre chose
	int nAffiche,nC,nE,nLargeurMax,kuIndexLg=iSup(nChaineLg(tcIndex),nChaineLg(sNom));
	char sIndex[kE3];
	for (sIndex[kuIndexLg]='\0',nC=0;nC<kuIndexLg;nC++)
		sIndex[nC]=(nC<nChaineLg(tcIndex))? tcIndex[nC] : ' ';
	Assert2("VecteurVoir1",sNom!=0,iQuelVecteur!=0);
	if ( bCroit(0,nIndexMin,nIndexMax) ){
		//nLargeurMax:=encombrt maximal,en caractères, d'un index ou d'un élt du segment iQuelVecteur[nIndexMin..nIndexMax]:
			if (1 || !bModeCaractere()){
				for (nLargeurMax=nChaineLg(sEnt(nIndexMax)),nE=nIndexMin;nE<=nIndexMax;nE++)
					nLargeurMax=iSup(nLargeurMax,nChaineLg((bPar3)? sPar3(iQuelVecteur[nE]): sEnt(iQuelVecteur[nE])));
			}else nLargeurMax=0;
			nLargeurMax=ySup(2,nLargeurMax);
//printf("VecteurVoir1.nLargeurMax=%d.\n",nLargeurMax);
		//NB nChaineLg ci-dessous non adapté aux sNom accentués,ctrairt à nCaractere()
		printf("%s%s:%s ",sTab0(),sIndex,sE(iSup(0,nCaractere(sNom)-kuIndexLg)));//affiche tcIndex et ajoute au besoin des espaces pour atteindre la longueur de sNom.
		for (nE=nIndexMin;nE<=nIndexMax || bPrint("");nE++)
			if (bModeCaractere())
				printf("%s%s%c",sE(nLargeurMax-1),sEnt2(nE,0),kcSeparateur);
			else printf("%s%c",sEnt2(nE,nLargeurMax),kcSeparateur);
		printf("%s%s%s: ",sTab0(),sNom,sE(iSup(0,kuIndexLg-nCaractere(sNom))));//qui ajoute 1 blanc sous chaq lettre du mot "index".
		for (nAffiche=0,nE=nIndexMin;nAffiche++,nE<=nIndexMax || bPrint("");nE++)
			printf("%s%s",(bPar3)? sEnt2(iQuelVecteur[nE],nLargeurMax) : sEntier(iQuelVecteur[nE],nLargeurMax) ,(nE<nIndexMax)? ",":".");
	} else printf("%s: le domaine %s est vide.\n",sNom,sDomaine(nIndexMin,nIndexMax));
}//VecteurVoir1

void VecteurVoir10(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche les doublets (index,iQuelVecteur[index]) dans l'intervalle [nIndexMin..nIndexMax], dc bornes incluses
	ModeCaractere(+1);
		VecteurVoir1(sNom,iQuelVecteur,nIndexMin,nIndexMax);
	ModeCaractere(-1);
}//VecteurVoir10

void VecteurVoir11(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche les doublets (index,iQuelVecteur[index]) dans l'intervalle [nIndexMin..nIndexMax], dc bornes incluses
	int nE;
	Assert2("VecteurVoir11",sNom!=0,iQuelVecteur!=0);
	printf("%s%s: ",sNom,sDomaine(nIndexMin,nIndexMax));
	if ( bCroit(0,nIndexMin,nIndexMax) ){
			for (nE=nIndexMin;nE<=nIndexMax;nE++)
				printf("%s ",sCouple(nE,iQuelVecteur[nE]));
		printf("\n");
	}else printf("domaine sans élément.\n");
}//VecteurVoir11

void VecteurVoir2(char *sNom1VirguleNom2,int iVecteur1[],int iVecteur2[],int nIndexMin,int nIndexMax){
	//affiche, alignés en colonne, iVecteur1 puis iVecteur2, sur le domaine [nIndexMin..nIndexMax].
	const int kbEspace=1;//ie 1 blanc après chq virgule
	int bPar3=bModeChiffre();
	int nAffiche,nE,nLargeurMax,kuIndexLg=5;
	Assert4("VecteurVoir2",sNom1VirguleNom2!=0,iVecteur1!=0,iVecteur2!=0,kuIndexLg==nChaineLg("index"));
	if ( bCroit(0,nIndexMin,nIndexMax) ){
		//nLargeurMax:=encombrt maximal,en caractères, d'un élt du segment iQuelVecteur[nIndexMin..nIndexMax] ou de nIndexMin..nIndexMax:
			if (1 || !bModeCaractere()){
				for (nLargeurMax=nChaineLg(sEnt(nIndexMax)),nE=nIndexMin;nE<=nIndexMax;nE++)
					if (bPar3)
						nLargeurMax=iSup3(nLargeurMax,nChaineLg(sPar3(iVecteur1[nE])),nChaineLg(sPar3(iVecteur2[nE])));
					else nLargeurMax=iSup3(nLargeurMax,nChaineLg(sEnt(iVecteur1[nE])),nChaineLg(sEnt(iVecteur2[nE])));
			}else nLargeurMax=0;
		nLargeurMax+=kbEspace;
		//NB nChaineLg ci-dessous non adapté aux sNom accentués
		int nBlanc=iSup3(kuIndexLg,nCaractere(sItem(sNom1VirguleNom2,1)),nCaractere(sItem(sNom1VirguleNom2,2)));
		printf("%s%s%s: ",sTab0(),sItem(sNom1VirguleNom2,1),sE(nBlanc-nCaractere(sItem(sNom1VirguleNom2,1))));//qui ajoute 1 blanc sous chaq lettre du mot "index".
		for (nE=nIndexMin;nE<=nIndexMax || bPrint("");nE++)
			printf("%s%s",(bPar3)? sEnt2(iVecteur1[nE],nLargeurMax) : sEnt1(iVecteur1[nE],nLargeurMax),(nE<nIndexMax)? ",":".");
		printf("%s%s%s: ",sTab0(),sItem(sNom1VirguleNom2,2),sE(nBlanc-nCaractere(sItem(sNom1VirguleNom2,2))));//qui ajoute 1 blanc sous chaq lettre du mot "index".
		for (nAffiche=0,nE=nIndexMin;nAffiche++,nE<=nIndexMax || bPrint("");nE++)
			printf("%s%s",(bPar3)? sEnt2(iVecteur2[nE],nLargeurMax) : sEnt1(iVecteur2[nE],nLargeurMax) ,(nE<nIndexMax)? ",":".");
	} else printf("%s: le domaine %s est vide.\n",sNom1VirguleNom2,sDomaine(nIndexMin,nIndexMax));
}//VecteurVoir2

void VecteurVoir3(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax,int nCaractereParItem){
	//affiche iQuelVecteur[nIndexMin..nIndexMax],dc bornes incluses
	int bPar3=bModeChiffre();
	Assert4("VecteurVoir3",sNom!=0,iQuelVecteur!=0,nIndexMin>=0,nIndexMax>=0);
	//printf("%s%s: ",sNom,sCrochet(nIndexMin,nIndexMax));
	printf("%s%s: ",sTab0(),sNom);
		if (bCroit(0,nIndexMin,nIndexMax) ){
			for (int nE=nIndexMin;nE<=nIndexMax;nE++)
				printf("%s%c",(bPar3)? sEnt2(iQuelVecteur[nE],nCaractereParItem) : sEnt(iQuelVecteur[nE]),(nE<nIndexMax)?',':'.');
		}else printf("%s est un domaine vide.",sDomaine(nIndexMin,nIndexMax));
	printf("\n");
}//VecteurVoir3

void VecteurVoir4(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche les seuls éléments non nuls de iQuelVecteur[nIndexMin..nIndexMax],dc bornes incluses
	int nE,bPremier,bPar3=bModeChiffre();
	Assert4("VecteurVoir4",sNom!=0,iQuelVecteur!=0,nIndexMin>=0,nIndexMax>=0);
	//printf("%s%s: ",sNom,sCrochet(nIndexMin,nIndexMax));
	printf("%s%s: ",sTab0(),sNom);
		if (bCroit(0,nIndexMin,nIndexMax) ){
			for (bPremier=1,nE=nIndexMin;nE<=nIndexMax;nE++)
				if (iQuelVecteur[nE]){
					printf("%s%dx%s",(bPremier)?"":",",nE,(bPar3)? sEnt(iQuelVecteur[nE]) : sEnt(iQuelVecteur[nE]));
					bPremier=0;
				}
			printf(".");
		}else printf("%s est un domaine vide.",sDomaine(nIndexMin,nIndexMax));
	printf("\n");
}//VecteurVoir4

void VecteurVoir5(char *sNom1VirguleNom2,int iVecteur1[],int iVecteur2[],int nIndexMin,int nIndexMax){
	//affiche les index nIndexMin..nIndexMax puis, ligne suivante, iVecteur1[nIndexMin..nIndexMax] puis, ligne suivante, iVecteur2[nIndexMin..nIndexMax].
	const int kbEspace=1;//ie 1 blanc après chq virgule
	int bPar3=bModeChiffre();
	int nAffiche,nE,nLargeurMax,kuIndexLg=5;
	Assert4("VecteurVoir5",sNom1VirguleNom2!=0,iVecteur1!=0,iVecteur2!=0,kuIndexLg==nChaineLg("index"));
	if ( bCroit(0,nIndexMin,nIndexMax) ){
		//nLargeurMax:=encombrement maximal,en caractères, d'un élément du segment iQuelVecteur[nIndexMin..nIndexMax] ou de nIndexMin..nIndexMax:
			if (1 || !bModeCaractere()){
				for (nLargeurMax=nChaineLg(sEnt(nIndexMax)),nE=nIndexMin;nE<=nIndexMax;nE++)
					if (bPar3)
						nLargeurMax=iSup3(nLargeurMax,nChaineLg(sPar3(iVecteur1[nE])),nChaineLg(sPar3(iVecteur2[nE])));
					else nLargeurMax=iSup3(nLargeurMax,nChaineLg(sEnt(iVecteur1[nE])),nChaineLg(sEnt(iVecteur2[nE])));
			}else nLargeurMax=0;
		nLargeurMax+=kbEspace;
		//NB nChaineLg ci-dessous non adapté aux sNom accentués
		int nBlanc=iSup3(kuIndexLg,nCaractere(sItem(sNom1VirguleNom2,1)),nCaractere(sItem(sNom1VirguleNom2,2)));
		printf("%sindex%s: ",sTab0(),sE(nBlanc-kuIndexLg));//affiche "index" et ajoute au besoin des espaces pr atteindre la lgr de sNom1 et sNom2.
		for (nE=nIndexMin;nE<=nIndexMax || bPrint("");nE++)
			if (bModeCaractere())
				printf("%s%s ",sE(nLargeurMax-1),sEnt2(nE,0));
			else printf("%s ",sEnt2(nE,nLargeurMax));
		printf("%s%s%s: ",sTab0(),sItem(sNom1VirguleNom2,1),sE(nBlanc-nCaractere(sItem(sNom1VirguleNom2,1))));//qui ajoute 1 blanc sous chaq lettre du mot "index".
		for (nE=nIndexMin;nE<=nIndexMax || bPrint("");nE++)
			printf("%s%s",(bPar3)? sEnt2(iVecteur1[nE],nLargeurMax) : sEnt1(iVecteur1[nE],nLargeurMax),(nE<nIndexMax)? ",":".");
		printf("%s%s%s: ",sTab0(),sItem(sNom1VirguleNom2,2),sE(nBlanc-nCaractere(sItem(sNom1VirguleNom2,2))));//qui ajoute 1 blanc sous chaq lettre du mot "index".
		for (nAffiche=0,nE=nIndexMin;nAffiche++,nE<=nIndexMax || bPrint("");nE++)
			printf("%s%s",(bPar3)? sEnt2(iVecteur2[nE],nLargeurMax) : sEnt1(iVecteur2[nE],nLargeurMax) ,(nE<nIndexMax)? ",":".");
	} else printf("%s: le domaine %s est vide.\n",sNom1VirguleNom2,sDomaine(nIndexMin,nIndexMax));
}//VecteurVoir5

void VecteurVoir6(char *sNom1VirguleNom2VirguleNom3,int iVecteur1[],int iVecteur2[],int iVecteur3[],int nIndexMin,int nIndexMax){
	//affiche les index nIndexMin..nIndexMax puis, ligne suivante, iVecteur1[nIndexMin..nIndexMax] puis, ligne suivante, iVecteur2[nIndexMin..nIndexMax].
	const int kbEspace=1;//ie 1 blanc après chq virgule
	int bPar3=bModeChiffre();
	int nAffiche,nE,nLargeurMax,kuIndexLg=5;
	Assert5("VecteurVoir6",sNom1VirguleNom2VirguleNom3!=0,iVecteur1!=0,iVecteur2!=0,iVecteur3!=0,kuIndexLg==nChaineLg("index"));
	if ( bCroit(0,nIndexMin,nIndexMax) ){
		//nLargeurMax:=encombrement maximal,en caractères, d'un élément du segment iQuelVecteur[nIndexMin..nIndexMax] ou de nIndexMin..nIndexMax:
			if (1 || !bModeCaractere()){
				for (nLargeurMax=nChaineLg(sEnt(nIndexMax)),nE=nIndexMin;nE<=nIndexMax;nE++)
					if (bPar3)
						nLargeurMax=iSup4(nLargeurMax,nChaineLg(sPar3(iVecteur1[nE])),nChaineLg(sPar3(iVecteur2[nE])),nChaineLg(sPar3(iVecteur3[nE])));
					else nLargeurMax=iSup4(nLargeurMax,nChaineLg(sEnt(iVecteur1[nE])),nChaineLg(sEnt(iVecteur2[nE])),nChaineLg(sEnt(iVecteur3[nE])));
			}else nLargeurMax=0;
		nLargeurMax+=kbEspace;
//d3(nLargeurMax,bPar3,kbEspace);
		//NB nChaineLg ci-dessous non adapté aux sNom accentués
		int nBlanc=iSup4(kuIndexLg,nCaractere(sItem(sNom1VirguleNom2VirguleNom3,1)),nCaractere(sItem(sNom1VirguleNom2VirguleNom3,2)),nCaractere(sItem(sNom1VirguleNom2VirguleNom3,3)));
		printf("%sindex%s: ",sTab0(),sE(nBlanc-kuIndexLg));//affiche "index" et ajoute au besoin des espaces pr atteindre la lgr de sNom1 et sNom2.
		for (nE=nIndexMin;nE<=nIndexMax || bPrint("");nE++)
			if (bModeCaractere())
				printf("%s%s ",sE(nLargeurMax-1),sEnt2(nE,0));
			else printf("%s ",sEnt2(nE,nLargeurMax));
		printf("%s%s%s: ",sTab0(),sItem(sNom1VirguleNom2VirguleNom3,1),sE(nBlanc-nCaractere(sItem(sNom1VirguleNom2VirguleNom3,1))));//qui ajoute 1 blanc sous chaq lettre du mot "index".
		for (nAffiche=0,nE=nIndexMin;nAffiche++,nE<=nIndexMax || bPrint("");nE++)
			printf("%s%s",(bPar3)? sEnt2(iVecteur1[nE],nLargeurMax) : sEnt1(iVecteur1[nE],nLargeurMax) ,(nE<nIndexMax)? ",":".");
		printf("%s%s%s: ",sTab0(),sItem(sNom1VirguleNom2VirguleNom3,2),sE(nBlanc-nCaractere(sItem(sNom1VirguleNom2VirguleNom3,2))));//qui ajoute 1 blanc sous chaq lettre du mot "index".
		for (nAffiche=0,nE=nIndexMin;nAffiche++,nE<=nIndexMax || bPrint("");nE++)
			printf("%s%s",(bPar3)? sEnt2(iVecteur2[nE],nLargeurMax) : sEnt1(iVecteur2[nE],nLargeurMax) ,(nE<nIndexMax)? ",":".");
		printf("%s%s%s: ",sTab0(),sItem(sNom1VirguleNom2VirguleNom3,3),sE(nBlanc-nCaractere(sItem(sNom1VirguleNom2VirguleNom3,3))));//qui ajoute 1 blanc sous chaq lettre du mot "index".
		for (nAffiche=0,nE=nIndexMin;nAffiche++,nE<=nIndexMax || bPrint("");nE++)
			printf("%s%s",(bPar3)? sEnt2(iVecteur3[nE],nLargeurMax) : sEnt1(iVecteur3[nE],nLargeurMax) ,(nE<nIndexMax)? ",":".");
	} else printf("%s: le domaine %s est vide.\n",sNom1VirguleNom2VirguleNom3,sDomaine(nIndexMin,nIndexMax));
}//VecteurVoir6

void VekhteurCopier(ri riVecteurA[],int nIndexMin,int nIndexMax,ri riVecteurB[]){
	//riVecteurB[nIndexMin..nIndexMax] := riVecteurA[nIndexMin..nIndexMax] 
	int nK;
	//d3(iVecteurA!=0,iVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	Assert3("VekhteurCopier",riVecteurA!=0,riVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<=nIndexMax;nK++)
		riVecteurB[nK]=riVecteurA[nK];
}//VekhteurCopier

void VekhteurVoir(char *sNom,ri riQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche riQuelVecteur[nIndexMin..nIndexMax],dc bornes incluses
	int kuMarge=10;
	int bAlaLigne=1;
	int nAffiche,nE;
	Assert4("VekhteurVoir",sNom!=0,riQuelVecteur!=0,nIndexMin>=0,nIndexMax>=0);
	printf("%s%s%s: ",sTab0(),sNom,sDomaine(nIndexMin,nIndexMax));
		if (bCroit(0,nIndexMin,nIndexMax) ){
			if (bAlaLigne)
				Ligne();
			for (nAffiche=0,nE=nIndexMin,printf("%s",sE(kuMarge));nAffiche++,nE<=nIndexMax;nE++){
				printf("%s%s",sK(riQuelVecteur[nE]) ,(nE<nIndexMax)? ", ":".");
				if (bAlaLigne && nAffiche%10==0)
					Ligne();
			}
		}else printf("%s est un domaine vide.",sDomaine(nIndexMin,nIndexMax));
	printf("\n");
}//VekhteurVoir

void VekteurAdditionner(long yVecteurA[],long yVecteurB[],int nIndexMin,int nIndexMax,long ySomme[]){
	//ySomme =yVecteurA+yVecteurB; iVecteurA[0] ctient le nb d'éléments
	Assert4("VekteurAdditionner",yVecteurA!=0,yVecteurB!=0,ySomme!=0,bCroit(0,nIndexMin,nIndexMax));
	for (int nK=nIndexMin;nK<=nIndexMax;nK++)
		ySomme[nK]=yVecteurA[nK]+yVecteurB[nK];
}//VekteurAdditionner

void VekteurAdditionner0(long yVecteurA[],long yVecteurB[],long ySomme[]){
	//ySomme =yVecteurA+iVecteurB; yVecteurA[0] ctient le nb d'éléments
	Assert4("VekteurAdditionner0",yVecteurA!=0,yVecteurB!=0,ySomme!=0,yVecteurA[0]==yVecteurB[0]);
	for (int nK=1;nK<=yVecteurA[0];nK++)
		ySomme[nK]=yVecteurA[nK]+yVecteurB[nK];
	ySomme[0]=yVecteurA[0];
}//VekteurAdditionner0

void VekteurAffecter(long yVecteur[],int nIndexMin,int nIndexMax,long yValeurAffectee){
	int nE;
	Assert2("VekteurAffecter",yVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nE=nIndexMin;nE<=nIndexMax;nE++)
		yVecteur[nE]=yValeurAffectee;
}//VekteurAffecter

void VekteurAjouter(long yVekteurA[],int nIndexMin,int nIndexMax,long yAjout){
	//ajoute yAjout à yVekteurA[nIndexMin..nIndexMax]
	int nK;
	//d3(yVekteurA!=0,bCroit(0,nIndexMin,nIndexMax),yAjout);
	Assert2("VecteurAjouter",yVekteurA!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<=nIndexMax;nK++)
		yVekteurA[nK]+=yAjout;
}//VekteurAjouter

void VekteurAjouter0(long yVekteurA[],long yAjout){
	//ajoute yAjout à yVekteurA[1..yVekteurA[0]]
	VekteurAjouter(yVekteurA,1,yVekteurA[0],yAjout);
}//VekteurAjouter0

int bVekteurContient(long yEnquis,int nCardinal,long yVecteur[]){
	//yEnquis dans yVecteur[1..nCardinal] 
	int uE;
	int bContient=kF;
	Assert1("bVekteurContient",nCardinal>0);
	for (uE=1;uE<=nCardinal;uE++)
		if (yEnquis==yVecteur[uE])
			 bContient=kV;
	return(bContient);
}//bVekteurContient

void VekteurCopier(long yVecteurA[],int nIndexMin,int nIndexMax,long yVecteurB[]){
	//yVecteurB[nIndexMin..nIndexMax] := yVecteurA[nIndexMin..nIndexMax] 
	int nK;
	Assert3("VekteurCopier",yVecteurA!=0,yVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<=nIndexMax;nK++)
		yVecteurB[nK]=yVecteurA[nK];
}//VekteurCopier

void VekteurCopier0(long yVecteurA[],long yVecteurB[]){
	//yVecteurB[0..yVecteurA[0]] := yVecteurA[0..yVecteurA[0]] 
	int nK,nIndexMin=0,nIndexMax=yVecteurA[0];
	Assert3("VekteurCopier",yVecteurA!=0,yVecteurB!=0,yVecteurA[0]>0);
	for (nK=nIndexMin;nK<=nIndexMax;nK++)
		yVecteurB[nK]=yVecteurA[nK];
}//VekteurCopier0

void VekteurDecaler(long yVecteur[],int nIndexMin,int nIndexMax,int iDecalage){
	//décale yVecteur[nIndexMin,nIndexMax] de iDecalage cases;les cases cibles sont supposées exister
	Assert2("VekteurDecaler",yVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	if (iDecalage>0)
		for (nE=nIndexMax;nE>=nIndexMin;nE--)
			yVecteur[nE+iDecalage]=yVecteur[nE];
	if (iDecalage<0)
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			yVecteur[nE+iDecalage]=yVecteur[nE];
}//VekteurDecaler

int bVekteurEgal(long yVecteurA[],long yVecteurB[],int nIndexMin,int nIndexMax){
	//vrai sssi yVecteurA[nIndexMin..nIndexMax] = yVecteurB[nIndexMin..nIndexMax] 
	int nK,bEgal;
	Assert3("bVekteurEgal",yVecteurA!=0,yVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	for (bEgal=kV,nK=nIndexMin;nK<=nIndexMax;nK++)
		bEgal=bEgal && yVecteurA[nK]==yVecteurB[nK];
	return(bEgal);
}//bVekteurEgal

long yVekteurInf(long iVekteur[],int nIndexMin,int nIndexMax){
	Assert2("yVekteurInf",iVekteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	long yInf;
	for (yInf=kxLongintMax,nE=nIndexMin;nE<=nIndexMax;nE++)
		yInf=yMin(yInf,iVekteur[nE]);
	return(yInf);
}//yVekteurInf

int bVekteurNul(long yVecteur[],int nIndexMin,int nIndexMax){
	//yVecteur[nIndexMin..nIndexMax] est nul partout 
	int uE;
	int bNul;
	Assert1("bVekteurNul",bCroit(0,nIndexMin,nIndexMax));
	for (bNul=kV,uE=nIndexMin;uE<=nIndexMax;uE++)
		if (yVecteur[uE]!=0)
			 bNul=kF;
	return(bNul);
}//bVekteurNul

int bVekteurNul0(long yVecteur[]){
	//yVecteur[1..yVecteur[0]] est nul partout 
	int uE,nIndexMin=1,nIndexMax=yVecteur[0];
	int bNul;
	Assert1("bVekteurNul0",nIndexMax>0);
	for (bNul=kV,uE=nIndexMin;uE<=nIndexMax;uE++)
		if (yVecteur[uE]!=0)
			 bNul=kF;
	return(bNul);
}//bVekteurNul0

long yVekteurProduit(long yVecteur[],int nIndexMin,int nIndexMax){
	Assert2("yVekteurProduit",yVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	long yProduit;
	//d2(nIndexMin,nIndexMax);
	for (yProduit=1,nE=nIndexMin;nE<=nIndexMax;nE++)
		yProduit*=yVecteur[nE];
	return(yProduit);
}//yVekteurProduit

void VekteurRaz(long yVecteur[],int nIndexMax){
	//annule yVecteur[1..nIndexMax] et stocke nIndexMax ds yVecteur[0]
	VekteurRazer(yVecteur,0,nIndexMax);
	yVecteur[0]=nIndexMax;
}//VekteurRaz

void VekteurRazer(long yVecteur[],int nIndexMin,int nIndexMax){
	int nE;
	Assert2("VekteurRazer",yVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	if ( bCroit(0,nIndexMin,nIndexMax) )
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			yVecteur[nE]=0;
}//VekteurRazer

void VekteurRazer0(long yVecteur[]){
	//annule yVecteur[1..yVecteur[0]] 
	int nE,nIndexMin=1,nIndexMax=yVecteur[0];
	Assert2("VekteurRazer0",yVecteur!=0,nIndexMax>0);
	if ( bCroit(0,nIndexMin,nIndexMax) )
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			yVecteur[nE]=0;
}//VekteurRazer0

long yVekteurSomme(long yVecteur[],int nIndexMin,int nIndexMax){
	Assert2("yVekteurSomme",yVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	long ySomme;
	//d2(nIndexMin,nIndexMax);
	for (ySomme=0,nE=nIndexMin;nE<=nIndexMax;nE++)
		ySomme+=yVecteur[nE];
	return(ySomme);
}//yVekteurSomme

long yVekteurSommeAlterneh(long yVecteur[],int nIndexMin,int nIndexMax){
	//rend V[nIndexMin]-V[nIndexMin+1]+V[nIndexMin+2],etc jusqu'à V[nIndexMax].
	Assert2("yVekteurSommeAlterneh",yVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE,muSigne;
	long ySomme;
	//d2(nIndexMin,nIndexMax);
	for (muSigne=1,ySomme=0,nE=nIndexMin;nE<=nIndexMax;nE++){
		ySomme+=muSigne*yVecteur[nE];
		muSigne=-muSigne;//change le signe
	}
	return(ySomme);
}//yVekteurSommeAlterneh

void VekteurSoustraire(long yVecteurA[],long yVecteurB[],int nIndexMin,int nIndexMax,long yDifference[]){
	//yDifference[nIndexMin..nIndexMax] =yVecteurA+yVecteurB
	Assert4("VekteurSoustraire",yVecteurA!=0,yVecteurB!=0,yDifference!=0,bCroit(0,nIndexMin,nIndexMax));
	for (int nK=nIndexMin;nK<=nIndexMax;nK++)
		yDifference[nK]=yVecteurA[nK]-yVecteurB[nK];
}//VekteurSoustraire

void VekteurSoustraire0(long yVecteurA[],long yVecteurB[],long yDifference[]){
	//yDifference[0..yVecteurA[0]] =yVecteurA+yVecteurB; yVecteurA[0] ctient le nb d'éléments
	Assert4("VekteurSoustraire0",yVecteurA!=0,yVecteurB!=0,yDifference!=0,yVecteurA[0]==yVecteurB[0]);
	for (int nK=1;nK<=yVecteurA[0];nK++)
		yDifference[nK]=yVecteurA[nK]-yVecteurB[nK];
	yDifference[0]=yVecteurA[0];
}//VekteurSoustraire0

long yVekteurSup(long yVecteur[],int nIndexMin,int nIndexMax){
	Assert2("yVekteurSup",yVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	long ySup;
	for (ySup=kyLongintMin,nE=nIndexMin;nE<=nIndexMax;nE++)
		ySup=yMax(ySup,yVecteur[nE]);
	return(ySup);
}//yVekteurSup

void VekteurTrier(long yQuelVecteur[],int nIndexMin,int nIndexMax){//O(N*N)
	//trie yQuelVecteur[nIndexMin..nIndexMax] par ordre croissant
	int nK,nL,nPlace;
	long yMin;
	if (!bCroit(0,nIndexMin,nIndexMax)) d2(nIndexMin,nIndexMax);
	Assert2("VekteurTrier",yQuelVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<nIndexMax;nK++){
		for (yMin=yQuelVecteur[nPlace=nK],nL=nK+1;nL<=nIndexMax;nL++)
			if (yMin>yQuelVecteur[nL])
				yMin=yQuelVecteur[nPlace=nL];
		//d3(nK,nPlace,nMin);
		EntyerEchanger(&yQuelVecteur[nK],&yQuelVecteur[nPlace]);
	}
}//VekteurTrier

void VekteurVoir(char *sNom,long yQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche yQuelVecteur[nIndexMin..nIndexMax],dc bornes incluses
	const int kuElementParLigne=25;
	int kuMarge=8*0;
	int bPar3=bModeChiffre(),bAlaLigne=0;
	int nAffiche,nE,nLargeurMax;
	Assert4("VekteurVoir",sNom!=0,yQuelVecteur!=0,nIndexMin>=0,nIndexMax>=0);
	//printf("%s%s: ",sTab0(),sNom);
	ModeCaractere(0);
		printf("%s%s%s:",sTab0(),sNom,sDomaine(nIndexMin,nIndexMax));
	ModeCaractere(-1);
		if (bCroit(0,nIndexMin,nIndexMax) ){
			//nLargeurMax:=encombrement maximal,en caractères, d'un élément du segment iQuelVecteur[nIndexMin..nIndexMax] ou de nIndexMin..nIndexMax:
				if (!bModeCaractere()){
					for (nLargeurMax=nChaineLg(sEnt(nIndexMax)),nE=nIndexMin;nE<=nIndexMax;nE++)
						nLargeurMax=iSup(nLargeurMax,nChaineLg((bPar3)? sPar3(yQuelVecteur[nE]): sEnt(yQuelVecteur[nE])));
				}else nLargeurMax=0;//pr que le mode caractère se manifeste
//nLargeurMax=2;
			if (bAlaLigne)
				Ligne();
			for (nAffiche=0,nE=nIndexMin,printf("%s",sE(kuMarge));nAffiche++,nE<=nIndexMax;nE++){
				printf("%s%s",(bPar3)? sEnt2(yQuelVecteur[nE],nLargeurMax) : sEnt(yQuelVecteur[nE]) ,(nE<nIndexMax)? ",":".");
				if (bAlaLigne && nAffiche%kuElementParLigne==0)
					Ligne();
			}
		}else printf("%s est un domaine vide.",sDomaine(nIndexMin,nIndexMax));
	printf("\n");
}//VekteurVoir

void VekteurVoir0(char *sNom,long yQuelVecteur[]){
	//affiche yQuelVecteur[1..yQuelVecteur[0]],dc bornes incluses
	int nE,nLargeurMax;
	Assert3("VekteurVoir0",sNom!=0,yQuelVecteur!=0,yQuelVecteur[0]>=0);
	printf("%s%s: ",sNom,sDomaine(1,yQuelVecteur[0]));
		if ( yQuelVecteur[0]>0 ){
			//nLargeurMax:=encombrement maximal,en caractères, d'un élément du segment yQuelVecteur[nIndexMin..nIndexMax] ou de nIndexMin..nIndexMax:
				for (nLargeurMax=nChaineLg(sEnt(yQuelVecteur[0])),nE=1;nE<=yQuelVecteur[0];nE++)
					nLargeurMax=iSup(nLargeurMax,nChaineLg(sPar3(yQuelVecteur[nE])));
			for (nE=1;nE<=yQuelVecteur[0];nE++)
				printf("%s%c ",sEnt3(yQuelVecteur[nE],nLargeurMax),(nE<yQuelVecteur[0])?',':'.');
		}else printf("ce domaine ne contient pas d'éléments.",sDomaine(1,yQuelVecteur[0]));
	printf("\n");
}//VekteurVoir0

void VekteurVoir1(char *sNom,long yQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche, ligne 1, les index nIndexMin..nIndexMax puis, ligne 2, yQuelVecteur[nIndexMin..nIndexMax] ——donc nIndexMax-nIndexMin+1 éléments.
	int nE,nLargeurMax,kuIndexLg=5;
	Assert4("VekteurVoir1",sNom!=0,yQuelVecteur!=0,bCroit(0,nIndexMin,nIndexMax),kuIndexLg==nChaineLg("index"));
	//nLargeurMax:=encombrement maximal,en caractères, d'un élément du segment yQuelVecteur[nIndexMin..nIndexMax] ou de nIndexMin..nIndexMax:
		for (nLargeurMax=nChaineLg(sEnt(nIndexMax)),nE=nIndexMin;nE<=nIndexMax;nE++)
			nLargeurMax=iSup(nLargeurMax,nChaineLg(sPar3(yQuelVecteur[nE])));
	printf("index:%s ",sE(iSup(0,nChaineLg(sNom)-kuIndexLg)));//affiche "index" et ajoute au besoin des espaces pour atteindre la longueur de sNom.
		for (nE=nIndexMin;nE<=nIndexMax || bPrint("");nE++)
			printf("%s%c ",sEnt3(nE,nLargeurMax),' ');
	printf("%s%s: ",sNom,sE(iSup(0,kuIndexLg-nChaineLg(sNom))));//affiche sNom et ajoute au besoin des espaces pour atteindre la longueur de "index".
		for (nE=nIndexMin;nE<=nIndexMax || bPrint("");nE++)
			printf("%s%c ",sEnt3(yQuelVecteur[nE],nLargeurMax),(nE<nIndexMax)?',':'.');
}//VekteurVoir1

void VekteurVoir2(char *sNom,long yQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche les doublets (index,yQuelVecteur[index]) dans l'intervalle [nIndexMin..nIndexMax], dc bornes incluses
	int nE;
	Assert3("VekteurVoir2",sNom!=0,yQuelVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	printf("%s: ",sNom);
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			printf("%s ",sCouple(nE,yQuelVecteur[nE]));
	printf("\n");
}//VekteurVoir2

void VekteurVoir5(char *sNom1VirguleNom2,long yVecteur1[],long yVecteur2[],int nIndexMin,int nIndexMax){
	//affiche les index nIndexMin..nIndexMax puis, ligne suivante, iVecteur1[nIndexMin..nIndexMax] puis, ligne suivante, iVecteur2[nIndexMin..nIndexMax].
	int bPar3=bModeChiffre();
	int nAffiche,nE,nLargeurMax,kuIndexLg=5;
	Assert4("VekteurVoir5",sNom1VirguleNom2!=0,yVecteur1!=0,yVecteur2!=0,kuIndexLg==nChaineLg("index"));
	if ( bCroit(0,nIndexMin,nIndexMax) ){
		//nLargeurMax:=encombrement maximal,en caractères, d'un élément du segment iQuelVecteur[nIndexMin..nIndexMax] ou de nIndexMin..nIndexMax:
			if (1 || !bModeCaractere()){
				for (nLargeurMax=nChaineLg(sEnt(nIndexMax)),nE=nIndexMin;nE<=nIndexMax;nE++)
					nLargeurMax=iSup3(nLargeurMax,nChaineLg(sEnt(yVecteur1[nE])),nChaineLg(sEnt(yVecteur2[nE])));
			}else nLargeurMax=0;
//nLargeurMax=3;
		//NB nChaineLg ci-dessous non adapté aux sNom accentués
		//t(sNom);d(nCaractere(sNom));
		int nBlanc=iSup3(kuIndexLg,nCaractere(sItem(sNom1VirguleNom2,1)),nCaractere(sItem(sNom1VirguleNom2,2)));
		printf("%sindex%s: ",sTab0(),sE(nBlanc-kuIndexLg));//affiche "index" et ajoute au besoin des espaces pr atteindre la lgr de sNom1 et sNom2.
		for (nE=nIndexMin;nE<=nIndexMax || bPrint("");nE++)
			if (bModeCaractere())
				printf("%s%s%c ",sE(nLargeurMax-1),sEnt2(nE,0),' ');
			else printf("%s%c ",sEnt2(nE,nLargeurMax),' ');
		printf("%s%s%s: ",sTab0(),sItem(sNom1VirguleNom2,1),sE(nBlanc-nCaractere(sItem(sNom1VirguleNom2,1))));//qui ajoute 1 blanc sous chaq lettre du mot "index".
		for (nAffiche=0,nE=nIndexMin;nAffiche++,nE<=nIndexMax || bPrint("");nE++)
			printf("%s%s",(bPar3)? sEnt2(yVecteur1[nE],nLargeurMax) : sEntier(yVecteur1[nE],nLargeurMax) ,(nE<nIndexMax)? ", ":".");
		printf("%s%s%s: ",sTab0(),sItem(sNom1VirguleNom2,2),sE(nBlanc-nCaractere(sItem(sNom1VirguleNom2,2))));//qui ajoute 1 blanc sous chaq lettre du mot "index".
		for (nAffiche=0,nE=nIndexMin;nAffiche++,nE<=nIndexMax || bPrint("");nE++)
			printf("%s%s",(bPar3)? sEnt2(yVecteur2[nE],nLargeurMax) : sEntier(yVecteur2[nE],nLargeurMax) ,(nE<nIndexMax)? ", ":".");
	} else printf("%s: le domaine %s est vide.\n",sNom1VirguleNom2,sDomaine(nIndexMin,nIndexMax));
}//VekteurVoir5

void VekteurVoir6(char *sNom1VirguleNom2VirguleNom3,long yVecteur1[],long yVecteur2[],long yVecteur3[],int nIndexMin,int nIndexMax){
	//affiche les index nIndexMin..nIndexMax puis, ligne suivante, iVecteur1[nIndexMin..nIndexMax] puis, ligne suivante, iVecteur2[nIndexMin..nIndexMax].
	const int kbEspace=1;//ie 1 blanc après chq virgule
	int bPar3=1 || bModeChiffre();
	int nAffiche,nE,nLargeurMax,kuIndexLg=5;
	Assert5("VecteurVoir6",sNom1VirguleNom2VirguleNom3!=0,yVecteur1!=0,yVecteur2!=0,yVecteur3!=0,kuIndexLg==nChaineLg("index"));
	if ( bCroit(0,nIndexMin,nIndexMax) ){
		//nLargeurMax:=encombrement maximal,en caractères, d'un élément du segment iQuelVecteur[nIndexMin..nIndexMax] ou de nIndexMin..nIndexMax:
			if (1 || !bModeCaractere()){
				for (nLargeurMax=nChaineLg(sEnt(nIndexMax)),nE=nIndexMin;nE<=nIndexMax;nE++)
					if (bPar3)
						nLargeurMax=iSup4(nLargeurMax,nChaineLg(sPar3(yVecteur1[nE])),nChaineLg(sPar3(yVecteur2[nE])),nChaineLg(sPar3(yVecteur3[nE])));
					else nLargeurMax=iSup4(nLargeurMax,nChaineLg(sEnt(yVecteur1[nE])),nChaineLg(sEnt(yVecteur2[nE])),nChaineLg(sEnt(yVecteur3[nE])));
			}else nLargeurMax=0;
		nLargeurMax+=kbEspace;
//d3(nLargeurMax,bPar3,kbEspace);
		//NB nChaineLg ci-dessous non adapté aux sNom accentués
		int nBlanc=iSup4(kuIndexLg,nCaractere(sItem(sNom1VirguleNom2VirguleNom3,1)),nCaractere(sItem(sNom1VirguleNom2VirguleNom3,2)),nCaractere(sItem(sNom1VirguleNom2VirguleNom3,3)));
		printf("%sindex%s: ",sTab0(),sE(nBlanc-kuIndexLg));//affiche "index" et ajoute au besoin des espaces pr atteindre la lgr de sNom1 et sNom2.
		for (nE=nIndexMin;nE<=nIndexMax || bPrint("");nE++)
			if (bModeCaractere())
				printf("%s%s ",sE(nLargeurMax-1),sEnt2(nE,0));
			else printf("%s ",sEnt2(nE,nLargeurMax));
		printf("%s%s%s: ",sTab0(),sItem(sNom1VirguleNom2VirguleNom3,1),sE(nBlanc-nCaractere(sItem(sNom1VirguleNom2VirguleNom3,1))));//qui ajoute 1 blanc sous chaq lettre du mot "index".
		for (nAffiche=0,nE=nIndexMin;nAffiche++,nE<=nIndexMax || bPrint("");nE++)
			printf("%s%s",(bPar3)? sEnt2(yVecteur1[nE],nLargeurMax) : sEnt1(yVecteur1[nE],nLargeurMax) ,(nE<nIndexMax)? ",":".");
		printf("%s%s%s: ",sTab0(),sItem(sNom1VirguleNom2VirguleNom3,2),sE(nBlanc-nCaractere(sItem(sNom1VirguleNom2VirguleNom3,2))));//qui ajoute 1 blanc sous chaq lettre du mot "index".
		for (nAffiche=0,nE=nIndexMin;nAffiche++,nE<=nIndexMax || bPrint("");nE++)
			printf("%s%s",(bPar3)? sEnt2(yVecteur2[nE],nLargeurMax) : sEnt1(yVecteur2[nE],nLargeurMax) ,(nE<nIndexMax)? ",":".");
		printf("%s%s%s: ",sTab0(),sItem(sNom1VirguleNom2VirguleNom3,3),sE(nBlanc-nCaractere(sItem(sNom1VirguleNom2VirguleNom3,3))));//qui ajoute 1 blanc sous chaq lettre du mot "index".
		for (nAffiche=0,nE=nIndexMin;nAffiche++,nE<=nIndexMax || bPrint("");nE++)
			printf("%s%s",(bPar3)? sEnt2(yVecteur3[nE],nLargeurMax) : sEnt1(yVecteur3[nE],nLargeurMax) ,(nE<nIndexMax)? ",":".");
	} else printf("%s: le domaine %s est vide.\n",sNom1VirguleNom2VirguleNom3,sDomaine(nIndexMin,nIndexMax));
}//VekteurVoir6

void VeqteurComplementer(float fVecteur[],int nIndexMin,int nIndexMax){
	//fVecteur[nIndexMin..nIndexMax] := - fVecteur[nIndexMin..nIndexMax] 
	Assert2("VeqteurComplementer",fVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (int nK=nIndexMin;nK<=nIndexMax;nK++)
		fVecteur[nK]=-fVecteur[nK];
}//VeqteurComplementer

void VeqteurCopier(float fVecteurA[],int nIndexMin,int nIndexMax,float fVecteurB[]){
	//fVecteurB[nIndexMin..nIndexMax] := fVecteurA[nIndexMin..nIndexMax] 
	int nK;
	//d3(fVecteurA!=0,fVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	Assert3("VeqteurCopier",fVecteurA!=0,fVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<=nIndexMax;nK++)
		fVecteurB[nK]=fVecteurA[nK];
}//VeqteurCopier

float fVeqteurInf(float fVecteur[],int nIndexMin,int nIndexMax){
	Assert2("fVeqteurInf",fVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	float fInf;
	for (fInf=kxLongintMax,nE=nIndexMin;nE<=nIndexMax;nE++)
		fInf=rInf(fInf,fVecteur[nE]);
	return(fInf);
}//fVeqteurInf

void VeqteurRaz(float fVecteur[],int nIndexMax){
	Assert2("VeqteurRaz",fVecteur!=0,nIndexMax>=0);
	for (int nE=1;nE<=nIndexMax;nE++)
		fVecteur[nE]=0.0;
	fVecteur[0]=nIndexMax;
}//VeqteurRaz

void VeqteurRazer(float fVecteur[],int nIndexMin,int nIndexMax){
	Assert2("VeqteurRazer",fVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (int nE=nIndexMin;nE<=nIndexMax;nE++)
		fVecteur[nE]=0.0;
}//VeqteurRazer

float fVeqteurSup(float fVecteur[],int nIndexMin,int nIndexMax){
	Assert2("fVeqteurSup",fVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	float fSup;
	for (fSup=kyLongintMin,nE=nIndexMin;nE<=nIndexMax;nE++)
		fSup=rSup(fSup,fVecteur[nE]);
	return(fSup);
}//fVeqteurSup

void VeqteurValuer(float fVecteur[],int nIndexMin,int nIndexMax,float fValeur){
	Assert2("VeqteurValuer",fVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (int nE=nIndexMin;nE<=nIndexMax;nE++)
		fVecteur[nE]=fValeur;
}//VeqteurValuer

void VeqteurVoir(char *sNom,float fQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche fQuelVecteur[nIndexMin..nIndexMax],dc bornes incluses
	int nE,nItem;
	Assert3("fQuelVecteur",sNom!=0,fQuelVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	printf("%s:\n",sNom);
		for (nItem=0,nE=nIndexMin;nE<=nIndexMax;nE++){
			printf("%5s%c ",sReel(fQuelVecteur[nE]),(nE<nIndexMax)?',':'.');
			if ((++nItem)%10==0) Ligne();
		}
	printf("\n");
}//VeqteurVoir

void VeqteurVoir0(char *sNom,float fQuelVecteur[]){
	//affiche fQuelVecteur[1..fQuelVecteur[0]],dc bornes incluses
	int nIndexMin=1,nIndexMax=trunc(fQuelVecteur[0]);
	VeqteurVoir(sNom,fQuelVecteur,nIndexMin,nIndexMax);
}//VeqteurVoir0

char *sVide(){
	char *sVide=sC1("");
	return(sVide);
}//sVide

void Voir(char *sFormat,...){
	//sFormat indique le type des paramètres qui le suivent (utiliser le format du printf,eg "%b,%d,%s,%f\n").
	int iEntier;
	char *pCar;
	char *sChaine;
	float fReel;
	va_list ap;//array of parameter
	va_start(ap,sFormat);
		//s(sFormat);
		for (pCar=sFormat;*pCar;pCar++){// *pCar permet de détecter le '\0' qui termine sFormat
			if (*pCar!='%'){
				putchar(*pCar);
				continue;
			}
			switch (*++pCar){
				case 'b': iEntier=va_arg(ap,int); printf("%s",(iEntier==0)? "Faux":"Vrai");break;
				case 'd': iEntier=va_arg(ap,int); printf("%d",iEntier);break;//"%5d": 5 caractR en tout,dont signe "-" éventuel.
				case 'f': fReel=va_arg(ap,double); printf("%f",fReel);break;//"%.2f" pr 2 caractR après le ".". "%5.2f": 5 caractR en tout.
				case 's': sChaine=va_arg(ap,char *);printf("%s",sChaine);break;
			}
		} 
	va_end(ap);
	printf(".\n");
}//Voir

int bVoyelle(char *sTexte,int nCodeCaractereRg){
	//sTexte[nCodeCaractereRg] ou Chaine[nCodeCaractereRg..nCodeCaractereRg+1] code une voyelle
	int nRg=nCodeCaractereRg;
	Assert2("bVoyelle",sTexte!=0,nCodeCaractereRg>=0);
	int bVoyelle=bVoyellE2(sTexte,&nRg);
	return(bVoyelle);
}//bVoyelle

int bVoyellE2(const char *ksTexte,int *pnCodeCaractereRg0){
	//ksTexte[*pnCodeCaractereRg0] ou Chaine[*pnCodeCaractereRg0..*pnCodeCaractereRg0+1] code une voyelle;si vrai et 2 codes, passe au code suivant
	//pour le seul ŸaeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸã";//piqûre Haüy;nValide2[1] pour le seul Ÿ
	int nCar;
	char cCode;
    #define knVoyelle1LiM 12
    #define knVoyelle2LiM 33
    #define knVoyelle3LiM 01
	//nVoyelle1 dédié voyelles sans signes diacritiques";
	int nVoyelle1[knVoyelle1LiM]={'A','E','I','O','U','Y','a','e','i','o','u','y'};
	//nVoyelle2 dédié dans l'ordre à éàèùâêîôûäïöüÿÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜã";
	int nVoyelle2[knVoyelle2LiM]={87,96,88,71,94,86,82,76,69,92, 81,74,68,65,126,118,114,108,101,119, 128,103,126,118,114,108,101,124,117,113, 106,100,93};
	//nVoyelle3 pour le seul Ÿ
	int nVoyelle3[knVoyelle3LiM]={72};
	int bVoyellE2=0;
	assert(ksTexte!=0);
	Assert1("bVoyellE2",bCroit(0,*pnCodeCaractereRg0,nChaineLg(ksTexte)));
	cCode=ksTexte[*pnCodeCaractereRg0];
	bVoyellE2=isalpha(cCode);
	if (bVoyellE2){//voyelle ou consonne?
		for (bVoyellE2=0,nCar=0; nCar<knVoyelle1LiM; nCar++)
			bVoyellE2=bVoyellE2||(cCode==nVoyelle1[nCar]);
		}
	else if (*pnCodeCaractereRg0<nChaineLg(ksTexte)) {//l'accès à sTexte[nCodeCaractereRg+1] est valide
		if (cCode==kcEchappemenT1){
			cCode=ksTexte[*pnCodeCaractereRg0+1];
			for (nCar=0; nCar<knVoyelle2LiM; nCar++)
				bVoyellE2=bVoyellE2||(cCode==-nVoyelle2[nCar]);
			if (bVoyellE2)
				(*pnCodeCaractereRg0)++;//2 codes pour un seul caractère
		}
		else if (cCode==kcEchappemenT2) {
			cCode=ksTexte[*pnCodeCaractereRg0+1];
			for (nCar=0; nCar<knVoyelle3LiM; nCar++)
				bVoyellE2= bVoyellE2 || (cCode==-nVoyelle3[nCar]);
			if (bVoyellE2)
				(*pnCodeCaractereRg0)++;//2 codes pour un seul caractère
		}
	}
	return(bVoyellE2);
}//bVoyellE2

int bVrai(int iEntier){
	//rend vrai ssi iEntier!=0
	int bVrai=(iEntier!=0) ? 1 : 0;
	return(bVrai);
}//bVrai

void While(long zIterationMax){
	//prend note du nombre maximum d'itérations acceptable dans le while ou le do while qui suit immédiatement l'appel de cette routine
//ATTENTION:l'utilisation de cette routine est incompatible avec des sorties de boucles intempestives telles que exit(), return, etc.
	Assert1("While",zIterationMax>=0);//le nombre maximum d'itérations est censé être positif
	ipWhilE++;
	Assert1("While",ipWhilE<=kuWhileMaX);//trop de boucles while/do while imbriquées (la constante kuWhileMaX est déclarée en haut de ce module)
	zWhilE[ipWhilE]=zIterationMax;
}//While

int bWhile(char *sContexte,int bExpressionBooleenne){
	//rend bExpressionBooleenne tout en gérant l'itération en cours (ie son rang ne dépasse pas zIterationMax spécifié dans l'appel à While() qui précède
//ATTENTION:l'utilisation de cette routine est incompatible avec des sorties de boucles intempestives telles que exit(), return,etc
	long zIterationRestante;
	Assert1("bWhile",bCroit(0,ipWhilE,kuWhileMaX));//la constante kuWhileMaX est déclarée en haut de ce module
	zWhilE[ipWhilE]--;//décrémente le nombre d'itérations de la boucle imbriquée de rang ipWhilE
	zIterationRestante=zWhilE[ipWhilE];
	if (zIterationRestante<0){
		printf("    *** Boucle \"while\" ou \"do while\" interrompue dans \"%s\". Le maximum spécifié a été dépassé.\n",sContexte);
		assert(zIterationRestante>=0);
	}
	if (bExpressionBooleenne==0){//la sortie imminente du while courant ramène le contexte ds la boucle imbriquée englobante,de rang ipWhilE-1
		zWhilE[ipWhilE]=0;//superflu mais ce nettoyage facilite la mise au point
		ipWhilE--;//vital
		if (ipWhilE<0){
			printf("    *** Manque un While() devant la boucle \"while\" ou \"do while\" de \"%s\" ou devant une boucle exécutée avant.\n",sContexte);
			assert(ipWhilE>=0);
		}
	}//Chaque boucle while est donc contrôlée via 1° un appel à While() avant le while et 2° un appel à bWhile() dans l'expression booléenne qui est...
	return(bExpressionBooleenne);//...attachée au while; Appel1("") à la fin du main() vérifie le bon ordonnancement des while,cf Appel1d et Appel1e.
}//bWhile

char *sZ(int iZero){
	//rend sup(0,iZero) zéros consécutifs
	char *sZ=sFois(iSup(0,iZero),'0');//sFois a appelé MallocGereR()
	return(sZ);
}//sZ

ri riZero(){
	ri riZero;
	riZero.r=riZero.i=0.0;
	return(riZero);
}//riZero

