#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct 
{
	char IdEtudiant[11];
	int Bourse, Echelon, Handicap;
	char Civilite[4],Nom[40];
	
}Etudiant;

typedef struct 
{
	char Nom[30];
	
}Cite;

typedef struct 
{
	char IdLogement[11],TypeLog[2];
	int Disponible,AdaptHandicap;
	char IdEtudiant[11],Cite[30];
}Logement;

typedef struct 
{
	char IdDemande[11],TypeLog[2];
	int EchelonEtudDem,Handicap;
	char IdEtudiant[11];
	char Cite[30];
}Demande;

Etudiant lireEtudiant(FILE *fe);
Demande lireDemande(FILE *fe);
Logement lireLogement(FILE *fe);
Cite lireCite(FILE *fe);


Etudiant* ChargementEtudiant(Etudiant *Tabetud,int *TmaxEtud,int *NbEtud,FILE *fe);
Cite* ChargementCite(FILE *fe, int *NbCite);
Logement* ChargementLogement(Logement *Tablog, int *TmaxLog, int *NbLog, FILE *fe);
Demande* ChargementDemande(Demande *TabDem, int *TmaxDem,int *NbDem, FILE *fe);

void faffichagedemande(Demande *TabDem,int NbDem);
void faffichagelogement(Logement *Tablog,int NbLog); 
void faffichagecite(Cite *TabCite,int NbCite);
void faffichageetudiant(Etudiant *TabEtud,int NbEtud);
void AffichageTRILog(Cite *TabCite,Logement *Tablog, int NbCite,int NbLog);
void Affichagelogementoccupe(Logement *Tablog,int NbLog,Etudiant *TabEtud, int NbEtud);

Demande* TraitementDemande(Demande *TabDem,int *NbDem,int *TmaxDem,Logement *Tablog,int NbLog);
int Conseillogement(Logement *Tablog,int NbLog,Demande demande);

Logement* Liberationlogement(Logement *Tablog,int NbLog,Etudiant *TabEtud,int *NbEtud,Demande *TabDem,int *NbDem,int *trouve);
Logement RecherchedemandeLOGEMENT(Logement logement,Demande *TabDem,int *NbDem);

Etudiant* CreationEtudiant (Etudiant *TabEtud,int *NbEtud,int *TmaxEtud);
int RechercheEtud(Etudiant *TabEtud,int NbEtud,int *trouve,char *e);
Etudiant* MAJTabEtud(Etudiant *TabEtud,int *NbEtud,int *TmaxEtud,int rang,Etudiant e);
void test (void);


Demande* CreationDemande(Demande *TabDem,int *NbDem,int *TmaxDem,Etudiant *TabEtud,int *NbEtud,int *TmaxEtud,Logement *Tablog,int NbLog);
Etudiant* CreationEtudiantDEMANDE(Etudiant *TabEtud,int *NbEtud,int *TmaxEtud,char *idetudiant);
int RechercheLogement(Logement *Tablog,int NbLog,int trouve,char *idetudiant);
int RechercheDemande(Demande *TabDem,int NbDem,int *trouve,char *iddemande);
Demande* SuppressionDemande(Demande *TabDem,int *NbDem,int *TmaxDem);
Demande* MAJDemandeSupp(Demande *TabDem,int *NbDem,int rang);
Demande* MAJDemande(Demande *TabDem,int *NbDem,int *TmaxDem,int rang,Demande demande);

void SavEtudiant (Etudiant *TabEtud,int NbEtud);
void SavDemande (Demande *TabDem,int NbDem);
void SavLogement (Logement *TabLog,int NbLog);

int verifnum (char *chaine, int n);




















