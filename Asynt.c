#include "Kit.h"
#include "Alex.h"
#include "Asynt.h"
#include "Erreur.h"
#include "Tds.h"
enum eRegleOU  {roAlphA,roEtaT,roExpressioN,roInstructioN,roProgrammE,roSuitE,roTermE,roOmegA};
char *sRegleOU="roAlphA,roEtaT,roExpressioN,roInstructioN,roProgrammE,roSuitE,roTermE,roOmegA";
	//Grammaire algébrique LL(k):
		//Programme->Instructions || FinFichier
		//		Instructions->Instruction Separateur Programme
		//Instruction->Acces || Achat || Affichage || Emprunt || Etat || Radiation || Reservation || Restitution || Affectation 
		//		Acces->Entier Suite				  Entier est une durée>0 pr une Interdiction et une date pr une inscription
		//		Achat->Prix Livre				  réel>0 et Livre non encore répertorié
		//		Affichage->"[" Identifiant"]"	  Identifiant en TDS
		//		Emprunt->"<" Livre Nom			  Livre répertorié et Nom en TDS
		//		Etat->"achat" || "stock"		  liste des livres achetés ou liste des livres présents dans la bibliothèque
		//		Reservation->"?" Livre Nom		  Livre répertorié et Nom en TDS
		//		Restitution->">" Livre Nom		  Livre répertorié et Nom en TDS 
/*		//		Radiation->Nom					  Nom en TDS*/
		//		Affectation->Identificateur Expression       Nom en TDS
		//Suite->Interdiction || Inscription
		//		Interdiction->Livre				  Livre répertorié
		//		Inscription->Nom				  Nom hors TDS
		//		Expression->Somme | Produit | Terme
		//		Somme->Terme "+" Expression 
		//		Produit->Terme "*" Expression 
		//		Terme->Entier || Identifiant || ExpressionParenthésée
		//		ExpressionParenthésée -> "(" Expression ")"
		//		Nom->Identificateur 
		//		Identifiant->Identificateur		déjà affecté,dc en TDS 
enum  eGrammaireRegle {grAlpha,grProgramme,grInstructions,grInstruction,grEmprunt,grReservation,grAchat,grRestitution,grRadiation,grAutre,grSuite,grInterdiction,grInscription,grOmega};
char *sGrammaireReglE="grAlpha,grProgramme,grInstructions,grInstruction,grEmprunt,grReservation,grAchat,grRestitution,grRadiation,grAutre,grSuite,grInterdiction,grInscription,grOmega";
enum {eGenererAlphA,eGenererAchaT,eGenererListE,eGenererOmegA};
#define bEclaireR kF
#define kbVoiR kV
int bGenerE=kF;
FILE *fGenerE;//nom du fichier (suffixe .c vital) destiné à recevoir le code généré par le compilateur
int nAchaT;
int bAppeL;
int nAPPEL;//nombre total d'appels associés aux règles terminales de la grammaire,ie bAlexIdentificateur(), etc
int nECHEC;
int bAsyntAmorceR;
int mAsyntAnalyseR;
int nCiblE;
int bkEclaireuR;
int iRegleOU[roOmegA][100];
int nMargE;
int nModeGeneratioN;
char cNoM;
char *sMACHINE="> MACHINE A PILE:";

int bAchaT(int iDebut,int *piFin);
int bAcceS(int iDebut,int *piFin);
int bAffectatioN(int iDebut,int *piFin);
int bAffichagE(int iDebut,int *piFin);
void AppeL0(char *sRoutine,int iDebut);
void AppeL1(char *sRoutine,int iDebut,int iFin);
int bCrochetFermanT(int iDebut,int *piFin);
int bCrochetOuvranT(int iDebut,int *piFin);
int bCalcuL(int iDebut,int *piFin);
int bEmprunT(int iDebut,int *piFin);
int bEntieR(int iDebut,int *piFin);
void ErreR(int eErreurNumero,int iDebut);
void ErrerSouS(int bSucces,int eErreurNumero,int iDebut);
int bExpressioN(int iDebut,int *piFin);
int bExpressionEntreParentheseS(int iDebut,int *piFin);
int bFinFichieR(int iDebut,int *piFin);
void GenerationTermineR();
void GenerE0();
void GenerE1(char *sA);
void GenerE2(char *sA,char *sB);
void GenerE3(char *sA,char *sB,char *sC);
void GenerE4(char *sA,char *sB,char *sC,char *sD);
void GenerE5(char *sA,char *sB,char *sC,char *sD,char *sE);
void GenereR(char *sCodeOp,char *sCommentaire);
void GenererChainE(char *sCodeOp,char *sChaine,char *sCommentaire);
void GenererEnT(char *sCodeOp,int nValeur,char *sCommentaire);
void GenererReeL(char *sCodeOp,float fValeur,char *sCommentaire);
void GenererSTX(char *sCodeOp,char *sChaine,char *sCommentaire);
int bHorairE(int iDebut,int *piFin);//dédié contrôle sémantique
int bIdentifianT(int iDebut,int *piFin);
int bIdentificateuR(int iDebut,int *piFin);
int bInferieurStricT(int iDebut,int *piFin);
int bInscriptioN(int iDebut,int *piFin);
int bInstructioN(int iDebut,int *piFin);
int bInstructionS(int iDebut,int *piFin);
int bInterdictioN(int iDebut,int *piFin);
int bInterrogatioN(int iDebut,int *piFin);
int bLivrE(int iDebut,int *piFin);
int bMotCleF(int iDebut,int nMotClefNumero,int *piFin);
int bNoM(int iDebut,int *piFin);
int bOperateuR(char cOperateur,int iDebut,int *piFin);
int bParentheseFermantE(int iDebut,int *piFin);
int bParentheseOuvrantE(int iDebut,int *piFin);
int bPriX(int iDebut,int *piFin);
int bProduiT(int iDebut,int *piFin);
int bProgrammE(int iDebut,int *piFin);
int bRadiatioN(int iDebut,int *piFin);
int bReeL(int iDebut,int *piFin);
int bReservatioN(int iDebut,int *piFin);
int bRestitutioN(int iDebut,int *piFin);
int bSeparateuR(int iDebut,int *piFin);
int bSommE(int iDebut,int *piFin);
int bSuitE(int iDebut,int *piFin);
int bSuperieurStricT(int iDebut,int *piFin);
int bTermE(int iDebut,int *piFin);
int bTextE(int iDebut,int *piFin);

