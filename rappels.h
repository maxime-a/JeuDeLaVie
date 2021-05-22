/*			rappels.h
 *
 * Contient les prototypes des procédures de rappels des éléments de l'interface graphique
 *
 */
 
#pragma once

#define MAXPERIOD 99.0
#define MINPERIOD 10.0

/*			quitterb
 *
 * Rôle: procédure de rappel du bouton quitter, désalloue la mémoire et quitte si l'utilisateur est sûr de son choix 
 * Antécédents: le widget représentant le bouton quitter, data (inutile mais nécessaire)
 *
 */
extern void quitterb(Widget w, void *data);

/*			RaZb
 *
 * Rôle: procédure de rappel du bouton RaZ, remet à zéro l'automate si l'utilisateur est sûr de son choix 
 * Antécédents: le widget représentant le bouton RaZ, label représentant le label affichant le numero de génération
 *
 */
extern void RaZb(Widget w, void *label);

/*			button_up
 *
 * Rôle: procédure de rappel du clic dans la zone de dessin, fait naitre ou mourir une cellule en fonction du bouton relaché et de l'emplacement 
 * Antécédents: le widget représentant la zone de dessin, le bouton relaché, ses coordonnées dans la zone, data(inutile mais nécessaire)
 *
 */
extern void button_up(Widget w, int which_button, int x, int y, void *data);

/*			redessiner
 *
 * Rôle: procédure de rappel de la zone de dessin, sur un redimmensionnement de fenêtre ou recouvrement redessine l'état actuel
 * Antécédents: le widget représentant la zone de dessin, la taille de la zone de dessin et data (les 3 inutiles mais nécessaires) 
 *
 */
extern void redessiner(Widget w, int largeur, int hauteur, void *data);

/*			changerDelai
 *
 * Rôle: procédure de rappel du slider, change la période d'animation 
 * Antécédents: le widget représentant le slider, la valeur de sa position, label représentant l'affichage de la période
 *
 */
extern void changerDelai(Widget w, float val, void *label);

/*			tic
 *
 * Rôle: procédure appelée à chaque fin de période, passe au prochaine état de l'automate 
 * Antécédents: label représentant le label affichant le numero de génération
 *
 */
extern void tic(void *label);

/*			animerb
 *
 * Rôle: procédure de rappel du bouton animer, active ou désactive l'animation 
 * Antécédents: label pointeur sur le widget label affichant le numero de génération
 *
 */
extern void animerb(Widget w, void *label);

/*			chargerOuSauvegarder
 *
 * Rôle: procédure de rappel de la zone texte sur l'appui touche entrer, charge ou sauvegarde le fichier après confirmation de l'utilisateur 
 * Antécédents: w le widget de la zone texte, string un pointeur sur la chaine de caractères représentant le nom de fichier, data un pointeur sur le widget de la zone texte
 *
 */
extern void chargerOuSauvegarder(Widget w, char *string, void *data);

/*			choixFichiersb
 *
 * Rôle: procédure de rappel du bouton choisir un fichier, permet de récupérer le chemin d'accès et le nom du fichier 
 * entré par l'utilisateur  
 * Antécédents: w le widget du bouton, data une structure donnees 
 *
 */
extern void choixFichiersb(Widget w,void *data);

/*			chargerb
 *
 * Rôle: procédure de rappel du bouton charger, charge le fichier après confirmation de l'utilisateur 
 * Antécédents: w le widget du bouton, data un pointeur sur le widget de la zone texte
 *
 */
extern void chargerb(Widget w, void *data);

/*			sauvegarderb
 *
 * Rôle: procédure de rappel du bouton sauvegarder, sauvegarde le fichier après confirmation de l'utilisateur 
 * Antécédents: w le widget du bouton, data un pointeur sur le widget de la zone texte
 *
 */
extern void sauvegarderb(Widget w, void *data);

/*			modeb
 *
 * Rôle: procédure de rappel du bouton mode, permute la variante de calcul 
 * Antécédents: w le widget du bouton, data (inutile mais nécessaire)
 *
 */
extern void modeb(Widget w, void *data);

/*			aideb
 *
 * Rôle: procédure de rappel du bouton aide, affiche une aide sur les fonctionnalités du programme
 * Antécédents: w le widget du bouton, data (inutile mais nécessaire)
 *
 */
extern void aideb(Widget w, void *data);

/*			Quadrillageb
 *
 * Rôle: procédure de rappel du bouton quadrillage, permute l'affichage de la grille 
 * Antécédents: w le widget du bouton, data (inutile mais nécessaire)
 *
 */
extern void Quadrillageb(Widget w, void *data);

/*			Couleurb
 *
 * Rôle: procédure de rappel du bouton grille, permute l'affichage des couleurs pour
 * des détails sur l'état des cellules 
 * Antécédents: w le widget du bouton, data une structure donnees 
 *
 */
extern void Couleurb(Widget w, void *data);

