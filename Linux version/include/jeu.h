/**
 * @file jeu.h
 * @author Hayk ZARIKIAN
 * @brief Fichier jeu.h qui stocke les déclarations des fonctions
 *        en relation avec le jeu.
 * @version 4.0
 * @date 2021-03-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 * @brief Fonction traitement de bord.
 * 
 * @param[in] int i  : Indice de la case.
 * @param[in] int m  : Indice.
 * @return int 
 */
// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 * @brief Fonction compte le nombre de voisins vivants
 *        les bords sont cycliques.
 * 
 * @param[in] int i     : Ligne.
 * @param[in] int j     : Colonne.
 * @param[in] grille g  : Grille.
 * @return int   Nombre de voisins vivants (cyclique). 
 */
// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
int compte_voisins_cyclique (int i, int j, grille g);

/**
 * @brief Fonction compte le nombre de voisins vivant 
 *        les bords sont non cycliques.
 * 
 * @param[in] int i     : Ligne. 
 * @param[in] int j     : Colonne.
 * @param[in] grille g  : Grille.
 * @return int   Nombre de voisins vivants (non cyclique).
 */
// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont non cycliques.
int compte_voisins_non_cyclique (int i, int j, grille g);

/**
 * @brief Fonction qui fait évoluer une grille d'un pas de temps.
 * 
 * @param[in] grille* g   : Grille g. 
 * @param[in] grille* gc  : Grille gc. 
 */
// fait évoluer la grille g d'un pas de temps
void evolue (grille *g, grille *gc);

#endif
