#include <stdio.h>
#include <string.h>

typedef struct {
    char nom[100];
    char prenom[100];
    int age;
    int nombre_de_votes;
} Candidat;

typedef struct {
    char nom[100];
    Candidat candidats[100];
    int nombre_de_candidats;
} Election;

typedef struct {
    char nom_utilisateur[50];
    char mot_de_passe[50];
} administrateur;

administrateur admins[100];
Candidat candidats[100];
Election elections[100];
int nombre_d_elections = 0;
int nombre_d_admins = 0;
int nombre_de_candidat = 0;

void load() {
    FILE *file;
    int i;
    file = fopen("admin.txt", "rb");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier admin\n");
        return;
    }
    i = 0;
    fread(&nombre_d_admins, sizeof(int), 1, file);
    while (fread(&admins[i], sizeof(administrateur), 1, file)) {
        i++;
    }
    fclose(file);

    file = fopen("candidat.txt", "rb");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier candidat\n");
        return;
    }
    i = 0;
    fread(&nombre_de_candidat, sizeof(int), 1, file);
    while (fread(&candidats[i], sizeof(Candidat), 1, file)) {
        i++;
    }
    fclose(file);

    file = fopen("election.txt", "rb");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier election\n");
        return;
    }
    i = 0;
    fread(&nombre_d_elections, sizeof(int), 1, file);
    for (int i=0;i<nombre_d_elections;i++) {
        fread(&elections[i], sizeof(Election), 1, file);
    }
    fclose(file);
}

void creer_compte_administrateur() {
    administrateur new_admin;
    printf("Entrez le nom de l'administrateur: ");
    scanf("%s", new_admin.nom_utilisateur);
    printf("Entrez le mot de passe de l'administrateur: ");
    scanf("%s", new_admin.mot_de_passe);
    for(int i=0;i<nombre_d_admins;i++){
        if(strcmp(new_admin.nom_utilisateur,admins[i].nom_utilisateur)==0 || \
           strcmp(new_admin.mot_de_passe,admins[i].mot_de_passe)==0 ){
            printf("Erreur lors de la saisie des donnees.\n");
            return;
           }
    }
    admins[nombre_d_admins] = new_admin;
    nombre_d_admins++;
}

void creer_compte_candidat() {
    Candidat new_candidat;
    printf("Entrez le nom du candidat: ");
    if (scanf("%s", new_candidat.nom) != 1) {
        printf("Erreur lors de la saisie du nom.\n");
        return;
    }
    printf("Entrez le prenom du candidat: ");
    if (scanf("%s", new_candidat.prenom) != 1) {
        printf("Erreur lors de la saisie du prenom.\n");
        return;
    }
    printf("Entrez l'age du candidat: ");
    if (scanf("%d", &new_candidat.age) != 1 || new_candidat.age < 0) {
        printf("Erreur lors de la saisie de l'age.\n");
        return;
    }
    for(int i=0;i<nombre_de_candidat;i++){
        if(strcmp(new_candidat.nom,candidats[i].nom)==0 || \
           strcmp(new_candidat.prenom,candidats[i].prenom)==0){
            printf("Erreur lors de la saisie des donnees.\n");
            return;
           }
    }
    new_candidat.nombre_de_votes = -1;
    candidats[nombre_de_candidat] = new_candidat;
    nombre_de_candidat++;
}

void creer_nouvelle_election() {
    Election new_election;
    printf("Entrez le nom de l'election: ");
    if (scanf("%s", new_election.nom) != 1) {
        printf("Erreur lors de la saisie du nom.\n");
        return;
    }
    for(int i=0;i<nombre_d_elections;i++){
        if(strcmp(new_election.nom,elections[i].nom)==0){
            printf("Nom invalid.\n");
            return ;
        }
    }

    printf("Entrez le nombre de candidats: ");
    if (scanf("%d", &new_election.nombre_de_candidats) != 1 || new_election.nombre_de_candidats < 0) {
        printf("Erreur lors de la saisie du nombre de candidats.\n");
        return;
    }
    for (int i = 0; i < new_election.nombre_de_candidats; i++) {
        printf("Entrez le nom d'un candidat registre %d: \n", i + 1);
        int found=0;
        if(scanf("%s", &new_election.candidats[i].nom)==1){
            for (Candidat Candi: candidats) {
                if (strcmp(Candi.nom,new_election.candidats[i].nom)  == 0) {
                    new_election.candidats[i]=Candi;
                    found=1;
                }
                if(found){
                    break;
                }
                }
        }else{
            printf("Erreur lors de la saisie du nom du candidat.\n");
            return ;
        }

        if(!found){
            printf("candidat invalid ou non registre\n");
            return;
        }
        new_election.candidats[i].nombre_de_votes = 0;
    }

    elections[nombre_d_elections] = new_election;
    nombre_d_elections++;
}

