#include "Kit.h"
#include "Erreur.h"
#include "Cfg.h"
#include "Grhom.h"
#include "Graphe.h"

#define kuAefColonneMaX 2
#define kuAefKolonneMaX 26
#define kuAefLigneMaX 26
int AEF0[1+kuAefLigneMaX][1+kuAefKolonneMaX][1+kuAefColonneMaX];//AEF0[0][0][0]:=nb lignes de l'AEF original et AEF0[0][1][0]:=' '
int AEF1[1+kuAefLigneMaX][1+kuAefKolonneMaX][1+kuAefColonneMaX];//AEF1[0][0][0]:=nb lignes de l'AEF cplémté et AEF1[0][1][0]:='{'
#define kuRegleMaX kE3
#define kuTermeMaX 50 //peut être important ds les gramR de Greibach
#define kuVocabulaireMaX 26
#define kuCfgCaratMaX (kE4-1)
char sCfG[1+kuCfgCaratMaX];
int bCfgAmorceR;
int nCfgReglE;

void AefComplementeR(int zdAfficher);
int bAefCompleteR(int bAfficher);
void AefDecodeR(int zdAfficher,char *sComplementaire);
int bAefDeterminiseR(int zdAfficher);
void AefReconnaitrE(int AEF2[][3],char *sMot,int nLettreAuPlus,int bAfficher,int *pnMotReconnu);
int bAefReconnaitrE(int AEF2[][3],char *sMot);
void AefReconnaitreTout(int AEF2[][3],int nLettreAuPlus);
void AefSimplifieR(int AEF[][1+kuAefKolonneMaX][1+kuAefColonneMaX],int AEF2[][1+2]);
void AefTabuleR();
void AefVoiR(char *sQuoi,int AEF2[][1+2]);
void AefVoirSouS(int bCondition,char *sQuoi,int AEF[][1+kuAefKolonneMaX][1+kuAefColonneMaX]);
void CommentE(int zdAfficher,char *sQuoi);
int bCfgAlgebriquE(const char *ksgrQuelconque,int bLineaire,int idAfficher);
int bCfgCompacteR(const char *ksNonCompact);
void CfgDecycleR(int zdAfficher);
void CfgDeformaliseR(int zdAfficher);
void CfgEpureR(int zdAfficher);
void CfgGreibacheR(const char *ksgrAlgebrique,int bPoursuivre,int bToutFaire,int zdAfficher,char *szgrGreibachOuQuasi);
void CfgGroupeR(int zdAfficher);
void CfgIdempoteR(int zdAfficher);
int bCfgLineaireAhDroitE(const char *ksGrAlgebrique);
void CfgListeR(char *sQuoi,int nPile[]);
int bCfgMotVidE(int zdAfficher);
void CfgOrdonneR(int zdAfficher);
void CfgPreordonneR(int zdAfficher);
int bCfgPropreR(const char *ksgrAlgebrique,int bDito,int zdAfficher,char *szgrPropre);
int bCfgProprerGreibacheR(const char *ksgrAlgebrique,int bPoursuivre,int bTout,int zdAfficher,char *szgrPropre);
int nCfgQuasiGreibachE(int mjRegle);
void CfgQuasiGreibacheR(int zdAfficher);
void CfgUnReduirE(int bVoir);
int bCfgUnSuprimeR();
void CfgVoiR(char *sQuoi,int bDetailler);
void CfgVoiR1(char *sQuoi,int bChange,int bDetailler);
char cMembreGauchE(int nRegle);
void MotVideSupprimeR(int bPanier[],int zdAfficher);
int bPanieR(int bPanier[],int nLieu);
void PanierJustifieR(int c1,int c2,int nDebut,int nFin,int bVoir);
int nProduitDebuT(int uRegle,int uProduit);
int nProduitEnTout(int uRegle);
int nProduitFiN(int uRegle,int uProduit);
int nRegleCopieR(int uR,int nOffset,int uT);
int nRegleDebuT(int uRegle);
void RegleDeriveR(int uRegle,int uProduit);
int nRegleFiN(int uRegle);
void RegleFusionneR(int uR,int uT);
int nRegleRanG(int mjDroit);
void RegleRetireR(int uRegle);
int bRegleSupprimeR(int bPanier[],int zdAfficher);
int nSuperEtaT(int uLigne,int uColonne,int uAef3LigneMax);
void SymboleRenommeR(int mjAvant,int mjApres,int bVoir);
int bSymboleSupprimeR(int bUnSinonBoucle,int bVoir);

void AefComplementeR(int zdAfficher){
	AefVoirSouS(zdAfficher,"original",AEF0);
	bAefCompleteR(zdAfficher);
	bAefDeterminiseR(zdAfficher);//actualise AEF1[0][0][0] 
	AefVoirSouS(zdAfficher>1,">>> AVANT complémentation",AEF1);
	CommentE(zdAfficher,"Pour tout super-état E et toute lettre l, il existe exactement une transition (E,l,…)");
	CommentE(zdAfficher,"Donc à tout mot m de A* correspond exactement un chemin depuis S");
	int uLigneMax=AEF1[0][0][0];
	for (int uL=1;uL<=uLigneMax;uL++)
		AEF1[uL][0][0]=1-AEF1[uL][0][0];
	AefVoirSouS(zdAfficher>1,">>> APRÈS complémentation",AEF1);
	CommentE(zdAfficher,"Un mot est reconnu ssi le dernier état du chemin associé à ce mot est un état final");
	CommentE(zdAfficher,"Donc complémenter le statut \"état final\" de chaque état complémente le langage initial");
	AefVoirSouS(zdAfficher,"complémenté",AEF1);
}//AefComplementeR

int bAefCompleteR(int idAfficher){
	//si non complet, ajoute une trappe ainsi que les transitions vers cette trappe. 
	int uC,bDejaComplet,cPasse,uL,uK,bNul;
	int uTrappe=kuVocabulaireMaX;
	//compléter l'AEF uniqt s'il n'est pas déjà complet, en ajoutant une transition vers la trappe pr chq transition manquante
		for (bDejaComplet=1,cPasse=0;cPasse<=1-bDejaComplet;cPasse++){
			for (uL=1;uL<=kuAefLigneMaX;uL++)
				if (AEF0[uL][uL][0])//l'état existe
					for (uC=1;uC<=kuAefColonneMaX;uC++){
						for (bNul=1,uK=1;uK<=kuAefKolonneMaX;uK++)
							bNul=bNul && AEF0[uL][uK][uC]==0;
						if (bNul)
							if (cPasse==0)
								bDejaComplet=0;
							else AEF0[uL][uTrappe][uC]=1;
					}
		}
	if (!bDejaComplet){//ajouter un état trappe et en faire une trappe
		AEF0[uTrappe][uTrappe][0]=1;//ajoute un état trappe, lequel n'est…
		AEF0[uTrappe][0][0]=0;//…pas un état final.
		for (int nC=1;nC<=kuAefColonneMaX;nC++)//ajoute ttes les transitions qui…
			AEF0[uTrappe][uTrappe][nC]=1;		//…vont de la trappe à la trappe.
	}else if (idAfficher>0)
		printf("%sL'AEF est déjà complet.\n",sTab0());
	if (!bDejaComplet)
		AefVoirSouS(idAfficher,"après complétude",AEF0);
	CommentE(iSup(0,idAfficher),"Pour tout état e et toute lettre l, il existe au moins une transition (e,l,…)");
	CommentE(iSup(0,idAfficher),"Donc à tout mot m de A* correspond au moins un chemin depuis S");
	return(bDejaComplet);
}//bAefCompleteR

void AefDecodeR(int zdAfficher,char *sComplementaire){
	//convertit AEF1 en grammaire linéaire à droite, la stocke ds sCfG[] avec ";" final" et ds sComplementaire SANS ";" final".
	const int kuLigneMax=AEF1[0][0][0];
	Assert1("AefDecodeR,AEF trop grand",kuLigneMax<'S'-'@');//sinon, améliorer la gestion des symboles, cf li-3.
	int nD=0,uL,uC,bEtatFinal,nEtat,bOperer;
	for (uL=1;uL<=kuLigneMax;uL++){
		sCfG[nD++]='@'+uL;//état origine
		sCfG[nD++]='-';
		sCfG[nD++]='>';
		for (bOperer=0,uC=1;uC<=kuAefColonneMaX;uC++){
			nEtat=nSuperEtaT(uL,uC,kuLigneMax);
			if (bOperer){
				sCfG[nD++]='+';
				bOperer=0;
			}
			if (nEtat){//ajouter la transition et l'état destination
				sCfG[nD++]='a'+uC-1;
				sCfG[nD++]='@'+nEtat;
				bOperer=1;
			}
		}
		bEtatFinal=AEF1[uL][0][0]>0;
		if (bEtatFinal){
			sCfG[nD++]='+';
			sCfG[nD++]='1';
		}
		sCfG[nD++]=';';
	}
	sCfG[nD]='\0';
	//forcer la présence du Start
		for (int nC=0;nC<nChaineLg(sCfG);nC++)
			if (sCfG[nC]=='A')
				sCfG[nC]='S';//valide si aucun état n'a déjà ce rang 
	ChaineCopier0(sCfG,sComplementaire);
	sComplementaire[nChaineLg(sComplementaire)-1]='\0';//supprime le ";" final
}//AefDecodeR

int bAefDeterminiseR(int zdAfficher){
	int bDejaDeterministe,uL,nC,uC,nChoix,uK,nEtat;
	//AefVoirSouS(1,"AVANT AefDeterminiseR",AEF0);
	//AEF1:=RAZ
		for (uL=0;uL<=kuAefLigneMaX;uL++)
			for (uC=0;uC<=kuAefColonneMaX;uC++)
				for (uK=0;uK<=kuAefKolonneMaX;uK++)
					AEF1[uL][uK][uC]=0;
	//le super état inital de AEF1 est l'état initial de AEF0
		for (nC=0;nC<=kuAefColonneMaX;nC++)
			for (uK=1;uK<=kuAefKolonneMaX;uK++)
				AEF1[1][uK][nC]=AEF0['S'-'@'][uK][nC];
		AEF1[1][0][0]=AEF0['S'-'@'][0][0];
	//bDejaDeterministe:=déjà déterministe
		for (bDejaDeterministe=uL=1;uL<=kuAefLigneMaX;uL++)
			if (AEF0[uL][uL][0])//l'état existe
				for (uC=1;uC<=kuAefColonneMaX;uC++){
					for (nChoix=0,uK=1;uK<=kuAefKolonneMaX;uK++)
						nChoix+=(AEF0[uL][uK][uC]>0);
					if (nChoix>1)
						bDejaDeterministe=0;
				}
	//le rendre déterministe
		int uAef3LigneMax=1;//compteur
		for (uL=1;uL<=uAef3LigneMax;uL++)
			for (uC=1;uC<=kuAefColonneMaX;uC++)
				if ( nSuperEtaT(uL,uC,uAef3LigneMax)==0 ) {
					for (uAef3LigneMax++,uK=1;uK<=kuAefKolonneMaX;uK++)
						AEF1[uAef3LigneMax][uK][0]=AEF1[uL][uK][uC];
					for (uK=1;nEtat=AEF1[uL][uK][uC],uK<=kuAefKolonneMaX;uK++)
						if (nEtat>0){//ajouter les états de AEF0(L,C)
							for (int uQ=1;uQ<=kuAefKolonneMaX;uQ++)
								for (int uD=1;uD<=2;uD++)
									AEF1[uAef3LigneMax][uQ][uD]=iSup(AEF1[uAef3LigneMax][uQ][uD],AEF0[uK][uQ][uD]);
							AEF1[uAef3LigneMax][0][0]=ySup(AEF1[uAef3LigneMax][0][0],AEF0[uK][0][0]);
						}
				}
		AEF1[0][0][0]=uAef3LigneMax;
		AEF1[0][1][0]='{';
	if (zdAfficher>0 && bDejaDeterministe)
		printf("%sL'AEF est déjà déterministe.\n",sTab0());
	if (!bDejaDeterministe)
		AefVoirSouS(zdAfficher,"après déterminisation",AEF1);
	if (bDejaDeterministe)
		CommentE(iSup(0,zdAfficher),"Pour tout état e et toute lettre l, il existe au plus une transition (e,l,…)");
	else CommentE(iSup(0,zdAfficher),"Pour tout super-état E et toute lettre l, il existe au plus une transition (E,l,…)");
	CommentE(iSup(0,zdAfficher),"Donc à tout mot m de A* correspond au plus un chemin depuis S");
	CommentE(iSup(0,zdAfficher),"Un AEF à n états déterminisé peut avoir O(2**n) états) et donc un coût exponentiel");
	return(bDejaDeterministe);
}//bAefDeterminiseR

