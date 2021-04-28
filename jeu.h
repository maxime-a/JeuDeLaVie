#pragma once

enum etat {mort,vivant};

enum mode {conway,thompson};

typedef struct {
	int largeur;
	int hauteur;
	char **valeurs;
}grille;

typedef struct {
	char variante;
	char activerGrille;
	char desactiverDelai;
	int delai;
	int nombreGeneration;
	grille cellules;	
}jeu;

jeu *j;

extern void dessinerGrille();

extern void dessiner();

extern void copierGrille(grille *a, grille *b);

extern void initialiserGrille(grille *g,char val);

extern void creerGrille(grille *g,char val);

extern void libererGrille(grille *g);

extern int calculerVoisins(grille g,int x,int y);

extern void appliquerConway(grille *cellules,grille *futurecellules,int x,int y,int nbVoisins);

extern void appliquerThompson(grille *cellules,grille *futurecellules,int x,int y,int nbVoisins);

extern void calculerProchaineGeneration();

extern void chargerFichier(const char *filename, Widget *label);

extern void sauvegarderFichier(const char *filename, Widget *label);
