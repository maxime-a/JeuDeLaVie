/*			jeu.h
 *
 * Contient les prototypes des fonctions et procédures permettant le déroulement du jeu de la vie 
 * et la manipulation des données du type jeu. Ainsi que la déclaration du type jeu et des
 * types énumérés etat et mode.
 *
 */
 
#pragma once

#include"grille.h"

enum etat {mort,vivant};

enum mode {conway,thompson};

typedef struct {
	char variante;
	char activerQuadrillage;
	char desactiverDelai;
	int delai;
	int nombreGeneration;
	grille cellules;	
}jeu;

jeu *j;

/*			dessinerQuadrillage
 *
 * Rôle: dessine un grille avec un pas de 10 pixels dans la zone de dessin
 *
 */
extern void dessinerQuadrillage();

/*			dessiner
 *
 * Rôle: dessine la grille si activée et les cellules vivantes de l'état actuel
 *
 */
extern void dessiner();


/*			calculerVoisins
 *
 * Rôle: calcul le nombre de voisins d'une cellule
 * Antécédents: g un pointeur sur grille et x,y des entiers pour les coordonnées de la cellule dans cette grille
 */
extern int calculerVoisins(grille g,int x,int y);

/*			appliquerConway
 *
 * Rôle: calcul selon la règle de J.Conway si une cellule nait, survit ou meurt
 * Antécédents: cellules un pointeur sur la grille des états courants, futureCellules un pointeur sur la grille des états suivants, x,y des entiers pour les coordonnées de la cellule dans cette grille, nbVoisins le nombre de voisins de cette cellules
 */
extern void appliquerConway(grille *cellules,grille *futurecellules,int x,int y,int nbVoisins);

/*			appliquerThompson
 *
 * Rôle: calcul selon la règle Day&Night de Thompson si une cellule nait, survit ou meurt
 * Antécédents: cellules un pointeur sur la grille des états courants, futureCellules un pointeur sur la grille des états suivants, x,y des entiers pour les coordonnées de la cellule dans cette grille, nbVoisins le nombre de voisins de cette cellules
 */
extern void appliquerThompson(grille *cellules,grille *futurecellules,int x,int y,int nbVoisins);

/*			calculerProchaineGeneration
 *
 * Rôle: calcul selon la règle en vigueur les prochains états des cellules de l'automate
 * 
 */
extern void calculerProchaineGeneration();

/*			chargerFichier
 *
 * Rôle: charge un état du jeu d'après un fichier
 * Antécédents: filename une chaine de caractères, label un pointeur sur le widget de la zone texte
 *
 */
extern void chargerFichier(const char *filename, Widget *label);

/*			sauvegarderFichier
 *
 * Rôle: sauvegarde un état du jeu dans un fichier
 * Antécédents: filename une chaine de caractères, label un pointeur sur le widget de la zone texte
 *
 */
extern void sauvegarderFichier(const char *filename, Widget *label);
