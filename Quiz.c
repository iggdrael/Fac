#include "Kit.h"
#include "Erreur.h"
#include "Graphe.h"
#include "Flot.h"
#include "Couplage.h"
#include "Quiz.h"

int bQuizAmorceR;
enum   eQuizQuestioN {qAlphA,qAcpMaX,qAcpMiN,qBipartI,qCC,qCFC,qCircuiT,qCoulH,qCourT,qCplgMaX,qDenS,qEuleR,qFilE0,qFilE1,qFilE2,qFloT,qHaM0,qHaM1,qLargE,qLonG,qOrdO,qPilE0,qPilE1,qPilE2,qPlanR,qStrucT0,qStrucT1,qStrucT2,qTopO,qOmegA};
char *sQuizQuestioN ="qAlphA,qAcpMaX,qAcpMiN,qBipartI,qCC,qCFC,qCircuiT,qCoulH,qCourT,qCplgMaX,qDenS,qEuleR,qFilE0,qFilE1,qFilE2,qFloT,qHaM0,qHaM1,qLargE,qLonG,qOrdO,qPilE0,qPilE1,qPilE2,qPlanR,qStrucT0,qStrucT1,qStrucT2,qTopO,qOmegA";
const int kuSommetMaX=kuAlphabet+kuAlphabet;

void QuizAfficheR(int uQuestionNumero,char *szQuestion);
void QuizCorrigeR(int uQuiz,graf *pgG,char  *sComplement,int bDigraphe,int sTrappe,int nRenumero,int tDetailler);
int bQuizGrapheR(const char *ksGraphe,const int kbDigraphe,const int knParametre,const char *ksArcParametreh,const char *ksAreteParametreh,const char *kszComplement,graf **ppgG,int *psTrappe);
void QuizRenumerotE(char *sGraphe);
void QuizRenumeroteR(graf *pgG,int sTrappe,int nRenumero);
void QuizRepondrE(const char *ksGrapheArcArete,const char *ksQuestionnaire,int nRenumero);
void SommetEtiqueteR(int nSommet);
int nSommetEtiquettE(int nSommetEnTout,char cSommet);
int bSommetPondereR(const char *ksPonderation,int *psTrappe,graf **ppgG);
void SommetRenommeR(int nSommet,int cListe[]);

void QuizAfficheR(int uQuestionNumero,char *szQuestion){
	//affiche un rappel qui décrit les questions que peut traiter le Quiz.
	int uItem,uItemEnTout=nItem(sQuizQuestioN);
	printf("Question n°%d: %s n'est pas une question valide.\n",uQuestionNumero,sG(szQuestion));
	Titrer2("Rappel sur le type de question que peut traiter le module Quiz",'.');
		printf("Syntaxe attendue: \"-\" si non orienté, puis le paramètre facultatif n dans [0,9], puis une question choisie parmi:\n");
		//lister sQuizQuestioN au sens strict,ie avec la casse originale
			for (printf("\t"),uItem=2;uItem<uItemEnTout || bPrint(".");uItem++)
				printf("%s%s",sItem(sQuizQuestioN,uItem),sEtc(uItem,uItemEnTout-1));
		printf("\tPour qFlot, le débit de certains sommets peut être restreint par ajout de restrictions annoncées par %s, eg %s.\n",sG(":"),sG(":A7D4"));
		printf("\tPour qPlanR, les réductions éventuelles suivies de K5 ou K33 sont séparées par des %s, eg %s, %s.\n",sG(":"),sG(":ABCDE"),sG(":GF:FE:ABCDE"));
		printf("\tPour qHaM0 et qHaM1, l'ajout de %s demande d'afficher les parcours hamiltoniens et les limite à 20.\n",sG(":20"));
		printf("\tUn %s ou un %s après la question demande une réponse détaillée. Le %s ajoute un affichage préalable du graphe.\n",sG("?"),sG("!"),sG("?"));
	Titrer2("Fin du rappel",'.');
}//QuizAfficheR

void QuizAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
	bQuizAmorceR=kV;
}//QuizAMORCER

