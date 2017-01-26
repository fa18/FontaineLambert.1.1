/*	Module axe sur la manipulation du contenu des cases et du plateau de jeux. Ce module ne gère pas l'affichage. */


#include "fonctions.h" 		// Pour la fonction 'valeur_absolue'	
#include "configuration.h" 	// Pour les structures, enumérations et constantes
#include "plateau.h" 		// Fichier d'en-tête comportant la VARIABLE GLOBAL 'plateau[y][x]' et les prototypes des fonctions


/*	modifier ces constantes pour creer des variantes de jeux.
ATTENTION, NE PAS CONFONDRE LES COORDONNES UTILISATEUR A0... avec l'origine en bas à gauche du plateau.
ET LES COORDONNES 'SYSTEMES'x=0,y=1'... avec l'origine en haut à gauche du plateau.
TOUJOURS DEVELOPPER EN TENANT COMPTE DES COORDONNEES SYSTEMES AVEC L'ORIGINE EN HAUT A GAUCHE	*/

const Boolean casesDansPlateau[DIM_V_PLATEAU][DIM_H_PLATEAU] = 	{	{ 0,  1,  1,  1,  1,  1,  1,  1,  1,  0 },
																	{ 0,  1,  1,  1,  1,  1,  1,  1,  1,  0 },
																	{ 0,  1,  1,  1,  1,  1,  1,  1,  1,  0 },
																	{ 0,  1,  1,  1,  1,  1,  1,  1,  1,  0 },
																	{ 1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },
																	{ 1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },
																	{ 0,  1,  1,  1,  1,  1,  1,  1,  1,  0 },
																	{ 0,  1,  1,  1,  1,  1,  1,  1,  1,  0 },
																	{ 0,  1,  1,  1,  1,  1,  1,  1,  1,  0 },
																	{ 0,  1,  1,  1,  1,  1,  1,  1,  1,  0 }	};

																/*	(x,y), (x,y)...	*/
const Coordonnees_s posInitBushi[NB_JOUEUR][NB_BUSHI_ARMEE] = { {	{1,2}, {2,1}, {3,0}, {6,0}, {7,1}, {8,2},	/* armee J1, singes */
																	{1,1}, {2,0}, {7,0}, {8,1},					/* armee J1, lions */
																	{1,0}, {8,0}	},							/* armee J1, dragons */
													
																{	{1,7}, {2,8}, {3,9}, {6,9}, {7,8}, {8,7},	/* armee J2, singes */
																	{1,8}, {2,9}, {7,9}, {8,8},					/* armee J2, lions */
																	{1,9}, {8,9}	}						};	/* armee J2, dragons */	
															
																	/*	(x,y), (x,y)	*/
const Coordonnees_s portails[NB_JOUEUR][NB_PORTAIL_PAR_JOUEUR] = {	{	{4,1}, {5,1}	},			/*	Portail J1	*/
																	{	{4,8}, {5,8}	}	};		/*	Portail J2	*/







