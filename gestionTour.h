#ifndef GESTION_TOUR_H
#define GESTION_TOUR_H

#include "configuration.h"


void		nouvelle_partie							(etatPartie_s *p_etatPartieEnCours);	
																/*	initialise le plateau, la structure gerant les tours, les types... pour une nouvelle partie	*/

void 		initialiser_debut_tour 					(etatPartie_s *p_etatPartieEnCours);
																/*	Initialise la variable gerant les evenements au sein d'un tour pour un joueur	*/

void		jouer_un_tour							(etatPartie_s *p_etatPartieEnCours);
																/*	Permet de saisir des commandes tant que le tour est actif
																	(tant q'un glissement n'a pas ete effectue ou que 'end' a ete tape)	*/

Boolean 	terminer_tour							(etatPartie_s *p_etatPartieEnCours);
																/*	Permet au joueur de terminer son tour manuellement avec la CMD 'end' si il a realise
																	au moins un saut ou un shingShang	*/

void 		incrementer_nombre_tour					(etatPartie_s *p_etatPartieEnCours);
																/*	Incremente le nombre de tour si tous les joueurs ont joue	*/

void 		changement_joueur_fin_tour				(etatPartie_s *p_etatPartieEnCours);
																/*	Donne la main au joueur suivant pour qu'il puisse jouer	*/

Boolean		bushi_a_realise_shing_shang_dans_tour	(etatPartie_s etatPartieEnCours, NumeroIdentificationBushi_e numeroIdentificationBushi);
																/*	Retourne vrai si un bushi a realise un shingShang pendant un tour	*/

Boolean 	dragon_en_vie_joueur					();
																/*	Retourne vrai si tous les joueurs possedent encore un dragon au minimun	*/

Boolean		dragon_present_sur_portail				(etatPartie_s etatPartieEnCours);
																/*	Retourne vrai si un dragon se trouve sur un des portails de son adversaire	*/

Boolean 	joueur_a_gagne							(etatPartie_s etatPartieEnCours);
																/*	Retourne vrai si un joueur a gagne la partie	*/

#endif
