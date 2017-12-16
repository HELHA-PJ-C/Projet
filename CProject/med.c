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

int main()
{
	FILE*fdat;
	fdat = fopen("medecin.dat","r");

	meds *tete, *courant, *medsuivant;
	courant = malloc(sizeof(meds));
	int i,j;
	tete = courant;	
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

}
