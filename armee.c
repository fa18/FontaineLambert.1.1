#include "armee.h" 
#include "configuration.h" // Pour les structures, enumérations et constantes


NumeroIdentificationBushi_e typeBushi[NB_JOUEUR][NB_BUSHI_ARMEE]; // Variable globale, permettant de déterminer le type d'un bushi en fonction de son numero d'identification



void initialiser_types_bushis(){

	int numJoueur, numBushi;


	for( numJoueur = 0 ; numJoueur < NB_JOUEUR ; ++numJoueur ) {

		for( numBushi = 0 ; numBushi < NB_BUSHI_ARMEE ; ++numBushi ) {

			if( numBushi < NB_SINGE ) {

				typeBushi[numJoueur][numBushi] = SINGE;
			}
			else if( numBushi < (NB_SINGE+NB_LION) ) {

				typeBushi[numJoueur][numBushi] = LION;
			}
			else {

				typeBushi[numJoueur][numBushi] = DRAGON;
			}
		}
	}
	
}



Boolean etre_proprietaire_du_bushi(NumeroIdentificationBushi_e numeroIdentificationBushi, NumeroJoueur_e numeroJoueur){
	
	if( numeroJoueur == determiner_proprietaire_du_bushi(numeroIdentificationBushi) )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}	

NumeroJoueur_e determiner_proprietaire_du_bushi(NumeroIdentificationBushi_e numeroIdentificationBushi) {
	
	return ( (numeroIdentificationBushi-1) / NB_BUSHI_ARMEE );
}


Boolean comparer_taille_bushi(NumeroIdentificationBushi_e bushiActif, NumeroIdentificationBushi_e bushiCible){	

	/* 	Le bushi actif correspond au bushi sélectionné par le joueur en train de jouer, et
		le bushi cible correspond à un bushi présent sur une case contigue */

	if ( determiner_type_bushi(bushiActif) >= determiner_type_bushi(bushiCible) ) // Le type d'un bushi defini egalement sa taille (CF:configuration.h)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}	



TypeBushi_e determiner_type_bushi (NumeroIdentificationBushi_e bushi) {
	
	return ( typeBushi[ bushi / NB_BUSHI_ARMEE ][ ( (bushi - 1) % NB_BUSHI_ARMEE) ] ) ; /*	 '-1' car le premier numero d'identification des bushis debutent a 1
											et le premier l'indice du tableau 'typeBushi' debute a 0. */
}

NumeroIdentificationBushi_e determiner_numero_identification_bushi(NumeroJoueur_e numeroJoueur, int numeroDansArmeeJoueur) {
	
	return ( (numeroJoueur * NB_BUSHI_ARMEE) + (numeroDansArmeeJoueur) );
}

int determiner_indice_bushi_dans_armee(NumeroIdentificationBushi_e bushi) {
	
	return ( (bushi % NB_BUSHI_ARMEE) - 1 );
}






