/*			donnees.c
 *
 * Contient la structure des données principales et la fonction d'initialisation
 *
 */

#include<stdlib.h>
#include<stdio.h>
#include<libsx.h>
#include<errno.h>
#include"donnees.h"
#include"vue.h"

/*			initialiserDonnees
 *
 * Rôle: créer et initialise les donnée partagées
 * Antécédents: argc et argv lors de l'appel du programme
 *
 */
donnees *initialiserDonnees(int argc, char *argv[])
{
	donnees *d=malloc(sizeof(donnees));
	
	if(d==NULL)				//Si problème d'allocation 
		return NULL;
	
	d->cellules.largeur=TAILLE;
	d->cellules.hauteur=TAILLE;
	
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

int getHauteur(donnees *d)
{
	return d->cellules.hauteur;
}

int getLargeur(donnees *d)
{
	return d->cellules.hauteur;
}

char getQuadrillage(donnees *d)
{
	return d->activerQuadrillage;
}

char getValeur(donnees *d,int x,int y)
{
	return d->cellules.valeurs[x][y];
}

int getNombreGeneration(donnees *d)
{
	return d->nombreGeneration;
}

int getDelai(donnees *d)
{
	return d->delai;
}

char getDesactiverDelai(donnees *d)
{
	return d->desactiverDelai;
}

char getVariante(donnees *d)
{
	return d->variante;
}

Widget getLabelGeneration(donnees *d)
{
	return d->labelGeneration;
}

Widget getLabelPeriode(donnees *d)
{
	return d->labelPeriode;
}

grille *getCellules(donnees *d)
{
	return &d->cellules;
}

Widget getWidgetFichier(donnees *d)
{	
	return d->widgetFichier;
}

void setValeur(donnees *d,int x,int y,char val)
{
	d->cellules.valeurs[x][y]=val;
}

void setNombreGeneration(donnees *d, int val)
{
	d->nombreGeneration=val;
}

void setDelai(donnees *d, int val)
{
	d->delai=val;
}

void setDesactiverDelai(donnees *d,char val)
{
	d->desactiverDelai=val;
}

void setActiverQuadrillage(donnees *d,char val)
{
	d->activerQuadrillage=val;
}

void setVariante(donnees *d, char val)
{
	d->variante=val;
}

void reinitialiserDonnees(donnees *d)
{
	initialiserGrille(&d->cellules,0);		//faire mourir toutes les cellules
	d->nombreGeneration=0;
}

void libererDonnees(donnees *d)
{
	libererGrille(&d->cellules);
	free(d);
}

/*			chargerFichier
 *
 * Rôle: charge un état du jeu d'après un fichier
 * Antécédents: filename une chaine de caractères, label un pointeur sur le widget de la zone texte, j un pointeur sur jeu
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
 * Antécédents: filename une chaine de caractères, label un pointeur sur le widget de la zone texte, j un pointeur sur jeu
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
