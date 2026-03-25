#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PARKING 100
//question 0
typedef struct {//on d�finit la structure
    char id [15];
    char nom[50];
    char Adresse[100];
    char Ville[50];
    char Etat[30] ;
    int Place_dispo;//nombres entiers
    int capacite_max;
    char date_maj[50] ;//chaine de caract�re
    char Affichage[50];

} Parking ;
// programme principal
int lesparkings (FILE *f,Parking tout[]);
void afficheLEparking (Parking tout[],int n);
void afficheLESparkings(Parking tout[], int n);
void sortieParking(Parking tout[], int n);
void suiviClient(char plaque[], float montant);
void mettreAJourOccupation (Parking tout[], int nb , char id[], int entree);
void sauvegarderEtatParking(Parking tout[], int n);

void afficheparkinParID (Parking tout[], int n, char idr[]);
int verifierPlacesDisponibles(Parking tout[], int nb, char id[]);

int main() {
    // --- INITIALISATION ---
    Parking tout[1000];
    int nb = 0;
    int choix;
    int n;
    char idSaisie[20];
    FILE *f;

    // --- QUESTION 1 : Chargement ---
    f = fopen("parking-metropole.csv", "r");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier CSV.\n");
        return 1;
    }
    nb = lesparkings(f, tout);
    fclose(f);

    do {
        printf("\n--- MENU OFFICIEL (Q1-Q9) ---\n");
        printf("1. Rechercher un parking (Q2)\n");
        printf("2. Afficher tous les parkings (Q3)\n");
        printf("3. Sortie d'un vehicule : Calcul Prix (Q4)\n");
        printf("4. Enregistrer dans suiviClient.txt (Q5)\n");
        printf("5. Mettre a jour les places (Q6)\n");
        printf("6. Mode Administrateur (Q7)\n");
        printf("7. Verifier si un parking est plein (Q8)\n");
        printf("8. Sauvegarder dans le CSV (Q9)\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: // Question 2
                // On peut utiliser soit afficheLEparking soit afficheparkingParID selon ton code
                afficheLEparking(tout, nb);
                break;

            case 2: // Question 3
                afficheLESparkings(tout, nb);
                break;

            case 3: // Question 4
                sortieParking(tout, nb);
                break;

            case 4: // Question 5
                // On demande une plaque pour tester la fonction suivi
                printf("Numero de plaque : "); scanf("%s", idSaisie);
                suiviClient(idSaisie, 0.0); // Le prix sera calcul� dans la fonction
                break;

            case 5: // Question 6
                printf("ID du parking : "); scanf("%s", idSaisie);
                printf("Action (1: Entree / 0: Sortie) : ");
                int action; scanf("%d", &action);
                mettreAJourOccupation(tout, nb, idSaisie, action);
                break;

            case 6: // Question 7
                // Ici on appelle ta fonction qui gere le mode admin
                modeAdministrateur();
                break;

            case 7: // Question 8
                printf("ID a verifier : "); scanf("%s", idSaisie);
                // ATTENTION : Verifie bien l'orthographe de cette fonction dans ton code
                if(verifierPlacesDisponibles(tout, nb, idSaisie) == 1) {
                    printf("Le parking est PLEIN.\n");
                } else {
                    printf("Il reste des places.\n");
                }
                break;

            case 8: // Question 9
                sauvegarderEtatParking(tout, nb);
                break;

            case 0:
                printf("Fin du programme.\n");
                break;

            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}


//question 1

int lesparkings (FILE *f,Parking tout[]){

    int nbParking=0;
    fscanf(f,"%*[^\n]\n"); //ignore la premiere ligne du CSV car c'est les noms des informations
    while(fscanf(f,"%79[^;];%79[^;];%79[^;];%79[^;];%79[^;];%d;%d;%79[^;];%79[^\n]\n",
                 tout[nbParking].id,
                 tout[nbParking].nom,
                 tout[nbParking].Adresse,
                 tout[nbParking].Ville,
                 tout[nbParking].Etat,
                 &tout[nbParking].Place_dispo,
                 &tout[nbParking].capacite_max,
                 tout[nbParking].date_maj,
                 tout[nbParking].Affichage)==9) {
          nbParking++;}
    return nbParking;
    }


    //question 2
void afficheLEparking (Parking tout[],int n){
    char idr[15];
    printf("afficher l'id du parking souhait�:");
    scanf("%s", idr );
    for(int i=0;i<n;i++){
            if(strcmp(idr, tout[i].id)==0) {
                printf("\Parking trouv� : %n");
                printf("Id :%s\n",tout[i].id);
                printf("nom :%s\n",tout[i].nom);
                printf("Adresse:%s\n",tout[i].Adresse);
                printf("Ville :%s\n",tout[i].Ville );
                printf("Etat:%s\n",tout[i].Etat);
                printf("Place_dispo :%d\n",tout[i].Place_dispo );
                printf("capacite_max:%d\n",tout[i].capacite_max);
                printf("date_maj:%s\n",tout[i].date_maj);
                printf("Affichage:%s\n",tout[i].Affichage);
            }


}}

 void afficheparkinParID (Parking tout[], int n, char idr[]) {
     for (int i=0; i<n;i++) {
            if (strcmp (idr, tout [1].id) ==0) {
                    printf("\Parking trouv� : %n");
                printf("Id :%s\n",tout[i].id);
                printf("nom :%s\n",tout[i].nom);
                printf("Adresse:%s\n",tout[i].Adresse);
                printf("Ville :%s\n",tout[i].Ville );
                printf("Etat:%s\n",tout[i].Etat);
                printf("Place_dispo :%d\n",tout[i].Place_dispo );
                printf("capacite_max:%d\n",tout[i].capacite_max);
                printf("date_maj:%s\n",tout[i].date_maj);
                printf("Affichage:%s\n",tout[i].Affichage);
            }


}}

//question 3

void afficheLESparkings(Parking tout[], int n) {
    printf("\n--- Liste de tous les parkings (%d trouv�s) ---\n", n);
    for (int i = 0; i < n; i++) {
        printf("ID: %s | Nom: %s | Places: %d/%d | Etat: %s\n",
                tout[i].id, tout[i].nom, tout[i].Place_dispo, tout[i].capacite_max, tout[i].Etat);
    }
}

// question 4

#include <time.h>


time_t saisirHeure() {
    struct tm t = {0};
    int jour, mois, annee, heure, minute;

    printf("  Jour (JJ) : "); scanf("%d", &jour);
    printf("  Mois (MM) : "); scanf("%d", &mois);
    printf("  Annee (AAAA) : "); scanf("%d", &annee);
    printf("  Heure (HH) : "); scanf("%d", &heure);
    printf("  Minute (MM) : "); scanf("%d", &minute);

    t.tm_mday = jour;
    t.tm_mon = mois - 1;
    t.tm_year = annee - 1900;
    t.tm_hour = heure;
    t.tm_min = minute;
    t.tm_isdst = -1;

    return mktime(&t);
}


int secondes;
void sortieParking(Parking tout[], int n) {
    char idr[15];
    char plaque[20];
    float tarifHoraire = 2.0;

    printf("\n--- PROCEDURE DE SORTIE ---\n");
    printf("Entrez l'identifiant du parking : ");
    scanf("%14s", idr);

    int indice = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(idr, tout[i].id) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Erreur : Parking '%s' introuvable.\n", idr);
        return;
    }

    printf("Numero de plaque d'immatriculation : ");
    scanf("%19s", plaque);

    printf("\n--- HEURE D'ENTREE ---\n");
    time_t entree = saisirHeure();

    printf("\n--- HEURE DE SORTIE ---\n");
    time_t sortie = saisirHeure();


    double secondes = difftime(sortie, entree);

    if (secondes < 0) {
        printf("Erreur : L'heure de sortie ne peut pas etre avant l'heure d'entree !\n");
        return;
    }

    double heures = secondes / 3600.0;
    float montant = (float)(heures * tarifHoraire);


    printf("Parking  : %s\n", tout[indice].nom);
    printf("Vehicule : %s\n", plaque);
    printf("Duree    : %.2f heures\n", heures);
    printf("TOTAL    : %.2f EUR\n", montant);

    if (tout[indice].Place_dispo < tout[indice].capacite_max) {
        tout[indice].Place_dispo++;
    }

    suiviClient(plaque, montant);
}

