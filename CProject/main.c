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
    int age, nPrest;
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
        int scan=0, nPres=0, nMed=1, nPat=1, i, numero, present;
        char inami[15], numRegNat;
        FILE *patdat, *meddat, *stdat, *ophdat, *orldat;
        Medecin *medcourant, *medintervale, *medfirst, *medsuivant;
        Patient *patcourant, *patintervale, *patsuivant;
        Prestation *prescourant, *presfirst, *pressuivant;
        void ajouterPatient(char[], Patient *), ajouterPrestation(Patient *, int, char[]);

        patdat=fopen("patient.dat","r");
        meddat=fopen("medecin.dat","r");
        stdat=fopen("stomato.dat","r");
        ophdat=fopen("ophtalmo.dat","r");
        orldat=fopen("orl.dat","r");

        while(scan<1|| scan >3){
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
        //gets(inami, 14);
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
        //Lecture du fichier
        printf("Encoder numéro du registre national du patient");
        scanf("%13s", numRegNat);

        patcourant=malloc(sizeof(Patient));
        fscanf(patdat,"%13s", patcourant->niss);
        patfirst=patcourant;
        while(!feof(patdat))
        {
            nPat++;
            fgets(patcourant->nom, 29, patdat);
            fgets(patcourant->prenom, 29, patdat);
            fscanf(patdat,"%10s, %d", patcourant->dateNaissance, &patcourant->nPrest);
            for(i=0;i<nPrest;i++){
                fscanf(patdat,"%6d %100s", &patcourant->presfinal->num, patcourant->presfinal->libelle);
            }
            patsuivant=malloc(sizeof(Patient));
            patcourant->suivant=patsuivant;
            patcourant=patsuivant;
            fscanf(patdat,"%13s", patcourant->niss);
        }
        patcourant->suivant=NULL;

        //trouver patient
        patcourant=patfirst;
        present=0;
        for(i=0;i<nPat;i++)
        {
            //On vérifie que le patient est dans la liste
            if(strcmp(patcourant->niss,numRegNat)==0)
            {
                i=nPat;
                present=1;
            }
            else
            {
                patcourant=patcourant->suivant;
            }
        }

        //Si le patient n'est pas dans le fichier, on l'ajoute
        if(present==0)
        {
            ajouterPatient(numRegNat, patcourant);
            nPat++;
        }

        //Partie 3 : trouver la prestation
        printf("Encoder numéro de prestation");
        scanf("%6d",&numero)
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

}

void ajouterPatient(char numRegNat[13], Patient *patcourant)
{
    Patient *patsuivant;
    patsuivant=malloc(sizeof(Patient));
    patcourant->suivant=patsuivant;
    patcourant=patsuivant;
    patcourant->niss=numRegNat;
    printf("Nom du patient : ");
    scanf("%30s", patcourant->nom);
    printf("Prénom du patient : ");
    scanf("%30s", patcourant->prenom);
}

void ajouterPrestation(Patient *patcourant, int numero, char nomPres[100])
{
    patcourant->presnouveau=malloc(sizeof(Prestation));
    patcourant->presfinal->suivant=patcourant->presnouveau;
    patcourant->presnouveau->suivant=NULL;
    patcourant->presnouveau->num=numero;
    patcourant->presnouveau->libelle=nomPres;
}