void TableInitialiseR();
void TableValueR(int nLigne,int nValeur);
void TableVoiR();

int bAcceS(int iDebut,int *piFin){
	//Acces->Entier Suite			  Entier est une durée>0 pr une Interdiction et une date pr une inscription
	int bSucces,iFin,iMilieu;
	AppeL0("bAcceS",iDebut);
		bSucces=bEntieR(iDebut,&iMilieu) && bSuitE(iMilieu,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
	AppeL1("bAcceS",iDebut,*piFin);
	return(bSucces);
}//bAcceS

int bAchaT(int iDebut,int *piFin){
	//Achat->Prix Livre
	int bAjouter,bSucces,iFin,iMilieu,nItem;
	char *sLivre;
	float fPrix;
	AppeL0("bAchaT",iDebut);
		bSucces=bPriX(iDebut,&iMilieu) && bLivrE(iMilieu,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
			sLivre=sAlexChaine(iMilieu);
			//ss("bAchaT",sLivre);
			bAjouter=bTdsAjouter(cNoM,sLivre);
			Assert1("bAchaT",bAjouter);
			if ( bTdsContient(cNoM,sLivre,&nItem) )
				TdsValuer(cNoM,nItem,TdsLivre);//indique que ce livre est disponible.

		}
		if (bSucces && nModeGeneratioN==eGenererAchaT){
			sLivre=sAlexChaine(iMilieu);
			bAjouter=bTdsAjouterValuer(cNoM,sLivre,TdsLivre);
			Assert1("bAchaT",bAjouter);
			if ( bTdsContient(cNoM,sLivre,&nItem) )
				TdsValuer(cNoM,nItem,TdsLivre);//indique que ce livre est disponible.
			fPrix=fAlexReel(iDebut);
			GenererReeL("EMP",fPrix,"achat");
			nAchaT++;
		}
		if (bSucces && nModeGeneratioN==eGenererListE){
			sLivre=sAlexChaine(iMilieu);
			bAjouter=bTdsAjouterValuer(cNoM,sLivre,TdsLivre);
			Assert1("bAchaT",bAjouter);
			if ( bTdsContient(cNoM,sLivre,&nItem) )
				TdsValuer(cNoM,nItem,TdsLivre);//indique que ce livre est disponible.
			fPrix=fAlexReel(iDebut);
			GenererSTX("EMP",sLivre,"achat");
			nAchaT++;
		}
	AppeL1("bAchaT",iDebut,*piFin);
	return(bSucces);
}//bAchaT

int bAffectatioN(int iDebut,int *piFin){
	//Affectation->>Identificateur "=" Expression
	int bSucces,iFin,iX;
	AppeL0("bAffectatioN",iDebut);
		bSucces=bIdentificateuR(iDebut,&iX) && bAlexOperateur(iX,'=') && bExpressioN(iX+1,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
			char *sIdent=sAlexChaine(iDebut);
			int bAjouter=bTdsAjouterValuer(cNoM,sIdent,0);
			Assert1("bAffectatioN",bAjouter);
		}
	AppeL1("bAffectatioN",iDebut,*piFin);
	return(bSucces);
}//bAffectatioN

int bAffichagE(int iDebut,int *piFin){
	//bAffichagE->"[" Identifiant "]"
	int bAjouter,bSucces,iFin,iX,iY,nItem;
	char *sNom;
	AppeL0("bAffichagE",iDebut);
		bSucces=bCrochetOuvranT(iDebut,&iX) && bIdentifianT(iX,&iY) && bCrochetFermanT(iY,&iFin);
		//d(bSucces);
		*piFin=(bSucces)? iFin:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique/**/){
			sNom=sAlexChaine(iDebut+1);
			if ( !bTdsContient(cNoM,sNom,&nItem) )
				ErreR(eSemAffichage,iDebut);
		}
		if (bSucces && mAsyntAnalyseR==mAsyntGeneration/**/){
			sNom=sAlexChaine(iDebut+1);
			bAjouter=bTdsAjouter(cNoM,sNom);
			GenerE5("        printf(\"",sNom,"= %d.\\n\",",sNom,");");
			GenerE0();
		}
	AppeL1("bAffichagE",iDebut,*piFin);
	return(bSucces);
}//bAffichagE

void AppeL0(char *sRoutine,int iDebut){
	if (bAppeL){
		printf("%s n°%d, %s",sTab(++nMargE),iDebut,sRoutine);
		if (bAlexLexeme(iDebut))
			printf(" %s",sG(sAlexChaine(iDebut)));
		Ligne();
		nAPPEL++;
	}
}//AppeL0

void AppeL1(char *sRoutine,int iDebut,int iFin){
	if (bAppeL){
		printf("%s%d…%d,%s\n",sTab(nMargE--),iDebut,iFin-1,sRoutine);
		if (iDebut==iFin) Titrer("ECHEC");
		if (iDebut==iFin) nECHEC++;
	}
}//AppeL1

void AsyntAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
	bkEclaireuR=kF;
	TableInitialiseR();
	if (0) TableVoiR();
	bAsyntAmorceR=kV;
}//AsyntAMORCER

