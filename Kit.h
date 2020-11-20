//liste des #include du C. Il suffit d'un #include "Kit.h" dans les autres modules.
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <stdbool.h> //bool bBool=false; b(bBool);
	#include <math.h>
	#include <ctype.h>
	#include <string.h>
	#include <limits.h>
	#include <time.h>
  //#define NDEBUG 1 //à activer pour inhiber les assertions
	#include <assert.h>
//fonctions de mise au point;affichent le libellé de l'expression puis l'expression;nom suggéré par le format,eg f pour float.
	#define b(Entier) printf(#Entier"=%s.\n",(Entier)? "VRAI": "FAUX")
	#define bb(EntierA,EntierB) printf("(" #EntierA "," #EntierB ") =(%s,%s).\n",(EntierA)? "VRAI": "FAUX",(EntierB)? "VRAI": "FAUX")
	#define bc(EntierA,CarB) printf("(" #EntierA "," #CarB ") =(%s,%s).\n",sEnt(EntierA),sG(sC0(CarB)))
	#define bd(EntierA,EntierB) printf("(" #EntierA "," #EntierB ") =(%s,%s).\n",(EntierA)? "VRAI": "FAUX",sEnt(EntierB))
	#define c(Caractere) printf(#Caractere"=%s.\n",sG(sC0(Caractere)))
	#define cb(CarA,EntierB) printf("(" #CarA "," #EntierB ") =(%s,%s).\n",sG(sC0(CarA)),sEnt(EntierB))
	#define cc(CarA,CarB) printf("(" #CarA "," #CarB ") =(%s,%s).\n",sG(sC0(CarA)),sG(sC0(CarB)))
	#define ccc(CarA,CarB,CarC) printf("(" #CarA "," #CarB "," #CarC ") =(%s,%s,%s).\n",sG(sC0(CarA)),sG(sC0(CarB)),sG(sC0(CarC)))
	#define cd(CarA,Entier) printf("(" #CarA "," #Entier ") =(%s,%s).\n",sG(sC0(CarA)),sEnt(Entier))
	#define cd2(CarA,dA,dB) printf("(" #CarA "," #dA "," #dB ") =(%s,%s,%s).\n",sG(sC0(CarA)),sEnt(dA),sEnt(dB))
	#define cdd(CarA,dA,dB) printf("(" #CarA "," #dA "," #dB ") =(%s,%s,%s).\n",sG(sC0(CarA)),sEnt(dA),sEnt(dB))
	#define d(Entier) printf(#Entier"=%s.\n",sEnt(Entier))
	#define d0(Entier) printf(#Entier"=%d.\n",Entier)
	#define d1(Entier) printf(#Entier"=%s.\n",sEnt(Entier))
	#define d2(dA,dB) printf("(" #dA "," #dB ")=(%s,%s).\n",sEnt(dA),sEnt(dB))
	#define d2f(dA,dB,fC) printf("(" #dA "," #dB "," #fC ")=(%s,%s,%.3f).\n",sEnt(dA),sEnt(dB),fC)
	#define d3(dA,dB,dC) printf("(" #dA "," #dB "," #dC ")=(%s,%s,%s).\n",sEnt(dA),sEnt(dB),sEnt(dC))
	#define d4(dA,dB,dC,dD) printf("(" #dA "," #dB "," #dC "," #dD ")=(%s,%s,%s,%s).\n",sEnt(dA),sEnt(dB),sEnt(dC),sEnt(dD))
	#define d5(dA,dB,dC,dD,dE) printf("(" #dA "," #dB "," #dC "," #dD "," #dE ")=(%s,%s,%s,%s,%s).\n",sEnt(dA),sEnt(dB),sEnt(dC),sEnt(dD),sEnt(dE))
	#define d6(dA,dB,dC,dD,dE,dF) printf("(" #dA "," #dB "," #dC "," #dD "," #dE "," #dF ")=(%s,%s,%s,%s,%s,%s).\n",sEnt(dA),sEnt(dB),sEnt(dC),sEnt(dD),sEnt(dE),sEnt(dF))
	#define d7(dA,dB,dC,dD,dE,dF,dG) printf("(" #dA "," #dB "," #dC "," #dD "," #dE "," #dF "," #dG ")=(%s,%s,%s,%s,%s,%s,%s).\n",sEnt(dA),sEnt(dB),sEnt(dC),sEnt(dD),sEnt(dE),sEnt(dF),sEnt(dG))
	#define d8(dA,dB,dC,dD,dE,dF,dG,dH) printf("(" #dA "," #dB "," #dC "," #dD "," #dE "," #dF "," #dG "," #dH ")=(%s,%s,%s,%s,%s,%s,%s,%s).\n",sEnt(dA),sEnt(dB),sEnt(dC),sEnt(dD),sEnt(dE),sEnt(dF),sEnt(dG),sEnt(dH))
	#define d9(dA,dB,dC,dD,dE,dF,dG,dH,dI) printf("(" #dA "," #dB "," #dC "," #dD "," #dE "," #dF "," #dG "," #dH "," #dI ")=(%s,%s,%s,%s,%s,%s,%s,%s,%s).\n",sEnt(dA),sEnt(dB),sEnt(dC),sEnt(dD),sEnt(dE),sEnt(dF),sEnt(dG),sEnt(dH),sEnt(dI))
	#define db(dA,bB) printf(#dA"=%s, "#bB"=%s.\n",sEnt(dA),(bB)? "VRAI": "FAUX")
	#define dd(dA,dB) printf(#dA"=%s, "#dB"=%s.\n",sEnt(dA),sEnt(dB))
	#define ddd(dA,dB,dC) printf(#dA"=%s, "#dB"=%s, "#dC"=%s.\n",sEnt(dA),sEnt(dB),sEnt(dC))
	#define dddd(dA,dB,dC,dD) printf(#dA"=%s, "#dB"=%s, "#dC"=%s, "#dD"=%s.\n",sEnt(dA),sEnt(dB),sEnt(dC),sEnt(dD))
	#define df(dA,fB) printf("(" #dA "," #fB ")=(%s,%.3f).\n",sEnt(dA),fB)
	#define ddf(dA,dB,fC) printf("(" #dA "," #dB "," #fC ")=(%s,%s,%.3f).\n",sEnt(dA),sEnt(dB),fC)
	#define ds(dA,sB) printf("(" #dA "," #sB ")=(%s,%s).\n",sEnt(dA),sB)
	#define dds(dA,dB,sC) printf("(" #dA "," #dB "," #sC ")=(%s,%s,%s).\n",sEnt(dA),sEnt(dB),sC)
	#define dss(dA,sB,sC) printf("(" #dA "," #sB "," #sC ")=(%s,%s,%s).\n",sEnt(dA),sB,sC)
	#define dsss(dA,sB,sC,sD) printf("(" #dA "," #sB "," #sC "," #sD ")=(%s,%s,%s,%s).\n",sEnt(dA),sB,sC,sD)
	#define f(Reel) printf(#Reel"=%.2f.\n",bNul(Reel)? 0.0 : Reel)
	#define f2(fA,fB) printf("(" #fA "," #fB ")=(%.3f,%.3f).\n",fA,fB)
	#define f3(fA,fB,fC) printf("(" #fA "," #fB "," #fC ")=(%.3f,%.3f,%.3f).\n",fA,fB,fC)
	#define f4(fA,fB,fC,fD) printf("(" #fA "," #fB "," #fC "," #fD ")=(%.3f,%.3f,%.3f,%.3f).\n",fA,fB,fC,fD)
	#define f5(fA,fB,fC,fD,fE) printf("(" #fA "," #fB "," #fC "," #fD "," #fE ")=(%.3f,%.3f,%.3f,%.3f,%.3f).\n",fA,fB,fC,fD,fE)
	#define f6(fA,fB,fC,fD,fE,fF) printf("(" #fA "," #fB "," #fC "," #fD "," #fE "," #fF ")=(%.3f,%.3f,%.3f,%.3f,%.3f,%.3f).\n",fA,fB,fC,fD,fE,fF)
	#define flag "    >>> " //4 blancs au début, pas de tabulation
	#define k(Complexe) printf(#Complexe"=%s.\n",sK(Complexe))
	#define ld(Entier) printf(#Entier"=%s.\n",sEnt(Entier))
	#define ld0(Entier) printf(#Entier"=%ld.\n",Entier)
	#define ld2(ldA,ldB) printf("(" #ldA "," #ldB ")=(%s,%s).\n",sEnt(ldA),sEnt(ldB))
	#define ld3(ldA,ldB,ldC) printf("(" #ldA "," #ldB "," #ldC ")=(%s,%s,%s).\n",sEnt(ldA),sEnt(ldB),sEnt(ldC))
	#define ld4(ldA,ldB,ldC,ldD) printf("(" #ldA "," #ldB "," #ldC "," #ldD ")=(%s,%s,%s,%s).\n",sEnt(ldA),sEnt(ldB),sEnt(ldC),sEnt(ldD))
	#define ld5(ldA,ldB,ldC,ldD,ldE) printf("(" #ldA "," #ldB "," #ldC "," #ldD "," #ldE ")=(%s,%s,%s,%s,%s).\n",sEnt(ldA),sEnt(ldB),sEnt(ldC),sEnt(ldD),sEnt(ldE))
	#define m0 printf("*0* franchi.\n");
	#define m1 printf("*1* franchi.\n");
	#define m2 printf("*2* franchi.\n");
	#define m3 printf("*3* franchi.\n");
	#define m4 printf("*4* franchi.\n");
	#define m5 printf("*5* franchi.\n");
	#define m6 printf("*6* franchi.\n");
	#define m7 printf("*7* franchi.\n");
	#define m8 printf("*8* franchi.\n");
	#define m9 printf("*9* franchi.\n");
	#define nada "n'est pas au programme de L3 info.\n"
	#define s(sTexte) printf(#sTexte"=\"%s\".\n",sTexte)
	#define s2(sA,sB) printf("(" #sA "," #sB ")=(\"%s\",\"%s\").\n",sA,sB)
	#define s3(sA,sB,sC) printf("(" #sA "," #sB "," #sC ")=(\"%s\",\"%s\",\"%s\").\n",sA,sB,sC)
	#define s4(sA,sB,sC,sD) printf("(" #sA "," #sB "," #sC "," #sD ")=(\"%s\",\"%s\",\"%s\",\"%s\").\n",sA,sB,sC,sD)
	#define s5(sA,sB,sC,sD,sE) printf("(" #sA "," #sB "," #sC "," #sD "," #sE ")=(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\").\n",sA,sB,sC,sD,sE)
	#define sd(sA,dB) printf("(" #sA "," #dB ")=(\"%s\",%s).\n",sA,sEnt(dB))
	#define sd2(sA,dB,dC) printf("(" #sA "," #dB "," #dC ")=(\"%s\",%s,%s).\n",sA,sEnt(dB),sEnt(dC))
	#define sd3(sA,dB,dC,dD) printf("(" #sA "," #dB "," #dC "," #dD ")=(\"%s\",%s,%s,%s).\n",sA,sEnt(dB),sEnt(dC),sEnt(dD))
	#define sd4(sA,dB,dC,dD,dE) printf("(" #sA "," #dB "," #dC "," #dD "," #dE ")=(\"%s\",%s,%s,%s,%s).\n",sA,sEnt(dB),sEnt(dC),sEnt(dD),sEnt(dE))
	#define sd5(sA,dB,dC,dD,dE,dF) printf("(" #sA "," #dB "," #dC "," #dD "," #dE "," #dF ")=(\"%s\",%s,%s,%s,%s,%s).\n",sA,sEnt(dB),sEnt(dC),sEnt(dD),sEnt(dE),sEnt(dF))
	#define sds(sA,dB,sC) printf("(" #sA "," #dB "," #sC ")=(\"%s\",%s,\"%s\").\n",sA,sEnt(dB),sC)
	#define sf(sA,fB) printf("(" #sA "," #fB ")=(%s,%.3f).\n",sA,fB)
	#define sf2(sA,fB,fC) printf("(" #sA "," #fB "," #fC ")=(%s,%.3f,%.3f).\n",sA,fB,fC)
	#define sf3(sA,fB,fC,fD) printf("(" #sA "," #fB "," #fC "," #fD ")=(%s,%.3f,%.3f,%.3f).\n",sA,fB,fC,fD)
	#define ss(sA,sB) printf("(" #sA "," #sB ")=(\"%s\",\"%s\").\n",sA,sB)
	#define ssd(sA,sB,dC) printf("(" #sA "," #sB "," #dC ")=(\"%s\",\"%s\",%s).\n",sA,sB,sEnt(dC))
	#define sss(sA,sB,sC) printf("(" #sA "," #sB "," #sC ")=(\"%s\",\"%s\",\"%s\").\n",sA,sB,sC)
