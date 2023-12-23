#include <stdio.h>
#include <string.h>
// Structure pour stocker les informations des candidats
typedef struct {
    char nom[100];
    char prenom[100];
    int age;
    int nombre_de_votes;
} Candidat;

// Structure pour stocker les informations des élections
typedef struct {
    char nom[100];
    Candidat candidats[100];
    int nombre_de_candidats;
} Election;

typedef struct {
    char nom_utilisateur[50];      // Nom de l'administrateur
    char mot_de_passe[50];   // mdp de l'administrateur
    // Ajoutez d'autres champs si nécessaire
} administrateur;

administrateur admins[100];
Candidat candidats[100];
Election elections[100];
int nombre_d_elections = 0;

//stocker les informations dans les tableaux
void load() {
    FILE *file;
    int i;

    // Charger les administrateurs
    file = fopen("admin.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier admin\n");
        return;
    }
    i = 0;
    while (fread(&admins[i], sizeof(administrateur), 1, file)) {
        i++;
    }
    fclose(file);

    // Charger les candidats
    file = fopen("candidat.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier candidat\n");
        return;
    }
    i = 0;
    while (fread(&candidats[i], sizeof(Candidat), 1, file)) {
        i++;
    }
    fclose(file);

    // Charger les élections
    file = fopen("election.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier election\n");
        return;
    }
    i = 0;
    while (fread(&elections[i], sizeof(Election), 1, file)) {
        i++;
    }
    fclose(file);
}

// Fonctions pour gérer les élections
void creer_compte_administrateur() {
    administrateur new_admin;
    printf("Entrez le nom de l'administrateur: ");
    scanf("%s", new_admin.nom_utilisateur);
    printf("Entrez le mot de passe de l'administrateur: ");
    scanf("%s", new_admin.mot_de_passe);
    // Add the new admin to the admins array
    admins[nombre_d_elections] = new_admin;
    nombre_d_elections++;
}


void creer_compte_candidat() {
    Candidat new_candidat;
    printf("Entrez le nom du candidat: ");
    if(scanf("%s", new_candidat.nom) != 1) {
        printf("Erreur lors de la saisie du nom.\n");
        return;
    }
    printf("Entrez le prenom du candidat: ");
    if(scanf("%s", new_candidat.prenom) != 1) {
        printf("Erreur lors de la saisie du prenom.\n");
        return;
    }
    printf("Entrez l'age du candidat: ");
    if(scanf("%d", &new_candidat.age) != 1 || new_candidat.age < 0) {
        printf("Erreur lors de la saisie de l'age.\n");
        return;
    }
    new_candidat.nombre_de_votes = 0;  // Initialize the number of votes to 0

    // Add the new candidate to the candidates array
    candidats[nombre_d_elections] = new_candidat;
    nombre_d_elections++;
}


void creer_nouvelle_election() {
    Election new_election;
    printf("Entrez le nom de l'election: ");
    if(scanf("%s", new_election.nom) != 1) {
        printf("Erreur lors de la saisie du nom.\n");
        return;
    }
    printf("Entrez le nombre de candidats: ");
    if(scanf("%d", &new_election.nombre_de_candidats) != 1 || new_election.nombre_de_candidats < 0) {
        printf("Erreur lors de la saisie du nombre de candidats.\n");
        return;
    }
    for(int i = 0; i < new_election.nombre_de_candidats; i++) {
        printf("Entrez le nom du candidat %d: ", i+1);
        if(scanf("%s", new_election.candidats[i].nom) != 1) {
            printf("Erreur lors de la saisie du nom du candidat.\n");
            return;
        }
        printf("Entrez le prenom du candidat %d: ", i+1);
        if(scanf("%s", new_election.candidats[i].prenom) != 1) {
            printf("Erreur lors de la saisie du prenom du candidat.\n");
            return;
        }
        printf("Entrez l'âge du candidat %d: ", i+1);
        if(scanf("%d", &new_election.candidats[i].age) != 1 || new_election.candidats[i].age < 0) {
            printf("Erreur lors de la saisie de l'âge du candidat.\n");
            return;
        }
        new_election.candidats[i].nombre_de_votes = 0;  // Initialize the number of votes to 0
    }

    // Add the new election to the elections array
    elections[nombre_d_elections] = new_election;
    nombre_d_elections++;
}

