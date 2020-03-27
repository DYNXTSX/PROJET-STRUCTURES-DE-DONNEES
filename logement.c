#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"logement.h"

Etudiant lireEtudiant(FILE *fe)
{
	/*
	Variables :
		- Etudiant e : désigne une structure e de type étudiant
	Finalité :
		- Crée un étudiant via la lecture des informations dans le fichier
	*/
	Etudiant e;
	fscanf(fe,"%s",e.IdEtudiant);
	fscanf(fe,"%d %d %d",&e.Bourse,&e.Echelon,&e.Handicap);
	fscanf(fe,"%s%*c",e.Civilite);
	fgets(e.Nom,30,fe);
	e.Nom[strlen(e.Nom)-1]='\0';
	return e;
}

Logement lireLogement(FILE *fe)
{
	/*
	Variables :
		- Logement l : désigne une structure l de type logement
	Finalité :
		- Crée un logement via la lecture des informations dans le fichier
	*/
	Logement l;
	fscanf(fe,"%s %s",l.IdLogement,l.TypeLog);
	fscanf(fe,"%d %d %s%*c",&l.Disponible,&l.AdaptHandicap,l.IdEtudiant);
	fgets(l.Cite,30,fe);
	l.Cite[strlen(l.Cite)-1]='\0';
	return l;
}


Demande lireDemande(FILE *fe)
{
	/*
	Variables :
		- Demande demande : désigne une structure demande de type Demande
	Finalité :
		- Crée une demande via la lecture des informations dans le fichier
	*/
	Demande demande;
	fgets(demande.IdDemande,11,fe);
	fscanf(fe,"%s%*c%d%*c%d%*c%s%*c",demande.TypeLog,&demande.EchelonEtudDem,&demande.Handicap,demande.IdEtudiant);
	fgets(demande.Cite,30,fe);
	demande.Cite[strlen(demande.Cite)-1]='\0';
	return demande;
}


Cite lireCite(FILE *fe)
{
	/*
	Variables :
		- Cite cite : désigne une structure cite de type Cite
	Finalité :
		- Crée une cité via la lecture des informations dans le fichier
	*/
	Cite cite;
	fgets(cite.Nom,30,fe);
	cite.Nom[strlen(cite.Nom)-1]='\0';
	return cite;
}

Etudiant* ChargementEtudiant(Etudiant *TabEtud,int *TmaxEtud,int *NbEtud,FILE *fe)
{
	/*
	Variables :
		- Etudiant etud : désigne une structure etud de type étudiant
		- *nvtEtud : désigne un tableau d'étudiant
	Finalité :
		- la variable etud permet de stocker un étudiant lu dans le fichier, pour ensuite l'insérer dans l'ordre dans le tableau *tabetud,
		  si la taille logique est égale à la taille physique, *nvtEtud intervient comme tableau intermédiaire dans le but d'augmenter la taille physique de *TabEtud,
		  on répète cette action, jusqu'à avoir lu tout les étudiants du fichier.
		- cette fonction retourne le tableau d'étudiant tabetud en modifiant la taille max du tableau étudiant et le nombre d'étudiants.
	*/
	Etudiant etud, *nvtEtud;
	etud=lireEtudiant(fe);
	while(feof(fe)==0)
	{
		if (*NbEtud==*TmaxEtud)
		{
			nvtEtud=(Etudiant*)realloc(TabEtud,sizeof(Etudiant)*(*TmaxEtud+5));
			TabEtud=nvtEtud;
			*TmaxEtud=*TmaxEtud+5;
		}
		
		TabEtud[*NbEtud]=etud;
		etud=lireEtudiant(fe);
		*NbEtud=*NbEtud+1;
	}
	faffichageetudiant(TabEtud,*NbEtud);
	return TabEtud;
}

Cite* ChargementCite(FILE *fe, int *NbCite)
{
	/*
	Variables :
		- Cite  *Tcite : désigne un tableau regroupant les cités
		- i : désigne un nombre entier
	Finalité :
		- Le nombre de cités étant indiqué au début du fichier, l'opération de lecture et de chargement s'effectura alors NbCite fois.
		  Une fois le nombre de cité lu, une allocation d'espace suffisante va être affecté à Tcite, dans le but d'y insérer les cités lu dans le fichier.
		- Cette fonction retourne le tableau Tcite tout en renseignant le Nombre de cités.
	*/
	int i;
	Cite *Tcite;
	fscanf(fe,"%d%*c",NbCite);
	Tcite=(Cite*)malloc(*NbCite*sizeof(Cite));
	if (Tcite==NULL)
	{
		printf("Probleme malloc\n");
		exit(1);
	}
	for (i=0; i < *NbCite;i++)
	{
		Tcite[i]=lireCite(fe);
	}
	faffichagecite(Tcite,*NbCite);
	return Tcite;
}



Logement* ChargementLogement(Logement *Tablog, int *TmaxLog, int *NbLog, FILE *fe)
{
	/*
	Variables :
		- Logement log : désigne une structure log de type Logement
		- *nvtlog : désigne un tableau de logement
	Finalité :
		- la variable log permet de stocker un logement lu dans le fichier, pour ensuite l'insérer dans l'ordre dans le tableau *Tablog,
		  si la taille logique est égale à la taille physique, *nvtlog intervient comme tableau intermédiaire dans le but d'augmenter la taille physique de *Tablog,
		  on répète cette action, jusqu'à avoir lu tous les logements du fichier.
		- cette fonction retourne le tableau de logement Tablog en modifiant la taille max du tableau logement et le nombre de logements.
	*/
	Logement log, *nvtlog;
	log=lireLogement(fe);
	while(feof(fe)==0)
	{	
		if(*NbLog==*TmaxLog)
		{
			nvtlog=(Logement*)realloc(Tablog,sizeof(Logement)*(*TmaxLog+5));
			if(nvtlog==NULL)
			{
				printf("Probleme realloc\n");
				exit(1);
			}
			*TmaxLog=*TmaxLog+5;
			Tablog=nvtlog;
		}
		Tablog[*NbLog]=log;
		log=lireLogement(fe);
		*NbLog=*NbLog+1;
	}
	faffichagelogement(Tablog,*NbLog);
	return Tablog;
}


Demande* ChargementDemande(Demande *TabDem, int *TmaxDem,int *NbDem, FILE *fe)
{
	/*
	Variables :
		- Demande demande : désigne une structure demande de type Demande
		- *nvtdem : désigne un tableau de demande
	Finalité :
		- la variable demande permet de stocker une demande lu dans le fichier, pour ensuite l'insérer dans l'ordre dans le tableau *Tabdem,
		  si la taille logique est égale à la taille physique, *nvtdem intervient comme tableau intermédiaire dans le but d'augmenter la taille physique de *Tabdem,
		  on répète cette action, jusqu'à avoir lu toutes les demande du fichiers.
		- cette fonction retourne le tableau de demande Tabdem en modifiant la taille max du tableau demande et le nombre de demandes.
	*/
	Demande demande,*nvtdem;
	demande=lireDemande(fe);
	while(feof(fe)==0)
	{
		if (*NbDem==*TmaxDem)
		{
			nvtdem=(Demande*)realloc(TabDem,sizeof(Demande)*(*TmaxDem+5));
			if (nvtdem==NULL)
			{
				printf("Probleme realloc\n");
				exit(1);
			}
			*TmaxDem=*TmaxDem+5;
			TabDem=nvtdem;
		}
		TabDem[*NbDem]=demande;
		demande=lireDemande(fe);
		*NbDem=*NbDem+1;
	}
	faffichagedemande(TabDem,*NbDem);
	return TabDem;
}


