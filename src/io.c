/**
 * @file io.c
 * @author Hayk ZARIKIAN
 * @brief Fichier io.c qui contient plusieurs fonctions pour 
 *        le début et la fin du jeu.
 * @version 4.0
 * @date 2021-03-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../include/io.h"

// pointeur de fonction pour compte voisins vivants (cyclique ou non cyclique)
int (*compte_voisins_vivants) (int, int, grille);
// déclaration du temps d'évolution en static 
static int temps_evolution = 0;
// pointeur de fonction pour activer/désactiver le viellissement
void (*age_cellule) (int, int, grille);

/**
 * @brief Fonction qui affichage d'un trait horizontal.
 * 
 * @param[in] int c  : Colonne c.
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

/**
 * @brief Fonction qui affichage d'une ligne de la grille.
 * 
 * @param[in] int c       : Colonne.
 * @param[in] int* ligne  : Ligne.
 */
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); 
		else if(ligne[i] == -1) printf("| X ");
		else printf ("| %d ", ligne[i]);
	printf("|\n");
	return;
}

/**
 * @brief Fonction qui affichage d'une grille.
 * 
 * @param[in] grille g  : Grille à afficher. 
 */
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	printf("temps d'evolution : %d\n", temps_evolution);
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

/**
 * @brief Fonction qui efface une grille.
 * 
 * @param[in] grille g  : Grille à effacer.
 */
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

/**
 * @brief Fonction qui fait débuter jeu.
 * 
 * @param[in] grille* g   : Grille g.
 * @param[in] grille* gc  : Grille gc.
 */
void debut_jeu(grille *g, grille *gc){
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entrée" pour évoluer
				evolue(g,gc);
				// temps d'évolution + 1
				temps_evolution++;
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n' :
			{ // touche 'n' pour créer une nouvelle grille
				// efface la grille g 
				efface_grille(*g);
				// libération de la mémoire
				libere_grille(g);
				// efface la grile gc
				efface_grille(*gc);
				// liberation de la mémoire
				libere_grille(gc);

                // demande l'insertion du nom de la nouvelle grille
			    char name_grille[40];
				// temps d'évolution à 0
				temps_evolution = -1;
				printf("\nEntrer le nom de la nouvelle grille :\n");
				// insertion du nom de la grille
				scanf("%s", name_grille);

				// initialisation et allocation de la grille
				init_grille_from_file(name_grille, g);

				// libération de la grille
				alloue_grille (g->nbl, g->nbc, gc);
				break;
			}
			case 'c' :
			{ // touche 'c' pour activer/désactiver le voisinage cyclique
			    putchar('\n');
				getchar();
				// passage en voisinage non cyclique
				if (compte_voisins_vivants == compte_voisins_cyclique){
					compte_voisins_vivants = compte_voisins_non_cyclique;
					printf("Passage Voisin -> non cyclique\n");
				}

				// passage en voisinage cyclique
				else{
					compte_voisins_vivants = compte_voisins_cyclique;
					printf("Passage Voisin -> cyclique\n");
				}

				break;
			}
			case 'v' :
			{ // touche 'v' pour activer/désactiver le vieillissement
				putchar('\n');
				getchar();
				if (age_cellule == viellissement_desactive){
					age_cellule = viellissement_active;
					printf("Viellissement active\n");
				}
				else{
					age_cellule = viellissement_desactive;
					printf("Viellissement desactive\n");
				}
				break;
				
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
