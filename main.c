//gcc -Wall -o JeuDeLaVie JeuDeLaVie.c rappels.o jeu.o -lsx
//commit test

#include<stdlib.h>
#include"libsx.h"
#include"jeu.h"
#include"rappels.h"

#define TAILLE 50

int initialiserDonnees()
{
	j=malloc(sizeof(jeu));
	
	if(j==NULL)		//Si problème d'allocation 
		return EXIT_FAILURE;
	
	j->cellules.largeur=TAILLE;
	j->cellules.hauteur=TAILLE;
	j->variante=conway;
	j->desactiverDelai=TRUE;
	j->delai=500;
	j->activerGrille=TRUE;
	j->nombreGeneration=0;
	creerGrille(&(j->cellules),0);
	
	return EXIT_SUCCESS;
}

int initialiserAffichage(int argc, char *argv[])
{
	argc = OpenDisplay(argc, argv);			//Permet de donner le nom au programme 
  	if (argc == FALSE)
    		return argc;
	
	Widget fichier=MakeStringEntry("Nom du fichier", 200, charger, NULL); 
	Widget bQuitter=MakeButton("Quitter", quitterb, NULL);
	Widget bCharger=MakeButton("Charger", chargerb, fichier);
	Widget bSauvegarder=MakeButton("Sauvegarder", sauvegarderb, fichier);
	Widget lGeneration=MakeLabel("Generation numero :     ");
	Widget bRaZ=MakeButton("RaZ", RaZb, lGeneration);
	Widget lPeriode=MakeLabel("Periode : 0.5s      ");
	Widget bAnimer=MakeToggle("  Animer  ", FALSE, NULL, animerb, lGeneration);
	Widget slider=MakeHorizScrollbar(400,changerDelai,lPeriode);
	Widget jeu=MakeDrawArea(TAILLE*10,TAILLE*10, redessiner, j);
	Widget lMode=MakeLabel("Variante de calcul :");
	Widget bMode=MakeToggle("Conway  ", FALSE, NULL, modeb, NULL); 
	Widget bAide=MakeButton("Aide",aideb,NULL);
	Widget bGrille=MakeToggle("Afficher grille",TRUE,NULL,grilleb,NULL);
		
	SetButtonUpCB(jeu, button_up); 
	
	SetScrollbar(slider, 50.0, MAXPERIOD, MINPERIOD);
	
	//First line
	SetWidgetPos(bCharger,PLACE_RIGHT,fichier,NO_CARE,NULL);
	SetWidgetPos(bSauvegarder,PLACE_RIGHT,bCharger,NO_CARE,NULL);
	SetWidgetPos(bRaZ,PLACE_RIGHT,bSauvegarder,NO_CARE,NULL);
	
	//Second line
	SetWidgetPos(lMode,PLACE_UNDER,fichier,NO_CARE,NULL);
	SetWidgetPos(bMode,PLACE_UNDER,fichier,PLACE_RIGHT,lMode);
	
	//Third
	SetWidgetPos(bGrille,PLACE_UNDER,lMode,NO_CARE,NULL);
	
	//Fourth line
	SetWidgetPos(bAnimer,PLACE_UNDER,bGrille,NO_CARE,NULL);
	SetWidgetPos(slider,PLACE_UNDER,bGrille,PLACE_RIGHT,bAnimer);
	
	//Fifth line
	SetWidgetPos(lPeriode,PLACE_UNDER,slider,NO_CARE,NULL);
	
	//Sixth line
	SetWidgetPos(lGeneration,PLACE_UNDER,lPeriode,NO_CARE,NULL);
	
	//Seventh line (draw area)
	SetWidgetPos(jeu,PLACE_RIGHT,slider,NO_CARE,NULL);
	
	//Bottom line
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