//QUESTION5



void suiviClient(char plaque[], float montant) {

    FILE *f = fopen("suivi_clients.txt", "a");


    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier de suivi\n");
        return;
    }


    fprintf(f, "Vehicule : %s | Montant paye : %.2f Euros\n", plaque, montant);


    fclose(f);

    printf("Sauvegarde terminee dans suivi_clients.txt\n");
}
//QUESTION 6 Thea
void mettreAJourOccupation (Parking tout[], int nb , char id[], int entree) {
    for(int i=0; i<nb ; i++){
            if(strcmp (tout[i].id,id)==0){
                    if( entree ==1){
                            tout[i].Place_dispo--;

                    }
                    else {
                        tout[i].Place_dispo++;}


                    }


                    }

            }

//QUESTION 7
int modeAdministrateur (){
    int mdp;
    printf("\nEntrez le code administrateur:");
    scanf("%d,&mdp");
    if(mdp==1234){
        printf("acces autoris�.\n");
        return 1;
    }
    else{
        printf("acces refuser car incorrect.\n");
    return 0;
    }
}


//QUESTION 8 thea
int verifierPlacesDisponibles(Parking tout[], int nb, char id[]) {
    for (int i = 0; i < nb; i++) {

        if (strcmp(tout[i].id, id) == 0) {
            if (tout[i].Place_dispo == 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    return -1;
}
//QUESTION 9

void sauvegarderEtatParking(Parking tout[], int nb) {

    FILE *f = fopen("parking-metropole.csv", "w");

    if (f == NULL) {
        printf("Erreur : Impossible de sauvegarder dans le fichier.\n");
        return;
    }

    fprintf(f, "Identifiant;Nom;Adresse;Ville;Etat;Places disponibles;Capacite max;Date de mise a jour;Affichage panneaux\n");

    for (int i = 0; i < nb; i++) {
        fprintf(f, "%s;%s;%s;%s;%s;%d;%d;%s;%s\n",
                tout[i].id,
                tout[i].nom,
                tout[i].Adresse,
                tout[i].Ville,
                tout[i].Etat,
                tout[i].Place_dispo,
                tout[i].capacite_max,
                tout[i].date_maj,
                tout[i].Affichage);
    }

    fclose(f);
    printf("Base de donnees mise \n");
}





