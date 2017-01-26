/*	Module contenant des fonctions aux usages generaux	*/

#ifndef FONCTIONS_H
#define FONCTIONS_H


#include "configuration.h"


void 				empty_buffer										();
																			/*	vidage du buffer de l'entree standard si necessaire	*/

void 				saisir												(char chaine[], int longueur);
																			/*	fonction de saisi "securisee" avec vidage de buffer et remplacement du '\n' par '\0'	*/

int					valeur_absolue										(int nombre);
																			/*	retourne la valeur absolue d'un entier	*/

char				upper_character										(char character);
																			/*	passe un caractere en majuscule si necessaire	*/

void 				recuperer_parametre_commande 						(char saisiePrompt[MAX_LENGTH_PROMPT], int tailleChaineCmd, char parametre[], int tailleParametre);
																			/*	tronque la commande pour extraire le parametre, attention ne prends pas en compte le type de separateur	*/

void 				sauvegarder_fichier									(char labelFichierSauvegarde[MAX_LENGTH_FILES], etatPartie_s etatPartieEnCours);
																			/*	permet de sauvegarder un fichier en binaire dans le repertoire de l'executable	*/

void 				sauvegarder_une_partie 								(etatPartie_s *p_etatPartieEnCours, char saisiePrompt[MAX_LENGTH_PROMPT]);
																			/*	amorce une procedure de sauvegarde binaire, avec controle pour ecraser le fichier	*/

void 				charger_fichier										(char labelFichierSauvegarde[MAX_LENGTH_FILES], etatPartie_s *p_etatPartieEnCours);
																			/*	permet de charger un fichier binaire sur la partie courante et donc de l'ecraser	*/

void 				charger_une_partie									(etatPartie_s *p_etatPartieEnCours, char saisiePrompt[MAX_LENGTH_PROMPT]);
																			/* amorce une procedure de chargement de sauvegarde binaire	*/

Coordonnees_s 		convertir_saisie_en_coordonnees						(char coordonneesAlphaNumerique[TAILLE_COORDONNEES_ALPHA_NUMERIQUE]);
																			/*	converti les coordonnées utilisateur ex:'A0' en coor 'systeme' 'x=0;y=0'	*/

Boolean 			conversion_possible_coordonnees_alpha_numerique 	(char coordonneesAlphaNumerique[TAILLE_COORDONNEES_ALPHA_NUMERIQUE]);
																			/*	verifie que la conversion de coordonnees utilisateur / systeme soit possible	*/

Boolean 			lettre_coordonnee_valide							(char lettreCoordonnee, int borneMaxCoordonnee);
																			/*	verifie que la lettre de la coordonnee utilisateur soit definie sur le plateau	*/

Boolean 			chiffre_coordonnee_valide							(char c_chiffreCoordonnee, int borneMaxCoordonnee);
																			/* verifie que le chiffre de la coordonnee utilisateur soit defini sur le plateau	*/


#endif