void AffichageTRILog(Cite *TabCite,Logement *Tablog, int NbCite,int NbLog)
{
	/*
	Variables :
		- i : désigne un nombre entier
	Finalité :
		- Affiche par cité les logements disponibles dans celle-ci
	*/
	for (int i=0;i<NbCite;i++)
	{
		printf("\n<=================-%s-=================> \n\n",TabCite[i].Nom);
		printf("IdLogement---Type Logement---AdapHadicap\n");
		for (int j=0;j<NbLog;j++)
		{
			if (strcmp(TabCite[i].Nom,Tablog[j].Cite)==0 && Tablog[j].Disponible==1)
			{
				printf("%s\t  %s\t\t  %d\n",Tablog[j].IdLogement,Tablog[j].TypeLog,Tablog[j].AdaptHandicap);
			}
		}
	}
	printf("\n");
}

void faffichagelogement(Logement *TabLog,int NbLog) 
{
	/*
	Variables :
		- i : désigne un nombre entier
	Finalité :
		- Affiche les logements et leurs informations ainsi que le nombre de logements total. 
	*/
	for (int i = 0; i < NbLog;i++) 
	{
		printf("%s %s %d %d %s %s\n",TabLog[i].IdLogement,TabLog[i].TypeLog,TabLog[i].Disponible,TabLog[i].AdaptHandicap,TabLog[i].IdEtudiant,TabLog[i].Cite);
	}
	printf("\n==(%d) LOGEMENTS==\n\n",NbLog );
}

void faffichagedemande(Demande *TabDem,int NbDem) 
{
	/*
	Variables :
		- i : désigne un nombre entier
	Finalité :
		- Affiche les demandes et leurs informations ainsi que le nombre total de demandes.
	*/
	for (int i = 0; i < NbDem;i++) 
	{
		printf("%s %s %d %d %s %s\n",TabDem[i].IdDemande,TabDem[i].TypeLog,TabDem[i].EchelonEtudDem,TabDem[i].Handicap,TabDem[i].IdEtudiant,TabDem[i].Cite);
	}
	printf("\n==(%d) DEMANDES==\n\n",NbDem);
}
 
void faffichagecite(Cite *TabCite,int NbCite)
 {
 	/*
	Variables :
		- i : désigne un nombre entier
	Finalité :
		- Affiche les cités ainsi que le nombre de cités
	*/
 	for (int i = 0; i < NbCite;i++) 
 	{
 		printf("%s\n",TabCite[i].Nom);
 	}
 	printf("\n==(%d) CITE==\n\n",NbCite);
 }
void faffichageetudiant(Etudiant *TabEtud,int NbEtud) 
	{
	/*
	Variables :
		- i : désigne un nombre entier
	Finalité :
		- Affiche les étudiants et leurs informations ainsi que le nombre total d'étudiants
	*/
	for (int i = 0; i < NbEtud;i++) 
	{
		printf("%s %d %d %d %s %s\n",TabEtud[i].IdEtudiant,TabEtud[i].Bourse,TabEtud[i].Echelon,TabEtud[i].Handicap,TabEtud[i].Civilite,TabEtud[i].Nom);
	}
	printf("\n==(%d) ETUDIANTS==\n\n",NbEtud );
	}

void Affichagelogementoccupe(Logement *Tablog,int NbLog,Etudiant *TabEtud, int NbEtud) 
{
	/*
	Variables :
		- i : désigne un nombre entier
		- logoccupe : désigne le nombre de logements occupés
		- comp : comparaison entre les IdEtudiant afin de voir si se sont les mêmes
	Finalité :
		- Affiche les logements occupés et leurs informations ainsi que le nombre de logements occupés
	*/
	int logoccupe=0,comp; 
	printf("\n\n================<LOGEMENTS OCCUPES>=================\n\n"); 
	printf("IdLogement==TypeLog==AdaptHandicap==IdEtudiant==Cite\n\n"); 
	for (int i = 0; i < NbLog;i++)
	{
		if (Tablog[i].Disponible==0) 
		{
			for (int k = 0; k < NbEtud ; k++)
			{
				comp=strcmp(Tablog[i].IdEtudiant,TabEtud[k].IdEtudiant);
				if (comp==0)
				{
					printf("%s    %s\t  %d\t    %s\t%s\t%s\n",Tablog[i].IdLogement,Tablog[i].TypeLog,Tablog[i].AdaptHandicap,Tablog[i].IdEtudiant,TabEtud[k].Nom ,Tablog[i].Cite);
				}
			}
			logoccupe=logoccupe+1;	
			printf("==========    ==\t  =\t    ==========\t===\n");
		}
	}
	printf("\n===(%d) Logement occupes===\n\n",logoccupe);
}


