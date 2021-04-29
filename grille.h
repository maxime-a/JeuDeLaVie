/*			grille.h
 *
 * Contient les prototypes des procédures de manipulation de grilles. Ainsi que la déclaration du type grille.
 *
 */

#pragma once

typedef struct {
	int largeur;
	int hauteur;
	char **valeurs;
}grille;

/*			copierGrille
 *
 * Rôle: copie toutes les valeurs d'une grille dans une autre
 * Antécédents : a un pointeur sur la grille de destination, b un pointeur sur la grille copiée 
 * 
 */
extern void copierGrille(grille *a, grille *b);

/*			initialiserGrille
 *
 * Rôle: affecte une valeur donnée à tout les éléments d'une grille
 * Antécédents: g un pointeur sur grille et val la valeur d'initialisation des éléments
 */
extern void initialiserGrille(grille *g,char val);

/*			creerGrille
 *
 * Rôle: créer une grille initialisée avec une valeur donnée
 * Antécédents: g un pointeur sur grille et val la valeur d'initialisation des éléments
 */
extern void creerGrille(grille *g,char val);

/*			libererGrille
 *
 * Rôle: désalloue l'espace mémoire occupé par une grille
 * Antécédents: g un pointeur sur grille
 */
extern void libererGrille(grille *g);
