/*			rappels.c
 *
 * Contient les procédures de rappels des éléments de l'interface graphique
 *
 */

#include<stdlib.h>
#include<stdio.h>
#include"libsx.h"
#include"donnees.h"
#include"vue.h"

#include"rappels.h"

/*			quitterb
 *
 * Rôle: procédure de rappel du bouton quitter, désalloue la mémoire et quitte si l'utilisateur est sûr de son choix 
 * Antécédents: le widget représentant le bouton quitter,  data une structure donnees
 *
 */
void quitterb(Widget w, void *data)
{
	donnees *d = (donnees *)data; 
	if(GetYesNo("Etes vous sur de vouloir quitter ?"))
	{
		libererDonnees(d);
		exit(0);
	}
}

/*			RaZb
 *
 * Rôle: procédure de rappel du bouton RaZ, remet à zéro l'automate si l'utilisateur est sûr de son choix 
 * Antécédents: le widget représentant le bouton RaZ, data une structure donnees 
 *
 */
void RaZb(Widget w, void *data)
{
	donnees *d = (donnees *)data;                           //cast pour bien spécifier que c'est un pointeur sur donnees et pas void.
	if(GetYesNo("Etes vous sur de vouloir reinitialiser le jeu ?"))
	{
		ClearDrawArea();				//éffacer l'affichage
		if(getQuadrillage(d))				
			dessinerQuadrillage(d);
		reinitialiserDonnees(d);
		SetLabel(getLabelGeneration(d),"Generation numero :    0 ");
	}
}

/*			button_up
 *
 * Rôle: procédure de rappel du clic dans la zone de dessin, fait naitre ou mourir une cellule en fonction du bouton relaché et de l'emplacement 
 * Antécédents: le widget représentant la zone de dessin, le bouton relaché, ses coordonnées dans la zone, data une structure donnees 
 *
 */
void button_up(Widget w, int which_button, int x, int y, void *data)
{
	donnees *d = (donnees *)data;                         //cast pour bien spécifier que c'est un pointeur sur donnees et pas void.
	if(which_button==1)
	{
		if(x/10<getLargeur(d) && y/10<getHauteur(d))	//eviter de dessiner sur des indices interdits hors de la grille lors de l'agrandissement de la fenêtre
		{
			DrawFilledBox(x/10*10, y/10*10, 10, 10); 		//dessiner un carré aux coordonnées arrondies à la dizaine pour respecter le pas (10pixel) d'une cellule sur la grille  
			setValeur(d,x/10,y/10,vivant);			//mettre à jour la cellule correspondante
		}
	}  
	else
	{ 
	  	setValeur(d,x/10,y/10,mort);
		dessiner(d);
	}
}

/*			redessiner
 *
 * Rôle: procédure de rappel de la zone de dessin, sur un redimmensionnement de fenêtre ou recouvrement redessine l'état actuel
 * Antécédents: le widget représentant la zone de dessin, la taille de la zone de dessin et data une structure donnees 
 *
 */
void redessiner(Widget w, int largeur, int hauteur, void *data)
{
	donnees *d = (donnees *)data;                           //cast pour bien spécifier que c'est un pointeur sur donnees et pas void.
	dessiner(d);	
}

/*			changerDelai
 *
 * Rôle: procédure de rappel du slider, change la période d'animation 
 * Antécédents: le widget représentant le slider, la valeur de sa position, data une structure donnees 
 *
 */
void changerDelai(Widget w, float val, void *data)
{
	donnees *d = (donnees *)data;                           //cast pour bien spécifier que c'est un pointeur sur donnees et pas void.
  	setDelai(d,(int)val*10+10);				  //mise à l'échelle et offset pour éviter une période nulle
  	char s[22];
  	sprintf(s,"Periode : %.2fs      ",(float)getDelai(d)/1000);
  	SetLabel(getLabelPeriode(d),s);
  
}

/*			tic
 *
 * Rôle: procédure appelée à chaque fin de période, passe au prochaine état de l'automate 
 * Antécédents: data une structure donnees 
 *
 */
void tic(void *data)
{
	donnees *d = (donnees *)data;                           //cast pour bien spécifier que c'est un pointeur sur donnees et pas void.
	
	calculerProchaineGeneration(d);
	
	char s[40];
	sprintf(s,"Generation numero : %4d",getNombreGeneration(d));
	SetLabel(getLabelGeneration(d),s);
	 
	dessiner(d);
	
	if (getDesactiverDelai(d) == FALSE)
    		AddTimeOut(getDelai(d), tic, d);
}

/*			animerb
 *
 * Rôle: procédure de rappel du bouton animer, active ou désactive l'animation 
 * Antécédents: data une structure donnees 
 *
 */
void animerb(Widget w, void *data)
{
	donnees *d = (donnees *)data;                           //cast pour bien spécifier que c'est un pointeur sur donnees et pas void.

  	if (GetToggleState(w))
   	{
     		setDesactiverDelai(d,FALSE);
     		SetLabel(w, "Stopper");
     		AddTimeOut(getDelai(d), tic, d); 
   	}
  	else
   	{
     		setDesactiverDelai(d,TRUE);
     		SetLabel(w, "  Animer  ");
   	}
}