Demande* TraitementDemande(Demande *TabDem,int *NbDem,int *TmaxDem,Logement *Tablog,int NbLog)
{
	/*
	Variables :
		- i : désigne un nombre entier
		- type : comparaison entre les TypeLog affin de voir si se sont les mêmes
		- cite : comparaison entre les Cite afin de voir si se sont les mêmes
		- suite : choix, suite a un logement indisponible afin de savoir si la personne souhaite un conseil ou non sur sa demande
		- conseil : variable retourné par la fonction conseillogement dans le but de trouver le bon logement
		- logdisponible : Nombres de logements disponibles
		- demande : sauvegarder l'Identifiant de la demande affin de la sauvegarder
		- IdEtudiant : l'identifiant de l'étudiant
		- Demande *nvt : tableau de type Demande
	Finalité :
		- PARTIE I : Lancement de la boucle de recherche de logement parfaitement compatible avec la demande	
		- PHASE DE TRANSITION : Demande de conseil dù à l'absence de logement parfaitement compatible à la demande
		- PARTIE II : Cas ou l'utilisateur demande un conseil
		- Ressort le tableau TabDem
	*/
	//PARTIE I
	int type,cite,suite,conseil,logdisponible=0;
	char demande[11],IdEtudiant[11],term;
	Demande *nvt;
	if (*NbDem==0)
	{
		printf("\n ===========TOUTES LES DEMANDES SONT TRAITEES=========\n\n");
		return TabDem;
	}
	for (int i = 0; i < NbLog; i++)
	{
		if (Tablog[i].Disponible==1)
			{
				printf("%s Disponible\n",Tablog[i].IdLogement);
				logdisponible=logdisponible+1;
			}
	}
	printf("\n\n===(%d) Logement Disponible===\n",logdisponible );
	for (int i=0;i<*NbDem;i++)
	{
		for (int j=0; j<NbLog;j++)
		{
			type=strcmp(Tablog[j].TypeLog,TabDem[i].TypeLog);
			cite=strcmp(Tablog[j].Cite,TabDem[i].Cite);
			if(Tablog[j].Disponible==1 && type==0 && cite==0 && TabDem[i].Handicap==Tablog[i].AdaptHandicap)
			{
				strcpy(demande,TabDem[i].IdDemande);
				printf("\n\n==========Demande %s de %s en traitement==========\n",demande,TabDem[i].IdEtudiant);
				strcpy(Tablog[j].IdEtudiant,TabDem[i].IdEtudiant);
				Tablog[j].Disponible=0;
				for (i=i+1;i<*NbDem;i++)
				{
					strcpy(TabDem[i-1].IdDemande,TabDem[i].IdDemande);
					TabDem[i-1].EchelonEtudDem=TabDem[i].EchelonEtudDem;
					strcpy(TabDem[i-1].IdEtudiant,TabDem[i].IdEtudiant);
					strcpy(TabDem[i-1].TypeLog,TabDem[i].TypeLog);
					strcpy(TabDem[i-1].Cite,TabDem[i].Cite);
				}
				printf("\n\n=========Suppression de demande %s valide========\n",demande);
				i=i-1;
				*NbDem=*NbDem-1;
				if(*TmaxDem-*NbDem==5)
				{
					printf("\n===realloc===\n");
					nvt= (Demande*)realloc(TabDem,sizeof(Demande)*(*TmaxDem-5));
					if (nvt==NULL)
					{
						printf("probleme realloc\n");
						exit(1);
					}
					*TmaxDem=*TmaxDem-5;
					TabDem=nvt;
				}
				for (int k=0;k<*NbDem;k++)
				{
					if(*NbDem-*TmaxDem==5)
					{
						printf("\n===realloc===\n");
						nvt= (Demande*)realloc(TabDem,sizeof(Demande)*(*TmaxDem-5));
						if (nvt==NULL)
						{
							printf("probleme realloc\n");
							exit(1);
						}
						*TmaxDem=*TmaxDem-5;
						TabDem=nvt;
					}
					if (strcmp(TabDem[k].IdEtudiant,Tablog[j].IdEtudiant)==0)
					{
						TabDem=MAJDemandeSupp(TabDem,NbDem,k);
						k=k-1;
					}
				}
			printf("\n\n\n==========NOUVEAU TABLEAU DE LOGEMENTS==========\n\n");
			faffichagelogement(Tablog,NbLog);
			printf("\n\n==========NOUVEAU TABLEAU DE DEMANDE==========\n\n");
			faffichagedemande(TabDem,*NbDem);
			return TabDem;
			}
		}
		//PHASE DE TRANSITION
		printf("\n\nLOGEMENTS DESIRE INDISPONIBLE POUR CETTE PERSONNE\n");
		printf("============UN CONSEIL POUR %s ?================\n",TabDem[i].IdEtudiant);
		printf("1 ou 0\n");
		while(scanf("%d%c", &suite, &term) != 2 || term != '\n' || suite < 0 || suite > 1)
		{
			printf("entrer 1 ou 0\n");
			while(getchar() != '\n');
		}
		//PARTIE II
		if (suite==1)
		{
			strcpy(IdEtudiant,TabDem[i].IdEtudiant);
			conseil=Conseillogement(Tablog,NbLog,TabDem[i]);
			if (conseil==1)
			//DANS LE CAS OU L'UTILISATEUR A CHOISIT UN CONSEIL
			{
				for (int j=i+1;j<*NbDem;j++)
				{
					strcpy(TabDem[j-1].IdDemande,TabDem[j].IdDemande);
					TabDem[j-1].EchelonEtudDem=TabDem[j].EchelonEtudDem;
					strcpy(TabDem[j-1].IdEtudiant,TabDem[j].IdEtudiant);
					strcpy(TabDem[j-1].TypeLog,TabDem[j].TypeLog);
					strcpy(TabDem[j-1].Cite,TabDem[j].Cite);
				}
				*NbDem=*NbDem-1;
				for (int k=0;k<*NbDem;k++)
				{
					if(*NbDem-*TmaxDem==5)
					{
						printf("\n===realloc===\n");
						nvt= (Demande*)realloc(TabDem,sizeof(Demande)*(*TmaxDem-5));
						if (nvt==NULL)
						{
							printf("probleme realloc\n");
							exit(1);
						}
						*TmaxDem=*TmaxDem-5;
						TabDem=nvt;
					}
					if (strcmp(TabDem[k].IdEtudiant,IdEtudiant)==0)
					{
						TabDem=MAJDemandeSupp(TabDem,NbDem,k);
						k=k-1;
					}
				}
				printf("=======Demande %s traitee=======\n",TabDem[i].IdEtudiant);
				printf("DEMANDES DESORMAIS EN ATTENTES\n");
				faffichagedemande(TabDem,*NbDem);
				printf("\n%d DEMANDES\n",*NbDem );
				return TabDem;
			}

		}
		if(i+1==*NbDem)
		{
			printf("(((((((AUCUN LOGEMENTS DESIRE DISPONIBLE)))))))\n");
		}
		
	}
	return TabDem;
}

int Conseillogement(Logement *Tablog,int NbLog,Demande demande)
{
	/*
	Variables :
		- j : désigne un nombre entier
		- i : désigne un nombre entier
		- choix : cas où l'utilisateur refuse le logement proposés par le conseil
		- id : comparaison afin de voir si les id correpondant
		- Logement *Tablogconseil : tableau qui répertorie les logements conseilé à l'utilisateur
	Finalité :
		- Propose des logements respectant un seul critère de demande
		- Ressort un nombre désignant si oui ou non l'étudiant a choisi un logement conseillé
	*/
	int j=0,choix,id;
	char term;
	Logement *Tablogconseil;
	Tablogconseil=(Logement*)malloc(sizeof(Logement)*NbLog);
	printf("\n\n===Logement Disponible dans %s===\n\n",demande.Cite);
	if (demande.Handicap==1)
	{
		printf("\n(===LOGEMENTS ADAPTES POUR ETUDIANTS===)\n\n");
	}
	for (int i = 0; i < NbLog;i++)
	{
		if (Tablog[i].Disponible==1 && strcmp(Tablog[i].Cite,demande.Cite)==0 && demande.Handicap==Tablog[i].AdaptHandicap)
		{
			j=j+1;
			printf("%d---%s %s \n",j,Tablog[i].IdLogement,Tablog[i].TypeLog);
			Tablogconseil[j-1]=Tablog[i];		
		}
	}
	printf("\n\n===Logement Disponible de type %s===\n\n",demande.TypeLog);
	for (int i = 0; i < NbLog; i++)
	{
		if (Tablog[i].Disponible==1 && strcmp(Tablog[i].TypeLog,demande.TypeLog)==0 && demande.Handicap==Tablog[i].AdaptHandicap)
		{
			j=j+1;
			printf("%d---%s %s \n",j,Tablog[i].IdLogement,Tablog[i].Cite);
			Tablogconseil[j-1]=Tablog[i];
		}
	}
	printf("\n\n=========LOGEMENT CHOISIT ?=========\n");
	printf("SAISIR 0 : ABANDON LOGEMENT POUR %s\n",demande.IdEtudiant);
	while(scanf("%d%c", &choix, &term) != 2 || term != '\n' || choix < 0 || choix > 1)
	{
			printf("SAISIR 0 : ABANDON LOGEMENT POUR %s\n",demande.IdEtudiant);
			while(getchar() != '\n');
	}
	while(choix!=0)
	{
		if(choix>j)
			{
				printf("Erreur\n");
				scanf("%d",&choix);
			}
		else
		{
			for (int i=0;i< NbLog;i++)
			{
				id=strcmp(Tablogconseil[choix-1].IdLogement,Tablog[i].IdLogement);
				if (id==0)
				{
					strcpy(Tablog[i].IdEtudiant,demande.IdEtudiant);
					Tablog[i].Disponible=0;
					return 1;
				}
			}
		}
	}
	printf("\n\n===========ABANDON===========\n\n");
	return 0;
}