void QuizCorrigeR(int uQuiz,graf *pgG,char  *sComplement,int bDigraphe,int sTrappe,int nRenumero,int tDetailler){
	//résout uQuiz sur pgG paramétré par sComplement et affiche son résultat.
	int sSource=1;
	const int k1LargeurSinonProfondeur=1;
	int bVoir=0;
	int zdAfficher=k1Afficher+abs(tDetailler);
	int nComplexiteh;
	if (bVoir) Appel0(sC2b("QuizCorrigeR, quiz n°",sEnt(uQuiz)));
		ModeCaractere(1);
			QuizRenumeroteR(pgG,sTrappe,nRenumero);
			Ligne();
			if (tDetailler) Flag(1);
			if (tDetailler>0) GrapheVoir0(sC2(flag,"Graphe généré"),pgG,gpZeta);
				switch (uQuiz) {
					case qAcpMaX:	GrapheCouvrir(pgG,k1Maximal,0,-zdAfficher);break;//Kruskal car Prim déroute si poids<0
					case qAcpMiN:	GrapheCouvrir(pgG,!k1Maximal,0,-zdAfficher);break;//Kruskal car Prim déroute si poids<0
					case qBipartI:	bGrapheBiparti(pgG,zdAfficher);break;
					case qCC:		nGrapheComposanteConnexe("Ce graphe",pgG,zdAfficher);break;
					case qCFC:		nGrapheComposanteFortementConnexe("Ce graphe",pgG,zdAfficher);break;
					case qCircuiT:	bGrapheCircuite(pgG,zdAfficher);break;
					case qCoulH:	nGrapheColorier(pgG,zdAfficher);break;
					case qCourT:	bGrapheCheminerCourt(pgG,sSource,sTrappe,!k1Tas,zdAfficher,&nBof,&nComplexiteh);break;
					case qCplgMaX:	bCouplageOptimiser(pgG,k1Ponderer,k1Maximiser,zdAfficher);	break;
					case qDenS:		fGrapheDensiteh(pgG,bDigraphe,zdAfficher);break;
					case qEuleR:	bGrapheEulerien(pgG,bDigraphe,0,0,k1Afficher);	break;
					case qFilE0:	GrapheExplorer(pgG,k1LargeurSinonProfondeur,0,zdAfficher);	break;
					case qFilE1:	GrapheExplorer(pgG,k1LargeurSinonProfondeur,-1,zdAfficher);	break;
					case qFilE2:	GrapheExplorer(pgG,k1LargeurSinonProfondeur,+1,zdAfficher);	break;
					case qFloT:		FlotMaxCalculer(pgG,sSource,sTrappe,zdAfficher);	break;
					case qHaM0:		nGrapheHamiltonien(pgG,bDigraphe,k1Circulaire,iEntier(sComplement));	break;
					case qHaM1:		nGrapheHamiltonien(pgG,bDigraphe,!k1Circulaire,iEntier(sComplement));break;
					case qLargE:	bGrapheCheminerAuLarge(pgG,sSource,sTrappe,zdAfficher);	break;
					case qLonG:		bGrapheCheminerLong(pgG,sSource,sTrappe,zdAfficher,&nComplexiteh);	break;
					case qOrdO:		bGrapheOrdonnancer(pgG,!k1Strict,zdAfficher);	break;
					case qPilE0:	GrapheExplorer(pgG,!k1LargeurSinonProfondeur,0,zdAfficher);	break;
					case qPilE1:	GrapheExplorer(pgG,!k1LargeurSinonProfondeur,-1,zdAfficher);	break;
					case qPilE2:	GrapheExplorer(pgG,!k1LargeurSinonProfondeur,+1,zdAfficher);	break;
					case qPlanR:	bGrapheNonPlanaire(pgG,sComplement,k1Afficher);	break;
					case qStrucT0:	GrapheScruter("\tGraphe direct",pgG,+1,abs(tDetailler));break;
					case qStrucT1:	GrapheScruter("\tGraphe inverse",pgG,-1,abs(tDetailler));break;
					case qStrucT2:	GrapheScruter("\tGraphes direct et inverse",pgG,0,abs(tDetailler));break;
					case qTopO:		bGrapheTrierTopologiquement(pgG,zdAfficher);	break;
					default:		Assert1("QuizCorrigeR default",0);break;
				}
			QuizRenumeroteR(pgG,sTrappe,0);
			if (tDetailler) Flag(0);
		ModeCaractere(0);
	if (bVoir) Appel1(sC2b("QuizCorrigeR, quiz n°",sEnt(uQuiz)));
}//QuizCorrigeR

