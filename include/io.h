/**
 * @file io.h
 * @author Hayk ZARIKIAN 
 * @brief Fichier io.h qui stocke les déclaration des fonctions
 *        en relation avec l'io.
 * @version 4.0
 * @date 2021-03-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/**
 * @brief Fonction affichage trait horizontal.
 * 
 * @param[i] int c  : Colonne. 
 */
// affichage d'un trait horizontal
void affiche_trait (int c);

/**
 * @brief Fonction affichage ligne.
 * 
 * @param[in] int c       : Colonne.
 * @param[in] int* ligne  : Ligne. 
 */
// affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne);

/**
 * @brief Fonction affichage d'une grille.
 * 
 * @param[in] grille g  : Grille.
 */
// affichage d'une grille
void affiche_grille (grille g);

/**
 * @brief Fonction effacement grille.
 * 
 * @param[in] grille g  : Grille.
 */
// effacement d'une grille
void efface_grille (grille g);

/**
 * @brief Fonction début de jeu
 * 
 * @param[in] grille* g   : Grille.
 * @param[in] grille* gc  : Grille.
 */
// debute le jeu
void debut_jeu(grille *g, grille *gc);

#endif
