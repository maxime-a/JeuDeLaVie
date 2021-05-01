/*			main.c
 *
 * Contient les fonctions permettant l'affichage de l'interface graphique de l'initialisation du jeu
 * et la fonction main 
 *
 */

#include<stdlib.h>
#include<string.h>
#include"libsx.h"
#include"jeu.h"
#include"rappels.h"

#define TAILLE 50
#define HAUTEURMIN 15
#define LARGEURMIN 1

/*			initialiserDonnees
 *
 * Rôle: initialise le jeu  
 * Antécédents: argc le nombre d'arguments et argv les arguments lors de l'appel du programme
 *
 */
donnee *initialiserDonnees(int argc, char *argv[])
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
	
	donnee *d=malloc(sizeof(donnee));
	
	d->j=j;
	
	return d;
}

/*			initialiserAffichage
 *
 * Rôle: créer et met en forme les widgets dans la fenêtre 
 * Antécédents: argc et argv lors de l'appel du programme
 *
 */
int initialiserAffichage(int argc, char *argv[],donnee *d)
{
	argc = OpenDisplay(argc, argv);						//Permet de donner le nom au programme (notamment)
  	if (argc == FALSE)
    		return EXIT_FAILURE;
    	//donne necessaire
    	// fichier
    	// lgeneration
    	// lPeriode
    	// j 
	
	Widget fichier=MakeStringEntry("Nom du fichier", 200, chargerOuSauvegarder, NULL); 	//Zone d'entrée texte pour le nom des fichiers
	d->widgetFichier=fichier;
	Widget bQuitter=MakeButton("Quitter", quitterb, d);
	Widget bCharger=MakeButton("Charger", chargerb, d);
	Widget bSauvegarder=MakeButton("Sauvegarder", sauvegarderb, d);
	Widget lGeneration=MakeLabel("Generation numero :    0 ");
	d->labelGeneration=lGeneration;
	Widget bRaZ=MakeButton("RaZ", RaZb, d);
	Widget lPeriode=MakeLabel("Periode : 0.5s      ");
	d->labelPeriode=lPeriode;
	Widget bAnimer=MakeToggle("  Animer  ", FALSE, NULL, animerb, d);
	Widget slider=MakeHorizScrollbar(400,changerDelai,d);
	Widget jeu=MakeDrawArea(d->j->cellules.largeur*10,d->j->cellules.hauteur*10, redessiner, d);			//Zone de dessin du jeu
	Widget lMode=MakeLabel("Variante de calcul :");
	Widget bMode=MakeToggle("Conway  ", FALSE, NULL, modeb, d); 
	Widget bAide=MakeButton("Aide",aideb,NULL);
	Widget bQuadrillage=MakeToggle("Afficher quadrillage",TRUE,NULL,Quadrillageb,d);
		
	SetButtonUpCB(jeu, button_up); 						//Rappel lors d'un clic dans la zone
	
	SetScrollbar(slider, 50.0, MAXPERIOD, MINPERIOD);				//Initalisation position à 0.5s par défaut
	
	//Première ligne
	SetWidgetPos(bCharger,PLACE_RIGHT,fichier,NO_CARE,NULL);
	SetWidgetPos(bSauvegarder,PLACE_RIGHT,bCharger,NO_CARE,NULL);
	SetWidgetPos(bRaZ,PLACE_RIGHT,bSauvegarder,NO_CARE,NULL);
	
	//Seconde ligne
	SetWidgetPos(lMode,PLACE_UNDER,fichier,NO_CARE,NULL);
	SetWidgetPos(bMode,PLACE_UNDER,fichier,PLACE_RIGHT,lMode);
	
	//Troisième ligne
	SetWidgetPos(bQuadrillage,PLACE_UNDER,lMode,NO_CARE,NULL);
	
	//Quatrième ligne (zone de dessin)
	SetWidgetPos(bAnimer,PLACE_UNDER,bQuadrillage,NO_CARE,NULL);
	SetWidgetPos(slider,PLACE_UNDER,bQuadrillage,PLACE_RIGHT,bAnimer);
	SetWidgetPos(jeu,PLACE_RIGHT,slider,NO_CARE,NULL);
	
	//Cinquième ligne
	SetWidgetPos(lPeriode,PLACE_UNDER,slider,NO_CARE,NULL);
	
	//Sixième ligne
	SetWidgetPos(lGeneration,PLACE_UNDER,lPeriode,NO_CARE,NULL);
	
	//Bas
	SetWidgetPos(bQuitter, PLACE_UNDER, jeu, NO_CARE, NULL);
	SetWidgetPos(bAide, PLACE_UNDER, jeu, PLACE_RIGHT, bQuitter);
	
	return argc;
}


int main(int argc, char *argv[])
{
	donnee *d;
	if((d=initialiserDonnees(argc,argv))==NULL)
		return EXIT_FAILURE;
		
	if(!initialiserAffichage(argc,argv,d))
		return EXIT_FAILURE;	
	
	ShowDisplay();
	MainLoop();
	
	return EXIT_SUCCESS;
}
