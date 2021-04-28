#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<errno.h>
#include"libsx.h"

#include"jeu.h"

void dessinerGrille()
{
	for(int x=1;x<=j->cellules.largeur;x++){
		DrawLine(x*10,0,x*10,j->cellules.hauteur*10);}
		for(int y=1;y<=j->cellules.hauteur;y++){
			DrawLine(0,y*10,j->cellules.largeur*10,y*10);}	
}

void dessiner()
{
	ClearDrawArea(); 
	if(j->activerGrille)
		dessinerGrille();
		
	for(int x=0;x<j->cellules.largeur;x++)
	{
		for(int y=0;y<j->cellules.hauteur;y++)
		{
			if(j->cellules.valeurs[x][y])
				DrawFilledBox(x*10, y*10, 10, 10); 
		}
	}
}

void copierGrille(grille *a, grille *b)
{
	assert(a->largeur==b->largeur&&a->hauteur==b->hauteur);
	for(int x=0;x<a->largeur;x++)
	{
		for(int y=0;y<a->hauteur;y++)
		{
			a->valeurs[x][y]=b->valeurs[x][y];
		}
	}
}

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

void creerGrille(grille *g,char val)
{
	g->valeurs = malloc(g->hauteur * sizeof(char *));	
    	for (int i=0; i<g->hauteur; i++)
        	g->valeurs[i] = malloc(g->largeur * sizeof(char));
	initialiserGrille(g,val);
}

void libererGrille(grille *g)
{	
    	for (int i=0; i<g->hauteur; i++)
        	free(g->valeurs[i]);
        free(g->valeurs);
}

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

void calculerProchaineGeneration()
{
	char nbVoisins;
	grille futurecellules={j->cellules.largeur,j->cellules.hauteur};
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

void chargerFichier(const char *filename, Widget *label)
{
	FILE *fichier;
	if((fichier=fopen(filename, "r"))== NULL)
	{
		perror(filename);
		SetStringEntry(*label, "Unable to load file");
		Beep();
	}
	else
	{
		int x,y;

		initialiserGrille(&j->cellules,0);

		while((fscanf(fichier,"%d,%d",&x,&y)!=EOF))		
			j->cellules.valeurs[x+j->cellules.largeur/2][y+j->cellules.hauteur/2]=vivant;
		dessiner();
		fclose(fichier);
		
		j->nombreGeneration=0;
	}
}

void sauvegarderFichier(const char *filename, Widget *label)
{
	FILE *fichier;
	if((fichier=fopen(filename, "w"))== NULL)
	{
		perror(filename);
		SetStringEntry(*label, "Unable to save file");
		Beep();
	}
	else
	{
		for(int x=0;x<j->cellules.largeur;x++)
			for(int y=0;y<j->cellules.hauteur;y++)
				if(j->cellules.valeurs[x][y])
					fprintf(fichier,"%d,%d\n",x-j->cellules.largeur/2,y-j->cellules.hauteur/2);
					//centrer les coordonnées (milieu de grille = 0,0)
		fclose(fichier);
	}
}
