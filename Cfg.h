//Cfg= Context Free Grammars
void CfgAMORCER();
void CfgComplementer(const char *ksgrLineaireAhDroite,int zdAfficher,char *szgrComplementaire);
int bCfgLineaireAhDroite(const char *ksgrLineaireAhDroite,int nLettreAuPlus);
int bCfgNormaliser(const char *ksgrAlgebriqueOuPropre,int bAlgebrique,int tPropre1Quasi2Greibach3,int zdAfficher,char *szgrPropreOuQuasiGreibachOuGreibach);
void CfgReconnaitre(const char *ksgrLineaireAhDroite,int nLettreAuPlus,int zdAfficher);
void CfgTESTER(int iTest);
