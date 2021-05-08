/*			donnees.c
 *
 * Contient la structure des données principales et la fonction d'initialisation
 *
 */

#include<stdlib.h>
#include<stdio.h>
#include<libsx.h>
#include<errno.h>
#include<assert.h>

#include"vue.h"

#include"donnees.h"

/*			initialiserDonnees
 *
 * Rôle: créer et initialise les données partagées
 * Antécédents: argc et argv lors de l'appel du programme
 *
 */
donnees *initialiserDonnees(int argc, char *argv[])
{
	donnees *d=malloc(sizeof(donnees));
	
	if(d==NULL)				//Si problème d'allocation 
		return NULL;
	
	d->cellules.largeur=TAILLEDEFAUT;
	d->cellules.hauteur=TAILLEDEFAUT;
	
    	if(argc>2)				//Si deux paramètres sont fournis pour la largeur et hauteur
    	{
    			int l,h;
    			
    			l=atoi(argv[1]);
    			if(l>=LARGEURMIN)    	//paramètre valide
    				d->cellules.largeur=l;
    			h=atoi(argv[2]);
    			if(h>=HAUTEURMIN)	//paramètre valide
    				d->cellules.hauteur=h;
    	}
    	else if(argc==2)			//Si un seul paramètre, largeur et hauteur seront identique au paramètre
 	{
    		int taille;
   			
  		taille=atoi(argv[1]);
    		if(taille>=HAUTEURMIN)		//paramètre valide
    		{
    			d->cellules.largeur=taille;
    			d->cellules.hauteur=taille;
		}
    	}
	
	d->variante=conway;
	d->desactiverDelai=TRUE;
	d->delai=500;				//0.5s par défaut
	d->activerQuadrillage=TRUE;
	d->nombreGeneration=0;
	
	creerGrille(&(d->cellules),0);
	
	return d;
}

/*			getHauteur
 *
 * Rôle: permet de récuperer la valeur de la hauteur de la zone de jeu
 * Antécédents: un pointeur sur donnees
 *
 */
int getHauteur(donnees *d)
{
	return d->cellules.hauteur;
}

/*			getLargeur
 *
 * Rôle: permet de récuperer la valeur de la largeur de la zone de jeu
 * Antécédents: un pointeur sur donnees
 *
 */
int getLargeur(donnees *d)
{
	return d->cellules.hauteur;
}

/*			getQuadrillage
 *
 * Rôle: permet de récuperer la volonté ou non d'activer le quadrillage
 * Antécédents: un pointeur sur donnees
 *
 */
char getQuadrillage(donnees *d)
{
	return d->activerQuadrillage;
}

/*			getValeur
 *
 * Rôle: permet de récuperer l'état d'une cellule particulière du jeu
 * Antécédents: un pointeur sur donnees et deux entiers x,y représentant les coordonnées de la cellule
 *
 */
char getValeur(donnees *d,int x,int y)
{
	return d->cellules.valeurs[x][y];
}

/*			getGeneration
 *
 * Rôle: permet de récuperer le nombre de générations effectuées
 * Antécédents: un pointeur sur donnees
 *
 */
int getNombreGeneration(donnees *d)
{
	return d->nombreGeneration;
}

/*			getDelai
 *
 * Rôle: permet de récuperer la valeur de la période entre chaque génération
 * Antécédents: un pointeur sur donnees
 *
 */
int getDelai(donnees *d)
{
	return d->delai;
}

/*			getDesacitverDelai
 *
 * Rôle: permet de récuperer la volonté ou non de stopper l'animation
 * Antécédents: un pointeur sur donnees
 *
 */
char getDesactiverDelai(donnees *d)
{
	return d->desactiverDelai;
}

/*			getVariante
 *
 * Rôle: permet de récuperer la variante de calcul utilisée
 * Antécédents: un pointeur sur donnees
 *
 */
char getVariante(donnees *d)
{
	return d->variante;
}

/*			getLabelGeneration
 *
 * Rôle: permet de récuperer le label affichant le nombre de génération
 * Antécédents: un pointeur sur donnees
 *
 */
Widget getLabelGeneration(donnees *d)
{
	return d->labelGeneration;
}

/*			getLabelPeriode
 *
 * Rôle: permet de récuperer le label affichant la valeur de la période
 * Antécédents: un pointeur sur donnees
 *
 */
Widget getLabelPeriode(donnees *d)
{
	return d->labelPeriode;
}

/*			getCellules
 *
 * Rôle: permet de récuperer un pointeur vers la population de cellules
 * Antécédents: un pointeur sur donnees
 *
 */
grille *getCellules(donnees *d)
{
	return &d->cellules;
}

/*			getWidgetFichier
 *
 * Rôle: permet de récuperer le widget avec l'entrée texte pour le nom de fichier
 * Antécédents: un pointeur sur donnees
 *
 */
Widget getWidgetFichier(donnees *d)
{	
	return d->widgetFichier;
}

