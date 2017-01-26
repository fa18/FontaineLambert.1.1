#include "armee.h" 
#include "fonctions.h"
#include "plateau.h"
#include "mouvement.h"
#include "interface.h"

#include <stdio.h>

/*	Modifier ces constantes pour creer des variantes de jeux...	*/
																	/*	SINGE,	LION,	DRAGON	*/
const TypeBushi_e directionVerouilleePdtMouvement[NB_TYPE_BUSHI] = 	{ 	SINGE, 	0, 		0 };
const int distanceGlissementMax[NB_TYPE_BUSHI] = 					{	2,		1,		0};
const int distanceSautMax[NB_TYPE_BUSHI] = 							{	2,		2,		2};


TypeMouvement_e determiner_mouvement(Coordonnees_s casePivot, Coordonnees_s caseCible, etatPartie_s *p_etatPartieEnCours) {
	
	CodeErreurMouvement_e codeErreurCoherenceMvt, codeErreurGlissement, codeErreurSaut;
	
	codeErreurCoherenceMvt = verifier_coherence_du_mouvement(casePivot, caseCible);
	
	if ( codeErreurCoherenceMvt == ERR_AUCUNE_ERREUR)
	{
		codeErreurGlissement = glissement_possible(casePivot, caseCible, p_etatPartieEnCours);
		codeErreurSaut = saut_possible(casePivot, caseCible, p_etatPartieEnCours->directionPrecedente);
		
		if ( codeErreurGlissement == ERR_AUCUNE_ERREUR )
		{
			return MVT_GLISSEMENT;
		}
		else if (codeErreurSaut == ERR_AUCUNE_ERREUR )
		{	
			return MVT_SAUT;
		}
		else
		{
			if( distanceGlissementMax[ (determiner_type_bushi (plateau[casePivot.y][casePivot.x]) - 1)] != 0)	// on affiche le code erreur glissement uniquement si le bushi peut glisser.
			{
				afficher_code_erreur_glissement(codeErreurGlissement, casePivot);
			}

			raffraichir_affichage_plateau (*p_etatPartieEnCours);

			afficher_code_erreur_saut(codeErreurSaut, casePivot);
			
			return MVT_AUCUN;
		}
	}
	else
	{
		afficher_code_erreur_coherence_mouvement(codeErreurCoherenceMvt);

		return MVT_AUCUN;
	}
}



//interpreter les appels de fonction pour le CodeErreurMouvement_e
CodeErreurMouvement_e verifier_coherence_du_mouvement(Coordonnees_s casePivot, Coordonnees_s caseCible){
		
	//si distance>2 saut ou glissement impossible
	if(calcul_distance_entre_case(casePivot,caseCible) > DISTANCE_MAX_MOUVEMENT)
	{
		return ERR_DISTANCE;
	}
	
	if( determiner_direction(casePivot, caseCible) == AUCUNE )
	{
		return ERR_DIRECTION_INEXISTANTE;
	}
	
	else if(case_dans_plateau(caseCible) != TRUE)
	{
		return ERR_CASE_HORS_PLATEAU;
	}
	
	else if(case_occupee(caseCible) == TRUE)
	{
		return ERR_CASE_OCCUPEE;
	}
	else
	{
		return ERR_AUCUNE_ERREUR;
	}

}	



Boolean type_bushi_direction_verouillee(NumeroIdentificationBushi_e numeroIdentificationBushi) {
	
	int i;
	
	for( i = 0 ; i < NB_TYPE_BUSHI ; ++i)
	{
		if( determiner_type_bushi(numeroIdentificationBushi) == directionVerouilleePdtMouvement[i])
		{
			return TRUE;
		}
	}
	
	return FALSE;
}



CodeErreurMouvement_e glissement_possible(Coordonnees_s casePivot, Coordonnees_s caseCible, etatPartie_s *p_etatPartieEnCours) {
	
	Direction_e direction = determiner_direction(casePivot, caseCible);
	TypeBushi_e typeBushiActif = determiner_type_bushi(plateau[casePivot.y][casePivot.x]);
	
	if(p_etatPartieEnCours->nbSautPendantTourUnBushi >= 1)
	{
		return ERR_SAUTS_EN_COURS;
	}
	if ( case_vide_requis_pour_glissement(casePivot, caseCible, direction) != TRUE )
	{
		return ERR_BUSHI_SUR_TRAJET_GLISSEMENT;
	}
	else if ( calcul_distance_entre_case(casePivot,caseCible) > distanceGlissementMax[ (typeBushiActif-1) ] )
	{
		return ERR_DISTANCE;
	}
	else
	{
		return ERR_AUCUNE_ERREUR;
	}
}



