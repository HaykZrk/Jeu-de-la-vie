/**
 * @file io_cairo.h
 * @author Hayk ZARIKIAN
 * @brief Fichier io_cairo.h qui stocke les déclarations des fonctions
 *        en relation avec le démarrage du jeu en interface graphique.
 * @version 4.0
 * @date 2021-03-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __IO_CAIRO_H
#define __IO_CAIRO_H

#include <stdio.h>
#include <stdlib.h>

#include "grille.h"
#include "jeu.h"

#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <X11/XKBlib.h>

// taille de l'interface graphique
#define SIZEX 300
#define SIZEY 300

/**
 * @brief Fonction qui affiche la grille dans l'interface graphique.
 * 
 * @param[in] cairo_surface_t* surface  :  Surface.
 * @param[in] grille g                  :  Grille.
 */
void affiche_graph(cairo_surface_t *surface, grille g);

/**
 * @brief Fonction début de jeu à interface graphique.
 * 
 * @param g 
 * @param gc 
 * @param dpy 
 * @param cs 
 */
void debut_jeu_cairo(grille *g, grille *gc, Display *dpy, cairo_surface_t *cs);

#endif