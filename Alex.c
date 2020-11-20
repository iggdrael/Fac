#include "Kit.h"
#include "Alex.h"
#include "Erreur.h"
#include "Tds.h"
//module d'analyse lexicale
#define knAEFetatMaX 14
#define knByteLiM 256
//ci-dessous, ne toucher ni à "ccAlphA,ccButoiR", ni à "ccBlanC,ccDiverS,ccOmegA". Insérer les nouvelles classes dans ]ccButoiR,ccBlanC[
enum eCaractereClassE {ccAlphA,ccButoiR,ccDeciT,ccMajusculE,ccMinusculE,ccPoinT,ccSeparateuR,ccApostrophE,ccGuillemeT,ccOperateuR,ccParenthesE,ccBlanC,ccDiverS,ccOmegA};
#define knClasseCaractereMaX (ccOmegA-ccAlphA+1)
#define kuCodeSourceLgMaX 200
#define knLexemeMaX	511
#define knTrancheMaX 147
#define kbVoiR kV

int iAEF[1+knAEFetatMaX][1+knClasseCaractereMaX];
int bAlexAmorceR;
int ccCaractereClassE[knByteLiM];
char *sCodeSourcE;//alloué dans AlexAMORCER
//ci-dessous, ne toucher ni à "lcAlphA,lcBlanC,lcInconnU", ni à "lcFinDeFichieR,lcOmegA". Insérer les nouvelles classes dans ]lcInconnU,lcFinDeFichieR[
char *sLexemeClassE  ="lcAlphA,lcBlanC,lcInconnU,lcEntieR,lcReheL,lcIdentificateuR,lcOperateuR,lcParenthesE,lcSeparateuR,lcMotCleF,lcTextE,lcFinDeFichieR,lcOmegA";
int nLexemeEnTouT;
typedef struct {int classe;int indexdebut;int indexfin;int lign;int valh;int prio;int suiv;} rLexemE;
rLexemE lxmChN[1+knLexemeMaX];//la chaîne lexicale est générée dans lxmChN
char *sMotCleF="achat,stock";
char cAlexTdS;
int ipLexemeEmpileR;
int  uLexemeEmpileR[100];
int nLexemeEmpileR=0;//prio
char *sOperateurListE="<,>,?,+,-,*,/,^,(,),[,],(+,(-,(*,(/,(^,+),-),*),/),^)";

int nAlexOperateuR(int uLexeme);
void AutomateAffecteR(int bVoir);
void ClasseCaractereDefiniR(int bVoir);
int bCodeSourceAnalyseR(int bVoiR);
void CodeSourceTrancheR(int nDebutInclus,int nFinExclue,int bVoir,char *sTranche);
char *sLexemE(int nLexeme);
void LexemeAugmenteR();
void LexemeEmpileR(int uLxmIndex,int nLxmClasse,int nLxmDebutInclus,int nLxmFinExclue, int bVoir,int *pnErreurLexicale);
void LexemeInsereR(char *sOperateur,int bParentheseurOuvrant,int uPredecesseur,int bVoir,int nLexemeEnTout0,int *pnLexemeEnTout1);//(O(1)
void LexemeVoiR(char *sQuoi);
void OperateurParentheseR(int bVoir);
int nOperateurPrioriteh(int uLxmIndex);

void AlexAfficher(){
	//affiche le code source ligne par ligne
	const int kbNumeroter = kV;
	int nC,nLg,iLigne,bSeparateur;
	//t("AlexAfficher");
	for (nC=0,iLigne=1,nLg=nChaineLg(sCodeSourcE);nC<nLg && (sCodeSourcE[nC]!='$');nC++){
		bSeparateur=(sCodeSourcE[nC]==';');
		if (bSeparateur){
			ErreurAfficher(abs(iLigne));
			printf("\n");
			iLigne=abs(iLigne)+1;//ie il faudra afficher iLigne avant d'afficher le prochain caractère du code source
		}else {
			if (kbNumeroter && iLigne>0){
				printf("Ligne %d: ",iLigne);
				iLigne= - iLigne;//négatif: le numéro iLigne a bien été affiché
			}
			printf("%c",sCodeSourcE[nC]);
		}
	}
	printf("\n");
}//AlexAfficher

void AlexAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
	int kbVoir=kF;
	AutomateAffecteR(kbVoir);
	ClasseCaractereDefiniR(kbVoir);
	sCodeSourcE=malloc(1+kuCodeSourceLgMaX);
	bAlexAmorceR=kV;
}//AlexAMORCER

int bAlexAnalyser(char *sCode){
	int bAnalyser;
	//Appel0("bAlexAnalyser");
		//AlexINITIALISER();
		strcpy(sCodeSourcE,sCode);
		printf("   Code source analysé:\"%s\".\n",sCodeSourcE);
		//AlexAfficher();
		bAnalyser=bCodeSourceAnalyseR(1|| kbVoiR);
	//Appel1("bAlexAnalyser");
	return(bAnalyser);
}//bAlexAnalyser

int nAlexCalcul(int uLexeme){
	//Calcul->Somme || Produit || Terme 
	int nCalcul=0;
	if (bAlexLexeme(uLexeme)){
		if (bAlexOperateur(uLexeme+1,'+'))
			nCalcul=1;
		else if (bAlexOperateur(uLexeme+1,'*'))
			nCalcul=2;
		else if (nAlexTerme(uLexeme))
			nCalcul=3;
		else if (bAlexParentheseur(uLexeme,'('))
			nCalcul=4;
	};
	return(nCalcul);
}//nAlexCalcul

char *sAlexChaine(int nLexeme){
	char *sChaine=sLexemE(nLexeme);
	//ds(nLexeme,sChaine);
	return(sChaine);
}//sAlexChaine

