#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<errno.h>
#include"libsx.h"

#include"jeu.h"

void drawGrid()
{
	for(int i=1;i<=g->cells.width;i++){
		DrawLine(i*10,0,i*10,g->cells.height*10);}
		for(int j=1;j<=g->cells.height;j++){
			DrawLine(0,j*10,g->cells.width*10,j*10);}	
}

void draw()
{
	ClearDrawArea(); 
	if(g->grid)
		drawGrid();
		
	for(int i=0;i<g->cells.width;i++)
	{
		for(int j=0;j<g->cells.height;j++)
		{
			if(g->cells.values[i][j])
				DrawFilledBox(i*10, j*10, 10, 10); 
		}
	}
}

void copyGrid(grid *a, grid *b)
{
	assert(a->width==b->width&&a->height==b->height);
	for(int x=0;x<a->width;x++)
	{
		for(int y=0;y<a->height;y++)
		{
			a->values[x][y]=b->values[x][y];
		}
	}
}

void setGrid(grid *g,char val)
{
	for(int x=0;x<g->width;x++)
	{
		for(int y=0;y<g->height;y++)
		{
			g->values[x][y]=val;
		}
	}
}

void initGrid(grid *g,char val)
{
	g->values = malloc(g->height * sizeof(char *));	
    	for (int i=0; i<g->height; i++)
        	g->values[i] = malloc(g->width * sizeof(char));
	setGrid(g,val);
}

void freeGrid(grid *g)
{	
    	for (int i=0; i<g->height; i++)
        	free(g->values[i]);
        free(g->values);
}

int calculVoisins(grid g,int x,int y)
{
	int nbVoisins=0;
	for(int b=0;b<3;b++)   
		for(int n=0;n<3;n++)
			if(x-1+b>=0 && y-1+n>0 && x-1+b<g.width &&y-1+n<g.height) //Vérifie si le voisin a un indice valide dans la grille
				if(b!=1 || n!=1)				    //Ne pas compter la cellule elle même dans ses voisins 
					if(g.values[x-1+b][y-1+n]==vivant)
						nbVoisins++;
	return nbVoisins;
}

void appliquerConway(grid *cells,grid *futureCells,int x,int y,int nbVoisins)
{
	if(cells->values[x][y]==vivant)
		if(nbVoisins==2||nbVoisins==3)
			futureCells->values[x][y]=vivant;
		else if(nbVoisins>3)
			futureCells->values[x][y]=mort;
		else
			futureCells->values[x][y]=mort;
	else if(cells->values[x][y]==mort && nbVoisins==3)
		futureCells->values[x][y]=vivant;
	else
		futureCells->values[x][y]=mort;
}

void appliquerThompson(grid *cells,grid *futureCells,int x,int y,int nbVoisins)
{
	if(cells->values[x][y]==vivant)
		if(nbVoisins==3||nbVoisins==4||nbVoisins==6||nbVoisins==7||nbVoisins==8)
			futureCells->values[x][y]=vivant;
		else
			futureCells->values[x][y]=mort;
	else
		if(nbVoisins==3||nbVoisins==6||nbVoisins==7||nbVoisins==8)
			futureCells->values[x][y]=vivant;
		else
			futureCells->values[x][y]=mort;
}

void update()
{
	char nbVoisins;
	grid futureCells={g->cells.width,g->cells.height};
	initGrid(&futureCells,0);
	
	for(int x=0;x<g->cells.width;x++)
		for(int y=0;y<g->cells.height;y++)
		{
			nbVoisins=calculVoisins(g->cells,x,y);
			if(g->variant==conway)
				appliquerConway(&(g->cells),&futureCells,x,y,nbVoisins);
			else
				appliquerThompson(&(g->cells),&futureCells,x,y,nbVoisins);
		}
	copyGrid(&(g->cells),&futureCells);
	g->generation++;
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

		setGrid(&g->cells,0);

		while((fscanf(fichier,"%d,%d",&x,&y)!=EOF))		
			g->cells.values[x+g->cells.width/2][y+g->cells.height/2]=vivant;
		draw();
		fclose(fichier);
	}
}

void saveFile(const char *filename, Widget *label)
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
		for(int x=0;x<g->cells.width;x++)
			for(int y=0;y<g->cells.height;y++)
				if(g->cells.values[x][y])
					fprintf(fichier,"%d,%d\n",x-g->cells.width/2,y-g->cells.height/2);
					//centrer les coordonnées (milieu de grille = 0,0)
		fclose(fichier);
	}
}