Logement* Liberationlogement(Logement *Tablog,int NbLog,Etudiant *TabEtud,int *NbEtud,Demande *TabDem,int *NbDem,int *trouve)
{
	/*
	Variables :
		- idLog : désigne un identifiant logement lambda 
		- finID : désigne les numéros de l'identifiant que l'étudiant va devoir rentrer
	Finalité :
		- Une fois la saisie d'un identifiant de logement fait, Dans le cas ou le logement existe et est occupé, 
		  le logement se libère excepté le cas ou une demande est parfaitement compatible avec ce logement et où l'utilisateur va accepter de l'intégrer
		- Ressort le tableau de logement Tablog
	*/
	char idLog[11],finID[6];
	strcpy(idLog,"LOGE-");
	printf("%s\n",idLog );
	printf("\n\n\n ====LOGEMENT==== \n\n");
	faffichagelogement(Tablog,NbLog);
	printf("=====Saisir Numéro de Logement=====\n");
	printf("%s",idLog);
	scanf("%s",finID);
	while(strlen(finID)!=5)
	{
		printf("Erreur saisie\n");
		printf("=====Saisir Numéro de Logement=====\n");
		printf("%s",idLog);
		scanf("%s",finID);
	}
	strcat(idLog,finID);
	printf("======%s=====\n",idLog);	
	for (int i = 0; i < NbLog;i++)
	{
		if(strcmp(Tablog[i].IdLogement,idLog)==0)
		{	
			if (Tablog[i].Disponible==1)
			{
				printf("\n=====Logement Trouve mais deja disponible retour=====\n\n");
				*trouve=1;
				return Tablog;
			}
			printf("===>LOGEMENT %s DE %s TROUVE<===\n",Tablog[i].IdLogement,Tablog[i].IdEtudiant);
			strcpy(Tablog[i].IdEtudiant,"XXXXXXXXXX");
			printf("====Liberation logement faite====\n");
			Tablog[i].Disponible=1;
			Tablog[i]=RecherchedemandeLOGEMENT(Tablog[i],TabDem,NbDem);
			printf("\n");
			faffichagelogement(Tablog,NbLog);
			*trouve=1;
			return Tablog;
		}
	}
	printf("Numéro Introuvable\n");
	*trouve=0;
	return Tablog;
}
Logement RecherchedemandeLOGEMENT(Logement logement,Demande *TabDem,int *NbDem)
{
	/*
	Variables :
		- choix : désigne si oui ou non l'utilisateur accepte d'attribuer le logement à la demande
		- i : désigne un entier naturel
	Finalité :
		- Recherche si une demande est parfaitement compatible avec le logement libéré
		- Ressort une structure de type Logement
	*/
	printf("\n\n==========Lancement de la recherche de demande==========\n");
	int choix;
	for (int i = 0; i <*NbDem;i++)
	{
		if (strcmp(TabDem[i].TypeLog,logement.TypeLog)==0 && strcmp(TabDem[i].Cite,logement.Cite)==0)
		{
			printf("DEMANDE %s COMPATIBLE\n ACCEPTER ?\n",TabDem[i].IdDemande);
			scanf("%d",&choix);
			while(choix!=0 && choix!= 1)
			{
				printf("Erreur\n");
				scanf("%d",&choix);
			}
			if (choix==1)
			{
				strcpy(logement.IdEtudiant,TabDem[i].IdEtudiant);
				logement.Disponible=0;
				for (i=i+1;i<*NbDem;i++)
				{
					strcpy(TabDem[i-1].IdDemande,TabDem[i].IdDemande);
					TabDem[i-1].EchelonEtudDem=TabDem[i].EchelonEtudDem;
					strcpy(TabDem[i-1].IdEtudiant,TabDem[i].IdEtudiant);
					strcpy(TabDem[i-1].TypeLog,TabDem[i].TypeLog);
					strcpy(TabDem[i-1].Cite,TabDem[i].Cite);
				}
				*NbDem=*NbDem-1;
				printf("DEMANDE %s SUPPRIMEE\n",TabDem[i].IdDemande);
				printf("REMPLACEMENT ETUDIANTS\n");				
			}
			else
				printf("DEMANDE %s NON TRAITEE\n",TabDem[i].IdDemande);
			return logement;
		}
	}
	printf("=====>AUCUNE DEMANDE POUR CE LOGEMENT<=====\n");
	return logement;
}


int RechercheEtud (Etudiant *TabEtud,int NbEtud,int *trouve,char *e)
{
	/*
	Finalité :
		- Fonction récursive permettant de trouver le rang de l'étudiant dans le tableau
		- Ressort le rang de l'étudiant
	*/
	if (NbEtud==0)
	{
		*trouve=0;
		return 0;
	}
	if (strcmp(e,TabEtud[0].IdEtudiant)==0)
	{
		*trouve=1;
		printf("===ETUDIANTS EXISTANTS===\n");
		return 0;
	}
	if (strcmp(e,TabEtud[0].IdEtudiant)>0)
	{
		return 1 + RechercheEtud(TabEtud+1,NbEtud-1,trouve,e);
	}
	else
	{
		*trouve=0;
		printf("=====RANG TROUVE=====\n");
		return 0;
	}
}


