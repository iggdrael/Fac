void FlotAfficher(graf *pgG,int bTout,char *sMessage);//si non bTout,censure les arcs dont le flot est nul
void FlotAMORCER();
void FlotCapaciter(graf *pgG,int szOrigine,int szDestination,int nCapacitehMaximale);//attribue une capacité
int bFlotCompatible(graf *pgG,int sSource,int sTrappe,int bAfficher);
void FlotCouter1(graf *pgG,int szOrigine,int szDestination,int nCout);//attribue un coût (champ nCout)
void FlotCouter2(graf *pgG,int szOrigine,int szDestination,int nCout);//attribue un coût (champ nPrix)
void FlotDeterminer(int uDimension,int iMatriceCarrehLineariseh[],int bBiflot);//flot d'un déterminant
void FlotMaxCalculer(graf *pgG,int sSource,int sTrappe,int bAfficher);//unifie pgG->nCout puis calcule un flot max de coût minimal
int nFlotMaxCalculer(graf *pgG,int sSource,int sTrappe,int nFlotRequis,int bAfficher,int bPreciser);//calcule un flot max de coût minimal
void FlotMaximiser(graf *pgG,int sSource,int sTrappe,int nFlotRequis,int sDomaine[],int bAfficher);
void FlotOptimiser(graf *pgG,int nSommetInitial,int sSource,int sTrappe,int bAfficher);
void FlotTESTER(int iTest);
