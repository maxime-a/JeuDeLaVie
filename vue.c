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
	
	Widget fichier=MakeStringEntry("./nomDossier/nomFichier.jdlv", 300, chargerOuSauvegarder, NULL); 	//Zone d'entrée texte pour le nom des fichiers
	d->widgetFichier=fichier;
	Widget bQuitter=MakeButton("Quitter", quitterb, d);
	Widget bCharger=MakeButton("Charger", chargerb, d);
	Widget bSauvegarder=MakeButton("Sauvegarder", sauvegarderb, d);
	Widget bChoixFichiers=MakeButton("Choisir un fichier", choixFichiersb,d);
	Widget lGeneration=MakeLabel("Generation numero :    0 ");
	d->labelGeneration=lGeneration;
	Widget bRaZ=MakeButton("Remise a zero", RaZb, d);
	Widget lPeriode=MakeLabel("Periode : 0.5s      ");
	d->labelPeriode=lPeriode;
	Widget bAnimer=MakeToggle("  Animer  ", FALSE, NULL, animerb, d);
	Widget slider=MakeHorizScrollbar(300,changerDelai,d);
	Widget jeu=MakeDrawArea(getLargeur(d)*10,getHauteur(d)*10, redessiner, d);			//Zone de dessin du jeu
	Widget lMode=MakeLabel("Variante de calcul :");
	Widget bMode=MakeToggle("Conway  ", FALSE, NULL, modeb, d); 
	Widget bAide=MakeButton("Aide",aideb,NULL);
	Widget bQuadrillage=MakeToggle("Afficher quadrillage",TRUE,NULL,Quadrillageb,d);
		
	SetButtonUpCB(jeu, button_up); 						//Rappel lors d'un clic dans la zone
	
	SetScrollbar(slider, 50.0, MAXPERIOD, MINPERIOD);				//Initalisation position à 0.5s par défaut
	
	//En tête
	
	//Première ligne
	SetWidgetPos(bChoixFichiers,PLACE_UNDER,fichier,NO_CARE,NULL);
	SetWidgetPos(bCharger,PLACE_RIGHT,bChoixFichiers,PLACE_UNDER,fichier);
	SetWidgetPos(bSauvegarder,PLACE_RIGHT,bCharger,PLACE_UNDER,fichier);
	SetWidgetPos(jeu,PLACE_RIGHT,fichier,NO_CARE,NULL);
	
	//Seconde ligne
	SetWidgetPos(lMode,PLACE_UNDER,bChoixFichiers,NO_CARE,NULL);
	SetWidgetPos(bMode,PLACE_UNDER,bChoixFichiers,PLACE_RIGHT,lMode);
	
	//Troisième ligne
	SetWidgetPos(bQuadrillage,PLACE_UNDER,lMode,NO_CARE,NULL);
	
	//Quatrième ligne 
	SetWidgetPos(bAnimer,PLACE_UNDER,bQuadrillage,NO_CARE,NULL);
	SetWidgetPos(slider,PLACE_UNDER,bAnimer,NO_CARE,NULL);
	
	//Cinquième ligne
	SetWidgetPos(lPeriode,PLACE_UNDER,slider,NO_CARE,NULL);
	
	//Sixième ligne
	SetWidgetPos(lGeneration,PLACE_UNDER,lPeriode,NO_CARE,NULL);
	
	//septième ligne
	SetWidgetPos(bRaZ,PLACE_UNDER,lGeneration,NO_CARE,NULL);
	
	//Bas
	SetWidgetPos(bQuitter, PLACE_UNDER, jeu, NO_CARE, NULL);
	SetWidgetPos(bAide, PLACE_UNDER, jeu, PLACE_RIGHT, bQuitter);
	
	return argc;
}

/*			dessinerQuadrillage
 *
 * Rôle: dessine un grille avec un pas de 10 pixels dans la zone de dessin
 * Antécédent: d un pointeur sur donnees
 *
 */
void dessinerQuadrillage(donnees *d)
{
	for(int x=1;x<=getLargeur(d);x++)
	{
		DrawLine(x*10,0,x*10,getHauteur(d)*10); 	 //Dessin des barres verticales
		
		for(int y=1;y<=getHauteur(d);y++)
			DrawLine(0,y*10,getLargeur(d)*10,y*10);  //Dessin des barres horizontales
	} 	
}

/*			dessiner
 *
 * Rôle: dessine la grille si activée et les cellules vivantes de l'état actuel
 * Antécédent: j un pointeur sur jeu
 *
 */
void dessiner(donnees *d)
{
	ClearDrawArea(); 
	if(getQuadrillage(d))
		dessinerQuadrillage(d);
		
	for(int x=0;x<getLargeur(d);x++)
	{
		for(int y=0;y<getHauteur(d);y++)
		{
			if(getValeur(d,x,y))
				DrawFilledBox(x*10, y*10, 10, 10); 
		}
	}
}
