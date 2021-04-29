/*			main.c
 *
 * Contient les fonctions permettant l'affichage de l'interface graphique de l'initialisation du jeu
 * et la fonction main 
 *
 */

#include<stdlib.h>
#include"libsx.h"
#include"jeu.h"
#include"rappels.h"

#define TAILLE 50

/*			initialiserDonnees
 *
 * Rôle: initialise le jeu  
 * Antécédents: aucuns , le jeu est une variable globale
 *
 */
int initialiserDonnees()
{
	j=malloc(sizeof(jeu));
	
	if(j==NULL)				//Si problème d'allocation 
		return EXIT_FAILURE;
	
	j->cellules.largeur=TAILLE;
	j->cellules.hauteur=TAILLE;
	j->variante=conway;
	j->desactiverDelai=TRUE;
	j->delai=500;				//0.5s par défaut
	j->activerQuadrillage=TRUE;
	j->nombreGeneration=0;
	creerGrille(&(j->cellules),0);
	
	return EXIT_SUCCESS;
}

/*			initialiserAffichage
 *
 * Rôle: créer et met en forme les widgets dans la fenêtre 
 * Antécédents: argc et argv lors de l'appel du programme
 *
 */
int initialiserAffichage(int argc, char *argv[])
{
	argc = OpenDisplay(argc, argv);						//Permet de donner le nom au programme (notamment)
  	if (argc == FALSE)
    		return EXIT_FAILURE;
	
	Widget fichier=MakeStringEntry("Nom du fichier", 200, chargerOuSauvegarder, NULL); 	//Zone d'entrée texte pour le nom des fichiers
	Widget bQuitter=MakeButton("Quitter", quitterb, NULL);
	Widget bCharger=MakeButton("Charger", chargerb, fichier);
	Widget bSauvegarder=MakeButton("Sauvegarder", sauvegarderb, fichier);
	Widget lGeneration=MakeLabel("Generation numero :    0 ");
	Widget bRaZ=MakeButton("RaZ", RaZb, lGeneration);
	Widget lPeriode=MakeLabel("Periode : 0.5s      ");
	Widget bAnimer=MakeToggle("  Animer  ", FALSE, NULL, animerb, lGeneration);
	Widget slider=MakeHorizScrollbar(400,changerDelai,lPeriode);
	Widget jeu=MakeDrawArea(TAILLE*10,TAILLE*10, redessiner, j);			//Zone de dessin du jeu
	Widget lMode=MakeLabel("Variante de calcul :");
	Widget bMode=MakeToggle("Conway  ", FALSE, NULL, modeb, NULL); 
	Widget bAide=MakeButton("Aide",aideb,NULL);
	Widget bQuadrillage=MakeToggle("Afficher quadrillage",TRUE,NULL,Quadrillageb,NULL);
		
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
	if(initialiserDonnees()==EXIT_FAILURE)
		return EXIT_FAILURE;
		
	if(!initialiserAffichage(argc,argv))
		return EXIT_FAILURE;	
	
	ShowDisplay();
	MainLoop();
	
	return EXIT_SUCCESS;
}