int bArcEnTroP(graf *pgG,const int ksOrigine,const int ksDestination,const char *ksArcParametreh,const char *ksAreteParametreh){
	//vrai ssi (sOrigine,sDestination) décrit un arc de sArcParametreh ou de sAreteParametreh
	const int kbVoir=1;
	int bEnTrop=0;
	//Appel0("bArcEnTroP");
		if (nChaineLg(ksArcParametreh)==2){
			int sX=nLettre(ksArcParametreh[0]);
			int sY=nLettre(ksArcParametreh[1]);
			bEnTrop=bEnTrop || (ksOrigine==sX && ksDestination==sY);
		}
		if (nChaineLg(ksAreteParametreh)==2){
			int sX=nLettre(ksArcParametreh[0]);
			int sY=nLettre(ksArcParametreh[1]);
			bEnTrop=bEnTrop || (ksOrigine==sX && ksDestination==sY) || (ksOrigine==sY && ksDestination==sX);
		}
		if (kbVoir && bEnTrop) Titrer("bEnTrop");
		if (kbVoir && bEnTrop) ss(ksArcParametreh,ksAreteParametreh);
		if (kbVoir && bEnTrop) d3(ksOrigine,ksDestination,bEnTrop);
	//Appel1("bArcEnTroP");
	return(bEnTrop);
}//bArcEnTroP

int bQuizGrapheR(const char *ksGraphe,const int kbDigraphe,const int knParametre,const char *ksArcParametreh,const char *ksAreteParametreh,const char *kszComplement,graf **ppgG,int *psTrappe){
	//alloue et rend le graphe demandé.
	//ksGraphe décrit le graphe générique G(n) décrit par ksGraphe et à transformer en G'(n) ou en G"(n), selon bDigraphe.
	//nParametre est le paramètre n associé au graphe, par exemple "3" dans l'énoncé: "calculer dans G'(3) un flot maximal".
	//sArcParametreh/sAreteParametreh désigne l'arc ou l'arête à retirer si nPoids est nul.
	//szComplement liste les sommets et débits contraints, eg "A9B4" pr limiter à 9 unités le débit de A et à 4 celui de B.
	int bVoir=0;
	int bGrapher=1,aK,sX,sY;
	int bArcEnSus=knParametre>0 && nChaineLg(ksArcParametreh)==2;
	int bAreteEnSus=knParametre>0 && nChaineLg(ksAreteParametreh)==2;
	int nBase4=2*bAreteEnSus+bArcEnSus;
	char *sGraphe;
	if (bVoir) Appel0("bQuizGrapheR");
		Assert1("QuizGrapheR0",!bModeCaractere());
		char sAreteInverse[1+3];
		if (bAreteEnSus){
			sAreteInverse[0]=ksAreteParametreh[1];
			sAreteInverse[1]=ksAreteParametreh[0];
			Assert1("bQuizGrapheR décit attendu",bCroit(0,knParametre,9));
			sAreteInverse[2]='0'+knParametre;
			sAreteInverse[3]='\0';
		}else sAreteInverse[0]='\0';
		switch (nBase4){
			case 0:	sGraphe=sC1(ksGraphe);break;//G(0,0)
			case 1:	sGraphe=sC2(ksGraphe,sC2(ksArcParametreh,sEnt(knParametre)));break;//G(1,0)
			case 2:	sGraphe=sC3(ksGraphe,sC2(ksAreteParametreh,sEnt(knParametre)),sAreteInverse);break;//G(0,1)
			case 3:	sGraphe=sC4(ksGraphe,sC2(ksArcParametreh,sEnt(knParametre)),sC2(ksAreteParametreh,sEnt(knParametre)),sAreteInverse);break;//G(1,1)
		}
		bGrapher=bGrapheGenerer(sGraphe,gpCouleur,ppgG);//dc orienté pr le moment; sera symétrisé plus bas si non orienté.
if (bVoir) GrapheWoir("QuizGrapheR66",*ppgG);
		if (bGrapher){
			*psTrappe=(*ppgG)->nSommetEnTout;
			//ppgG:=ppgG \ {sArcParametreh,sAreteParametreh} si nParametre=0
				for (aK=(*ppgG)->nArcEnTout;aK>0;aK--)
					if ((*ppgG)->coulh[aK]==0) //arc ou arête paramétrée, mais aussi tout autre arc de poids nul
						if (knParametre==0){//supprimer l'arc en question seult si arc ou arête paramétrée
							GrapheDelimiter(*ppgG,aK,&sX,&sY);
							if (bArcEnTroP(*ppgG,sX,sY,ksArcParametreh,ksAreteParametreh)){
								GrapheDesarquer(*ppgG,sX,sY);//seult arc ou arête paramétrée
							}else (*ppgG)->coulh[aK]=knParametre;
						}else (*ppgG)->coulh[aK]=knParametre;
if (bVoir) GrapheWoir("QuizGrapheR77",*ppgG);
			for (int aK=1;aK<=(*ppgG)->nArcEnTout;aK++)
				(*ppgG)->nCapaMax[aK]=(*ppgG)->nCout[aK]=(*ppgG)->nPoids[aK]=(*ppgG)->coulh[aK];
			if (0 || bVoir) GrapheWoir0("Graphe pondéré généré par QuizGrapheR",*ppgG,gpCapaMax+gpCout);
			ModeCaractere(+1);
				bGrapher=(kszComplement==NULL) || bSommetPondereR(kszComplement,psTrappe,ppgG);
			ModeCaractere(-1);
			if (0) GrapheWoir0("Graphe pondéré généré avec dédoublt par QuizGrapheR",*ppgG,gpCapaMax+gpCout);
			bGrapher=bGrapher && bGrapheSimple(*ppgG);
		};
if (bVoir) GrapheWoir("QuizGrapheR88",*ppgG);

//GrapheWoir0("bQuizGrapheR0 final",*ppgG,gpCapaMax+gpCout);
		if (bGrapher && !kbDigraphe)//cf Graphe.h
			GrapheSymetriser(*ppgG,gpCapaMax+gpCout+gpPoids);
//GrapheWoir0("bQuizGrapheR1 final",*ppgG,gpCapaMax+gpCout);
	if (bVoir) Appel1("bQuizGrapheR");
	return(bGrapher);
}//bQuizGrapheR

