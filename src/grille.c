/**
 * @file grille.c
 * @author Hayk ZARIKIAN 
 * @brief Fichier grille.c qui contient plusieurs fonctions pour 
 *        gérer les grilles.
 * @version 4.0
 * @date 2021-03-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../include/grille.h"

/**
 * @brief Fonction qui alloue dynamiquement une grille de 
 *        taille l*c et initialise toutes les cellules à mortes.
 * 
 * @param[in]   int l      : Nombre de ligne de la grille. 
 * @param[in]   int c      : Nombre de colonne de la grille.
 * @param[in]   grille* g  : Grille à allouer.
 * @param[out]  grille g   : Grille allouée dynamiquement.
 */
void alloue_grille (int l, int c, grille* g){
	g->cellules = (int**)malloc(l * sizeof(int*));

	if (g->cellules == NULL)
		exit(-1);
	

	for(int i = 0; i < l; i++){
	    g->cellules[i] = (int*)malloc(c * sizeof(int));
		if (g->cellules == NULL)
			exit(-1);
	}

    for(int i = 0; i < l; i++)
		for(int j = 0; j < c; j++)
			set_morte(i, j, *g);
	
	g->nbl = l;
	g->nbc = c;

	return;
}

/**
 * @brief Fonction qui libère la grille en mémoire.
 * 
 * @param[in] grille* g  : Grille à libérer.
 */
void libere_grille (grille* g){
	for(int i = 0; i < g->nbl; i++)
		free(g->cellules[i]);
	
	free(g->cellules);
}

/**
 * @brief Fonction qui alloue et initalise la grille g à partir 
 *        d'un fichier.
 * 
 * @param[in] char* filename  : Prend le nom du fichier. 
 * @param[in] grille* g       : Grille à allouer et initialiser à partir d'un fichier.
 */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}

	int non_viable = 0;
	fscanf(pfile, "%d", &non_viable);
	for(n=0; n < non_viable; n++){
		fscanf(pfile, "%d", &i);
		fscanf(pfile, "%d", &j);
		set_non_viable(i, j, *g);
	}
	
	fclose (pfile);
	return;
}

/**
 * @brief Recopie gs dans gd (sans allocation).
 * 
 * @param[in] grille gs   : Grille à copier.
 * @param[in] grille gd   : Grille à coller.
 * @param[out] grille gd  : Grille coller.
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

/**
 * @brief Fonction qui désactive le viellissement (on ne change rien).
 * 
 * @param[in] int i     : Ligne.
 * @param[in] int j     : Colonne.
 * @param[in] grille g  : Grille.
 */
void viellissement_desactive(int i, int j, grille g){
	return;
}

/**
 * @brief Fonction qui active le viellissement.
 * 
 * @param[in] int i     : Ligne.
 * @param[in] int j     : Colonne.
 * @param[in] grille g  : Grille.
 */
void viellissement_active(int i, int j, grille g){
	g.cellules[i][j] = (g.cellules[i][j] + 1) % 9;
}

