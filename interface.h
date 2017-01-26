/*	Module qui fait le lien avec tous les autres. Se focalise sur l'interaction entre le joueur et la machine ansi que l'affichage	*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include "configuration.h"

extern const char *p_typeCommandePrompt[];	// Contient toutes les commandes realisable pendant une partie


void 						clear_screen								();
																					/*	Efface le contenu affiche sur la console, la console doit supporter les codes ANSI	*/

void 						reset_display_attributes					();
																					/*	Reset les parametres d'affichages de la console, a ceux d'origine	*/

void 						raffraichir_affichage_plateau 				(etatPartie_s etatPartieEnCours);
																					/*	Raffraichi l'integralite des elements, plateau, n° tour, de joueur, bushis...	*/

void						afficher_plateau_de_jeu						();
																					/*	Affiche la structure du plataeu de jeux (vide)	*/

void 						afficher_label_joueur_actif					(etatPartie_s etatPartieEnCours);
																					/*	Affiche le label 'bleu/rouge' du joueur en train de jouer	*/

void 						afficher_numero_tour						(etatPartie_s etatPartieEnCours);
																					/*	Affiche le numero de tour en fonction de la couleur du joueur qui joue	*/

void 						afficher_bushi_sur_curseur					(Coordonnees_s caseCible, char caractere);
																					/*	Permet d'afficher un bushi sur une case precise en fonction des coordonnees.
																						Utilise le positionnement de curseur par code ASCII	*/

void 						afficher_portail_sur_curseur				(Coordonnees_s caseCible, char caractere, AnsiColorsTxt_e colorTxtBushi);
																					/*	Permet d'afficher un portails sur une case precise en fonction des coordonnees.
																						Utilise le positionnement de curseur par code ASCII	*/	

void						afficher_tous_les_bushis 					();
																					/*	Parcours tout le plateau et si la case est occupee, affiche le bushi	*/

void 						afficher_portails							();
																					/*	Affiche tous les portails sur le plateau */

void						afficher_gagnant							(etatPartie_s etatPartieEnCours);
																					/*	En fin de partie affiche le joueur gagnant et le type de victoire	*/

AnsiColorsTxt_e 			determiner_couleur_bushi					(NumeroIdentificationBushi_e numeroIdentificationBushi);
																					/*	Retourne la couleur d'affichage d'un bushi en fonction du numero de bushi	*/

AnsiColorsTxt_e 			determiner_couleur_avec_num_joueur			(NumeroJoueur_e numJoueur);
																					/*	Retourne la couleur à afficher en fonction du numero de joueur (utilise pour les
																						portails	*/

void 						placer_curseur 								(PositionCurseur_e positionCurseur);
																					/*	Place le curseur a un endroit précis de l'ecran, défini par une enumeration et
																						un switch case dans la fonction	*/

void 						afficher_message_information_prompt 		(char message[]);
																					/*	Affiche un message d'erreur personnalisable sur la sortie standard et attend que la 
																						touche entree soit pressee	*/

Boolean 					saisi_de_confirmation 						(char question[]);
																					/*	Affiche une question et demande la confirmation de l'utilisateur par saisi via l'entree standard	*/

typeCommandePrompt_e 		recherche_commande_saisie_prompt			(char saisiePrompt[MAX_LENGTH_PROMPT]);
																					/*	Analyse la saisie dans le prompt pour identifier une commande	*/

void 						executer_commande							(typeCommandePrompt_e commande, char saisiePrompt[MAX_LENGTH_PROMPT], etatPartie_s *p_etatPartieEnCours);
																					/*	Contient un switch case qui execute la commande trouvee	*/

void 						selectionner_jouer_bushi					(char saisiePrompt[MAX_LENGTH_PROMPT], etatPartie_s *p_etatPartieEnCours);
																					/*	Permet la selection d'une case contenant un bushi appartenant au joueur, la selection d'une case
																						d'arrivee pour le deplacement et l'appel au fonction de mouvement (saut/glissement)	*/

void 						afficher_cmd_help 							();
																					/*	Affiche sur la sortie standard des indications sur l'emploi des commandes disponibles	*/


#endif
