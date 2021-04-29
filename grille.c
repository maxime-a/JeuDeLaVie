/*			grille.c
 *
 * Contient les procédures de manipulation de grilles.
 *
 */

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

#include"grille.h"

/*			copierGrille
 *
 * Rôle: copie toutes les valeurs d'une grille dans une autre
 * Antécédents : a un pointeur sur la grille de destination, b un pointeur sur la grille copiée 
 * 
 */
void copierGrille(grille *a, grille *b)
{
	assert(a->largeur==b->largeur&&a->hauteur==b->hauteur); //Les grilles sont de même tailles
	for(int x=0;x<a->largeur;x++)
	{
		for(int y=0;y<a->hauteur;y++)
		{
			a->valeurs[x][y]=b->valeurs[x][y];
		}
	}
}

/*			initialiserGrille
 *
 * Rôle: affecte une valeur donnée à tout les éléments d'une grille
 * Antécédents: g un pointeur sur grille et val la valeur d'initialisation des éléments
 */
void initialiserGrille(grille *g,char val)
{
	for(int x=0;x<g->largeur;x++)
	{
		for(int y=0;y<g->hauteur;y++)
		{
			g->valeurs[x][y]=val;
		}
	}
}

/*			creerGrille
 *
 * Rôle: créer une grille initialisée avec une valeur donnée
 * Antécédents: g un pointeur sur grille et val la valeur d'initialisation des éléments
 */
void creerGrille(grille *g,char val)
{
	g->valeurs = malloc(g->hauteur * sizeof(char *));	
    	for (int i=0; i<g->hauteur; i++)
        	g->valeurs[i] = malloc(g->largeur * sizeof(char));
	initialiserGrille(g,val);
}

/*			libererGrille
 *
 * Rôle: désalloue l'espace mémoire occupé par une grille
 * Antécédents: g un pointeur sur grille
 */
void libererGrille(grille *g)
{	
    	for (int i=0; i<g->hauteur; i++)
        	free(g->valeurs[i]);
        free(g->valeurs);
}
