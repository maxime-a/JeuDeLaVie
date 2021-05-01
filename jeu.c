/*			jeu.c
 *
 * Contient les fonctions et procédures permettant le déroulement du jeu de la vie 
 * et la manipulation des données du type jeu.
 *
 */

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<errno.h>
#include"libsx.h"
#include"grille.h"

#include"jeu.h"

/*			dessinerQuadrillage
 *
 * Rôle: dessine un grille avec un pas de 10 pixels dans la zone de dessin
 * Antécédent: j un pointeur sur jeu
 *
 */
void dessinerQuadrillage(jeu *j)
{
	for(int x=1;x<=j->cellules.largeur;x++)
	{
		DrawLine(x*10,0,x*10,j->cellules.hauteur*10); 	 //Dessin des barres verticales
		
		for(int y=1;y<=j->cellules.hauteur;y++)
			DrawLine(0,y*10,j->cellules.largeur*10,y*10);  //Dessin des barres horizontales
	} 	
}

/*			dessiner
 *
 * Rôle: dessine la grille si activée et les cellules vivantes de l'état actuel
 * Antécédent: j un pointeur sur jeu
 *
 */
void dessiner(jeu *j)
{
	ClearDrawArea(); 
	if(j->activerQuadrillage)
		dessinerQuadrillage(j);
		
	for(int x=0;x<j->cellules.largeur;x++)
	{
		for(int y=0;y<j->cellules.hauteur;y++)
		{
			if(j->cellules.valeurs[x][y])
				DrawFilledBox(x*10, y*10, 10, 10); 
		}
	}
}

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
 * Antécédents: cellules un pointeur sur la grille des états courants, futureCellules un pointeur sur la grille des états suivants, x,y des entiers pour les coordonnées de la cellule dans cette grille, nbVoisins le nombre de voisins de cette cellules
 */
void appliquerConway(grille *cellules,grille *futurecellules,int x,int y,int nbVoisins)
{
	if(cellules->valeurs[x][y]==vivant)
		if(nbVoisins==2||nbVoisins==3)
			futurecellules->valeurs[x][y]=vivant;
		else if(nbVoisins>3)
			futurecellules->valeurs[x][y]=mort;
		else
			futurecellules->valeurs[x][y]=mort;
	else if(cellules->valeurs[x][y]==mort && nbVoisins==3)
		futurecellules->valeurs[x][y]=vivant;
	else
		futurecellules->valeurs[x][y]=mort;
}

/*			appliquerThompson
 *
 * Rôle: calcul selon la règle Day&Night de Thompson si une cellule nait, survit ou meurt
 * Antécédents: cellules un pointeur sur la grille des états courants, futureCellules un pointeur sur la grille des états suivants, x,y des entiers pour les coordonnées de la cellule dans cette grille, nbVoisins le nombre de voisins de cette cellules
 */
void appliquerThompson(grille *cellules,grille *futurecellules,int x,int y,int nbVoisins)
{
	if(cellules->valeurs[x][y]==vivant)
		if(nbVoisins==3||nbVoisins==4||nbVoisins==6||nbVoisins==7||nbVoisins==8)
			futurecellules->valeurs[x][y]=vivant;
		else
			futurecellules->valeurs[x][y]=mort;
	else
		if(nbVoisins==3||nbVoisins==6||nbVoisins==7||nbVoisins==8)
			futurecellules->valeurs[x][y]=vivant;
		else
			futurecellules->valeurs[x][y]=mort;
}

/*			calculerProchaineGeneration
 *
 * Rôle: calcul selon la règle en vigueur les prochains états des cellules de l'automate
 * Antécédent: j un pointeur sur jeu
 * 
 */
void calculerProchaineGeneration(jeu *j)
{
	char nbVoisins;
	grille futurecellules={j->cellules.largeur,j->cellules.hauteur};		//grille tampon pour la nouvelle genration
	creerGrille(&futurecellules,0);
	
	for(int x=0;x<j->cellules.largeur;x++)
		for(int y=0;y<j->cellules.hauteur;y++)
		{
			nbVoisins=calculerVoisins(j->cellules,x,y);
			if(j->variante==conway)
				appliquerConway(&(j->cellules),&futurecellules,x,y,nbVoisins);
			else
				appliquerThompson(&(j->cellules),&futurecellules,x,y,nbVoisins);
		}
	copierGrille(&(j->cellules),&futurecellules);					
	j->nombreGeneration++;
}

/*			chargerFichier
 *
 * Rôle: charge un état du jeu d'après un fichier
 * Antécédents: filename une chaine de caractères, label un pointeur sur le widget de la zone texte, j un pointeur sur jeu
 *
 */
void chargerFichier(const char *filename, Widget *label, jeu *j)
{
	FILE *fichier;
	if((fichier=fopen(filename, "r"))== NULL)
	{
		perror(filename);
		SetStringEntry(*label, "Chargement impossible");
		Beep();
	}
	else
	{
		int x1,y1,x2,y2; //x1,y1 coordonnées du fichier , x2,y2 coordonées du jeu

		initialiserGrille(&j->cellules,0);

		//lire et décentrer les coordonées du fichier avant de modifier l'état de la cellule correspondante.
		while((fscanf(fichier,"%d,%d",&x1,&y1)!=EOF))
		{
			x2=x1+j->cellules.largeur/2;
			y2=y1+j->cellules.hauteur/2;
			
			if(x2>=0 && x2<j->cellules.largeur && y2>=0 && y2<j->cellules.hauteur) //coordonnées valide dans la zone de jeu 
				j->cellules.valeurs[x2][y2]=vivant; 
			else
			{
				Beep();
				SetStringEntry(*label, "Dessin partiel taille insuffisante");
			}
		}
		dessiner(j);
		fclose(fichier);
		
		j->nombreGeneration=0;
	}
}

/*			sauvegarderFichier
 *
 * Rôle: sauvegarde un état du jeu dans un fichier
 * Antécédents: filename une chaine de caractères, label un pointeur sur le widget de la zone texte, j un pointeur sur jeu
 *
 */
void sauvegarderFichier(const char *filename, Widget *label,jeu *j)
{
	FILE *fichier;
	if((fichier=fopen(filename, "w"))== NULL)
	{
		perror(filename);
		SetStringEntry(*label, "Sauvegarde impossible");
		Beep();
	}
	else
	{
		for(int x=0;x<j->cellules.largeur;x++)
			for(int y=0;y<j->cellules.hauteur;y++)
				if(j->cellules.valeurs[x][y])
					fprintf(fichier,"%d,%d\n",x-j->cellules.largeur/2,y-j->cellules.hauteur/2); //écrire avec les coordonnées centrées(milieu de grille = 0,0 selon l'écriture fichier)
		fclose(fichier);
	}
}
