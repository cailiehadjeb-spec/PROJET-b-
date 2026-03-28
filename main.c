#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PARKING 100
//question 0
typedef struct {//on d�finit la structure
    char id [15];//identifiant unique 
    char nom[50];//nom du parking 
    char Adresse[100];//adresse du parking 
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

    int nbParking=0; //c'est le compteur du nombre de parking lu 
    fscanf(f,"%*[^\n]\n"); //ignore la premiere ligne du CSV car c'est les noms des informations
    //on lit ligne par ligne le fichier csv 
    while(fscanf(f,"%79[^;];%79[^;];%79[^;];%79[^;];%79[^;];%d;%d;%79[^;];%79[^\n]\n",// utilise f comme pointeur
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
    //si les 9 éléments sont corrects on passe au suivant 
    // on retourne le nombre de parkings 
    return nbParking;
    }


    //question 2
void afficheLEparking (Parking tout[],int n){
    // tout est un tableau contenant les parking et n le nombre de parkings 
    char idr[15];// variable poour stocker l'id utilisé 
    printf("afficher l'id du parking souhait�:");//demande a l'utilisateur de donné l'id du parking 
    scanf("%s", idr );
    //on va parcourir tous les parkings 
    for(int i=0;i<n;i++){
        // si on le trouve on affiche toutes ses informations 
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

//on ne retourne aucun affichage a l'écran car c'est une procédure 
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
    //on affiche le nombre de parkings total trouvés 
    printf("\nListe de tous les parkings (%d trouv�s) \n", n);
    //parcours tous les parkings 
    for (int i = 0; i < n; i++) {
        //affichage de toutes les informations principales 
        printf("ID: %s | Nom: %s | Places: %d/%d | Etat: %s\n",
                tout[i].id, tout[i].nom, tout[i].Place_dispo, tout[i].capacite_max, tout[i].Etat);
    }
}

// question 4

#include <time.h>


time_t saisirHeure() {
    struct tm t = {0};
    //on utiliste une structure pour manipuler le mois et les heures 
    int jour, mois, annee, heure, minute;
// saisie par l'utilisateur 
    printf("  Jour (JJ) : "); scanf("%d", &jour);
    printf("  Mois (MM) : "); scanf("%d", &mois);
    printf("  Annee (AAAA) : "); scanf("%d", &annee);
    printf("  Heure (HH) : "); scanf("%d", &heure);
    printf("  Minute (MM) : "); scanf("%d", &minute);
// on affecte des valeurs a la structure tm 
    t.tm_mday = jour; // jour du mois
    t.tm_mon = mois - 1; // mois (0 = janvier donc on enlève 1)
    t.tm_year = annee - 1900; // années depuis 1900
    t.tm_hour = heure;
    t.tm_min = minute;
    t.tm_isdst = -1;
    // Permet au système de déterminer automatiquement l'heure d'été/hiver
//conversion de la structure 
    return mktime(&t);
}


int secondes;
void sortieParking(Parking tout[], int n) {
    char idr[15];//id du parking 
    char plaque[20];//plaque d'immatriculation 
    float tarifHoraire = 2.0;// on choisit ici un tarif par heure 
    printf("\n SORTIE\n");
    //ON DEMANDE L'IDENTIFIANT DU PARKING A L'UTILISATEUR 
    printf("Entrez l'identifiant du parking : ");
    scanf("%14s", idr);

    int indice = -1; // On stock l'indice du parking 
    //on parcourt tous les parking pour trouver le bon identifiant 
    for (int i = 0; i < n; i++) {
        if (strcmp(idr, tout[i].id) == 0) {
            indice = i;
            break;// on arrete quand on trouve 
        }
    }
// si on ne le trouve par on marque erreur 
    if (indice == -1) {
        printf("Erreur : Parking '%s' introuvable.\n", idr);
        return;
    }
    printf("Numero de plaque d'immatriculation : ");
    scanf("%19s", plaque);
    printf("\n HEURE D'ENTREe\n");
    time_t entree = saisirHeure();
    printf("\n HEURE DE SORTIE \n");
    time_t sortie = saisirHeure();
// calcule du temps en seconde 
    double secondes = difftime(sortie, entree);
    if (secondes < 0) {
        printf("Erreur : L'heure de sortie ne peut pas etre avant l'heure d'entree !\n");
        return;
    }
    double heures = secondes / 3600.0;
    //calcul du montant a payer 
    float montant = (float)(heures * tarifHoraire);

// résumé 
    printf("Parking  : %s\n", tout[indice].nom);
    printf("Vehicule : %s\n", plaque);
    printf("Duree    : %.2f heures\n", heures);
    printf("TOTAL    : %.2f EUR\n", montant);
// mise a jour d'une place qui se libere si le parking est plein
    if (tout[indice].Place_dispo < tout[indice].capacite_max) {
        tout[indice].Place_dispo++;
    }

    suiviClient(plaque, montant);
}

//QUESTION5
void suiviClient(char plaque[], float montant) {
    // Ouverture du fichier en mode "ajout" (a = append)
    FILE *f = fopen("suivi_clients.txt", "a");
    //on verifie si le fichier s'est bien ouvert sinon on marque erreur 
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier de suivi\n");
        return;
    }
    fprintf(f, "Vehicule : %s | Montant paye : %.2f Euros\n", plaque, montant);
    //fermeture du fichier pour enregistrer et sauvegarder les données 
    fclose(f);
//on confirme que c'est bien enregistrer 
    printf("Sauvegarde terminee dans suivi_clients.txt\n");
}


//QUESTION 6 
void mettreAJourOccupation (Parking tout[], int nb , char id[], int entree) {
    //parcourt les parkings 
    for(int i=0; i<nb ; i++){
        //recherche du parking correspondant 
            if(strcmp (tout[i].id,id)==0){
                // si une voiture entre on a une place en moins 
                    if( entree ==1){
                            tout[i].Place_dispo--;

                    }
                    else {
                        // si une voiture sort on a une place en plus 
                        tout[i].Place_dispo++;}
                    }
                    }
            }

//QUESTION 7
int modeAdministrateur (){
    int mdp;
    //demande du mdp 
    printf("\nEntrez le code administrateur:");
    scanf("%d,&mdp");
    //si le mdp donné est coorect cela renvoie acces autorisé sinon refusé 
    if(mdp==1234){
        printf("acces autoris�.\n");
        return 1;
    }
    else{
        printf("acces refuser car incorrect.\n");
    return 0;
    }
}


//QUESTION 8 
int verifierPlacesDisponibles(Parking tout[], int nb, char id[]) {
    for (int i = 0; i < nb; i++) {
//recherche du parking 
        if (strcmp(tout[i].id, id) == 0) {
            if (tout[i].Place_dispo == 0) {
                return 1;// le parking est plein 
            } else {
                return 0;//il y a des places disponibles 
            }
        }
    }
    return -1;//on ne trouve pas le parking 
}


//QUESTION 9

void sauvegarderEtatParking(Parking tout[], int nb) {
//ouverure du fichier 
    FILE *f = fopen("parking-metropole.csv", "w");
//on verifie l'ouverture 
    if (f == NULL) {
        printf("Erreur : Impossible de sauvegarder dans le fichier.\n");
        return;
    }
    fprintf(f, "Identifiant;Nom;Adresse;Ville;Etat;Places disponibles;Capacite max;Date de mise a jour;Affichage panneaux\n");
//ecriture des données de chaques parkings 
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
//fermeture du dossier 
    fclose(f);
    printf("Base de donnees mise \n");
}





