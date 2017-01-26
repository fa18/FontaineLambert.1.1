#include "interface.h"
#include "configuration.h"
#include "fonctions.h"
#include "plateau.h"
#include "armee.h"
#include "gestionTour.h"
#include "mouvement.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>	//	Pour les manipulations de chaines


/*	Indique le nombre de colonnes par ligne du plateau necessaire pour un affichage qui s'adapte "aux lignes du milieu" dans la regle de base.
	Pour creer une variante du plateau, modifier le nombre de colonne en (DIM_H_PLATEAU, ou DIM_H_PLATEAU,-2) et mettre a jour la
	variable globale 'casesDansPlateau' du fichier 'plateau.h'.		*/
const int nbColonneSurLigne[DIM_V_PLATEAU] = {	(DIM_H_PLATEAU-2), 
												(DIM_H_PLATEAU-2), 
												(DIM_H_PLATEAU-2), 
												(DIM_H_PLATEAU-2), 
												DIM_H_PLATEAU, 
												DIM_H_PLATEAU, 
												(DIM_H_PLATEAU-2), 
												(DIM_H_PLATEAU-2), 
												(DIM_H_PLATEAU-2), 
												(DIM_H_PLATEAU-2)	};
									
/* 	Mots cles permettant d'activer les commandes du prompt. Il est possible de modifier leur valeur mais PAS la disposition
	qui correspond au valeurs defini dans l'enumération 'typeCommandePrompt_e' du fichier 'configuration.h'		*/
const char *p_typeCommandePrompt[] = { "help", "load", "new_game", "-", "redraw", "save", "end", "back"};
 



void clear_screen() {

	printf("\e[1;1H\e[2J");
}



void reset_display_attributes() {
	
		printf("\033[%d;%d;%dm", ATT_ALL_ATTRIBUTES_OFF, ATT_DEFAULT_TXT_COLOR, ATT_DEFAULT_BGD_COLOR);
}



void raffraichir_affichage_plateau (etatPartie_s etatPartieEnCours) {
	
	clear_screen();
	
	afficher_plateau_de_jeu();
	
	afficher_numero_tour(etatPartieEnCours);
	
	afficher_label_joueur_actif(etatPartieEnCours);

	afficher_portails();

	afficher_tous_les_bushis ();

}



void afficher_plateau_de_jeu() {
	
	int ligne, colonne;
	
	printf("\n                  SHING-SHANG\n       Tour\n");	// Affichage de l'en-tete
	
	for( ligne = 0 ; ligne < DIM_V_PLATEAU ; ++ligne ) {
		
		if( (DIM_H_PLATEAU == nbColonneSurLigne[ligne]) ) /* Affichage des lignes horizontales delimitant les cases du plateau */
		{
			printf("   -----------------------------------------\n %d |", (DIM_V_PLATEAU-1) - ligne); // DIM_H_PLATEAU-1 pour afficher des coordonnees de 0 à 9 (aff des coordonnées 'chiffres' a gauche du plateau )
		}
		else if (nbColonneSurLigne[ligne-1] == DIM_H_PLATEAU) 
		{
			printf("   -----------------------------------------\n %d     |", (DIM_V_PLATEAU-1) - ligne); 
		}
		else
		{
			printf("       ---------------------------------\n %d     |", (DIM_V_PLATEAU-1) - ligne);
		}
		for(colonne = 0 ; colonne < nbColonneSurLigne[ligne] ; ++colonne ) // Affichage des lignes verticales delimitant les cases du plateau
		{
			printf("   |");
		}
			printf("\n");
	}
		printf("       ---------------------------------\n     ");
		
		for( colonne = 0 ; colonne < DIM_H_PLATEAU ; ++colonne )
		{
			printf("%c   ", 'A'+ colonne);	// Affichage des coordonnées 'lettres' en bas du plateau
		}
		printf("\n\nC'est au tour du joueur \n");
} 



