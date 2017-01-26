/* ---------------------------------------------------------------

PROJET C: SHING-SHANG - Module M1106

auteurs : 	Fabien FONTAINE & Maxime LAMBERT
			DUT Informatique 1ere Annee - TD1 / TP1
			IUT de Caen

date : 2 janvier 2016

version : 1.0

avec l'assistance de :	M. Loudni et M. Plessis
						enseignants à l'IUT de Caen

-----------------------------------------------------------------*/


#include "configuration.h"
#include "plateau.h"
#include "interface.h"
#include "armee.h"
#include "fonctions.h"
#include "gestionTour.h"

#include <stdio.h>


int main (void) {
	
	etatPartie_s etatPartieEnCours;	// cf. "configuration.h" permet de stocker toutes les informations relatives à l'état de la partie, excepte la position des bushis sur le plateau
	
	nouvelle_partie(&etatPartieEnCours);

	do {
	
		initialiser_debut_tour (&etatPartieEnCours);

		raffraichir_affichage_plateau (etatPartieEnCours);
			
		jouer_un_tour(&etatPartieEnCours);// Un joueur peux rejouer en cas de shingShang ou même d'enchainement de saut.

		if(joueur_a_gagne(etatPartieEnCours) != TRUE)
		{

			changement_joueur_fin_tour(&etatPartieEnCours);
				
			incrementer_nombre_tour(&etatPartieEnCours);
		}
		else
		{
			afficher_gagnant(etatPartieEnCours);
		}

	}while( (joueur_a_gagne(etatPartieEnCours) != TRUE) );
	
	return 0;
}
