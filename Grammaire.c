#include "Kit.h"
#include "Grammaire.h"
char *sMOT;
int bGrammaireAmorceR=kF;
// Grammaire algébrique (3 règles):
            // (a) S->K.Q
            // (b) K->A.K.A+Q
            // (c) Q->B.Q+B
// Grammaire homogène (7 règles):
            // (1) S->K.Q
            // (2) K->P+Q
            // (3) P->A.K.A
            // (4) Q->U+B
            // (5) U->B.Q
            // (6) A->a
            // (7) B->b
int bA(int iDebut,int *piFin);
int bB(int iDebut,int *piFin);
int bK(int iDebut,int *piFin);
int bP(int iDebut,int *piFin);
int bQ(int iDebut,int *piFin);
int bS(int iDebut,int *piFin);
int bU(int iDebut,int *piFin);

void GrammaireAMORCER(){
    bGrammaireAmorceR=kV;
}//GrammaireAMORCER

void GrammaireTesteR(char *sMot,int nLgMax){
    int bEngendre,iFin,bSucces;
    sMOT=sMot;
    bSucces=bS(0,&iFin);
    bEngendre=bSucces && nChaineLg(sMOT)==iFin;
    if (bEngendre)
        printf("%s: %s %s engendré par la grammaire décrite dans \"Grammaire.c\".\n",(bEngendre)? "SUCCES": "ECHEC ",sG(sMOT),sEst(bEngendre));
    if (nChaineLg(sMot)<nLgMax){
        GrammaireTesteR(sC2(sMot,"a"),nLgMax);
        GrammaireTesteR(sC2(sMot,"b"),nLgMax);
    }
}//GrammaireTesteR

void GrammaireTESTER(int iTest){
    int bEngendre,iFin,bSucces;
    Assert1("GrammaireTESTER0",bGrammaireAmorceR);
    //sMOT:=mot à tester selon iTest
        switch(iTest){
            case 0: GrammaireTesteR("",10);break;
            case 1: sMOT="aab";break;
            case 2: sMOT="aaba";break;
            default:Assert1("GrammaireTESTER1",0);break;
        }
    if (iTest>0){
        bSucces=bS(0,&iFin);
        bEngendre=bSucces && nChaineLg(sMOT)==iFin;
        printf("%s: %s %s engendré par la grammaire décrite dans \"Grammaire.c\".\n",(bEngendre)? "SUCCES": "ECHEC ",sG(sMOT),sEst(bEngendre));
    }
}//GrammaireTESTER

int bA(int iDebut,int *piFin){
    //A->a
    int bSucces = sMOT[iDebut]=='a';
    *piFin = (bSucces) ? iDebut+1 : iDebut;
    return(bSucces);
}//bA

int bB(int iDebut,int *piFin){
    //B->b
    int bSucces = sMOT[iDebut]=='b';
    *piFin = (bSucces) ? iDebut+1 : iDebut;
    return(bSucces);
}//bB

int bK(int iDebut,int *piFin){
    //K->P+Q
    int iFin;
    int bSucces=bP(iDebut,&iFin) || bQ(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bK

int bP(int iDebut,int *piFin){
    //P->A.K.A
    int iA=iDebut,iB,iC,iD;
    int bSucces=bA(iA,&iB) && bK(iB,&iC) && bA(iC,&iD);
    *piFin=(bSucces)?iD:iDebut;
    return(bSucces);
}//bP

int bQ(int iDebut,int *piFin){
    //Q->U+B
    int iFin;
    int bSucces=bU(iDebut,&iFin) || bB(iDebut,&iFin);
    *piFin=(bSucces)?iFin:iDebut;
    return(bSucces);
}//bQ

int bS(int iDebut,int *piFin){
    //S->K.Q
    int iA=iDebut,iB,iC;
    int bSucces=bK(iA,&iB) && bQ(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bS

int bU(int iDebut,int *piFin){
    //U->B.Q
    int iA=iDebut,iB,iC;
    int bSucces=bB(iA,&iB) && bQ(iB,&iC);
    *piFin=(bSucces)?iC:iDebut;
    return(bSucces);
}//bU

