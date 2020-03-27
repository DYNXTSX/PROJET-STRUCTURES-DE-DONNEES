# PROJET STRUCTURES DE DONNEES
**GESTION DES LOGEMENTS DU CROUS**
> Avec C.TOFFIN, Y.SEVRET & A.GOLFIER EN A1P2 de DUT Info.

---
## SOMMAIRE
   - [Structures des fichiers](#structure)
   - [Définition des structures](#bonjour)
   - [Chargement des fichiers](#contributing)
   - [Affichage des logements disponibles par cité](#team)
   - [Affichage de la liste des logements occupés](#faq)
   - [Affichage des demandes de logement en attente](#support)
   - [Traitement des demandes en attentes](#license)
   - [Saisie d'une nouvelle demande](#license)
   - [Annulation d'une demande](#license)
   - [Libération de logement](#license)
   - [Sauvegarde](#license)
   
---
## Structures des fichiers

### Fichier I : "Etudiant.don"

Ce fichier contient un nombre de ligne indéterminé triées par identifiant. Chaque ligne de
celui-ci définit un seul étudiant comportant ces informations suivantes :
   - Un identifiant d’étudiant sous la forme « ETUD – XXXXX »
   - Un code booléen ( 1-vrai ou 0-non ) qui détermine si l’étudiant est boursier ou non
   - Un numéro ( 0 à 7 ) qui détermine l’échelon de l’étudiant
   - Un code booléen ( 1-vrai ou 0-non ) qui détermine si l’étudiant est handicapé ou non
   - La civilité de l’étudiant ( MR ou MME )
   - Nom, Prénom de l’étudiant

### Fichier II : "Logement.don"

Ce fichier contient un nombre de ligne indéterminé non triées. Chaque ligne de celui-ci
définit un seul logement comportant ces informations suivantes :
   - Un identifiant de logement sous la forme « LOGE-XXXXX »
   - Un type de logement ( T2, T1, ST = Studio, CH = Chambre )
   - Un code booléen ( 1-vrai ou 0-non ) qui détermine si le logement est disponible ou non
   - Un second code booléen ( 1-vrai ou 0-non ) qui détermine si le logement est adapté pour une personne à mobilités réduite
   - Un identifiant d’étudiant si celui-ci est habité ou « XXXXXXXXXX » si celui-ci est disponible
   -La Cité où se situe le logement

### Fichier III : "Demande.don"

Ce fichier contient un nombre de ligne indéterminé triées par échelon. Chaque ligne de
celui-ci définit une seule demande comportant ces informations suivantes :
   - Un identifiant de demande sous la forme « DEMA-XXXXX »
   - Un type de logement ( T2, T1, ST = Studio, CH = Chambre )
   - L’echelon de l’étudiant demandeur ( 0 à 7 )
   - Un code booléen ( 1-vrai ou 0-non ) qui détermine si l’étudiant demandeur possède un
   handicape ou non
   - L’identifiant de l’étudiant demandeur
   - La Cité où l’étudiant souhaite résider

### Fichier IV : "Cite.don"

Ce fichier contient un nombre de ligne déterminé et précisé dès la première ligne de celui-ci.
Chaque ligne est essentiellement constituée d’un Nom de cité.

---
## Définition des structures

### Structure I : Etudiant

Cette structure contient :
   - une chaîne de caractères pour l’identifiant étudiant
   - Trois entier représentant la bourse, l’échelon ainsi que l’handicape de l’étudiant
   - une chaîne de caractères pour la civilité de celui-ci
   - une chaîne de caractères contenant le nom et le prénom de l’étudiant

```c
typedef struct
{
   char IdEtudiant[11];
   int Bourse, Echelon, Handicap;
   char Civilite[4],Nom[40];
}Etudiant;
```