void QuizRenumerotE(char *sGraphe){
	//remplace S par A, et T par le rg1 du dernier sommet, en supposant que les sommets sont consécutifs.
	int nC,nSommetEnTout;
	for (nSommetEnTout=nC=0;nC<nChaineLg(sGraphe);nC++)
		if (bLettre(sGraphe[nC]) && nLettre(sGraphe[nC])<nLettre('S') )
			nSommetEnTout=nLettre(sGraphe[nC]);
	Assert1("QuizRenumerotE",nSommetEnTout>0);
	for (nC=0;nC<nChaineLg(sGraphe);nC++){
		if (sGraphe[nC]=='S')
			sGraphe[nC]='A';
		if (sGraphe[nC]=='T')
			sGraphe[nC]='@'+nSommetEnTout+1;
	}
	//ss("QuizRenumerotE",sGraphe);
}//QuizRenumerotE

void QuizRenumeroteR(graf *pgG,int sTrappe,int nRenumero){
	//renumérote les sommets de en les décalant circulairt selon nRenumero, excepté les sommets 1 et sTrappe.
	int bVoir=0;
	const int ksSource=1;
	const int kdIndex0=1+ksSource;
	int cListe[1+kuModeCaractereMax];
	Assert2("QuizRenumeroteR",nRenumero>=0,bCroitStrict(1,pgG->nSommetEnTout,kuModeCaractereMax));
	cListe[0]=kuModeCaractereMax;
	VecteurIndexer(cListe,1,kuModeCaractereMax);
	if (bVoir) Ligne();
	if (bVoir) d(pgG->nSommetEnTout);
	if (bVoir) VecteurVoir("cListe0",cListe,1,pgG->nSommetEnTout);
	if (nRenumero>0){
		for (int dIndex=kdIndex0;dIndex<pgG->nSommetEnTout;dIndex++)
			if (dIndex!=sTrappe)
				cListe[dIndex]=1+uModulo1(dIndex+nRenumero-2,pgG->nSommetEnTout-2);//invariant si nRenumero=1
		cListe[ksSource]=nLettre('S');//A est rebaptisé S
		cListe[sTrappe]=nLettre('T');//le dernier sommmet est rebaptisé T
	}
	if (bVoir) VecteurVoir("cListe1",cListe,1,pgG->nSommetEnTout);
	ModeCaracteriser(cListe);
}//QuizRenumeroteR