int bAsyntAnalyser(int amMode,int bAvecEclaireur){
	int bAnalyser;
	const int kbDebug= kF;
	int iFin;
	char *sGeneration="des achats,de la liste de livres,céfini";
	char *sGenere="Code.c";
	//Appel0(sC2b("bAsyntAnalyser en mode analyse",sChoix(mAsyntAnalyseR==amMode,"syntaxique","sémantique")));
		bkEclaireuR=bAvecEclaireur;
		mAsyntAnalyseR=amMode;
		nAPPEL=nECHEC=nMargE=0;
		bAppeL=1 && (mAsyntAnalyseR==mAsyntSyntaxique);
		nModeGeneratioN=0;
		if (mAsyntAnalyseR==mAsyntSyntaxique){ 
			Appel0(sC3b("Analyse syntaxique",sChoix(bkEclaireuR,"avec","sans"),"éclaireur"));
				bAnalyser=bProgrammE(1,&iFin) && (nErreurEnTout()==0);
			Appel1(sC3b("Analyse syntaxique",sChoix(bkEclaireuR,"avec","sans"),"éclaireur"));
			if (bAppeL)
				dd(nAPPEL,nECHEC);
		}
		if (mAsyntAnalyseR==mAsyntSemantique){ 
			bAnalyser=bTdsAllouer(kV,&cNoM);
				bAnalyser=bAnalyser && bProgrammE(1,&iFin) && (nErreurEnTout()==0);
				//d(nAPPEL);
				TdsVoir(cNoM,"TDS après analyse sémantique");
			bBof=bTdsAllouer(kF,&cNoM);
		}
		if (mAsyntAnalyseR==mAsyntGeneration){
			Titrer("Génération du code");
			//printf("Indiquer par un chiffre le type de génération demandée (1:achat; 2:liste livres; 0 :annuler): ");
			//scanf("%d",&nModeGeneratioN);
			nModeGeneratioN=1;
			if (bCroit(1,nModeGeneratioN,2)){
				if (kbDebug) printf("Génération %s en cours...\n",sItem(sGeneration,nModeGeneratioN));
					nAchaT=0;
					nCiblE=50;
						bAnalyser=bTdsAllouer(kV,&cNoM);
							fGenerE=fopen(sGenere,"w");/**/
								Assert1("bAsyntAnalyser1",fGenerE!=0);/**/
								GenerE1("#include \"Kit.h\"");/**/
								GenerE0();/**/
								GenerE1("void CodeExecuter(){");/**/
								GenerE0();/**/
									GenerE1("    Appel0(\"CodeExecuter\");");/**/
									GenerE0();/**/
										//TdsVoir(cNoM,"TDS AVANT Generation");
											bAnalyser=bAnalyser && bProgrammE(1,&iFin) && (nErreurEnTout()==0);
										//d(bAnalyser);
										//d(nAPPEL);
										//TdsVoir(cNoM,"TDS après génération du code");
									GenerE1("    Appel1(\"CodeExecuter\");");/**/
									GenerE0();/**/
								GenerE1("}");/**/
								GenerE0();/**/
							iBof=fclose(fGenerE);/**/
						bBof=bTdsAllouer(kF,&cNoM);
					//GenerationTermineR();
				if (kbDebug) printf("Génération %s terminée...\n",sItem(sGeneration,nModeGeneratioN));
			}else printf("La génération du code est annulée conformément à votre demande.\n");
		}
	//Appel1(sC2b("bAsyntAnalyser en mode analyse",sChoix(mAsyntAnalyseR==amMode,"syntaxique","sémantique")));
	return(bAnalyser);
}//bAsyntAnalyser


void AsyntTESTER(int iTest){
	//teste le présent module
	int bAnalyser=kF;
	int iFin;
	Appel0(sC2("AsyntTESTER,test n°",sEnt(iTest)));
		nAPPEL=nECHEC=nMargE=0;
		bkEclaireuR=kV;
		switch (iTest) {
			case  1:	bkEclaireuR=kF;bAnalyser=bProgrammE(1,&iFin);break;
			case  2:	bkEclaireuR=kV;bAnalyser=bProgrammE(1,&iFin);break;
			default:break;
		}
		printf("%s de l'analyse syntaxique après %s %s.\n",(bAnalyser)? "Succès":"Echec",sPluriel(nAPPEL,"appel"),(nECHEC)? sPluriel(nECHEC,"échec"):"");
	Appel1(sC2("AsyntTESTER,test n°",sEnt(iTest)));
}//AsyntTESTER	

