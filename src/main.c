/**
 * @file main.c
 * @author Hayk ZARIKIAN
 * @brief Fichier main.c qui contient le code principal (main)
 * @version 4.0
 * @date 2021-03-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>

#include "../include/grille.h"
#include "../include/io.h"
#include "../include/jeu.h"

/**
 * @brief Retourne 1 si argc != 2, sinon procède à la 
 *        création/allocation de grille.
 * 
 * @param[in] int   argc  : Donne le nombre d'éléments de la ligne de commande.
 * @param[in] char* argv  : Contient ces éléments sous la forme d'un 
 *                          tableau de char.
 * @return int  Retourne un entier 0 ou 1.
*/
int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g); 
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
