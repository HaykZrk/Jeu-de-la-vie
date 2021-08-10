/**
 * @file jeu.c
 * @author Hayk ZARIKIAN
 * @brief Fichier jeu.c qui contient plusieurs foontions pour gérer
 *        le jeu de la vie.
 * @version 4.0
 * @date 2021-03-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../include/jeu.h"

/**
 * @brief Pointeur de fonction compte voisins vivants qui pointe
 *        vers le calcul de voisinage en cours (cyclique ou non cyclique).
 * 
 * @param[in] int
 * @param[in] int
 * @param[in] grille
 */
int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_non_cyclique;

/**
 * @brief Pointeur de fonction pour l'activation et la 
 *        désactivation.
 * 
 */
void (*age_cellule)(int, int, grille) = viellissement_desactive;

/**
 * @brief Fonction qui compte le nombre de voisins vivants de 
 *        la cellule (i,j) les bords sont cycliques.
 * 
 * @param[in] int i     : Ligne i.
 * @param[in] int j     : Colonne j.
 * @param[in] grille g  : Grille pris en charge par la fonction.
 * @return int   Retourne v (nombre de voisins vivants).
 */
int compte_voisins_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

/**
 * @brief Fonction qui compte le nombre de voisins vivants de 
 *        la cellule (i, j) les bords sont non cycliques.
 * 
 * @param[in] int i     : Ligne i.
 * @param[in] int j     : Colonne j
 * @param[in] grille g  : Grille pris en charge par la fonction.
 * @return int   Retourne v (nombre de voisins vivants).
 */
int compte_voisins_non_cyclique(int i, int j, grille g){
	int v = 0, l = g.nbl, c = g.nbc;

	if (i > 0) v += est_vivante(i, j-1, g);
	
	if (j > 0) v += est_vivante(i, j-1, g);

	if (i > 0 && j > 0) v+= est_vivante(i-1, j-1, g);

	if (c - 1 > j && i > 0) v+= est_vivante(i-1, j+1, g);

	if (l -1 > i && c-1 > j) v+= est_vivante(i+1, j+1, g);

	if (c-1 > j) v+= est_vivante(i, j+1, g);

	if (l- 1 > i && j > 0) v+= est_vivante(i+1, j-1, g);

	if (l-1 > i) v+= est_vivante(i+1, j, g);

	return v;	
	
}


/**
 * @brief Fonction qui fait évoluer la grille g d'un pas de temps.
 * 
 * @param[in] grille* g   : Grille g à faire évoluer.
 * @param[in] grille* gc  : Grile temporaire.
 * @param[out] g  Grille g évoluer. 
 */
void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			if (set_viable(i, j, *g)){
				v = compte_voisins_vivants (i, j, *gc);
				if (est_vivante(i,j,*g)) 
				{ // evolution d'une cellule vivante
					if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
					else age_cellule(i, j, *g);
				}
				else 
				{ // evolution d'une cellule morte
					if ( v==3 ) set_vivante(i,j,*g);
				}
			}	
		}
	}
	return;
}