void mettre_a_jour_info_candidat() {
    char nom[100];

    printf("Entrez le nom d'election: ");
    if (scanf("%s", nom) != 1) {
        printf("Erreur lors de la saisie du nom.\n");
        return;
    }else{
        int found =0;
        Election e;
        for(int i=0;i<nombre_d_elections;i++){
            if(strcmp(elections[i].nom,nom)==0){
                found=1;
            }
            if(found){
                break;
            }
        }
        if(!found){
            printf("Erreur lors de la saisie du nom.\n");
            return;
        }
        char nom[100];
        char prenom[100];
        printf("Entrez le nom du candidat: ");
        if (scanf("%s", nom) != 1) {
            printf("Erreur lors de la saisie du nom.\n");
            return;
        }
        printf("Entrez le prenom du candidat: ");
        if (scanf("%s", prenom) != 1) {
            printf("Erreur lors de la saisie du prenom.\n");
            return;
        }

        for (int i = 0; i < elections[i].nombre_de_candidats; i++) {
            if (strcmp(elections[i].candidats[i].nom, nom) == 0 && strcmp(elections[i].candidats[i].prenom, prenom) == 0) {
                printf("Entrez le nouveau nombre de votes du candidat: ");
                if (scanf("%d", &elections[i].candidats[i].nombre_de_votes) != 1 || elections[i].candidats[i].nombre_de_votes < 0) {
                    printf("Erreur lors de la saisie du nombre de votes.\n");
                    return;
                }

                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Candidat non trouve.\n");
        }
    }
}

void afficher_elections() {
    if (nombre_d_elections == 0) {
        printf("Aucune election n'a ete creee.\n");
        return;
    }

    for (int i = 0; i < nombre_d_elections; i++) {
        printf("Election %d:\n", i + 1);
        printf("  Nom de l'election: %s\n", elections[i].nom);
        printf("  Nombre de candidats: %d\n", elections[i].nombre_de_candidats);
        for (int j = 0; j < elections[i].nombre_de_candidats; j++) {
            printf("  *Candidat %d:\n", j + 1);
            printf("\tNom: %s\n", elections[i].candidats[j].nom);
            printf("\tPrenom: %s\n", elections[i].candidats[j].prenom);
            printf("\tAge: %d\n", elections[i].candidats[j].age);
            printf("\tNombre de votes: %d\n", elections[i].candidats[j].nombre_de_votes);
        }
        printf("\n");
    }
}

void afficher_liste_votes() {
    if (nombre_d_elections == 0) {
        printf("Aucune election n'a ete creee.\n");
        return;
    }

    for (int i = 0; i < nombre_d_elections; i++) {
        printf("*Election %d:\n", i + 1);
        printf("   Nom de l'election: %s\n", elections[i].nom);
        printf("   Nombre de candidats: %d\n", elections[i].nombre_de_candidats);
        for (int j = 0; j < elections[i].nombre_de_candidats; j++) {
            printf("   *Candidat %d:\n", j + 1);
            printf("\tNom: %s\n", elections[i].candidats[j].nom);
            printf("\tPrenom: %s\n", elections[i].candidats[j].prenom);
            printf("\tNombre de votes: %d\n", elections[i].candidats[j].nombre_de_votes);
        }
        printf("\n");
    }
}

void rechercher_candidat() {
    if (nombre_d_elections == 0) {
        printf("Aucune election n'a ete creee.\n");
        return;
    }

    char nom_recherche[100];
    printf("Entrez le nom du candidat que vous souhaitez rechercher : ");
    scanf("%s", nom_recherche);

    int found = 0;

    printf("Candidats trouves avec le nom '%s' :\n", nom_recherche);
    for (int i = 0; i < nombre_d_elections; i++) {
        for (int j = 0; j < elections[i].nombre_de_candidats; j++) {
            if (strcmp(elections[i].candidats[j].nom, nom_recherche) == 0) {
                printf("Election : %s\n", elections[i].nom);
                printf("\tNom : %s\n", elections[i].candidats[j].nom);
                printf("\tPrenom : %s\n", elections[i].candidats[j].prenom);
                printf("\tAge : %d\n", elections[i].candidats[j].age);
                printf("\tNombre de votes : %d\n", elections[i].candidats[j].nombre_de_votes);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("Aucun candidat trouve avec le nom '%s'.\n", nom_recherche);
    }
}

void save() {
    FILE *file;

    file = fopen("admin.txt", "wb");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier admin pour sauvegarde.\n");
        return;
    }
    fwrite(&nombre_d_admins, sizeof(int), 1, file);
    fwrite(admins, sizeof(administrateur), nombre_d_admins, file);
    fclose(file);

    file = fopen("candidat.txt", "wb");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier candidat pour sauvegarde.\n");
        return;
    }
    fwrite(&nombre_de_candidat, sizeof(int), 1, file);
    fwrite(candidats, sizeof(Candidat), nombre_de_candidat, file);
    fclose(file);

    file = fopen("election.txt", "wb");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier election pour sauvegarde.\n");
        return;
    }
    fwrite(&nombre_d_elections, sizeof(int), 1, file);
    fwrite(elections, sizeof(Election), nombre_d_elections, file);
    fclose(file);

    printf("Donnees sauvegardees avec succes.\n");
}

