//Grhom pour GRammaire HOMogene
void GrhomAMORCER();
void GrhomCompiler(const char *ksGrammaireAlgebrique,const char *ksGrammaireHomogene);
int bGrhomCompiler(const char *ksGrammaireAlgebrique,const char *ksGrammaireHomogene,int bAfficher,char *szFichierCible,int *pnRegleEnTout);
void GrhomDecliner(const char *ksGrammaireAlgebrique,const char *ksGrammaireHomogene,int uMotLgMax,int zdAfficher);
void GhromSeparer(const char *ksGrammaire,int nSeparateur[]);
void GrhomTESTER(int iTest);