/*			chargerOuSauvegarder
 *
 * Rôle: procédure de rappel de la zone texte sur l'appui touche entrer, charge ou sauvegarde le fichier après confirmation de l'utilisateur 
 * Antécédents: w le widget de la zone texte, string un pointeur sur la chaine de caractères représentant le nom de fichier, data une structure donnees 
 *
 */
void chargerOuSauvegarder(Widget w, char *string, void *data)
{
	donnees *d = (donnees *)data;                           //cast pour bien spécifier que c'est un pointeur sur donnees et pas void.
	
	char nomFichier[100];
  	sprintf(nomFichier,"sauvegarde_etat/%s",string);
  	
  	int choix = GetTriState("Appuyez sur Yes pour charger un nouvel etat avec ce fichier\nAppuyez sur No pour sauvegarder l'etat actuel dans ce fichier\nAppuyez sur Cancel pour annuler");
  	
	if(choix==TRUE)
		chargerFichier(nomFichier,d);
	else if(choix==FALSE)
		sauvegarderFichier(nomFichier,d);
}

/*			choixFichiersb
 *
 * Rôle: procédure de rappel du bouton choisir un fichier, permet de récupérer le chemin d'accès et le nom du fichier 
 * entré par l'utilisateur  
 * Antécédents: w le widget du bouton, data une structure donnees 
 *
 */
void choixFichiersb(Widget w,void *data)
{
	donnees *d = (donnees *)data;                      //cast pour bien spécifier que c'est un pointeur sur donnees et pas void.

	SetFreqFilter("*.jdlv"); 
	char *nomFichier=GetFile("/!\\ Un clic dans l'aboresence peut provoquer une erreur\nEcrire sinon le nom dans la zone texte de cette fenetre\nOu encore depuis la fenetre principale avec le chemin d'acces\nSi le fichier n'existe pas il sera cree lors de l'appui sur le bouton sauvegarder", "./sauvegarde_etat", NULL, NULL) ;
	SetStringEntry(getWidgetFichier(d),nomFichier);
}

/*			chargerb
 *
 * Rôle: procédure de rappel du bouton charger, charge le fichier après confirmation de l'utilisateur 
 * Antécédents: w le widget du bouton, data une structure donnees 
 *
 *
 */
void chargerb(Widget w, void *data)
{
	donnees *d = (donnees *)data;                           //cast pour bien spécifier que c'est un pointeur sur donnees et pas void.
	
	char *nomFichier=GetStringEntry(getWidgetFichier(d)); 
  	
	if(GetYesNo("Etes vous sur de vouloir charger un nouvel etat avec ce fichier ?"))	
		chargerFichier(nomFichier,d);

}

/*			sauvegarderb
 *
 * Rôle: procédure de rappel du bouton sauvegarder, sauvegarde le fichier après confirmation de l'utilisateur 
 * Antécédents: w le widget du bouton, data une structure donnees 
 *
 */
void sauvegarderb(Widget w, void *data)
{
	donnees *d = (donnees *)data;                           //cast pour bien spécifier que c'est un pointeur sur donnees et pas void.
	
	char *nomFichier=GetStringEntry(getWidgetFichier(d)); 
	
	if(GetYesNo("Etes vous sur de vouloir sauvegarder un nouvel etat avec ce nom de fichier ?"))
		sauvegarderFichier(nomFichier,d);
}

/*			modeb
 *
 * Rôle: procédure de rappel du bouton mode, permute la variante de calcul 
 * Antécédents: w le widget du bouton, data une structure donnees 
 *
 */
void modeb(Widget w, void *data)
{
	donnees *d = (donnees *)data;                           //cast pour bien spécifier que c'est un pointeur sur donnees et pas void.
	
	if(GetToggleState(w))
	{
		setVariante(d,thompson);
		SetLabel(w,"Thompson");
	}
	else
	{
		setVariante(d,conway);
		SetLabel(w,"Conway");
	}
}

/*			aideb
 *
 * Rôle: procédure de rappel du bouton aide, affiche une aide sur les fonctionnalités du programme
 * Antécédents: w le widget du bouton, data (inutile mais nécessaire)
 *
 */
void aideb(Widget w, void *data)
{
	GetOkay("-Entrez un nom de fichier et appuyez sur les boutons correspondants pour charger ou sauvegarder un etat\n-Appuyez sur le bouton RaZ pour réinitiliser l'automate\n-Utilisez la barre horizontale pour changer la periode d'animation\n-Clic gauche dans la zone d'affichage pour faire naitre une cellule a cet endroit\n-Clic droit dans la zone d'affichage pour faire mourir une cellule a cet endroit");
}

/*			Quadrillageb
 *
 * Rôle: procédure de rappel du bouton grille, permute l'affichage de la grille 
 * Antécédents: w le widget du bouton, data une structure donnees 
 *
 */
void Quadrillageb(Widget w, void *data)
{
	donnees *d = (donnees *)data;                           //cast pour bien spécifier que c'est un pointeur sur donnees et pas void.
	
	if(GetToggleState(w))
	{
		setActiverQuadrillage(d,TRUE);
		dessinerQuadrillage(d);
	}
	else
	{	
		setActiverQuadrillage(d,FALSE);
		dessiner(d);
	}
}