Etudiant* CreationEtudiant (Etudiant *TabEtud,int *NbEtud,int *TmaxEtud)
{
	/*
	Variables :
		- Etudiant e : désigne un étudiant e de structure Etudiant
		- rang : désigne le rang d'insertion de l'étudiant 
		- trouve : désigne si l'étudiant existe déjà ou non dans le tableau
		- retour : permet de vérifier l'erreur de l'identifiant étudiant
		- i : désigne un nombre entier
		- z : désigne un nombre entier
		- nom : nom que l'utilisateur va rentrer
		- finID : numéro de l'identifiant étudiant que l'utilisateur va rentrer
		- prenom : prenom que l'utilisateur va rentrer
		- NOM : identité complète de l'étudiant
		- term : caractère afin d'éviter les erreurs de saisie
	Finalité :
		- Création et insertion d'un étudiant via les informations rentrer par l'utilisateur
		- Ressort le tableau d'étudiant TabEtud avec l'intégration du nouvel étudiant
	*/
	Etudiant e;
	int rang,trouve=1, retour=0,i,z;
	char nom[20],finID[5];
	char prenom[20];
	char NOM[40];
	char term;
	while(trouve==1)
	{
		//NUMERO ETUDIANT
		printf("Saississez les numéros de votre idEtudiant de type  : ETUD-XXXXX\n");
		strcpy(e.IdEtudiant,"ETUD-");
		printf("%s",e.IdEtudiant);
		scanf("%s",finID );

		for(i=0;i<5;i++)
		{
			if (isalpha(finID[i])!=0)
			{
				retour=0;
				break;				
			}
			retour=1;
		}


		while(strlen(finID)!=5 || retour==0)
		{
			printf("Erreur saisie\n");
			printf("Saississez les numéros de votre idEtudiant de type  : ETUD-XXXXX\n");
			strcpy(e.IdEtudiant,"ETUD-");
			printf("%s",e.IdEtudiant);
			scanf("%s",finID );
			for(i=0;i<5;i++)
			{
				if (isalpha(finID[i])!=0)
				{
					retour=0;
					break;				
				}
				retour=1;
			}
		}
		strcat(e.IdEtudiant,finID);
		printf("=====>Num étudiant : %s <=====\n",e.IdEtudiant);
		rang=RechercheEtud(TabEtud,*NbEtud,&trouve,e.IdEtudiant);
		printf("(%d)\n",rang );
		if(trouve==1)
		{
			printf("\n\n===RESSAISIR NUMERO ETUDIANTS====\n");
			printf("ABANDON ? ( 0 = oui & 1 = non )\n");
			while(scanf("%d%c",&trouve, &term) != 2 || term != '\n' || trouve > 1 || trouve < 0)
			{
				printf("ABANDON ? ( 0 = oui & 1 = non )\n");
				while(getchar() != '\n');

			}
			if (trouve==0)
			{
				printf("=======ABANDON SAISIE=======\n");
				exit(1);
			}
		}
	}
	//CIVILITE
	printf("\n===Civilité : MR ou MME ?=== \n");
	scanf("%s", e.Civilite);
	while( (strcmp(e.Civilite,"MR")!=0) && (strcmp(e.Civilite,"MME")!=0))
	{
		printf("Civilité : MR ou MME ? \n");
		scanf("%s", e.Civilite);
	}
	printf("\n===Civilité : %s ===\n", e.Civilite);
	//NOM
	printf("\n===Quel est son nom=== \n");
	scanf(" %s", e.Nom);
	//Transformation majuscule
	for(z=0; e.Nom[z] != '\0' ;z++)
	{
		if(e.Nom[z] >= 'a' && e.Nom[z] <= 'z')
			e.Nom[z] = e.Nom[z] -32;
	}
	printf("\n<Nom : %s >\n", e.Nom);
	//NOM
	printf("\n====Quel est son prénom=== \n");
	scanf("%s", prenom);
	for(z=0; prenom[z] != '\0' ;z++)
	{
		if(prenom[z] >= 'a' && prenom[z] <= 'z')
			prenom[z] = prenom[z] -32;
	}
	printf("\n<Prenom : %s >\n", prenom);
	strcat(e.Nom," ");
	strcat(e.Nom,prenom);
	printf("\nNom complet : %s\n", e.Nom);

	//BOURSE
	printf("\n===<BOURSE ? 0-non et 1-oui>===\n");
	while(scanf("%d%c", &e.Bourse, &term) != 2 || term != '\n' || e.Bourse < 0 || e.Bourse > 1)
	{
		printf("\n===<BOURSE ? 0-non et 1-oui>===\n");
		while(getchar() != '\n');
	}
	if(e.Bourse == 0)
		e.Echelon= 0;
	if(e.Bourse == 1)
	{
		printf("\n===<ECHELON de 0 à 7>===\n");
		while( scanf("%d%c", &e.Echelon, &term) != 2 || (e.Echelon < 0) || (e.Echelon > 7))
		{
			printf("\n===<ECHELON de 0 à 7>===\n");
			while(getchar() != '\n');
		}
	}
	//HANDICAP
	printf("\n===<HANDICAP 0-non et 1-oui>===\n");
	
	while( scanf("%d%c", &e.Handicap, &term) != 2 || term != '\n' || (e.Handicap < 0) || (e.Handicap > 1 ))
	{
		printf("\n===<HANDICAP 0-non et 1-oui>===\n");
		while(getchar() != '\n');
	}
	TabEtud=MAJTabEtud(TabEtud,NbEtud,TmaxEtud,rang,e);
	return TabEtud;
}

Etudiant* MAJTabEtud(Etudiant *TabEtud,int *NbEtud,int *TmaxEtud,int rang,Etudiant e)
{
	/*
	Variables :
		- Etudiant *nvt : *nvtEtud intervient comme tableau intermédiaire dans le but d'augmenter la taille physique de *TabEtud
		- i : désigne un nombre entier
	Finalité :
		- Mettre à jour le tableau TabEtud dans le cas d'une insertion d'étudiant
		- Ressort le tableau d'étudiant TabEtud avec l'intégration du nouvel étudiant
	*/
	Etudiant *nvt;
	if (*NbEtud==*TmaxEtud)
	{
		nvt=(Etudiant*)realloc(TabEtud,sizeof(Etudiant)*(*TmaxEtud+5));
		if (nvt==NULL)
		{
			printf("Probleme realloc\n");
			exit(1);
		}
		*TmaxEtud=*TmaxEtud+5;
		TabEtud=nvt;
	}
	for (int i=*NbEtud-1; i >=rang;i--)
	{
		strcpy(TabEtud[i+1].IdEtudiant,TabEtud[i].IdEtudiant);
		TabEtud[i+1].Bourse=TabEtud[i].Bourse;
		TabEtud[i+1].Echelon=TabEtud[i].Echelon;
		TabEtud[i+1].Handicap=TabEtud[i].Handicap;
		strcpy(TabEtud[i+1].Civilite,TabEtud[i].Civilite);
		strcpy(TabEtud[i+1].Nom,TabEtud[i].Nom);		
	}
	TabEtud[rang]=e;
	*NbEtud=*NbEtud+1;
	return TabEtud;
}

Demande* MAJDemande(Demande *TabDem,int *NbDem,int *TmaxDem,int rang,Demande demande)
{
	/*
	Variables :
		- Demande *nvt : *nvt intervient comme tableau intermédiaire dans le but d'augmenter la taille physique de *TabDem
		- i : désigne un nombre entier
	Finalité :
		- Mettre à jour le tableau TabDem dans le cas d'une insertion de demande
		- Ressort le tableau de demande TabDem avec l'intégration d'une nouvelle demande
	*/
	Demande *nvt;
	if (*NbDem==*TmaxDem)
	{
		nvt=(Demande*)realloc(TabDem,sizeof(Demande)*(*TmaxDem+5));
		if (nvt==NULL)
		{
			printf("Probleme realloc\n");
			exit(1);
		}
		*TmaxDem=*TmaxDem+5;
		TabDem=nvt;
	}
	for (int i = *NbDem; i >rang;i--)
	{
		if (TabDem[i].EchelonEtudDem>=demande.EchelonEtudDem)
		{
			for (int j = *NbDem; j >= i;j--)
			{
			strcpy(TabDem[j+1].IdDemande,TabDem[j].IdDemande);
			strcpy(TabDem[j+1].TypeLog,TabDem[j].TypeLog);
			TabDem[j+1].EchelonEtudDem=TabDem[j].EchelonEtudDem;
			TabDem[j+1].Handicap=TabDem[j].Handicap;
			strcpy(TabDem[j+1].IdEtudiant,TabDem[j].IdEtudiant);
			strcpy(TabDem[j+1].Cite,TabDem[j].Cite);
			}
		TabDem[i]=demande;
		*NbDem=*NbDem+1;
		return TabDem;
		}
			
	}
	TabDem[*NbDem]=demande;
	*NbDem=*NbDem+1;
	return TabDem;
}