void afficher_label_joueur_actif(etatPartie_s etatPartieEnCours)
{
	placer_curseur (CUR_LABEL_JOUEUR);
	
	AnsiColorsTxt_e colorTxt = determiner_couleur_avec_num_joueur(etatPartieEnCours.numeroJoueur);
	
	if(etatPartieEnCours.numeroJoueur == UN)
	{
		printf("\033[%d;%dmbleu", ATT_INCREASE_INTENSITY, colorTxt);
	}
	else if (etatPartieEnCours.numeroJoueur == DEUX)
	{
		printf("\033[%d;%dmrouge", ATT_INCREASE_INTENSITY, colorTxt);
	}

	reset_display_attributes();
}



void afficher_numero_tour(etatPartie_s etatPartieEnCours)
{
	placer_curseur (CUR_NUMERO_TOUR);
	
	AnsiColorsTxt_e colorTxt = determiner_couleur_avec_num_joueur(etatPartieEnCours.numeroJoueur);
	
	printf("\033[%d;%dm%d", ATT_INCREASE_INTENSITY, colorTxt, etatPartieEnCours.numeroTour);
	
	reset_display_attributes();

}



void afficher_bushi_sur_curseur(Coordonnees_s caseCible, char caractere) {
	
	Coordonnees_s curseur;
	AnsiColorsTxt_e colorTxtBushi = determiner_couleur_bushi(plateau[caseCible.y][caseCible.x]);
	
	/*	On positionne en premier le curseur au centre de la case 'A9'(coor.aff utilisateur) càd x=0 et y=0 (coor.sys developpeur)
		Puis on applique un delta en x et y en fonction de largeur/hauteur des cases	*/
	curseur.x = CURSEUR_ORIGINE_X_PLT + ( caseCible.x * LARGEUR_CASE );
	curseur.y = CURSEUR_ORIGINE_Y_PLT + ( caseCible.y * HAUTEUR_CASE );
	
	printf("\033[%d;%dm\033[%d;%df%c", ATT_INCREASE_INTENSITY, colorTxtBushi, curseur.y, curseur.x, caractere);
	
	reset_display_attributes();
}



void afficher_portail_sur_curseur(Coordonnees_s caseCible, char caractere, AnsiColorsTxt_e colorTxtBushi) {
	
	Coordonnees_s curseur;
	
	/*	Pour les coordonnees du curseur, meme principe que dans la fonction 'afficher_bushi_sur_curseur'	*/
	curseur.x = CURSEUR_ORIGINE_X_PLT + ( caseCible.x * LARGEUR_CASE )-1;
	curseur.y = CURSEUR_ORIGINE_Y_PLT + ( caseCible.y * HAUTEUR_CASE );
	
	printf("\033[%dm\033[%d;%df[ ]", colorTxtBushi, curseur.y, curseur.x);
	reset_display_attributes();
	

}



void afficher_tous_les_bushis () {
	
	Coordonnees_s caseCible;
	TypeBushi_e typeBushiSurCase;

	/*	Parcours de l'integralite du plateau et si la case est occupee on affiche le bushi	*/	
	for( caseCible.y = 0 ; caseCible.y < DIM_V_PLATEAU ; ++caseCible.y)
	{
		for( caseCible.x = 0 ; caseCible.x < DIM_H_PLATEAU ; ++caseCible.x) 
		{

			if(case_dans_plateau(caseCible) == TRUE && plateau[caseCible.y][caseCible.x] != CASE_VIDE)
			{
	
				typeBushiSurCase = determiner_type_bushi(plateau[caseCible.y][caseCible.x]);
				

				if(typeBushiSurCase == SINGE)
				{
					afficher_bushi_sur_curseur(caseCible, AFF_SINGE);

				}
				else if (typeBushiSurCase == LION)
				{
					afficher_bushi_sur_curseur(caseCible, AFF_LION);

				}
				else
				{
					afficher_bushi_sur_curseur(caseCible, AFF_DRAGON);

				}
			}				

		}
	}
	printf("\n");
}



void afficher_portails() {

	int numJoueur, numPortail;
	
	for( numJoueur = 0 ; numJoueur < NB_JOUEUR ; ++numJoueur)
	{
		for( numPortail = 0 ; numPortail < NB_PORTAIL_PAR_JOUEUR ; ++numPortail)
		{
			afficher_portail_sur_curseur( portails[numJoueur][numPortail], AFF_PORTAIL, determiner_couleur_avec_num_joueur(numJoueur) );
		}
	}
}