void QuizRepondrE(const char *ksGrapheArcArete,const char *ksQuestionnaire,int nRenumero){
	//répond à chq question du ksQuestionnaireconcernant la famille de graphes définie par ksGrapheArcArete.
	int bVoir=0;
	int uQuestionnaireLim=1+nChaineLg(ksQuestionnaire);
	char szComplement[uQuestionnaireLim],szQuestion[uQuestionnaireLim];
	int uGrapheLim=1+nChaineLg(ksGrapheArcArete);
	char sGraphe[uGrapheLim];
	char szArc[1+2],szArete[1+2];
	int tDetailler,bDigraphe,nEntame,nParametre,mPosition,uQ,mQuiz,bSigne,sTrappe,bValide=kV;
	if (bVoir) Appel0("QuizRepondrE");
	printf("Paramètres du quiz:\n\tGraphe{,Arc(n){,Arête(n)}}: %s.\n\tQuestionnaire: %s.\n",sG(ksGrapheArcArete),sG(ksQuestionnaire));
	ErreurDenoncer(bCroit(1,nItem(ksGrapheArcArete),3) && nChaineLg(sItem(ksGrapheArcArete,2))<=2 && nChaineLg(sItem(ksGrapheArcArete,3))<=2,eGrafItem,nChaineLg(ksGrapheArcArete),&bValide);
	if (bValide){
		ChaineCopier0(sItem(ksGrapheArcArete,1),sGraphe);
		QuizRenumerotE(sGraphe);//remplace le cas échéant S par le 1er sommet A et T par le dernier sommet
		ChaineCopier0(sItem(ksGrapheArcArete,2),szArc);//valide vu li-3:"<=2"
		ChaineCopier0(sItem(ksGrapheArcArete,3),szArete);//valide vu li-3:"<=2"
	}
	if (bValide)
		for (uQ=1;uQ<=nItem(ksQuestionnaire) && bValide;uQ++){
			ChaineCopier0(sItem(ksQuestionnaire,uQ),szQuestion);
			tDetailler=0;
			if (szQuestion[nChaineLg(szQuestion)-1]=='?')
				tDetailler=+1;//le "?" termine la question et demande de détailler complètement la réponse
			if (szQuestion[nChaineLg(szQuestion)-1]=='!')
				tDetailler=-1;//le "!" termine la question et demande de détailler partiellement la réponse
			if (tDetailler)//enlever "?" ou "!"
				ChaineCopier0(sChainon0(szQuestion,nChaineLg(szQuestion)-2),szQuestion);
			//szComplement:=complément de la question annoncé par ":", auquel cas ce cplément est à retirer de szQuestion
				mPosition=mChainePos(':',szQuestion);
				if (mPosition>=0){
					ChaineCopier0(sChainon1(szQuestion,mPosition+1),szComplement);
					ChaineCopier0(sChainon0(szQuestion,mPosition-1),szQuestion);
				}else ChaineCopier0(sVide(),szComplement);
				if (bVoir) s(szQuestion);
			bDigraphe=kV;//L'absence de signe vaut pour un digraphe.
			nEntame=nParametre=0;//c'est le paramètre "n" de G(n).
			if (!bLettre(szQuestion[0])){
				bSigne=bDans2(szQuestion[0],'+','-');//spécifie le type de graphe: orienté ("+") par défaut, ou non ("-").
				bDigraphe=szQuestion[0]!='-';
				nEntame+=bSigne;
				if ( bDecit(szQuestion[nEntame]) )
					nParametre=szQuestion[nEntame++]-'0';//décit; c'est le paramètre "n" de G(n).
			};
			if (bValide){
				//mQuiz:=rang de la question (privée de son complément) ds sQuizQuestioN, à la casse près et à "q" près, facultatif:
					char sQuestion[1+nChaineLg(szQuestion)];
					ChaineCopier0(sMajusculer(sChainon1(szQuestion,nEntame)),sQuestion);
					char sQuizMaj[1+nChaineLg(sQuizQuestioN)];
					ChaineCopier0(sMajusculer(sQuizQuestioN),sQuizMaj);
					mQuiz=nItemRang(sC2("Q",sQuestion),sQuizMaj)-1;
					if (mQuiz<0)//échec, provisoire si la question commençait par "q" ou "Q"
						mQuiz=nItemRang(sQuestion,sQuizMaj)-1;
				int bDefini=bCroitStrict(qAlphA,mQuiz,qOmegA);//"const int" pr le paramètre 1 de ErreurDenoncer
				int nLg=nChaineLg(sQuestion);
				//sd3(sQuestion,bDefini,eGrafQuestion,nLg);
				ErreurDenoncer(bDefini,eGrafQuestion,nLg,&bValide);
				if (bValide){
					if ( bDans2(mQuiz,qHaM0,qHaM1) )
						ErreurDenoncer(iEntier(szComplement)>=0,eGrafPositif,nChaineLg(szComplement),&bValide);
					if (bValide){
						printf("Question n°%d sur G%c(%d):",uQ,(bDigraphe)?'\'':'"',abs(nParametre));
						printf(" %s",sG(sC2(sItem(sQuizQuestioN,1+mQuiz),(nChaineLg(szComplement)>0)?sC2(":",szComplement):"")));
						graf *pgG;
						if ( !bQuizGrapheR(sGraphe,bDigraphe,nParametre,szArc,szArete,(mQuiz!=qPlanR)?szComplement:sVide(),&pgG,&sTrappe) ){
							printf("Question n°%d non traitée car la description du graphe est incorrecte.\n",uQ);
							ErreurAfficherTout(sGraphe);
						} else QuizCorrigeR(mQuiz,pgG,szComplement,bDigraphe,sTrappe,nRenumero,tDetailler);
					}else ErreurAfficherTout(szComplement);
				}else QuizAfficheR(uQ,szQuestion);
			}else ErreurAfficherTout(szQuestion);
		}
	else ErreurAfficherTout(ksGrapheArcArete);
	if (bVoir) Appel1("QuizRepondrE");
}//QuizRepondrE