void AefReconnaitrE(int AEF2[][3],char *sMot,int nLettreAuPlus,int bAfficher,int *pnMotReconnu){
	if (bAefReconnaitrE(AEF2,sMot)){
		*pnMotReconnu=(*pnMotReconnu)+1;
		if (bAfficher)
			printf("\n%s%3d: %s",sTab0(),*pnMotReconnu,sG(sMot));
	}
	if (nChaineLg(sMot)<nLettreAuPlus){
		AefReconnaitrE(AEF2,sC2(sMot,"a"),nLettreAuPlus,bAfficher,pnMotReconnu);
		AefReconnaitrE(AEF2,sC2(sMot,"b"),nLettreAuPlus,bAfficher,pnMotReconnu);
	}
}//AefReconnaitreTouT

int bAefReconnaitrE(int AEF2[][3],char *sMot){
	//vrai ssi l'AEF2 déterministe complet reconnaît le mot sMot
	int nCar,udLettre,nEtat0,nEtat1,bReconnaitre;
	char cCar;
	for (nEtat1=1,nCar=0;nCar<nChaineLg(sMot);nCar++){
		nEtat0=nEtat1;
		cCar=sMot[nCar];
		udLettre=(cCar=='a')? 1 : 2;
		nEtat1=AEF2[nEtat0][udLettre];
	}
	bReconnaitre=AEF2[nEtat1][0]>0;
	return(bReconnaitre);
}//bAefReconnaitrE

void AefReconnaitreTout(int AEF2[][3],int nLettreAuPlus){
	Assert1("AefReconnaitreTout",bCroit(0,nLettreAuPlus,10));
	//compter les mots reconnus
		int nMotReconnu=0;
		AefReconnaitrE(AEF2,"",nLettreAuPlus,!k1Afficher,&nMotReconnu);
	Flag(1);
		if (nMotReconnu){//les afficher
			Tabuler(-1);
				printf("%sMots de %s maximum engendrés par cette grammaire (ordre alphabétique croissant):",sTab0(),sPluriel(nLettreAuPlus,"lettre"));
				Tabuler(+1);
					nMotReconnu=0;
					AefReconnaitrE(AEF2,"",nLettreAuPlus,k1Afficher,&nMotReconnu);
					printf(".\n");
					int nMotEnTout=zPuissance(2,nLettreAuPlus+1)-1;
				Tabuler(-1);
				printf("%s%s plus %s (du langage complémentaire),",sTab0(),sPluriel(nMotReconnu,"mot"),sPluriel(nMotEnTout-nMotReconnu,"mot"));
				printf(" cela fait %s avec %s.\n",sPluriel(nMotEnTout,"mot$ réalisable$"),sPluriel(nLettreAuPlus,"lettre"));
			Tabuler(+1);
		}else printf("%sAucun mot n'est engendré par cette grammaire.\n",sTab0());
	Flag(0);
}//AefReconnaitreTout

void AefSimplifieR(int AEF[][1+kuAefKolonneMaX][1+kuAefColonneMaX],int AEF2[][1+2]){
	//transforme l'AEF en 3 dimensions en AEF à 2 dimensions
	const int kuStart='S'-'A'+1;
	int bPris,uL,nC,uK,nPile[1+kuAefLigneMaX];//cf vu +bas
	Assert1("AefSimplifieR",zPuissance(2,kuVocabulaireMaX)<kuIntegerMax);
	//AEF2:=AEF;
		for (AEF2[0][0]=AEF[0][0][0],nPile[0]=0,uL=1;uL<=AEF2[0][0];uL++){
			for (bPris=0,uK=1;uK<=kuAefKolonneMaX;uK++)
				bPris=bPris || 2*AEF[uL][uK][0];
			if (bPris)//établir une bijection entre les superétats et les entiers
				for (nC=0;nC<=kuAefColonneMaX;nC++)
					for (AEF2[uL][nC]=0,uK=1;uK<=kuAefKolonneMaX;uK++)
						if (AEF[uL][uK][nC])
							AEF2[uL][nC]=2*AEF2[uL][nC]+uK;//vu Assert1(), bijection valide car pas d'overflow
			AEF2[uL][0]=AEF[uL][0][0]>0;
		}
	//nPile:=pile des numéros distincts associés aux superétats
		for (nPile[0]=0,nPile[++nPile[0]]=kuStart,uL=1;uL<=AEF2[0][0];uL++)
			for (nC=1;nC<=2;nC++)
				if (!bVecteurContient(AEF2[uL][nC],nPile) ) 
					nPile[++nPile[0]]=AEF2[uL][nC];
		//VecteurVoir0("nPile",nPile);
	//renommer les états dans [1..AEF2[0][0]]
		for (uL=1;uL<=AEF2[0][0];uL++)
			for (nC=1;nC<=2;nC++)//2 cases qui ont le mm superentier auront maintenant le mm nouveau petit entier et le superétat…
				AEF2[uL][nC]=mVecteurContient(AEF2[uL][nC],nPile,1,nPile[0]);//…initial sera numéro 1 car c'est le 1er de nPile[].
}//AefSimplifieR

void AefTabuleR(){
	//tabule sCfG ds AEF0[][][]
	int uL,uK,nC,nDebut,nFin,uP,uR,uSource,udTerminal,uCible;
	for (uL=0;uL<=kuAefLigneMaX;uL++)
		for (nC=0;nC<=kuAefColonneMaX;nC++)
			for (uK=0;uK<=kuAefKolonneMaX;uK++)
				AEF0[uL][uK][nC]=0;
	for (uR=1;uR<=nCfgReglE;uR++){
		uSource=sCfG[nRegleDebuT(uR)]-'@';
		AEF0[uSource][uSource][0]=1;//ajoute l'état uSource aux états qui existent
		for (uP=1;uP<=nProduitEnTout(uR);uP++){
			nDebut=nProduitDebuT(uR,uP);
			nFin=nProduitFiN(uR,uP);
			if (nDebut<nFin){
				udTerminal=sCfG[nDebut]-'a'+1;
				uCible=sCfG[nFin]-'@';
				AEF0[uSource][uCible][udTerminal]=1;
			}else AEF0[uSource][0][0]=1;//état final
		}
	}
	AEF0[0][0][0]=kuAefLigneMaX;
	//AefVoirSouS(2*k1Afficher,"à la fin de AefTabuleR",AEF0);
}//AefTabuleR

void AefVoiR(char *sQuoi,int AEF2[][1+2]){
	int uL,nC;
	Flag(1);
		for (printf("%s%s:\n%s%s a   b\n",sTab0(),sQuoi,sTab0(),sE(9)),uL=1;uL<=AEF2[0][0];uL++)
			for (printf("%s%s%s%c%2d:",sTab0(),sE(2),(AEF2[uL][0])?"<=":"  ",(uL==1)?'>':' ',uL),nC=1;nC<=2|| bPrint("");nC++)
				printf ("%3d ",AEF2[uL][nC]);
		printf("%sNoter que l'AEF n'est en général pas minimal en nombre d'états (minimiser un AEF à n états coûte O(nlg(n)).\n",sTab0());
	Flag(0);
}//AefVoiR

void AefVoirSouS(int bCondition,char *sQuoi,int AEF[][1+kuAefKolonneMaX][1+kuAefColonneMaX]){
	if (bCondition){
		const int kuMarge = 31,kuEmpan = 20,kuTrou=3;
		const char ksTransition[]="Arc étiqueté",ksQuoi[]="Table associée à l'AEF";
		int nC,uK,uL,bEtatFinal,nLigne,nFormat,bPris,nPile[1+kuAefKolonneMaX],bStart,bSuperEtat=AEF[0][1][0]=='{';
		ModeCaractere(1);
			printf("\n%s     %s%s",sChaine2(ksQuoi,kuMarge),sChaine1((bSuperEtat)? "Super-état":"État",kuEmpan-4),sE(4));
			printf("%s%s%s\n",sChaine2(sC2b(ksTransition,sG("a")),kuEmpan),sE(kuTrou),sChaine2(sC2b(ksTransition,sG("b")),kuEmpan));
			for (nLigne=0,uL=1;uL<=kuAefLigneMaX;uL++){
				for (bPris=0,uK=1;uK<=kuAefKolonneMaX && !bPris;uK++)
					bPris=(AEF[uL][uK][0]!=0);
				//if (bPris) d(uL);
				if (bPris){
					printf("%s",(nLigne==0)? sChaine2(sQuoi,kuMarge) : sE(kuMarge));
					for (nLigne++,nC=0;nC<=kuAefColonneMaX || bPrint("");nC++){
						for (nPile[0]=0,uK=1;uK<=kuAefKolonneMaX;uK++)
							if (AEF[uL][uK][nC])
								nPile[++nPile[0]]=uK*AEF[uL][uK][nC];
						bEtatFinal=AEF[uL][0][0]>0;
//if ((nPile[0]>0)) {d(uL);VecteurVoir0("nPile",nPile);}
						bStart= uL==( (bSuperEtat)? 1 : 19 );
						// ménager kuTrou caractères pr "<=" suivide ">"
						if (nC==0) printf("%s%c%2d ",(bEtatFinal)?"<=":"  ",(bStart)?'>':' ',nLigne); else printf("%s",sE(kuTrou));
						if (nPile[0]>0)
							if (nC==0)
								printf("%s",sChaine1(sListe(nPile,nFormat=AEF[0][1][0]),kuEmpan-4));//-4 pr pouvoir placer "<=" devant
							else printf("%s",sChaine2(sListe(nPile,nFormat=AEF[0][1][0]),kuEmpan));
							//else printf("%s",sChaine2(sFois(kuEmpan-0,'.'),kuEmpan));
						else printf("%s",sChaine2(".",kuEmpan));
					}
				};
			}
		ModeCaractere(0);
	}
}//AefVoirSouS

int bCfgAlgebriquE(const char *ksgrQuelconque,int bLineaire,int idAfficher){
	//membre gauche=1 majuscule;membre droit=opérandes min ou maj séparés par des + ou rien
	int bDetailler=abs(idAfficher)>1;
	int nC,bSeparateur,bStart;
	int mSymboleAcquis[1+kuRegleMaX];
	int bAlgebrique=bCfgCompacteR(ksgrQuelconque);
	if (bAlgebrique){
		//réserver ds mSymboleAcquis[] les majuscules présentes ds ksgrQuelconque afin d'en interdire l'usage comme nouveau symbole
			VecteurRazer(mSymboleAcquis,0,kuRegleMaX);
			for (bSeparateur=1,bStart=nC=0;nC<nChaineLg(sCfG);nC++){
				if ( bMajuscule(sCfG[nC]) )
					mSymboleAcquis[sCfG[nC]-'@']=-1;//marque provisoire
					if (bSeparateur && sCfG[nC]=='S')
						bStart=1;
				bSeparateur=sCfG[nC]==';';
			}
		//b(bStart);printf("%sCode sCompact: %s.\n",sTab0(),sG(sCfG));VecteurVoir1("mSymboleAcquis",mSymboleAcquis,1,kuVocabulaireMaX);
		if (bDetailler) Flag(1);
			if (idAfficher>0) printf("%sCode source: %s.\n",sTab0(),sG(ksgrQuelconque));
			Tabuler(+1);
				if (idAfficher>1) printf("%sVoici les règles au sens large obtenues après suppression des blancs et des séparateurs du code source:\n",sTab0()); 
				bAlgebrique=bStart;
				Flag(0);//ici, même si refait plus bas
				nVecteurEcreter(mSymboleAcquis,0,kuRegleMaX,0,kuIntegerMax);
				if (idAfficher>0){
					CfgVoiR("Grammaire algébrique",bDetailler);
					if (bDetailler)
						printf("%sLa grammaire %s algébrique",sTab0(),sEst(bAlgebrique));
					if (idAfficher>1){
						if (bAlgebrique)
							printf(" car ses règles au sens strict sont de la forme V->(1+A+V)* et S débute une règle.");
						else if (bStart)
							printf(" car ses règles au sens strict ne sont pas toutes de la forme V->(1+A+V)*.");
						else printf(" car S ne figure pas en membre gauche d'une règle.");
						printf("\n");
					};
				}
			Tabuler(-1);
		if (bDetailler) Flag(0);
	}
	return(bAlgebrique);
}//bCfgAlgebriquE

void CfgAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
	bCfgAmorceR=kV;
}//CfgAMORCER