/*			setValeur
 *
 * Rôle: permet de modifier l'état d'une cellule
 * Antécédents: un pointeur sur donnees, deux entiers x, y et la valeur de l'état
 *
 */
void setValeur(donnees *d,int x,int y,char val)
{
	assert(x>=0 && x<d->cellules.largeur && y>=0 && y<d->cellules.hauteur); 
	d->cellules.valeurs[x][y]=val;
}

/*			setValeur
 *
 * Rôle: permet de modifier le numéro de génération de l'automate
 * Antécédents: un pointeur sur donnees et un entier avec la valeur voulue
 *
 */
void setNombreGeneration(donnees *d, int val)
{
	assert(val>=0);
	d->nombreGeneration=val;
}

/*			setDelai
 *
 * Rôle: permet de modifier la valeur de la période entre générations
 * Antécédents: un pointeur sur donnees et un entier pour la valeur de la période
 *
 */
void setDelai(donnees *d, int val)
{
	assert(val>=0);
	d->delai=val;
}

/*			setDesactiverDelai
 *
 * Rôle: permet de modifier la volonté ou non de stopper l'animation
 * Antécédents: un pointeur sur donnees et la valeur de type char (attendue comme FALSE ou TRUE)
 *
 */
void setDesactiverDelai(donnees *d,char val)
{
	d->desactiverDelai=val;
}

/*			setActiverQuadrillage
 *
 * Rôle: permet de modifier la volonté ou non d'activer le quadrillage
 * Antécédents: un pointeur sur donnees et la valeur de type char (attendue comme FALSE ou TRUE)
 *
 */
void setActiverQuadrillage(donnees *d,char val)
{
	d->activerQuadrillage=val;
}

/*			setVariante
 *
 * Rôle: permet de modifier la variante de calcul
 * Antécédents: un pointeur sur donnees et la valeur de type char (attendue comme conway ou thompson)
 *
 */
void setVariante(donnees *d, char val)
{
	d->variante=val;
}

/*			reinitialiserDonnees
 *
 * Rôle: permet de faire mourir toutes les cellules et remettre à zéro le nombre de génération
 * Antécédents: un pointeur sur donnees
 *
 */
void reinitialiserDonnees(donnees *d)
{
	initialiserGrille(&d->cellules,0);		//faire mourir toutes les cellules
	d->nombreGeneration=0;
}

/*			libererDonnees
 *
 * Rôle: permet de désalloué l'espace mémoire pris par les données partagées
 * Antécédents: un pointeur sur donnees 
 *
 */
void libererDonnees(donnees *d)
{
	libererGrille(&d->cellules);
	free(d);
}

/*			chargerFichier
 *
 * Rôle: charge un état du jeu d'après un fichier
 * Antécédents: filename une chaine de caractères, d un pointeur sur donnees
 *
 */
void chargerFichier(const char *filename, donnees *d)
{
	FILE *fichier;
	if((fichier=fopen(filename, "r"))== NULL)
	{
		perror(filename);
		SetStringEntry(getWidgetFichier(d), "Chargement impossible");
		Beep();
	}
	else
	{
		int x1,y1,x2,y2; //x1,y1 coordonnées du fichier , x2,y2 coordonées du jeu

		initialiserGrille(getCellules(d),0);

		//lire et décentrer les coordonées du fichier avant de modifier l'état de la cellule correspondante.
		while((fscanf(fichier,"%d,%d",&x1,&y1)!=EOF))
		{
			x2=x1+getLargeur(d)/2;
			y2=y1+getHauteur(d)/2;
			
			if(x2>=0 && x2<getLargeur(d) && y2>=0 && y2<getHauteur(d)) //coordonnées valide dans la zone de jeu 
				setValeur(d,x2,y2,vivant); 
			else
			{
				Beep();
				SetStringEntry(getWidgetFichier(d), "Dessin partiel taille insuffisante");
			}
		}
		dessiner(d);
		fclose(fichier);
		
		setNombreGeneration(d,0);
	}
}

/*			sauvegarderFichier
 *
 * Rôle: sauvegarde un état du jeu dans un fichier
 * Antécédents: filename une chaine de caractères, d un pointeur sur donnees
 *
 */
void sauvegarderFichier(const char *filename, donnees *d)
{
	FILE *fichier;
	if((fichier=fopen(filename, "w"))== NULL)
	{
		perror(filename);
		SetStringEntry(getWidgetFichier(d), "Sauvegarde impossible");
		Beep();
	}
	else
	{
		for(int x=0;x<getLargeur(d);x++)
			for(int y=0;y<getHauteur(d);y++)
				if(getValeur(d,x,y))
					fprintf(fichier,"%d,%d\n",x-getLargeur(d)/2,y-getHauteur(d)/2); //écrire avec les coordonnées centrées(milieu de grille = 0,0 selon l'écriture fichier)
		fclose(fichier);
	}
}