int bAlexDate(int uLexeme){
	//uLexeme est bien une date de l'année 2017 (l'année de l'ouverture de la bibliothèque) et au-delà donnée sous la forme JJMMAA.
	int bDate,nEntier,nJour,nMois,nAnnee;
	int nJourEnTout[1+12]={-1,    31,28,31,    30,31,30,    31,31,30,    31,30,31};
	//sd("bAlexDate",uLexeme);
	bDate=bAlexEntier(uLexeme);
	if (bDate){
		nEntier=mAlexEntier(uLexeme);
		nAnnee=nEntier%100;
		nEntier=(nEntier-nAnnee)/100;
		nMois=nEntier%100;
		nJour=(nEntier-nMois)/100;
		//teee("nJour,nMois,nAnnee",nJour,nMois,nAnnee);
		bDate=bCroit(1,nJour,31) && bCroit(1,nMois,12) && bCroit(17,nAnnee,99);
		bDate=bDate && nJour<=nJourEnTout[nMois] || (nJour==29 && nMois==2 && nAnnee%4==0);
	}
	return(bDate);
}//bAlexDate

void AlexDenoncer(int nLexeme){
	//affiche le numéro de la ligne de code source et la lexie à dénoncer suite à une erreur lexicale,syntaxique ou d'une autre nature.
	int bVoir=0;
	int nLexemeEnCause,uLxm,nLigne;
	char sLexeme[knByteLiM];
	if (bVoir) Appel0("AlexDenoncer");
		//nLigne:=rang1 de la ligne contenant le lexème de rang nLexeme
			//d2(nLexeme,nLexemeEnTouT);
			for (nLigne=1,uLxm=1;uLxm<nLexeme;uLxm++)
				if (lxmChN[uLxm].classe==lcSeparateuR)
					nLigne++;
		nLexemeEnCause=iBorner(1,nLexeme,nLexemeEnTouT);//dc valide,quitte à choisir un voisin immédiat du lexème à dénoncer
		//d2(lxmChN[nLexemeEnCause].indexdebut,lxmChN[nLexemeEnCause].indexfin);
		CodeSourceTrancheR(lxmChN[nLexemeEnCause].indexdebut,lxmChN[nLexemeEnCause].indexfin,kF,/**/sLexeme);
		printf("   *** ligne %d,lexème n°%d %s",nLigne,nLexeme,sG(sLexeme));
	if (bVoir) Appel1("AlexDenoncer");
}//AlexDenoncer

int bAlexEntier(int uLexeme){
	int bEntier;
	bEntier=bAlexLexeme(uLexeme) && (lxmChN[uLexeme].classe==lcEntieR);
	return(bEntier);
}//bAlexEntier

int mAlexEntier(int uLexeme){
	int nApostrophe,uBase,nC,nCarMax,nDecit,mEntier=0,bValide;
	if (bAlexEntier(uLexeme)){
		//s(sLexemE(uLexeme));
		//sscanf(sLexemE(uLexeme),"%d",&nEntier);
		//Titrer("##########");
		nApostrophe=mChainePos('\'',sLexemE(uLexeme));
		bValide=nApostrophe<0 || nApostrophe>0 && mChainePos('\'',sChainon(sLexemE(uLexeme),nApostrophe+1,100))<0;
		//sd2(sLexemE(uLexeme),nApostrophe,bValide);
		//nChainePos(sLexemE(uLexeme),'\');
		//d(nEntier);
		if (bValide){
			nCarMax=nChaineLg(sLexemE(uLexeme));
			//d(nCarMax);
			if (nApostrophe>0){
				uBase=sLexemE(uLexeme)[nCarMax-1]-'0';
				Assert1("nAlexEntier",bCroit(1,uBase,9));
				nCarMax=nApostrophe-1;
			}else uBase=10;
			for (mEntier=0,nC=0;nC<nCarMax+(nApostrophe>0);nC++){
				nDecit=sLexemE(uLexeme)[nC]-'0';
				bValide=bValide && bCroit(0,nDecit,uBase-1);
				mEntier=mEntier*uBase+nDecit;
				//d4(nDecit,uBase,bValide,mEntier);
			}
			//d(mEntier);
		};
		if (!bValide)
			mEntier=-1;
	}
	return(mEntier);
}//mAlexEntier

int nAlexEtat(int uLexeme){
	//Etat->achat | stock 
	int nEtat=0;
	if (bAlexLexeme(uLexeme) && lxmChN[uLexeme].classe==lcMotCleF){
		switch (lxmChN[uLexeme].valh){
			case mcAchat:		nEtat=1;break;
			case mcStock:		nEtat=2;break;
			default:			nEtat=0;
		};
	};
	return(nEtat);
}//nAlexEtat

int nAlexExpression(int uLexeme){
	//rend la pré-vision de l'expression courante: 1 si somme, 2 si produit, 3 si terme, et 0 si échec
	//Expression->Somme | Produit | Terme 
	int nExpression=0,nOperateur;
	if (bAlexLexeme(uLexeme)){
		switch (nOperateur=nAlexOperateuR(uLexeme)){
			case 1:		nExpression=1;break;//Somme
			case 2:		nExpression=2;break;//Produit
			default:	if (lxmChN[uLexeme].classe==lcIdentificateuR)
							nExpression=3;//Terme
						if (bAlexParentheseur(uLexeme,'('))
							nExpression=3;//ExpressionParenthésée
		};
	};
	//sd2("nAlexExpression",uLexeme,nExpression);
	return(nExpression);
}//nAlexExpression

int bAlexFermant(int uLexeme,char cFermant){
	//uLexeme est le lcParenthesE cFermant+')'
	int bFermant=bAlexLexeme(uLexeme) && lxmChN[uLexeme].classe==lcParenthesE && bChaineEgale(sLexemE(uLexeme),sC2(sC0(cFermant),")"));
	return(bFermant);
}//bAlexFermant

int bAlexFinFichier(int uLexeme){
	int bFinFichier;
	bFinFichier=(uLexeme>=nLexemeEnTouT);
	return(bFinFichier);
}//bAlexFinFichier

