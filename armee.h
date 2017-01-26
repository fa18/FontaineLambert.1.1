/*	Module axe sur l'initialisation des types definissant l'armee des joueurs, l'interpretation des numeros d'identification de bushi et sur les comparaisons entre bushis
	par soucis de simplification un numero identification bushi sera parfois appelé bushi mais c'est IDENTIQUE.	*/

#ifndef ARMEE_H
#define ARMEE_H


#include "configuration.h" // Pour les structures, enumérations et constantes



void 							initialiser_types_bushis					();
																						/*	Initialise a chaque nouvelle partie les types de bushi en fonction des nb de bushis
																							pour chaques types.	*/

Boolean 						etre_proprietaire_du_bushi					(NumeroIdentificationBushi_e bushi, NumeroJoueur_e numeroJoueur);
																						/*	Retourne vrai si le bushi spécifié est celui appartenant au joueur en train de joueur */

NumeroJoueur_e 					determiner_proprietaire_du_bushi			(NumeroIdentificationBushi_e numeroIdentificationBushi);
																						/*	Retourne le numero de joueur possedant le bushi	*/
								
Boolean							comparer_taille_bushi						(NumeroIdentificationBushi_e bushiActif, NumeroIdentificationBushi_e bushiCible);
																						/*	Compare si le bushi cible appartenant aussi bien au joueur ou à l'adversaire 
																							est plus petit que le bushi actif */

TypeBushi_e						determiner_type_bushi 						(NumeroIdentificationBushi_e bushi);
																						/*	Retourne le type d'un bushi à partir de son numero d'identification	*/

NumeroIdentificationBushi_e 	determiner_numero_identification_bushi		(NumeroJoueur_e numeroJoueur, int numeroDansArmeeJoueur);
																						/*	Retourne le numero d'identification d'un bushi a partir du numero de joueur
																							et de son indice dans l'armée du joueur	*/

int 							determiner_indice_bushi_dans_armee			(NumeroIdentificationBushi_e bushi);
																						/*	Retourne l'indice du bushi dans l'armée d'un joueur a partir de son numero d'identification	*/

#endif