void afficher_gagnant (etatPartie_s etatPartieEnCours) {
	
	raffraichir_affichage_plateau (etatPartieEnCours);

	placer_curseur (CUR_RETOUR_INFOS_PROMPT);

	AnsiColorsTxt_e colorTxt = determiner_couleur_avec_num_joueur(etatPartieEnCours.numeroJoueur);

	printf("Felicitation, le joueur ");

	if(etatPartieEnCours.numeroJoueur == UN)
	{
		printf("\033[%d;%dmbleu", ATT_INCREASE_INTENSITY, colorTxt);
	}
	else if (etatPartieEnCours.numeroJoueur == DEUX)
	{
		printf("\033[%d;%dmrouge", ATT_INCREASE_INTENSITY, colorTxt);
	}

	reset_display_attributes();

	printf(" a remporté la partie !");

	getchar();

}



AnsiColorsTxt_e determiner_couleur_bushi(NumeroIdentificationBushi_e numeroIdentificationBushi) {
	
	if( determiner_proprietaire_du_bushi(numeroIdentificationBushi) == UN)
	{
		return CL_TXT_BLUE;
	}
	else 
	{
		return CL_TXT_RED;
	}
}



AnsiColorsTxt_e determiner_couleur_avec_num_joueur(NumeroJoueur_e numJoueur) {
	
	if(numJoueur == UN)
	{
		return CL_TXT_BLUE;
	}
	else 
	{
		return CL_TXT_RED;
	}
}



void placer_curseur (PositionCurseur_e positionCurseur) {
	
	Coordonnees_s curseur;
	
	switch (positionCurseur)
	{
		case CUR_NUMERO_TOUR :
		
			curseur.x = 13;
			curseur.y = 3;
			break;
			
		/*--------------*/
		case CUR_LABEL_JOUEUR :
		
			curseur.x = 25;
			curseur.y = 27;
			break;
			
		/*--------------*/
		case CUR_PROMPT :
		
			curseur.x = 1;
			curseur.y = 28;
			break;
			
		/*--------------*/
		case CUR_RETOUR_INFOS_PROMPT :
		
			curseur.x = 1;
			curseur.y = 30;
			break;
		
	}
	printf("\033[%d;%df", curseur.y, curseur.x);

}



void afficher_message_information_prompt (char message[]) {
	
	placer_curseur(CUR_RETOUR_INFOS_PROMPT);	// positionnement du curseur en dessous du prompt
	
	printf("%s\n%s", message, MSG_APPUYER_SUR_ENTREE);	// affichage de MSG_APPUYER_SUR_ENTREE pour informer l'utilisateur sur le getchar();
	
	getchar();
}



