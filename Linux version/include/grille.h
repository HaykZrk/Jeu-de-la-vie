/**
 * @file grille.h
 * @author Hayk ZARIKIAN
 * @brief Fichier grille.h qui stoke les déclaration
 *        fonctions concernant les grilles.
 * @version 4.0
 * @date 2021-03-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
/**
 * @brief Structure prenant le nombre de ligne, colonne et un tableau 
 *        à deux dimensions.
 * 
 * @param[in] int nbl         : Nombre de ligne.
 * @param[in] int nbc         : Nombre de colonne.
 * @param[in] int** cellules  : Tableau Cellules à deux dimensions. 
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
/**
 * @brief Fonction d'allocation grille.
 * 
 * @param[in] int l      : Ligne.
 * @param[in] int c      : Colonne.
 * @param[in] grille* g  : Grille.
 */
void alloue_grille (int l, int c, grille* g);

// libère une grille
/**
 * @brief Fonction libération de grille.
 * 
 * @param[in] grille* g  : Grille à libérer.
 */
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
/**
 * @brief Fonction qui prend le nom d'une grille via un fichier.
 * 
 * @param[in] char* filename  : Nom du fichier.
 * @param[in] grille*         : Grille.
 */
void init_grille_from_file (char * filename, grille* g);

// rend vivante la cellule (i,j) de la grille g
/**
 * @brief Met la cellule en vivante.
 * 
 * @param[in] int i     : Ligne.
 * @param[in] int j     : Colonne.
 * @param[in] grille g  : Grille.
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}


/**
 * @brief Rend la cellule (i, j) de la grille g non viable.
 * 
 * @param[in] int i     : Ligne.
 * @param[in] int j     : Colonne.
 * @param[in] grille g  : Grille.
 */
static inline void set_non_viable(int i, int j, grille g){g.cellules[i][j] = -1;}

/**
 * @brief Rend la cellule (i, j) de la grille g viable.
 * 
 * @param int i     : Ligne. 
 * @param int j     : Colonne.
 * @param grille g  : Grille. 
 * @return int 
 */
static inline int set_viable(int i, int j, grille g){return g.cellules[i][j] >= 0;}

// rend morte la cellule (i,j) de la grille g
/**
 * @brief Met la celulle en morte.
 * 
 * @param[in] int i     : Ligne.
 * @param[in] int j     : Colonne.
 * @param[in] grille g  : Grille.
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

// teste si la cellule (i,j) de la grille g est vivante
/**
 * @brief Vérifier si la cellule est vivante ou non.
 * 
 * @param[in] int i     : Ligne. 
 * @param[in] int j     : Colonne.
 * @param[in] grille g  : Grille.
 * @return int. 
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] > 0;}

// recopie gs dans gd (sans allocation)
/**
 * @brief Fonction copie une grille.
 * 
 * @param[in] grille gs  : Grile gs à copier.
 * @param[in] grille gd  : Grille gd à coller.
 */
void copie_grille (grille gs, grille gd);

/**
 * @brief Fonction qui désactive le viellissement (on ne change rien).
 * 
 * @param[in] int i     : Ligne.
 * @param[in] int j     : Colonne.
 * @param[in] grille g  : Grille.
 */
void viellissement_desactive(int i, int j, grille g);

/**
 * @brief Fonction qui active le viellissement.
 * 
 * @param[in] int i     : Ligne.
 * @param[in] int j     : Colonne.
 * @param[in] grille g  : Grille.
 */
void viellissement_active(int i, int j, grille g);


#endif
