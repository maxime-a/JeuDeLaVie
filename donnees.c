/*			donnees.c
 *
 * Contient la structure des données principales et la fonction d'initialisation
 *
 */

#include<stdlib.h>
#include<libsx.h>
#include"donnees.h"

/*			initialiserDonnees
 *
 * Rôle: créer et initialise les donnée partagées
 * Antécédents: argc et argv lors de l'appel du programme
 *
 */
donnees *initialiserDonnees(int argc, char *argv[])
{
	jeu *j;
	
	j=malloc(sizeof(jeu));
	
	if(j==NULL)				//Si problème d'allocation 
		return NULL;
	
	j->cellules.largeur=TAILLE;
	j->cellules.hauteur=TAILLE;
	
    	if(argc>2)				//Si deux paramètres sont fournis pour la largeur et hauteur
    	{
    			int l,h;
    			
    			l=atoi(argv[1]);
    			if(l>=LARGEURMIN)    	//paramètre valide
    				j->cellules.largeur=l;
    			h=atoi(argv[2]);
    			if(h>=HAUTEURMIN)	//paramètre valide
    				j->cellules.hauteur=h;
    	}
    	else if(argc==2)			//Si un seul paramètre, largeur et hauteur seront identique au paramètre
 	{
    		int taille;
   			
  		taille=atoi(argv[1]);
    		if(taille>=HAUTEURMIN)		//paramètre valide
    		{
    			j->cellules.largeur=taille;
    			j->cellules.hauteur=taille;
		}
    	}
	
	j->variante=conway;
	j->desactiverDelai=TRUE;
	j->delai=500;				//0.5s par défaut
	j->activerQuadrillage=TRUE;
	j->nombreGeneration=0;
	
	creerGrille(&(j->cellules),0);
	
	donnees *d=malloc(sizeof(donnees));
	
	d->j=j;
	
	return d;
}