Boolean saisi_de_confirmation (char question[]){
	
	char saisiConfirmation[MAX_LENGTH_SAISI_CTRL];
		
	placer_curseur(CUR_RETOUR_INFOS_PROMPT);
	printf("%s\nPour valider, taper 'oui' ou 'o' : ", question);
	
	saisir(saisiConfirmation, MAX_LENGTH_SAISI_CTRL);
	
	if( (strcmp(saisiConfirmation, "oui")) == 0 || (strcmp(saisiConfirmation, "o") == 0) )	// rappel si chaines identiques, strcmp retourne 0.
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



typeCommandePrompt_e recherche_commande_saisie_prompt (char saisiePrompt[MAX_LENGTH_PROMPT]) {

	int nbCommandeParcouru = 0, commandeIdentifiee;
	char emplacementTxtCmde[MAX_LENGTH_CMDE_PROMPT];

	do {
		memset (emplacementTxtCmde, 0, sizeof (emplacementTxtCmde));	// Vide la chaine de caracteres en la remplissant de '0', sans cela la comparaison de chaine risque d'etre faussee.
		
		/*	Les commandes suivantes different des autres, car elles possedent des parametres (nom de fichier par exemple).
			il faut donc comparer uniquement le txt de la commande sans prendre en compte le caractere de fin de chaine		*/
		if(nbCommandeParcouru == CMD_LOAD || nbCommandeParcouru == CMD_SELECT || nbCommandeParcouru == CMD_SAVE)
		{
			memmove(emplacementTxtCmde, saisiePrompt, (strlen(p_typeCommandePrompt[nbCommandeParcouru])) );

		}
		else
		{
			/* CMD sans paramètre, la CMD devra se terminer par '\0', cad un retour chariot modifiee en '\0' par la fonction 'saisi' du module 'fonctions' */ 
			memmove(emplacementTxtCmde, saisiePrompt, (strlen(p_typeCommandePrompt[nbCommandeParcouru])+1) );	
		}
		
		commandeIdentifiee = strcmp(emplacementTxtCmde, p_typeCommandePrompt[nbCommandeParcouru]);		// recherche de la CMD à partir du tableau de CMD autorisee 'p_typeCommandePrompt'
		
		if(commandeIdentifiee != 0)	// En cas d'egalite dans la comparaison, commandeIdentifiee = 0
		{
			++nbCommandeParcouru;
		}
		
	}while( (commandeIdentifiee != 0) && (nbCommandeParcouru < NB_COMMANDE_PROMPT) );
	
	if( commandeIdentifiee != 0)
	{
		return CMD_AUCUNE;
	}
	else
	{
		/*	On retourne l'indice de la commande dans 'p_typeCommandePrompt', cette indice correspond a la valeur de
			la commande dans l'enumeration 'typeCommandePrompt_e' du fichier 'configuration.h'		*/
		return nbCommandeParcouru;
	}
}



void executer_commande (typeCommandePrompt_e commande, char saisiePrompt[MAX_LENGTH_PROMPT], etatPartie_s *p_etatPartieEnCours) {
	
	switch (commande)
	{
		case CMD_AUCUNE:
			
			raffraichir_affichage_plateau (*p_etatPartieEnCours);
			afficher_message_information_prompt("Erreur de saisi. Pour obtenir de l'aide taper 'help'.");
			
			break;
			
		/*--------------*/
		case CMD_HELP:
		
			clear_screen();
			
			afficher_cmd_help();	// contient un getchar() pour creer une pause
			
			raffraichir_affichage_plateau (*p_etatPartieEnCours);
			
			break;
			
		/*--------------*/
		case CMD_LOAD:
		
			charger_une_partie (p_etatPartieEnCours, saisiePrompt);

			break;
			
		/*--------------*/
		case CMD_NEW_GAME:
		
			if( saisi_de_confirmation("Voulez-vous vraiment démarrer une nouvelle partie ?\n(ne sauvegarde pas la partie actuelle)") == TRUE )
			{
				nouvelle_partie(p_etatPartieEnCours);
			}
			else
			{
				raffraichir_affichage_plateau (*p_etatPartieEnCours);
				afficher_message_information_prompt("Vous continuez la partie en cours.");
			}
			
			break;
			
		/*--------------*/
		case CMD_SELECT:
		
			/*	Commande qui permet de selectionne un bushi par ces coordonnees, de selectionner la case d'arrivee et de lancer la procedure de
				mouvement avec affichage d'erreur sur la sortie standard en cas d'incompatibilite	*/
			selectionner_jouer_bushi(saisiePrompt, p_etatPartieEnCours);
				
			break;
			
		/*--------------*/
		case CMD_REDRAW:
		
			raffraichir_affichage_plateau (*p_etatPartieEnCours);
			
			break;
			
		/*--------------*/
		case CMD_SAVE:
		
			sauvegarder_une_partie (p_etatPartieEnCours, saisiePrompt);
		
			break;
			
		/*--------------*/
		case CMD_END:
			
			if( p_etatPartieEnCours->nbSautPendantTourUnBushi < 1 && p_etatPartieEnCours->nbShingShangPendantTour < 1 )
			{
				raffraichir_affichage_plateau (*p_etatPartieEnCours);
				afficher_message_information_prompt("Impossible de terminer un tour sans avoir jouer un bushi.\nPour terminer un tour manuellement, réaliser au moins 1 saut.");
			}
			else
			{
				p_etatPartieEnCours->tourTermine = TRUE;
			}
			
			break;
			
		/*--------------*/
		case CMD_BACK:
		
			/* Pris en compte dans le cas CMD_SELECT */
			
			break;
		
	}
	
}



void selectionner_jouer_bushi(char saisiePrompt[MAX_LENGTH_PROMPT], etatPartie_s *p_etatPartieEnCours) {
				
	char coordonneesAlphaNumerique[TAILLE_COORDONNEES_ALPHA_NUMERIQUE];
	Coordonnees_s casePivot;
	
	/*	On recupere les coordonnées "utilisateur" sous la forme 'A0'	*/
	recuperer_parametre_commande(saisiePrompt, strlen(p_typeCommandePrompt[CMD_SELECT]), coordonneesAlphaNumerique, TAILLE_COORDONNEES_ALPHA_NUMERIQUE);
	
	coordonneesAlphaNumerique[0] = upper_character(coordonneesAlphaNumerique[0]);	// si l'utilisteur a saisi 'a0' on modifie en 'A0' pour la compatibilite de l'interprétation
		
	if( (conversion_possible_coordonnees_alpha_numerique(coordonneesAlphaNumerique)) == TRUE)
	{
		casePivot = convertir_saisie_en_coordonnees(coordonneesAlphaNumerique);		// on converti la saisi 'A0' en coordonnees x, y et détermine la casePivot contenant le bushi a déplacer
		
		
		
		/*	Verification de la validite de la case 'pivot' selectionnee	*/
		
		if(case_dans_plateau(casePivot) == FALSE)
		{
			raffraichir_affichage_plateau (*p_etatPartieEnCours);
			afficher_message_information_prompt("La case sélectionnée est hors plateau.");
		}
		else if(case_occupee(casePivot) == FALSE)
		{
			raffraichir_affichage_plateau (*p_etatPartieEnCours);
			afficher_message_information_prompt("Impossible de sélectionner un bushi sur une case vide...");
		}
		else if(	p_etatPartieEnCours->BushiJouePendantTour[p_etatPartieEnCours->nbShingShangPendantTour] != plateau[casePivot.y][casePivot.x] &&
					p_etatPartieEnCours->nbSautPendantTourUnBushi != 0 )
		{
			raffraichir_affichage_plateau (*p_etatPartieEnCours);
			afficher_message_information_prompt("Vous ne pouvez pas selectionner un autre bushi sans avoir réalisé de shing shang.");
		}
		else if(bushi_a_realise_shing_shang_dans_tour(*p_etatPartieEnCours, plateau[casePivot.y][casePivot.x]))
		{
			raffraichir_affichage_plateau (*p_etatPartieEnCours);
			afficher_message_information_prompt("Vous ne pouvez pas sélectionner un bushi qui a déjà réalisé un shing shang lors de ce tour.");
		}
		else if( (etre_proprietaire_du_bushi(plateau[casePivot.y][casePivot.x], p_etatPartieEnCours->numeroJoueur)) == TRUE)
			
		/*	Fin des verifications de la validite de la case 'pivot' selectionnee	*/
		
		/*	Vérification si les coordonnees de la case d'arrivee du deplacement sont definis sur la plateau	*/
		{
			char saisieCaseCible[5];	// coordonnée de taille 2 ('A0') + '\0' ou saisi egal à 'back'
			Boolean conversionPossibleCoorCaseCible;
			
			do {
				raffraichir_affichage_plateau(*p_etatPartieEnCours);
				placer_curseur(CUR_PROMPT);
				printf("(%s) -> ", coordonneesAlphaNumerique);
				
				saisir(saisieCaseCible, 5);
				
				conversionPossibleCoorCaseCible = conversion_possible_coordonnees_alpha_numerique(saisieCaseCible);
				
				if(conversionPossibleCoorCaseCible == FALSE && (strcmp(saisieCaseCible, p_typeCommandePrompt[CMD_BACK]) != 0)) // rappel si chaines identiques, strcmp retourne 0.
				{
					raffraichir_affichage_plateau (*p_etatPartieEnCours);
					afficher_message_information_prompt("Coordonnées invalides. Pour de l'aide, 'back' puis 'help'.");
				}
				
			}while(	(conversionPossibleCoorCaseCible == FALSE) && (strcmp(saisieCaseCible,  p_typeCommandePrompt[CMD_BACK]) != 0)	);
			
			if((conversionPossibleCoorCaseCible == TRUE) && (strcmp(saisieCaseCible,  p_typeCommandePrompt[CMD_BACK]) != 0))
			{
				Coordonnees_s caseCible = convertir_saisie_en_coordonnees(saisieCaseCible);
				
				/*	Bushi sélectionne et case d'arrivee du deplacement également, on test si un deplacement est possible	*/
				TypeMouvement_e typeMouvement = determiner_mouvement(casePivot, caseCible, p_etatPartieEnCours);
						
				if(typeMouvement != MVT_AUCUN)
				{
					/*	On ajoute le bushi joue a la liste des bushis joues pendant le tour.	*/
					p_etatPartieEnCours->BushiJouePendantTour[p_etatPartieEnCours->nbShingShangPendantTour]=plateau[casePivot.y][casePivot.x];
					
					if(typeMouvement == MVT_GLISSEMENT)
					{
						glisser(casePivot, caseCible, p_etatPartieEnCours);
					}
					else
					{
						sauter(casePivot, caseCible, p_etatPartieEnCours);
					}
					
				}
				else
				{
					/* Affichage du type d'erreur pris en compte dans mouvement.c */
				}
			}
			else if(strcmp(saisieCaseCible, p_typeCommandePrompt[CMD_BACK]) == 0)
			{
				raffraichir_affichage_plateau (*p_etatPartieEnCours);
				afficher_message_information_prompt("Vous avez annulé la sélection de votre bushi.");
			}
		}
		else
		{
			raffraichir_affichage_plateau (*p_etatPartieEnCours);
			afficher_message_information_prompt("Vous ne pouvez pas selectionner un bushi qui ne vous appartient pas.");
		}
	}
	else
	{
		raffraichir_affichage_plateau (*p_etatPartieEnCours);
		afficher_message_information_prompt("Syntaxe invalide. Pour de l'aide taper 'help'.");
	}	
			
}



void afficher_cmd_help () {
	
	printf("COMMANDES :\n\n%s: permet d'obtenir de l'aide sur le fonctionnement du jeux.\n\n", p_typeCommandePrompt[CMD_HELP]);
	
	printf("%s: redessine le plateau en cas de problème d'affichage.\n  Syntaxe: '%s'\n\n", p_typeCommandePrompt[CMD_REDRAW], p_typeCommandePrompt[CMD_REDRAW]);
	
	printf("%s: démarrer une nouvelle partie. Attention, ne sauvegarde pas la partie actuelle !\n  Syntaxe: '%s'\n\n", p_typeCommandePrompt[CMD_NEW_GAME], p_typeCommandePrompt[CMD_NEW_GAME]);
	
	printf("%s: sauvegarde une partie en vue de la poursuivre ultérieurement.\n  Syntaxe: '%s nomSauvegarde'\n\n", p_typeCommandePrompt[CMD_SAVE], p_typeCommandePrompt[CMD_SAVE]);
	
	printf("%s: charger une partie sauvegardée précédemment.\n  Syntaxe: '%s nomSauvegarde'\n\n", p_typeCommandePrompt[CMD_LOAD], p_typeCommandePrompt[CMD_LOAD]);
	
	printf("%s: selectionner un bushi appartenant au joueur afin d'entamer un déplacement.\nUne fois selectionne,",  p_typeCommandePrompt[CMD_SELECT]);
	
	printf(" il faut entrer uniquement la coordonnée de la case d'arrivée du mouvement souhaité.\n  Syntaxe: '%sB2' puis 'B3'\n\n", p_typeCommandePrompt[CMD_SELECT]);
	
	printf("%s: après la commande '%s', annule la selection d'un bushi.\n  Syntaxe: '%s'\n\n", p_typeCommandePrompt[CMD_BACK], p_typeCommandePrompt[CMD_SELECT], p_typeCommandePrompt[CMD_BACK]);
		
	printf("%s: achève le tour du joueur après avoir réalisé au moins un saut.\n  Syntaxe: '%s'\n\n\n%s", p_typeCommandePrompt[CMD_END], p_typeCommandePrompt[CMD_END], MSG_APPUYER_SUR_ENTREE);
	
	getchar();
	
}


