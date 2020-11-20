enum eErreur {eLimite0,
	eAlex0,eAlexInconnu,eAlexEntier,eAlexMotClef,eAlexReel,eAlex1,
	eCfg0,eCfg1Fleche,eCfg2Fleche,eCfgGauche,eCfgInconnu,eCfgLineaire,eCfgOperande,eCfgSomme,eCfg1,
	eGraf0,eGrafBcle,eGrafDecit,eGrafDito,eGrafEpars,eGrafItem,eGrafPoids,eGrafPositif,eGrafQuestion,eGrafSommet,eGrafSymbole,eGrafZero,eGraf1,
	ePlnr0,ePlnrReduc,ePlnrK5K33,ePlnrSommet,ePlnrSym,ePlnr1,
	eSem0,eSemAffectation,eSemAffichage,eSemDate,eSemDelaiTropLong,eSemDoublon,eSemHoraire,eSemIdentifiant,eSemInscrit,eSemLivreDispo,eSemLivreInconnu,eSemLivrePris,eSemNonInscrit,eSemPrix,eSem1,
	eSynt0,eSyntCalcuL,eSyntEtat,eSyntInstruction,eSyntLivre,eSyntNom,eSyntProgramme,eSyntSeparateur,eSyntSuite,eSyntTerme,eSynt1,
	eLimite1};
void ErreurAfficher(const int uLigne);
void ErreurAfficherTout(const char *szCodeSource);
void ErreurAMORCER();
void ErreurDeclarer(const int bAffirmation,const int nPlnrErreur,const int iCaractereRg,int *pbValide);
void ErreurDenoncer(const int bAffirmation,const int grfErreur,const int iCaractereRg,int *pbValide);
void ErreurDetecter(const int bAffirmation,const int cfgErreur,const int iCaractereRg,int *pbValide);
void ErreurEmpiler(const int nErreurNumero,const  int nLexeme);
int bErreurEmpiler(const int nErreurNumero,const  int nLexeme);
int nErreurEnTout();
void ErreurTESTER(int iTest);