Demande* CreationDemande (Demande *TabDem,int *NbDem,int *TmaxDem,Etudiant *TabEtud,int *NbEtud,int *TmaxEtud,Logement *Tablog,int NbLog)
{
	/*
	Variables :
		- Demande demandeur : désigne une structure de type Demande
		- numcite : désigne le numéro de la cité entré par l'utilisateur
		- rangdem : désigne le rang de la demande en fonction de l'échellon de l'étudiant
		- rangetud : désigne le rang de l'étudiant en fonction de son identifiant
		- trouvelog : désigne si l'étudiant est déjà logé ou pas
		- trouvedem : désigne si l'identifiant demande est déjà existant
		- trouveetud : désigne si l'étudiant est déjà existant
		- i : désigne un nombre entier
		- retour : erreur en fonction de la saisie de l'identifiant demande
		- finID : les numéros de l'identifiant que l'utilisateur va rentrer
		- EchelonDem : échelon de l'étudiant
	Finalité :
		- Permet la création d'une damande
		- Ressort le tableau en y intégrant la nouvelle demande
	*/
	Demande demandeur;
	int numcite,rangdem,rangetud,trouvelog,trouvedem=0,trouveetud,str,i,retour;
	char finID[5],term;
	strcpy(demandeur.IdDemande,"DEMA-");
	strcpy(demandeur.IdEtudiant,"ETUD-");
	faffichagedemande(TabDem,*NbDem);
	while(trouvedem==0)
	{
		//NUMERO ETUDIANT
		printf("\nSaississez votre IdDemande de type :XXXXX\n");
		printf("\n%s",demandeur.IdDemande);
		scanf("%s",finID);

		for(i=0;i<5;i++)
		{
			if (isalpha(finID[i])!=0)
			{
				retour=0;
				break;				
			}
			retour=1;
		}

		while(strlen(finID)!=5 || retour==0)
		{
			printf("\n=====<Erreur SAISIE>=====\n");
			printf("\nSaississez votre IdDemande de type :XXXXX\n");
			printf("%s",demandeur.IdDemande);
			scanf("%s",finID);
			for(i=0;i<5;i++)
			{
				if (isalpha(finID[i])!=0)
				{
					retour=0;
					break;				
				}
				retour=1;
			}
		}
		strcat(demandeur.IdDemande,finID);
		rangdem=RechercheDemande(TabDem,*NbDem,&trouvedem,demandeur.IdDemande);
		//CAS OU LA DEMANDE EXISTE DEJA
		if (trouvedem==1)
		{
			printf("\n====DEMANDE DEJA EXISTANTE ABANDON ? 0-non 1-oui====\n");
			while(scanf("%d%c", &trouvedem, &term) != 2 || term != '\n' || trouvedem < 0 || trouvedem >1)
			{
				printf("\n====DEMANDE DEJA EXISTANTE ABANDON ? 0-non 1-oui====\n");
				while(getchar() != '\n');
			}
			if (trouvedem==1)
			{
				printf("\n===>ABANDON<===\n\n");
				return TabDem;
			}
			else
			{
				printf("=========NOUVELLE SAISIE=========\n");
				strcpy(demandeur.IdDemande,"DEMA-");
			}
		}
		else
		{
			trouvedem=1;
		}
	}
	printf("\n===<Num demande : %s>=== \n", demandeur.IdDemande);


		//NUMERO ETUDIANT
		printf("Saississez les numéros de votre idEtudiant de type  : ETUD-XXXXX\n");
		printf("%s",demandeur.IdEtudiant);
		scanf("%s",finID );

		for(i=0;i<5;i++)
		{
			if (isalpha(finID[i])!=0)
			{
				retour=0;
				break;				
			}
			retour=1;
		}


		while(strlen(finID)!=5 || retour==0)
		{
			printf("Erreur saisie\n");
			printf("Saississez les numéros de votre idEtudiant de type  : ETUD-XXXXX\n");
			printf("%s",demandeur.IdEtudiant);
			scanf("%s",finID );
			for(i=0;i<5;i++)
			{
				if (isalpha(finID[i])!=0)
				{
					retour=0;
					break;				
				}
				retour=1;
			}
		}

	strcat(demandeur.IdEtudiant,finID);
	//CAS OU L'ETUDIANT EXISTE & RÉCUPÉRE LES INFORMATIONS NÉCESSAIRES À LA DEMANDE
	rangetud=RechercheEtud(TabEtud,*NbEtud,&trouveetud,demandeur.IdEtudiant);
	if (trouveetud==1)
	{
		printf("\n====CREER UNE DEMANDE 0-non 1-oui ?====\n");
		scanf("%d",&trouveetud);
		if (trouveetud==0)
		{
			printf("\n===>ABANDON<===\n\n");
			return TabDem;
		}
		if (trouveetud==1)
		{
			trouvelog=RechercheLogement(Tablog,NbLog,trouvelog,demandeur.IdEtudiant);
			if (trouvelog==1)
			{
				printf("====ARRET SAISIE DEMANDE====\n\n");
				return TabDem;
			}
			if (trouvelog==0)
			{
				printf("====ETUDIANT SANS LOGEMENT====\n\n");

			}
		}
	}

	printf("<><><><Num étudiant : %s><><><> \n", demandeur.IdEtudiant);
	if (trouveetud==1)
	{
		strcpy(demandeur.IdEtudiant,TabEtud[rangetud].IdEtudiant);
		printf("\n=====(IDENTIFAINT : %s)=====\n",demandeur.IdEtudiant);
		demandeur.EchelonEtudDem=TabEtud[rangetud].Echelon;
		printf("\n=====(ECHELON: %d)=====\n",demandeur.EchelonEtudDem);
		demandeur.Handicap=TabEtud[rangetud].Handicap;
		if (demandeur.Handicap==1)
		{
			printf("\n=====(HANDICAPE : OUI)=====\n");
		}
		else printf("\n=====(HANDICAPE : NON)=====\n");
	}
	else
	{
		printf("=======CreationEtudiant=======\n");
		TabEtud=CreationEtudiantDEMANDE(TabEtud,NbEtud,TmaxEtud,demandeur.IdEtudiant);
		faffichageetudiant(TabEtud,*NbEtud);
		rangetud=RechercheEtud(TabEtud,*NbEtud,&trouveetud,demandeur.IdEtudiant);
		if (trouveetud==1)
		{
			printf("\n=====(%s)ETUDIANTS INSERE=====\n",demandeur.IdEtudiant );
		}
		else
		{
			printf("\n\nprobleme INSERTION\n\n");
		}
		demandeur.EchelonEtudDem=TabEtud[rangetud].Echelon;
		demandeur.Handicap=TabEtud[rangetud].Handicap;
	}
	//TYPE LOGEMENT
	printf("\n=======<Saisissez votre type de logement shouaité : T1 / T2 / CH / ST>======\n");
	scanf("%s", demandeur.TypeLog);
	while(strcmp(demandeur.TypeLog,"T2")!=0 &&strcmp(demandeur.TypeLog,"T1")!=0 && strcmp(demandeur.TypeLog,"CH")!=0 && strcmp(demandeur.TypeLog,"ST")!=0 )
	{
		printf("\nErreur saisie\n");
		printf("\n=======<Saississez votre type de logement shouaité : T1 / T2 / CH / ST>======\n");
		scanf("%s", demandeur.TypeLog);
	}
	printf("\n======Type de logement : %s====== \n", demandeur.TypeLog);
	//Cité
	printf("\n===<Dans quel cité ? (Entrer le nombre correspondant)>=== \n");
	printf("\n");
	printf("1 - Cite U Arc de Meyran\n");
	printf("2 - Cite U Alice Chatenoud\n");
	printf("3 - Cite U Claude Delorme\n");
	printf("4 - Cite U Galinat\n");
	printf("5 - Cite Gaston Berger\n");
	printf("6 - Cite Lucien Cornil\n");
	printf("7 - Cite Luminy\n");
	printf("8 - Residence Canada\n");
	printf("9 - Residence La Garidelle\n\n");

	while( scanf("%d%c", &numcite, &term) != 2 || term != '\n' || numcite < 0 || numcite>9 )
	{
		printf("\n===<ERREUR> (Entrer le nombre correspondant)>=== \n");
		printf("\n");
		printf("1 - Cite U Arc de Meyran\n");
		printf("2 - Cite U Alice Chatenoud\n");
		printf("3 - Cite U Claude Delorme\n");
		printf("4 - Cite U Galinat\n");
		printf("5 - Cite Gaston Berger\n");
		printf("6 - Cite Lucien Cornil\n");
		printf("7 - Cite Luminy\n");
		printf("8 - Residence Canada\n");
		printf("9 - Residence La Garidelle\n\n");
		while(getchar() != '\n');
	}

	if(numcite==1)
		memcpy(demandeur.Cite, "Cite U Arc de Meyran", 30);
	if(numcite==2)
		memcpy(demandeur.Cite, "Cite U Alice Chatenoud", 30);
	if(numcite==3)
		memcpy(demandeur.Cite, "Cite U Claude Delorme", 30);
	if(numcite==4)
		memcpy(demandeur.Cite, "Cite U Galinat", 30);
	if(numcite==5)
		memcpy(demandeur.Cite, "Cite Gaston Berger", 30);
	if(numcite==6)
		memcpy(demandeur.Cite, "Cite Lucien Cornil", 30);
	if(numcite==7)
		memcpy(demandeur.Cite, "Cite Luminy", 30);
	if(numcite==8)
		memcpy(demandeur.Cite, "Residence Canada", 30);
	if(numcite==9)
		memcpy(demandeur.Cite, "Residence La Garidelle", 30);


	
	printf("Cité  : %s \n", demandeur.Cite);
	printf("Demande crée : \n");
	printf("\n===|%s %d  %d %s %s  %s|===\n\n", demandeur.IdDemande, demandeur.EchelonEtudDem,demandeur.Handicap , demandeur.IdEtudiant, demandeur.TypeLog, demandeur.Cite);
		
	TabDem=MAJDemande(TabDem,NbDem,TmaxDem,rangdem,demandeur);
	faffichagedemande(TabDem,*NbDem);
	return TabDem;
}

