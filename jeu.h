#pragma once

enum etat {mort,vivant};

enum mode {conway,thompson};

typedef struct {
	int width;
	int height;
	char **values;
}grid;

typedef struct {
	char variant;
	char grid;
	char remove_timeout;
	int timeout;
	int generation;
	grid cells;	
}game;

game *g;

extern void drawGrid();

extern void draw();

extern void copyGrid(grid *a, grid *b);

extern void setGrid(grid *g,char val);

extern void initGrid(grid *g,char val);

extern void freeGrid(grid *g);

extern int calculVoisins(grid g,int x,int y);

extern void appliquerConway(grid *cells,grid *futureCells,int x,int y,int nbVoisins);

extern void appliquerThompson(grid *cells,grid *futureCells,int x,int y,int nbVoisins);

extern void update();

extern void chargerFichier(const char *filename, Widget *label);

extern void saveFile(const char *filename, Widget *label);
