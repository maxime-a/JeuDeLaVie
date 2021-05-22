/*			modele.c
 *
 * Contient les fonctions et procédures permettant le déroulement du jeu de la vie.
 * 
 *
 */

#include<stdlib.h>
#include<libsx.h>

#include"modele.h"

/*			calculerVoisins
 *
 * Rôle: calcul le nombre de voisins d'une cellule
 * Antécédents: g un pointeur sur grille et x,y des entiers pour les coordonnées de la cellule dans cette grille
 */
int calculerVoisins(grille g,int x,int y)
{
	int nbVoisins=0;
	for(int b=-1;b<2;b++)   
		for(int n=-1;n<2;n++)
			if(x+b>=0 && y+n>0 && x+b<g.largeur &&y+n<g.hauteur)  //Vérifie si le voisin a un indice valide dans la grille
				if(b!=0 || n!=0)				//Ne pas compter la cellule elle même dans ses voisins 
					if(g.valeurs[x+b][y+n]==survie||g.valeurs[x+b][y+n]==naissance)
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
	if(val==survie||val==naissance)
	{
		if(nbVoisins==2||nbVoisins==3)
			return survie;		//survie
		else if(nbVoisins>3)
			return surpopulation;	//mort par surpopulation
		else
			return isolement;	//mort par isolement
	}
	if((val==isolement || val==surpopulation || val==mort) && nbVoisins==3)
		return naissance;		//naissance
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
	if(val==survie||val==naissance)
		if(nbVoisins==3||nbVoisins==4||nbVoisins==6||nbVoisins==7||nbVoisins==8)
			return survie;
		else
			return mort;
	else
		if(nbVoisins==3||nbVoisins==6||nbVoisins==7||nbVoisins==8)
			return survie;
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
	grille futureCellules={getLargeur(d),getHauteur(d)};			//grille tampon pour la nouvelle genration
	creerGrille(&futureCellules,0);
	
	for(int x=0;x<getLargeur(d);x++)					//parcours de toutes les cellules en largeur
		for(int y=0;y<getHauteur(d);y++)				//et en hauteur
		{
			nbVoisins=calculerVoisins(*getCellules(d),x,y);	//calcul des voisins pour la cellule de coordonnées x,y
			if(getVariante(d)==conway)
				futureCellules.valeurs[x][y]=appliquerConway(getValeur(d,x,y),nbVoisins);
			else
				futureCellules.valeurs[x][y]=appliquerThompson(getValeur(d,x,y),nbVoisins);
		}
	copierGrille(getCellules(d),&futureCellules);					
	setNombreGeneration(d,getNombreGeneration(d)+1);			//incrémentation du numéro de génération
}
