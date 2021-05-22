/*			donnees.h
 *
 * Contient la structure des données principales et le prototype de la fonction d'initialisation
 * Ainsi que la déclaration des types énumérés etat et mode.
 *
 */

#pragma once 

#include"grille.h"

#define TAILLEDEFAUT 50
#define HAUTEURMIN 20
#define LARGEURMIN 1

enum etat {naissance,survie,isolement,surpopulation,mort,vivant};

enum mode {conway,thompson};

typedef struct {

	Widget widgetFichier;
	Widget labelGeneration;
	Widget labelPeriode;
	
	char variante;
	char activerQuadrillage;
	char desactiverDelai;
	char couleur;
	int delai;
	int nombreGeneration;
	
	grille cellules;
}donnees;

/*			initialiserDonnees
 *
 * Rôle: créer et initialise les données partagées
 * Antécédents: argc et argv lors de l'appel du programme
 *
 */
extern donnees *initialiserDonnees(int argc, char *argv[]);

/*			getHauteur
 *
 * Rôle: permet de récuperer la valeur de la hauteur de la zone de jeu
 * Antécédents: un pointeur sur donnees
 *
 */
extern int getHauteur(donnees *d);

/*			getLargeur
 *
 * Rôle: permet de récuperer la valeur de la largeur de la zone de jeu
 * Antécédents: un pointeur sur donnees
 *
 */
extern int getLargeur(donnees *d);

/*			getQuadrillage
 *
 * Rôle: permet de récuperer la volonté ou non d'activer le quadrillage
 * Antécédents: un pointeur sur donnees
 *
 */
extern char getQuadrillage(donnees *d);

/*			getValeur
 *
 * Rôle: permet de récuperer l'état d'une cellule particulière du jeu
 * Antécédents: un pointeur sur donnees et deux entiers x,y représentant les coordonnées de la cellule
 *
 */
extern char getValeur(donnees *d,int x,int y);

/*			getGeneration
 *
 * Rôle: permet de récuperer le nombre de générations effectuées
 * Antécédents: un pointeur sur donnees
 *
 */
extern int getNombreGeneration(donnees *d);

/*			getDelai
 *
 * Rôle: permet de récuperer la valeur de la période entre chaque génération
 * Antécédents: un pointeur sur donnees
 *
 */
extern int getDelai(donnees *d);

/*			getDesacitverDelai
 *
 * Rôle: permet de récuperer la volonté ou non de stopper l'animation
 * Antécédents: un pointeur sur donnees
 *
 */
extern char getDesactiverDelai(donnees *d);

/*			getVariante
 *
 * Rôle: permet de récuperer la variante de calcul utilisée
 * Antécédents: un pointeur sur donnees
 *
 */
extern char getVariante(donnees *d);

/*			getCouleur
 *
 * Rôle: permet de récuperer le mode d'affichage voulu
 * Antécédents: un pointeur sur donnees
 *
 */
char getCouleur(donnees *d);

/*			getLabelGeneration
 *
 * Rôle: permet de récuperer le label affichant le nombre de génération
 * Antécédents: un pointeur sur donnees
 *
 */
extern Widget getLabelGeneration(donnees *d);

/*			getLabelPeriode
 *
 * Rôle: permet de récuperer le label affichant la valeur de la période
 * Antécédents: un pointeur sur donnees
 *
 */
extern Widget getLabelPeriode(donnees *d);

/*			getCellules
 *
 * Rôle: permet de récuperer un pointeur vers la population de cellules
 * Antécédents: un pointeur sur donnees
 *
 */
extern grille *getCellules(donnees *d);

/*			getWidgetFichier
 *
 * Rôle: permet de récuperer le widget avec l'entrée texte pour le nom de fichier
 * Antécédents: un pointeur sur donnees
 *
 */
extern Widget getWidgetFichier(donnees *d);

/*			setValeur
 *
 * Rôle: permet de modifier l'état d'une cellule
 * Antécédents: un pointeur sur donnees, deux entiers x, y et la valeur de l'état
 *
 */
extern void setValeur(donnees *d,int x,int y,char val);

/*			setValeur
 *
 * Rôle: permet de modifier le numéro de génération de l'automate
 * Antécédents: un pointeur sur donnees et un entier avec la valeur voulue
 *
 */
extern void setNombreGeneration(donnees *d, int val);

/*			setDelai
 *
 * Rôle: permet de modifier la valeur de la période entre générations
 * Antécédents: un pointeur sur donnees et un entier pour la valeur de la période
 *
 */
extern void setDelai(donnees *d, int val);

/*			setDesactiverDelai
 *
 * Rôle: permet de modifier la volonté ou non de stopper l'animation
 * Antécédents: un pointeur sur donnees et la valeur de type char (attendue comme FALSE ou TRUE)
 *
 */
extern void setDesactiverDelai(donnees *d,char val);

/*			setActiverQuadrillage
 *
 * Rôle: permet de modifier la volonté ou non d'activer le quadrillage
 * Antécédents: un pointeur sur donnees et la valeur de type char (attendue comme FALSE ou TRUE)
 *
 */
extern void setActiverQuadrillage(donnees *d,char val);

/*			setCouleur
 *
 * Rôle: permet de modifier la volonté ou non d'activer l'affichage des couleurs
 * Antécédents: un pointeur sur donnees et la valeur de type char (attendue comme FALSE ou TRUE)
 *
 */
 
extern void setCouleur(donnees *d,char val);

/*			setVariante
 *
 * Rôle: permet de modifier la variante de calcul
 * Antécédents: un pointeur sur donnees et la valeur de type char (attendue comme conway ou thompson)
 *
 */
extern void setVariante(donnees *d, char val);

/*			reinitialiserDonnees
 *
 * Rôle: permet de faire mourir toutes les cellules et remettre à zéro le nombre de génération
 * Antécédents: un pointeur sur donnees
 *
 */
extern void reinitialiserDonnees(donnees *d);

/*			libererDonnees
 *
 * Rôle: permet de désalloué l'espace mémoire pris par les données partagées
 * Antécédents: un pointeur sur donnees 
 *
 */
extern void libererDonnees(donnees *d);

/*			chargerFichier
 *
 * Rôle: charge un état du jeu d'après un fichier
 * Antécédents: filename une chaine de caractères, d un pointeur sur donnees
 *
 */
extern void chargerFichier(const char *filename, donnees *d);

/*			sauvegarderFichier
 *
 * Rôle: sauvegarde un état du jeu dans un fichier
 * Antécédents: filename une chaine de caractères, d un pointeur sur donnees
 *
 */
extern void sauvegarderFichier(const char *filename, donnees *d);
