#include "configuration.h"
#include "interface.h"
#include "armee.h"
#include "plateau.h"
#include "fonctions.h"
#include "gestionTour.h"



void nouvelle_partie(etatPartie_s *p_etatPartieEnCours) {
		
	p_etatPartieEnCours->victoire = FALSE;
	p_etatPartieEnCours->numeroTour = 1;
	p_etatPartieEnCours->numeroJoueur = UN;
	
	initialiser_types_bushis();
		
	initialiser_plateau();
	
	initialiser_debut_tour (p_etatPartieEnCours);
	
}



void initialiser_debut_tour (etatPartie_s *p_etatPartieEnCours) {
	
	p_etatPartieEnCours->tourTermine = FALSE;
	p_etatPartieEnCours->nbShingShangPendantTour = 0;
	p_etatPartieEnCours->nbSautPendantTourUnBushi = 0;
	
	int numBushi;
	for ( numBushi = 0 ; numBushi < NB_BUSHI_ARMEE ; ++numBushi )
	{
		p_etatPartieEnCours->directionPrecedente[numBushi] = AUCUNE;
		p_etatPartieEnCours->BushiJouePendantTour[numBushi] = 0;

	}
	
}



void jouer_un_tour(etatPartie_s *p_etatPartieEnCours) {
	
	char saisiePrompt[MAX_LENGTH_PROMPT];
	
	do{
		
		placer_curseur(CUR_PROMPT);
		saisir(saisiePrompt, MAX_LENGTH_PROMPT);

		typeCommandePrompt_e commande =  recherche_commande_saisie_prompt(saisiePrompt);

		executer_commande(commande,saisiePrompt,p_etatPartieEnCours);	// Si aucune CMD n'est trouve, retourne uniquement un message d'erreur sur la sortie standard.
		
		raffraichir_affichage_plateau (*p_etatPartieEnCours);

		
	}while(p_etatPartieEnCours->tourTermine != TRUE );
	
}



Boolean terminer_tour(etatPartie_s *p_etatPartieEnCours) {
	
	if( p_etatPartieEnCours->nbSautPendantTourUnBushi >= 1)
	{
		p_etatPartieEnCours->tourTermine = TRUE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



void incrementer_nombre_tour(etatPartie_s *p_etatPartieEnCours) {
	
	if(p_etatPartieEnCours->numeroJoueur == UN)
	{
		++p_etatPartieEnCours->numeroTour;
	}
}



void changement_joueur_fin_tour(etatPartie_s *p_etatPartieEnCours) {
	
	++p_etatPartieEnCours->numeroJoueur;
	
	if(p_etatPartieEnCours->numeroJoueur > DEUX)
	{
		p_etatPartieEnCours->numeroJoueur = UN;
	}
}



Boolean dragon_en_vie_joueur() {
	
	int numJoueur, numDragon;
	int nombreDragonEnVie;
	NumeroIdentificationBushi_e numIndBushiDragon;
	Coordonnees_s caseCible;
	
	for( numJoueur = 0 ; numJoueur < NB_JOUEUR ; ++numJoueur )
	{
		nombreDragonEnVie = 0;
		
		for( numDragon = 0 ; numDragon < NB_DRAGON ; ++numDragon )
		{
			numIndBushiDragon = determiner_numero_identification_bushi(numJoueur, (NB_BUSHI_ARMEE - numDragon));

			for( caseCible.y = 0 ; caseCible.y < DIM_V_PLATEAU ; ++caseCible.y)
			{
				for( caseCible.x = 0 ; caseCible.x < DIM_H_PLATEAU ; ++ caseCible.x)
				{
					if(plateau[caseCible.y][caseCible.x] == numIndBushiDragon)
					{
						++nombreDragonEnVie;
					}
				}
			}
		}

		if (nombreDragonEnVie == 0)
		{
			return FALSE;
		}
	}

	return TRUE;
	
}



Boolean dragon_present_sur_portail(etatPartie_s etatPartieEnCours) {
	
	int numJoueur, numPortail;
	NumeroIdentificationBushi_e bushiSurPortail;
	Coordonnees_s casePortailCible;
	
	for( numJoueur = 0 ; numJoueur < NB_JOUEUR ; ++numJoueur )
	{
		for( numPortail = 0 ; numPortail < NB_PORTAIL_PAR_JOUEUR ; ++ numPortail)
		{
			casePortailCible = portails[numJoueur][numPortail];
			bushiSurPortail = plateau[casePortailCible.y][casePortailCible.x];
			
			if( (case_occupee(casePortailCible) == TRUE) &&
				(etre_proprietaire_du_bushi(bushiSurPortail, etatPartieEnCours.numeroJoueur) == FALSE) &&
				(determiner_type_bushi(bushiSurPortail)	== DRAGON)					)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}



Boolean joueur_a_gagne(etatPartie_s etatPartieEnCours){
	
	if( (dragon_present_sur_portail(etatPartieEnCours) == TRUE) || (dragon_en_vie_joueur() == FALSE) )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}



Boolean	bushi_a_realise_shing_shang_dans_tour (etatPartie_s etatPartieEnCours, NumeroIdentificationBushi_e numeroIdentificationBushi) {
	int numBushi;
	
	for( numBushi = 0 ; numBushi < etatPartieEnCours.nbShingShangPendantTour ; ++numBushi )
	{
		if(numeroIdentificationBushi == etatPartieEnCours.BushiJouePendantTour[numBushi])
		{
			return TRUE;
		}
	}
	return FALSE;
}



