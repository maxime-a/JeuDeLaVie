/*			modele.c
 *
 * Contient les fonctions et procédures permettant le déroulement du jeu de la vie.
 * 
 *
 */

#include<stdlib.h>
#include<assert.h>
#include"libsx.h"
#include"grille.h"
#include"donnees.h"
#include"vue.h"

#include"modele.h"

/*			calculerVoisins
 *
 * Rôle: calcul le nombre de voisins d'une cellule
 * Antécédents: g un pointeur sur grille et x,y des entiers pour les coordonnées de la cellule dans cette grille
 */
int calculerVoisins(grille g,int x,int y)
{
	int nbVoisins=0;
	for(int b=0;b<3;b++)   
		for(int n=0;n<3;n++)
			if(x-1+b>=0 && y-1+n>0 && x-1+b<g.largeur &&y-1+n<g.hauteur) //Vérifie si le voisin a un indice valide dans la grille
				if(b!=1 || n!=1)				    //Ne pas compter la cellule elle même dans ses voisins 
					if(g.valeurs[x-1+b][y-1+n]==vivant)
						nbVoisins++;
	return nbVoisins;
}

/*			appliquerConway
 *
 * Rôle: calcul selon la règle de J.Conway si une cellule nait, survit ou meurt
 * Antécédents: val l'état de la cellule, nbVoisins le nombre de voisins de cette cellules
 */
char appliquerConway(char val,int nbVoisins)
{
	if(val==vivant)
		if(nbVoisins==2||nbVoisins==3)
			return vivant;
		else if(nbVoisins>3)
			return mort;
		else
			return mort;
	else if(val==mort && nbVoisins==3)
		return vivant;
	else
		return mort;
}

/*			appliquerThompson
 *
 * Rôle: calcul selon la règle Day&Night de Thompson si une cellule nait, survit ou meurt
 * Antécédents: val l'état de la cellule, nbVoisins le nombre de voisins de cette cellules
 */
char appliquerThompson(char val,int nbVoisins)
{
	if(val==vivant)
		if(nbVoisins==3||nbVoisins==4||nbVoisins==6||nbVoisins==7||nbVoisins==8)
			return vivant;
		else
			return mort;
	else
		if(nbVoisins==3||nbVoisins==6||nbVoisins==7||nbVoisins==8)
			return vivant;
		else
			return mort;
}

/*			calculerProchaineGeneration
 *
 * Rôle: calcul selon la règle en vigueur les prochains états des cellules de l'automate
 * Antécédent: j un pointeur sur jeu
 * 
 */
void calculerProchaineGeneration(donnees *d)
{
	char nbVoisins;
	grille futureCellules={getLargeur(d),getHauteur(d)};		//grille tampon pour la nouvelle genration
	creerGrille(&futureCellules,0);
	
	for(int x=0;x<getLargeur(d);x++)
		for(int y=0;y<getHauteur(d);y++)
		{
			nbVoisins=calculerVoisins(*getCellules(d),x,y);
			if(getVariante(d)==conway)
				futureCellules.valeurs[x][y]=appliquerConway(getValeur(d,x,y),nbVoisins);
			else
				futureCellules.valeurs[x][y]=appliquerThompson(getValeur(d,x,y),nbVoisins);
		}
	copierGrille(getCellules(d),&futureCellules);					
	setNombreGeneration(d,getNombreGeneration(d)+1);
}
