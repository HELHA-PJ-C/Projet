#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct meds meds;
struct meds
{
	struct meds *suivant;
	char inami[15],spec[21],prenom[31],nom[31],start[9],end[9];
};

typedef struct pats pats;
struct pats
{
	struct pats *suivant;
	char nom[31], prenom[31], niss[14], dateNaissance[11];
	int age;
};

int main()
{
	FILE*fdat,*fpat;
	fpat = fopen("patients.dat","r");
	fdat = fopen("medecin.dat","r");
	pats *ptete,*pcourant,*psuivant,*pfirst;
	meds *tete, *courant, *medsuivant,*medfirst;
	pcourant = malloc(sizeof(pats));
	courant = malloc(sizeof(meds));
	int i,j;
	tete = courant;	
	medfirst = courant;
	
	fscanf(fdat,"%14s",courant->inami);
	while(!feof(fdat))
	{
		j++;
		fscanf(fdat,"%20s %30s %30s %8s %8s",courant->spec,courant->prenom,courant->nom,courant->start,courant->end);
		medsuivant = malloc(sizeof(meds));
		courant->suivant = medsuivant;
		courant = medsuivant;
		fscanf(fdat,"%14s",courant->inami);
	}
	courant->suivant = NULL;
	courant = tete;
	for(i = 0; i <= j; i++)
	{
		printf("%-14s %-20s %-30s %-30s %-8s %-8s\n",courant->inami,courant->spec,courant->prenom,courant->nom,courant->start,courant->end);
		courant = courant->suivant;
	}
	int p;
	
	
	int ret1;
	int ret2;

	
	time_t rawtime;
	struct tm *tminfo;
	time(&rawtime);
	tminfo = localtime(&rawtime);
	char timeString[9];
	printf("Medecins disponibles maintenant à cette heure ci ");
	strftime(timeString,sizeof(timeString),"%H:%M:%S", tminfo);
	printf("(%s)\n",timeString);
	
	printf("------------------------------------------------------------\n\n");
	courant = medfirst;
	for(i = 0; i<=j;i++)
	{
		ret1 = strcmp(timeString,courant->start);
		ret2 = strcmp(timeString,courant->end);
		if(ret1 > 0 && ret2 < 0)
		{
			printf("%-14s %-20s %-30s %-30s %-8s %-8s\n",courant->inami,courant->spec,courant->prenom,courant->nom,courant->start,courant->end);
		}
		courant = courant->suivant;
	}

	printf("\n");
	char bjr[8];

	scanf("%7s",&bjr);
	
}