int bAlexHoraire(int uLexeme){
	#define kuHeureHeurePointMinuteMinuteLg 5
	int bHoraire;
	float rHoraire;
	int nMinute;
	char sLexeme[knByteLiM];
	bHoraire=bAlexReel(uLexeme);
	if (bHoraire){
		CodeSourceTrancheR(lxmChN[uLexeme].indexdebut,lxmChN[uLexeme].indexfin,kF,/**/sLexeme);
		//tt("sLexeme",sG(sLexeme));
		bHoraire=bHoraire && (nChaineLg(sLexeme)==kuHeureHeurePointMinuteMinuteLg);
		if (bHoraire){
			sscanf(sLexeme,"%f5.2",&rHoraire);
			//tr("rHoraire",rHoraire);
			nMinute=trunc(rHoraire*100);
			nMinute=nMinute%100;
			//d(nMinute);
			bHoraire=bHoraire && bCroit(0,nMinute,59);
			//compléter le code pour valider les heures
		}
	}
	return(bHoraire);
}//bAlexHoraire

int bAlexIdentificateur(int uLexeme){
	int bIdentificateur;
	bIdentificateur=bAlexLexeme(uLexeme) && lxmChN[uLexeme].classe==lcIdentificateuR;
	return(bIdentificateur);
}//bAlexIdentificateur

void AlexINITIALISER(){//O(?)
	//relance le présent module
	Assert1("AlexINITIALISER1",bAlexAmorceR);
	//remplir une TDS avec les mot-clés de Alex
		int bCreer=bTdsAllouer(1,&cAlexTdS);
		for (int uItem=mcAlpha+1;uItem<mcOmega;uItem++)
			bCreer=bCreer && bTdsAjouterValuer(cAlexTdS,sItem(sMotCleF,uItem),uItem);
		TdsVoir(cAlexTdS,"cAlexTdS");
	Assert1("AlexINITIALISER2",bCreer);
}//AlexINITIALISER

int nAlexInstruction(int uLexeme){
	//Instruction->Acces || Achat || Affichage || Emprunt || Etat || Radiation || Reservation || Restitution || Affectation	int nInstruction=0;
	int nInstruction=0;
	if (bAlexLexeme(uLexeme)){
		switch (lxmChN[uLexeme].classe){
			case  lcMotCleF:		nInstruction=5;break;//Acces
			case  lcOperateuR:		switch (sCodeSourcE[lxmChN[uLexeme].indexdebut]){
										case '<':	nInstruction=4;break;//Emprunt
										case '?':	nInstruction=7;break;//Reservation
										case '>':	nInstruction=8;break;//Restitution
										case '[':	nInstruction=3;break;//Affichage
									};break;
			case  lcIdentificateuR:	nInstruction=9;break;//Affectation
			case  lcEntieR:			nInstruction=1;break;//Acces
			case  lcReeL:			nInstruction=2;break;//Achat
		}
	};
	//sd2("nAlexInstruction",uLexeme,nInstruction);
	return(nInstruction);
}//nAlexInstruction

int bAlexLexeme(int uLexeme){
	int bLexeme=bCroit(1,uLexeme,nLexemeEnTouT);
	return(bLexeme);
}//bAlexLexeme

char *sAlexLxm(int uLexeme){
	char *sLxm;
	if (uLexeme<=nAlexOffset(1))
		sLxm=sChaine1(sC2(sE(5),sItem(sOperateurListE,uLexeme)),5);
	else if (uLexeme<=nAlexOffset(2))
		sLxm=sC2(sChainon1(sItem(sLexemeClassE,uLexeme-nAlexOffset(1)+1),2),sE(10));
	else if (uLexeme<=nAlexOffset(0))
		sLxm=sItem(sMotCleF,uLexeme-nAlexOffset(2));
	return(sLxm);
}//sAlexLxm

int uAlexLexeme(char *sLexeme){
	//rend le rang1 d'un opérateur réel ou virtuel,ou 0 si échec
	int uLexeme=nItemRang(sLexeme,sOperateurListE);
	return(uLexeme);
}//uAlexLexeme

int nAlexLexeme(int uLexeme){
	//rend le numéro de colonne ds la table Asynt.iFirst qui est associé au uLexeme,ou le nb de colonnes
	Assert1("nAlexLexeme",bAlexLexeme(uLexeme));
	int nLexeme;
//{lcAlphA,lcBlanC,lcInconnU,lcEntieR,lcReeL,lcIdentificateuR,lcOperateuR,lcParenthesE,lcSeparateuR,lcMotCleF,lcTextE,lcFinDeFichieR,lcOmegA};
	switch (lxmChN[uLexeme].classe){
		case lcOperateuR		:nLexeme=lxmChN[uLexeme].valh;break;
		case lcParenthesE		:nLexeme=lxmChN[uLexeme].valh;break;

		case lcInconnU			:nLexeme=nAlexOffset(1)+lcInconnU;break;
		case lcEntieR			:nLexeme=nAlexOffset(1)+lcEntieR;break;
		case lcIdentificateuR	:nLexeme=nAlexOffset(1)+lcIdentificateuR;break;
		case lcReeL				:nLexeme=nAlexOffset(1)+lcReeL;break;
		case lcSeparateuR		:nLexeme=nAlexOffset(1)+lcSeparateuR;break;
		case lcTextE			:nLexeme=nAlexOffset(1)+lcTextE;break;
		case lcFinDeFichieR		:nLexeme=nAlexOffset(1)+lcFinDeFichieR;break;
		case lcMotCleF			:nLexeme=nAlexOffset(2)+lxmChN[uLexeme].valh;break;
		default					:Assert1("nAlexLexeme default",0); break;
	}
	//d2(nLexemeOuZero,nLexeme);
	//d3(lcFinDeFichieR,nItem(sMotCleF),nItem(sOperateurListE));
	return(nLexeme);
}//nAlexLexeme

int nAlexLigne(int uLexeme){
	//rend le rang1 de la ligne qui contient le lexème d'index uLexeme
	int nLigne;
	Assert1("nAlexLigne",bCroit(1,uLexeme,nLexemeEnTouT));
	nLigne=lxmChN[uLexeme].lign;
	return(nLigne);
}//nAlexLigne

