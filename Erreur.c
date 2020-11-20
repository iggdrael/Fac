#include "Kit.h"
#include "Erreur.h"
#include "Alex.h"
#define knPileMaX kE2
enum niErreuR		 {niAlphA,niGramAlgbQ,niGrafiquE,niPlanR,niLexicaL,niSyntaxiquE,niSemantiquE,niOmegA};
const char *ksErreuR="niAlphA,niGramAlgbQ,niGrafiquE,niPlanR,niLexical,niSyntaxiquE,niSemantiquE,niOmegA";
int bErreurAmorceR=kF;
int ipErreuR;//ip = index de pile
struct{int eBug;int uLxm;} nPilE[1+knPileMaX];

void ErreurAfficheR(const char *szCodeSource,int ipErreur);
int nErreurNiveaU(int ipErreur);

void ErreurAfficheR(const char *szCodeSource,int ipErreur){
	//affiche en clair l'erreur numéro ipErreur;ip = index de pile
	Assert1("ErreurAfficheR",bCroit(1,ipErreur,knPileMaX));
	char *sErreur="erreur système";//signifie que votre compilateur se plante
	int bCompil=!bDans3(nErreurNiveaU(ipErreur),niGramAlgbQ,niGrafiquE,niPlanR);
	if (bCompil)
		AlexDenoncer(nPilE[ipErreur].uLxm);//affiche le n° de ligne et la lexie incriminée
	switch (nPilE[ipErreur].eBug) {
		case  eAlexInconnu:	    sErreur="lexème inconnu";break;
		case  eAlexEntier:	    sErreur="lexème inconnu;si entier basé, le format est ([0..b-1]+)'b, en appelant b la base,0<b<10";break;
		case  eAlexMotClef:	    sErreur="lexème inconnu;si mot-clef,il y a une erreur dans son libellé";break;
		case  eAlexReel:	    sErreur="lexème inconnu;si réel, 1 seul point entre parties entière et fractionnaire,eg \"0.0\"";break;
		
		case  eCfg1Fleche:		sErreur="1 seule flèche par règle";break;
		case  eCfg2Fleche:		sErreur="flèche non dissociée attendue";break;
		case  eCfgLineaire:		sErreur="règle linéaire à droite attendue dans A={a,b}: soit V->aV,soit V->bV, soit V->1.";break;
		case  eCfgGauche:		sErreur="la flèche doit suivre immédiatement un non terminal";break;
		case  eCfgInconnu:		sErreur="symbole non valide";break;
		case  eCfgOperande:		sErreur="opérande attendu";break;
		case  eCfgSomme:		sErreur="opérateurs consécutifs";break;

		case  eGrafBcle:		sErreur="boucle interdite";break;
		case  eGrafDecit:		sErreur="la question ne commence pas par un signe facultatif suivi d'un décit";break;
		case  eGrafDito:		sErreur="arc redondant";break;
		case  eGrafEpars:		sErreur="sommets non consécutifs";break;
		case  eGrafItem:		sErreur="Graphe { {,Arc},Arete } attendu; les 2 items facultatifs contiennent chacun 2 sommets";break;
		case  eGrafPoids:		sErreur="poids attendu (un ou plusieurs décits)";break;
		case  eGrafPositif:		sErreur="poids positif ou nul attendu";break;
		case  eGrafSommet:		sErreur="sommet attendu";break;
		case  eGrafSymbole:		sErreur="lettre ou chiffre attendus";break;
		case  eGrafQuestion:	sErreur="question non connue";break;
		case  eGrafZero:		sErreur="le poids d'un arc non paramétré ne peut pas commencer par un 0";break;

		case  ePlnrK5K33:		sErreur="K5 ou K33 attendu à la fin de la question";break;
		case  ePlnrReduc:		sErreur="Paire de sommets terminée par ':' attendue";break;
		case  ePlnrSommet:		sErreur="Sommet du graphe attendu";break;
		case  ePlnrSym:			sErreur="Graphe non orienté attendu";break;

		case  eSyntCalcuL:		sErreur="somme ou produit ou terme attendu";break;
		case  eSyntEtat:		sErreur="achat ou stock attendu";break;
		case  eSyntInstruction:	sErreur="instruction attendue";break;
		case  eSyntLivre:		sErreur="livre attendu (type texte,ni blanc ni apostrophe ni trait d'union)";break;
		case  eSyntNom:			sErreur="nom attendu (type identificateur)";break;
		case  eSyntProgramme:	sErreur="instruction ou fin de fichier attendue";break;
		case  eSyntSeparateur:	sErreur="séparateur attendu (ajouter le symbole \";\")";break;
		case  eSyntSuite:		sErreur="inscription ou interdiction attendue";break;

		case  eSemAffichage:	sErreur="identifiant inconnu";break;
		case  eSemAffectation:	sErreur="nom attendu pour affectation";break;
		case  eSemDate:			sErreur="date attendue (au format JJMMAA)";break;
		case  eSemDelaiTropLong:sErreur="délai d'interdiction limité à 99 jours maximum";break;//*********************************
		case  eSemDoublon:		sErreur="ce livre est déjà présent en bibliothèque";break;
		case  eSemHoraire:		sErreur="horaire au format \"hh.mm\" avec 0≤h≤23 et 0≤mm≤59 attendu";break;
		case  eSemIdentifiant:	sErreur="identifiant sans valeur affectée";break;
		case  eSemLivreDispo:   sErreur="ce livre est actuellement disponible, le réserver est inutile";break;
		case  eSemInscrit:		sErreur="personne déjà inscrite";break;
		case  eSemLivreInconnu:	sErreur="le livre cité est inconnu";break;
		case  eSemLivrePris:	sErreur="ce livre existe mais il ne peut pas être emprunté car il est déjà pris";break;
		case  eSemNonInscrit:	sErreur="personne non inscrite";break;
		case  eSemPrix:			sErreur="prix NON NUL attendu";break;
		case eSyntTerme:		sErreur="terme attendu,ie entier ou expression";break;
		default:break;
	}
	if (!bCompil){
		printf("%s%s dans ",flag,sPhrase0(sErreur));
		//sd(szCodeSource,nPilE[ipErreur].uLxm);
		printf("%s.\n",sG(sC3(sChainon0(szCodeSource,nPilE[ipErreur].uLxm),"[?]",sChainon1(szCodeSource,nPilE[ipErreur].uLxm+1))));
	}else printf(": %s(niveau %s).",sPhrase0(sErreur),sItem(ksErreuR,nErreurNiveaU(ipErreur)));
}//ErreurAfficheR