Boolean case_vide_requis_pour_glissement(Coordonnees_s casePivot, Coordonnees_s caseCible, Direction_e direction){
	
	Coordonnees_s caseAdjacente = casePivot;
	int distance;
	
	for( distance = 1 ; distance < calcul_distance_entre_case(casePivot, caseCible) ; ++distance )
	{
		caseAdjacente = calcul_coordonnees_case(caseAdjacente, direction, 1);
		
		if(case_occupee(caseAdjacente) == TRUE)
		{
			return FALSE;
		}
	}
	return TRUE;
	
}



void glisser(Coordonnees_s casePivot, Coordonnees_s caseCible, etatPartie_s *p_etatPartieEnCours){
	
	
	placer_bushi_sur_case(caseCible, plateau[casePivot.y][casePivot.x]);

	effacer_bushi_case(casePivot);
	
	p_etatPartieEnCours->tourTermine = TRUE;
	
	
}



//Retourne si la présence necessaire d'un bushi sur une case adjacente pour un saut est verifiee ou non
CodeErreurMouvement_e bushi_requis_pour_saut(Coordonnees_s casePivot, Coordonnees_s caseCible, Direction_e direction){
	
	Coordonnees_s caseAdjacente = casePivot;
	int distance;
	
	
	for( distance = 1 ; distance < calcul_distance_entre_case(casePivot, caseCible) ; ++distance )
	{
		caseAdjacente = calcul_coordonnees_case(caseAdjacente, direction, 1);
		
		if( case_occupee(caseAdjacente) == FALSE )
		{
			return ERR_BUSHI_ADJACENT_ABSENT;
		}
		else if ( 	determiner_type_bushi(plateau[casePivot.y][casePivot.x]) <
					determiner_type_bushi(plateau[caseAdjacente.y][caseAdjacente.x]))
		{
			return ERR_BUSHI_ADJACENT_PLUS_GRAND;
		}
	}
	return ERR_AUCUNE_ERREUR;
	
}	



//Analyse les positions de la case cible et du bushi actif pour déterminer et retourner si un saut est possible ou non 
CodeErreurMouvement_e saut_possible(Coordonnees_s casePivot, Coordonnees_s caseCible, Direction_e directionPrecedente[NB_BUSHI_ARMEE]){
	
	Direction_e direction = determiner_direction(casePivot, caseCible);
	TypeBushi_e typeBushiActif = determiner_type_bushi(plateau[casePivot.y][casePivot.x]);
	CodeErreurMouvement_e codeErreur;
	
	//On vérifie qu'un bushi adjacent n'est pas présent dans la direction du saut 
	codeErreur = bushi_requis_pour_saut(casePivot, caseCible, direction);
	
	if( codeErreur != ERR_AUCUNE_ERREUR)
	{
		return codeErreur;
	}
	else if( (calcul_distance_entre_case(casePivot,caseCible) > distanceSautMax[ (typeBushiActif-1) ]) )
	{
		return ERR_DISTANCE;
	}
	else if ((calcul_distance_entre_case(casePivot,caseCible) == 1))
	{
		return ERR_DISTANCE_SAUT_CASE_ADJACENTE;
	}
	else if( 	(directionPrecedente[determiner_indice_bushi_dans_armee(plateau[casePivot.y][casePivot.x]) ] != determiner_direction(casePivot, caseCible)) && 
				(directionPrecedente[determiner_indice_bushi_dans_armee(plateau[casePivot.y][casePivot.x]) ] != AUCUNE)  &&
				(type_bushi_direction_verouillee(plateau[caseCible.y][caseCible.x]) == TRUE)		)
	{
		return ERR_DIRECTION_PRECEDENTE_VEROUILLEE;
	}
	else
	{
		return ERR_AUCUNE_ERREUR;
	}

}	



void sauter(Coordonnees_s casePivot, Coordonnees_s caseCible, etatPartie_s *p_etatPartieEnCours){
	
	++p_etatPartieEnCours->nbSautPendantTourUnBushi;
	
	if(type_bushi_direction_verouillee(plateau[casePivot.y][casePivot.x]) == TRUE)
	{
		p_etatPartieEnCours->directionPrecedente[determiner_indice_bushi_dans_armee(plateau[casePivot.y][casePivot.x])] = determiner_direction(casePivot, caseCible);
	}
	
	if( p_etatPartieEnCours->nbSautPendantTourUnBushi >= NB_SAUT_POUR_SHINGSHANG) {
		supprimer_figurine_apres_shing_shang(casePivot, caseCible, p_etatPartieEnCours );
	}
	
	placer_bushi_sur_case(caseCible, plateau[casePivot.y][casePivot.x]);
	
	effacer_bushi_case(casePivot);
	
}



