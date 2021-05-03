/*			rappels.c
 *
 * Contient les procédures de rappels des éléments de l'interface graphique
 *
 */

#include<stdlib.h>
#include<stdio.h>
#include"libsx.h"
#include"donnees.h"
#include"grille.h"

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
		//faire une fonction pour liberer d
		libererGrille(&d->j->cellules);
		free(d->j);
		free(d);
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
		if(d->j->activerQuadrillage)				
			dessinerQuadrillage(d->j);
		initialiserGrille(&d->j->cellules,0);		//faire mourir toutes les cellules
	
		d->j->nombreGeneration=0;
		SetLabel(d->labelGeneration,"Generation numero :    0 ");
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
		if(x/10<d->j->cellules.largeur && y/10<d->j->cellules.hauteur)	//eviter de dessiner sur des indices interdits hors de la grille lors de l'agrandissement de la fenêtre
		{
			DrawFilledBox(x/10*10, y/10*10, 10, 10); 		//dessiner un carré aux coordonnées arrondies à la dizaine pour respecter le pas (10pixel) d'une cellule sur la grille  
			d->j->cellules.valeurs[x/10][y/10]=vivant;		//mettre à jour la cellule correspondante
		}
	}  
	else
	{ 
	  	d->j->cellules.valeurs[x/10][y/10]=mort;
		dessiner(d->j);
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
	dessiner(d->j);	
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
  	d->j->delai = (int)val*10+10;					//mise à l'échelle et offset pour éviter une période nulle
  	char s[22];
  	sprintf(s,"Periode : %.2fs      ",(float)d->j->delai/1000);
  	SetLabel(d->labelPeriode,s);
  
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
	
	calculerProchaineGeneration(d->j);
	
	char s[40];
	sprintf(s,"Generation numero : %4d",d->j->nombreGeneration);
	SetLabel(d->labelGeneration,s);
	 
	dessiner(d->j);
	
	if (d->j->desactiverDelai == FALSE)
    		AddTimeOut(d->j->delai, tic, d);
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
     		d->j->desactiverDelai = FALSE;
     		SetLabel(w, "Stopper");
     		AddTimeOut(d->j->delai, tic, d); 
   	}
  	else
   	{
     		d->j->desactiverDelai = TRUE;
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
		chargerFichier(nomFichier,&d->widgetFichier,d->j);
	else if(choix==FALSE)
		sauvegarderFichier(nomFichier,&d->widgetFichier,d->j);
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

	char *string=GetStringEntry(d->widgetFichier); 
	
	char nomFichier[100];
  	sprintf(nomFichier,"sauvegarde_etat/%s",string);
  	
	if(GetYesNo("Etes vous sur de vouloir charger un nouvel etat avec ce fichier ?"))
		chargerFichier(nomFichier,&d->widgetFichier,d->j);
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
	
	char *string=GetStringEntry(d->widgetFichier); 
	
	char nomFichier[100];
  	sprintf(nomFichier,"sauvegarde_etat/%s",string);
	
	if(GetYesNo("Etes vous sur de vouloir sauvegarder un nouvel etat avec ce nom de fichier ?"))
		sauvegarderFichier(nomFichier,&d->widgetFichier,d->j);
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
		d->j->variante=thompson;
		SetLabel(w,"Thompson");
	}
	else
	{
		d->j->variante=conway;
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
		d->j->activerQuadrillage=TRUE;
		dessinerQuadrillage(d->j);
	}
	else
	{	
		d->j->activerQuadrillage=FALSE;
		dessiner(d->j);
	}
}