void ErreurAfficher(const int uLigne){
	//affiche le libellé de toutes les erreurs détectées sur la ligne uLigne
	int ipErreur;
	for (ipErreur=1;ipErreur<=ipErreuR;ipErreur++)
		if (nAlexLigne(nPilE[ipErreur].uLxm)==uLigne)
			ErreurAfficheR("",ipErreur);
}//ErreurAfficher

void ErreurAfficherTout(const char *szCodeSource){
	//affiche à la console les erreurs éventuelles empilées pendant la compilation
	int ipErreur;
	if (szCodeSource!=NULL)
	Assert2("ErreurAfficherTout",bErreurAmorceR,ipErreuR>=0);
	for (ipErreur=1;ipErreur<=ipErreuR;ipErreur++)
		ErreurAfficheR(szCodeSource,ipErreur);
	Ligne();
}//ErreurAfficherTout

void ErreurAMORCER(){
	//amorce le présent module une fois pour toutes
	ipErreuR=0;
	//ds le type énuméré eErreur, vérifier que les balises sont présentes et bien placées
		Assert1("ErreurAMORCER1",bCroitStrict8(eLimite0,eAlex0,eAlex1,eCfg0,eCfg1,eGraf0,eGraf1,ePlnr0));
		Assert1("ErreurAMORCER2",bCroitStrict8(eGraf1,ePlnr0,ePlnr1,eSem0,eSem1,eSynt0,eSynt1,eLimite1));
		Assert5("ErreurAMORCER3",eLimite0+1==eAlex0,eAlex1+1==eCfg0,eCfg1+1==eGraf0,eGraf1+1==ePlnr0,ePlnr1+1==eSem0);
		Assert2("ErreurAMORCER4",eSem1+1==eSynt0,eSynt1+1==eLimite1);
		//s("Le module ERREUR a été amorcé");
	bErreurAmorceR=kV;
}//ErreurAMORCER

void ErreurDeclarer(const int bAffirmation,const int nPlnrErreur,const int iCaractereRg,int *pbValide){
	//dédié ePlnr0..ePlnr1; si pbValide et bAffirmation faux, empile le nPlnrErreur et négative pbValide 
	Assert3("ErreurDeclarer3",bErreurAmorceR,bBool(bAffirmation),bCroitStrict(ePlnr0,nPlnrErreur,ePlnr1));
	if (*pbValide && !bAffirmation){
		*pbValide=0;
		ipErreuR++;
		Assert1("ErreurDeclarer4",ipErreuR<knPileMaX);
		nPilE[ipErreuR].eBug=nPlnrErreur;
		nPilE[ipErreuR].uLxm=iSup(0,iCaractereRg);
		Assert1("ErreurDeclarer5",nErreurNiveaU(ipErreuR)==niPlanR);
	}
}//ErreurDeclarer