int RechercheDemande(Demande *TabDem,int NbDem,int *trouve,char *iddemande)
{
	/*
	Variables :
		- i : désigne un nombre entier
	Finalité :
		- Permet de rechercher une demande dans le tableau *TabDem
		- Ressort le rang et renseigne s'il existe ou non dans le tableau
	*/
	for (int i = 0; i < NbDem;i++)
	{
		if (strcmp(iddemande,TabDem[i].IdDemande)==0)
		{
			printf("\n<========DEMANDE-EXISTANTE==========>\n");
			*trouve=1;
			return i;
		}
	}
	printf("\n==========DEMANDE NON EXISTANTE=========\n");
	*trouve=0;
	return 0;
}


int RechercheLogement(Logement *Tablog,int NbLog,int trouve,char *idetudiant)
{
	/*
	Variables :
		- i : désigne un nombre entier
	Finalité :
		- Permet de rechercher un logement dans le tableau *Tablog
		- Ressort si le logement existe ou non dans le tableau
	*/
	for (int i = 0; i < NbLog;i++)
	{
		if (strcmp(Tablog[i].IdEtudiant,idetudiant)==0)
		{
			printf("===ETUDIANT DEJA DANS UN LOGEMENT\n\n");
			trouve=1;
			return trouve;
		}
	}
	trouve=0;
	return trouve;
}

Etudiant* CreationEtudiantDEMANDE (Etudiant *TabEtud,int *NbEtud,int *TmaxEtud,char *idetudiant)
{
	/*
	Variables :
		- Etudiant e : désigne une structure de type Etudiant
		- rang : désigne le rang d'insertion
		- trouve : si l'étudiant existe déjà
		- nom : nom rentré par l'utilisateur
		- prenom : prénom rentré par l'utilisateur
	Finalité :
		- Permet la création d'un étudiant et l'insertion dans le tableau
		- Ressort le tableau étudiant TabEtud avec le nouvel étudiant
	*/

	Etudiant e;
	int rang,trouve=1,z;
	char nom[20],term;
	char prenom[20];
	strcpy(e.IdEtudiant,idetudiant);
	printf("%s\n",e.IdEtudiant);
	//CIVILITE
	printf("\n===Civilité : MR ou MME=== \n");
	scanf("%s", e.Civilite);
	while( (strcmp(e.Civilite,"MR")!=0) && (strcmp(e.Civilite,"MME")!=0))
	{
		printf("\n===Civilité : MR ou MME=== \n");
		scanf("%s", e.Civilite);
	}
	printf("==<Civilité : %s>== \n", e.Civilite);
	//NOM
	printf("\n===<NOM>====\n");
	scanf(" %s", e.Nom);
	printf("\nNom : %s \n", e.Nom);
	//Transformation majuscule
	for(z=0; e.Nom[z] != '\0' ;z++)
	{
		if(e.Nom[z] >= 'a' && e.Nom[z] <= 'z')
			e.Nom[z] = e.Nom[z] -32;
	}
	printf("\n<Nom : %s >\n", e.Nom);
	//NOM
	printf("===<PRENOM>=== \n");
	scanf("%s", prenom);
	for(z=0; prenom[z] != '\0' ;z++)
	{
		if(prenom[z] >= 'a' && prenom[z] <= 'z')
			prenom[z] = prenom[z] -32;
	}
	printf("\nPrenom : %s \n", prenom);
	strcat(e.Nom," ");
	strcat(e.Nom,prenom);
	printf("\n<Nom complet : %s>\n", e.Nom);

	//BOURSE
	printf("\n==<Bourse 0-non et 1-oui>==\n");
	while(scanf("%d%c", &e.Bourse, &term) != 2 || term != '\n' || e.Bourse < 0 || e.Bourse > 1)
	{
		printf("\n===<BOURSE ? 0-non et 1-oui>===\n");
		while(getchar() != '\n');
	}
	if(e.Bourse == 0)
		e.Echelon= 0;
	if(e.Bourse == 1)
	{
		printf("\n===<ECHELON de 0 à 7>===\n");
		while( scanf("%d%c", &e.Echelon, &term) != 2 || (e.Echelon < 0) || (e.Echelon > 7))
		{
			printf("\n===<ECHELON de 0 à 7>===\n");
			while(getchar() != '\n');
		}
	}
	//HANDICAP
	printf("\n===<HANDICAP 0-non et 1-oui>===\n");
	
	while( scanf("%d%c", &e.Handicap, &term) != 2 || (e.Handicap < 0) || (e.Handicap > 1 ))
	{
		printf("\n===<HANDICAP 0-non et 1-oui>===\n");
		while(getchar() != '\n');
	}
	rang=RechercheEtud (TabEtud,*NbEtud,&trouve,e.IdEtudiant);
	TabEtud=MAJTabEtud(TabEtud,NbEtud,TmaxEtud,rang,e);
	return TabEtud;
}