int bAlexMotClef(int uLexeme,int nMotClefNumero){
	//si nMotClefNumero=0, rend vrai ssi le lxm de rg uLexeme est un mot-clef; si >0,rend vrai ssi nMotClefNumero est bien le n° du mot-clef de rg uLexeme
	int bMotClef;
	bMotClef=bAlexLexeme(uLexeme) && (lxmChN[uLexeme].classe==lcMotCleF);
	if (nMotClefNumero>0)
		bMotClef=lxmChN[uLexeme].valh==nMotClefNumero;
	return(bMotClef);
}//bAlexMotClef

int nAlexOffset(int nCumul){
	//rend le nbre total de colonnes ds la table Asynt.iFirst qui est associé au nLexemeOuZero,ou le nb de colonnes
	int nOffset=0;
	switch (nCumul){
		case 1:	nOffset=nItem(sOperateurListE);break;
		case 2:	nOffset=nItem(sOperateurListE)+lcFinDeFichieR;break;
		case 0:	nOffset=nItem(sOperateurListE)+lcFinDeFichieR+nItem(sMotCleF);;break;
		default:Assert1("nAlexOffset default",0); break;
	}
	return(nOffset);
}//nAlexOffset

int bAlexOperateur(int uLexeme,char cOperateur){
	int bOperateur=bAlexLexeme(uLexeme) && lxmChN[uLexeme].classe==lcOperateuR && sCodeSourcE[lxmChN[uLexeme].indexdebut]==cOperateur;
	return(bOperateur);
}//bAlexOperateur

int nAlexOperateuR(int uLexeme){
	//rend 1 si le 1er opérateur rencontré est "+", 2 si c'est un "*", et 0 sinon.
	int uLxm,nOperateur,nNiveau=1;
	for (nOperateur=0,uLxm=uLexeme;uLxm<=nLexemeEnTouT;uLxm++){//break
		if (nNiveau==1 && lxmChN[uLxm].classe==lcOperateuR)
			switch (sCodeSourcE[lxmChN[uLxm].indexdebut]){
				case '+'	:	nOperateur=1;break;//Somme
				case '*'	:	if (nOperateur==0)
									nOperateur=2;
								break;//Produit
			}
		if  (bAlexParentheseur(uLxm,'(')){//sauter les lexèmes qui suivent
			nNiveau++;
		}
		if  (bAlexParentheseur(uLxm,')')){
			nNiveau--;
			if (nNiveau<=0)
				break;//inutile de chercher plus loin
		}
		if  (lxmChN[uLxm].classe==lcSeparateuR)//inutile de chercher plus loin
			break;
	}
	//sd2("nAlexOperateuR",uLexeme,nOperateur);
	return(nOperateur);
}//nAlexOperateuR

int bAlexOuvrant(int uLexeme,char cOuvrant){
	//uLexeme est le lcParenthesE '('+cOuvrant
	int bOuvrant=bAlexLexeme(uLexeme) && lxmChN[uLexeme].classe==lcParenthesE && bChaineEgale(sLexemE(uLexeme),sC2("(",sC0(cOuvrant)));
	return(bOuvrant);
}//bAlexOuvrant

int bAlexParentheseur(int uLexeme,char cParenthese){
	//uLexeme est le lcParenthesE '(' ou ')' ou '[' ou ']'
	int bParentheseur=bAlexLexeme(uLexeme) && lxmChN[uLexeme].classe==lcParenthesE && sLexemE(uLexeme)[0]==cParenthese;
	return(bParentheseur);
}//bAlexParentheseur

int nAlexProduitOuTerme(int uLexeme){
	//rend 1 un opérateur est un *
	int uLxm,nProduitOuTerme;
	for (nProduitOuTerme=0,uLxm=uLexeme;uLxm<=nLexemeEnTouT;uLxm++){//break
		if (lxmChN[uLxm].classe==lcOperateuR)
			switch (sCodeSourcE[lxmChN[uLxm].indexdebut]){
				case '+'	:	break;//Somme=butée rencontrée
				case '*'	:	if (nProduitOuTerme==0){
									nProduitOuTerme=1;
									break;//Produit
								}
			}
		if  (lxmChN[uLxm].classe==lcSeparateuR)//inutile de chercher plus loin
			break;
	}
	if (nProduitOuTerme==0 && nAlexTerme(uLexeme))
		nProduitOuTerme=2;
	sd2("nAlexOperateuR",uLexeme,nProduitOuTerme);
	return(nProduitOuTerme);
}//nAlexProduitOuTerme

int nAlexProgramme(int uLexeme){
	int nProgramme=0;
	if (nAlexInstruction(uLexeme)>0)
		nProgramme=1;
	else if (bAlexFinFichier(uLexeme))
		nProgramme=2;
	return(nProgramme);
}//nAlexProgramme

int bAlexReel(int uLexeme){
	int bReel;
	bReel=bAlexLexeme(uLexeme) && lxmChN[uLexeme].classe==lcReeL;
	return(bReel);
}//bAlexReel

float fAlexReel(int uLexeme){
	float fReel;
	Assert1("fAlexReel",bAlexReel(uLexeme));
	sscanf(sLexemE(uLexeme),"%f\n",&fReel);
	//tr("fReel",fReel);
	return(fReel);
}//fAlexReel

int bAlexSeparateur(int uLexeme){
	int bSeparateur;
	bSeparateur=bAlexLexeme(uLexeme) && lxmChN[uLexeme].classe==lcSeparateuR;
	return(bSeparateur);
}//bAlexSeparateur

int nAlexSuite(int uLexeme){
	//rend la pré-vision de l'instruction courante:  1 si Interdiction, 2 si Inscription, et 0 si échec
	//Suite->Interdiction || Inscription
	//		Interdiction->Livre->Texte
	//		Inscription->Nom->Identificateur
	int nSuite=0;
	if (bAlexLexeme(uLexeme)){
		switch (lxmChN[uLexeme].classe){
			case  lcTextE:			nSuite=1;break;//Interdiction
			case  lcIdentificateuR:	nSuite=2;break;//Inscription
		}
	};
	return(nSuite);
}//nAlexSuite

