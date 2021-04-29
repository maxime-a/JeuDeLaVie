/*			rappels.c
 *
 * Contient les procédures de rappels des éléments de l'interface graphique
 *
 */

#include<stdlib.h>
#include<stdio.h>
#include"libsx.h"
#include"grille.h"
#include"jeu.h"

#include"rappels.h"

/*			quitterb
 *
 * Rôle: procédure de rappel du bouton quitter, désalloue la mémoire et quitte si l'utilisateur est sûr de son choix 
 * Antécédents: le widget représentant le bouton quitter, data (inutile mais nécessaire)
 *
 */
void quitterb(Widget w, void *data)
{
	if(GetYesNo("Etes vous sur de vouloir quitter ?"))
	{
		libererGrille(&j->cellules);
		free(j);
		exit(0);
	}
}

/*			RaZb
 *
 * Rôle: procédure de rappel du bouton RaZ, remet à zéro l'automate si l'utilisateur est sûr de son choix 
 * Antécédents: le widget représentant le bouton RaZ, label représentant le label affichant le numero de génération
 *
 */
void RaZb(Widget w, void *label)
{
	if(GetYesNo("Etes vous sur de vouloir reinitialiser le jeu ?"))
	{
		ClearDrawArea();				//éffacer l'affichage
		if(j->activerQuadrillage)				
			dessinerQuadrillage();
		initialiserGrille(&j->cellules,0);		//faire mourir toutes les cellules
	
		j->nombreGeneration=0;
		SetLabel(label,"Generation numero :    0 ");
	}
}

/*			button_up
 *
 * Rôle: procédure de rappel du clic dans la zone de dessin, fait naitre ou mourir une cellule en fonction du bouton relaché et de l'emplacement 
 * Antécédents: le widget représentant la zone de dessin, le bouton relaché, ses coordonnées dans la zone, data(inutile mais nécessaire)
 *
 */
void button_up(Widget w, int which_button, int x, int y, void *data)
{
	if(which_button==1)
	{
		if(x/10<j->cellules.largeur && y/10<j->cellules.hauteur)	//eviter de dessiner sur des indices interdits hors de la grille lors de l'agrandissement de la fenêtre
		{
			DrawFilledBox(x/10*10, y/10*10, 10, 10); 		//dessiner un carré aux coordonnées arrondies à la dizaine pour respecter le pas (10pixel) d'une cellule sur la grille  
			j->cellules.valeurs[x/10][y/10]=vivant;		//mettre à jour la cellule correspondante
		}
	}  
	else
	{ 
	  	j->cellules.valeurs[x/10][y/10]=mort;
		dessiner();
	}
}

/*			redessiner
 *
 * Rôle: procédure de rappel de la zone de dessin, sur un redimmensionnement de fenêtre ou recouvrement redessine l'état actuel
 * Antécédents: le widget représentant la zone de dessin, la taille de la zone de dessin et data (les 3 inutiles mais nécessaires) 
 *
 */
void redessiner(Widget w, int largeur, int hauteur, void *data)
{
	dessiner();	
}

/*			changerDelai
 *
 * Rôle: procédure de rappel du slider, change la période d'animation 
 * Antécédents: le widget représentant le slider, la valeur de sa position, label représentant l'affichage de la période
 *
 */
void changerDelai(Widget w, float val, void *label)
{
  j->delai = (int)val*10+10;					//mise à l'échelle et offset pour éviter une période nulle
  char s[22];
  sprintf(s,"Periode : %.2fs      ",(float)j->delai/1000);
  SetLabel(label,s);
  
}

/*			tic
 *
 * Rôle: procédure appelée à chaque fin de période, passe au prochaine état de l'automate 
 * Antécédents: label représentant le label affichant le numero de génération
 *
 */
void tic(void *label)
{
	calculerProchaineGeneration(j);
	
	char s[40];
	sprintf(s,"Generation numero : %4d",j->nombreGeneration);
	SetLabel(label,s);
	 
	dessiner();
	
	if (j->desactiverDelai == FALSE)
    		AddTimeOut(j->delai, tic, label);
}

/*			animerb
 *
 * Rôle: procédure de rappel du bouton animer, active ou désactive l'animation 
 * Antécédents: label pointeur sur le widget label affichant le numero de génération
 *
 */
void animerb(Widget w, void *label)
{
  if (GetToggleState(w))
   {
     j->desactiverDelai = FALSE;
     SetLabel(w, "Stopper");
     AddTimeOut(j->delai, tic, label); 
   }
  else
   {
     j->desactiverDelai = TRUE;
     SetLabel(w, "  Animer  ");
   }
}

/*			chargerOuSauvegarder
 *
 * Rôle: procédure de rappel de la zone texte sur l'appui touche entrer, charge ou sauvegarde le fichier après confirmation de l'utilisateur 
 * Antécédents: w le widget de la zone texte, string un pointeur sur la chaine de caractères représentant le nom de fichier, data un pointeur sur le widget de la zone texte
 *
 */
void chargerOuSauvegarder(Widget w, char *string, void *data)
{
	char nomFichier[100];
  	sprintf(nomFichier,"sauvegarde_etat/%s",string);
  	
  	int choix = GetTriState("Appuyez sur Yes pour charger un nouvel etat avec ce fichier\nAppuyez sur No pour sauvegarder l'etat actuel dans ce fichier\nAppuyez sur Cancel pour annuler");
  	
	if(choix==TRUE)
		chargerFichier(nomFichier,data);
	else if(choix==FALSE)
		sauvegarderFichier(nomFichier,data);
}

/*			chargerb
 *
 * Rôle: procédure de rappel du bouton charger, charge le fichier après confirmation de l'utilisateur 
 * Antécédents: w le widget du bouton, data un pointeur sur le widget de la zone texte
 *
 */
void chargerb(Widget w, void *data)
{
	char *string=GetStringEntry(data); 
	
	char nomFichier[100];
  	sprintf(nomFichier,"sauvegarde_etat/%s",string);
  	
	if(GetYesNo("Etes vous sur de vouloir charger un nouvel etat avec ce fichier ?"))
		chargerFichier(nomFichier,data);
}

/*			sauvegarderb
 *
 * Rôle: procédure de rappel du bouton sauvegarder, sauvegarde le fichier après confirmation de l'utilisateur 
 * Antécédents: w le widget du bouton, data un pointeur sur le widget de la zone texte
 *
 */
void sauvegarderb(Widget w, void *data)
{
	char *string=GetStringEntry(data); 
	
	char nomFichier[100];
  	sprintf(nomFichier,"sauvegarde_etat/%s",string);
	
	if(GetYesNo("Etes vous sur de vouloir sauvegarder un nouvel etat avec ce nom de fichier ?"))
		sauvegarderFichier(nomFichier,data);
}

/*			modeb
 *
 * Rôle: procédure de rappel du bouton mode, permute la variante de calcul 
 * Antécédents: w le widget du bouton, data (inutile mais nécessaire)
 *
 */
void modeb(Widget w, void *data)
{
	if(GetToggleState(w))
	{
		j->variante=thompson;
		SetLabel(w,"Thompson");
	}
	else
	{
		j->variante=conway;
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
 * Antécédents: w le widget du bouton, data (inutile mais nécessaire)
 *
 */
void Quadrillageb(Widget w, void *data)
{
	if(GetToggleState(w))
	{
		j->activerQuadrillage=TRUE;
		dessinerQuadrillage();
	}
	else
	{	
		j->activerQuadrillage=FALSE;
		dessiner();
	}
}