int bCfgCompacteR(const char *ksNonCompact){
	//sCompact:=ksNonCompact sans blancs ou caractères inconnus: si anomalie, rend le rg0 du 1er caractère invalide
	int bVoir=0;
	int nC,nD,uR,bCompacter,nFleche,bOperateur=0,bOperande=0,bOperateur0=0,cPasse,bAttendu;
	char cCar;
	Assert11("bCfgCompacteR",nChaineLg(ksNonCompact)<kuCfgCaratMaX,nChaineLg(ksNonCompact));
	for (bCompacter=1,cPasse=0;cPasse<=1 && bCompacter;cPasse++)
		for (nFleche=0,nCfgReglE=1,nC=nD=0,uR=1;cCar=ksNonCompact[nC],nC<nChaineLg(ksNonCompact) && bCompacter;nC++)
			if (cCar!=' ' && cCar!='.'){
				if (cPasse==1) sCfG[nD++]=cCar;
				if (cPasse==1) nCfgReglE+=cCar==';';
				bAttendu=bLettre(cCar) || cCar=='-' || cCar=='>' || cCar=='+' || cCar==';' || cCar=='1';
				ErreurDetecter(bAttendu,eCfgInconnu,nC+1-bAscii(cCar),&bCompacter);
				ErreurDetecter(cCar!='-' || bFleche(ksNonCompact,nC-1),eCfg2Fleche,nC+1,&bCompacter);//flèche dissociée
				ErreurDetecter(cCar!='>' || bFleche(ksNonCompact,nC-2),eCfg2Fleche,nC+1,&bCompacter);//flèche dissociée
				ErreurDetecter(cCar!='-' || bLettre(ksNonCompact[nC-1]),eCfgGauche,nC,&bCompacter);//T->
				nFleche+=bFleche(ksNonCompact,nC);
				bOperateur0=bOperateur;
				bOperateur=(cCar=='+');
				ErreurDetecter(!bOperateur0 || !bOperateur,eCfgSomme,nC,&bCompacter);//opérateurs consécutifs
				ErreurDetecter(cCar!=';' || nFleche==1,eCfg1Fleche,nC,&bCompacter);//trop de flèches
				ErreurDetecter(cCar!=';' || bOperande,eCfgOperande,nC,&bCompacter);//opérande manque
				bOperande=bLettre(cCar) || cCar=='1';
				if (cCar==';')
					nFleche=0;
			}
	if (bCompacter){
		sCfG[nD++]=';';
		sCfG[nD]='\0';
		if (bVoir)
			for (s(sCfG),uR=1;uR<=nCfgReglE;uR++)
				d2(nRegleDebuT(uR),nRegleFiN(uR));
	}else {
		/*d(mCompacter);
		Tabuler(+1);
			printf("%s%s contient un symbole invalide signalé ci-dessous par \"[?]\":\n",sTab0(),sG(ksNonCompact));
			printf("%s\"%s[?]%s\".\n",sTab0(),sChainon(ksNonCompact,0,mCompacter),sChainon(ksNonCompact,mCompacter+1,kuIntegerMax));
		Tabuler(-1);*/
		ErreurAfficherTout(ksNonCompact);
	}
	return(bCompacter);
}//bCfgCompacteR

void CfgComplementer(const char *ksgrLineaireAhDroite,int nLettreAuPlus,int zdAfficher,char *szgrComplementaire){
	//rend ds szgrComplementaire la grammaire complémentaire de ksgrLineaireAhDroite ou affiche un message d'erreur si non défini.
	//si affichage détaillé et nLettreAuPlus>0, affiche les mots engendrés par ksgrLineaireAhDroite et ceux du complémentaire
	char sComplementaire[kE4];
	int bDetailler=zdAfficher>1;
	int bMotLister=bDetailler && nLettreAuPlus>0;
	Assert1("CfgComplementer",bCroit(0,zdAfficher,2) );
	int bGld=bCfgLineaireAhDroite(ksgrLineaireAhDroite,zdAfficher);
	if ( bGld ){
		if (bMotLister){
			Tabuler(-1);
				CfgReconnaitre(ksgrLineaireAhDroite,nLettreAuPlus,-zdAfficher);
			Tabuler(-1);
		}else {Tabuler(+1);CfgVoiR("Grammaire linéaire G",!k1Detailler);Tabuler(-1);}
		Tabuler(+1);
			if (zdAfficher>0)
				printf("%sG est linéaire à droite et A={a,b}. Donc le complémentaire de G par rapport à A* est calculable par AEF.\n",sTab0());
			if (bDetailler){
				Flag(1);
					printf("%sLe Start est le seul point d'entrée de G. Donc l'AEF associé à G a un seul état initial: S.\n",sTab0());
				Flag(0);
			}
			AefTabuleR();//stocke sCfG dans AEF0 
			AefComplementeR(zdAfficher);//rend le complément de AEF0 dans AEF1
			AefDecodeR(zdAfficher,sComplementaire);//stocke AEF1 ds sComplementaire
			int bAlgebriquer=bCfgAlgebriquE(sComplementaire,k1Lineaire,!k1Afficher);
			Assert1("CfgComplementer9",bAlgebriquer);
			CfgVoiR("Grammaire complémentaire",zdAfficher);
			if (bMotLister){
				Tabuler(-1);
					CfgReconnaitre(sComplementaire,nLettreAuPlus,zdAfficher);
				Tabuler(-1);
			}
			if (szgrComplementaire!=NULL)
				szgrComplementaire=sChaineCopie(sCfG);
	}else bCfgLineaireAhDroite(ksgrLineaireAhDroite,k1Afficher);
}//CfgComplementer