int nAlexTerme(int uLexeme){//pré-vision instruction courante: 1 si Entier 2 si Expression, et 0 si échec.
	//Terme->Entier || Identifiant || ExpressionParenthésée   
	int nTerme=0;
	if (bAlexLexeme(uLexeme))
		switch (lxmChN[uLexeme].classe){
			case  lcEntieR:			nTerme=1;break;
			case  lcIdentificateuR:	nTerme=2;break;
			case  lcParenthesE:		if (bAlexParentheseur(uLexeme,'('))
										nTerme=3;
									break;
		}
	return(nTerme);
}//nAlexTerme

void AlexTESTER(int iTest){
	//teste le présent module
	int bSucces;
	Appel0(sC2("AlexTESTER,test n°",sEnt(iTest)));
		sCodeSourcE="27+3.14;AB=5*8$";
		switch (iTest) {
			case  1:	sCodeSourcE="27 + 3.14 ; CD = 5 * 8 ' $";break;
			case  5:	sCodeSourcE="27+3.14;EF      =  5*8$";break;
			case  8:	sCodeSourcE="27+3.14;EF      =  5*8$$";break;
			case  4:	sCodeSourcE="$";break;
			case  3:	sCodeSourcE="";break;
			case  2:	sCodeSourcE="24 ; 5 ; 3...2 ; 4$";break;
			case  6:    sCodeSourcE="ALPHA1BETA22GAMMA333DELTA4444$$";break;
			default:	Assert1("AlexTESTER: entrée de case inconnue",0); break;
		}
		printf("sCodeSourcE=\"%s\".\n",sCodeSourcE);
		bSucces=bCodeSourceAnalyseR(kbVoiR);
		if (!bSucces)
			AlexDenoncer(0);
	Appel1(sC2("AlexTESTER,test n°",sEnt(iTest)));
}//AlexTESTER	

int bAlexTexte(int uLexeme){
	int bTexte;
	bTexte=bAlexLexeme(uLexeme) && lxmChN[uLexeme].classe==lcTextE;
	return(bTexte);
}//bAlexTexte

void AutomateAffecteR(int bVoir){
	//affecte une fois pour toutes l'automate d'états finis iAEF[]
	char *sAEF[1+knAEFetatMaX];
	const int knbPas=5;//nombre total de caractères consommés pour indiquer le numéro de l'état suivant ds la i-ième ligne de texte sAEF[i]
	int nL,nC;
	if (bVoir) Appel0("AutomateAffecteR");
        //classes:         $  0..9  AZ   az    .    ;    '    "  operH ()  blc autre
		sAEF[ 0]="    0    9    3    5    8    2    7    2   12    6   10    1    2";//dispatcheur vers les sous-automates
		sAEF[ 1]="    0    0    0    0    0    0    0    0    0    0    0    1    0";//lcBlanC
		sAEF[ 2]="    0   -2   -2   -2   -2   -2   -2   -2   -2   -2   -2   -2    2";//lcInconnU
		sAEF[ 3]="    0   -3    3   -3   -3   11   -3   13   -3   -3   -3   -3   -3";//lcEntieR, ou pas
		sAEF[ 4]="    0   -4    4   -4   -4   -4   -4   -4   -4   -4   -4   -4   -4";//lcReeL
		sAEF[ 5]="    0   -5    5    5    5   -5   -5   -5   -5   -5   -5   -5   -5";//lcIdentificateuR
		sAEF[ 6]="    0   -6   -6   -6   -6   -6   -6   -6   -6   -6   -6   -6   -6";//lcOperateuR
		sAEF[ 7]="    0   -8   -8   -8   -8   -8   -8   -8   -8   -8   -8   -8   -8";//lcSeparateuR
		sAEF[ 8]="    0   -9   -9   -9    8   -9   -9   -9   -9   -9   -9   -9   -9";//lcMotCleF
		sAEF[ 9]="    0  -11  -11  -11  -11  -11  -11  -11  -11  -11  -11  -11  -11";//lcFinDeFichieR
		sAEF[10]="    0   -7   -7   -7   -7   -7   -7   -7   -7   -7   -7   -7   -7";//lcParenthesE
		sAEF[11]="    0   -1    4   -1   -1  -20   -2   -1   -1   -1   -1   -1   -1";//un point a été rencontré;constante réelle attendue
		sAEF[12]="    0   -3   12   12   12   12   12   12   14   12   12   12   12";//un guillemet a été rencontré;guillemet fermant attendu
		sAEF[13]="    0   -3    3   12   12   12   12   12    8   12   12   12   12";//une apostrophe a été rencontrée;décit attendu
		sAEF[14]="    0  -10  -10  -10  -10  -10  -10  -10   12  -10  -10  -10  -10";//un second guillemet a été rencontré
//enum eLexemeClassE{lcAlphA,lcBlanC,lcInconnU,lcEntieR,lcReeL,lcIdentificateuR,lcOperateuR,lcParenthesE,lcSeparateuR,lcMotCleF,lcTextE,lcFinDeFichieR,lcOmegA};
		for (nL=0;nL<=knAEFetatMaX;nL++){
			for (nC=0;nC<=knClasseCaractereMaX;nC++){
				sscanf(sAEF[nL]+knbPas*nC,"%d\n",&iAEF[nL][nC]);
				if (bVoir)
					printf("[%2d,%2d]=%2d ",nL,nC,iAEF[nL][nC]);
			}
			if (bVoir)
				printf("\n");
		}
	if (bVoir) Appel1("AutomateAffecteR");
}//AutomateAffecteR

