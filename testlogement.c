#include"logement.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>


void test (void)
{
	int Nblog=0,Tmaxlog=5,NbEtud=0,TmaxEtud=5,NbCite=0,TmaxDem=5,NbDem=0,trouve=0,choix=1;
	int OPTION=-1,SOUSOPTION=-1;
	Demande *TabDem;
	char term;
	Logement *TabLog;
	Cite *TabCite;
	Etudiant *TabEtud,e;
	FILE *flogement, *fdemande, *fetudiant, *fCite;
	fdemande=fopen("Demande.don","r");
	if (fdemande==NULL)
	{
		printf("Probleme ouverture DEMANDE\n");
		exit(1);
	}
	else printf("ok logement\n");
	flogement=fopen("Logement.don","r");
	if (flogement==NULL)
	{
		printf("Probleme ouverture LOGEMENT\n");
		exit(1);
	}
	else printf("ok cite\n");
	fCite=fopen("Cite.don","r");
	if (fCite==NULL)
	{
		printf("Probleme ouverture CITE\n");
	}
	else printf("ok etudiant\n");
	fetudiant=fopen("Etudiant.don","r");
	if (fetudiant==NULL)
	{
		printf("Probleme ouverture ETUDIANT\n");
		exit(1);
	}
	else printf("ok fin\n");
	
	printf("\n===========ETUDIANTS===========\n\n");
	TabEtud=(Etudiant*)malloc(TmaxEtud*sizeof(Etudiant));
	if (TabEtud==NULL){printf("pb malloc etud\n");exit(1);}
	TabEtud=ChargementEtudiant(TabEtud,&TmaxEtud,&NbEtud,fetudiant);

	
	printf("\n===========LOGEMENTS===========\n\n");
	TabLog=(Logement*)malloc(Tmaxlog*sizeof(Logement));
	if (TabLog==NULL){printf("pb malloc log\n");exit(1);}
	TabLog=ChargementLogement(TabLog,&Tmaxlog,&Nblog,flogement);
	

	
	printf("\n===========CITES===========\n\n");
	TabCite=ChargementCite(fCite,&NbCite);

	printf("\n===========DEMANDES==========\n\n");
	TabDem=(Demande*)malloc(TmaxDem*sizeof(Demande));
	if(TabDem==NULL){printf("pb malloc dem\n");exit(1);}
	TabDem=ChargementDemande(TabDem,&TmaxDem,&NbDem,fdemande);
	printf("\n\n\nDONNEES CHARGEES\n");

	while(OPTION!=0)
	{
		if(OPTION==1)
		{	
			while(SOUSOPTION!=0)
			{
				if (SOUSOPTION==1)
				{
					printf("\n\n<><>1-AFFICHAGE ETUDIANTS<><>\n\n");
					printf("==IdEtudiant==Bourse==Echelon==Handicap==Civilite==Nom\n\n");
					faffichageetudiant(TabEtud,NbEtud);
				}
				if (SOUSOPTION==2)
				{
					printf("\n\n<><>2-AFFICHAGE LOGEMENTS<><>\n\n");
					printf("==IdLogement==TypeLog==Disponible==AdaptHandicap==IdEtudiant==Cite\n\n");
					faffichagelogement(TabLog,Nblog);
				}
				if (SOUSOPTION==3)
				{
					printf("\n\n<><>3-AFFICHAGE CITE<><>\n\n");
					printf("===Nom===\n\n");
					faffichagecite(TabCite,NbCite);
				}
				if (SOUSOPTION==4)
				{
					printf("\n\n<><>4-AFFICHAGE DEMANDE<><>\n\n");
					printf("==IdDemande==Echelon==IdEtudiant==TypeLog==Cite\n\n");
					faffichagedemande(TabDem,NbDem);
				}
				if (SOUSOPTION==5)
				{
					TabEtud=CreationEtudiant(TabEtud,&NbEtud,&TmaxEtud);
					printf("\n\n====NOUVEAU TABLEAU====\n\n");
					faffichageetudiant(TabEtud,NbEtud);
				}

				printf("\n<><>AFFICHAGE DONNEES<><>\n");
				printf("|-> 0-QUITTER\n");
				printf("|--> 1-AFFICHAGE ETUDIANTS\n");
				printf("|---> 2-AFFICHAGE LOGEMENTS\n");
				printf("|----> 3-AFFICHAGE CITE\n");
				printf("|-----> 4-AFFICHAGE DEMANDE\n");
				printf("|------> 5-CREATION ETUDIANT\n");
		        while(scanf("%d%c",&SOUSOPTION, &term) != 2 || term != '\n')
			    {
					printf("\n<><>AFFICHAGE DONNEES<><>\n");
					printf("|-> 0-QUITTER\n");
					printf("|--> 1-AFFICHAGE ETUDIANTS\n");
					printf("|---> 2-AFFICHAGE LOGEMENTS\n");
					printf("|----> 3-AFFICHAGE CITE\n");
					printf("|-----> 4-AFFICHAGE DEMANDE\n");
					printf("|------> 5-CREATION ETUDIANT\n");
			        while(getchar() != '\n');
			    }



			}
		}
		if (OPTION==2)
		{
			while(SOUSOPTION!=0)
			{
				if(SOUSOPTION==1)
						AffichageTRILog(TabCite,TabLog,NbCite,Nblog);
				if (SOUSOPTION==2)
					Affichagelogementoccupe(TabLog,Nblog,TabEtud,NbEtud); 
				if (SOUSOPTION==3)
					{
						while(trouve==0&&choix==1)
						{
							TabLog=Liberationlogement(TabLog,Nblog,TabEtud,&NbEtud,TabDem,&NbDem,&trouve);
							if (trouve==0)
							{
								printf("Nouvel essai ?\n");
								scanf("%d",&choix);
								while(choix!=0&& choix!=1)
								{
									printf("Erreur saisie 0 ou 1\n");
									scanf("%d",&choix);
								}
							}
						}
					}
				printf("\n<><>LOGEMENT<><>\n");
				printf("|-> 0-QUITTER \n");
				printf("|--> 1-AFFICHAGE LOGEMENT TRIEE\n");
				printf("|---> 2-AFFICHAGE LOGEMENT OCCUPES \n");
				printf("|----> 3-LIBERATION LOGEMENT\n");
				printf("Saisir option :\n");
		        while(scanf("%d%c",&SOUSOPTION, &term) != 2 || term != '\n')
			    {
					printf("\n<><>LOGEMENT<><>\n");
					printf("|-> 0-QUITTER\n");
					printf("|--> 1-AFFICHAGE LOGEMENT TRIEE\n");
					printf("|---> 2-AFFICHAGE LOGEMENT OCCUPES \n");
					printf("|----> 3-LIBERATION LOGEMENT\n");
					printf("Saisir option :\n");
			        while(getchar() != '\n');
			    }				
			    trouve=0;
				choix=1;
			}
		}
		if (OPTION==3)
		{
			while(SOUSOPTION!=0)
			{
				if(SOUSOPTION==1)
					{
						printf("\n\n\n========<DEAMADES>========\n\n");
						printf("IdDemande==Echelon==IdEtudiant==TypeLog==Cite\n\n");
						faffichagedemande(TabDem,NbDem);
					}
				if (SOUSOPTION==2)
				{
					printf("<><>SOUSOPTION-2<><>\n");
					printf("\n\n==========ANCIEN TABLEAU LOGEMENTS==========\n\n");
					faffichagelogement(TabLog,Nblog);
					printf("\n\n==========ANCIEN TABLEAU DE DEMANDES==========\n\n");
					faffichagedemande(TabDem,NbDem);
					TabDem=TraitementDemande(TabDem,&NbDem,&TmaxDem,TabLog,Nblog);
				}
				if (SOUSOPTION==3)
				{
					printf("<><>SOUSOPTION-3<><>\n");
					TabDem=CreationDemande(TabDem,&NbDem,&TmaxDem,TabEtud,&NbEtud,&TmaxEtud,TabLog,Nblog);
				}
				if (SOUSOPTION==4)
				{

					TabDem=SuppressionDemande(TabDem,&NbDem,&TmaxDem);
				}
				printf("\n<><>DEMANDE<><>\n");
				printf("|-> 0-QUITTER\n");
				printf("|--> 1-LISTE DES DEMANDES EN ATTENTE\n");
				printf("|---> 2-TRAITEMENT DES DEMANDES\n");
				printf("|----> 3-SAISIE D'UNE DEMANDE\n");
				printf("|-----> 4-ANNULATION DE DEMANDE\n");
				while(scanf("%d%c",&SOUSOPTION, &term) != 2 || term != '\n')
			    {
					printf("\n<><>DEMANDE<><>\n");
					printf("|-> 0-QUITTER\n");
					printf("|--> 1-LISTE DES DEMANDES EN ATTENTE\n");
					printf("|---> 2-TRAITEMENT DES DEMANDES\n");
					printf("|----> 3-SAISIE D'UNE DEMANDE\n");
					printf("|-----> 4-ANNULATION DE DEMANDE\n");
			        while(getchar() != '\n');
			    }	
			}
		}
		if (OPTION==4)
		{
			printf("<><>SAUVEGARDER<><>\n");
			printf("Sauvegarde en cours...\n");
			SavEtudiant(TabEtud,NbEtud);
			printf("Sauvegarde Etudiant faite.\n");
			SavDemande(TabDem,NbDem);
			printf("Sauvegarde Demande faite.\n");
			SavLogement(TabLog,Nblog);
			printf("Sauvegarde Logement faite.\n");
			printf("Sauvegarde terminée.\n");
		}
		printf("\n================== MENU =================\n");
		printf("=========== 1-AFFICHAGE DONNEES =========\n");
		printf("=============== 2-LOGEMENT ==============\n");
		printf("=============== 3-DEMANDE ===============\n");
		printf("============= 4-SAUVEGARDER =============\n");
		printf("=============== 0-QUITTER ===============\n");
		printf("Saisir option :\n");
		SOUSOPTION=-1;
		
		while(scanf("%d%c",&OPTION, &term) != 2 || term != '\n')
	    {
			printf("\n====================MENU=================\n");
			printf("============ 1-AFFICHAGE DONNEES=========\n");
			printf("=============== 2-LOGEMENT===============\n");
			printf("================3-DEMANDE================\n");
			printf("==============4-SAUVEGARDER==============\n");
			printf("================0-QUITTER================\n");
			printf("Saisir option :\n");
	        while(getchar() != '\n');
	    }
		
	}

}


int main (void)
{
	test();
	return 0;
}










































