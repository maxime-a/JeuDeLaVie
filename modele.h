/*			modele.h
 *
 * Contient les prototypes des fonctions et procédures permettant le déroulement du jeu de la vie.
 *
 */
 
#pragma once

/*			calculerVoisins
 *
 * Rôle: calcul le nombre de voisins d'une cellule
 * Antécédents: g un pointeur sur grille et x,y des entiers pour les coordonnées de la cellule dans cette grille
 */
extern int calculerVoisins(grille g,int x,int y);

/*			appliquerConway
 *
 * Rôle: calcul selon la règle de J.Conway si une cellule nait, survit ou meurt
 * Antécédents: val l'état de la cellule, nbVoisins le nombre de voisins de cette cellules
 */
extern char appliquerConway(char val,int nbVoisins);

/*			appliquerThompson
 *
 * Rôle: calcul selon la règle Day&Night de Thompson si une cellule nait, survit ou meurt
 * Antécédents: val l'état de la cellule, nbVoisins le nombre de voisins de cette cellules
 */
extern char appliquerThompson(char val,int nbVoisins);

/*			calculerProchaineGeneration
 *
 * Rôle: calcul selon la règle en vigueur les prochains états des cellules de l'automate
 * Antécédent: j un pointeur sur jeu
 * 
 */
extern void calculerProchaineGeneration(donnees *d);
