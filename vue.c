/*			vue.c
 *
 * Contient la fonction de déclaration et d'assemblage des widgets
 *
 */

#include<stdlib.h>
#include<string.h>
#include"libsx.h"
#include"donnees.h"
#include"rappels.h"
#include"vue.h"

/*			initialiserAffichage
 *
 * Rôle: créer et met en forme les widgets dans la fenêtre 
 * Antécédents: argc et argv lors de l'appel du programme
 *
 */
int initialiserAffichage(int argc, char *argv[],donnees *d)
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