#define kF 0 //booléen FALSE
#define kV 1 //booléen TRUE
#define k0EnSonge kF
#define k1Additif kV
#define k1Afficher kV
#define k1Algebrique kV
#define k1Aller kV
#define k1Aller kV
#define k1Allouer kV
#define k1Alterer kV
#define k1Alterner kV
#define kuAlphabet 26
#define kuAlphaNumerique (26+26+10)
#define k1Amender kV
#define k1Amont kV
#define kmAntiSymetrique -1
#define k1Apparier kV
#define k1Areter kV
#define k1Ascii kV
#define k1Arquer kV
#define k1Avant kV
#define k1Bander kV
#define k1Bicolore kV
#define k1Biflot kV
#define k1Biparti kV
#define k1Bipartir kV
#define k1Bipolariser kV
#define k1Boucler kV
#define k1Brider kV
#define kuByteLim 256
#define kuByteMax (kuByteLim-1)
#define knCapaNulle 0
#define kuCapaUnitaire 1
#define knCoutNul 0
#define kuCoutUnitaire 1
#define k1Circulaire kV
#define k1Clos kV
#define k1Commutatif kV
#define kuComparateurEnTout 5
#define k1Comparer kV
#define k1Compter kV
#define k1Couleur kV
#define CouleurNom  {"coAlpha  ,coVert   ,coRouge  ,coBleu   ,coJaune  ,coOrange ,coViolet ,coNoir   ,coGris   ,coFacultF,coOmega  "}
#define CouleurType { coAlpha  ,coVert   ,coRouge  ,coBleu   ,coJaune  ,coOrange ,coViolet ,coNoir   ,coGris   ,coFacultF,coOmega   }
#define k1Coupler kV
#define k1Cout kV
#define k1Creer kV
#define k1Croissant kV
#define k1Croiser kV
#define k1Cycle kV
#define k1Dense kV
#define k1Detailler kV
#define k1Dextrorsum kV
#define k1Digraphe kV
#define k1Dire kV
#define k1Dito kV
#define Direction {diAlpha,diNord,diEst,diSud,diOuest,diOmega}
#define k1Doublon kV
#define k1Dedoubler kV
#define k1Distinguer kV
#define k1Droit kV
#define k1Droite kV
#define kE 2.7182818284
//Puissances de 10
	#define kE0 1
	#define kE1 10
	#define kE2 100
	#define kE3 1000
	#define kE4 10000
	#define kE5 100000
	#define kE6 1000000
	#define kE7 10000000
	#define kE8 100000000
	#define kE9 1000000000
	#define kE10 10000000000
	#define kE11 100000000000
	#define kE12 1000000000000
	#define kE13 10000000000000
	#define kE14 100000000000000
	#define kE15 1000000000000000
	#define kE16 10000000000000000
	#define kE17 100000000000000000
	#define kE18 1000000000000000000
	#define kE19 10000000000000000000
	#define kE20 100000000000000000000
	#define kE21 1000000000000000000000
	#define kE22 10000000000000000000000
	#define kE23 100000000000000000000000
	#define kE24 1000000000000000000000000
	#define kE25 10000000000000000000000000
	#define kE26 100000000000000000000000000
	#define kE27 1000000000000000000000000000
	#define kE28 10000000000000000000000000000
	#define kE29 100000000000000000000000000000
	#define kE30 1000000000000000000000000000000
	#define kE31 10000000000000000000000000000000
	#define kE32 100000000000000000000000000000000
//Puissances de 2
	#define k2E0 1
	#define k2E1 2
	#define k2E2 4
	#define k2E3 8
	#define k2E4 16
	#define k2E5 32
	#define k2E6 64
	#define k2E7 128
	#define k2E8 256
	#define k2E9 512
	#define k2E10 1024
	#define k2E11 2048
	#define k2E12 4096
	#define k2E13 8192
	#define k2E14 16384
	#define k2E15 32768
	#define k2E16 65536
	#define k2E17 131072
	#define k2E18 262144
	#define k2E19 524288
	#define k2E20 1048576
	#define k2E21 (k2E16*k2E5)
	#define k2E22 (k2E16*k2E6)
	#define k2E23 (k2E16*k2E7)
	#define k2E24 (k2E16*k2E8)
	#define k2E25 (k2E16*k2E9)