void supprimer_figurine_apres_shing_shang(Coordonnees_s casePivot, Coordonnees_s caseCible, etatPartie_s *p_etatPartieEnCours ){
	
	Direction_e direction = determiner_direction(casePivot, caseCible);
	Coordonnees_s caseAdjacente = casePivot;
	int distance;
		
	for( distance = 1 ; distance < calcul_distance_entre_case(casePivot, caseCible) ; ++distance )
	{
		caseAdjacente = calcul_coordonnees_case(caseAdjacente, direction, 1);
		if ( 	((determiner_type_bushi (plateau[casePivot.y][casePivot.x])) >= (determiner_type_bushi (plateau[caseAdjacente.y][caseAdjacente.x]))));
		{
			if( (determiner_proprietaire_du_bushi(plateau[casePivot.y][casePivot.x]) != determiner_proprietaire_du_bushi(plateau[caseAdjacente.y][caseAdjacente.x])))
			{	
				p_etatPartieEnCours->nbSautPendantTourUnBushi = 0;
				effacer_bushi_case(caseAdjacente);
				++p_etatPartieEnCours->nbShingShangPendantTour;
			}
		}
	}	
}



void afficher_code_erreur_coherence_mouvement (CodeErreurMouvement_e codeErreurCoherenceMvt){
	
	placer_curseur(CUR_RETOUR_INFOS_PROMPT);
		
		switch (codeErreurCoherenceMvt)
		{
			case ERR_DISTANCE: 
			
				printf("ERREUR: la distance maximale d'un déplacement est de %d cases.\n%s", DISTANCE_MAX_MOUVEMENT, MSG_APPUYER_SUR_ENTREE);
				break;
			
			/*--------------*/
			case ERR_DIRECTION_INEXISTANTE:

				printf("ERREUR: la direction entre les cases n'est pas définie.\n%s", MSG_APPUYER_SUR_ENTREE);
				break;
			
			/*--------------*/
			case ERR_CASE_HORS_PLATEAU:
			
				printf("ERREUR: le mouvement se termine sur une case en dehors du plateau.\n%s", MSG_APPUYER_SUR_ENTREE);
				break;
			
			/*--------------*/	
			case ERR_CASE_OCCUPEE:
			
				printf("ERREUR: le mouvement se termine sur une case occupée.\n%s", MSG_APPUYER_SUR_ENTREE);
				break;
		}
	getchar();
}



void afficher_code_erreur_glissement(CodeErreurMouvement_e codeErreurGlissement, Coordonnees_s casePivot){
	
	placer_curseur(CUR_PROMPT);
		
		switch (codeErreurGlissement)
		{
			case ERR_SAUTS_EN_COURS:
			
				printf("ERREUR: Vous ne pouvez pas interrompre vos sauts pour effectuer un glissement.\n%s", MSG_APPUYER_SUR_ENTREE);
				break;
				
			/*--------------*/
			case ERR_DISTANCE: 
				printf("ERREUR: la distance maximale d'un glissement pour ce type de figurine est de %d cases.\n%s",  
				(distanceGlissementMax[ (determiner_type_bushi(plateau[casePivot.y][casePivot.x])) - 1 ]), MSG_APPUYER_SUR_ENTREE);
				break;
			
			/*--------------*/	
			case ERR_BUSHI_SUR_TRAJET_GLISSEMENT:

				printf("ERREUR: un bushi se trouve sur la trajectoire.\n%s", MSG_APPUYER_SUR_ENTREE);
				break;
			
		}
	getchar();
}



void afficher_code_erreur_saut(CodeErreurMouvement_e codeErreurSaut, Coordonnees_s casePivot){
	
	placer_curseur(CUR_PROMPT);
		
		switch (codeErreurSaut)
		{
			case ERR_BUSHI_ADJACENT_ABSENT: 
			
				printf("ERREUR: un bushi requis pour le saut est absent de la trajectoire.\n%s", MSG_APPUYER_SUR_ENTREE);
				break;
				
			/*--------------*/
			case ERR_BUSHI_ADJACENT_PLUS_GRAND:

				printf("ERREUR: un bushi plus grand se trouve sur la trajectoire du saut.\n%s", MSG_APPUYER_SUR_ENTREE);
				break;

			/*--------------*/				
			case ERR_DISTANCE:
			
				printf("ERREUR: la distance maximale d'un saut pour ce type de figurine est de %d cases.\n%s", 
				distanceSautMax[ (determiner_type_bushi(plateau[casePivot.y][casePivot.x]) - 1) ], MSG_APPUYER_SUR_ENTREE);
				break;
			
			/*--------------*/
			case ERR_DISTANCE_SAUT_CASE_ADJACENTE:
			
				printf("ERREUR: impossible de sauter sur une case adjacente.\n%s", MSG_APPUYER_SUR_ENTREE);
				break;

			/*--------------*/				
			case ERR_DIRECTION_PRECEDENTE_VEROUILLEE:
			
				printf("ERREUR: la direction est verrouillée sur celle du précédent saut pour cette figurine.\n%s", MSG_APPUYER_SUR_ENTREE);
				break;
		}
	getchar();
}