void mettre_a_jour_info_candidat() {
    char nom[100];
    char prenom[100];
    int found = 0;

    printf("Entrez le nom du candidat: ");
    if(scanf("%s", nom) != 1) {
        printf("Erreur lors de la saisie du nom.\n");
        return;
    }
    printf("Entrez le prenom du candidat: ");
    if(scanf("%s", prenom) != 1) {
        printf("Erreur lors de la saisie du prenom.\n");
        return;
    }

    // Search for the candidate in the candidates array
    for(int i = 0; i < nombre_d_elections; i++) {
        if(strcmp(candidats[i].nom, nom) == 0 && strcmp(candidats[i].prenom, prenom) == 0) {
            printf("Entrez le nouvel âge du candidat: ");
            if(scanf("%d", &candidats[i].age) != 1 || candidats[i].age < 0) {
                printf("Erreur lors de la saisie de l'âge.\n");
                return;
            }
            printf("Entrez le nouveau nombre de votes du candidat: ");
            if(scanf("%d", &candidats[i].nombre_de_votes) != 1 || candidats[i].nombre_de_votes < 0) {
                printf("Erreur lors de la saisie du nombre de votes.\n");
                return;
            }
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Candidat non trouve.\n");
    }
}

void afficher_elections() {
    if(nombre_d_elections == 0) {
        printf("Aucune election n'a ete creee.\n");
        return;
    }

    for(int i = 0; i < nombre_d_elections; i++) {
        printf("Election %d:\n", i+1);
        printf("Nom de l'election: %s\n", elections[i].nom);
        printf("Nombre de candidats: %d\n", elections[i].nombre_de_candidats);
        for(int j = 0; j < elections[i].nombre_de_candidats; j++) {
            printf("Candidat %d:\n", j+1);
            printf("Nom: %s\n", elections[i].candidats[j].nom);
            printf("Prenom: %s\n", elections[i].candidats[j].prenom);
            printf("Âge: %d\n", elections[i].candidats[j].age);
            printf("Nombre de votes: %d\n", elections[i].candidats[j].nombre_de_votes);
        }
        printf("\n");
    }
}
void afficher_liste_votes() {
    if(nombre_d_elections == 0) {
        printf("Aucune election n'a ete creee.\n");
        return;
    }

    for(int i = 0; i < nombre_d_elections; i++) {
        printf("Election %d:\n", i+1);
        printf("Nom de l'election: %s\n", elections[i].nom);
        printf("Nombre de candidats: %d\n", elections[i].nombre_de_candidats);
        for(int j = 0; j < elections[i].nombre_de_candidats; j++) {
            printf("Candidat %d:\n", j+1);
            printf("Nom: %s\n", elections[i].candidats[j].nom);
            printf("Prenom: %s\n", elections[i].candidats[j].prenom);
            printf("Nombre de votes: %d\n", elections[i].candidats[j].nombre_de_votes);
        }
        printf("\n");
    }
}

void save() {
    FILE *file;

    // Sauvegarder les administrateurs
    file = fopen("admin.txt", "w");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier admin pour sauvegarde.\n");
        return;
    }
    fwrite(admins, sizeof(administrateur), nombre_d_elections, file);
    fclose(file);

    // Sauvegarder les candidats
    file = fopen("candidat.txt", "w");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier candidat pour sauvegarde.\n");
        return;
    }
    fwrite(candidats, sizeof(Candidat), nombre_d_elections, file);
    fclose(file);

    // Sauvegarder les élections
    file = fopen("election.txt", "w");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier election pour sauvegarde.\n");
        return;
    }
    fwrite(elections, sizeof(Election), nombre_d_elections, file);
    fclose(file);

    printf("Donnees sauvegardees avec succes.\n");
}

int main() {
    int choix;
    load(); //stock les informations dans des tableaux respective
    do{    
        printf("**********************************************************************\n");
        printf("Veuillez selectionner une fonction :\n");
        printf("1. Creer un compte administrateur\n");
        printf("2. Creer un compte candidat\n");
        printf("3. Creer une nouvelle election\n");
        printf("4. Mettre a jour les informations du candidat\n");
        printf("5. Afficher les elections\n");
        printf("6. Afficher la liste des votes\n");
        printf("7. Quitter\n");
        printf("**********************************************************************\n");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                creer_compte_administrateur();
                break;
            case 2:
                creer_compte_candidat();
                break;
            case 3:
                creer_nouvelle_election();
                break;
            case 4:
                mettre_a_jour_info_candidat();
                break;
            case 5:
                afficher_elections();
                break;
            case 6:
                afficher_liste_votes();
                break;
            case 7:
                save();// sauvegarde les informations dans des fichiers 
                break;
            default:
                printf("Choix non valide\n");
        }
    }while(choix!=7);
    return 0;
}

//NOT UPDATED
