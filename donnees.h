/*			donnees.h
 *
 * Contient la structure des données principales et le prototype de la fonction d'initialisation
 *
 */

#pragma once 

#include"jeu.h"


#define TAILLE 50
#define HAUTEURMIN 15
#define LARGEURMIN 1

typedef struct {
	Widget widgetFichier;
	Widget labelGeneration;
	Widget labelPeriode;
	jeu *j;
}donnees;

/*			initialiserDonnees
 *
 * Rôle: créer et initialise les donnée partagées
 * Antécédents: argc et argv lors de l'appel du programme
 *
 */
extern donnees *initialiserDonnees(int argc, char *argv[]);

//extern void uneFonctionDuModel();