int bCalcuL(int iDebut,int *piFin){
	//Calcul->Somme || Produit || Terme || Expression
	int nChoix2,bSucces,iFin;
	AppeL0("bCalcuL",-iDebut);
		if (bkEclaireuR){
			nChoix2=nAlexCalcul(iDebut);//pré-vision instruction courante: 1 si Entier, 2 si Reservation, et 0 si échec.
			if (bEclaireR) tee("iDebut et nChoix2 pr Terme",iDebut,nChoix2);
			switch(nChoix2){
				case  1:	bSucces=bSommE(iDebut,&iFin);break;
				case  2:	bSucces=bProduiT(iDebut,&iFin);break;
				case  3:	bSucces=bTermE(iDebut,&iFin);break;
				case  4:	bSucces=bExpressioN(iDebut,&iFin);break;
				default:	ErreR(eSyntCalcuL,iDebut);break;
			}
		}else bSucces=bSommE(iDebut,&iFin) || bProduiT(iDebut,&iFin) || bTermE(iDebut,&iFin) || bExpressioN(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		//d2(3,*piFin);
		//d(bSucces);
	AppeL1("bCalcuL",iDebut,*piFin);
	return(bSucces);
}//bCalcuL

int nChoiX(int nRegle,int iDebut){
	Assert1("nChoiX",bCroitStrict(roAlphA,nRegle,roOmegA));
	int nChoix=iRegleOU[nRegle][nAlexLexeme(iDebut)];
	//if (nRegle==roExpressioN) d2(iDebut,nAlexLexeme(iDebut));
	return(nChoix);
}

int bCrochetFermanT(int iDebut,int *piFin){
	//sd("bCrochetFermanT",iDebut);
	//s(sAlexChaine(iDebut));
	int bSucces=bAlexParentheseur(iDebut,']');
	*piFin=(bSucces)? iDebut+1:iDebut;
	//sd("bParentheseFermantE",*piFin);
	return(bSucces);
}//bCrochetFermanT

int bCrochetOuvranT(int iDebut,int *piFin){
	int bSucces=bAlexParentheseur(iDebut,'[');
	*piFin=(bSucces)? iDebut+1:iDebut;
	return(bSucces);
}//bCrochetOuvranT

int bDatatioN(int iDebut,int *piFin){
	//Datation->Horaire
	int bSucces,iFin;
	AppeL0("bDatatioN",iDebut);
		bSucces=bReeL(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		//d(bSucces);
	AppeL1("bDatatioN",iDebut,*piFin);
	return(bSucces);
}//bDatatioN

int bEmprunT(int iDebut,int *piFin){
	//Emprunt->"<" Livre Nom
	const int knEmpruntDuree=30;
	int bConnu,bEmprunteurInscrit,iValeur,bSucces,iFin,iMilieu,iSuivant,nItem;
	char *sLivre;
	AppeL0("bEmprunT",iDebut);
		bSucces=bInferieurStricT(iDebut,&iMilieu) && bLivrE(iMilieu,&iSuivant) && bNoM(iSuivant,&iFin);
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){//Livre répertorié et Nom inscrit
			//TdsVoir("avant emprunt");
				sLivre=sAlexChaine(iMilieu);
				bConnu=bTdsPresent(cNoM,sLivre,&iValeur);
				if (bConnu){//répertorié = connu ET disponible
					//sd(sLivre,iValeur);
					if (iValeur==0){
						bEmprunteurInscrit=bTdsContient(cNoM,sAlexChaine(iSuivant),&iBof);
						if (!bEmprunteurInscrit)
							ErreR(eSemNonInscrit,iSuivant);
						else if ( bTdsContient(cNoM,sLivre,&nItem) )
							TdsValuer(cNoM,nItem,knEmpruntDuree);//ie sLivre est emprunté pour une durée de knEmpruntDuree jours maximum.
					} else ErreR(eSemLivrePris,iMilieu);
				}else ErreR(eSemLivreInconnu,iMilieu);
			//TdsVoir("après emprunt");
		}
		*piFin=(bSucces)? iFin:iDebut;
		//d3(iDebut,bSucces,*piFin);
	AppeL1("bEmprunT",iDebut,*piFin);
	return(bSucces);
}//bEmprunT

int bEntieR(int iDebut,int *piFin){
	int bSucces;
	AppeL0("bEntieR",iDebut);
		bSucces=bAlexEntier(iDebut);
		*piFin=(bSucces)? iDebut+1:iDebut;
		//tee("bEntieR debut et fin",iDebut,*piFin);
	AppeL1("bEntieR",iDebut,*piFin);
	return(bSucces);
}//bEntieR

void ErreR(int eErreurNumero,int iDebut){
	//empile  l'erreur eErreurNumero ssi le mode correspondant à eErreurNumero est actif
	if (mAsyntAnalyseR==mAsyntSyntaxique && bCroitStrict(eSynt0,eErreurNumero,eSynt1) )
		ErreurEmpiler(eErreurNumero,iDebut);
	if (mAsyntAnalyseR==mAsyntSemantique && bCroitStrict(eSem0,eErreurNumero,eSem1) )
		ErreurEmpiler(eErreurNumero,iDebut);
}//ErreR

void ErrerSouS(int bSucces,int eErreurNumero,int iDebut){
	if (!bSucces){
		//if (eErreurNumero==eSyntSeparateur) tee("séparateur manque",eErreurNumero,iDebut);
		ErreR(eErreurNumero,iDebut);
	}
}//ErrerSouS

int bEtaT(int iDebut,int *piFin){
	//Etat->"achat" || "stock"  
	int nChoix2,bSucces,iValeur,nItem;
	AppeL0("bTermE",-iDebut);
		if (bkEclaireuR){
			nChoix2=nAlexEtat(iDebut);
			if (0 || bEclaireR) tee("iDebut et nChoix2 pr bEtaT",iDebut,nChoix2);
			switch(nChoix2){
				case  1:	bSucces=bAlexMotClef(iDebut,mcAchat);break;
				case  2:	bSucces=bAlexMotClef(iDebut,mcStock);break;
				default:	ErreR(eSyntEtat,iDebut);break;
			}
		}else bSucces=bAlexMotClef(iDebut,mcAchat) || bAlexMotClef(iDebut,mcStock);
		*piFin=(bSucces)? iDebut+1:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntGeneration && nChoix2==1){//générer la liste des livres achetés
			GenerE1("    Achats:");GenerE0();
			nItem=0;
			while (bTdsSymbole(cNoM,&nItem)){
				char *sChose=sTdsSymbole(cNoM,nItem);
				if (bTdsPresent(cNoM,sChose,&iValeur) && iValeur==TdsLivre)
					GenerE5("        printf(\"",sChose,"= %d.\\n\",",sChose,");");
			}
			GenerE0();
		}
		if (bSucces && mAsyntAnalyseR==mAsyntGeneration && nChoix2==2){//générer la liste des livres en stock
			GenerE1("    Stocks:");GenerE0();
			nItem=0;
			while (bTdsSymbole(cNoM,&nItem)){
				char *sChose=sTdsSymbole(cNoM,nItem);
				if (bTdsPresent(cNoM,sChose,&iValeur) && iValeur==TdsLivre)
					GenerE5("        printf(\"",sChose,"= %d.\\n\",",sChose,");");
			}
			GenerE0();
		}
	AppeL1("bTermE",iDebut,*piFin);
	return(bSucces);
}//bEtaT

