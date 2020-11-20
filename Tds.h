#define TdsLivre 99
int bTdsAllouer(int bAllouer,char* pcTds);
int bTdsAjouter(char cTdsNom,char *sIdentificateur);
int nTdsAjouter(char cTds,char *sIdentificateur);
int bTdsAjouterValuer(char cTdsNom,char *sIdentificateur,int iValeur);
int nTdsAjouterValuer(char cTdsNom,char *sIdentificateur,int iValeur);
void TdsAMORCER();
int bTdsContient(char cTdsNom,char *sIdentificateur,int *pnItem);
int nTdsCout();//coût en nombre d'appels depuis le dernier TdsINITIALISER
float fTdsDensiteh();
int nTdsItem(char cTdsNom);//rend le nombres d'items mémorisés en TDS
int bTdsPresent(char cTdsNom,char *sIdentificateur,int *piValeur);
int bTdsSymbole(char cTdsNom,int *pnItemAvant);
char *sTdsSymbole(char cTdsNom,int nItem);
char *sTdsSymboleDepuisValeur(char cTdsNom,int iValeur);//O(t);TRÈS COÛTEUX: t est la taille de la table,eg 100 000
void TdsTESTER(int iTest);
void TdsValoriser(char cTdsNom,char *sIdentificateur,int iValeur);
void TdsValuer(char cTdsNom,int nItem,int iValeur);
void TdsVoir(char cTdsNom,char *sTitre);