void ClasseCaractereDefiniR(int bVoir){
	//définit une fois pour toutes la classe ClasseDeC au caractère C en mémorisant ClasseDeC dans ccCaractereClassE[C] pour tout C.
	if (bVoir) Appel0("ClasseCaractereDefiniR");
		int nC,nClasse;
		char *sOperateur="+-*/^%&#<>?=";
		for (nC=0;nC<knByteLiM;nC++){
			nClasse=ccDiverS;
			if (isdigit(nC)) nClasse=ccDeciT;
			if (isupper(nC)) nClasse=ccMajusculE;
			if (islower(nC)) nClasse=ccMinusculE;
			if (nC=='.') nClasse=ccPoinT;
			if (nC=='\'') nClasse=ccApostrophE;
			if (nC==';') nClasse=ccSeparateuR;
			if (nC=='"') nClasse=ccGuillemeT;
			if ( mChainePos(nC,sOperateur)>=0) nClasse=ccOperateuR;
			if ( (nC=='(') || (nC==')') || (nC=='[') || (nC==']') ) nClasse=ccParenthesE;
			if (nC==' ') nClasse=ccBlanC;//blanc ou assimilé
			if (nC=='$') nClasse=ccButoiR;
			ccCaractereClassE[nC]=nClasse;
			if (bVoir)
				printf("caractère %3d    classe %2d \n",nC,nClasse);
		}
	if (bVoir) Appel1("ClasseCaractereDefiniR");
}//ClasseCaractereDefiniR

int bCodeSourceAnalyseR(int bVoiR){
	//analyse le code source censé figurer dans sCodeSourcE[] et empile dans lxmChN la chaîne lexicale;rend faux ssi un lexème inconnu est empilé
	int bAnalyser,nC,nClasse,nClim,nErreurLexicale,nEtat,nEtat0,nDebut,nLxm,lcType,bDetailAfficher=0;
	//Appel0("bCodeSourceAnalyseR");
		Assert1("bCodeSourceAnalyseR0",bAlexAmorceR);
		bAnalyser=kV;
		nLexemeEnTouT=0;
		nClim=nChaineLg(sCodeSourcE);
		for (nEtat=0,nC=0,nDebut=nC;nC<=nClim;nC++){// *** donc atteint et lit un caractère "\0"
			nClasse=ccCaractereClassE[sCodeSourcE[nC]];
			nEtat0=nEtat;
			nEtat=iAEF[nEtat0][nClasse];
			if (bDetailAfficher)
				printf("Itération n°%d: à l'état courant %d, '%c' est lu, la classe de ce caractère vaut %d, donc iAEF[%d][%d] rend l'état %d.\n",nC,nEtat0,sCodeSourcE[nC],nClasse,nEtat0,nClasse,nEtat);
			//d2(nEtat,bAnalyser);
			if (nEtat<=0){
				if (nEtat0!=lcBlanC){//empiler le lexème courant dans la chaîne lexicale de sommet nLexemeEnTouT
					lcType=-nEtat;
					nErreurLexicale=(nEtat==-20)? eAlexReel: ((lcType==lcInconnU)? eAlexInconnu : 0);
					if (nEtat<=-20)
						lcType=lcInconnU;
					Assert1("bCodeSourceAnalyseR1",bCroitStrict(lcAlphA,lcType,lcOmegA));
					LexemeEmpileR(++nLexemeEnTouT,lcType, nDebut, nC,bDetailAfficher,&nErreurLexicale);
					if (nErreurLexicale )
						ErreurEmpiler(nErreurLexicale,nLexemeEnTouT);
					bAnalyser=bAnalyser && (lcType!=lcInconnU);
				} else if (bDetailAfficher)
					printf("\t\t Suite de blancs: aucun lexème n'est empilé.\n");
				nDebut=nC;//saute donc aussi les blancs éventuels
				nEtat=iAEF[nEtat0=0][nClasse];//inutile de relire le caractère qui vient d'être lu puisque sa classe est nClasse.
			}
		}
		if ((nLexemeEnTouT<=0) || (lxmChN[nLexemeEnTouT].classe!=lcFinDeFichieR))
			LexemeEmpileR(++nLexemeEnTouT,lcFinDeFichieR, nDebut, nDebut+1, !k1Afficher,&nErreurLexicale);//assimile donc la lexie '\0' au '$'.
		if (!k1Afficher) LexemeVoiR("Chaîne lexicale générée par l'AEF");
		if (1) OperateurParentheseR(!k1Afficher);
		if (k1Afficher) LexemeVoiR("Chaîne lexicale étendue");
		if (k1Afficher && bVoiR &&!bAnalyser)
			t(sC3b("      Il",sUn("y a",!bAnalyser),"lexème inconnu dans la chaîne lexicale"));
		//d(nClim);
		//d(lcFinDeFichieR);
		Assert2("bCodeSourceAnalyseR2",nLexemeEnTouT>0,(!bAnalyser || lxmChN[nLexemeEnTouT].classe==lcFinDeFichieR));
		//tb("bAnalyser",bAnalyser);
	//Appel1("bCodeSourceAnalyseR");
	//bAnalyser:=aucun lexeme inconnu n'a été empilé
		for (bAnalyser=1,nLxm=1;nLxm<=nLexemeEnTouT;nLxm++)
			bAnalyser=bAnalyser && (lxmChN[nLxm].classe!=lcInconnU);
	return bAnalyser;
}//bCodeSourceAnalyseR

void CodeSourceTrancheR(int nDebutInclus,int nFinExclue,int bVoir,char *sTranche){
	//copie dans sTranche le fragment sCodeSourcE[nDebutInclus..nFinExclue[ ou rend sFinDeFichier afin que sTranche ne soit pas vide
	char *sFinDeFichier="Fin de fichier";
	int nC,bValide;
	bValide=bCroit(0,nDebutInclus,nFinExclue-1) && (nFinExclue-nDebutInclus<knTrancheMaX);
	if (bValide){
		for (nC=nDebutInclus;nC<nFinExclue;nC++)
			sTranche[nC-nDebutInclus]=sCodeSourcE[nC];
		sTranche[nFinExclue-nDebutInclus]='\0';
		if (nChaineLg(sTranche)==0)//copie d'un caractère '\0' dès nDebutInclus, caractéristQ du lexème "fin de fichier"
			strcpy(sTranche,sFinDeFichier);
	} else sTranche[nFinExclue-nDebutInclus]='\0';
	//else Assert1(sC5p("CodeSourceTrancheR:tranche [",sEnt(nDebutInclus),"..",sEnt(nFinExclue),"[ invalide"),bValide);
}//CodeSourceTrancheR

