#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Medecin Medecin;
struct Medecin{
    char nom[31], prenom[31], inami[15];
    int heureDeb, heureFin;
    struct Medecin *suivant;
} ;

typedef struct Patient Patient;
struct Patient {
    char nom[31], prenom[31], niss[14], dateNaissance[11];
    int age;
    struct Patient *suivant;
} ;

typedef struct Prestation Prestation;
struct Prestation{
    int num;
    float prix;
    char libelle[101];
    struct Prestation *suivant;
};

main()
{
        int scan=0, nPres=0, nMed=1, nPat=1, i, numero;
        char inami[15], numRegNat;
        FILE *patdat, *meddat, *stdat, *ophdat, *orldat;
        Medecin *medcourant, *medintervale, *medfisrt, *medsuivant;
        Patient *patcourant, *patintervale, *patcourant, *patsuivant;
        Prestation *prescourant, *presfirst, *pressuivant;

        patdat=fopen("patient.dat","r");
        meddat=fopen("medecin.dat","r");
        stdat=fopen("stomato.dat","r");
        ophdat=fopen("ophtalmo.dat","r");
        orldat=fopen("orl.dat","r");

        while(scan<1|| scan >3{
            printf("Bienvenue dans votre programme de gestion.\n1. Encoder prestation\n2. Rechercher patient\n3. Prise de rendez-vous\n");
            scanf("%1d", scan);
            if(scan<1|| scan >3) {
                printf("Commande inexistante\n");
            }
        }

        if(scan==1){

            encoderPrestation();
        }

        else if(scan==2){
            rechercherPatient();
        }

        else{
            PrendreRendezVous();
        }

        //Encoder prestation

        //Partie 1 : Trouver le médecin
        printf("Numéro inami : ");
        gets(inami, 14);
        medcourant = medfirst;
        for(i=0;i<nMed;i++){
            if(strcmp(inami, medcourant->inami)==0){
                i=nMed;
            }
            else{
                medcourant = medcourant->suivant;
            }
        }

        //Partie 2 : trouver le patient.
        printf("Encoder numéro du registre national du patient");
        scanf("%13s", numRegNat);

        patcourant=malloc(sizeof(patcourant));
        fscanf(patdat,"%13s", patcourant->niss);
        patfirst=patcourant;
        while(!feof(patdat)){
            nPat++;
            fgets(patcourant->nom, 29, patdat);
            fgets(patcourant->prenom, 29, patdat);
            fscanf(patdat,"%10s", patcourant->dateNaissance);

        }



        //Partie 3 : trouver la prestation
        prescourant=malloc(sizeof(Prestation));
        if(strcmp(medcourant->specialite,"stomatologue")==0){
            prescourant=fscanf(stdat,"%6d", &prescourant->num);
            presfirst=prescourant;
            while(!feof(stdat)){
                nPres++;
                fgets(prescourant->libelle, 100, stdat);
                pressuivant=malloc(sizeof(Prestation));
                prescourant->suivant=pressuivant;
                prescourant=pressuivant;
                prescourant=fscanf(stdat,"%6d", &prescourant->num);
            }
        }
        else if(strcmp(medcourant->specialite,"ophtalmologue")==0){
            prescourant=fscanf(ophdat,"%6d", &prescourant->num);
            presfirst=prescourant;
            while(!feof(ophdat)){
                nPres++;
                fgets(prescourant->libelle, 100, ophdat);
                pressuivant=malloc(sizeof(Prestation));
                prescourant->suivant=pressuivant;
                prescourant=pressuivant;
                prescourant=fscanf(ophdat,"%6d", &prescourant->num);
        }
        else{
            prescourant=fscanf(orldat,"%6d", &prescourant->num);
            presfirst=prescourant;
            while(!feof(orldat)){
                nPres++;
                fgets(prescourant->libelle, 100, orldat);
                pressuivant=malloc(sizeof(Prestation));
                prescourant->suivant=pressuivant;
                prescourant=pressuivant;
                prescourant=fscanf(orldat,"%6d", &prescourant->num);
        }
        prescourant->suivant=null;

        //Partie2

        //Partie 3 : trouver le nom de la prestation
        printf("Encoder numéro de prestation");
        scanf("%6d",&numero)
        for(i=0;i<nPres;i++){
            if(prescourant->num==numero){
                i=nPres;
            }
        }
        printf("%-s",prescourant->libelle);

}
