/*			main.c
 *
 * Contient les fonctions permettant l'affichage de l'interface graphique de l'initialisation du jeu
 * et la fonction main 
 *
 */

#include<stdlib.h>
#include<string.h>
#include"libsx.h"
#include"donnees.h"
#include"vue.h"

int main(int argc, char *argv[])
{
	donnees *d;
	if((d=initialiserDonnees(argc,argv))==NULL)
		return EXIT_FAILURE;
		
	if(!initialiserAffichage(argc,argv,d))
		return EXIT_FAILURE;	
	
	ShowDisplay();
	MainLoop();
	
	return EXIT_SUCCESS;
}
