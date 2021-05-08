/*			vue.h
 *
 * Contient le prototype de la fonction de déclaration et d'assemblage des widgets
 *
 */

#pragma once

#include<stdlib.h>
#include<string.h>
#include<libsx.h>

#include"modele.h"

/*			initialiserAffichage
 *
 * Rôle: créer et met en forme les widgets dans la fenêtre 
 * Antécédents: argc et argv lors de l'appel du programme
 *
 */
extern int initialiserAffichage(int argc, char *argv[],donnees *d);

/*			dessinerQuadrillage
 *
 * Rôle: dessine un grille avec un pas de 10 pixels dans la zone de dessin
 * Antécédent: j un pointeur sur jeu
 *
 */
extern void dessinerQuadrillage(donnees *d);

/*			dessiner
 *
 * Rôle: dessine la grille si activée et les cellules vivantes de l'état actuel
 * Antécédent: j un pointeur sur jeu
 *
 */
extern void dessiner(donnees *d);
