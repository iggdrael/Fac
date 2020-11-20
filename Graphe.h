#define knGrapheCouleurMax 9
#define kuGrapheSommetLim 32//360 frontiere8
#define kuGrapheArcLim (kuGrapheSommetLim*kuGrapheSommetLim)
//genre de pondération 
#define gpAlpha		k2E2
#define gpCapaMax	k2E3
#define gpCapaMin	k2E4
#define gpCouleur	k2E5
#define gpCout		k2E6
#define gpPoids		k2E7
#define gpPhi		k2E8
#define gpZeta		k2E9
#define GrapheNom  "grAlpha,gr2Aile,grB,gr2Croix,gr2Diam,gr2P,grC,grC4b,grD,grE2,grE3,grH,grK,grL4,grP,grPt,grPtr,grQ0,grQ1,grS,grT,grT2,grU,grW,grXor,grX,grXX,grXY,grY,grOmega"
#define GrapheType {grAlpha,gr2Aile,grB,gr2Croix,gr2Diam,gr2P,grC,grC4b,grD,grE2,grE3,grH,grK,grL4,grP,grPt,grPtr,grQ0,grQ1,grS,grT,grT2,grU,grW,grXor,grX,grXX,grXY,grY,grOmega}
enum eGrapheOrientation    {goAlpha,goMixte,goOrienteh,goNonOrienteh,goOmega};
#define sGrapheOrientation "goAlpha,goMixte,goOrienteh,goNonOrienteh,goOmega"
typedef struct{
	int nSommetEnTout;
	int nArcEnTout;
	int aHed[kuGrapheSommetLim];//numéros d'arcs
	int sSuk[kuGrapheArcLim];//sommet destination de l'arc courant
	int aDeh[kuGrapheSommetLim];//numéros d'arcs ds le graphe inverse
	int sKus[kuGrapheArcLim];//sommet origine de l'arc courant;ATTENTION: a=(X,Y) et sSuk[a]=Y n'implique pas sKus[a]=X.
	int aInv[kuGrapheArcLim];//arc inverse aL associé à l'arc direct aK
	int nCapaMax[kuGrapheArcLim];//capacité maximale de l'arc courant
	int nCapaMin[kuGrapheArcLim];//capacité maximale de l'arc courant
	int nCout[kuGrapheArcLim];//poids ou coût n°1 associé à l'arc courant
	int nPoids[kuGrapheArcLim];//poids ou coût n°2 associé à l'arc courant
	int aArcTo[kuGrapheArcLim];
	int nAugVal[kuGrapheArcLim];
	int coulh[kuGrapheArcLim];
	int sPer[kuGrapheSommetLim];
	int nPhi[kuGrapheArcLim];//disponible
	int nVal[kuGrapheArcLim];//disponible
} graf;
int bGraphe(graf *pgG);//O(A)
char *sGraphe(int tGrapheType);//rend le nom du graphe de type tGrapheType,cf GrapheNom et GrapheType plus haut
void GrapheAMORCER();
int nGrapheApparier(int nGenreDePoids,graf **ppgG);//O(A)
int bGrapheArc(graf *pgG,int sOrigine,int sDestination);//O(S)
int nGrapheArc(graf *pgG,int sOrigine,int sDestination);//O(S)
char *sGrapheArc(graf *pgG,int aArcNumero);//O(S) //rend un couple,eg (X,Y)
void GrapheAntisymetriser(graf *pgG);//O(A)
void GrapheAreter(graf *pgG,int sOrigine,int sDestination);//O(A)
void GrapheAreter0(graf *pgG,int sOrigine,int sDestination,int nGenreDePoids,int iPoidsSurArc);//O(A)
void GrapheAreter1(graf *pgG,int sOrigine,int sDestination,int nCouleur);//O(A)
void GrapheAreter2(graf *pgG,int sOrigine,int sDestination,int nCouleurDirecte,int nCouleurInverse);//O(A)
void GrapheArquer(graf *pgG,int sOrigine,int sDestination);//O(A);ajoute, ou déroute si déjà présent
void GrapheArquer0(graf *pgG,int sOrigine,int sDestination,int nGenreDePoids,int iPoidsSurArc);//O(A)
void GrapheArquer1(graf *pgG,int sOrigine,int sDestination);//O(A);ajoute si absent
void GrapheArquer2(graf *pgG,int sOrigine,int sDestination,int nCouleurDirecte,int nCouleurInverse);//O(A)
void GrapheArquer3(graf *pgG,int sOrigine,int sDestination,int nCapaMin,int nCapaMax,int nCout);//O(A)
void GrapheArquer4(graf *pgG,int sOrigine,int sDestination,int nCouleur,int nPoids);//O(A)
int bGrapheBiparti(graf *pgG,int idAfficher);//O(A)
int bGrapheBipartiOuAfficherCycleImpair(graf *pgG);//O(A)
int bGrapheBipartition(graf *pgG,int sEnsembleX[],int sEnsembleY[]);//O(A)
void GrapheBipartitionne(graf *pgG);//O(A). X devient X' et X"=X+pgG->nSommetEnTout,contrairt à GrapheBipartitionner()
void GrapheBipartitionner(graf *pgG);//O(A). X devient X' et X"=X+1,contrairt à GrapheBipartitionne()
void GrapheBipartir(graf *pgG,int bBipartir);//O(A)
void GrapheBoucler(graf *pgG,int sBoucle);//technique
void GrapheCadufoua();
int nGrapheCardinal(int grGadget,int nGadgetTaille);//rend le nbre de sommets du gadget de nom grGadget
void GrapheChaine(int sX,int sY,int bColorer,int nCouleur,int nPoids,const int kuChaineLgMax,char *sChaine,int *pipC);//convertit (sX,sY) en chaîne.
void GrapheChainer(graf *pgG,const char *kszPoleItem,const int knGenreDePoids,const int kuChaineLgMax,char *sChaineDejaAlloueh);
int bGrapheCheminerAuLarge(graf *pgG,int sSource,int sTrappe,int zdCheminAfficher);//O(S2)
int bGrapheCheminerCourt(graf *pgG,int sSource,int sTrappe,int bTas,int zdCheminAfficher,int *pnCheminLg,int *pnComplexiteh);//O(S2)
int bGrapheCheminerLong(graf *pgG,int sSource,int sTrappe,int zdCheminAfficher,int *pnComplexiteh);//O(S2)
int bGrapheCircuite(graf *pgG,int bAfficher);//O(A)
void GrapheCircuiterAuMieux(graf *pgFortementConnexe); 
void GrapheCliquer(graf *pgG,int uCliqueTaille);
void GrapheColorer(graf *pgG,int sOrigine,int sDestination,int nCouleur);
int nGrapheColorier(graf *pgG,int zdAfficher);
void GrapheComposanteConnexe(char *sQuoi,graf *pgG);
int nGrapheComposanteConnexe(char *sQuoi,graf *pgG,int zdAfficher);//O(A)
int nGrapheComposanteFortementConnexe(char *sQuoi,graf *pgG,int zdAfficher);//O(SA)
void GrapheConnecter(graf *pgG,int bArete,int sOrigine,int sDestination);//O(A)
void GrapheConnecter0(graf *pgG,int bArete,int sOrigine,int sDestination,int nGenreDePoids,int iPoidsSurArc);//O(A)
void GrapheConnecter1(graf *pgG,int bArete,int sOrigine,int sDestination,int nCouleur);//O(A)
void GrapheConnecter2(graf *pgG,int sOrigine,int sDestination,int nCouleurDirecte,int nCouleurInverse);//O(A)
void GrapheConnecterTout(graf *pgG,int sSource[],int sCible[],int nGenreDePoids,int nPoidsInitial);
int bGrapheConnexe(graf *pgG);//O(A)
int nGrapheCouleur(graf *pgG,int sOrigine,int sDestination);//O(S)
char *sGrapheCouple(graf *pgG,int sX,int sY,int nGenreDePoids);//O(A)
void GrapheCouvrir(graf *pgG,int bArbreCouvrantDePoidsMaximum,int tPerformanceComparer,int idAfficher);
void GrapheCreer(int nSommet,graf **ppgG);
void GrapheCreer1(graf **ppgG,int grGadget,int nGadgetTaille,int bCreer);
void GrapheCreer0(graf **ppgG,int bCreer);
void GrapheCreer2(graf **ppgG,int nSommet,int nArc,int nArcOrigine[],int nArcDestination[]);
int nGrapheCycle2(graf *pgG);
void GrapheDecolorer(graf *pgG,graf **ppgC);//O(A)
void GrapheDecrire(graf *pgG);//O(A)
void GrapheDedoubler(int sSommet,int nGenreDePoids,graf **ppgG);//O(A)
int nGrapheDegreh(graf *pgG,int sSommet,int tMode);//O(A) -1:degré entrant,0:entrant+sortant,+1:sortant.
void GrapheDegrer(graf *pgG,int tMode);//O(SA) -1:degré entrant,0:entrant+sortant,+1:sortant.
void GrapheDelimiter(graf *pgG,int uArcIndex,int *psOrigine,int *psDestination);//O(A). rend les sommets qui délimitent l'arc considéré
void GrapheDerouler(graf *pgPatron,int bCirculaire,graf *pgG);//O(SA)
void GrapheDeplier(graf *pgG);//O(SA)
float fGrapheDensiteh(graf *pgG,int bDigraphe,int zdAfficher);//O(1)
void GrapheDesarquer(graf *pgG,int sOrigine,int sDestination);//O(A)
int bGrapheDesarquer(graf *pgG,int sOrigine,int sDestination);//O(A)
void GrapheDesarquerTout(graf *pgG,int sAccroche);//retire tout arc lié à sAccroche
int bGrapheDesareter(graf *pgG,int sExtremiteh0,int sExtremiteh1);//O(A)
void GrapheDupliquer(graf *pgOriginal,graf **ppgCopie);
void GrapheEmpiler(graf *pgEmpilota,int nGenreDePoids,graf *pgG);
void GrapheEtoiler(graf *pgG,int uEtoile,int uBrancheParEtoile);
int bGrapheEulerien(graf *pgG,int bDigraphe,int szSource,int szTrappe,int bAfficher);//O(A);sz:sommet ou 0
int bGrapheEulerier(graf *pgG,int bDigraphe,int szSource,int szTrappe);//O(A);sz:sommet ou 0
void GrapheExplorer(graf *pgG,int bLargeurSinonProfondeur,int tMode,int zdAfficher);//O(A)
void GrapheFormuler(graf *pgG,int kuFormuleLim,char sFormule[]);
void GrapheFormulerTout(graf *pgG,int kuListeLim,char sListe[],int bFacultatif[],int nPoids[],int szAccroche0,int szAccroche1);
void GrapheGadgeter(graf *pgG,int grGadget,int nGadgetTaille,int sGadgetAncre);
int bGrapheGenerer(char kcArc[],int nGenreDePoids,graf **ppgG);
int bGrapheFortementConnexe(graf *pgG);//O(SA)
int nGrapheHamiltonien(graf *pgG,int bDigraphe,int bParcoursFermeh,const int kmAfficherAuPlus);//(O//2**N)
void GrapheInverser(graf *pgG);//O(A)
int bGrapheNonPlanaire(graf *pgG,char *sReduction,int bAfficher);//O(S3)
int bGrapheOrdonnancer(graf *pgG,int bStrict,int zdAfficher);//O(A)
int iGraphePoids(graf *pgG,int nGenreDePoids,int nArc);//O(A)
void GraphePolariser(graf *pgG,int *psSource,int *psTrappe);//O(A)
void GraphePonderer(graf *pgG,int sOrigine,int sDestination,int nGenreDePoids,int iPoidsSurArc);//O(A)
void GraphePonderer1(graf *pgG,int nArcPoids);//O(A)
void GraphePonderer0(graf *pgG,int nArcCout);//O(A)
void GraphePonderer2(graf *pgG,int uCapaMax,int uCoutMax);//O(A)
void GraphePonderer3(graf *pgG,int uCapaMin,int uCapaMax,int uCoutMax);//O(A)
void GraphePonderer5(graf *pgG,int sOrigine,int sDestination,int nCapaMin,int nCapaMax,int nCoutMax);//O(A)
void GraphePondererAleatoirement(graf *pgG,int nGenreDePoids,int uBorneMax);//O(A)
void GraphePondererDistinctement(graf *pgG,int iOffset);//O(A)
void GraphePondererTout(graf *pgG,int nGenreDePoids,int iPoidsSurArc);
int bGrapheQuadripole(int nTypeDeMotif);//O(1)
int nGrapheQuadripoler(graf *pgSansGadget,int grGadget,int nGadgetTaille,int bCroiser,int bTout,int nGenreDePoids,graf **ppgAvecGadget);//O(A);rend le nb de sommets par motif
void GrapheQuintesser(graf *pgG,int nSommet);
void GrapheRenumeroter(graf **ppgG,int sSommetAvant,int sSommetApres);//O(A)
void GrapheRenumeroterTout(int sListe[],graf *pgG);//O(A)
void GrapheRetourner(graf *pgG,int bRetourner,graf **ppgH);//si bRetourner,alloue et rend le graphe inverse de pgG;sinon,restitue pgH
void GrapheScruter(char *sQuoi,graf *pgG,int tMode,int bDetailler);//affiche la structure du graphe
void GrapheSimple(int bSimple);//change le mode des graphes mémorisés: graphes simples ou 1-graphes
int bGrapheSimple(graf *pgG);//O(A)
void GrapheSommer(graf *pgG,int inEmpilerSinonDepiler);//empile inEmpilerSinonDepiler sommets si >0, les dépile,si <0, avec leurs arcs incidents. 
int bGrapheSommet(graf *pgG,int sSommet);
int bGrapheSymetrique(graf *pgG);//O(A)
void GrapheSymetriser(graf *pgG,int nGenreDePoids);//O(A)
void GrapheTESTER(int iTest);
void GrapheTranslater(graf *pgG,int nOffset);
int bGrapheTrierTopologiquement(graf *pgG,int idAfficher);//O(A)
void GrapheVoir(char *sMessage,graf *pgG);//affiche tous les arcs
void GrapheVoir0(char *sMessage,graf *pgG,int nGenreDePoids);//affiche les arcs de pgG avec les pondérateurs listés ds nGenreDePoids (voir identifiants en haut de ce module)
void GrapheVoir00(char *sMessage,graf *pgG,int nGenreDePoids);//comme GrapheVoir0 mais les numéros de sommets deviennent des lettres
void GrapheVoir1(char *sMessage,graf *pgG,int bDontCouleur);
void GrapheVoir10(char *sMessage,graf *pgG,int nGenreDePoids);//comme GrapheVoir1 mais les sommets sont tjrs désignés par des lettres
void GrapheVoir11(char *sMessage,graf *pgG);//GrapheVoir10 dédié couleurs
void GrapheVoir2(char *sMessage,graf *pgG);
void GrapheVoir3(char *sMessage,graf *pgG);
void GrapheWoir(char *sMessage,graf *pgG);//GrapheVoir, mais les numéros de sommets deviennent des lettres 
void GrapheWoir0(char *sMessage,graf *pgG,int nGenreDePoids);//affiche les arcs de pgG avec les pondérateurs listés ds nGenreDePoids (voir identifiants en haut de ce module)
void GrapheWoir00(char *sMessage,graf *pgG,int nGenreDePoids);//comme GrapheVoir0 mais les numéros de sommets deviennent des lettres
void GrapheWoir1(char *sMessage,graf *pgG,int bDontCouleur);
void GrapheWoir10(char *sMessage,graf *pgG,int nGenreDePoids);//comme GrapheVoir1 mais les sommets sont tjrs désignés par des lettres
void GrapheWoir11(char *sMessage,graf *pgG);//GrapheVoir10 dédié couleurs
void GrapheWoir2(char *sMessage,graf *pgG);
void GrapheWoir3(char *sMessage,graf *pgG);