void ErreurDenoncer(const int bAffirmation,const int grfErreur,const int iCaractereRg,int *pbValide){
	//dédié eGraf0..eGraf1; si pbValide et bAffirmation faux, empile le nGrafErreur et négative pbValide 
	//Assert3("ErreurDenoncer3",bErreurAmorceR,bBool(bAffirmation),bCroitStrict(eGraf0,grfErreur,eGraf1));
	if (*pbValide && !bAffirmation){
		*pbValide=0;
		ipErreuR++;
		Assert1("ErreurDenoncer4",ipErreuR<knPileMaX);
		nPilE[ipErreuR].eBug=grfErreur;
		nPilE[ipErreuR].uLxm=iSup(0,iCaractereRg);
		Assert1("ErreurDenoncer5",nErreurNiveaU(ipErreuR)==niGrafiquE);
	}
}//ErreurDenoncer

void ErreurDetecter(const int bAffirmation,const int cfgErreur,const int iCaractereRg,int *pbValide){
	//dédié eCfg0..eCfg1; si pbValide et bAffirmation faux, empile le cfgErreur et négative pbValide 
	//Assert3("ErreurDetecter3",bErreurAmorceR,bBool(bAffirmation),bCroitStrict(eCfg0,grfErreur,eCfg1));
	if (*pbValide && !bAffirmation){
		*pbValide=0;
		ipErreuR++;
		Assert1("ErreurDetecter4",ipErreuR<knPileMaX);
		nPilE[ipErreuR].eBug=cfgErreur;
		nPilE[ipErreuR].uLxm=iSup(0,iCaractereRg);
		Assert1("ErreurDetecter5",nErreurNiveaU(ipErreuR)==niGramAlgbQ);
	}
}//ErreurDenoncer

void ErreurEmpiler(const int nErreurNumero,const int nLexeme){
	//empile le nErreurNumero et le nLexeme où l'erreur a été détectée (donc l'erreur concerne ce lexème ou l'un de ses prédécesseurs) 
	Assert3("ErreurEmpiler1",bErreurAmorceR,bCroitStrict(eLimite0,nErreurNumero,eLimite1),bAlexLexeme(nLexeme));
	ipErreuR++;
	Assert1("ErreurEmpiler2",ipErreuR<knPileMaX);
	nPilE[ipErreuR].eBug=nErreurNumero;
	nPilE[ipErreuR].uLxm=nLexeme;
	Assert1("ErreurEmpiler3",bCroit(niLexicaL,nErreurNiveaU(ipErreuR),niSemantiquE));
}//ErreurEmpiler

int bErreurEmpiler(const int nErreurNumero,const int nLexeme){
	//empile le nErreurNumero et le nLexeme où l'erreur a été détectée (donc l'erreur est sur ce lexème ou avant celui-ci) 
	ErreurEmpiler(nErreurNumero,nLexeme);
	return(1);
}//bErreurEmpiler

int nErreurEnTout(){
	Assert2("nErreurEnTout",bErreurAmorceR,ipErreuR>=0);
	return(ipErreuR);
}//nErreurEnTout

int nErreurNiveaU(int ipErreur){
	int nNiveau=niAlphA;
	if ( bCroitStrict(eCfg0,nPilE[ipErreur].eBug,eCfg1) )
		nNiveau=niGramAlgbQ;
	if ( bCroitStrict(eGraf0,nPilE[ipErreur].eBug,eGraf1) )
		nNiveau=niGrafiquE;
	if ( bCroitStrict(ePlnr0,nPilE[ipErreur].eBug,ePlnr1) )
		nNiveau=niPlanR;
	if ( bCroitStrict(eAlex0,nPilE[ipErreur].eBug,eAlex1) )
		nNiveau=niLexicaL;
	if ( bCroitStrict(eSynt0,nPilE[ipErreur].eBug,eSynt1) )
		nNiveau=niSyntaxiquE;
	if ( bCroitStrict(eSem0,nPilE[ipErreur].eBug,eSem1) )
		nNiveau=niSemantiquE;
	return(nNiveau);
}//nErreurNiveaU

void ErreurTESTER(int iTest){
	//teste le présent module
	Appel0(sC2("ErreurTESTER,test n°",sEnt(iTest)));
		Assert1("ErreurTESTER",bErreurAmorceR);
		switch (iTest) {
			case  1:	break;
			default:break;
		}
	Appel1(sC2("ErreurTESTER,test n°",sEnt(iTest)));
}//ErreurTESTER