char *sLexemE(int uLexeme){
	//rend le fragment sCodeSourcE[nDebutInclus..nFinExclue[
	char *sLexeme=malloc(100);
	sLexeme[0]='\0';
	CodeSourceTrancheR(lxmChN[uLexeme].indexdebut,lxmChN[uLexeme].indexfin,!k1Voir,sLexeme);
	if (nChaineLg(sLexeme)==0){//colexeme
		sLexeme=sItem(sOperateurListE,lxmChN[uLexeme].valh);
	}
	return(sLexeme);
}//sLexemE

void LexemeEmpileR(int uLxmIndex,int nLxmClasse,int nLxmDebutInclus,int nLxmFinExclue, int bVoir,int *pnErreurLexicale){
	char sLexeme[knByteLiM];
	int nRang;
	//Appel0("LexemeEmpileR");
		Assert3("LexemeEmpileR1",uLxmIndex>0,bCroitStrict(lcAlphA,nLxmClasse,lcOmegA),bCroit(0,nLxmDebutInclus,nLxmFinExclue));
		lxmChN[uLxmIndex].classe=nLxmClasse;
		lxmChN[uLxmIndex].indexdebut=nLxmDebutInclus;
		lxmChN[uLxmIndex].indexfin=nLxmFinExclue;
		lxmChN[uLxmIndex].prio=nOperateurPrioriteh(uLxmIndex);
		lxmChN[uLxmIndex].suiv=uLxmIndex+1;
		//d3(uLxmIndex,nLxmDebutInclus,nLxmFinExclue);
		lxmChN[uLxmIndex].lign=(uLxmIndex==1)? 1: lxmChN[uLxmIndex-1].lign;
		if (uLxmIndex>1 && lxmChN[uLxmIndex-1].classe==lcSeparateuR)
			lxmChN[uLxmIndex].lign++;
		CodeSourceTrancheR(nLxmDebutInclus,nLxmFinExclue,bVoir,/**/sLexeme);
		if (nLxmClasse==lcMotCleF)
			if ( !bTdsPresent(cAlexTdS,sLexeme,&nRang) ){
				lxmChN[uLxmIndex].classe=lcInconnU;
				*pnErreurLexicale=eAlexMotClef;
			}else lxmChN[uLxmIndex].valh=nRang;
		//s(sLexeme);
		if (nLxmClasse==lcOperateuR)
			lxmChN[uLxmIndex].valh=uAlexLexeme(sLexeme);
		if (nLxmClasse==lcParenthesE){//apparier les parenthèses ds .valleur
			if (bAlexParentheseur(uLxmIndex,'('))
				uLexemeEmpileR[++ipLexemeEmpileR]=uLxmIndex;
			if (bAlexParentheseur(uLxmIndex,')')) {
				lxmChN[uLxmIndex].valh=uLexemeEmpileR[ipLexemeEmpileR];
				lxmChN[uLexemeEmpileR[ipLexemeEmpileR--]].valh=uLxmIndex;
				//int nEcart=lxmChN[uLxmIndex].valleur-lxmChN[lxmChN[uLxmIndex].valleur].valleur;
				//d(nEcart);
			}
		}
		if (nLxmClasse==lcEntieR && mAlexEntier(uLxmIndex)<0){
			lxmChN[uLxmIndex].classe=lcInconnU;
			*pnErreurLexicale=eAlexEntier;
		}
		if (nLxmClasse==lcFinDeFichieR)
			lxmChN[uLxmIndex].suiv=0;
		if (bVoir)
			printf("\t\t État négatif, donc un nouveau lexème (d'index %d) est empilé: (classe %s, lexie %s).\n",uLxmIndex,sItem(sLexemeClassE,nLxmClasse+1),sG(sLexemE(uLxmIndex)));
	//Appel1("LexemeEmpileR");
}//LexemeEmpileR

void LexemeInsereR(char *sOperateur,int bParentheseurOuvrant,int uPredecesseur,int bVoir,int nLexemeEnTout0,int *pnLexemeEnTout1){//(O(1)
	//insère juste après lxmChN[uPredecesseur] le rlxmVirtuel (sOperateur,bParentheseurOuvrant) et incrémente *pnLexemeEnTout
	//NB: chq insertO par LexemeInsereR() laisse invariant la pile lxmChN[1..nLexemeEnTout0] ORIGINALE,au champ .suiv près,dc…
	//…l'appelant peut y calculer l'empan de chaq opérH mm si LexemeInsereR() insère des lxm: ceux-ci ne créent pas d'effets de bord. 
	Assert2("LexemeInsereR",bCroit(1,uPredecesseur,nLexemeEnTout0),*pnLexemeEnTout1<knLexemeMaX);
	char *sParentheseur=(bParentheseurOuvrant)? sC2("(",sOperateur) : sC2(sOperateur,")");
	if (bVoir) Titrer(sC4("lxmChN[",sEnt(uPredecesseur),"]=",sG(sParentheseur)));
	rLexemE rlxmVirtuel;
	//rlxmVirtuel:=lexème virtuel
		rlxmVirtuel.classe=lcParenthesE;
		rlxmVirtuel.indexdebut=lxmChN[uPredecesseur].indexfin;
		rlxmVirtuel.indexfin=lxmChN[uPredecesseur].indexfin;
		rlxmVirtuel.lign=lxmChN[uPredecesseur].lign;
		rlxmVirtuel.valh=uAlexLexeme(sParentheseur);
		rlxmVirtuel.prio=-1;
		rlxmVirtuel.suiv=lxmChN[uPredecesseur].suiv;
	(*pnLexemeEnTout1)++;
	//insérer rlxmVirtuel en *pnLexemeEnTout:
		lxmChN[*pnLexemeEnTout1]=rlxmVirtuel;
		lxmChN[uPredecesseur].suiv=*pnLexemeEnTout1;
}//LexemeInsereR

