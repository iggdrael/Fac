enum {mcAlpha,mcAchat,mcStock,mcOmega};
enum  eLexemeClassE   {lcAlphA,lcBlanC,lcInconnU,lcEntieR,lcReeL,lcIdentificateuR,lcOperateuR,lcParenthesE,lcSeparateuR,lcMotCleF,lcTextE,lcFinDeFichieR,lcOmegA};
void AlexAfficher();
void AlexAMORCER();
int bAlexAnalyser(char *sCode);
int nAlexCalcul(int nLexeme);
char *sAlexChaine(int nLexeme);
int bAlexDate(int uLexeme);
void AlexDenoncer(int nLexeme);
int bAlexEntier(int uLexeme);
int mAlexEntier(int uLexeme);
int nAlexEtat(int uLexeme);
int nAlexExpression(int uLexeme);
int bAlexFermant(int uLexeme,char cFermant);
int bAlexFinFichier(int uLexeme);
int bAlexHoraire(int uLexeme);
int bAlexIdentificateur(int uLexeme);
int nAlexInstruction(int uLexeme);
int bAlexLexeme(int uLexeme);
int nAlexLexeme(int uLexeme);//rend la colonne associée au lxm uLexeme ds la table Asynt.iFirst
int uAlexLexeme(char *sLexeme);//rend la colonne associée au uLexeme ds la table Asynt.iFirst
char *sAlexLxm(int uLexeme);
int nAlexLigne(int uLexeme);
int bAlexMotClef(int uLexeme,int nMotClefNumero);
int nAlexOffset(int nCumul);
int bAlexOperateur(int uLexeme,char cOperateur);
int bAlexOuvrant(int uLexeme,char cOuvrant);
int bAlexParentheseur(int uLexeme,char cParenthese);
int nAlexProduitOuTerme(int uLexeme);
int nAlexProgramme(int uLexeme);
int bAlexReel(int uLexeme);
float fAlexReel(int uLexeme);
int bAlexSeparateur(int uLexeme);
int nAlexSuite(int uLexeme);
int nAlexTerme(int uLexeme);
void AlexTESTER(int iTest);
int bAlexTexte(int uLexeme);