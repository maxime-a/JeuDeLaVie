/*			vue.h
 *
 * Contient le prototype de la fonction de déclaration et d'assemblage des widgets
 *
 */

#pragma once

#include<stdlib.h>
#include<string.h>
#include"libsx.h"
#include"jeu.h"

/*			initialiserAffichage
 *
 * Rôle: créer et met en forme les widgets dans la fenêtre 
 * Antécédents: argc et argv lors de l'appel du programme
 *
 */
extern int initialiserAffichage(int argc, char *argv[],donnees *d);