void debug() {
    printf("===== Debug Information =====\n");
    printf("Administrateurs: %d\n",nombre_d_admins);
    for (int i = 0; i < 100; ++i) {
        if (strlen(admins[i].nom_utilisateur) == 0) {
            break;
        }
        printf("Admin %d: Nom d'utilisateur: %s, Mot de passe: %s\n", i + 1, admins[i].nom_utilisateur, admins[i].mot_de_passe);
    }

    printf("\nCandidats: %d\n",nombre_de_candidat);
    for (int i = 0; i < 100; ++i) {
        if (strlen(candidats[i].nom) == 0) {
            break;
        }
        printf("Candidat %d: Nom: %s, Prenom: %s, Age: %d\n", i + 1, candidats[i].nom, candidats[i].prenom, candidats[i].age);
    }

    printf("\nElections: %d \n",nombre_d_elections);
    for (int i = 0; i < nombre_d_elections; ++i) {
        printf("Election %d: Nom: %s, Nombre de candidats: %d\n", i + 1, elections[i].nom, elections[i].nombre_de_candidats);
        printf("Candidats:\n");
        for (int j = 0; j < elections[i].nombre_de_candidats; ++j) {
            printf("\tCandidat %d: Nom: %s, Prenom: %s, Age: %d, Nombre de votes: %d\n", j + 1, elections[i].candidats[j].nom, elections[i].candidats[j].prenom, elections[i].candidats[j].age, elections[i].candidats[j].nombre_de_votes);
        }
    }
}

int admin=0;
void run_as_administrator(){
    char nom[50];
    char mdp[50];
    if(admin){
        printf("Vous ete deja en mode administrateur.");
        return;
    }
    if(nombre_d_admins==0){
        printf("Aucun admin n'a ete creee\n");
        return;
    }
    printf("Entrez avec votre compte administrateur.\n");
    printf("Entrez le nom admin: ");
    if (scanf("%s", nom) != 1) {
        printf("Erreur lors de la saisie du nom.\n");
        return;
    }
    printf("Entrez le mot de passe admin: ");
    if (scanf("%s", mdp) != 1) {
        printf("Erreur lors de la saisie du mot de passe.\n");
        return;
    }
    for (int i = 0; i < nombre_d_admins; i++) {
        if (strcmp(admins[i].nom_utilisateur, nom) == 0 && strcmp(admins[i].mot_de_passe, mdp) == 0) {
            printf("Vous etes en mode adminstrateur.\n");
            admin^=1;
            return;
        }
    }
    printf("Erreur lors de la saisie des donnees.\n");
    return;
}

int main() {
    load();
    int choix;
    skip:
    do {
        printf("\n**********************************************************************\n");
        printf("Veuillez selectionner une fonction :\n");
        printf("1. Creer un compte administrateur\n");
        printf("2. Creer un compte candidat\n");
        printf("3. Creer une nouvelle election\n");
        printf("4. Mettre a jour les informations du candidat\n");
        printf("5. Afficher les elections\n");
        printf("6. Afficher la liste des votes\n");
        printf("7. Rechercher un candidat\n");
        printf("8. Run as administrator\n");
        printf("9. Quitter\n");
        if(admin){
            printf("10. debug\n");
            printf("11. log off\n");
        }
        printf("**********************************************************************\n");
        scanf("%d", &choix);
        switch (choix) {
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
                rechercher_candidat();
                break;
            case 8:
                run_as_administrator();
                break;
            case 9:
                save();
                break;
            case 10:
                if(!admin){
                    printf("Cette commande est pas accessible pour vous, \n essayer de logger comme administrateur\n");
                    goto skip;
                }
                debug();
                break;
            case 11:
                if(!admin){
                    printf("Cette commande est pas accessible pour vous,\n essayer de logger comme administrateur.\n");
                    goto skip;
                }
                admin^=1;
                printf("plus un administrateur\n");
                break;
            default:
                save();
                printf("Choix non valide\n");
                printf("quitter!");
                return 0;
        }
    } while (choix != 9);

    return 0;
}
