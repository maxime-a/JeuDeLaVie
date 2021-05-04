/*			donnees.h
 *
 * Contient la structure des données principales et le prototype de la fonction d'initialisation
 * Ainsi que la déclaration des types énumérés etat et mode.
 *
 */

#pragma once 

#include"grille.h"

#define TAILLE 50
#define HAUTEURMIN 15
#define LARGEURMIN 1

enum etat {mort,vivant};

enum mode {conway,thompson};

typedef struct {

	Widget widgetFichier;
	Widget labelGeneration;
	Widget labelPeriode;
	
	char variante;
	char activerQuadrillage;
	char desactiverDelai;
	int delai;
	int nombreGeneration;
	
	grille cellules;
}donnees;
/*			initialiserDonnees
 *
 * Rôle: créer et initialise les donnée partagées
 * Antécédents: argc et argv lors de l'appel du programme
 *
 */
extern donnees *initialiserDonnees(int argc, char *argv[]);

extern int getHauteur(donnees *d);

extern int getLargeur(donnees *d);

extern char getQuadrillage(donnees *d);

extern char getValeur(donnees *d,int x,int y);

extern char getVariante(donnees *d);

extern int getDelai(donnees *d);

extern char getDesactiverDelai(donnees *d);

extern int getNombreGeneration(donnees *d);

extern Widget getLabelGeneration(donnees *d);

extern Widget getLabelPeriode(donnees *d);

extern grille *getCellules(donnees *d);

extern Widget getWidgetFichier(donnees *d);

extern void setValeur(donnees *d,int x,int y,char val);

extern void setNombreGeneration(donnees *d, int val);

extern void setDelai(donnees *d, int val);

extern void setDesactiverDelai(donnees *d,char val);

extern void setActiverQuadrillage(donnees *d,char val);

extern void setVariante(donnees *d, char val);

extern void reinitialiserDonnees(donnees *d);

extern void libererDonnees(donnees *d);

/*			chargerFichier
 *
 * Rôle: charge un état du jeu d'après un fichier
 * Antécédents: filename une chaine de caractères, label un pointeur sur le widget de la zone texte, j un pointeur sur jeu
 *
 */
extern void chargerFichier(const char *filename, donnees *d);

/*			sauvegarderFichier
 *
 * Rôle: sauvegarde un état du jeu dans un fichier
 * Antécédents: filename une chaine de caractères, label un pointeur sur le widget de la zone texte, j un pointeur sur jeu
 *
 */
extern void sauvegarderFichier(const char *filename, donnees *d);