Demande* SuppressionDemande(Demande *TabDem,int *NbDem,int *TmaxDem)
{
	/*
	Variables :
		- IdDemande : désigne l'identifiant de la demande
		- finID : désigne les numéros de l'identifiant
		- rang : désigne le rang de la demande
		- trouve : voir si la demande existe
		- Demande *nvt : interviens comme tableau intermédiaire dans le but de réduire la taille physique de *TabDem
	Finalité :
		- Permet de supprimer une demande
		- Ressort le tableau TabDem
	*/
	char IdDemande[11],finID[6];
	int rang,trouve;
	Demande *nvt;
	strcpy(IdDemande,"DEMA-");
	faffichagedemande(TabDem,*NbDem);
	printf("\n========<SUPPRESION>========\n");
	printf("\n<SAISIR IDENTIFAINT DEMANDE>\n");
	printf("%s",IdDemande);
	scanf("%s",finID);
	strcat(IdDemande,finID);
	printf("%s\n",IdDemande );
	rang=RechercheDemande(TabDem,*NbDem,&trouve,IdDemande);
	while(strlen(finID)!=5 || trouve==0)
	{
		strcpy(IdDemande,"DEMA-");
		printf("\n=====<DEMANDE NON TROUVEE>=====\n");
		printf("\n========<SUPPRESION>========\n");
		printf("\n<SAISIR IDENTIFAINT DEMANDE>\n");
		printf("%s",IdDemande);
		scanf("%s",finID);
		strcat(IdDemande,finID);
		rang=RechercheDemande(TabDem,*NbDem,&trouve,IdDemande);
	}
	printf("\n%s %d %d %s %s %s\n",TabDem[rang].IdDemande,TabDem[rang].EchelonEtudDem,TabDem[rang].Handicap,TabDem[rang].IdEtudiant ,TabDem[rang].TypeLog,TabDem[rang].Cite );
	TabDem=MAJDemandeSupp(TabDem,NbDem,rang);
	if (*TmaxDem-*NbDem==5)
	{
		printf("\n========realloc=======\n");
		nvt=(Demande*)realloc(TabDem,sizeof(Demande)*(*TmaxDem-5));
		if (nvt==NULL)
		{
			printf("Probleme realloc\n");
			exit(1);
		}
		*TmaxDem=*TmaxDem-5;
		TabDem=nvt;
	}
	printf("\n====<NOUVEAU TABLEAU DE DEMANDE>=====\n");
	faffichagedemande(TabDem,*NbDem);
	return TabDem;
}

Demande* MAJDemandeSupp(Demande *TabDem,int *NbDem,int rang)
{
	/*
	Variables :
		- i : désigne un nombre entier
	Finalité :
		- Permet de supprimer une demande
		- Ressort le tableau TabDem tout en modifiant le nombre de demandes
	*/	
	for (int i = rang; i < *NbDem;i++)
	{
		strcpy(TabDem[i].IdDemande,TabDem[i+1].IdDemande);
		strcpy(TabDem[i].TypeLog,TabDem[i+1].TypeLog);
		TabDem[i].EchelonEtudDem=TabDem[i+1].EchelonEtudDem;
		TabDem[i].Handicap=TabDem[i+1].Handicap;
		strcpy(TabDem[i].IdEtudiant,TabDem[i+1].IdEtudiant);
		strcpy(TabDem[i].Cite,TabDem[i+1].Cite);
	}
	*NbDem=*NbDem-1;
	return TabDem;
}


void SavEtudiant (Etudiant *TabEtud,int NbEtud)
{
	/*
	Variables :
		- i : désigne un nombre entier
	Finalité :
		- Permet de sauvegarder le tableau Etudiant
	*/	
	FILE *fe;
	fe=fopen("Etudiant.don","w");
	if(fe==NULL)printf("Erreur sauvegarde étudiant\n");
	for (int i = 0; i < NbEtud;i++)
	{
		fprintf(fe,"%s %d %d %d %s %s\n",TabEtud[i].IdEtudiant,TabEtud[i].Bourse,TabEtud[i].Echelon,TabEtud[i].Handicap,TabEtud[i].Civilite,TabEtud[i].Nom);
	}
	fclose(fe);

}

void SavDemande (Demande *TabDem,int NbDem)
{
	/*
	Variables :
		- i : désigne un nombre entier
	Finalité :
		- Permet de sauvegarder le tableau Demande
	*/	
	FILE *fe;
	fe=fopen("Demande.don","w");
	if(fe==NULL)printf("Erreur sauvegarde étudiant\n");
	for (int i = 0; i < NbDem;i++)
	{
		fprintf(fe,"%s %s %d %d %s %s\n",TabDem[i].IdDemande,TabDem[i].TypeLog,TabDem[i].EchelonEtudDem,TabDem[i].Handicap,TabDem[i].IdEtudiant,TabDem[i].Cite);
	}
	fclose(fe);

}

void SavLogement (Logement *TabLog,int NbLog)
{
	/*
	Variables :
		- i : désigne un nombre entier
	Finalité :
		- Permet de sauvegarder le tableau Logement
	*/	
	FILE *fe;
	fe=fopen("Logement.don","w");
	if(fe==NULL)printf("Erreur sauvegarde étudiant\n");
	for (int i = 0; i < NbLog;i++)
	{
		fprintf(fe,"%s %s %d %d %s %s\n",TabLog[i].IdLogement,TabLog[i].TypeLog,TabLog[i].Disponible,TabLog[i].AdaptHandicap,TabLog[i].IdEtudiant,TabLog[i].Cite);
	}
	fclose(fe);

}

