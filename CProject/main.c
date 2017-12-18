#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Medecin Medecin;
struct Medecin
{
    char nom[31], prenom[31], inami[15], specialite[21], heureDeb[9], heureFin[9], agenda[21];

    struct Medecin *suivant;
    struct Agenda *agfirst;
} ;

typedef struct Patient Patient;
struct Patient
{
    char nom[31], prenom[31], niss[14], dateNaissance[11];
    int age, nPres;
    struct Patient *suivant;
    struct Prestation *presfirst, *prescourant, *presfinal;
} ;

typedef struct Prestation Prestation;
struct Prestation
{
    int num;
    float prix;
    char libelle[101];
    struct Prestation *suivant;
};

typedef struct Agenda Agenda;
struct Agenda
{
    char nom[31];
    int jour, int heure, int mois, int annee, minute;
};

main()
{
        int scan=0, nPres=0, nMed=0, nPat=0, i, present, nPrest, j, int nbJours[13], int kint; //i, j, k servent uniquement à incrémenter
        float k;
        char numRegNat[14], libelle[101];
        FILE *patdat, *meddat, *stdat, *ophdat, *orldat;
        Medecin *medcourant, *medintervale, *medfirst, *medsuivant;
        Patient *patfirst, *patcourant, *patintervale, *patsuivant;
        Prestation *prescourant, *presfirst, *pressuivant;
        void convertirLibelle(Prestation *, int);
        struct Prestation ajouterPrestation(Prestation *, int, int *);
        struct Patient rechercherPatient(Patient *, int, int *, char[]), ajouterPatient(char[]);
        struct Medecin rechercherMedecin(Medecin *, int, int *);
        struct Agenda *agcourant, *agsuivant;


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
            patcourant->nPres=nPrest;
            prescourant=malloc(sizeof(Prestation));
            patcourant->presfirst=prescourant;
            fscanf(patdat,"%6d", &prescourant->num);
            fgets(prescourant->libelle, 100, patdat);

            for(i=1;i<nPrest;i++){
                pressuivant=malloc(sizeof(Prestation));
                prescourant->suivant=pressuivant;
                prescourant=pressuivant;
                fscanf(patdat,"%6d", &prescourant->num);
                fgets(prescourant->libelle, 100, patdat);
            }
            patcourant->presfinal=prescourant;
            convertirLibelle(patcourant->presfirst, nPrest);

            patsuivant=malloc(sizeof(Patient));
            patcourant->suivant=patsuivant;
            patcourant=patsuivant;
            fscanf(patdat,"%13s", patcourant->niss);

        }
        patcourant->suivant=NULL;
        fclose(patdat);


        //Partie 1 : Encoder une prestation

        if(scan==1){

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

            // Lecture prestation en fonction de la spécialité du médecin
            prescourant=malloc(sizeof(Prestation));
            if(strcmp(medcourant->specialite,"STOMATOLOGUE")==0)
            {
                fscanf(stdat,"%6d", &nPrest);
                prescourant->num=nPrest;
                presfirst=prescourant;
                while(!feof(stdat)){
                    nPres++;
                    fgets(prescourant->libelle, 100, stdat);
                    pressuivant=malloc(sizeof(Prestation));
                    prescourant->suivant=pressuivant;
                    prescourant=pressuivant;
                    fscanf(stdat,"%6d", &nPrest);
                    prescourant->num=nPrest;
                }
            }
            else if(strcmp(medcourant->specialite,"OPHTALMOLOGUE")==0)
            {
                fscanf(ophdat,"%6d", &nPrest);
                prescourant->num=nPrest;
                presfirst=prescourant;
                while(!feof(ophdat)){
                    nPres++;
                    fgets(prescourant->libelle, 100, ophdat);
                    pressuivant=malloc(sizeof(Prestation));
                    prescourant->suivant=pressuivant;
                    prescourant=pressuivant;
                    fscanf(ophdat,"%6d", &nPrest);
                    prescourant->num=nPrest;
                }
            }
            else
            {
                fscanf(orldat,"%6d", &nPrest);
                prescourant->num=nPrest;
                presfirst=prescourant;
                while(!feof(orldat)){
                    nPres++;
                    fgets(prescourant->libelle, 100, orldat);
                    pressuivant=malloc(sizeof(Prestation));
                    prescourant->suivant=pressuivant;
                    prescourant=pressuivant;
                    fscanf(orldat,"%6d", &nPrest);
                    prescourant->num=nPrest;
                }
            }
            prescourant->suivant=NULL;
            convertirLibelle(presfirst, nPres);

            //recherche du patient
            *patcourant=rechercherPatient(patfirst, nPat, &present, numRegNat);



            //Si le patient n'est pas dans le fichier, on l'ajoute

            if(present==0)
            {
                patcourant=patfirst;
                for(i=0;i<nPat-1;i++)
                {
                    patcourant=patcourant->suivant;
                }
                patsuivant=malloc(sizeof(Patient));
                *patsuivant=ajouterPatient(numRegNat);
                patsuivant->suivant=NULL;
                patcourant->suivant=patsuivant;
                patcourant=patsuivant;

                while(present==0)
                {
                    *prescourant=ajouterPrestation(presfirst, nPres, &present);
                    if(present==0)
                    {
                        printf("Prestation inexistante");
                    }
                }

                patcourant->presfirst=prescourant;
                nPat++;
            }
            else
            {
                prescourant=patcourant->presfinal;
                pressuivant=malloc(sizeof(Prestation));
                prescourant->suivant=pressuivant;
                prescourant=pressuivant;
                present=0;
                while(present==0)
                {
                    *prescourant=ajouterPrestation(presfirst, nPres, &present);
                    printf("%-100s", prescourant->libelle);
                    if(present==0)
                    {
                        printf("Prestation inexistante");
                    }
                }

            }

            patdat=fopen("patient.dat","w");
            patcourant=patfirst;

            for(i=0;i<nPat;i++)
            {
                fprintf(patdat,"%13s %-30s %-30s %10s %d\n", patcourant->niss, patcourant->nom, patcourant->prenom, patcourant->dateNaissance, patcourant->nPres);

                prescourant=patcourant->presfirst;
                nPrest=patcourant->nPres;

                for(j=0;j<nPrest;j++)
                {
                    fprintf(patdat,"%6d %-100s\n", prescourant->num, prescourant->libelle);
                    prescourant=prescourant->suivant;
                }
                if(i<(nPat-1))
                {
                    patcourant=patcourant->suivant;
                }

            }


        }

        //Partie 2 : rechercher un patient

        else if(scan==2){
            *patcourant=rechercherPatient(patfirst, nPat, &present, numRegNat);
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

            medcourant=medfirst;
            nbJours={31,28,31,30,31,30,31,31,30,31,30,31};
            char[13][10] nomMois;
            strcpy(nomMois[0], "JANVIER");
            strcpy(nomMois[1], "FEVRIER");
            strcpy(nomMois[2], "MARS");
            strcpy(nomMois[3], "AVRIL");
            strcpy(nomMois[4], "MAI");
            strcpy(nomMois[5], "JUIN");
            strcpy(nomMois[6], "JUILLET");
            strcpy(nomMois[7], "AOUT");
            strcpy(nomMois[8], "SEPTEMBRE");
            strcpy(nomMois[9], "OCTOBRE");
            strcpy(nomMois[10], "NOVEMBRE");
            strcpy(nomMois[11], "DECEMBRE");
            fprintf(agdat,"2017\n");
            for(i=0;i<12;i++)
            {
                for(j=0;j<nbJours[i];j++)
                {
                    fprintf(agdat,"%d %9s\n------------------------------", j+1, nomMois[j])
                    for(k=medcourant->heureDeb;k<medcourant->heureFin;k+=.25)
                    {
                        kint=(int)k;
                        if(kint%k==.25)
                        {
                            fprintf(agdat,"%dh15 : LIBRE\n", kint);
                        }
                        else if(kint%k==.5)
                        {
                            fprintf(agdat,"%dh30 : LIBRE\n", kint);
                        }
                        if(kint%k==.75)
                        {
                            fprintf(agdat,"%dh45 : LIBRE\n", kint);
                        }
                        else
                        {
                            fprintf(agdat,"%dh00 : LIBRE\n", kint);
                        }
                    }
                    fprintf(agdat,"\f");

                }
            }
        }

}