void CfgDecycleR(int zdAfficher){
	//inventorie les dépendances, génère le graphe associé (1 arc pardépendanceRF), puis élimine les cycles.
	int bDetailler=zdAfficher>1;
	int nArc,mjAvant,sX,uP,uR,uT,nElement,uCfc,nCfcEnTout,mjUnique,nCfc,nDebut,nFin,bFusion;
	char cGauche,cTerme,cDroit;
	graf *pgG;
	if (zdAfficher) printf("\n5° Supprimer les cycles:\n");
	GrapheCreer(kuVocabulaireMaX,&pgG);
		//pgG:=graphe généré
			for (uR=1;uR<=nCfgReglE;uR++)
				for (cGauche=cMembreGauchE(uR),uP=1;uP<=nProduitEnTout(uR);uP++){
					nDebut=nProduitDebuT(uR,uP);
					nFin=nProduitFiN(uR,uP);
					cTerme=sCfG[nDebut];
					//c(cTerme);
					if (nDebut==nFin && cGauche!=cTerme && bMajuscule(cTerme))
						GrapheArquer(pgG,cGauche-'@',cTerme-'@');
				}
		if (zdAfficher)
			if (pgG->nArcEnTout>0)
				GrapheWoir(sC2(sTab0(),"Graphe des règles formelles, dont cycles éventuels"),pgG);
			else printf("%sLe graphe des règles formelles ne renferme aucun arc.\n",sTab0());
		//remplacer les RF qui sont dans un même circuit, et donc homonymes, par l'un de ses représentants
			nCfcEnTout=nGrapheComposanteFortementConnexe("CfgDecycleR",pgG,!k1Voir);
			int mjPile[1+pgG->nSommetEnTout];
			if (nCfcEnTout<pgG->nSommetEnTout && zdAfficher)
				printf("%sListe des composantes fortement connexes à 2 éléments ou plus (CFC):\n",sTab0());
		Tabuler(+1);
			for (nCfc=0,uCfc=1;uCfc<=nCfcEnTout;uCfc++){
				for (nElement=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
					nElement+=(pgG->sPer[sX]==uCfc);
				if (nElement>1){
					nCfc++;
					mjUnique=(pgG->sPer['S'-'@']==uCfc)? 'S': uCfc+'@';
					if (zdAfficher) printf("%sCFC n°%d: {%c",sTab0(),nCfc,mjUnique);
					//rplacer sX par le représentant mjUnique ds tte la CFC courante
						for (mjPile[0]=1,mjPile[1]=mjUnique,sX=uCfc;mjAvant=sX+'@',sX<=pgG->nSommetEnTout;sX++)
							if (mjAvant!=mjUnique && pgG->sPer[sX]==uCfc){
								//cc(mjAvant,mjUnique);
								SymboleRenommeR(mjAvant,mjUnique,bDetailler);
								if (zdAfficher) printf(",%c",mjAvant);
								mjPile[++mjPile[0]]=mjAvant;
							}
					//if (bVoir) printf(", %c}.\n",mjUnique);
					if (zdAfficher) printf("}.\n");
					//d2(mjPile[0],mjUnique);
				}
			}
		Tabuler(-1);
		nArc=pgG->nArcEnTout;
	GrapheCreer(0,&pgG);
	Flag(1);
		do{
			//s(sCfG);
			for (bFusion=0,uR=1;uR<nCfgReglE && !bFusion;uR++){
				nDebut=nRegleDebuT(uR);
				cGauche=sCfG[nDebut];
				//cd(cGauche,uR);
				for (uT=uR+1;uT<=nCfgReglE && !bFusion;uT++){
					nDebut=nRegleDebuT(uT);cDroit=sCfG[nDebut];
					//cd(cDroit,uT);
					if ( cGauche==cDroit){
						//Titrer("eureka");//cd(cGauche,uR);
						Tabuler(-1);
							if (zdAfficher)
								printf("%sFusion des règles %d et %d.\n",sTab0(),uR,uT);
						Tabuler(+1);
						RegleFusionneR(uT,uR);
						if (bDetailler)
							CfgVoiR("Grammaire après fusion",bDetailler);
						bFusion=1;
					}
				}
			}
		}while (bFusion);
		int bSupprimer=bSymboleSupprimeR(nArc,bDetailler);
	Flag(0);
	if (zdAfficher)
		CfgVoiR1("grammaire sans cycles",bSupprimer,bDetailler);
}//CfgDecycleR

void CfgDeformaliseR(int zdAfficher){
	//supprime les règles formelles
	int bDetailler=zdAfficher>1;
	int uP,uR,nTermat,uNiveauMax,uNivo,nDebut,nFin;
	char cGauche,cTerme;
	graf *pgG;
	if (zdAfficher) printf("\n6° Supprimer les règle formelles:\n");
	GrapheCreer(kuVocabulaireMaX,&pgG);
		//pgG:=graphe généré
			for (uR=1;uR<=nCfgReglE;uR++)
				for (cGauche=cMembreGauchE(uR),uP=1;uP<=nProduitEnTout(uR);uP++){
					nDebut=nProduitDebuT(uR,uP);
					nFin=nProduitFiN(uR,uP);
					cTerme=sCfG[nDebut];
					if (nDebut==nFin && cGauche!=cTerme && bMajuscule(cTerme))
						GrapheArquer(pgG,cGauche-'@',cTerme-'@');
				}
		if (zdAfficher)
			if (pgG->nArcEnTout>0)
				GrapheWoir(sC2(sTab0(),"Graphe des règles formelles, réputé sans cycles"),pgG);
			else printf("%sLe graphe des règles formelles ne renferme aucun arc.\n",sTab0());
	if (bDetailler) Flag(1);
//if (bDetailler) Tabuler(-1);
		bGrapheTrierTopologiquement(pgG,!k1Afficher);//O(A);
		uNiveauMax=yVecteurSup(pgG->nVal,1,pgG->nSommetEnTout);
		for (uNivo=uNiveauMax-1;uNivo>=1;uNivo--)
			for (uR=1;uR<=nCfgReglE;uR++){
				cGauche=cMembreGauchE(uR);
				if (pgG->nVal[cGauche-'@']==uNivo){
					for (uP=1;uP<=nProduitEnTout(uR);uP++){
						nDebut=nProduitDebuT(uR,uP);
						nFin=nProduitFiN(uR,uP);
						nTermat=nFin-nDebut+1;
						if ( nTermat==1 && bMajuscule(sCfG[nDebut])){
							char cDroit=sCfG[nDebut];//vu li+1
							RegleDeriveR(uR,uP);
							if (bDetailler)
								CfgVoiR(sC6("Grammaire après dérivation de ",sC0(cDroit),", le terme n°",sEnt(uP)," de la règle ",sEnt(uR)),!k1Voir);
						}
					}
				}
		}
//if (bDetailler) Tabuler(+1);
if (bDetailler) Flag(0);
		CfgIdempoteR(zdAfficher);
	if (zdAfficher) 
		CfgVoiR("Grammaire irredondante sans règles formelles",!k1Voir);
}//CfgDeformaliseR

void CfgEpureR(int zdAfficher){
	//supprime ts les non terminaux qui ne sont pas des noms de règle ——ils engendrent le langage vide.
	int nC,nD,uR,uP,nDebut,bOperer,nReglEnTroP;
	int bDetailler=zdAfficher>1;
	int bPerte,bPerdu[kE2];
	const int kuNonTerminauxMax=kuVocabulaireMaX;
	int bConnu[1+kuNonTerminauxMax];
	int nPerdu[1+kuNonTerminauxMax];
	//ds(4,sCfG);
	VecteurRazer(bConnu,1,kuNonTerminauxMax);
	VecteurRazer(nPerdu,1,kuNonTerminauxMax);
	for (uR=1;uR<=nCfgReglE;uR++)
		bConnu[cMembreGauchE(uR)-'@']=1;
	//VecteurVoir("bConnu",bConnu,1,kuNonTerminauxMax);
	char sCfg1[kuCfgCaratMaX];
	strcpy(sCfg1,sCfG);
		Flag(1);Tabuler(-1);
		for (bPerte=nReglEnTroP=nD=0,uR=1;uR<=nCfgReglE;uR++){
			//nPerdu[]:=1 coche par produit contenant un non terminal superflu
				for (uP=1;uP<=nProduitEnTout(uR);uP++)
					for (bPerdu[uP]=0,nC=nProduitDebuT(uR,uP);nC<=nProduitFiN(uR,uP);nC++)
						if (bMajuscule(sCfG[nC]) && !bConnu[sCfG[nC]-'@'])
							nPerdu[sCfG[nC]-'@']=bPerdu[uP]=1;
			int bNonVide=yVecteurInf(bPerdu,1,nProduitEnTout(uR))==0;//tous les produits sont superflus
			if (bNonVide){
				//recopier le début de règle
					for (nDebut=nProduitDebuT(uR,1),nC=nDebut-3;nC<nDebut;nC++)
						sCfg1[nD++]=sCfG[nC];
				//empiler les seuls produits non nuls et les relier par des '+'
					for (bOperer=0,uP=1;uP<=nProduitEnTout(uR);uP++)
						if (!bPerdu[uP]){
							if (bOperer){
								sCfg1[nD++]='+';
								bOperer=0;
							}
							for (nC=nProduitDebuT(uR,uP);nC<=nProduitFiN(uR,uP);nC++)
								sCfg1[nD++]=sCfG[nC];
							bOperer=1;
						}else {
							bPerte=1;
							if (bDetailler)
								printf("%sLe produit %d de la règle %d engendre le langage vide.\n",sTab0(),uP,uR);
						}
				sCfg1[nD++]=';';
			}else {
				nReglEnTroP++;
				int bPlusieurs=nProduitEnTout(uR)>1;
				if (bDetailler)
					printf("%s%s de la règle %d engendre%s le langage vide.\n",sTab0(),(bPlusieurs)?"Tous les produits":"Le produit",uR,(bPlusieurs)?"nt":"");
			}
		}
		sCfg1[nD]='\0';
		Flag(0);Tabuler(+1);
	strcpy(sCfG,sCfg1);
	//s(sCfG);
	nCfgReglE-=nReglEnTroP;
	if (zdAfficher){
		CfgVoiR1("grammaire définie à droite (1 règle exactement par non terminal en membre droit)",nReglEnTroP>0 || bPerte,bDetailler);
		ModeCaractere(+1);
			Flag(1);
				//printf("%sNon terminaux absents des membres gauches: %s.\n",sTab0(),sListe(nPerdu,'}'));
			Flag(0);
		ModeCaractere(-1);
		//CfgVoiR("Grammaire sans les non terminaux qui ne figurent dans aucun membre gauche",!k1Voir);
	}
}//CfgEpureR

int nMajusculE(int nRang,int bVocabulaire[]){
	//réquisitionne une majuscule disponible, si possible par simple chgt de casse.
	Assert1("nMajusculE",yVecteurInf(bVocabulaire,3,26)==0);//une majuscule Au moins est disponible
	int nMajuscule=nRang;
	if (bVocabulaire[nMajuscule]){
		nMajuscule=2;//dc au-delà de A et B
		do{
		}while (bVocabulaire[++nMajuscule]);
	}
	return(nMajuscule);
}//nMajusculE

int bCfgGreibachE(){
	//supprimer ds les membres droits les minuscules non premières
	int nC,nD,uP,uR,nDebut,nFin,bGreibache=0;
	char sCfg1[kuCfgCaratMaX];
	int nAlphabet[1+kuVocabulaireMaX];
	int bVocabulaire[1+kuVocabulaireMaX];
	//bVocabulaire:={non terminaux} avant de devoir réquisitionner des majuscules
		VecteurRazer(bVocabulaire,1,kuVocabulaireMaX);
		for (nD=0,uR=1;uR<=nCfgReglE;uR++){
			nDebut=nRegleDebuT(uR);
			int mjGauche=cMembreGauchE(uR);
			bVocabulaire[mjGauche-'@']=1;
		}
	VecteurRazer(nAlphabet,1,kuVocabulaireMaX);
	for (nD=0,uR=1;uR<=nCfgReglE;uR++){
		nDebut=nRegleDebuT(uR);
		for (nC=nDebut;nC<nDebut+3+(sCfG[nDebut+1]=='\'');nC++)
			sCfg1[nD++]=sCfG[nC];
		//recopier le membre droit en majusculant au besoin les terminaux secondaires
			for (uP=1;uP<=nProduitEnTout(uR);uP++){
				nDebut=nProduitDebuT(uR,uP);
				nFin=nProduitFiN(uR,uP);
				sCfg1[nD++]=sCfG[nDebut];
				for (nC=nDebut+1;nC<=nFin;nC++){
					if (sCfG[nC]!='\'' && !bMajuscule(sCfG[nC])){
						int nRang=sCfG[nC]+'A'-'a'-'@';
						if (!nAlphabet[nRang])//attribuer une fois pr ttes 1 majuscule à la minuscule de rang nRang 
							nAlphabet[nRang]=nMajusculE(nRang,bVocabulaire);
						sCfg1[nD++]=cLettre(nAlphabet[nRang]);
						bGreibache=1;
					}else sCfg1[nD++]=sCfG[nC] ;
				}
				sCfg1[nD++]='+';
			}
		sCfg1[nD-1]=';';
	}
	//VecteurVoir("nAlphabet",nAlphabet,1,kuVocabulaireMaX);
	//VecteurVoir("bVocabulaire",bVocabulaire,1,kuVocabulaireMaX);
	//ajouter 1 règle terminale par minuscule non en tête de produit en réquisitionnant des éléments de bVocabulaire[]
		for (int uC=1;uC<=kuVocabulaireMaX;uC++)
			if (nAlphabet[uC]){
				sCfg1[nD++]=cLettre(nAlphabet[uC]);sCfg1[nD++]='-';sCfg1[nD++]='>';sCfg1[nD++]=cLettre(26+uC);sCfg1[nD++]=';';
				nAlphabet[uC]=0;
				nCfgReglE++;
			}
	sCfg1[nD]='\0';
	strcpy(sCfG,sCfg1);
	//s(sCfG);
	return(bGreibache);// vrai ssi au moins 1 minuscule a été majusculée
}//bCfgGreibachE

void CfgGreibacheR(const char *ksgrAlgebrique,int bPoursuite,int bToutFaire,int zdAfficher,char *szgrGreibachOuQuasi){
	int bGreibache=0;
	char sCfgPropre[kE4];
	Assert1("CfgGreibacheR",bCroit(0,zdAfficher,2));
	if ( bCfgPropreR(ksgrAlgebrique,!k1Dito,!k1Afficher,sCfgPropre) ){
		if (1) {
			Tabuler(-1);
			CfgVoiR("Grammaire propre",!k1Detailler);
			if (zdAfficher)
				printf("\n%d° Éliminer les récursivités à gauche:\n",(bPoursuite)? 7 : 1);
			CfgQuasiGreibacheR(zdAfficher);
			if (zdAfficher==1) CfgVoiR("Grammaire non récursive à gauche",!k1Detailler);
			if (zdAfficher>1) printf("%sCette grammaire est quasi-Greibach.\n",sTab0());
			if (zdAfficher && bToutFaire)
				printf("\n%d° Remplacer les terminaux qui ne débutent pas un produit par des non terminaux:\n",(bPoursuite)?8:2);
			bGreibache=bToutFaire && bCfgGreibachE(zdAfficher);//supprime les minuscules en tête de membre droit
			if (szgrGreibachOuQuasi==NULL){
				if (bToutFaire)
					if (bGreibache)
						CfgVoiR("Grammaire de Greibach obtenue en remplaçant les terminaux qui ne débutent pas un produit par des non terminaux",!k1Detailler);
					else printf("%sC'est aussi une grammaire de Greibach car aucun terminal ne débute un produit.\n",sTab0());
			}else ChaineCopier(sCfG,nChaineLg(sCfG),szgrGreibachOuQuasi);
			//s(szgrGreibachOuQuasi);
		}
	}else printf("La grammaire fournie n'est pas propre.\n");
}//CfgGreibacheR

void CfgGroupeR(int zdAfficher){
	//rassemble toutes les règles qui ont le même membre gauche en une règle unique
	int bFusion,uR,bDetailler=zdAfficher>1;
	if (bDetailler) {Flag(1);Tabuler(-1);}
		for (bFusion=0,uR=nCfgReglE;uR>0;uR--)
			for (int uT=uR-1;uT>0;uT--){
				if ( cMembreGauchE(uR)==cMembreGauchE(uT)){
					//Titrer("eureka");
					if (bDetailler)
						printf("%sLa fusion des règles %d et %d réduit le nombre de règles au sens large.\n",sTab0(),uR,uT);
					RegleFusionneR(uR,uT);
					bFusion=1;
				}
			}
	if (bDetailler) {Flag(0);Tabuler(+1);}
	if (zdAfficher)
		CfgVoiR1("grammaire définie à gauche (1 règle exactement par non terminal en membre gauche)",bFusion,bDetailler);
	Flag(1);
		if (bDetailler)
			printf("%sNoter que les membres gauches sont maintenant distincts ––et qu'ils le resteront.\n",sTab0());
	Flag(0);
}//CfgGroupeR

void CfgIdempoteR(int zdAfficher){
	//remplace a+a par a
	int nC,bEgal,nD,nDebut,nDebut0,nDebut1,nFin0,nFin1,bOperer,uP,uQ,uR,bChange;
	int bDito[1+100];
	VecteurRazer(bDito,1,100);
	char sCfg1[kuCfgCaratMaX];
	strcpy(sCfg1,sCfG);
		for (bChange=0,nD=0,uR=1;uR<=nCfgReglE;uR++){
			VecteurRazer(bDito,1,nProduitEnTout(uR));
			for (uP=1;uP<nProduitEnTout(uR);uP++){
				nDebut0=nProduitDebuT(uR,uP);
				nFin0=nProduitFiN(uR,uP);
				for (uQ=uP+1;uQ<=nProduitEnTout(uR);uQ++){
					nDebut1=nProduitDebuT(uR,uQ);
					nFin1=nProduitFiN(uR,uQ);
					//if (uR==3) d6(uP,nDebut0,nFin0,uQ,nDebut1,nFin1);
					for (bEgal=nFin0-nDebut0==nFin1-nDebut1,nC=0;nC<=nFin1-nDebut1 && bEgal;nC++)
						bEgal=sCfG[nDebut0+nC]==sCfG[nDebut1+nC];
					bDito[uQ]=bDito[uQ] || bEgal;
				}
			}
			//d(uR);VecteurVoir("bDito",bDito,1,nProduitEnTout(uR));
			//recopier le début de règle
				for (nDebut=nProduitDebuT(uR,1),nC=nDebut-3;nC<nDebut;nC++)
					sCfg1[nD++]=sCfG[nC];
			//recopier les produits qui ne sont pas des redites
				for (bOperer=0,uP=1;uP<=nProduitEnTout(uR);uP++){
					if (!bDito[uP]){//empiler les seuls produits non nuls et les relier par des '+'
						if (bOperer){
							sCfg1[nD++]='+';
							bOperer=0;
						}
						for (nC=nProduitDebuT(uR,uP);nC<=nProduitFiN(uR,uP);nC++)
							sCfg1[nD++]=sCfG[nC];
						bOperer=1;
					}else bChange=1;
				}
			sCfg1[nD++]=';';
		}
		sCfg1[nD]='\0';
	strcpy(sCfG,sCfg1);
	//b(bChange);
	if (zdAfficher)
		CfgVoiR1("grammaire à sommes simples (par idempotence: T+T=T)",bChange,zdAfficher>1);
}//CfgIdempoteR

int bCfgLineaireAhDroitE(const char *ksGrAlgebrique){
	//rend vrai ssi linéaire à droite vérifiant A={a,b};sinon, affiche un message d'erreur adéquat et son contexte.
	int nDebut,nFin,bOk,uP,uR;
	for (bOk=1,uR=1;uR<=nCfgReglE && bOk;uR++)
		for (uP=1;nDebut=nProduitDebuT(uR,uP),nFin=nProduitFiN(uR,uP),uP<=nProduitEnTout(uR) && bOk;uP++)
			if (nDebut<nFin){
				ErreurDetecter(nDebut+1==nFin,eCfgLineaire,nFin,&bOk);
				ErreurDetecter(bDans2(sCfG[nDebut],'a','b'),eCfgLineaire,nDebut,&bOk);
				ErreurDetecter(bMajuscule(sCfG[nFin]),eCfgLineaire,nFin,&bOk);
			}else ErreurDetecter(sCfG[nDebut]=='1',eCfgLineaire,nDebut,&bOk);
	if (!bOk)
		ErreurAfficherTout(sCfG);
	return(bOk);
}//bCfgLineaireAhDroitE

int bCfgLineaireAhDroite(const char *ksgrLineaireAhDroite,int tAfficher){
	//Rend vrai ssi c'est une gld. Si nLettreAuPlus est >0, affiche la gramR et la teste avec ts les mots de lgr<=nLettreAuPlus.
	if (tAfficher){
		Tabuler(+1);
			printf("%sGrammaire%s:\n",sTab0(),(tAfficher<0)?" à complémenter":"");
			printf("%s%s%s.\n",sTab0(),sTab0(),sG(ksgrLineaireAhDroite));
		Tabuler(-1);
	}
	int bLineaireAhDroite=bCfgAlgebriquE(ksgrLineaireAhDroite,k1Lineaire,-k1Afficher) && bCfgLineaireAhDroitE(ksgrLineaireAhDroite);
	if (!bLineaireAhDroite){
		Tabuler(+1);
			printf("%sCette grammaire %s linéaire à droite.\n",sTab0(),sEst(bLineaireAhDroite));
		Tabuler(-1);
	}
	return(bLineaireAhDroite);
}//bCfgLineaireAhDroite

void CfgListeR(char *sQuoi,int nPile[]){
	int uP;
	ModeCaractere(+1);
		for (printf("%sRègles atteintes en partant %s: ",sTab0(),sQuoi),uP=1;uP<=nPile[0] || bPrint("|.");uP++)
			if (nPile[uP]<0)
				printf("1%s",(nPile[uP+1]>0)? ", ": " |");
			else if (nPile[uP])
				printf("%s%s",sEnt(nPile[uP]),(nPile[uP+1]>0)? ", ": " |");
			else if (uP+1<nPile[0])
				printf(" ");
	ModeCaractere(-1);
}//CfgListeR

int bCfgMotVidE(int zdAfficher){
	//vrai ssi le mot vide est engendré depuis la règle Start
	int bDetailler=zdAfficher>1;
	int bBarre=0,nC,uP,uR,bPoursuivre,bMotVide,nPlace,nPasse=0,nDebut,nFin,mjGauche,bEngendre;
	int bPanier[1+kuVocabulaireMaX];//bPanier[uMajuscule] vrai ssi le symbole de rg1 uMajuscule est en membre gauche
	int bPanetiere[1+kuVocabulaireMaX];
	int nPile[1+kuRegleMaX];
	if (zdAfficher) printf("\n3° Inventorier les productions vides:\n");
	VecteurRaz(bPanetiere,kuVocabulaireMaX);
	nPile[0]=1;nPile[1]='1'-'@';nPile[++nPile[0]]=0;//séparateur
if (bDetailler) Flag(1);
		do{
			VecteurCopier(bPanetiere,0,kuVocabulaireMaX,bPanier);
			nPasse++;
			for (bPoursuivre=0,uR=1;uR<=nCfgReglE;uR++){
				nDebut=nRegleDebuT(uR);
				mjGauche=sCfG[nDebut];
				//c(mjGauche);
				nPlace=mjGauche-'@';
				if (!bPanier[nPlace]){
					for (bEngendre=0,uP=1;uP<=nProduitEnTout(uR) && !bEngendre;uP++){
						nDebut=nProduitDebuT(uR,uP);
						nFin=nProduitFiN(uR,uP);
						for (bEngendre=1,nC=nDebut;nC<=nFin && bEngendre;nC++){
							char cTerme=sCfG[nC];
							bEngendre=cTerme=='1' || bPanieR(bPanier,cTerme-'@');
						}
					}
					Assert1("bCfgMotVidE",bCroit(1,nPlace,kuVocabulaireMaX));
					bPanetiere[nPlace]=bEngendre;
					if (bEngendre){
						PanierJustifieR(mjGauche,mjGauche,nDebut,nFin,bDetailler);
						nPile[++nPile[0]]=nPlace;
						bBarre=0;
					}
					bPoursuivre=bPoursuivre || bEngendre;
				}
			}//for
			if (!bBarre){
				nPile[++nPile[0]]=0;//séparateur
				bBarre=1;
			}
		}while (bPoursuivre);
if (bDetailler) Flag(0);
	if (zdAfficher) CfgListeR("du mot vide",nPile);
	if (zdAfficher && nPile[0]<=3)
		CfgVoiR1("grammaire sans mots vides",0,bDetailler);
	bMotVide=bPanier['S'-'@']==1;
	if (!bMotVide){
		if (zdAfficher) printf("\n4° Supprimer les productions vides:\n");
		//VecteurVoir("bPanetiere",bPanetiere,1,kuVocabulaireMaX);
		MotVideSupprimeR(bPanetiere,bDetailler);
		CfgUnReduirE(zdAfficher);
		CfgIdempoteR(zdAfficher);
		bCfgUnSuprimeR(zdAfficher);
		if (zdAfficher) CfgVoiR("Grammaire après suppression des règles vides",bDetailler);
	}else Titrer("La grammaire ne pourra jamais être propre car elle engendre le mot vide");
	return(bMotVide);
}//bCfgMotVidE

int bCfgNormaliser(const char *ksgrAlgebriqueOuPropre,int bAlgebrique,int tPropre1Quasi2Greibach3,int zdAfficher,char *szgrPropreOuQuasiGreibachOuGreibach){
	Assert2("CfgNormaliseR",bBool(bAlgebrique),zdAfficher>=0);
	int bSucces=kV;
	char *sCible="propre,quasi-Greibach,de Greibach";
	Titrer(sC4b("Transformation d'une grammaire",sChoix(bAlgebrique,"algébrique","propre"),"en grammaire",sItem(sCible,tPropre1Quasi2Greibach3)));
	if (bAlgebrique)
		switch(tPropre1Quasi2Greibach3){
			case 1: bSucces=bCfgProprerGreibacheR(ksgrAlgebriqueOuPropre,!k1Poursuivre,k1Tout,zdAfficher,szgrPropreOuQuasiGreibachOuGreibach);break;
			case 2: bSucces=bCfgProprerGreibacheR(ksgrAlgebriqueOuPropre,k1Poursuivre,!k1Tout,zdAfficher,szgrPropreOuQuasiGreibachOuGreibach);break;
			case 3: bSucces=bCfgProprerGreibacheR(ksgrAlgebriqueOuPropre,k1Poursuivre,k1Tout,zdAfficher,szgrPropreOuQuasiGreibachOuGreibach);break;
			default:Assert1("CfgNormaliser default",0);
	}else switch(tPropre1Quasi2Greibach3){
			case 1: bCfgPropreR(ksgrAlgebriqueOuPropre,!k1Dito,zdAfficher,szgrPropreOuQuasiGreibachOuGreibach);break;
			case 2: CfgGreibacheR(ksgrAlgebriqueOuPropre,!k1Poursuivre,!k1Tout,zdAfficher,szgrPropreOuQuasiGreibachOuGreibach);break;
			case 3: CfgGreibacheR(ksgrAlgebriqueOuPropre,!k1Poursuivre,k1Tout,zdAfficher,szgrPropreOuQuasiGreibachOuGreibach);break;
			default:Assert1("CfgNormaliser default",0);
		}
	return(bSucces);
}//bCfgNormaliser

void CfgOrdonneR(int zdAfficher){
	//retire de la gramR les règles non accessibles depuis la règle Start
	int bDetailler=zdAfficher>1;
	int bBarre=0,uR,bPoursuivre,nPasse=0,nDebut,nFin,mjGauche,nPlace,bEngendre,uP;
	int bPanier[1+kuRegleMaX];//bPanier[uMajuscule] vrai ssi le symbole de rg1 uMajuscule est en membre gauche
	int bPanetiere[1+kuRegleMaX];
	int nPile[1+kuRegleMaX];
	if (zdAfficher) printf("\n2° Ordonner:\n");
	VecteurRaz(bPanier,kuRegleMaX);
	VecteurRaz(bPanetiere,kuRegleMaX);
	bPanetiere[nLettre('S')]=1;
	nPile[0]=1;nPile[1]='S'-'@';nPile[++nPile[0]]=0;//séparateur
if (bDetailler) Flag(1);
		do{
			VecteurCopier(bPanetiere,0,kuRegleMaX,bPanier);
			nPasse++;
			for (bPoursuivre=0,uR=1;uR<=nCfgReglE;uR++){
				nDebut=nRegleDebuT(uR);
				mjGauche=sCfG[nDebut];
				nPlace=mjGauche-'@';
				//c(mjGauche);d(nPlace);
				if (bPanier[nPlace]){
					for (bEngendre=0,uP=1;uP<=nProduitEnTout(uR);uP++){
						nDebut=nProduitDebuT(uR,uP);
						nFin=nProduitFiN(uR,uP);
						for (int nC=nDebut;nC<=nFin;nC++){
							if ( bMajuscule(sCfG[nC]) ){
								nPlace=sCfG[nC]-'@';
								bPanetiere[nPlace]=1;
								if (mVecteurContient(nPlace,nPile,1,nPile[0])<0){
									//d(nPlace);
									PanierJustifieR(sCfG[nC],mjGauche,nDebut,nFin,bDetailler);
									nPile[++nPile[0]]=nPlace;
									bEngendre=1;
									bBarre=0;
								}
							}
						}
					}
					bPoursuivre=bPoursuivre || bEngendre;
				}
			}//for
			if (!bBarre){
				nPile[++nPile[0]]=0;//séparateur
				bBarre=1;
			}
		}while (bPoursuivre);
if (bDetailler) Flag(0);
	//if (bVoir) ld(yVecteurSomme(bPanier,1,kuRegleMaX));
	if (zdAfficher) CfgListeR("du Start",nPile);
	bPanetiere[0]=kuVocabulaireMaX;
	int bSupprimer=bRegleSupprimeR(bPanetiere,zdAfficher);
	if (zdAfficher)
		CfgVoiR1("grammaire ordonnée",bSupprimer,bDetailler);
}//CfgOrdonneR

void CfgPreordonneR(int zdAfficher){
	//retire de la gramR les règles qui engendrent le langage vide
	const int kbVoir=0;
	int bDetailler=zdAfficher>1;
	int bBarre=0,nC,uR,uP,bPoursuivre,bEngendre,nDebut,nPlace,nFin,nPasse=0,mjGauche;
	int bPanier[1+kuRegleMaX];//bPanier[uMajuscule] vrai ssi le symbole de rg1 uMajuscule est en membre gauche
	int bPanetiere[1+kuRegleMaX],nPile[1+kuRegleMaX];
	if (kbVoir) Appel0("CfgPreordonneR");
		if (zdAfficher) printf("\n1° Préordonner:\n");
		VecteurRaz(bPanetiere,kuRegleMaX);
		nPile[0]=2;nPile[1]='a'-'@';nPile[2]='b'-'@';nPile[++nPile[0]]=0;//séparateur
if (bDetailler) Flag(1);
		do{
			VecteurCopier(bPanetiere,0,kuRegleMaX,bPanier);
			nPasse++;
			for (bPoursuivre=0,uR=1;uR<=nCfgReglE;uR++){
				nDebut=nRegleDebuT(uR);
				mjGauche=sCfG[nDebut];
				nPlace=mjGauche-'@';
				//c(mjGauche);d(nPlace);
				if (!bPanier[nPlace]){
					for (bEngendre=0,uP=1;uP<=nProduitEnTout(uR) && !bEngendre;uP++){
						nDebut=nProduitDebuT(uR,uP);
						nFin=nProduitFiN(uR,uP);
						for (bEngendre=1,nC=nDebut;nC<=nFin && bEngendre;nC++)
							bEngendre=sCfG[nC]=='1' || bMinuscule(sCfG[nC]) || bPanieR(bPanier,sCfG[nC]-'@');
					}
					bPanetiere[nPlace]=bEngendre;
					if (bEngendre){
						PanierJustifieR(mjGauche,mjGauche,nDebut,nFin,bDetailler);
						nPile[++nPile[0]]=nPlace;
						bBarre=0;
					}
					bPoursuivre=bPoursuivre || bEngendre;
				}
			}//for
			if (!bBarre){
				nPile[++nPile[0]]=0;//séparateur
				bBarre=1;
			}
		}while (bPoursuivre);
if (bDetailler) Flag(0);
		//if (bVoir) ld(yVecteurSomme(bPanier,1,kuRegleMaX));
		if (bDetailler) CfgListeR("de l'alphabet",nPile);
		bPanier[0]=kuVocabulaireMaX;
		int bSupprimer=bRegleSupprimeR(bPanier,zdAfficher);
		if (zdAfficher)
			CfgVoiR1("grammaire préordonnée",bSupprimer,bDetailler);
	if (kbVoir) Appel1("CfgPreordonneR");
}//CfgPreordonneR

int bCfgPropreR(const char *ksgrAlgebrique,int bDito,int zdAfficher,char *szgrPropre){
	//génère une szgrPropre équivalente à ksgrAlgebrique, ou affiche un message d'erreur si non défini. 
	Assert1("bCfgProprer",bCroit(0,zdAfficher,2));
	int bProprer=bCfgAlgebriquE(ksgrAlgebrique,!k1Lineaire,zdAfficher);
	if ( bProprer ){
		if (zdAfficher && !bDito)
			CfgVoiR("Grammaire algébrique",!k1Detailler);
		int bDetailler=(zdAfficher>1);
		if (bDetailler) Ligne();
		if (bDetailler) Titrer2("Nettoyage préalable de la grammaire: définir et simplifier",'.');
		CfgGroupeR(zdAfficher);//vital pr préordonner
		CfgEpureR(zdAfficher);
		CfgUnReduirE(zdAfficher);
		CfgIdempoteR(zdAfficher);
		if (bDetailler) Ligne();
		if (bDetailler) Titrer2("Obtention de la grammaire propre",'.');
		CfgPreordonneR(zdAfficher);
		CfgOrdonneR(zdAfficher);
		if (!bCfgMotVidE(zdAfficher)){
			CfgDecycleR(zdAfficher);
			CfgDeformaliseR(zdAfficher);
			//supprimer les règles devenues superflues APRÈS le trait complet de CfgDeformaliseR qui trie topologiQt
				CfgOrdonneR(!k1Afficher);//S->H et H->a donne S->a et la règle H->a peut devenir superflue
		}
		if (zdAfficher>1)
			CfgVoiR("Grammaire propre finale",!k1Detailler);//systématq pour le moment
		if (szgrPropre!=NULL)
			szgrPropre=sChaineCopie(sCfG);
	}
	return(bProprer);
}//bCfgPropreR

int bCfgProprerGreibacheR(const char *ksgrAlgebrique,int bPoursuivre,int bTout,int zdAfficher,char *szgrPropre){
	//génère une szgrPropre équivalente à ksgrAlgebrique, ou affiche un message d'erreur si non défini. 
	int bPropre=bCfgPropreR(ksgrAlgebrique,k1Dito,zdAfficher,szgrPropre);
	if (bPropre && bPoursuivre)
		CfgGreibacheR(ksgrAlgebrique,bPoursuivre,bTout,zdAfficher,NULL);
	return(1);
}//bCfgProprerGreibacheR

int nCfgQuasiGreibachE(int mjRegle){
	//remplace chq récursivité gauche sur mjRegle par la dérivation de mjRegle
	const int kbBaliser=0;
	int nC,nD,nDebut,nFin,mjDroit,mjGauche,nIndirecte,uP,uR,uT,nRegle;
	char sCfg1[kuCfgCaratMaX];
	for (nIndirecte=nD=0,uR=1;uR<=nCfgReglE;uR++){
		nDebut=nRegleDebuT(uR);
		mjGauche=sCfG[nDebut];
		//recopier le début de règle
			for (nC=nDebut;nC<nDebut+3+(sCfG[nDebut+1]=='\'');nC++)
				sCfg1[nD++]=sCfG[nC];
		for (uP=1;uP<=nProduitEnTout(uR);uP++){
			nDebut=nProduitDebuT(uR,uP);
			nFin=nProduitFiN(uR,uP);
			if (sCfG[nDebut]==mjRegle){
				nIndirecte++;
				mjDroit=sCfG[nDebut];
				nRegle=nRegleRanG(mjDroit);
				for (uT=1;uT<=nProduitEnTout(nRegle);uT++){
					for (nC=nProduitDebuT(nRegle,uT);nC<=nProduitFiN(nRegle,uT);nC++)
						sCfg1[nD++]=sCfG[nC];
					if (kbBaliser) sCfg1[nD++]='Y';
					for (nC=nDebut+1;nC<=nFin;nC++)
						sCfg1[nD++]=sCfG[nC];
					if (kbBaliser) sCfg1[nD++]='Z';
					sCfg1[nD++]='+';
				}
			}else {
				for (nC=nDebut;nC<=nFin;nC++)
					sCfg1[nD++]=sCfG[nC];
				sCfg1[nD++]='+';
			}
		}
		sCfg1[nD-1]=';';
	}
	sCfg1[nD]='\0';
	strcpy(sCfG,sCfg1);
	return(nIndirecte);
}//nCfgQuasiGreibachE

void CfgQuasiGreibacheR(int zdAfficher){
	//pr tt non terminal donnant lieu à récursivité à gauche, l'éliminer en 2 étapes: récursivités directes, puis indirectes.
	int nC,nD,nDebut,nFin,mjGauche,uP,cPasse,cTour,uR,nbProduitEnTout,bRecursivitehGauche,nDirecte,nIndirecte;
	int nPile[1+kuVocabulaireMaX];//suffit
	char sCfg1[kuCfgCaratMaX];
	for (uR=1;uR<=nCfgReglE;uR++){
		//if (uR>1) CfgVoiR(">>> Grammaire intermédiaire",!k1Detailler);
		//recopier le début de sCfG
			for (nD=nC=0;nC<nRegleDebuT(uR);nC++)
				sCfg1[nD++]=sCfG[nC];
		mjGauche=cMembreGauchE(uR);
		//nPile:=pile des numéros de produits réordonnée en commençant par ceux qui font un appel récursif à gauche sur mjGauche
			for (nDirecte=nPile[0]=0,nbProduitEnTout=nProduitEnTout(uR),cPasse=0;cPasse<=1;cPasse++)
				for (uP=1;uP<=nbProduitEnTout;uP++){
					nDebut=nProduitDebuT(uR,uP);
					nFin=nProduitFiN(uR,uP);
					bRecursivitehGauche=sCfG[nDebut]==mjGauche && sCfG[nDebut+1]!='\'';
					if (bRecursivitehGauche==(cPasse==0)){
						nPile[++nPile[0]]=uP;
						if (bRecursivitehGauche && cPasse==0)
							nDirecte++;
					}
				}
		//Étape 1: Éliminer la récursivité gauche directe ds la règle courante uR en ajoutant une règle
			if (nDirecte>0)
				for (cTour=0;cTour<=1;cTour++){
					//recopier le début de règle, avec une apostrophe en plus au second tour
						for (nDebut=nProduitDebuT(uR,1),nC=nDebut-3;nC<nDebut;nC++){
							sCfg1[nD++]=sCfG[nC];
							if (cTour && nC==nDebut-3)
								sCfg1[nD++]='\'';
						}
					//générer deux sommes, la première prolongée par mjGauche sur chq sommande. 
						for (cPasse=0;cPasse<=1;cPasse++)
							for (uP=1;uP<=nbProduitEnTout;uP++){
								nDebut=nProduitDebuT(uR,uP);
								nFin=nProduitFiN(uR,uP);
								bRecursivitehGauche=sCfG[nDebut]==mjGauche && sCfG[nDebut+1]!='\'';
								if (bRecursivitehGauche==cTour){
									for (nC=nDebut+cTour;nC<=nFin;nC++)
										sCfg1[nD++]=sCfG[nC];
									if (!cPasse){
										sCfg1[nD++]=mjGauche;
										sCfg1[nD++]='\'';
									}
									sCfg1[nD++]='+';
								}
							}
					sCfg1[nD-1]=';';
				}//cTour
		//recopier la fin de sCfG
			nFin=nRegleDebuT(uR+(nDirecte>0));
			for (nC=nFin;nC<=nRegleFiN(nCfgReglE);nC++)
				sCfg1[nD++]=sCfG[nC];
		if (nDirecte>0) uR++;
		strcpy(sCfG,sCfg1);
		nCfgReglE+=(nDirecte>0);//puisque l'étape 1 ajoute 1 règle
		if (zdAfficher>1)
			if (nDirecte>0)
				CfgVoiR(sC4b(">>> Grammaire après suppression de",sPluriel(nDirecte,"récursivité$ gauche$ directe$"),"dans la règle",sC0(mjGauche)),!k1Detailler);
			else printf("%s>>> Aucune récursivité gauche directe pour la règle %s.\n",sTab0(),sC0(mjGauche));
		//Étape 2: Remplacer la récursivité gauche indirecte à mjGauche sur la totalité de sCfG
			nIndirecte=nCfgQuasiGreibachE(mjGauche);
		if (zdAfficher>1)
			if (nIndirecte>0)
				CfgVoiR(sC5b(">>> Grammaire après suppression de",sPluriel(nIndirecte,"récursivité$ gauche$ indirecte$"),"sur",sC0(mjGauche),"(considérer toutes les règles)"),!k1Detailler);
			else printf("%s>>> Aucune récursivité gauche indirecte pour la règle %s.\n",sTab0(),sC0(mjGauche));
		else CfgVoiR(sC2b("Grammaire après suppression des récursivités gauches directes et indirectes sur",sC0(mjGauche)),!k1Detailler);
	};
	//ds(2,sCfG);
}//CfgQuasiGreibacheR

void CfgReconnaitre(const char *ksgrLineaireAhDroite,int nLettreAuPlus,int idAfficher){
	//Génère l'AEF complet déterministe associé à ksgrLineaireAhDroite et énumère les mots reconnus qui ont nLettreAuPlus. 
	int AEF2[1+26][3];
	int zdAfficher=abs(idAfficher);
	int bDetailler=abs(idAfficher)>1;
	Assert1("CfgReconnaitre",bCroit(0,abs(idAfficher),2) );
	if ( bCfgLineaireAhDroite(ksgrLineaireAhDroite,iSup(0,idAfficher)) ){
		Tabuler(+1);
			CfgVoiR("Grammaire linéaire G",!k1Detailler);
			if (idAfficher>0)
				printf("%sG est linéaire à droite et A={a,b}. Donc les mots engendrés par G peuvent être reconnus par un AEF.\n",sTab0());
			if (bDetailler){
				Flag(1);
					printf("%sLe Start est le seul point d'entrée de G. Donc l'AEF associé à G a un seul état initial: S.\n",sTab0());
					AefTabuleR();//stocke sCfG dans AEF0
				Flag(0);
			}else AefTabuleR();//stocke sCfG dans AEF0
			if (zdAfficher)
				AefVoirSouS(idAfficher,"avant transformation",AEF0);
			int bDejaComplet=bAefCompleteR(idAfficher);
			int bDejaDeterministe=bAefDeterminiseR(idAfficher);//actualise AEF1[0][0][0] 
			int bDito=bDejaComplet && bDejaDeterministe;
			if (zdAfficher)
				if (bDito)
					printf("%sL'AEF, déjà complet et déterministe, ne change pas.\n",sTab0());
				else AefVoirSouS(zdAfficher>1,"déterministe et complet",AEF1);
			if (zdAfficher>0){
				if (bDito)
					CommentE(zdAfficher,"Pour tout état e et toute lettre l, il existe exactement 1 transition (e,l,…)");
				else CommentE(zdAfficher,"Pour tout super-état E et toute lettre l, il existe exactement 1 transition (E,l,…)");
				CommentE(zdAfficher,"Donc à tout mot m de A* correspond exactement un chemin unique d'origine S");
			}
			AefSimplifieR(AEF1,AEF2);
			if (bDetailler) Ligne(); 
			if (bDetailler)
				AefVoiR(sC2b("AEF complet déterministe après renommage", (bDito)? "éventuel des états":"des super-états"),AEF2);
			if (bDetailler) 
				CfgVoiR("Conversion de l'automate de l'AEF en grammaire",!k1Detailler);
			AefReconnaitreTout(AEF2,nLettreAuPlus);
		Tabuler(-1);
	}
}//CfgReconnaitre

void CfgTESTER(int iTest){
	//teste le présent module
	iTest=301;//304
	int zdAfficher=1;
	Appel0(sC2("CfgTESTER,test n°",sEnt(iTest)));
		Assert1("CfgTESTER",bCfgAmorceR);
//d(iTest);
		if (1) switch (iTest) {//tPropre0Quasi1Greibach2
			case 11:bCfgNormaliser("S->aT+a+Tb+b;T->a+b",k1Algebrique,1,zdAfficher,NULL);break;
			case 12:bCfgNormaliser("S->aT+a+Tb+b;T->a+b",k1Algebrique,2,zdAfficher,NULL);break;
			case 13:bCfgNormaliser("S->aT+a+Tb+b;T->a+b",k1Algebrique,3,zdAfficher,NULL);break;
			case 21:bCfgNormaliser("S->aT+a+Tb+b;T->a+b",!k1Algebrique,1,zdAfficher,NULL);break;
			case 22:bCfgNormaliser("S->aT+a+Tb+b;T->a+b",!k1Algebrique,2,zdAfficher,NULL);break;
			case 23:bCfgNormaliser("S->aT+a+Tb+b;T->a+b",!k1Algebrique,3,zdAfficher,NULL);break;

			case 31:bCfgPropreR("S->aT+a+Tb+b;T->a+b",!k1Dito,2,NULL);break;
			case 32:CfgGreibacheR("S->aT+a+Tb+b;T->a+b",!k1Poursuivre,k1Tout,2,NULL);break;
			case 33:bCfgProprerGreibacheR("S->aT+Tb;T->a+b+1+1",k1Poursuivre,k1Tout,2,NULL);break;
			case 40:bCfgPropreR("S->A  aA+MbM + H+CdE +S;A->a+b; H->L;L->a; B->A; A->  1A +R +11 + B+ a  ;K->B + P;R->RR;Q->a",!k1Dito,1,NULL);
					break;
			case 41:bCfgPropreR("S->A;S->aTbT+ ba1b+b+1;T->Z+ZZ+PaP+1+U;U->V+T1T1T+TNTb;V->abW+bWa+WaW;K->PL;T->Ta+N;N->11N111",!k1Dito,2,NULL);
					break;
			case 42:bCfgPropreR("S->aTTaTaT;T->aTbT+1",!k1Dito,k1Afficher+k1Detailler,NULL);
					break;
			case 43:bCfgPropreR("S->aT+Tb;T->a+b+1+1",!k1Dito,k1Afficher,NULL);
					break;
			case 50:CfgComplementer("S->aT+bT+aU;T->aS+1;U->bU+aS+1",0,k1Afficher+k1Detailler,NULL);break;
			case 51:CfgComplementer("S->aT;T->1",k1Afficher+k1Detailler,0,NULL);break;
			case 60:CfgGreibacheR("S->SSa+Tb;T->Sb+Ta+b",!k1Poursuivre,k1Tout,0,NULL);break;

			case 100:CfgReconnaitre("S->aB+bC+1;B->aB+bB+1;C->aD+bE+1;D->aD+bD;E->aD+bE+1",4,2*k1Afficher);break;
			case 101:bCfgLineaireAhDroite("S->1+aV+bV+aA+bA+bB;A->aV;B->bV;V->1",k1Afficher);break;
			case 102:bCfgLineaireAhDroite("S->aT+bT;T->aU+bU;U->aV+bV+aU+bU;V->1",k1Afficher);break;

			case 201:CfgReconnaitre("S->aT;T->bV;V->1",4,k1Afficher+k1Detailler);break;//L=ab
			case 301:CfgComplementer("S->aT;T->bV;V->1",4,k1Afficher+k1Detailler,NULL);break;//L=ab
			default:Assert1("CfgTESTER default",0);
		}
	Appel1(sC2("CfgTESTER,test n°",sEnt(iTest)));
}//CfgTESTER

void CfgUnReduirE(int zdAfficher){
	//réduit le nombre de mots vides pr n'en garder qu'un Au plus
	int nC,nD,nDebut,nFin,uR,uP,bNonVide[100],nDepart,bOperer,bReduction=0,nTermat[100];
	char sCfg1[kuCfgCaratMaX];
	strcpy(sCfg1,sCfG);
		for (nD=0,uR=1;uR<=nCfgReglE;uR++){
			//bNonVide[]:=1 coche par produit distinct du mot vide
				for (uP=1;uP<=nProduitEnTout(uR);uP++){
					nDebut=nProduitDebuT(uR,uP);
					nFin=nProduitFiN(uR,uP);
					nTermat[uP]=nFin-nDebut+1;
					for (bNonVide[uP]=0,nC=nDebut;nC<=nFin &&!bNonVide[uP];nC++)
						bNonVide[uP]=sCfG[nC]!='1';
				}
			//VecteurVoir("bNonVide",bNonVide,1,nProduitEnTout(uR));
			//conserver le début de règle
				for (nDebut=nProduitDebuT(uR,1),nC=nDebut-3;nC<nDebut;nC++)
					sCfg1[nD++]=sCfG[nC];
			//recopier les produits sans les mots vides, sauf si production vide
				for (bOperer=0,uP=1;uP<=nProduitEnTout(uR);uP++){
					if (bOperer)
						sCfg1[nD++]='+';
					if (bNonVide[uP]){//empiler les seuls produits non nuls et les relier par des '+'
						for (nDepart=nD,nC=nProduitDebuT(uR,uP);nC<=nProduitFiN(uR,uP);nC++){
							if (sCfG[nC]!='1')
								sCfg1[nD++]=sCfG[nC];
						}
						bReduction=bReduction || nD-nDepart<nTermat[uP];
					}else sCfg1[nD++]='1';
					bOperer=1;
				}
			sCfg1[nD++]=';';
		}
		sCfg1[nD]='\0';
	strcpy(sCfG,sCfg1);
	if (zdAfficher)
		if (bReduction)
			CfgVoiR("Grammaire à produits simples (1 multiplié par 1 = 1)",zdAfficher>1);
		else CfgVoiR1("grammaire à produits simples",0,zdAfficher>1);
	//if (bVoir) Appel1("CfgUnReduirE");
}//CfgUnReduirE

int bCfgUnSuprimeR(){
	//supprime les occurences des règles vides et ces règles elles-mêmes
	const int kbVoir=0;
	int nC,nDebut,nFin,uR,nTermat,nUn,bProductionVide,bSupprimer;
	//VecteurVoir("nReglE0",nReglE,1,nCfgReglE);
	if (kbVoir) Appel0("bCfgUnSuprimeR");
		for (bSupprimer=0,uR=nCfgReglE;uR>0;uR--){
			nDebut=nRegleDebuT(uR)+3;
			nFin=nRegleFiN(uR);
			nTermat=nFin-nDebut+1;
			//nUn=nb total de 1
				for (nUn=0,nC=nDebut;nC<=nFin;nC++)
					if (sCfG[nC]=='1')
						nUn++;
			bProductionVide=(nTermat==nUn);
			if (!bProductionVide){
				if (nUn){//supprimer ts les 1 ds cette règle
					if (0) d4(uR,nDebut,nFin,nTermat);
					if (0) cd(cMembreGauchE(uR),nUn);
				}
			}else {
				RegleRetireR(uR);
				bSupprimer=1;
			}
		}
		if (bSymboleSupprimeR(-k1Un,!k1Voir))
			bSupprimer=1;
	if (kbVoir) Appel1("bCfgUnSuprimeR");
	return(bSupprimer);
}//bCfgUnSuprimeR

void CfgVoiR(char *sQuoi,int bDetailler){
	int nC,nDebut,bExtension,uR,nProduit;
	//nRegleOu:=nb de règles présentes,de type OU
		for (nProduit=0,uR=1;uR<=nCfgReglE;uR++)
			nProduit+=nProduitEnTout(uR);
	printf("%s%s",sTab0(),sQuoi);
	if (bDetailler) printf(" (%s au sens large, %d au sens strict)",sPluriel(nCfgReglE,"règle"),nProduit);
	printf(":\n");
	Tabuler(+1);
		for (uR=1;uR<=nCfgReglE;uR++){
			nDebut=nRegleDebuT(uR);
			printf("%s%3d: %c",sTab0(),uR,sCfG[nDebut]);
			bExtension=sCfG[nDebut+1]=='\'';
			printf("%c",(bExtension)?'\'':' ');
			for (nC=nDebut+1+bExtension;nC<nDebut+3+bExtension;nC++)
				printf("%c",sCfG[nC]);
			for (printf(" "),nC=nDebut+3+bExtension;nC<nRegleFiN(uR)-1 || bPrint("");nC++)
				printf("%c",sCfG[nC]);
		}
	Tabuler(-1);
}//CfgVoiR

void CfgVoiR1(char *sQuoi,int bChange,int bDetailler){
	if (bChange)
		CfgVoiR(sPhrase0(sQuoi),bDetailler);
	else printf("%sLa %s est identique à la précédente.\n",sTab0(),sQuoi);
}//CfgVoiR1

void CommentE(int zdAfficher,char *sQuoi){
	if (zdAfficher>1){
		Flag(1);
			printf("%s%s%s.\n",sE(20),sTab0(),sQuoi);
		Flag(0);
	}
}//CommentE

char cMembreGauchE(int uRegle){
	int nIndex=nRegleDebuT(uRegle);
	char cGauche=sCfG[nIndex];
	Assert1("cMembreGauchE",bMajuscule(cGauche));
	return(cGauche);
}//cMembreGauchE

void MotVideSupprimeR(int bPanier[],int zdAfficher){
	//remplace partout V par V+1, développer puis retire le mot vide ds ttes les règles
	int nAjout,nTermat,bMotVide,nMotVide,nVariante,uP,uR,nDebut,nFin,nC,nD;
	int bDetailler=(zdAfficher>1);
	//CfgVoiR("AVANT MotVideSupprimeR",-,!k1Voir);
	//VecteurVoir10("bPanier AVANT MotVideSupprimeR",bPanier,1,kuRegleMaX);
	char sCfg1[kuCfgCaratMaX];
	strcpy(sCfg1,sCfG);
	//VecteurVoir("bPanier",bPanier,1,kuVocabulaireMaX);
	if (bDetailler) {Flag(1);Tabuler(-1);}
	//remplacer partout V par V+1
		int nRegleEnTout=nCfgReglE;
		for (nD=0,uR=1;uR<=nRegleEnTout;uR++){
			//recopier le début de règle
				for (nDebut=nProduitDebuT(uR,1),nC=nDebut-3;nC<nDebut;nC++)
					sCfg1[nD++]=sCfG[nC];
			for (uP=1;uP<=nProduitEnTout(uR);uP++){
				nDebut=nProduitDebuT(uR,uP);
				nFin=nProduitFiN(uR,uP);
				nTermat=nFin-nDebut+1;
				//d3(uR,uP,nTermat);
				int bGrille[1+nTermat];
				int bFiltre[1+nTermat];
				VecteurRazer(bGrille,1,nTermat);
				for (nMotVide=0,nC=nDebut;nC<=nFin;nC++){
					bMotVide=bPanieR(bPanier,sCfG[nC]-'@');
					bGrille[1+nC-nDebut]=bMotVide;
					nMotVide+=bMotVide;
				}
				//empiler zPuissance(2,nMotVide) produits filtrés du produit (uR,uP)
					for (nAjout=zPuissance(2,nMotVide),nVariante=0;nVariante<nAjout;nVariante++){
						//bFiltre:=un filtre unique caractéristique de nVariante
							VecteurCopier(bGrille,1,nTermat,bFiltre);
							for (int nT=0,nV=nVariante,uBit=1;uBit<=nMotVide;uBit++){
								do
									nT++;
								while(!bGrille[nT]);
								bFiltre[nT]=nV%2;
								nV=nV/2;
							}
						//empiler le produit filtré	
							for (nC=nDebut;nC<=nFin;nC++)
								sCfg1[nD++]=(bFiltre[nC-nDebut+1])? '1' : sCfG[nC];
						if (uP<nProduitEnTout(uR) || nVariante+1<nAjout)
							sCfg1[nD++]='+';
					}
			}
			sCfg1[nD++]=';';
		}//for
	if (bDetailler) {Flag(0);Tabuler(+1);}
	//if (bVoir) CfgVoiR("après remplacement de V par V+1 et développement",!k1Voir);
	strcpy(sCfG,sCfg1);
	if (zdAfficher)
		CfgVoiR("Après remplacement de V par V+1 (V étant une production vide) et développement",bDetailler);
}//MotVideSupprimeR

int bPanieR(int bPanier[],int nLieu){
	int bDans=bCroit(1,nLieu,kuVocabulaireMaX) && bPanier[nLieu];
	return(bDans);
}//bPanieR

void PanierJustifieR(int c1,int c2,int nDebut,int nFin,int bVoir){
	if (bVoir)
		printf("%sAjout de %c grâce à %c->%s.\n",sTab0(),c1,c2,sChainon(sCfG,nDebut,nFin));
}//PanierJustifieR

int nProduitDebuT(int uRegle,int uProduit){
	//rend le rg0 du premier caractère du produit uProduit dans uRegle
	int nC,nDebut,nPlus;
	nDebut=nRegleDebuT(uRegle)+2;
	for (nPlus=0,nC=nDebut;nC<nRegleFiN(uRegle);nC++){
		nPlus+=(sCfG[nC]=='>') || (sCfG[nC]=='+');
		if (nPlus==uProduit){
			nDebut=nC+1;
			break;
		}
	}
	return(nDebut);
}//nProduitDebuT

int nProduitEnTout(int uRegle){
	int nC,nProduitEnTout=0;
	for (nProduitEnTout=1,nC=nRegleDebuT(uRegle);nC<nRegleFiN(uRegle);nC++){
		nProduitEnTout+=(sCfG[nC]=='+');
	}
	//d2(uRegle,nProduitEnTout);
	return(nProduitEnTout);
}//nProduitEnTout

int nProduitFiN(int uRegle,int uProduit){
	//rend le rg0 du premier caractère du produit uProduit dans uRegle
	int nC,nDebut,nFin,nPlus;
	nDebut=nRegleDebuT(uRegle)+2;
	nFin=nRegleFiN(uRegle);
	//d4(uRegle,uProduit,nDebut,nFin);
	for (nFin=nPlus=0,nC=nDebut;nC<nRegleFiN(uRegle) && !nFin;nC++){
		nPlus+=(sCfG[nC]=='>') || (sCfG[nC]=='+') || (sCfG[nC]==';');
		//cd(sCfG[nC],nPlus);
		if (nPlus>uProduit)
			nFin=nC-1;
	}
	//d2(nFin,nFin);
	return(nFin);
}//nProduitFiN

int nRegleCopieR(int uR,int nOffset,int uT){
	int nCar,nCarEnTout;
	int nDebut=nRegleDebuT(uR)+nOffset;
	int nFin=nRegleFiN(uR);
	nCarEnTout=nFin-nDebut;
	int nBut=nRegleFiN(nCfgReglE);
	//d3(nDebut,nBut,nCarEnTout);
	for (nCar=0;nCar<nCarEnTout;nCar++)
		sCfG[nBut+nCar]=sCfG[nDebut+nCar];
	int nDernier=nBut+nCarEnTout-1;
	sCfG[nDernier]=';';
	sCfG[nDernier+1]='\0';
	return(nDernier);
}//nRegleCopieR

int nRegleDebuT(int uRegle){
	//rend le rg0 du premier caractère de uRegle
	int nDebut,nSeparateur;
	for (nSeparateur=1,nDebut=0;nDebut<nChaineLg(sCfG) && nSeparateur<uRegle;nDebut++)
		nSeparateur+=(sCfG[nDebut]==';');
	return(nDebut);
}//nRegleDebuT

void RegleDeriveR(int uRegle,int uProduit){
	//remplace le produit (uRegle,uProduit) par sa dérivation
	int nC,nD,nDerive,uR,uP,uT,nDebut,nFin,cGauche,bOperer;
	char sCfg1[kuCfgCaratMaX];
	for (nD=0,uR=1;uR<=nCfgReglE;uR++){
		//recopier le début de règle
			for (nDebut=nRegleDebuT(uR),nC=nDebut;nC<nDebut+3;nC++)
				sCfg1[nD++]=sCfG[nC];
		for (bOperer=0,uP=1;uP<=nProduitEnTout(uR);uP++){
			if (bOperer){
				sCfg1[nD++]='+';
				bOperer=0;
			}
			nDebut=nProduitDebuT(uR,uP);
			nFin=nProduitFiN(uR,uP);
			if (uRegle==uR && uProduit==uP){
				Assert1("RegleDeriveR0",nDebut==nFin);
				cGauche=sCfG[nDebut];
				//nDerive:=rg1 de la règle à remplacer par sa dérivation
					for (nDerive=0,uT=1;uT<=nCfgReglE;uT++)
						if (cGauche==sCfG[nRegleDebuT(uT)])
							nDerive=uT;
					Assert1("RegleDeriveR1",nDerive>0);
				nDebut=nRegleDebuT(nDerive)+3;
				nFin=nRegleFiN(nDerive)-2;
			};
			for (nC=nDebut;nC<=nFin;nC++)
				sCfg1[nD++]=sCfG[nC];
			bOperer=1;
		}
		sCfg1[nD++]=';';
	}
	sCfg1[nD]='\0';
	strcpy(sCfG,sCfg1);
}//RegleDeriveR

int nRegleFiN(int uRegle){
	//rend le rg0 du dernier caractère de uRegle; c'est un séparateur.
	int nFin=nRegleDebuT(uRegle+1);
	return(nFin);
}//nRegleFiN

void RegleFusionneR(int uR,int uT){
	int nFin;
	//empiler une nouvelle règle qui somme les règles uR et uT
		nFin=nRegleCopieR(uR,0,nCfgReglE);
		sCfG[nFin]='+';
		nCfgReglE++;
		nFin=nRegleCopieR(uT,3,nCfgReglE);
	//retirer les règles uR et uT
		Assert1("RegleFusionneR",uR>uT);//z
		RegleRetireR(uR);
		RegleRetireR(uT);
}//RegleFusionneR

int nRegleRanG(int mjDroit){
	int nDebut,nRang,uR;
	for (nRang=0,uR=1;nDebut=nRegleDebuT(uR),uR<=nCfgReglE && !nRang;uR++)
		if (sCfG[nDebut]==mjDroit && sCfG[nDebut+1]=='-')
			nRang=uR;
	Assert1("nRegleRanG",nRang);
	return(nRang);
}//nRegleRanG

void RegleRetireR(int uRegle){
	int nDebut=nRegleDebuT(uRegle);
	int nFin=nRegleFiN(uRegle);
	int nCarEnTout=nRegleFiN(nCfgReglE)-nRegleFiN(uRegle);
	for (int nCar=0;nCar<=nCarEnTout;nCar++)
		sCfG[nDebut+nCar]=sCfG[nFin+nCar];
	nCfgReglE--;
	//ds(2,sCfG);
}//RegleRetireR

int bRegleSupprimeR(int bPanier[],int zdAfficher){
	//supprime les règles hors bPanier[] et leurs occurrences ds les membres droits des règles
	//appels:CfgOrdonneR et CfgPreordonneR
	const int kbVoir=0;
	int nC,nD,uR,nLieu,uP,nDebut,nFin,bOperer,nGauche;
	int nPile[1+kuRegleMaX];
	int bProduit[100];
	if (kbVoir) Appel0("bRegleSupprimeR");
		//VecteurVoir("bPanier",bPanier,1,bPanier[0]);
		//supprimer les règles hors bPanier[]
			for (nPile[0]=0,uR=nCfgReglE;uR>0;uR--){
				nGauche=nRegleDebuT(uR);
				nLieu=sCfG[nGauche]-'@';
				if (!bPanier[nLieu]){
					nPile[++nPile[0]]=nLieu+'@';
					RegleRetireR(uR);
				}
			}
		//CfgVoiR("hors bPanier",!k1Voir);
	char sCfg1[kuCfgCaratMaX];
	strcpy(sCfg1,sCfG);
		//supprimer leurs occurrences ds les membres droits des règles
			for (nD=0,uR=1;uR<=nCfgReglE;uR++){
				VecteurValuer(bProduit,1,nProduitEnTout(uR),1);
				for (uP=1;uP<=nProduitEnTout(uR);uP++){
					nDebut=nProduitDebuT(uR,uP);
					nFin=nProduitFiN(uR,uP);
					for (nC=nDebut;nC<=nFin && bProduit[uP];nC++){
						nLieu=sCfG[nC]-'@';
						if (bCroit(1,nLieu,kuVocabulaireMaX) && bPanier[nLieu]==0){
							bProduit[uP]=0;
							//d2(nLieu,bProduit[uP]);
						}
					}
				}
				//VecteurVoir("nProduit",bProduit,1,nProduitEnTout(uR));
				//recopier le début de règle
					for (nDebut=nProduitDebuT(uR,1),nC=nDebut-3;nC<nDebut;nC++)
						sCfg1[nD++]=sCfG[nC];
				//empiler les seuls produits non nuls et les relier par des '+'
					for (bOperer=0,uP=1;uP<=nProduitEnTout(uR);uP++)
						if (bProduit[uP]){
							if (bOperer){
								sCfg1[nD++]='+';
								bOperer=0;
							}
							for (nC=nProduitDebuT(uR,uP);nC<=nProduitFiN(uR,uP);nC++)
								sCfg1[nD++]=sCfG[nC];
							bOperer=1;
						}
				sCfg1[nD++]=';';
			}
	sCfg1[nD]='\0';
	strcpy(sCfG,sCfg1);
	int bSupprimer=nPile[0]>0;
	if (1)
		if (bSupprimer){
			for (printf("%sSuppression %s ",sTab0(),(nPile[0]==1)? "de la règle":"des règles"),uP=1;uP<=nPile[0] || bPrint(".");uP++)
				printf("%c%s",nPile[uP],sEtc(uP,nPile[0]));
		}else if (zdAfficher>1)
			printf("%sAucune règle n'est supprimée.\n",sTab0());
	if (kbVoir) Appel1("bRegleSupprimeR");
	return(bSupprimer);
}//bRegleSupprimeR

int nSuperEtaT(int uLigne,int uColonne,int uAef3LigneMax){
	//vrai ssi l'état (uLigne,uColonne) n'est pas un super état qui figure en colonne 0
	int uL,uK,nSuperEtat=0,bConnu;
	for (uL=1;uL<=uAef3LigneMax && !nSuperEtat;uL++){
		for (bConnu=uK=1;uK<=kuAefKolonneMaX;uK++)
			bConnu=bConnu && AEF1[uL][uK][0]==AEF1[uLigne][uK][uColonne];
		if (bConnu)
			nSuperEtat=uL;
	}
	return(nSuperEtat);
}//nSuperEtaT

void SymboleRenommeR(int mjAvant,int mjApres,int bVoir){
	//if (bVoir) cc(mjAvant,mjApres);
	for (int nC=0;nC<=nChaineLg(sCfG);nC++)
		if (sCfG[nC]==mjAvant)
			sCfG[nC]=mjApres;
}//SymboleRenommeR

int bSymboleSupprimeR(int mArcEnToutSinonMoinsUn,int bVoir){
	//supprime, selon bUnSinonBoucle, soit ts les 1, soit ttes les boucles
	int uB,nC,nD,nDebut,bEnTrop,nFin,bOperer,uP,uR,bSupprimer=0;
	int nBoucle[1+kuVocabulaireMaX];
	char sCfg1[kuCfgCaratMaX],cEnTrop='1';
	//Appel0("bSymboleSupprimeR");
		//ds(0,sCfG);
			for (VecteurRaz(nBoucle,kuVocabulaireMaX),nD=0,uR=1;uR<=nCfgReglE;uR++){
				//recopier le début de règle
					for (nDebut=nRegleDebuT(uR),nC=nDebut;nC<nDebut+3;nC++)
						sCfg1[nD++]=sCfG[nC];
				cEnTrop=(mArcEnToutSinonMoinsUn<0)? '1': sCfG[nDebut];
				for (bOperer=0,uP=1;uP<=nProduitEnTout(uR);uP++){
					nDebut=nProduitDebuT(uR,uP);
					nFin=nProduitFiN(uR,uP);
					bEnTrop=nDebut==nFin && sCfG[nDebut]==cEnTrop;
					if (bOperer && !bEnTrop){
						sCfg1[nD++]='+';
						bOperer=0;
					}
					if (!bEnTrop)
						for (nC=nDebut;nC<=nFin;nC++){
							sCfg1[nD++]=sCfG[nC];
							bOperer=1;
						}
					else nBoucle[sCfG[nDebut]-'@']=bSupprimer=1;
				}
				sCfg1[nD++]=';';
			}
			sCfg1[nD]='\0';
			strcpy(sCfG,sCfg1);
		for (nBoucle[0]=yVecteurSomme(nBoucle,1,kuVocabulaireMaX),uB=1;uB<=kuVocabulaireMaX;uB++)
			nBoucle[uB]*='@'+uB;
		bSupprimer=bSupprimer || nBoucle[0]>0;
		VecteurTasser(nBoucle,1,kuVocabulaireMaX);
		if (bVoir){
			Tabuler(-1);
				//VecteurVoir0("nBoucle",nBoucle);
				if (nBoucle[0]>0){
					printf("%sSuppression %s sur ",sTab0(),(nBoucle[0]>1)? "des boucles":"d'une boucle");
					ModeCaractere(1);
						for (uB=1;uB<=nBoucle[0] || bPrint(".");uB++)
							printf("%c%s",nBoucle[uB],sEtc(uB,nBoucle[0]));
					ModeCaractere(-1);
				}else if (!bSupprimer)
					if (mArcEnToutSinonMoinsUn>0)
						printf("%sAucune boucle à supprimer.\n",sTab0());
					//else printf("%sAucune règle vide à supprimer.\n",sTab0());
			Tabuler(+1);
		}
		//ds(1,sCfG);
	//Appel1("bSymboleSupprimeR");
	return(bSupprimer);
}//bSymboleSupprimeR