void QuizRepondre(const char *ksGrapheArcArete,const char *ksQuestionnaire){
	int nRenumero;
	QuizRepondrE(ksGrapheArcArete,ksQuestionnaire,nRenumero=0);
}//QuizRepondre

void QuizTESTER(int iTest){
	//teste le présent module
	int bRegler=iTest<0;//pr imprimer la correction sur une seule page
	const int bVoir=1-bRegler;
	int uTest=abs(iTest);
	if (bVoir) Appel0(sC2("QuizTESTER,test n°",sEnt(uTest)));
		if (bRegler) Regler(70);
		Assert1("QuizTESTER",bQuizAmorceR);
			switch (uTest) {
			case  0:	Titrer("Exemple");
						QuizRepondre("AB1AC2AD3AE3BC1BD3BF4CD1CE2DC2DE1EF1FA3","1Pile0,-0PlanR:FE:ABCDE?");
						break;
			case  1:	Titrer("Contrôle continu 2018/1");
						QuizRepondre("AB6AE6AG6BD5CD7DJ3EC8EG8EH8FC4FI4GB3GH3HF4HI4ID7IJ7,BC,EI","CourT?,-AcpMiN?,TopO?,OrdO?,LargE?,FloT:C5?");
						//QuizRepondre("AB6AE6AG6BD5CD7DJ3EC8EG8EH8FC4FI4GB3GH3HF4HI4ID7IJ7,BC,EI","CourT,-AcpMiN,TopO,OrdO,LargE,FloT:C5?,FloT:C5");
						break;
			case  2:	Titrer("Contrôle continu 2018/2");
						QuizRepondre("AB5AC1AE3AG9BC9BE2CD1CF8DJ5EC8EH5FD5FH1FI3FJ1GE8GH8HI4IJ7,BC,EI","CourT,-AcpMiN,TopO,OrdO,LargE,FloT:C5");
						break;
			case  3:	Titrer("Contrôle continu 2019");
						QuizRepondre("AB6AE6AG6BC3BG3CD4CF4DI7DJ7EB3EC5EH5FD4FH4GI5HI8IJ3,AH,HJ","CourT,-AcpMiN,TopO,OrdO,LargE");
						break;
			case  4:	Titrer("Contrôle continu nov 2019");
						char ksQuiz4[]="AB13AE13AH13BC9BF5CD9CJ9CK1DF9DG6DL9EI7FH2FJ2GJ8GK9HI9HG9IJ8JL9KL9,AK,BI";
						QuizRepondre(ksQuiz4,"CoulH,BipartI,CourT,OrdO,TopO,FloT:D7,-Accpm,-CplG,-HaM0,-EuleR");
						break;
			case  5:	Titrer("Contrôle continu déc 2019");
						char ksQuiz5[]="AB7AE8AF5AH8AI9BC7CD7CE6CF9DL9EG9EJ9GF9GH9GK9HL8IJ9JH9JK8KL9DH0FJ0,CD,BE";
						QuizRepondre(ksQuiz5,"CoulH,LargE,OrdO,TopO,FloT,-qAcpMiN,-CplG,-PlanR");
						break;
			case  6:	Titrer("Quizen décembre 2019");
						QuizRepondre("AB9AE8AH9BC9CD9CF1DF0DK5EF0EI9FG0FI1GI9GK9HC9HI9IJ9JK7,CD,BE","4CoulH,4CourT,4OrdO,4TopO");
						break;
			case  7:	Titrer("2de session juin 2020");
						QuizRepondre("AB9AE9AH9BC9CD9CF1DF0DK7EF0EI9FG0FI1GI9GK9HC9HI8IJ9JK7,CD,BE","8CoulH,8CourT,8OrdO,8TopO,8FloT,-8qAcpMiN,8BipartI,-8CplG");
						break;
			case  8:	Titrer("CquoiToutÇa");//ùù
						QuizRepondre("AB9AE9BC6BG5CD6CE7DF6DI6EF8EG8FH6FJ6GH6HI9IJ9,AG,DJ","0qOrdO?,8FloT:D4E7?,-CplG?,-AcpMiN?,-8CoulH!,8CFC,5HAM0:9?,Court!");
						//QuizRepondre("AB9AE9BC6BG5CD6CE7DF6DI6EF8EG8FH6FJ6GH6HI9IJ9AJ256","FloT?");
						break;
			case 12:	Titrer("Coupe minimale");
						QuizRepondre("AB1AC2BC1","0FloT");
						break;
			case 13:	Titrer("K3");
						QuizRepondre("AB1AC2BC1,DA,AC","-2HaM0");
						break;
			case 14:	Titrer("K4");
						//QuizRepondre("AB1AC2AD3BC1BD2CD1","-0qHaM1");
						QuizRepondre("AB1BC2CD3DA4","1CicuiT,4HaM0");
						break;
			case 15:	Titrer("K5");
						QuizRepondre("AB1AC2AD3AE3BC1BD3BE4CD1CE2DE1","-9PlanR:ABCDE");
						break;
			case 17:	Titrer("ksTD2019");
						QuizRepondre("AE9AJ9BD9DE5CE9CF5DG5EH5FG5HG5FI5IJ5IK5IL5JK5JL5KJ5LJ5JM9KM9LM9,BC,EK","8CoulH,8CourT,8TopO,d8OrdO,8FloT,-8qAcpMiN,-8qAcpMaX");
						break;
			case 49:	Titrer("ksExo49");
						QuizRepondre("AB2AD5AE7BC3CD3DE3,AC,CE","7CoulH,7CourT,7TopO,7OrdO,7FloT,-7qAcpMiN,-7qAcpMaX");
						break;
			default:break;
			}
		if (bRegler) Regler(-70);
	if (bVoir) Appel1(sC2("QuizTESTER,test n°",sEnt(uTest)));
}//QuizTESTER

