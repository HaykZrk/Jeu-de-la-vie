# JEU DE LA VIE - LIB CAIRO 

## Description 
Ce dépôt contiendra l'évolution du projet "Jeu de la vie" programmé pour l'UE Techniques de développement de
l'UFR Mathématique et Informatique (Université de Strasbourg).

## Commande Makefile 

- make : Compilation du jeu avec l'interface graphique.

- make MODE=TEXTE : Compilation du jeu en mode texte.

- make docs : Création de la documentation grâce à doxygen 
	    (génération en html et en latex).

- make dist : Création d'une archive avec les fichiers indispensables
	    pour la compilation.

- make clean : Suppression des fichiers optionnelles à la compilation.

## Touches de contrôle

- v : permet d'activer/désactiver le vieillissement

- c : permet d'activer/désactiver le mode cyclique

- n : permet de charger une nouvelle grille en respectant le chemin grilles/

- o : permet de savoir si la colonie est oscillante ou non

- clic gauche de souris : fait évoluer la grille

- clic droit de souris : quitte le jeu

## Exécution

./"nom exe" grilles/grille"nombre 1-8".txt

exemple : ./prog_cairo grilles/grille1.txt