Boolean case_occupee (Coordonnees_s caseCible) {
	
	if( plateau[caseCible.y][caseCible.x] != CASE_VIDE )
	{	
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



Boolean case_dans_plateau (Coordonnees_s caseCible) {

	if( casesDansPlateau[caseCible.y][caseCible.x] == TRUE)
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}



Boolean case_accessible(Coordonnees_s caseCible){
	
	if( (case_occupee(caseCible) == FALSE) && (case_dans_plateau(caseCible) == TRUE) )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



Direction_e determiner_direction(Coordonnees_s casePivot, Coordonnees_s caseCible){
	
	Direction_e direction;
	int deltaX, deltaY;
	
	deltaX = caseCible.x - casePivot.x;
	deltaY = caseCible.y - casePivot.y;
	
	if( ( 	(deltaX != 0) && (deltaY != 0) && (valeur_absolue(deltaX) != valeur_absolue(deltaY) ) 	) || 	/* Direction impossible... */
		(	(deltaX == deltaY) && (deltaX == 0))	 )														/* La case pivot et la case cible ont les mêmes coordonnées */
	{																				
		direction = AUCUNE;
	}
	else if( (deltaX >= 1) && (deltaY >= 1) && (valeur_absolue(deltaX) == valeur_absolue(deltaY)) )
	{	
		direction = HAUT_DROITE;
	}
	else if( (deltaY == 0) && (deltaX >= 1) )
	{
		direction = DROITE;
	}
	else if( (deltaY <= -1) && (deltaX >= 1) && (valeur_absolue(deltaX) == valeur_absolue(deltaY)) )
	{
		direction = BAS_DROITE;
	}
	else if((deltaX == 0) && (deltaY <= -1))
	{
		direction = BAS;
	}
	else if((deltaY <= -1) && (deltaX <= -1) && (valeur_absolue(deltaX) == valeur_absolue(deltaY)))
	{
		direction = BAS_GAUCHE;
	}
	else if((deltaY == 0) && (deltaX <= -1))
	{
		direction = GAUCHE;
	}
	else if((deltaY >= 1) && (deltaX <= -1) && (valeur_absolue(deltaX) == valeur_absolue(deltaY)))
	{
		direction = HAUT_GAUCHE;
	}
	else		// <-> (deltaX == 0) && (deltaY >= 1)
	{ 
		direction = HAUT; 
	}
	
		return direction;
}



int calcul_distance_entre_case(Coordonnees_s casePivot, Coordonnees_s caseCible){
	
	int distance;
	int deltaX, deltaY;
	int valAbsDeltaX, valAbsDeltaY;
	
	/* on ne peut pas calculer une distance si la direction n'est pas defini */
	if( determiner_direction(casePivot,caseCible) == AUCUNE )
	{	
		return ERREUR_DISTANCE;
	}
	
	/* calcul des delta de coordonnees afin de déterminer les distance */
	deltaX = caseCible.x - casePivot.x;
	deltaY = caseCible.y - casePivot.y;

	valAbsDeltaX = valeur_absolue(deltaX); 
	valAbsDeltaY = valeur_absolue(deltaY);

	
	/* Pour les distances, on retourne toujours la valeur absolue. Car deltaX ou deltaY peut être négatif */
	
	if( deltaX == 0 )			/*	Correspond à une des 2 directions verticales. Prend egalement en compte le cas ou */
	{							/* 	deltaX et deltaY sont egaux à 0, et retourne donc une distance egal a 0 */									
		distance = valAbsDeltaY;
	}
	else if( deltaY == 0 )		// Correspond à une des 2 directions horizontales
	{
		distance = valAbsDeltaX;
	}
	else if ( valAbsDeltaY == valAbsDeltaX )	// Correspond à une des 4 directions diagonales	
	{ 
		distance = valAbsDeltaY;
	}
		
	return distance;
}



Coordonnees_s calcul_coordonnees_case(Coordonnees_s casePivot,Direction_e direction, int distance){
	
	Coordonnees_s caseCalculee;
	
	/* On part des coordonees du pivot pour ajouter ou retirer la distance sur les coordonnees en fonction de la direction passee en parametre */
	caseCalculee.y = casePivot.y; 	
	caseCalculee.x = casePivot.x;
	
	switch (direction)
	{
		case AUCUNE :	// Il est impossible de calculer une nouvelle case, on retourne donc la case pivot.
		
			caseCalculee.y = casePivot.y; 
			caseCalculee.x = casePivot.x;
			break;
			
		/*--------------*/
		case HAUT :
			
			caseCalculee.y += distance;
			break;
			
		/*--------------*/
		case BAS :
			
			caseCalculee.y -= distance;
			break;
		
		/*--------------*/
		case DROITE :
		
			caseCalculee.x += distance;
			break;
			
		/*--------------*/
		case GAUCHE :
		
			caseCalculee.x -= distance;
			break;
			
		/*--------------*/
		case HAUT_DROITE :
		
			caseCalculee.x += distance;
			caseCalculee.y += distance;
			break;
		
		/*--------------*/
		case HAUT_GAUCHE :
		
			caseCalculee.x -= distance;
			caseCalculee.y += distance;
			break;
			
		/*--------------*/
		case BAS_DROITE :
		
			caseCalculee.x += distance;
			caseCalculee.y -= distance;
			break;
			
		/*--------------*/
		case BAS_GAUCHE :
		
			caseCalculee.x -= distance;
			caseCalculee.y -= distance;
			break;
	}
	
	return caseCalculee;
}



void initialiser_plateau(){
	
	fixer_plateau_vierge();
	integrer_placements_initiaux_bushis();
}



void fixer_plateau_vierge() {	

	Coordonnees_s caseInitialisee;
	
	for( caseInitialisee.y = 0 ; caseInitialisee.y < DIM_V_PLATEAU ; caseInitialisee.y++ )
	{
		for( caseInitialisee.x = 0; caseInitialisee.x < DIM_H_PLATEAU ; caseInitialisee.x++ )
		{
			if( case_dans_plateau(caseInitialisee) == TRUE )
			{
				plateau[caseInitialisee.y][caseInitialisee.x] = CASE_VIDE;
			}	
		}
	}
	
}



void integrer_placements_initiaux_bushis() {
	
	NumeroIdentificationBushi_e numeroIdentificationBushi = 1;
	Coordonnees_s coord;
	int numJoueur, numBushi;
	
	for( numJoueur = 0 ; numJoueur < NB_JOUEUR ; ++numJoueur )
	{
		for( numBushi = 0 ; numBushi < NB_BUSHI_ARMEE ; ++numBushi )
		{
			coord.x = posInitBushi[numJoueur][numBushi].x;
			coord.y = posInitBushi[numJoueur][numBushi].y;
			
			plateau[coord.y][coord.x] = numeroIdentificationBushi;
			++numeroIdentificationBushi;
		}
	}
	
}



void effacer_bushi_case(Coordonnees_s caseCible){
	
	plateau[caseCible.y][caseCible.x] = CASE_VIDE;
}



void placer_bushi_sur_case(Coordonnees_s caseCible, NumeroIdentificationBushi_e numeroIdentificationBushi){
	
	plateau[caseCible.y][caseCible.x] = numeroIdentificationBushi;
}




