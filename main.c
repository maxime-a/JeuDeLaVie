//gcc -Wall -o JeuDeLaVie JeuDeLaVie.c rappels.o jeu.o -lsx

#include<stdlib.h>
#include"libsx.h"
#include"jeu.h"
#include"rappels.h"

#define TAILLE 50

int initData()
{
	g=malloc(sizeof(game));
	
	if(g==NULL)		//Si problème d'allocation 
		return EXIT_FAILURE;
	
	g->cells.width=TAILLE;
	g->cells.height=TAILLE;
	g->variant=conway;
	g->remove_timeout=FALSE;
	g->timeout=500;
	g->grid=1;
	initGrid(&(g->cells),0);
	
	return EXIT_SUCCESS;
}

int initDisplay(int argc, char *argv[])
{
	argc = OpenDisplay(argc, argv);			//Permet de donner le nom au programme 
  	if (argc == FALSE)
    		return argc;
	
	Widget fichier=MakeStringEntry("File name", 200, load, NULL); 
	Widget bquit=MakeButton("Quit", quit, NULL);
	Widget bload=MakeButton("Load", loadb, fichier);
	Widget bsave=MakeButton("Save", saveb, fichier);
	Widget bclear=MakeButton("RAZ", clear, &g->cells);
	Widget myLabel=MakeLabel("Generation numero :     ");
	Widget labelPeriod=MakeLabel("Periode : 0.5s      ");
	Widget banime=MakeToggle("  Animate  ", FALSE, NULL, anim, myLabel);
	Widget slider=MakeHorizScrollbar(400,set_timeout_val,labelPeriod);
	Widget jeu=MakeDrawArea(TAILLE*10,TAILLE*10, redraw, g);
	Widget lmod=MakeLabel("Computation mode :");
	Widget bmod=MakeToggle("Conway  ", FALSE, NULL, modb, NULL); 
	Widget bhelp=MakeButton("Help",helpb,NULL);
	Widget bgrid=MakeToggle("Turn grid off",TRUE,NULL,gridb,NULL);
		
	SetButtonUpCB(jeu, button_up); 
	
	SetScrollbar(slider, 50.0, MAXPERIOD, MINPERIOD);
	
	//First line
	SetWidgetPos(bload,PLACE_RIGHT,fichier,NO_CARE,NULL);
	SetWidgetPos(bsave,PLACE_RIGHT,bload,NO_CARE,NULL);
	SetWidgetPos(bclear,PLACE_RIGHT,bsave,NO_CARE,NULL);
	
	//Second line
	SetWidgetPos(lmod,PLACE_UNDER,fichier,NO_CARE,NULL);
	SetWidgetPos(bmod,PLACE_UNDER,fichier,PLACE_RIGHT,lmod);
	
	//Third
	SetWidgetPos(bgrid,PLACE_UNDER,lmod,NO_CARE,NULL);
	
	//Fourth line
	SetWidgetPos(banime,PLACE_UNDER,bgrid,NO_CARE,NULL);
	SetWidgetPos(slider,PLACE_UNDER,bgrid,PLACE_RIGHT,banime);
	
	//Fifth line
	SetWidgetPos(labelPeriod,PLACE_UNDER,slider,NO_CARE,NULL);
	
	//Sixth line
	SetWidgetPos(myLabel,PLACE_UNDER,labelPeriod,NO_CARE,NULL);
	
	//Seventh line (draw area)
	SetWidgetPos(jeu,PLACE_RIGHT,slider,NO_CARE,NULL);
	
	//Bottom line
	SetWidgetPos(bquit, PLACE_UNDER, jeu, NO_CARE, NULL);
	SetWidgetPos(bhelp, PLACE_UNDER, jeu, PLACE_RIGHT, bquit);
	
	return argc;
}

int main(int argc, char *argv[])
{
	if(initData()==EXIT_FAILURE)
		return EXIT_FAILURE;
		
	if(!initDisplay(argc,argv))
		return EXIT_FAILURE;	
	
	ShowDisplay();
	MainLoop();
	
	return EXIT_SUCCESS;
}
