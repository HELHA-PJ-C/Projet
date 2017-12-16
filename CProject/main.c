#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Medecin Medecin;
struct Medecin{
    char nom[31], prenom[31], inami[15], specialite[21], heureDeb[9], heureFin[9];
    struct Medecin *suivant;
} ;

typedef struct Patient Patient;
struct Patient {
    char nom[31], prenom[31], niss[14], dateNaissance[11];
    int age;
    struct Patient *suivant;
    struct Prestation *presfinal, *presnouveau;
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
        int scan=0, nPres=0, nMed=0, nPat=0, i, numero, present, nPrest;
        char inami[15], numRegNat[13];
        FILE *patdat, *meddat, *stdat, *ophdat, *orldat;
        Medecin *medcourant, *medintervale, *medfirst, *medsuivant;
        Patient *patfirst, *patcourant, *patintervale, *patsuivant;
        Prestation *prescourant, *presfirst, *pressuivant;
        void ajouterPatient(char[], Patient *, FILE *), ajouterPrestation(Patient *, int, char[]);
        struct Patient rechercherPatient(Patient *, int, int*);
        struct Medecin rechercherMedecin(Medecin *, int, int*);

        patdat=fopen("patient.dat","r");
        meddat=fopen("medecin.dat","r");
        stdat=fopen("stomato.dat","r");
        ophdat=fopen("ophtalmo.dat","r");
        orldat=fopen("orl.dat","r");

        while(scan<1|| scan >3){
            printf("Bienvenue dans votre programme de gestion.\n1. Encoder prestation\n2. Rechercher patient\n3. Prise de rendez-vous\n");
            scanf("%1d", &scan);
            if(scan<1|| scan >3) {
                printf("Commande inexistante\n");
            }
        }

        //Lecture de medecin.dat

        medcourant=malloc(sizeof(Medecin));
        fscanf(meddat,"%14s", medcourant->inami);
        medfirst=medcourant;

        while(!feof(meddat))
        {
            nMed++;
            fscanf(meddat,"%20s",medcourant->specialite);
            fgets(medcourant->prenom, 30, meddat);
            fgets(medcourant->nom, 30, meddat);
            fscanf(meddat,"%8s %8s", medcourant->heureDeb, medcourant->heureFin);
            medsuivant=malloc(sizeof(Medecin));
            medcourant->suivant=medsuivant;
            medcourant=medsuivant;
            fscanf(meddat,"%14s", medcourant->inami);
        }
        medcourant->suivant=NULL;


        //Lecture de patient.dat

        patcourant=malloc(sizeof(Patient));
        fscanf(patdat,"%13s", patcourant->niss);
        patfirst=patcourant;


        while(!feof(patdat))
        {
            nPat++;
            fgets(patcourant->nom, 30, patdat);
            fgets(patcourant->prenom, 30, patdat);
            fscanf(patdat,"%10s %d", patcourant->dateNaissance, &nPrest);


            for(i=0;i<nPrest;i++){
                prescourant=malloc(sizeof(Prestation));
                fscanf(patdat,"%6d", &prescourant->num);
                fgets(prescourant->libelle, 100, patdat);
                patcourant->presfinal=prescourant;

            }
            patsuivant=malloc(sizeof(Patient));
            patcourant->suivant=patsuivant;
            patcourant=patsuivant;
            fscanf(patdat,"%13s", patcourant->niss);

        }
        patcourant->suivant=NULL;
        fclose(patdat);


        //Partie 1 : Encoder une prestation

        if(scan==1){

            //encoderPrestation();
        }

        //Partie 2 : rechercher un patient

        else if(scan==2){
            *patcourant=rechercherPatient(patfirst, nPat, &present);
            if(present==1)
            {
                printf("%13s %-30s %-30s\n", patcourant->niss, patcourant->nom, patcourant->prenom);
            }
            else
            {
                printf("Patient non présent dans les données\n");
            }

        }

        //partie 3 : prendre rendez-vous

        else{
            //PrendreRendezVous();
        }

        //Encoder prestation

        //Recherche du médecin
        present=0;
        while(present==0)
        {
            *medcourant=rechercherMedecin(medfirst, nMed, &present);
            if(present==0)
            {
                printf("Erreur : médecin inexistant");
            }
        }


        //recherche du patient
        *patcourant=rechercherPatient(patfirst, nPat, &present);




        //Si le patient n'est pas dans le fichier, on l'ajoute
        if(present==0)
        {
            ajouterPatient(numRegNat, patcourant, &patdat);
            nPat++;
        }
/*
        //Partie 3 : trouver la prestation
        printf("Encoder numéro de prestation");
        scanf("%6d",&numero);
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
        }
        prescourant->suivant=NULL;



        for(i=0;i<nPres;i++){
            if(prescourant->num==numero){
                i=nPres;
            }
        }

        ajouterPrestation(patcourant, numero, prescourant->libelle);
*/
}

void ajouterPatient(char numRegNat[13], Patient *patcourant, FILE *patdat)
{
    *patdat=fopen("patient.dat","a");
    Patient *patsuivant;
    patsuivant=malloc(sizeof(Patient));
    patcourant->suivant=patsuivant;
    patcourant=patsuivant;
    patcourant->niss=numRegNat;
    printf("Nom du patient : ");
    scanf("%30s", patcourant->nom);
    printf("Prénom du patient : ");
    scanf("%30s", patcourant->prenom);
    priintf("Date de naissance du patient : ");
    scanf("%10s", patcourant->dateNaissance);
    fprintf(*patdat,"\n%13s %-30s %-30s %10s ", patcourant->niss, patcourant->nom, patcourant->prenom, patcourant->dateNaissance);
}
/*
void ajouterPrestation(Patient *patcourant, int numero, char nomPres[100])
{
    patcourant->presnouveau=malloc(sizeof(Prestation));
    patcourant->presfinal->suivant=patcourant->presnouveau;
    patcourant->presnouveau->suivant=NULL;
    patcourant->presnouveau->num=numero;
    *patcourant->presnouveau->libelle=nomPres;
}*/

struct Patient rechercherPatient(Patient *patfirst, int nPat, int *present)
{
    int i;
    char numRegNat[14];
    Patient *patcourant;
    printf("Encoder numéro du registre national du patient\n");
    scanf("%13s", numRegNat);

    *present=0;
    patcourant=patfirst;
    for(i=0;i<nPat;i++)
    {
        //On vérifie que le patient est dans la liste
        if(strcmp(patcourant->niss,numRegNat)==0)
        {
            i=nPat;
            *present=1;
        }
        else
        {
            patcourant=patcourant->suivant;
        }
    }
    return *patcourant;
}

struct Medecin rechercherMedecein(Medecin *medfirst, int nMed, int *present)
{
    int i;
    char inami[15];
    Medecin *medcourant;

    printf("Numéro inami : ");
    scanf("%14s", inami);

    medcourant=medfirst;
    for(i=0;i<nMed;i++)
    {
        if(strcmp(medcourant->inami, inami)==0)
        {
            i=nMed;
            *present=1;
        }
        else
        {
            medcourant=medcourant->suivant;
        }
    }
    return *medcourant;
};