struct Patient ajouterPatient(char numRegNat[13])
{
    void convertirNom(char[]), convertirPrenom(char[]);
    Patient *pat;
    pat=malloc(sizeof(Patient));
    strcpy(pat->niss, numRegNat);
    printf("Nom du patient : ");
    scanf("%30s", pat->nom);
    convertirNom(pat->nom);
    printf("Prénom du patient : ");
    convertirPrenom(pat->prenom);
    scanf("%30s", pat->prenom);
    printf("Date de naissance : ");
    scanf("%10s", pat->dateNaissance);
    pat->nPres=1;
    return *pat;
}

struct Prestation ajouterPrestation(Prestation *presfirst, int nPres, int *present)
{
    Prestation *prescourant;
    int numero, i;
    printf("Numéro de prestation : ");
    scanf("%6d", &numero);
    prescourant=presfirst;
    *present=0;
    for(i=0;i<nPres;i++)
    {
        if(prescourant->num==numero)
        {
            i=nPres;
            *present=1;
        }
        else
        {
            prescourant=prescourant->suivant;
        }
    }

    return *prescourant;
}

struct Patient rechercherPatient(Patient *patfirst, int nPat, int *present, char numRegNat[14])
{
    int i;
    Patient *patcourant;
    printf("Numéro du registre national du patient : ");
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
        else if(i<(nPat-1))
        {
            patcourant=patcourant->suivant;
        }
    }
    return *patcourant;
}

struct Medecin rechercherMedecin(Medecin *medfirst, int nMed, int *present)
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
}

void convertirNom(char nom[31])
{
    int i;
    for(i=0;i<30;i++)
    {
        char[i] = toupper(char[i]);
    }
}

void convertirPrenom(char prenom[31])
{
    char[0] = toupper(char[0]);
}
void convertirLibelle(Prestation *pres, int nPres)
{
    int i, j;
    prescourant=pres;
    for(i=0;i<nPres;i++)
    {
        for(j=0;j<100;j++)
        {
            if(prescourant->libelle[j]=='\n')
            {
                prescourant->libelle[j]=' ';
            }
        }
        prescourant=prescourant->suivant;
    }
}
