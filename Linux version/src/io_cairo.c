/**
 * @file io_cairo.c
 * @author Hayk ZARIKIAN
 * @brief Fichier io_cairo.c qui contient plusieurs fonctions pour
 * 		  le début et la fin du jeu.
 * @version 4.0
 * @date 2021-03-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../include/io_cairo.h"

// pointeur de fonction pour compte voisins vivants (cyclique ou non cyclique)
int (*compte_voisins_vivants) (int, int, grille);
// déclaration du temps d'évolution en static
static int temps_evolution = 0;
// déclaration de l'indicateur de viellissement
static int indication_viellissement = 0;
// déclaration de l'indicateur de cyclique
static int indication_cyclique = 0;
// pointeur de fonction pour activer/désactiver le viellissement
void (*age_cellule) (int, int, grille);

/**
 * @brief Fonction qui affichage une grille dans une interface graphique.
 * 
 * @param[in] cairo_surface_t* surface  : Surface.
 * @param[in] grille g                  : Grille.
 */
void affiche_graph(cairo_surface_t *surface, grille g){
	int i, j;
	float x, y; // abscisse et ordonée
	float longueur = SIZEX / g.nbc; 
	float largeur = SIZEY / g.nbl;
	float age = 0.0;

	// create cairo mask
	cairo_t *cr;
	cr = cairo_create(surface);

	// création du background
	cairo_set_source_rgb(cr, 255, 255, 255);
	cairo_paint(cr);
	cairo_set_line_width(cr, 1.0);
	// affichage de la grille
	for (i = 0; i < g.nbl; i++){
		for (j = 0; j < g.nbc; j++){
			x = longueur * j;
			y = largeur * i;
			cairo_rectangle(cr, x, y, longueur - 5, largeur - 5);
			if (set_viable(i, j, g)){
				if (est_vivante(i, j, g)){
					age = 0.1 * g.cellules[i][j];
					cairo_set_source_rgb(cr, age, 0.8 - age, 0);
					cairo_fill(cr);
				}
				else{
					cairo_set_source_rgb(cr, 255, 255, 255);
					cairo_fill(cr);
				}
			}	
			else{
				cairo_set_source_rgb(cr, 255, 255, 255);
				cairo_fill(cr);
			}
		}
	}
	cairo_destroy(cr); 
	return;
}

/**
 * @brief Fonction qui débute le jeu dans l'interface graphique.
 * 
 * @param grille* g     : Grille.
 * @param grille* gc    : Grille.
 * @param Display* dpy  : Affichage/Ecran.
 * @param cairo_surface_t* cs 
 */
void debut_jeu_cairo(grille *g, grille *gc, Display *dpy, cairo_surface_t *cs){
	XEvent e;
	char *touche_clavier;

	// boucle qui teste si l'utilisateur interagit avec le clavier ou la souris
	while(1){
		// SOURIS
		XNextEvent(dpy, &e);
		// affichage de l'interface graphique
		if(e.type == Expose && e.xexpose.count <1){
			affiche_graph(cs, *g);
		}
		// clic droit : quitte l'interface
		else if(e.type == ButtonPress){
			if(e.xbutton.button == 3) break;
			// clic gauche : évolue la grille
			else if (e.xbutton.button == 1) {
				temps_evolution ++;
				printf("\nTemps d'évolution : %d, cyclique : %d, viellissement : %d\n", temps_evolution, indication_cyclique, indication_viellissement);
				evolue(g, gc);
				affiche_graph(cs, *g);
			}
		}
		// CLAVIER
		else if (e.type == KeyPress){
			touche_clavier = XKeysymToString(XkbKeycodeToKeysym(dpy, e.xkey.keycode, 0, 0));
			switch(touche_clavier[0]){
				// demande une nouvelle grille à entrée
				case 'n' : 
					libere_grille(g);
					libere_grille(gc);

					char name_grille[40];
					temps_evolution = 0;
					printf("\nEntrer le nom de la nouvelle grille :\n");
					scanf("%s", name_grille);
					init_grille_from_file(name_grille, g);
					alloue_grille(g->nbl, g->nbc, gc);
					break;
				// active/désactive cyclique
				case 'c' :
					if (compte_voisins_vivants == compte_voisins_cyclique){
						compte_voisins_vivants = compte_voisins_non_cyclique;
						indication_cyclique = 0;
						printf("Passage Voisin -> non Cyclique\n");
					}
					else{
						compte_voisins_vivants = compte_voisins_cyclique;
						indication_cyclique =1;
						printf("Passage Voisin -> cyclique\n");
					}
					break;
				// active/désactive viellissement
				case 'v' :
					if (age_cellule == viellissement_desactive){
						age_cellule = viellissement_active;
						indication_viellissement = 1;
						printf("Viellissement active\n");
					}
					else {
						age_cellule = viellissement_desactive;
						indication_viellissement = 0;
						printf("Viellissement desactive\n");
					}
					break;
				
				default :
					break;
				
			}
		affiche_graph(cs, *g);
		}

	}

}