int bExpressioN(int iDebut,int *piFin){
	//Expression->Somme || Produit || Terme 
	int nChoix3,bSucces,iFin;
	AppeL0("bExpressioN",iDebut);
		if (bkEclaireuR){
			nChoix3=nChoiX(roExpressioN,iDebut);
			if (bEclaireR) sd("bExpressioN",nChoix3);
			switch(nChoix3){
				case  1:	bSucces=bSommE(iDebut,&iFin);break;
				case  2:	bSucces=bProduiT(iDebut,&iFin);break;
				case  3:	bSucces=bTermE(iDebut,&iFin);break;
				default:	ErreR(eSyntInstruction,iDebut);break;
			}
		}else bSucces=bSommE(iDebut,&iFin) || bProduiT(iDebut,&iFin) || bTermE(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
	AppeL1("bExpressioN",iDebut,*piFin);
	return(bSucces);
}//bExpressioN

int bExpressionEntreParentheseS(int iDebut,int *piFin){
	//ExpressionParenthésée -> "(" Expression ")"
	int bSucces,iX,iY,iFin;
	AppeL0("bExpressionEntreParentheseS",iDebut);
		bSucces=bParentheseOuvrantE(iDebut,&iX) && bExpressioN(iX,&iY) && bParentheseFermantE(iY,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
	AppeL1("bExpressionEntreParentheseS",iDebut,*piFin);
	return(bSucces);
}//bExpressionEntreParentheseS

int bFinFichieR(int iDebut,int *piFin){
	int bSucces;
	AppeL0("bFinFichieR",iDebut);
		bSucces=bAlexFinFichier(iDebut);
		*piFin=(bSucces)? iDebut+1:iDebut;
		//sd("bFinFichieR",iDebut);
	AppeL1("bFinFichieR",iDebut,*piFin);
	return(bSucces);
}//bFinFichieR

void GenerationTermineR(){
	if (nModeGeneratioN==1){
		for (int nAchat=nAchaT-1;nAchat>0;nAchat--)
			GenereR("ADD","calculer achat");
		GenererEnT("EMP",nCiblE,"");
		GenereR("STO","");
	}
	if (nModeGeneratioN==2){
		GenererEnT("EMP",nCiblE,"");
		GenereR("STO","");
	}
}//GenerationTermineR

void GenerE0(){
	printf("\n");
	if (bGenerE)
		fprintf(fGenerE,"\n");
}//GenerE0

void GenerE1(char *sA){
	printf("%s ",sA);
	if (bGenerE)
		fprintf(fGenerE,"%s ",sA);
}//GenerE1

void GenerE2(char *sA,char *sB){
	printf("%s %s ",sA,sB);
	if (bGenerE)
		fprintf(fGenerE,"%s %s ",sA,sB);
}//GenerE2

void GenerE3(char *sA,char *sB,char *sC){
	printf("%s %s %s ",sA,sB,sC);
	if (bGenerE)
		fprintf(fGenerE,"%s %s %s ",sA,sB,sC);
}//GenerE3

void GenerE4(char *sA,char *sB,char *sC,char *sD){
	printf("%s %s %s %s ",sA,sB,sC,sD);
	if (bGenerE)
		fprintf(fGenerE,"%s %s %s %s ",sA,sB,sC,sD);
}//GenerE4

void GenerE5(char *sA,char *sB,char *sC,char *sD,char *sE){
	printf("%s %s %s %s %s ",sA,sB,sC,sD,sE);
	if (bGenerE)
		fprintf(fGenerE,"%s %s %s %s %s ",sA,sB,sC,sD,sE);
}//GenerE5

void GenereR(char *sCodeOp,char *sCommentaire){
	printf("\t%s%9s%7s    ; %s\n",sMACHINE,sCodeOp," ",sCommentaire);
}//GenereR

void GenererChainE(char *sCodeOp,char *sChaine,char *sCommentaire){
	printf("\t%s%9s%7s    ; %s\n",sMACHINE,sCodeOp,sChaine,sCommentaire);
}//GenererChainE

void GenererEnT(char *sCodeOp,int nValeur,char *sCommentaire){
	printf("\t%s%9s%7d    ; %s\n",sMACHINE,sCodeOp,nValeur,sCommentaire);
}//GenererEnT

void GenererReeL(char *sCodeOp,float fValeur,char *sCommentaire){
	printf("\t%s%9s%7.2f    ; %s\n",sMACHINE,sCodeOp,fValeur,sCommentaire);
}//GenererReeL

void GenererSTX(char *sCodeOp,char *sChaine,char *sCommentaire){
	//empile STX après l'opérande 1 (adresse nCiblE), lui-même après l'opérande 2 (sChaine,tranche par tranche;la plus extrême a au moins un cButoir).
	int nCar,nTranche;
	char sQuad[1+4],cButoir='$';//cButoir='\0'
	int nTrancheEnTout=1+yArrondi(0.5+nChaineLg(sChaine))/4.0;
	//d(nTrancheEnTout);
	//opérande 2 à empiler en premier
		for (sQuad[4]='\0',nTranche=nTrancheEnTout-1;nTranche>=0;nTranche--){
			for (nCar=0;nCar<4;nCar++)
				sQuad[nCar]=(nTranche*4+nCar<nChaineLg(sChaine))? sChaine[nTranche*4+nCar] : cButoir;
			Assert1("GenererSTX",nTranche<nTrancheEnTout-1 || sQuad[3]==cButoir);
			printf("\t%s%9s%7s    ; %s\n",sMACHINE,sCodeOp,sQuad,sCommentaire);
		}
	//opérande 1 à empiler en second
		GenererEnT(sCodeOp,nCiblE,"");
	//code opération 1 à empiler en dernier
		GenereR("STX","");
	//actualiser nCiblE pour qu'il pointe sur un nouvel espace mémoire vierge, utilisable par exemple pour un autre STX
		nCiblE+=nTrancheEnTout*4;
}//GenererSTX

int bHorairE(int iDebut,int *piFin){
	int bSucces;
	AppeL0("bHorairE",iDebut);
		bSucces=bAlexReel(iDebut);
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
			if (!bAlexHoraire(iDebut))
				ErreR(eSemHoraire,iDebut);
		}
		*piFin=(bSucces)? iDebut+1:iDebut;
	AppeL1("bHorairE",iDebut,*piFin);
	return(bSucces);
}//bHoraire

int bIdentifianT(int iDebut,int *piFin){
	//Identifiant->Identificateur
	int bSucces,iFin,nItem;
	char *sNom;
	AppeL0("bIdentifianT",iDebut);
		bSucces=bIdentificateuR(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
			sNom=sAlexChaine(iDebut);//nom de la personne qui s'inscrit
			if (!bTdsContient(cNoM,sNom,&nItem))
				ErreR(eSemIdentifiant,iDebut);
			//d(nItem);
		}
	AppeL1("bIdentifianT",iDebut,*piFin);
	return(bSucces);
}//bIdentifianT

int bIdentificateuR(int iDebut,int *piFin){
	int bSucces;
	AppeL0("bIdentificateuR",iDebut);
		bSucces=bAlexIdentificateur(iDebut);
		*piFin=(bSucces)? iDebut+1:iDebut;
		//sd("bIdentificateuR",iDebut);
	AppeL1("bIdentificateuR",iDebut,*piFin);
	return(bSucces);
}//bIdentificateuR

int bInferieurStricT(int iDebut,int *piFin){
	int bSucces;
	AppeL0("bInferieurStricT",iDebut);
		bSucces=bAlexOperateur(iDebut,'<');
		*piFin=(bSucces)? iDebut+1:iDebut;
		//sd("bInferieurStricT",iDebut);
	AppeL1("bInferieurStricT",iDebut,*piFin);
	return(bSucces);
}//bInferieurStricT

int bInscriptioN(int iDebut,int *piFin){
	//Inscription->Nom
	int bAjouter,nDate,bSucces,iFin,nItem;
	char *sNom;
	AppeL0("bInscriptioN",iDebut);
		bSucces=bNoM(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
			sNom=sAlexChaine(iDebut);//nom de la personne qui s'inscrit
			nDate=mAlexEntier(iDebut-1);//date d'inscription
			bAjouter=bTdsAjouter(cNoM,sNom);
			if (!bAjouter)//puisque la TDS ne déborde pas,il n'y a qu'une explication:le…
				ErreR(eSemInscrit,iDebut);//…sNom en question est déjà en TDS,donc la personne est déjà inscrite
			else if (bTdsContient(cNoM,sNom,&nItem))
				TdsValuer(cNoM,nItem,mAlexEntier(iDebut-1));
			if (!bAlexDate(iDebut-1))
				ErreR(eSemDate,iDebut-1);
			//d(nItem);
		}
		//sd("bInscriptioN",iDebut);
	AppeL1("bInscriptioN",iDebut,*piFin);
	return(bSucces);
}//bInscriptioN

int bInstructioN(int iDebut,int *piFin){
	//Instruction->Acces || Achat || Affichage || Emprunt || Etat || Radiation || Reservation || Restitution || Affectation 
	int nChoix9,iFin=0,bSucces=kF;
	AppeL0("bInstructioN",iDebut);
		Assert1("bInstructioN0",iDebut>0);
		if (bkEclaireuR){
			nChoix9=nChoiX(roInstructioN,iDebut);
			if (bEclaireR) sd("bInstruction",nChoix9);
			switch(nChoix9){
				case  1:	bSucces=bAcceS(iDebut,&iFin);break;
				case  2:	bSucces=bAchaT(iDebut,&iFin);break;
				case  3:	bSucces=bAffichagE(iDebut,&iFin);break;
				case  4:	bSucces=bEmprunT(iDebut,&iFin);break;
				case  5:	bSucces=bEtaT(iDebut,&iFin);break;
				//case  6:	bSucces=bRadiatioN(iDebut,&iFin);break;
				case  7:	bSucces=bReservatioN(iDebut,&iFin);break;
				case  8:	bSucces=bRestitutioN(iDebut,&iFin);break;
				case  9:	bSucces=bAffectatioN(iDebut,&iFin);break;
				default:	ErreR(eSyntInstruction,iDebut);break;
			}
		}else bSucces=bAcceS(iDebut,&iFin) || bAchaT(iDebut,&iFin) || bAffichagE(iDebut,&iFin) || bEmprunT(iDebut,&iFin) 
			|| bEtaT(iDebut,&iFin) || bReservatioN(iDebut,&iFin) || bRestitutioN(iDebut,&iFin) || bAffectatioN(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		Assert1("bInstructioN1",*piFin>0);
	AppeL1("bInstructioN",iDebut,*piFin);
	return(bSucces);
}//bInstructioN

int bInstructionS(int iDebut,int *piFin){
	//Instructions->Instruction Separateur Programme
	int bSucces,iFin,iMilieu,iSuivant;
	AppeL0("bInstructionS",iDebut);
		bSucces=bInstructioN(iDebut,&iMilieu) && bSeparateuR(iMilieu,&iSuivant) && bProgrammE(iSuivant,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
	AppeL1("bInstructionS",iDebut,*piFin);
	return(bSucces);
}//bInstructionS

int bInterdictioN(int iDebut,int *piFin){
	//Interdiction->Livre
	int nDuree,bSucces,iFin,nItem;
	char *sLivre;
	AppeL0("bInterdictioN",iDebut);
		bSucces=bLivrE(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		//sd("bInterdictioN",iDebut);
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
			sLivre=sAlexChaine(iDebut);
			nDuree=mAlexEntier(iDebut-1);//durée en jours de l'interdiction (pour cause de réparation ou autre) de l'accès au livre
			if (nDuree>=100)
				ErreR(eSemDelaiTropLong,iDebut);
			else if (bTdsContient(cNoM,sLivre,&nItem))
				TdsValuer(cNoM,nItem,nDuree);
			else ErreR(eSemLivreInconnu,iDebut);
			//d(nItem);
			TdsVoir(cNoM,"après interdiction");
		}
	AppeL1("bInterdictioN",iDebut,*piFin);
	return(bSucces);
}//bInterdictioN

int bInterrogatioN(int iDebut,int *piFin){
	int bSucces;
	AppeL0("bInterrogatioN",iDebut);
		bSucces=bAlexOperateur(iDebut,'?');
		*piFin=(bSucces)? iDebut+1:iDebut;
		//sd("bInterrogatioN",iDebut);
	AppeL1("bInterrogatioN",iDebut,*piFin);
	return(bSucces);
}//bInterrogatioN

int bLivrE(int iDebut,int *piFin){
	//Livre->Texte
	int bSucces,iFin;
	AppeL0("bLivrE",iDebut);
		bSucces=bTextE(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		ErrerSouS(bSucces,eSyntLivre,iDebut);
	AppeL1("bLivrE",iDebut,*piFin);
	return(bSucces);
}//bLivrE

int bMotCleF(int iDebut,int nMotClefNumero,int *piFin){
	//MotCleF -> motclef n°nMotClefNumero
	int bSucces;
	AppeL0("bMotCleF",iDebut);
		bSucces=bAlexMotClef(iDebut,nMotClefNumero);
		*piFin=(bSucces)? iDebut+1 : iDebut;
	AppeL1("bMotCleF",iDebut,*piFin);
	return(bSucces);
}//bMotCleF

int bNoM(int iDebut,int *piFin){
	//Nom->Identificateur
	int bSucces,iFin;
	AppeL0("bNoM",iDebut);
		bSucces=bIdentificateuR(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		if (mAsyntAnalyseR==mAsyntSemantique)
			ErrerSouS(bSucces,eSyntNom,iDebut);
	AppeL1("bNoM",iDebut,*piFin);
	return(bSucces);
}//bNoM

int bOperateuR(char cOperateur,int iDebut,int *piFin){
	//Operateur->cOperateur
	int bSucces;
	AppeL0("bOperateuR",iDebut);
		bSucces=bAlexOperateur(iDebut,cOperateur);
		*piFin=(bSucces)? iDebut+1:iDebut;
	AppeL1("bOperateuR",iDebut,*piFin);
	return(bSucces);
}//bOperateuR

int bParentheseFermantE(int iDebut,int *piFin){
	//sd("bParentheseFermantE",iDebut);
	//s(sAlexChaine(iDebut));
	int bSucces=bAlexParentheseur(iDebut,')');
	*piFin=(bSucces)? iDebut+1:iDebut;
	//sd("bParentheseFermantE",*piFin);
	return(bSucces);
}//bParentheseFermantE

int bParentheseOuvrantE(int iDebut,int *piFin){
	int bSucces=bAlexParentheseur(iDebut,'(');
	*piFin=(bSucces)? iDebut+1:iDebut;
	return(bSucces);
}//bParentheseOuvrantE

int bPriX(int iDebut,int *piFin){
	//Prix->Reel
	int bSucces,iFin;
	AppeL0("bPriX",iDebut);
		bSucces=bReeL(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique && fAlexReel(iDebut)<=0.0)
			ErreR(eSemPrix,iDebut);
	AppeL1("bPriX",iDebut,*piFin);
	return(bSucces);
}//bPriX

int bProduiT(int iDebut,int *piFin){
	//Produit-> Terme "*" Expression  
	int bSucces,iFin,iX;
	AppeL0("bProduiT",iDebut);
		bSucces=bTermE(iDebut,&iX) && bAlexOperateur(iX,'*') && bExpressioN(iX+1,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		//d(bSucces);
	AppeL1("bProduiT",iDebut,*piFin);
	return(bSucces);
}//bProduiT

int bProduitOuTermE(int iDebut,int *piFin){
	//ProduitOuTerme -> Produit | Terme 
	int nChoix2,bSucces,iFin;
	AppeL0("bProduitOuTermE",iDebut);
		if (bkEclaireuR){
			nChoix2=nAlexProduitOuTerme(iDebut);
			if (bEclaireR) sd("bProduitOuTermE",nChoix2);
			switch(nChoix2){
				case 1:	bSucces=bProduiT(iDebut,&iFin);break;
				case 2:	bSucces=bTermE(iDebut,&iFin);break;
				default:ErreR(eSyntProgramme,iDebut);break;
			};
		}else bSucces=bProduiT(iDebut,&iFin) || bTermE(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
	AppeL1("bProduitOuTermE",iDebut,*piFin);
	return(bSucces);
}//bProduitOuTermE

int bProgrammE(int iDebut,int *piFin){
	//Programme->Instructions || FinFichier
	int bSucces,iFin,nChoix2;
	AppeL0("bProgrammE",-iDebut);
		//sd("bProgrammE:iDebut",iDebut);
		if (bkEclaireuR){
			nChoix2=nChoiX(roProgrammE,iDebut);
			if (bEclaireR) sd("bProgrammE",nChoix2);
			switch(nChoix2){
				case 1:	bSucces=bInstructionS(iDebut,&iFin);break;
				case 2:	bSucces=bFinFichieR(iDebut,&iFin);break;
				default:ErreR(eSyntProgramme,iDebut);break;
			};
		}else bSucces=bInstructionS(iDebut,&iFin) || bFinFichieR(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		//d4(77,iDebut,bSucces,*piFin);
	AppeL1("bProgrammE",iDebut,*piFin);
	return(bSucces);
}//bProgrammE

int bRadiatioN(int iDebut,int *piFin){
	//Radiation->Nom
	int bSucces,iFin,nItem;
	char *sNom;
	AppeL0("bRadiatioN",iDebut);
		bSucces=bNoM(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
			//TdsVoir("avant radiation");
			sNom=sAlexChaine(iDebut);
			if (bTdsContient(cNoM,sNom,&nItem))
				TdsValuer(cNoM,nItem,0);
			else ErreR(eSemNonInscrit,iDebut);
			//TdsVoir("après radiation");
		}
	AppeL1("bRadiatioN",iDebut,*piFin);
	return(bSucces);
}//bRadiatioN

int bReeL(int iDebut,int *piFin){
	int bSucces;
	AppeL0("bReeL",iDebut);
	bSucces=bAlexReel(iDebut);
	*piFin=(bSucces)? iDebut+1:iDebut;
	//sd("bReeL",iDebut);
	AppeL1("bReeL",iDebut,*piFin);
	return(bSucces);
}//bReeL

int bReservatioN(int iDebut,int *piFin){
	//Reservation->"?" Livre Nom
	int bDefini1,bDefini2,bSucces,iFin,iMilieu,iSuivant,nValeur,nItem1,nItem2;
	char *sLivre,*sNom;
	AppeL0("bReservatioN",iDebut);
		bSucces=bInterrogatioN(iDebut,&iMilieu) && bLivrE(iMilieu,&iSuivant) && bNoM(iSuivant,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
			//TdsVoir("avant réservation");
			sLivre=sAlexChaine(iSuivant);
			bDefini1=bTdsContient(cNoM,sLivre,&nItem1);
			if (!bDefini1)
				ErreR(eSemLivreInconnu,iDebut);
			else if ( bTdsPresent(cNoM,sLivre,&nValeur) )
					if (nValeur==0)
						ErreR(eSemLivreDispo,iDebut);
					else TdsValuer(cNoM,nItem1,0);
			sNom=sAlexChaine(iSuivant);
			bDefini2=bTdsContient(cNoM,sNom,&nItem2);
			if (!bDefini2)
				ErreR(eSemNonInscrit,iDebut);
			//TdsVoir("après réservation");
		}
	AppeL1("bReservatioN",iDebut,*piFin);
	return(bSucces);
}//bReservatioN

int bRestitutioN(int iDebut,int *piFin){
	//Restitution->">" Livre Nom
	int bDefini1,bDefini2,bSucces,iFin,iMilieu,iSuivant,nItem1,nItem2;
	char *sNom,*sLivre;
	AppeL0("bRestitutioN",iDebut);
		bSucces=bSuperieurStricT(iDebut,&iMilieu) && bLivrE(iMilieu,&iSuivant) && bNoM(iSuivant,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
			//TdsVoir("avant restitution");
			sLivre=sAlexChaine(iMilieu);
			bDefini1=bTdsContient(cNoM,sLivre,&nItem1);
			if (!bDefini1)
				ErreR(eSemLivreInconnu,iDebut);
			else TdsValuer(cNoM,nItem1,0);
			sNom=sAlexChaine(iSuivant);
			bDefini2=bTdsContient(cNoM,sNom,&nItem2);
			if (!bDefini2)
				ErreR(eSemNonInscrit,iDebut);
			//TdsVoir("après restitution");
		}
	AppeL1("bRestitutioN",iDebut,*piFin);
	return(bSucces);
}//bRestitutioN

int bSeparateuR(int iDebut,int *piFin){
	int bSucces;
	AppeL0("bSeparateuR",iDebut);
		bSucces=bAlexSeparateur(iDebut);
		*piFin=(bSucces)? iDebut+1:iDebut;
		ErrerSouS(bSucces,eSyntSeparateur,iDebut);
	AppeL1("bSeparateuR",iDebut,*piFin);
	return(bSucces);
}//bSeparateuR

int bSommE(int iDebut,int *piFin){
	//Somme -> "(+" Terme "+" Expression "+)" 
	int bSucces,iFinMoins1,iX;
	AppeL0("bSommE",iDebut);
		bSucces=bAlexOuvrant(iDebut,'+') && bTermE(iDebut+1,&iX) && bAlexOperateur(iX,'+') && bExpressioN(iX+1,&iFinMoins1) && bAlexFermant(iFinMoins1,'+');
		*piFin=(bSucces)? iFinMoins1+1:iDebut;
	AppeL1("bSommE",iDebut,*piFin);
	return(bSucces);
}//bSommE

int bSuitE(int iDebut,int *piFin){
	//Suite->Interdiction || Inscription
	int bSucces=kF,iFin=0,nChoix2;
	AppeL0("bSuitE",-iDebut);
		if (bkEclaireuR){
			nChoix2=nAlexSuite(iDebut);//pré-vision instruction courante: 1 si Interdiction, 2 si Inscription, et 0 si échec.
			if (bEclaireR) tee("iDebut et nChoix2 pr bSuitE",iDebut,nChoix2);
			switch(nChoix2){
				case 1:	bSucces=bInterdictioN(iDebut,&iFin);break;
				case 2:	bSucces=bInscriptioN(iDebut,&iFin);break;
				default:ErreR(eSyntSuite,iDebut);break;
			};
		}else bSucces=bInterdictioN(iDebut,&iFin) || bInscriptioN(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		Assert1("bSuitE1",*piFin>0);
		//sd("bSuitE",iDebut);
	AppeL1("bSuitE",iDebut,*piFin);
	return(bSucces);
}//bSuitE

int bSuperieurStricT(int iDebut,int *piFin){
	int bSucces;
	AppeL0("bSuperieurStricT",iDebut);
	bSucces=bAlexOperateur(iDebut,'>');
	*piFin=(bSucces)? iDebut+1:iDebut;
	//sd("bSuperieurStricT",iDebut);
	AppeL1("bSuperieurStricT",iDebut,*piFin);
	return(bSucces);
}//bSuperieurStricT

int bTermE(int iDebut,int *piFin){
	//Terme->Entier || Identifiant || ExpressionParenthésée  
	int nChoix3,bSucces,iFin;
	AppeL0("bTermE",-iDebut);
		if (bkEclaireuR){
			nChoix3=nChoiX(roTermE,iDebut);
			if (bEclaireR) sd("bTermE",nChoix3);
			switch(nChoix3){
				case  1:	bSucces=bEntieR(iDebut,&iFin);break;
				case  2:	bSucces=bIdentifianT(iDebut,&iFin);break;
				case  3:	bSucces=bExpressionEntreParentheseS(iDebut,&iFin);break;
				default:	ErreR(eSyntTerme,iDebut);break;
			}
		}else bSucces=bEntieR(iDebut,&iFin) || bIdentifianT(iDebut,&iFin) || bExpressionEntreParentheseS(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		//d(bSucces);
	AppeL1("bTermE",iDebut,*piFin);
	return(bSucces);
}//bTermE

int bTextE(int iDebut,int *piFin){
	//Texte->lexème
	int bSucces;
	AppeL0("bTextE",iDebut);
	bSucces=bAlexTexte(iDebut);
	*piFin=(bSucces)? iDebut+1:iDebut;
	//sd("bTextE",iDebut);
	AppeL1("bTextE",iDebut,*piFin);
	return(bSucces);
}//bTextE

void TableInitialiseR(){
	//iRegleOU[RegleOu][TypeDeLxm]:= rg1 du mbre droit de la RegleOu à analyser au vu du 1er lxm de pré-vision TypeDeLxm, ou 0 sinon. 
	int bVoir=0;
	if (bVoir) Appel0("TableInitialiseR");
		for (int uL=roAlphA+1;uL<=roOmegA-1;uL++)
			TableValueR(uL,0);
		//Expression->Somme | Produit | Terme
			TableValueR(roExpressioN,3);
			//d(uAlexLexeme("(+"));
			iRegleOU[roExpressioN][uAlexLexeme("(+")]=1;
			iRegleOU[roExpressioN][uAlexLexeme("(*")]=2;
		//Instruction->Acces || Achat || Affichage || Emprunt || Etat || Radiation || Reservation || Restitution || Affectation 
			TableValueR(roInstructioN,3);
			iRegleOU[roInstructioN][nAlexOffset(1)+lcIdentificateuR]=9;
		//Programme->Instructions || FinFichier
			TableValueR(roProgrammE,1);
			iRegleOU[roProgrammE][nAlexOffset(1)+lcFinDeFichieR]=2;
		//Terme->Entier || Identifiant || ExpressionParenthésée  
			//TableValueR(roTermE,1);
			//d(nAlexOffset(1)+lcEntieR);
			iRegleOU[roTermE][nAlexOffset(1)+lcEntieR]=1;
			iRegleOU[roTermE][nAlexOffset(1)+lcIdentificateuR]=2;
			iRegleOU[roTermE][uAlexLexeme("(")]=3;
 	if (bVoir) Appel1("TableInitialiseR");
}//TableInitialiseR

void TableValueR(int nLigne,int nValeur){
	for (int uC=1;uC<=nAlexOffset(0);uC++)
		iRegleOU[nLigne][uC]=nValeur;
}//TableValueR

void TableVoiR(){
	const int kuFois=5;//nb de lignes en haut de la table csacré au libellé du type de lexème
	const int kuRegleLg=15;//nb de caractR en marge gauche csacré au libellé de la règle OU
	const int kuCarat=3;//nb de caractR par case
	int uC,uL,nFois;
	//for (int uL=1;uL<=nAlexOffset(0);uL++) ds(uL,sG(sAlexLxm(uL)));
	for (Titrer("Table FIRST"),nFois=0;nFois<kuFois;nFois++)
		for (printf("%s",sE(kuRegleLg)),uC=1;uC<=nAlexOffset(0) || !bLigne();uC++)
			printf("%s",sC2(sE(kuCarat-1),sC0(sAlexLxm(uC)[nFois])));
	for (printf("%s",sE(kuRegleLg)),uC=1;uC<=nAlexOffset(0) || !bLigne();uC++)
			printf("%3d",uC);
	for (uL=roAlphA+1;uL<=roOmegA-1;uL++)
		for (printf("%s",sChaine0(sChainon1(sItem(sRegleOU,uL+1),2),kuRegleLg)),uC=1;uC<=nAlexOffset(0) || !bLigne();uC++)
			printf("%s",(iRegleOU[uL][uC])? sEnt2(iRegleOU[uL][uC],kuCarat) : sC2(sE(kuCarat-1),"."));
	Titrer("fin de la table FIRST");
}//TableVoiR

