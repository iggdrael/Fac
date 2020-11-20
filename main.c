#include "Kit.h"
#include "Abe.h"
#include "Alex.h"
#include "Asynt.h"
#include "Cfg.h"
#include "Code.h"
#include "Deque.h"
#include "Erreur.h"
#include "Grammaire.h"
#include "Grhom.h"
#include "Graphe.h"
#include "Couplage.h" //APRES Graphe.h
#include "Foret.h"
#include "Flot.h" //APRES Graphe.h
#include "Quiz.h"
#include "Sat2.h"
#include "Tas.h"
#include "Tds.h"
#include "Ticket.h"
#include "Tri.h"
#include "Tp1.h"
#include "Tp2.h"
#include "Tp3.h"
#include "Tp4.h"

void ModuleAmorceR(){
	//amorce tous les modules (code à exécuter une fois pour toutes AVANT d'utiliser un quelconque module depuis le main)
	KitAMORCER();//NE PAS DECLASSER: doit toujours être appelé en premier
	//amorcer TOUS les modules autres que Kit mentionnés dans les include de main.c
		AbeAMORCER();
		AlexAMORCER();
		AsyntAMORCER();
		ErreurAMORCER();
		CfgAMORCER();
		GrammaireAMORCER();
		GrhomAMORCER();
		GrapheAMORCER();//avant FlotAMORCER()
		CouplageAMORCER();
		DequeAMORCER();
		FlotAMORCER();
		ForetAMORCER();
		TasAMORCER();
		TdsAMORCER();
		QuizAMORCER();
		Sat2AMORCER();
		TicketAMORCER();
		Tp1AMORCER();
		Tp2AMORCER();
		Tp3AMORCER();
		Tp4AMORCER();
		TriAMORCER();
}//ModuleAmorceR

void DiagnostiqueR(char *sContexte,int bSucces){
	printf("Le code source %s valide au niveau %s%s",sEst(bSucces),sContexte,sChoix1(!bSucces,sC2(" ",sP(sPluriel(nErreurEnTout(),"erreur")))));
	printf("%c\n",(bSucces)?'.':':');
}//DiagnostiqueR

		//Programme->Instructions || FinFichier
		//		Instructions->Instruction Separateur Programme
		//		Instruction-> Lecture || Ecriture || Affectation 
		//		Lecture -> "get" Identificateur			
		//		Ecriture -> "put" Expression		  
		//		Affectation -> Variable "=" Expression
		//		Expression -> Somme | Produit | Terme 
		//		Somme -> ProduitOuTerme "+" Expression
		//		ProduitOuTerme -> Produit | Terme
		//		Produit-> Terme "*" Expression
		//		Terme-> Identificateur || Entier

void CompileR(int nSource){
	const int bEclaireur=kV;
	int bSourceConnu=kV,bSucces;
	char *sSource;
	switch (nSource){
		//case 0: sSource="A=(2*3^4+(5 6+7)+8) 9*0; ";
		case 0: sSource="TOTAL=2+3; ";
				break;
		case 1: sSource="19.90 \"guerre\";achat;19.90 \"paix\";stock;$";
		//case 1: sSource="get A; $";
				break;
		case 10: sSource="(7) sinon Sept;(3+Sept) Dix ;[Dix] ;[Sept] ;(Dix*(Sept+3)) Cent;[Cent] ;";
				break;
		case 2: //livre est acheté;LUI et ELLE s'inscrivent;Lui emprunte le livre et le restitue puis ELLE l'emprunte
				sSource="19.90 \"livre\";8.05 \"autrelivre\";240317 LUI;250317 ELLE; < \"livre\" LUI; >\"livre\" LUI; < \"livre\" ELLE;";//***********
				break;
		case 3: //1 bug sémantique: livre est acheté;LUI et ELLE s'inscrivent;Lui emprunte le livre donc ELLE ne peut pas l'emprunter
				sSource="19.90 livre; 240317 LUI; 250317 ELLE; < livre LUI; < livre ELLE;";
				break;
		case 4: //livre est acheté;LUI et ELLE s'inscrivent;LUI emprunte le livre donc ELLE ne peut pas l'emprunter
				sSource="19.90 livre; 240317 LUI; 50 livre; 2500 livre; < livre LUI; < livre ELLE;";
				break;
		case 7: sSource="240317 ELLE; 0.5 dune; < dune ELLE; 0 dune; < dune ELLE; > dune ELLE ; 440317 MOI  ; 3.5 machin ; 55 Truc ;$";
				break;
		case 8: sSource="240218 MOI; 0.5 livre; < livre MOI; 0 elle; < livre MOI; > livre MOI ; 440317 MOI  ; 3.5 machin ; 55 Truc ;$";
				break;
		default: bSourceConnu=kF;printf("Clause default: code source n°%d inconnu.\n",nSource);break;
	}
	bSucces=bSourceConnu;
	bSucces=bSucces && bAlexAnalyser(sSource); DiagnostiqueR("lexical",bSucces);
	bSucces=bSucces && bAsyntAnalyser(mAsyntSyntaxique,bEclaireur); DiagnostiqueR(sC2b("syntaxique",sP(sC2b((bEclaireur)?"avec":"sans","éclaireur"))),bSucces);
	bSucces=bSucces && bEclaireur && bAsyntAnalyser(mAsyntSemantique,bEclaireur); DiagnostiqueR("sémantique",bSucces);
	//bSucces=bSucces && bEclaireur && bAsyntAnalyser(mAsyntGeneration,bEclaireur); DiagnostiqueR("génération du code",bSucces);
	ErreurAfficherTout("");
	if (0 && bSucces)
		CodeExecuter();//lance l'exécution du code C généré par le compilateur à partir de sSource
}//CompileR

int main (int argc, const char * argv[]) {
	Appel0("");//NE PAS TOUCHER; ce code doit toujours être placé ici, au début du main
		ModuleAmorceR();//NE PAS TOUCHER; ce code doit toujours suivre immédiatement Appel0("")
		//CfgTESTER(0);
		Tp4TESTER(11);
	Appel1("");//NE PAS TOUCHER; ce code doit toujours être placé ici, à la fin du main, juste avant le return()
    return 0;
}//main
