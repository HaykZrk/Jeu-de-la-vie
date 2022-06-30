/**
 * @file main_cairo.c
 * @author Hayk ZARIKIAN
 * @brief Fonction principale pour le jeu en interface graphique.
 * @version 4.0
 * @date 2021-03-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>

#include "../include/grille.h"
#include "../include/io_cairo.h"
#include "../include/jeu.h"

#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

/**
 * @brief Retourne 1 si argc != 2, sinon procède au démarrage du jeu.
 * 
 * @param[in] argc  : Donne le nombre d'éléments de la ligne de commande.
 * @param[in] argv  : Contient ces éléments sous la forme d'un tableau de char.
 * @return int Retourne un entier 0 ou 1.
 */
int main (int argc, char *argv[]){
    if(argc != 2){
        printf("usage : main <fichier grille>\n");
        return 1;
    }

    grille g, gc;
    init_grille_from_file(argv[1], &g);
    alloue_grille(g.nbl, g.nbc, &gc);

    // X11 display
    Display *dpy;
    Window rootwin;
    Window win;
    int scr;

    // init the display
    if (!(dpy = XOpenDisplay(NULL))){
        fprintf(stderr, "ERROR: Could not open display\n");
        exit(1);
    }

    scr = DefaultScreen(dpy);
    rootwin = RootWindow(dpy, scr);

    win = XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, BlackPixel(dpy, scr), BlackPixel(dpy, scr));

    XStoreName(dpy, win, "jeu de la vie");
    XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
    XMapWindow(dpy, win);

    // create cairo surface
    cairo_surface_t *cs;
    cs = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

    // run the event loop
    debut_jeu_cairo(&g, &gc, dpy, cs);

    libere_grille(&g);
    libere_grille(&gc);

    cairo_surface_destroy(cs); // destroy cairo surface
    XCloseDisplay(dpy); // close the display
    return 0;
}