void SommetEtiqueteR(int nSommet){
	int cListe[1+kuSommetMaX];
	SommetRenommeR(nSommet,cListe);
}//SommetEtiqueteR

int nSommetEtiquettE(int nSommetEnTout,char cSommet){
	int uE,nEtiquette=0,cListe[1+kuAlphabet];
	int nSommet=nSommetEnTout;
	SommetRenommeR(nSommet,cListe);
	//sd(sC0(cSommet),nSommetEnTout);
	for (nEtiquette=0,uE=1;uE<=nSommetEnTout;uE++)
		if (cSommet-'@'==cListe[uE])
			nEtiquette=uE;
	Assert1("nSommetEtiquettE",bCroit(1,nEtiquette,kuAlphabet));
	return(nEtiquette);
}//nSommetEtiquettE

int bSommetPondereR(const char *ksPonderation,int *psTrappe,graf **ppgG){
	//dédouble chq sommet cité ds ksPonderation et lui attribue le poids (1 ou plusieurs décits) qui le suit
	int bVoir=0;
	int bPonderer=1,nC,nDedouble,aK,sX,nPoids,bSommetOuDecit,bSommetDistinct,bPremiere;
	int nOccurrence[1+kuSommetMaX];
	Assert1("bSommetPondereR",(*ppgG)->nSommetEnTout<kuSommetMaX);
	if (0) s(ksPonderation);
	//bSommetOuDecit:=ksPonderation ne ctient que des sommets de *ppgG et des décits; en profiter pr cpter les occurrences des sommets.
		VecteurRaz(nOccurrence,kuSommetMaX);
		for (bSommetOuDecit=1,nC=0;nC<nChaineLg(ksPonderation) && bSommetOuDecit;nC++)
			if ( bLettre(ksPonderation[nC]) ) {
				sX=nLettre(ksPonderation[nC]);
				if (bVoir) cc(ksPonderation[nC],ksPonderation[1+nC]);
				bSommetOuDecit=bCroit(1,sX,(*ppgG)->nSommetEnTout) && bDecit(ksPonderation[nC+1]);
				if (bSommetOuDecit)
					nOccurrence[nSommetEtiquettE((*ppgG)->nSommetEnTout,ksPonderation[nC])]++;
				if (bSommetOuDecit)
					nC++;//le décit
			}else bSommetOuDecit=bDecit(ksPonderation[nC]); 
	if (bVoir) b(bSommetOuDecit);
	//bSommetDistinct:=les sommets cités ds ksPonderation et dc nOccurrence[] sont distincts
		bSommetDistinct=iVecteurMax(nOccurrence,1,kuSommetMaX)<=1;
	if (bVoir) bb(bSommetOuDecit,bSommetDistinct);
	bPonderer=bSommetOuDecit && bSommetDistinct;
	int nDedoublt=yVecteurSomme(nOccurrence,1,(*ppgG)->nSommetEnTout);
Tabuler(+1);
	if (bPonderer) for (bPremiere=1,nDedouble=nC=0;nPoids=0,nC<nChaineLg(ksPonderation);nC++)
		if ( bLettre(ksPonderation[nC]) ){
			nDedouble++;
			sX=nSommetEtiquettE((*ppgG)->nSommetEnTout,ksPonderation[nC]);
			if (bVoir) {c(ksPonderation[nC]);d(sX);}
			while ( bDecit(ksPonderation[1+nC]) )
				nPoids=nPoids*10+ksPonderation[++nC]-'0';
			if (bVoir) printf("nPoids=%d.\n",nPoids);
			if (0) GrapheVoir0("bSommetPondereR AVANT pondération0",*ppgG,gpCapaMax);
				GrapheDedoubler(sX,gpCouleur+gpCout+gpPoids+gpCapaMax,ppgG);
			if (bPremiere) Ligne();
				printf("%sLe sommet %s est dédoublé: entrée %s, sortie %s,",sTab0(),sEnt(sX),sEnt(sX),sEnt( (*ppgG)->nSommetEnTout) );
				printf(" avec (%s,%s) de capacité maximale %d.",sEnt(sX),sEnt( (*ppgG)->nSommetEnTout),nPoids);
				/*if (*psTrappe==sX){
					*psTrappe=(*ppgG)->nSommetEnTout;
					printf(" Donc la trappe n'est plus %s mais %s.",sEnt(sX),sEnt(*psTrappe));
				};*/
				if (nDedouble<nDedoublt)
					Ligne();
				aK=nGrapheArc(*ppgG,sX,(*ppgG)->nSommetEnTout);
				(*ppgG)->nCapaMax[aK]=(*ppgG)->nPoids[aK]=(*ppgG)->nCout[aK]=(*ppgG)->coulh[aK]=nPoids;
			if (0) GrapheVoir0("bSommetPondereR APRÈS pondération1",*ppgG,gpCapaMax);
			bPremiere=0;
		}
Tabuler(-1);
	if (bVoir) b(bPonderer);
	if (!bPonderer)
		printf("Terme sommet+capacité incorrect (paires <1 sommet puis 1 chiffre> séparées par des ':' attendues).\n");
	//GrapheVoir0("bSommetPondereR FINAL",*ppgG,gpCapaMax);
	return(bPonderer);
}//bSommetPondereR

void SommetRenommeR(int nSommet,int cListe[]){
	cListe[0]=nSommet;
	VecteurIndexer(cListe,1,nSommet);
	//VecteurAjouter0(cListe,-1);
	//cListe[1]='S'-'@';
	//cListe[nSommet]='T'-'@';
}//SommetRenommeR