#define k1Egrener kV
#define k1Elementaire kV
#define k1Empiler kV
#define k1Enfiler kV
#define k1Entier kV
#define k1EntierVersReel kV
#define k1EnVrai kV
#define k1Executer kV
#define kdEpsilon 0.00001l
#define k1Feminin kV
#define k1Forcer kV
#define k1Gauche kV
#define k1General kV
#define k1Greibach kV
#define k1Incidence kV
#define k1Incrementer kV
#define k1Initialiser kV
#define k1Initier kV
#define kuIntegerMax INT_MAX //constante prédéfinie déclarée dans la bibliothèque <limits.h>.
#define kxLongintMax LONG_MAX //constante prédéfinie déclarée dans la bibliothèque <limits.h>.
#define kiIntegerMin INT_MIN //constante prédéfinie déclarée dans la bibliothèque <limits.h>.
#define k1Intriquer kV
#define k1Ligne kV
#define k1Lineaire kV
#define k1Litteraliser kV
#define k1Logn kV
#define kyLongintMin LONG_MIN //constante prédéfinie déclarée dans la bibliothèque <limits.h>.
#define kuMajusculeOffset 1 //A est la 1ère lettre de l'alphabet.
#define k1Marge kV
#define k1MargeNulle kV
#define k1Matricer kV
#define k1Maximal kV
#define k1Maximiser kV
#define k1Maximum kV
#define k1Mietter kV
#define kuMinusculeOffset 27 //a est la 27ème lettre de l'alphabet à 52 lettres obtenu en complétant les majuscules par les minuscules.
#define kuModeCaractereMax 100
#define k1NonNul kV
#define k1Obligatoire kV
#define k1Optimal kV
#define k1Optimum kV
#define k1Ouvrant kV
#define kPi 3.14159265358979
#define k1Par3 kV
#define k0ParaSymetrique 0 //symétrQ pr ce qui est des cases non nulles
#define k1Partition kV
#define k1Partitionner kV
#define k1PivotApresSommet kV
#define k1Poids kV
#define knPoidsNul 0
#define kuPoidsUnitaire 1
#define k1Ponderer kV
#define k1Poursuivre kV
#define k1Premier kV
#define kuPremierRgMax 2*kE4 //rang1 du dernier nombre 1er stocké ds le tableau de nbres 1ers uPremieR[] accessible par nPremier().
#define k1Preciser kV
#define k1Produit kV
#define k1Prolixe kV
#define k1Propre kV
#define k1QuasiGreibach kV
#define k1Redresser kV
#define k1Rouge kV
#define k1Saturer kV
#define k1Selecteur kV
#define k1Secondaire kV
#define k1SensInverse kV
#define k1Simple kV
#define k1Simplifier kV
#define k1Sinus kV
#define k1Strict kV
#define k1Simuler kV
#define k1Somme kV
#define k1SommetEnSus kV
#define k1SommetEnSusEnTete kV
#define k1Sortie kV
#define k1Standard kV
#define k1Symetrique kV
#define k1SymetriqueSinonAntisymetrique kV
#define k1Symetriser kV
#define k1Synchrone kV
#define kuTableauLigneMax kE4
#define k1Tas kV
#define k1Tout kV
#define k1Trace kV
#define k1Trianguler kV
#define k1Trier kV
#define k1Un kV
#define k1Unifier kV
#define k1Unitaire kV
#define k1Vectoriser kV
#define k1Verifier kV
#define k1Voir kV
int bBof;//booléen prédéclaré destiné à recevoir une valeur booléenne quelconque 
int iBof;//entier de signe quelconque prédéclaré
int mBof;//entier >=0 prédéclaré
int nBof;//entier >=0 prédéclaré
int uBof;//entier >0 prédéclaré
long xBof;//entier long >0 prédéclaré
long yBof;//entier long de signe quelconque prédéclaré
long zBof;//entier long >=0 prédéclaré
float fBof;//float prédéclaré
double dBof;//double prédéclaré
typedef struct{
	int h;//cote horizontale
	int v;//cote verticale
} point;
typedef struct{//nbre complexe
	float r;//partie réelle
	float i;//partie imaginaire
} ri;
typedef struct{
	int num;//numérateur
	int den;//dénominateur
} q;//ensemble Q des rationnels
enum eMatrice {maAlpha,maFormuler0,maFormuler1,maInferieur,maPremier0,maPremier1,maSuperieur,maTout,maOmega};
enum eMatriceComparer {macAlpha,macSupEgal,macInfEgal,macSingleton,macRedondant,macOmega};
enum eMatriceType {matAlpha,matHBbit1,matHBbit2,matHBtrit,matOmega};
//les routines en minuscules ci-dessous cachent les printf(),ajoutent un point final et passent à la ligne;b=booléen, e=entier, r=réel, t=texte.
	void t(char *sTexte);//affiche sTexte.
	void tb(char *sTexte,int bBooleen);//affiche sTexte puis "vrai" ou "faux" selon bBooleen.
	void tc(char *sTexte,char cCaractere);//affiche sTexte puis le cCaractere entre 2 apostrophes.
	void tri(char *sTexte,ri rComplexe);//affiche sTexte puis rComplexe: tri("riA",riA) affiche "eA:2+i" si eA vaut 2+i.
	void te(char *sTexte,long yEntier1);//affiche sTexte puis yEntier1: te("eA",eA) affiche "eA:2" si eA vaut 2.
	void tee(char *sTexte,long yEntier1,long yEntier2);
	void teee(char *sTexte,long yEntier1,long yEntier2,long yEntier3);
	void teeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4);
	void teeeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4,long yEntier5);
	void teeeeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4,long yEntier5,long yEntier6);
	void tq(char *sTexte,q qRationnel);
	void tr(char *sTexte,double dReel1);//affiche la valeur de sTexte puis celle du réel dReel1: tr("dA",dA) affiche dA:2.5 si dA vaut 2,5.
	void trr(char *sTexte,double dReel1,double dReel2);
	void trrr(char *sTexte,double dReel1,double dReel2,double dReel3);
	void tt(char *sTexte1,char *sTexte2);//affiche sTexte1 et sTexte2 entre virgules.
	void ttt(char *sTexte1,char *sTexte2,char *sTexte3);
	void tttt(char *sTexte1,char *sTexte2,char *sTexte3,char *sTexte4);
	void ttttt(char *sTexte1,char *sTexte2,char *sTexte3,char *sTexte4,char *sTexte5);