void LexemeReordonneR(int bVoir){//(O(N)
	//réordonne les élts de lxmChN selon les index croissants
	int uL,uSuivant;
	rLexemE lxmCopie[1+nLexemeEnTouT];
	if (bVoir)
		for (printf("Avant LexemeReordonneR (%s):\n",sPluriel(nLexemeEnTouT,"lexème")),uL=1;uL<=nLexemeEnTouT;uL++)
			printf("\tLxm n°%2d: %s %s suiv=%d.\n",uL,sG(sLexemE(uL)),sItem(sLexemeClassE,1+lxmChN[uL].classe),lxmChN[uL].suiv);
	for (uSuivant=uL=1;uL<=nLexemeEnTouT;uSuivant=lxmChN[uSuivant].suiv,uL++)
		lxmCopie[uL]=lxmChN[uSuivant];
	for (uL=1;uL<=nLexemeEnTouT;uL++)
		lxmChN[uL]=lxmCopie[uL];
	if (bVoir)
		LexemeVoiR("Après LexemeReordonneR");
}//LexemeReordonneR

void LexemeVoiR(char *sQuoi){
	//affiche les lxm de lxmChN[]; si kbIndenter, l'indentO évolue avec chaq lxm parenthésant.
	const int kbIndenter=	kV;
	const int kbLign	=	kF;
	const int kbPrio	=	kF;
	const int kbSuivan	=	kF;
	const int kbValh	=	kV;
	const int kuTabulation = 5;
	int uLxm,nMarge,tOuvrant;
	for (printf("%s (%s):\n",sQuoi,sPluriel(nLexemeEnTouT,"lexème")),nMarge=0,uLxm=1;uLxm<=nLexemeEnTouT;uLxm++){
		tOuvrant=(lxmChN[uLxm].classe==lcParenthesE) ? ySignePres(sLexemE(uLxm)[0]=='(',-1) : 0;
		nMarge-=(tOuvrant<0)*kbIndenter*kuTabulation;
			printf("   Lexème n°%2d: %s %s %s",uLxm,sE(nMarge),sG(sLexemE(uLxm)),sItem(sLexemeClassE,1+lxmChN[uLxm].classe));
				if (kbLign) printf(" lign=%d",lxmChN[uLxm].lign);
				if (kbPrio) printf(" prio=%d",lxmChN[uLxm].prio);
				if (kbValh) printf(" valh=%d",lxmChN[uLxm].valh);
				if (kbSuivan) printf(" suiv=%d",lxmChN[uLxm].suiv);
			printf(".\n");
		nMarge+=(tOuvrant>0)*kbIndenter*kuTabulation;
	}
}//LexemeVoiR

int nOperateurPrioriteh(int uLxmIndex){
	//retourne le rang1 de la priorité de l'opérateur de rang1 uLxmDeClasseOperateur, ou 0 si la priorité est non définie
	//Assert1("nOperateurPrioriteh",bAlexLexeme(uLxmDeClasseOperateur) && lxmChN[uLxmDeClasseOperateur].classe==lcOperateuR);
	//char cOperateur=sLexemE(uLxmDeClasseOperateur)[0];
	char cOperateur=sLexemE(uLxmIndex)[0];
	int nPrioriteh=0;//priorité non définie
	if (cOperateur=='+' || cOperateur=='-') nPrioriteh=1;//priorité la plus faible
	if (cOperateur=='*' || cOperateur=='/') nPrioriteh=2;
	if (cOperateur=='^') nPrioriteh=3;//priorité la plus forte
	return(nPrioriteh);
}//nOperateurPrioriteh

void OperateurParentheseR(int bVoir){
	//étend lxmChN en délimitant l'empan de chaq opérH binR à l'aide de parenthésH dédiés: "2+3" devient "(+  2  +  3  +)".
	int nAval,nAmont,nInsertion,nPrioriteh,uL,uLxm;
	if (bVoir) Appel0("OperateurParentheseR");
		int nLexemeEnTout0=nLexemeEnTouT;//car chq appel de LexemeInsereR(), li-7, incrémente nLexemeEnTouT
		for (nInsertion=0,uLxm=1;uLxm<nLexemeEnTout0;uLxm++)
			if (lxmChN[uLxm].classe==lcOperateuR && (nPrioriteh=lxmChN[uLxm].prio)>0){//>0 exclut l'opérH "="
				//nAval:=butée aval,ou 0 si échec
					for (nAval=0,uL=uLxm-1;uL>=1 && nAval==0;uL--){
						if (bAlexParentheseur(uL,'(') || lxmChN[uL].classe==lcOperateuR && lxmChN[uL].prio<nPrioriteh)
							nAval=uL;
						if (bAlexParentheseur(uL,')') && lxmChN[uL].valh>0)
							uL=lxmChN[uL].valh;//uL indexe maintenant la '(' appariée à ')' ——elle existe vu valh>0. 
					}
				//nAmont:=butée amont,ou 0 si échec
					for (nAmont=0,uL=uLxm+1;uL<nLexemeEnTouT && nAmont==0;uL++){
						if (bAlexParentheseur(uL,')') || lxmChN[uL].classe==lcOperateuR && lxmChN[uL].prio<=nPrioriteh || lxmChN[uL].classe==lcSeparateuR )
							nAmont=uL-1;
						if (bAlexParentheseur(uL,'(') && lxmChN[uL].valh>0)
							uL=lxmChN[uL].valh;//uL indexe maintenant la ')' appariée à '(' ——elle existe vu valh>0.
					}
				char *sOperateur=sLexemE(uLxm);
				if (bVoir) printf("Opérateur %s, lxm n°%2d, empan [%d..%d].\n",sG(sOperateur),uLxm,nAval+1,nAmont);
				if ( bCroitStrict4(0,nAval,nAmont,nLexemeEnTout0) ){
					LexemeInsereR(sOperateur, k1Ouvrant,nAval,!k1Voir,nLexemeEnTout0,&nLexemeEnTouT);//(O(1)
					LexemeInsereR(sOperateur,!k1Ouvrant,nAmont,!k1Voir,nLexemeEnTout0,&nLexemeEnTouT);//(O(1)
					//if (++nInsertion>1) break;
				};//else insertion non définie, eg pas de lcSeparateuR après une instruction
			}//if
		LexemeReordonneR(bVoir);//(O(N)
	if (bVoir) Appel1("OperateurParentheseR");
}//OperateurParentheseR
