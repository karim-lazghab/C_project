E-Election est une application de gestion d'élections écrite en langage C. le code utilise des structures de données pour stocker des informations sur les administrateurs, les candidats et les élections, ainsi que des fichiers pour sauvegarder et charger les données depuis et vers des fichiers texte.

Voici une description des structures principales :

Structures de données :
Candidat :

Contient les informations d'un candidat : nom, prénom, âge et nombre de votes reçus.

Election :

Représente une élection avec un nom et une liste de candidats. Elle contient également le nombre total de candidats.
Administrateur :

Stocke les informations d'un administrateur avec un nom d'utilisateur et un mot de passe.
Fonctions principales :
load() :

Charge les données à partir de fichiers texte pour les administrateurs, les candidats et les élections.
creer_compte_administrateur() :

Permet de créer un nouveau compte administrateur en saisissant un nom d'utilisateur et un mot de passe.
creer_compte_candidat() :

Ajoute un nouveau candidat avec son nom, prénom et âge, vérifiant qu'il n'existe pas déjà.
creer_nouvelle_election() :

Crée une nouvelle élection en demandant son nom et le nombre de candidats à inclure, puis enregistre les candidats pour cette élection.
mettre_a_jour_info_candidat() :

Met à jour le nombre de votes d'un candidat pour une élection spécifique.
afficher_elections() :

Affiche la liste de toutes les élections avec les détails de chaque candidat pour chaque élection.
afficher_liste_votes() :

Affiche la liste des votes pour chaque candidat dans chaque élection.
rechercher_candidat() :

Recherche un candidat spécifique en fonction du nom saisi et affiche ses détails s'il est trouvé.
save() :

Sauvegarde toutes les données (administrateurs, candidats et élections) dans des fichiers texte.
debug() :

Affiche des informations de débogage, telles que les administrateurs, les candidats et les élections enregistrés.
run_as_administrator() :

Active le mode administrateur pour accéder à certaines fonctionnalités supplémentaires en se connectant avec un nom d'utilisateur et un mot de passe.
Fonctionnement du programme :
Le programme principal (fonction main()) est une boucle qui affiche un menu pour permettre à l'utilisateur d'interagir avec le système en choisissant parmi différentes options. Les utilisateurs peuvent créer des comptes administrateurs, enregistrer des candidats, créer de nouvelles élections, mettre à jour les informations des candidats, afficher les élections enregistrées, rechercher des candidats, etc. Certains de ces choix nécessitent des autorisations d'administrateur pour être accessibles.

Le code prend également en charge la sauvegarde et le chargement des données à partir de fichiers texte pour assurer la persistence des données entre les sessions d'exécution du programme.

Ce code pourrait être étendu pour inclure davantage de fonctionnalités, une interface utilisateur améliorée ou une gestion plus robuste des erreurs et des exceptions.