//les routines ci-dessous cachent les fonctions systèmes, gèrent le contexte des appels de routines, les chaîne de caractère et les boucles sans fin
char *sA(char *sEntreAccolade);//rend sEntreAccolade précédé de "{" et suivi de "}"
float fAbs(float fReel);//valeur absolue de fReel
int nAbs(int iEntier);//valeur absolue;déroute si le résultat est non défini,contrairement à la fonction abs() du C qui rend une valeur négative
long zAbs(long yEntier);//valeur absolue;déroute si le résultat est non défini,contrairement à la fonction labs() du C qui rend une valeur négative
q qAdd(q qA,q qB);//somme de deux nombres rationnels
ri riAdd(ri riA,ri riB);//somme de deux nombres complexes à composantes entières
ri riAff(float fReel,float fImaginaire);//rend le nombre complexe fReel+i.fImaginaire
int bAffichable(char cCaractere);
void Appel0(char *sMessage);//doit toujours être associé à Appel1;à placer en tête de routine (affiche le nom de la routine au début de son exécution)
void Appel1(char *sQuoi);//doit toujours être associé à Appel0;à placer en fin de routine (affiche le nom de la routine à la fin de son exécution)
float fArrondemi(double dNombre);//arrondi au demi-entier le plus proche
long yArrondi(double dNombre);//arrondi à l'entier le plus proche
int bAscii(char cUnCaractere);
void Assert1(char *sContexte,int bAssertion1);//comme assert() du langage C, mais affiche sContexte si bAssertion1 est faux
void Assert11(char *sContexte,int bAssertion1,int iValeur1);//Assert1 précédé d'un affichage de iValeur1 si bAssertion1 est faux
void Assert12(char *sContexte,int bAssertion1,int iValeur1,int iValeur2);
void Assert2(char *sContexte,int bAssertion1,int bAssertion2);//comme assert(bAssertion1 && bAssertion2);affiche sContexte si une assertion est fausse.
void Assert21(char *sContexte,int bAssertion1,int bAssertion2,int iValeur);//Assert2 précédé d'un affichage de iValeur si bAssertion1 ou bAssertion2 est faux
void Assert22(char *sContexte,int bAssertion1,int bAssertion2,int iValeur1,int iValeur2);
void Assert3(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3);
void Assert4(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4);
void Assert5(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5);
void Assert6(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6);
char *sAvec(int bAvecSinonSans,char *sQuoi);
int nBase4(int bA,int bB);//rend 2*bA+bB.
void Base10(int nDizaineUniteh,int *pnDizaine,int *pnUniteh);
int nBase10(int nDizaine,int nUniteh);
int nBase16(int bA,int bB,int bC,int bD);//rend 8*bA+4*bB+2*bC+bD.
void Base16(int nABCD,int *pbA,int *pbB,int *pbC,int *pbD);//inverse de nBase16
int bBit(char cCaractere);//rend vrai ssi cCaractere est '0' ou '1'.
int bBool(long yEntier);//rend vrai ssi yEntier vaut 0 ou 1.
char *sBool(long yValeur);//rend "faux" si yValeur est nul, et "vrai" sinon.
int iBorner(int iBorneInf,int iValeur,int iBorneSup);//rend iValeur si iBorneInf≤iValeur≤iBorneSup, ou la borne la plus proche de iValeur
long yBorner(long yBorneInf,long yValeur,long yBorneSup);//rend yValeur si yBorneInf≤yValeur≤yBorneSup, ou la borne la plus proche de yValeur
int bByte(long yEntier);//0 ≤ yEntier ≤ 255.
char *sC(const char *sEntreCrochet);//rend sEntreCrochet précédé de "[" et suivi de "]"
char *sC0(const char  cImprimableOuEspace);//convertit un char en string.
char *sC02(const char  cBase,int iOffset);//convertit cBase+iOffset en string.
char *sC1(const char *sNonNull);//vérifie sNonNull!=NULL puis rend sNonNull.
char *sC1p(const char *sA);//complète sA par un point terminal.
char *sC2(const char *sA,const char *sB);
char *sC2b(const char *sA,const char *sB);//concatène en ajoutant un blanc entre sA et sB.
char *sC2bp(const char *sA,const char *sB);//blanc entre sA et sB et point terminal.
char *sC2p(const char *sA,const char *sB);//point terminal.
char *sC2v(const char *sA,const char *sB);//concatène en ajoutant une virgule entre sA et sB.
char *sC3(const char *sA,const char *sB,const char *sC);
char *sC3b(const char *sA,const char *sB,const char *sC);
char *sC3bp(const char  *sA,const char  *sB,const char  *sC);
char *sC3p(const char  *sA,const char  *sB,const char  *sC);
char *sC3v(const char  *sA,const char  *sB,const char  *sC);
char *sC4(const char  *sA,const char  *sB,const char  *sC,const char  *sD);
char *sC4b(const char  *sA,const char  *sB,const char  *sC,const char  *sD);
char *sC4bp(const char  *sA,const char  *sB,const char  *sC,const char  *sD);
char *sC4p(const char  *sA,const char  *sB,const char  *sC,const char  *sD);
char *sC4v(const char  *sA,const char  *sB,const char  *sC,const char  *sD);
char *sC5(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE);
char *sC5b(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE);
char *sC5bp(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE);
char *sC5p(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE);
char *sC5v(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE);
char *sC6(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF);
char *sC6b(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF);
char *sC6bp(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF);
char *sC6p(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF);
char *sC6v(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF);
char *sC7(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG);
char *sC7b(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG);
char *sC7bp(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG);
char *sC7p(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG);
char *sC8(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH);
char *sC8b(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH);
char *sC8bp(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH);
char *sC8p(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH);
char *sC9(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH,const char  *sI);
char *sC9b(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH,const char  *sI);
char *sC9bp(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH,const char  *sI);
char *sC9p(const char  *sA,const char  *sB,const char  *sC,const char  *sD,const char  *sE,const char  *sF,const char  *sG,const char  *sH,const char  *sI);
int nCaractere(const char *ksTexte);//rend le nombre de caractères (1 pour "é") contrairement à strlen() qui rend le nombre de CODES caractères (2 pour "é"). 
void CaractereEchanger(char *pCar0,char *pCar1);
int bCarreh(int iValeur);//iValeur est le carré d'un entier
int nCarreh(int iValeur);
int nCas16(int bA,int bB,int bC,int bD);//rend 8*bA+4*bB+2*bC+bD,dc ds 0..15.
int nCas4(int bA,int bB);//rend 2*bA+bB,dc ds 0..3.
int nCas8(int bA,int bB,int bC);//rend 4*bA+2*bB+bC,dc ds 0..7.
char *sChainage(int nFois,char *sMotif);//rend sMotif dupliqué nFois
float fChaine(char *sChaine);//convertit sChaine en float (signé)
int iChaine(char *sChaine);//convertit sChaine en integer (signé)
char *sChaine(char cCaractere);//convertit cCaractere en char *; synonyme de sC0()
char *sChaine0(const char *ksTexte,int nLargeurHorsTout);//rend les nLargeurHorsTout premiers caractères de ksTexte
char *sChaine1(const char *ksTexte,int nLargeurHorsTout);//rend les nLargeurHorsTout derniers caractères de ksTexte
char *sChaine2(const char *ksTexte,int nLargeurHorsTout);//rend ksTexte centré dans nLargeurHorsTout caractères
char *sChaine3(const char *ksTexte,int nLargeurHorsTout);//rend ksTexte abrégé pr tenir sur nLargeurHorsTout caractères
char *sChaineCopie(const char *ksSource);
void ChaineCopier(const char *sSource,int nCibleLgMax,char *sCible);//cache strcpy
void ChaineCopier0(const char *sSource,char *sCible);//cache strcpy
int bChaineDistincte(const char *ksTexte);//que des caractR différents
void ChaineGarnir(char cImprimable);//change le caractère de remplissage utilisé dans les routines sChaine0,sChaine1 et sChaine2.
char *sChaineEclate(char sTexteOriginal[],char cSeparateur);//rend les caractères de sTexteOriginal séparés par des cSeparateur.
int bChaineEgale(char *sA,char *sB);
char *sChaineEtale(char *sChaine,int nEspaceEntreCaractere);//interpose nEspaceEntreCaractere blancs entre 2 caractères consécutifs de sChaine
char *sChaineEtale1(char *sChaine);//interpose 1 blanc entre 2 caractères consécutifs de sChaine
char *sChaineEtale2(char *sChaine);//interpose 2 blancs entre 2 caractères consécutifs de sChaine
void ChaineInverser(char *sChaine);
int nChaineLg(const char *sTexte);//strlen(sTexte) dans [0..kuIntegerMax]
char *sChaineSubstituer(char *sChaine,char *sAvant,char *sApres);
char *sChainon(const char *ksChaine,const int kiDebutInclus,const int kiFinIncluse);//rend ksChaine[kiDebutInclus,kiFinIncluse],ou une chaîne vide si non défini
char *sChainon0(const char *sChaine,int iFinIncluse);//rend sChaine[0,iFinIncluse],ou une chaîne vide si non défini
char *sChainon1(const char *sChaine,int iDebutInclus);//rend sChaine[nDebutInclus,…],ou une chaîne vide si non défini
int nChainonEnTout(char *sSousChaine,char *sChaine);
int mChainePos(char cQuoi,char *sDansQuoi);//rend le rang0, c'est-à-dire la position en commençant par 0, de cQuoi dans sDansQuoi;rend -1 si échec.
int mChainonPos(char *sSousChaine,char *sChaine);//étend mChainePos à une sous-chaîne plus longue qu'un caractère
int mChainePosition(const char *ksTexte,char cEnquis);//rend le rg0 du dernier caractR de ksTexte égal à cEnquis
int bChiffre(char cCaractere);//'0'..'9',comme bDecit
char *sChoix(int bOptionSinonAlternative,char *sOption,char *sAlternative);//cf (bOptionSinonAlternative)? sOption: sAlternative
char *sChoix0(int bOption,char *sOption);//si bOption,rend sOption;sinon, rend une chaîne vide. Synonyme: sChoix1()
char *sChoix1(int bOption,char *sOption);//si bOption,rend sOption;sinon, rend une chaîne vide. Synonyme: sChoix0()
int nChoix2(int bCondition1,int bCondition2);
int nChoix3(int bCondition1,int bCondition2,int bCondition3);
int nChoix4(int bCondition1,int bCondition2,int bCondition3,int bCondition4);
char cCoul(int ctCouleur);//convertit ctCouleur en caractère correspondant au type énuméré eCouleurType	
void Chrono(int bDemarrer,int *pnDuree);//pr chronométrer une exécution,l'encadrer avec Chrono(kV,&nT) et Chrono(kF,&nT); nT final donne la durée de l'exécution.
int nChrono(int bDemarrer);//pr chronométrer une exécution,l'encadrer avec nT=nChrono(kV) et nT=nChrono(kF); nT final donne la durée de l'exécution.
long zChrono(int bDemarrer);//pr chronométrer une exécution,l'encadrer avec zT=zChrono(kV) et zT=nChrono(kF); zT final donne la durée de l'exécution.
long zCnp(int nN,int nP);//nombre de combinaisons de nN éléments pris par paquets de nP éléments.
int iComparateur(char *sComparateur);//technique 
char *sComparateur(int iRang);//rend un symbole parmi {<,≤,=,>,≥}
void Confirmer(char *sMessage);//affiche sMessage et demande à l'utilisateur de valider
int bCopremier(int iA,int iB);//iA premier avec iB
char *sCouple(long yEntierA,long yEntierB);//eg "(3,15)" 
char *sCouple2(long yEntierA,long yEntierB);//eg "(03,15)"
char *sCrochet(long yEntierA,long yEntierB);//eg "[3,15]" 
char *sCrochet1(long yEntier);//eg "[3]" 
char *sCrochet2(long yEntierA,long yEntierB);//eg "[3,5]" ,comme sCrochet
char *sCrochet3(long yEntierA,long yEntierB,long yEntierC);//eg "[3,5,7]" 
void Croissant(double dMinInclus,double dDedans,double dMaxInclus);//vérifie dMinInclus ≤ dDedans ≤ dMaxInclus
int bCroissant(double dMinInclus,double dDedans,double dMaxInclus);//rend vrai ssi dMinInclus ≤ dDedans ≤ dMaxInclus
int bCroissantStrict(double dMinExclu,double dDedans,double dMaxExclu);//vérifie dMinInclus < dDedans < dMaxInclus
void CroissantStrict(double dMinExclu,double dDedans,double dMaxExclu);
int bCroit(long yMinInclus,long yDedans,long yMaxInclus);//évalue et rend yMinInclus ≤ yDedans ≤ yMaxInclus
int bCroit4(long yA,long yB,long yC,long yD);//rend yA≤yB≤yC≤yD
int bCroitStrict(long yMinExclu,long yDedans,long yMaxExclu);//évalue et rend yMinInclus < yDedans < yMaxInclus
int bCroitStrict4(long yA,long yB,long yC,long yD);//rend yA<yB<yC<yD
int bCroitStrict6(long yA,long yB,long yC,long yD,long yE,long yF);
int bCroitStrict8(long yA,long yB,long yC,long yD,long yE,long yF,long yG,long yH);
int iCube(int iValeur);//rend iValeur**3
char *sD1(char *sA,int iIndex);//renvoie sA suivi du domaine iIndex entre crochets
char *sD2(char *sA,int iIndexMin,int iIndexMax);//renvoie sA suivi du domaine iIndexMin,iIndexMax entre crochets
int bDans1(int iQuoi,int iValeur);//technique
int bDans2(int iQuoi,int iValeurA,int iValeurB);//iQuoi est iValeurA ou iValeurB
int bDans3(int iQuoi,int iValeurA,int iValeurB,int iValeurC);
int bDans4(int iQuoi,int iValeurA,int iValeurB,int iValeurC,int iValeurD);
int bDans5(int iQuoi,int iValeurA,int iValeurB,int iValeurC,int iValeurD,int iValeurE);
int bDans6(int iQuoi,int iValeurA,int iValeurB,int iValeurC,int iValeurD,int iValeurE,int iValeurF);
int bDans7(int iQuoi,int iValeurA,int iValeurB,int iValeurC,int iValeurD,int iValeurE,int iValeurF,int iValeurG);
int bDans8(int iQuoi,int iValeurA,int iValeurB,int iValeurC,int iValeurD,int iValeurE,int iValeurF,int iValeurG,int iValeurH);
int bDans9(int iQuoi,int iValeurA,int iValeurB,int iValeurC,int iValeurD,int iValeurE,int iValeurF,int iValeurG,int iValeurH,int iValeurI);
char *sDateEnClair(int nQuantieme,int nMois,int nAnnee);//années 1900 à 2100
int bDecimal(int iEntier);//dans [0..9]
int bDecit(char cCaractere);//alias bChiffre
int nDecit(int iValeur);//encombrt de iValeur, en nb de caractères à afficher 
char *sDire(int bAffirmation,char *sVerbePuisBlancPuisQqch);//rend sVerbePuisBlancPuisQqch,nié si !bAffirmation: sDire(0,"est rouge")="n'est pas grouge".
char *sDire1(int bAffirmation,char *sVerbePuisUnOuUnePuisQqch);//rend sVerbePuisUnOuUnePuisQqch,nié si !bAffirmation: sDire1(0,"a une couleur")="n'a pas de couleur".
int bDistinct3(long yA,long yB,long yC);
int bDistinct4(long yA,long yB,long yC,long yD);
double dDiv(int nNumerateur,int nDenominateur);
float fDiv(int nNumerateur,int nDenominateur);
q qDiv(q qA,q qB);//division qA/qB des deux rationnels
char *sDiv(int nNumerateur,int nDenominateur);//rend la division de nNumerateur/nDenominateur avec 2 décimales.
char *sDomaine(long yEntierA,long yEntierB);//rend [yEntierA..yEntierB]
//char *sDuree(long zUnitehDeTemps);//voir sJhms()
char *sE(int iEspace);//rend sup(0,iEspace) blancs consécutifs
float fEcartType(float fListe[]);
int bEgal3(long yA,long yB,long yC);//tous égaux
char *sEnt(long yEntier);//hors ModeCaractere,convertit yEntier en chaîne de caractères; sinon, affiche A au lieu de 1, B pour 2,etc.
char *sEnt0(long yValeur,int nCaractere);//si nCaractere>0,rend sEnt() zéroté à gauche pr obtenir nCaractere caractères en tout.
char *sEnt00(long yValeur,int nCaractere,int nMargeDroite);//sEnt0(yValeur,nCaractere-nMargeDroite) suivi de nMargeDroite blancs
char *sEnt1(long yEntier,int nCaractere);//si nCaractere>0,rend sEnt()cadré à droite sur nCaractere caractères.
char *sEnt10(long yValeur,int nCaractere,int nMargeDroite);//sEnt1(yValeur,nCaractere-nMargeDroite) suivi de nMargeDroite blancs
char *sEnt2(long yEntier,int nCaractere);//si nCaractere>0,cf sEnt3(); sinon, cf sEnt().
char *sEnt3(long yEntier,int nCaractere);//rend les décits groupés par paquets de 3, le tout cadré à droite sur nCaractere caractères.
char *sEnt30(long yEntier,int nCaractere);//idem sEnt3 mais ' ' à gauche remplacés par '0'.
int bEntier(double dNombre);//vrai ssi dNombre est assimilable à un entier de type longint
int iEntier(char *sEntierAvecOuSansSigne);//convertit sEntierAvecOuSansSigne en entier
long yEntier(char *sEntierAvecOuSansSigne);//idem
char *sEntier(long yEntier,int nCaractere);//résultat sur nCaractere caractères:sEntier("24,3)=" 24".
char *sEntier0(long yEntier,int nCaractere);//résultat sur nCaractere caractères:sEntier("24,3)="024".
char *sEntier1(long yEntier,int nCaractere);//résultat centré dans une zone de nCaractere caractères:sEntier("24,5)="  24 ".
char *sEntier2(long yEntier);//résultat sur 2 caractères.
char *sEntier3(long yEntier);//résultat sur 3 caractères.
char *sEntierCourt(int iPoids);//technique
void EntierDepiler(int *piA);
void EntierDepiler2(int *piA,int *piB);//dépile d'abord piA
void EntierDepiler3(int *piA,int *piB,int *piC);
void EntierDepiler4(int *piA,int *piB,int *piC,int *piD);
void EntierDepilerTout();
void EntierEchanger(int *piA,int *piB);
void EntierEmpiler(int iA);
void EntierEmpiler2(int iA,int iB);
void EntierEmpiler3(int iA,int iB,int iC);
void EntierEmpiler4(int iA,int iB,int iC,int iD);
void EntierEchanger(int *piA,int *piB);
char *sEntierEnClair(int iEntier,int bPremiere);
int nEntierEnTout();
char *sEntierSigneh(long yEntier);// "+5" ou "-5" ou " 0"; "12 345".
void EntyerEchanger(long *pyA,long *pyB);
float fEsperance(float fListe[]);
char *sEst(int bAssertion);//rend "est" ou "n'est pas".
char *sESt(int bAssertion);//rend "EST" ou "N'EST PAS".
char *sEtc(int iGauche,int iDroit);//technique,pr les énumérations
char *sEtc1(int iGauche,int iDroit);//technique,pr les énumérations
char *sEtc3(int iGauche,int iDroit,char * sAvant,char *sPenultieme,char *sDernier);//technique,pr les énumérations
char *sEuro(float fReel);//convertit en chaîne avec euros et centimes d'euros
char *sEuro0(float fReel,int nCaractereEnTout);
char *sEuro1(float fReel,int nCaractereEnTout);
char *sEuro2(float fReel,int nCaractereEnTout);
long xFact(int nN);//rend la factorielle de l'entier positif ou nul nN
long zFactModulo(int nN,int nModulo);
int bFaux(int iEntier);//vrai ssi iEntier==0.
long zFib(int nIndex);//fonction de Fibonacci définie par F(n)=F(n-1)+F(n-2) avec F(1)=F(2)=1, n>0.
void Flag(int bFlag);
int bFlag();
int bFleche(const char *ksChaine,int nDebutExclu);//technique
void FlipFlop(char* sContexte,int bApres,int *pbAvant);// "pb"="pointeur sur booléen";si bApres≠pbAvant,mémorise bApres dans pbAvant; sinon,déroute.
//FlipFlop,placé en tête d'une routine R(bMode,…),permet de vérifier que les appels successifs à R sont R(true,…),R(false,…),R(true,…),R(false,…),etc.
char *sFois(int nFois,char cMotif);//rend cMotif juxtaposé nFois.
int bFrontiere16(long zSizeOf);
int nFrontiere16(long zSizeOf);
int bFrontiere4(long zSizeOf);
int nFrontiere4(long zSizeOf);
int bFrontiere8(long zSizeOf);//ySizeOf est un multiple de 8
int nFrontiere8(long zSizeOf);//rend le plus petit entier ≥ zSizeOf aligné sur une frontière de 8 octets
char *sG(const char* sTexte);//rend sTexte entre guillemets.
int nHasard(int uBorneLim);//rend un entier pseudo-aléatoire dans [0..uBorneLim[, donc borne supérieure exclue.
int uHasard(int uBorneMax);//rend un entier pseudo-aléatoire dans [1..uBorneMax], donc borne supérieure incluse.
void Hasarder(int iGerme);//si iGerme non nul,réinitialise la suite de nombres pseudo-aléatoires;sinon,ne fait rien.
int bImpair(int iEntier);
double rInf(double dA,double dB);//inf(dA,dB).
int iInf(int iA,int iB);//identique à iMin(iA,iB).
int iInf3(int iA,int iB,int iC);
long yInf(long yA,long yB);//identique à iMin(iA,iB).
long yInf3(long yA,long yB,long yC);
int bInteger(long yEntier);
q qInv(q qA);//inverse du rationnel qA
int nItem(const char *ksItemVirguleItemVirguleItem);//nItem(alpha,b,c)=3;nItem(a)=1;nItem(a,,c)=3.nItem(,a,)=1.nItem(,a)=1.nItem(a,)=1.nItem()=1.
char *sItem(const char *ksItemVirguleItemVirguleItem,int uItemRang);//sItem("a,b,c",1)="a". sItem("a,b,c",5)="". sItem("a,,c",2)="".
char *sItem0(const char *ksItemVirguleItemVirguleItem,int nItemRang);//sItem("a,b,c",0)="a".
char *sItem4(int uItem,char* sItem1,char* sItem2,char* sItem3,char* sItem4);//rend l'item de numéro uItem>0 ou une chaîne vide si non défini
char *sItem6(int uItem,char* sItem1,char* sItem2,char* sItem3,char* sItem4,char* sItem5,char* sItem6);
char *sItem8(int uItem,char* sItem1,char* sItem2,char* sItem3,char* sItem4,char* sItem5,char* sItem6,char* sItem7,char* sItem8);
int nItemPos(const char *ksItemListe,char *sItemEnquis);//rend le + petit rg1 d'un item de ksItemListe égal à sItemEnquis;rend 0 si échec.
int mItemPosition(const char *ksItemListe,char *sOu,int *puItem);///rg0 du 1er caractR du 1er item de ksItemListe qui est ds sOu, et le rg1 de cet item ds *puItem.
int nItemRang(char *sQuoi,const char *ksItemVirguleItemVirguleItem);//nItemRang("deux","un,deux,trois")=2. Rend 0 si sQuoi n'est pas un item.
char *sJhms(long zUnitehDeTemps);//jours heures minutes et secondes
int nJourSemaine(int nQuantieme,int nMois,int nAnnee);
char *sK(ri rComplexe);
char *sK3(ri rComplexe);//idem mais groupe les décits par paquets de 3
void KitActiver(int bActiver);//technique
void KitAMORCER();
void KitTESTER(int iTest);
int bLettre(char cCaractere);
char cLettre(int nLettre);//donne le caractère de rang nLettre: "A" pour 1,"B" pour 2, etc, "a" pour 27, etc.
int nLettre(char cCaractere);//donne le rang 1 de cCaractere: 1 pour "A",2 pour "B", etc, 27 pour "a", etc.
char *sLettre(int iLettre);
int bLettreOuChiffre(char cCaractere);
void Ligne();//passe à la ligne.
int bLigne();//passe à la ligne et rend vrai.
int bLigne0(char *sLigneFin);//affiche sLigneFin, n'ajoute pas de point, passe à la ligne et rend vrai.
int bLigne1(char *sLigneFin);//affiche sLigneFin, ajoute un point, passe à la ligne et rend vrai.
void Ligner(int nLigneBlancheEnTout);//passe à la ligne nLigneBlancheEnTout fois. 
char *sListe(int iListe[],char cSeparateur);//rend "(2,5,6)" si iListe=[3,2,5,6]
void LigneSauter(int nLigneEnTout);//dont 0 ligne
float rLn(float rN);//logarithme népérien;rend par exemple 1.0 pour rLn(2.718).
double rLog10(double dN);//logarithme en base 10;rend par exemple 3.0 pour rLog10(1000).
int nLog10(long yValeur);//nombre de bits requis pour coder iValeur en base 10.
int nLog2(long yValeur);//nombre de bits requis pour coder iValeur en complément à 2.
double rLog2(double dN);//logarithme en base 2;rend par exemple 4.0 pour rLog2(16).
void Marner(int iValeur,int *piMin,int *piMax);
void Marner0(int *piMin,int *piMax);
int iMax(int iA,int iB);//sup(iA,iB).
double rMax(double dA,double dB);//sup(dA,ddB).
long yMax(long yA,long yB);//sup(yA,yB).
void MemIntRaz(int piMemOrigine[],int nItemEnTout);
void MemIntValuer(int piMemOrigine[],int nItemEnTout,int iValeur);
void MemLongRaz(int pyMemOrigine[],int nItemEnTout);
void MemLongValuer(int pyMemOrigine[],int nItemEnTout,long yValeur);
int bMajuscule(char cCaractere);
char *sMajuscule(char* sCaractere);//rend la majuscule qui correspond à sCaractere 
char *sMajusculer(char *sTexte);//rend sTexte entièrement majusculé
int iMin(int iA,int iB);//inf(iA,iB).
double rMin(double dA,double dB);//inf(dA,dB).
long yMin(long yA,long yB);//inf(yA,yB).
int bMinuscule(char cCaractere);
char *sMinuscule(char *sCaractere);//rend la minuscule qui correspond à sCaractere 
void ModeCaractere(int tMode);//bModeCaracterE:=1 si tMode=1, :=0 si tMode=0, :=le mode précédent si tMode=-1.
int bModeCaractere();//rend vrai ssi le mode caractère est actif.
void ModeCaracteriser(int cListe[]);//technique
void ModeChiffre(int tMode);
int bModeChiffre();
int iModulo(long yDividende,int uDiviseur);//résultat dans ]-uDiviseur..uDiviseur[,ie nModulo multiplié par le signe de iDividende
int nModulo(long yDividende,int uDiviseur);//résultat dans [0..uDiviseur[
long zModulo(long yDividende,long xDiviseur);//résultat dans [0..xDiviseur[
int uModulo1(long zDividende,int uDiviseur);//résultat dans [1..uDiviseur];calcule un modulo classique puis remplace le résultat éventuel 0 par uDiviseur.
q qMul(q qA,q qB);//produit de deux rationnels
ri riMul(ri riA,ri riB);//produit de deux nombres complexes à composantes entières
char *sNbre(int bFormatEntier,float fValeur);
char *sNbre1(int bFormatEntier,float fValeur,int nCaractereEnTout);
char *sNiet(int bOui,char *sQuoi);//rend sQuoi, ou "non" suivi de sQuoi si bOui est faux
char *sNon(int bNegativer,char *sVerbe);//encadre avec "ne" et "pas" si bNegativer est vrai.
int bNul(double dNombre);//dNombre est très proche de zéro
int briNul(ri riA);//riA est nul
q qOpp(q qA);//opposé du rationnel qA
ri riOpp(ri riA);//opposé d'un complexe
char *sOk(int bOui);//rend "oui" ou "non" selon bOui.
char *sOui(int bVrai,char *sVerbe);//encadre avec "ne" et "pas" si bPositiver est faux.
char *sP(char *sEntreParenthese);//rend sEntreParenthese entre 2 parenthèses,eg sP("oui") rend "(oui)".
char *sP1(char *sA,int iIndex);//renvoie sA suivi de iIndex entre parenthèses
char *sP2(char *sA,int iIndexMin,int iIndexMax);//renvoie sA suivi de iIndexMin,iIndexMax entre parenthèses
int bPair(int iEntier);
char *sPar3(long yEntier);//convertit yEntier en chaîne en groupant les chiffres par 3, eg sPar3(12345) rend "12 345".
char *sPas(char *sVerbe,int bNegativer);//encadre avec "ne" et "pas" si bNegativer.
void Pause();//suspend l'exécution et attend une frappe clavier minimale.
int nbPermutation(int uDistinct[]);//rend le nb de permutO d'élts ds la liste uDistinct[] censée ctenir des entiers non nuls distincts
long xPgcd(long xA,long xB);//rend le Plus Grand Commun Diviseur de xA et xB positifs ;en O(lg(Sup(xA,xB))
long zPgcd(long zA,long zB);//rend le Plus Grand Commun Diviseur de yA et yB de signes qcq;en O(lg(Sup(|yA|,|yB|))
char *sPhrase0(char *sTexte);//rend sTexte avec 1ère lettre majusculée.
char *sPhrase1(char *sTexte);//rend sTexte avec 1ère lettre majusculée et point final.
char *sPhrase2(char *sTexte);//rend sTexte entièrement majusculé et ajoute un point final si pas déjà là.
long yPlafond(double rN);//rend le plus petit entier supérieur ou égal à rN.
long yPlancher(double rN);//rend le plus grand entier inférieur ou égal à rN.
char *sPluriel(long zEffectif,char *sSingulier);//sPluriel(3,"fruit") rend "3 fruits" et sPluriel(3,"fruit$ rouge$") rend "3 fruits rouges".
char *sPluriel0(long zEffectif,char *sSingulier);//idem sPluriel mais "0" est convertit en "aucun"
char *sPluriel1(long zEffectif,char *sSingulier,int bFeminin);//idem sPluriel mais "0" est convertit en "aucun" ou "aucune"
char *sPluriel2(char *sVerbe,long zEffectif,char *sSingulier);
char *sPluriel3(char *sVerbe,long zEffectif,char *sSingulier,int bFeminin);
char *sPluriel4(long zEffectif,char *sSingulier,int bFeminin);//technique
char *sPluriel5(long zEffectif,char *sSingulier,int bFeminin);//technique
char *sPluriel6(long zEffectif,char *sSingulier,int bFeminin,int dPlusieursSeuil);//technique
long zPpcm(long xA,long xB);//plus petit commun multiple.
int mPoidsFort(long yEntier);//rend le bit de poids fort de yEntier,eg 3 si yEntier=13 puisque 13 s'écrit 1101 en base 2.
char *sPourcent(int nNumerateur,int nDenominateur);//rapport absolu;pr le rapport relatif,cf sSurcout
int bPremier(int iNombre);//vrai ssi iNombre est un nombre premier
int nPremier(int nRangDuNombrePremier);//rend le nombre premier de rang1 nRangDuNombrePremier,ie nPremier(1)=2, nPremier(2)=3, nPremier(3)=5...
void Print(char *sPrint);//affiche sPrint suivi de "\n"
int bPrint(char *sPrint);//affiche sPrint suivi de "\n" et rend faux
int bPrint0(char *sPrint);//affiche sPrint et rend faux
int nPuissance(int iOperande,int nExposant);//nExposant positif ou nul.
long yPuissance(long yOperande,int nExposant);//nExposant positif ou nul.
long zPuissance(long yOperande,int nExposant);//nExposant positif ou nul.
int bPuissanceDe10(long yOperande);//yOperande est une puissance de 10 positive.
int bPuissanceDe2(long yOperande);//yOperande est une puissance de 2 positive.
int nPuissanceModulo(int iOperande,int nExposant,int nModulo);//O(log(nExposant))
long zPuissanceModulo(long yOperande,long zExposant,long xModulo);//(yOperande**zExposant) % xModulo
char *sQ(q qRationnel);
int nRac(long zEntier);//plus grand entier inférieur ou égal à la racine carrée de zEntier
ri riRac(int uRacineEnTout,int nRang);//rend la racine de l'unité de rang nRang
char *sRatio(long yNumerateur,long yDenominateur);//convertit yNumerateur/yDenominateur en chaîne de caractères: sRatio(6,5) rend "1.20".
char *sReel(float fReel);
char *sReel0(float fReel,int nCaractereEnTout);
char *sReel1(float fReel,int nCaractereEnTout);
char *sReel2(float fReel,int nCaractereEnTout);
char *sReel3(float fReel,int nCaractereEnTout);
char *sReel4(float fReel,int nCaractereEnTout);
void ReelEchanger(double *pdA,double *pdB);
int bReelEgal(float fA,float fB);//à kdEpsilon près
int bReelEgal0(float fA,float fB,int mPuissanceDe10);//à 10**mPuissanceDe10 près,dc mPuissanceDe10<0
void ReelEgaliser(int nDecimale);//kdEpsilon:=1/10**nDecimale
int bReelNul(float fValeur);//=0 à kdEpsilon près
int bReelUn(float fValeur);//=1 à kdEpsilon près
void Regler(int iLigneBlanche);//technique;affiche nott une règle de longueur maximale imprimable sans troncature (124 caractères)  
char cSigne(long yEntier);//"+" ou "-" ou " " selon le signe de yEntier ("+" pour yEntier=0).
char *sSigne(long yEntier);//"+" ou "-" ou " " selon le signe de yEntier ("+" pour yEntier=0).
int tSigne(int iValeur);//rend +1 si iValeur>0,-1 si iValeur<0, et 0 sinon.
char *sSigneEnClair(long yEntier);//"positif" ou "négatif" ou "nul" selon le signe de yEntier.
float fSignePres(int bSigneInverser,float fValeur);//si bSigneInverser est vrai,rend -fValeur;sinon,rend +fValeur.
int iSignePres(int bSigneInverser,int iValeur);//si bSigneInverser est vrai,rend -iValeur;sinon,rend +iValeur.
long ySignePres(int bSigneInverser,long yValeur);//si bSigneInverser est vrai,rend -yValeur;sinon,rend +yValeur.
int nSommePuissance(int uEntierMax,int uExposant);//somme des puissances d'ordre uExposant des entiers consécutifs de 1 à uEntierMax
void Stop(int byMassacre);//sortie catastrophe;affiche byMassacre compris entre 0 et 255 puis stoppe l'exécution.
q qSub(q qA,q qB);//différence de deux rationnels
ri riSub(ri riA,ri riB);//différence de deux nombres complexes à composantes entières
char *sSucces(int bSuccesSinonEchec);//rend "succès" ou "échec"
int iSup(int iA,int iB);//max(iA,iB).
int iSup3(int iA,int iB,int iC);
int iSup4(int iA,int iB,int iC,int iD);
double rSup(double dA,double dB);//identique à rMax(dA,dB).
long ySup(long yA,long yB);//identique à yMax(yA,yB).
char *sSurcout(int uNumerateur,int uDenominateur);//rapport relatif ≥0; pr le rapport absolu,cf sPourcent
int iSwitch3(int iCas,int iValeur1,int iValeur2,int iValeurParDefaut);
char *sTab(int nIndentation);//rend 4*nIndentation blancs consécutifs
char *sTab0();
int nTabulation();
void TableauVoir(char *sNom,int iQuelTableau[kuTableauLigneMax][kuTableauLigneMax],int nIndexMin1,int nIndexMax1,int nIndexMin2,int nIndexMax2);
void Tabuler(int iTabulation);
void Titrer(char *sTitre);//affiche sTitre centré sur une ligne de 100 caractères de large et passe à la ligne.
void Titrer0(int nTitreLargeur);//modifie la largeur du titre, ou largeur par défaut si nul
void Titrer1(char *sTitre);//affiche sTitre étalé puis centré sur une ligne de 100 caractères de large et passe à la ligne.
void Titrer2(char *sTitre,char cMotif);//idemTitrer, mais le caractère répété de part et d'autre du titre est cMotif.
char *sTriplet(long yEntierA,long yEntierB,long yEntierC);
int bTrit(int tVariable);//vrai ssi tVariable est un trit à valeur dans {-1,0,+1}
ri riUn();//rend le nbre cplexe 1.
char *sUn(char *sVerbe,int bUn);//si bUn,rend sVerbe suivi de "un";sinon,encadre sVerbe avec "ne" et "aucun".
char *sUnOuUne(char *sVerbe,int bUn,int bFeminin);//si bUn,rend sVerbe suivi de "un" ou "une";sinon,encadre sVerbe avec "ne" et "aucun" ou "aucune".
char *sUne(char *sVerbe,int bUne);//si bUne,rend sVerbe suivi de "une";sinon,encadre sVerbe avec "ne" et "aucune".
void VecteurAdditionner(int iVecteurA[],int iVecteurB[],int nIndexMin,int nIndexMax,int iSomme[]);
void VecteurAdditionner0(int iVecteurA[],int iVecteurB[],int iSomme[]);//iVecteurA[0] ctient le nb d'élts
void VecteurAdditionnerReel(double dVecteurA[],double dVecteurB[],double dSomme[]);
void VecteurAffecter(int iVecteur[],int nIndexMin,int nIndexMax,int iValeurAffectee);
void VecteurAjouter(int iVecteurA[],int nIndexMin,int nIndexMax,int iAjout);//ajoute iAjout à iVecteurA[nIndexMin..nIndexMax]
void VecteurAjouter0(int iVecteurA[],int iAjout);//ajoute iAjout à iVecteurA[1..iVecteurA[0]]
void VecteurComplementer(int bVecteur[],int nIndexMin,int nIndexMax);
void VecteurCompleter(int iVecteur[],int nIndexPris,int nIndexMax);
int bVecteurContient(int nEnquis,int iVecteur[]);//vrai ssi nEnquis est dans iVecteur[1..iVecteur[0]]
int mVecteurContient(int nEnquis,int iVecteur[],int nIndexMin,int nIndexMax);//rend le rang de nEnquis dans iVecteur[nIndexMin..nIndexMax],ou -1 si absent
int nVecteurContient(int nEnquis,int iVecteur[],int nIndexMin,int nIndexMax);//rend le nombre d'occurrences de nEnquis dans iVecteur[nIndexMin..nIndexMax]
int bVecteurContient1(int nEnquis,int nCardinal,int iVecteur[]);//vrai ssi nEnquis est dans iVecteur[1..nCardinal]
void VecteurCopier(int iVecteurA[],int nIndexMin,int nIndexMax,int iVecteurB[]);//iVecteurB[nIndexMin..nIndexMax] := iVecteurA[idem]
void VecteurCopier0(int iVecteurA[],int iVecteurB[]);//iVecteurB[0..iVecteurA[0]] := iVecteurA[0..iVecteurA[0]]
void VecteurCopierReel(double dVecteurA[],int nIndexMin,int nIndexMax,double dVecteurB[]);
void VecteurCopierReel0(double dVecteurA[],double dVecteurB[]);
int bVecteurCroit(int iVecteur[],int nIndexMin,int nIndexMax,int bOrdreStrict);
void VecteurCumuler(int iVecteur[],int nIndexMin,int nIndexMax);
void VecteurCumuler0(int iVecteur[]);
void VecteurDecaler(int iVecteur[],int nIndexMin,int nIndexMax,int iDecalage);
int bVecteurDistinct(int iVecteur[],int nIndexMin,int nIndexMax,int bNonNul);//les éléments de iVecteur[nIndexMin,nIndexMax] (non nuls) sont tous distincts
int nVecteurDoublet(int iVecteur[],int nIndexMin,int nIndexMax);//nb de paires d'éléments consécutifs qui sont égaux
int nVecteurDoublon(int iVecteur[],int nIndexMin,int nIndexMax);//au moins 2 éléments de iVecteur[nIndexMin..nIndexMax] sont égaux
int nVecteurEcreter(int iVecteur[],int nIndexMin,int nIndexMax,int iPlancherMin,int iPlafondMax);
int bVecteurEgal(int iVecteurA[],int iVecteurB[],int nIndexMin,int nIndexMax);//les vecteurs sont identiques dans [nIndexMin..nIndexMax]
void VecteurEtendre(int iVecteur[],int nIndexMin,int nIndexMax,long yVecteur[]);
void VecteurHasarder0(int iVecteur[],int nIndexMin,int nIndexMax,int nValeurMaximale);//initialisation aléatoire ds [0..nValeurMaximale]
void VecteurHasarder1(int iVecteur[],int nIndexMin,int nIndexMax,int uValeurMaximale);//initialisation aléatoire ds [1..uValeurMaximale]
void VecteurIndexer(int iVecteur[],int nIndexMin,int nIndexMax);
long yVecteurInf(int iVecteur[],int nIndexMin,int nIndexMax);
void VecteurInverser(int iVecteur[],int nIndexMin,int nIndexMax);//iVecteur[nIndexMin..nIndexMax] := iVecteur[nIndexMax..nIndexMin] 
int iVecteurMax(int iVecteur[],int nIndexMin,int nIndexMax);//rend 9 si iVecteur=(1,6,1,6,6,9,8)
int iVecteurMin(int iVecteur[],int nIndexMin,int nIndexMax);//rend 1 si iVecteur=(5,6,1,6,6,9,8)
void VecteurMultiplier(int iVecteurA[],int nIndexMin,int nIndexMax,int iMultiplicande);
void VecteurMultiplier0(int iVecteurA[],int iMultiplicande);
void VecteurMultiplierReel(double dVecteurA[],int nIndexMin,int nIndexMax,double dMultiplicande);
void VecteurMultiplierReel0(double dVecteurA[],double dMultiplicande);
float fVecteurNorme(int iVecteur[]);//rend la norme euclidienne de iVecteur[0] élts
double dVecteurNorme(double dVecteur[]);//rend la norme euclidienne de dVecteur[0] élts
int bVecteurNul(int iVecteur[],int nIndexMin,int nIndexMax);
int nVecteurOccurrence(int nEnquis,int iVecteur[],int nIndexMin,int nIndexMax);//nombre d'occurrences de nEnquis dans iVecteur[nIndexMin..nIndexMax] 
int nVecteurOccurrenceMax(int iVecteur[],int nIndexMin,int nIndexMax);//nombre d'occurrences maximal d'un élément de iVecteur[nIndexMin..nIndexMax] 
void VecteurOpposer(int iVecteur[],int nIndexMin,int nIndexMax);
int bVecteurPremier(int iVecteur[],int nIndexMin,int nIndexMax);
long yVecteurProduit(int iVecteur[],int nIndexMin,int nIndexMax);
long yVecteurProduitScalaire(int iVecteurA[],int iVecteurB[]);//iVecteurA[0] élts
double dVecteurProduitScalaire(double dVecteurA[],double dVecteurB[]);
void VecteurRaz(int iVecteur[],int nIndexMax);//iVecteur[1..nIndexMax]=0 et iVecteur[0]=nIndexMax
void VecteurRazer(int iVecteur[],int nIndexMin,int nIndexMax);//iVecteur[nIndexMin..nIndexMax]=0
int bVecteurSemblable(int iVecteurA[],int iVecteurB[],int nIndexMin,int nIndexMax);//iVecteurA = copie désordonnée de iVecteurB
long yVecteurSomme(int iVecteur[],int nIndexMin,int nIndexMax);
long yVecteurSommeAlterneh(int yVecteur[],int nIndexMin,int nIndexMax);//rend V[nIndexMin]-V[nIndexMin+1]+V[nIndexMin+2]],etc jusqu'à V[nIndexMax].
void VecteurSoustraire(int iVecteurA[],int iVecteurB[],int nIndexMin,int nIndexMax,int iDifference[]);
void VecteurSoustraire0(int iVecteurA[],int iVecteurB[],int iDifference[]);//iVecteurA[0] ctient le nb d'élts
void VecteurSoustraireReel(double dVecteurA[],double dVecteurB[],double dDifference[]);
void VecteurSubstituer(int iVecteur[],int nIndexMin,int nIndexMax,int iAvant,int iApres);
long yVecteurSup(int iVecteur[],int nIndexMin,int nIndexMax);
void VecteurTasser(int iVecteur[],int nIndexMin,int nIndexMax);//tasse les éléments à gauche en supprimant les zéros 
void VecteurTasser0(int iVecteur[]);//tasse les éléments à gauche en supprimant les zéros 
void VecteurTrier(int iQuelVecteur[],int nIndexMin,int nIndexMax);//trie par ordre croissant en O(N*N)
void VecteurTrier2(int iQuelVecteur[],int nIndexMin,int nIndexMax,int nIndex[]);//trie par ordre croissant en O(N*N)
void VecteurTrierCompacter(int iQuelVecteur[]);//O(N*N) //iQuelVecteur[0] ctient le nb d'élts avant compactage, puis après compactage
void VecteurTrierVite(int iQuelVecteur[],int nIndexMin,int nIndexMax);//trie par ordre croissant en O(NlogN)
void VecteurValuer(int iVecteur[],int nIndexMin,int nIndexMax,int iValeur);//iVecteur[nIndexMin..nIndexMax]=iValeur
void VecteurViser(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax);
void VecteurViser0(char *sNom,int iQuelVecteur[]);
void VecteurVisionner(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax,int bSensInverse);//affiche les valeurs du vecteurs d'entiers de type integer.
void VecteurVoir(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax);//affiche proprt les valeurs du vecteurs d'entiers de type integer.
void VecteurVoir0(char *sNom,int iQuelVecteur[]);//affiche iQuelVecteur[1..iQuelVecteur[0]]
void VecteurVoir1(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax);//idem + n°s des index affichés ligne précédente
void VecteurVoir11(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax);//affiche les doublets (index,iQuelVecteur[index])
void VecteurVoir2(char *sNom1VirguleNom2,int iVecteur1[],int iVecteur2[],int nIndexMin,int nIndexMax);//les 2 vecteurs, alignés l'un sous l'autre
void VecteurVoir3(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax,int nCaractereParItem);//variante de VecteurVoir
void VecteurVoir4(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax);//affiche les seuls éléments non nuls
void VecteurVoir5(char *sNom1VirguleNom2,int iVecteur1[],int iVecteur2[],int nIndexMin,int nIndexMax);//affiche les 2 vecteurs, 1 par ligne.
void VecteurVoir6(char *sNom1VirguleNom2VirguleNom3,int iVecteur1[],int iVecteur2[],int iVecteur3[],int nIndexMin,int nIndexMax);
void VekhteurCopier(ri riVecteurA[],int nIndexMin,int nIndexMax,ri riVecteurB[]);//nb complexes
void VekhteurVoir(char *sNom,ri riQuelVecteur[],int nIndexMin,int nIndexMax);//affiche le vecteur de nb complexes
void VekteurAdditionner(long yVecteurA[],long yVecteurB[],int nIndexMin,int nIndexMax,long ySomme[]);
void VekteurAdditionner0(long yVecteurA[],long yVecteurB[],long ySomme[]);
void VekteurAffecter(long yVecteur[],int nIndexMin,int nIndexMax,long yValeurAffectee);
void VekteurAjouter(long yVekteurA[],int nIndexMin,int nIndexMax,long yAjout);
void VekteurAjouter0(long yVekteurA[],long yAjout);
int bVekteurContient(long yEnquis,int nCardinal,long yVecteur[]);//vrai ssi yEnquis est dans yVecteur[1..nCardinal]
void VekteurCopier(long yVecteurA[],int nIndexMin,int nIndexMax,long yVecteurB[]);
void VekteurCopier0(long yVecteurA[],long yVecteurB[]);//yVecteurB[0..yVecteurA[0]] := yVecteurA[0..yVecteurA[0]]
void VekteurDecaler(long yVecteur[],int nIndexMin,int nIndexMax,int iDecalage);
int bVekteurEgal(long yVecteurA[],long yVecteurB[],int nIndexMin,int nIndexMax);
long yVekteurInf(long iVekteur[],int nIndexMin,int nIndexMax);
int bVekteurNul(long yVecteur[],int nIndexMin,int nIndexMax);
int bVekteurNul0(long yVecteur[]);//yVecteur[1..yVecteur[0]] est nul partout 
long yVekteurProduit(long yVecteur[],int nIndexMin,int nIndexMax);
void VekteurRaz(long yVecteur[],int nIndexMax);
void VekteurRazer(long yVecteur[],int nIndexMin,int nIndexMax);
void VekteurRazer0(long yVecteur[]);//annule yVecteur[1..yVecteur[0]] 
long yVekteurSomme(long yVecteur[],int nIndexMin,int nIndexMax);
long yVekteurSommeAlterneh(long yVecteur[],int nIndexMin,int nIndexMax);//rend V[nIndexMin]-V[nIndexMin+1]+V[nIndexMin+2]],etc jusqu'à V[nIndexMax].
void VekteurSoustraire(long yVecteurA[],long yVecteurB[],int nIndexMin,int nIndexMax,long yDifference[]);
void VekteurSoustraire0(long yVecteurA[],long yVecteurB[],long yDifference[]);
long yVekteurSup(long iVekteur[],int nIndexMin,int nIndexMax);
void VeqteurRaz(float fVecteur[],int nIndexMax);
void VeqteurRazer(float fVecteur[],int nIndexMin,int nIndexMax);
void VekteurTrier(long yQuelVecteur[],int nIndexMin,int nIndexMax);//O(N*N)
void VeqteurValuer(float fVecteur[],int nIndexMin,int nIndexMax,float fValeur);
void VekteurVoir(char *sNom,long yQuelVecteur[],int nIndexMin,int nIndexMax);//affiche les valeurs du vecteurs d'entiers de type integer.
void VekteurVoir0(char *sNom,long yQuelVecteur[]);//affiche yQuelVecteur[1..yQuelVecteur[0]]
void VekteurVoir1(char *sNom,long yQuelVecteur[],int nIndexMin,int nIndexMax);//idem mais les numéros des index sont affichés ligne précédente
void VecteurVoir10(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax);//technique
void VekteurVoir2(char *sNom,long yQuelVecteur[],int nIndexMin,int nIndexMax);//affiche les doublets (index,yQuelVecteur[index])
void VekteurVoir5(char *sNom1VirguleNom2,long yVecteur1[],long yVecteur2[],int nIndexMin,int nIndexMax);
void VekteurVoir6(char *sNom1VirguleNom2VirguleNom3,long yVecteur1[],long yVecteur2[],long yVecteur3[],int nIndexMin,int nIndexMax);
void VeqteurComplementer(float fVecteur[],int nIndexMin,int nIndexMax);
void VeqteurCopier(float fVecteurA[],int nIndexMin,int nIndexMax,float fVecteurB[]);
float fVeqteurInf(float fVecteur[],int nIndexMin,int nIndexMax);
float fVeqteurSup(float fVecteur[],int nIndexMin,int nIndexMax);
void VeqteurVoir(char *sNom,float fQuelVecteur[],int nIndexMin,int nIndexMax);
void VeqteurVoir0(char *sNom,float fQuelVecteur[]);
char *sVide();//renvoie une chaîne vide
void Voir(char *sFormat,...);//affiche tous les paramètres mentionnés dans sFormat,eg Voir("%f,%s %d.\n",3.14,"environ",3).
int bVoyelle(char *sTexte,int nCodeCaractereRg);//vrai ssi sTexte[nCodeCaractereRg] est une voyelle.
int bVrai(int iEntier);//rend 1 ssi iEntier est non nul;rend 0 sinon.
void While(long zIterationMax);//prend note du nombre maximum d'itérations à exécuter dans le while qui suit l'appel de cette routine.
int bWhile(char *sContexte,int bExpressionBooleenne);//rend bExpressionBooleenne après avoir vérifié que l'itération en cours ne dépasse pas zIterationMax spécifié li-1.
char *sZ(int iZero);//rend sup(0,iZero) zéros consécutifs
ri riZero();//rend le nbre cplexe 0.


