#ifndef PLATEAU_H
#define PLATEAU_H

#include "configuration.h"



NumeroIdentificationBushi_e	plateau[DIM_V_PLATEAU][DIM_H_PLATEAU];

extern const Boolean casesDansPlateau[DIM_V_PLATEAU][DIM_H_PLATEAU];
extern const Coordonnees_s posInitBushi[NB_JOUEUR][NB_BUSHI_ARMEE];
extern const Coordonnees_s portails[NB_JOUEUR][NB_PORTAIL_PAR_JOUEUR];



Boolean 		case_occupee							(Coordonnees_s coordonnees);
																	/*	retourne si une case est occupee par un bushi ou non	*/

Boolean			case_dans_plateau						(Coordonnees_s coordonnees);
																	/*	retourne si une case fait partie du plateau ou non (se base sur le plateau global 'plateau' de 'plateau.c').	*/

Boolean			case_accessible							(Coordonnees_s coordonnees);
																	/*	si la case n'est pas occupee ni hors plateau alors elle est accessible	*/

Direction_e		determiner_direction					(Coordonnees_s casePivot, Coordonnees_s caseCible);
																	/*	la différence de  distance entre les coordonnees de la case Pivot et de la case Cible determine la direction */

int				calcul_distance_entre_case				(Coordonnees_s pivot, Coordonnees_s cible);
																	/*	calcule et retourne la distance entre deux cases du plateau */

Coordonnees_s	calcul_coordonnees_case					(Coordonnees_s casePivot,Direction_e direction, int distance);
																	/*	Permet de calculer les coordonnees d'une case a partir d'une case pivot(=origine)	*/

void 			initialiser_plateau						();
																	/*	initialise le plateau en rajoutant les intégrant la position initiales des bushis	*/

void 			fixer_plateau_vierge					();
																	/*	initialise les cases du plateau avec la constante CASE_VIDE	*/

void			integrer_placements_initiaux_bushis		();
																	/*	Intègre les coordonnees initiaux des bushis present dans le tableau global 'posInitBushi'	*/

void 			effacer_bushi_case						(Coordonnees_s caseCible);
																	/*	Place la constante CASE_VIDE sur une case du plateau	*/

void 			placer_bushi_sur_case					(Coordonnees_s caseCible, NumeroIdentificationBushi_e numeroIdentificationBushi);
																	/*	Place le numero d'identification d'un bushi sur une case du plateau	*/
														

#endif
