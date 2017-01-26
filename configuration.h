/*	Ce fichier d'en-tête contient toutes les structures, énumérations et les constantes utilisées par les autres fichiers de ce projet. */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H



/* constantes =========================================================== */



#define TRUE 1
#define FALSE 0

#define MSG_APPUYER_SUR_ENTREE "Appuyer sur entrée pour revenir à la partie. "

#define MAX_LENGTH_CMDE_PROMPT 8
#define MAX_LENGTH_PROMPT 40
#define NB_COMMANDE_PROMPT 8

#define MAX_LENGTH_FILES 30
#define MAX_LENGTH_SAISI_CTRL 4	// 'o' ou 'oui' + '\0'
#define TAILLE_COORDONNEES_ALPHA_NUMERIQUE 3 // Contient '\0' avec fgets en 3eme indice

#define NB_JOUEUR 2
#define NB_PORTAIL_PAR_JOUEUR 2
#define NB_BUSHI_ARMEE 12

#define NB_SINGE 6
#define NB_LION 4
#define NB_DRAGON 2
#define NB_TYPE_BUSHI 3

#define NB_SAUT_POUR_SHINGSHANG 2
#define DISTANCE_MAX_MOUVEMENT 2
#define DISTANCE_REQUISE_POUR_SAUT 2

#define INDICE_COOR_LETTRE 0	//Pour les coordonnees 'utilisateurs' ex :	'A0'
#define INDICE_COOR_CHIFFRE 1


#define CASE_VIDE 0
#define DIM_V_PLATEAU 10
#define DIM_H_PLATEAU 10 // Le plateau fait 10 cases de largeur/hauteur au plus large

#define ERREUR_DISTANCE -1

/*	affichage */
#define CURSEUR_ORIGINE_X_PLT 6
#define CURSEUR_ORIGINE_Y_PLT 5

#define LARGEUR_CASE 4
#define HAUTEUR_CASE 2

#define AFF_SINGE 'S'
#define AFF_LION 'L'
#define AFF_DRAGON 'D'
#define AFF_PORTAIL ' '



/* énumérations ========================================================== */



typedef enum {
	
	MVT_AUCUN,
	MVT_GLISSEMENT,
	MVT_SAUT
	
} TypeMouvement_e;

typedef enum {
	UN = 0,
	DEUX = 1
} NumeroJoueur_e; // Il n'y a que DEUX joueurs possible au ShingShang

typedef enum {
	/*	L'armee de 12 bushis possedee par UN joueur au ShingShang est constituee de 3 types de figurine. */
	
	SINGE = 1, // Le SINGE est la plus petite figurine (d'ou la valeur 1 dans cette enumeration)
	LION = 2, // Le LION est plus grand que le SINGE mais plus petit que le DRAGON
	DRAGON = 3 // Le DRAGON est la figurine la plus grande (d'ou la valeur 3 dans cette enumeration)
} TypeBushi_e;

typedef int Boolean; // Ne doit etre employe qu'avec les constantes TRUE et FALSE ou 1 / 0

typedef enum {
	
	CL_TXT_BLACK 	= 30,
	CL_TXT_WHITE 	= 37,
	CL_TXT_RED		= 31,
	CL_TXT_BLUE 	= 34
	
} AnsiColorsTxt_e;

typedef enum {
	
	CL_BGD_BLACK 	= 40,
	CL_BGD_WHITE 	= 47,
	CL_BGD_RED		= 41,
	CL_BGD_BLUE 	= 44
	
} AnsiColorsBgd_e;

typedef enum {
	
	ATT_ALL_ATTRIBUTES_OFF 	= 0,
	ATT_INCREASE_INTENSITY 	= 1,
	ATT_DEFAULT_TXT_COLOR 	= 39,
	ATT_DEFAULT_BGD_COLOR 	= 49,
	
} AnsiAttributesDisplay_e;

typedef enum {
	/*	9 directions sont possibles sur le plateau. Une direction est exprimé à partir d'une "case pivot"
		vers une "case cible". */
	
	AUCUNE, // Utilisé si case pivot = case cible ou que le "chemin" d'accès entre DEUX cases résulte d'une combinaison de direction.
	HAUT_DROITE,
	DROITE, 
	BAS_DROITE,
	BAS,
	BAS_GAUCHE,
	GAUCHE,
	HAUT_GAUCHE,
	HAUT
} Direction_e;


typedef enum {
	
	CUR_NUMERO_TOUR,
	CUR_LABEL_JOUEUR,
	CUR_PROMPT,
	CUR_RETOUR_INFOS_PROMPT
	
} PositionCurseur_e;


typedef enum{
	
	ERR_AUCUNE_ERREUR,
	ERR_DISTANCE,
	ERR_DISTANCE_SAUT_CASE_ADJACENTE,
	ERR_BUSHI_ADJACENT_ABSENT,
	ERR_BUSHI_ADJACENT_PLUS_GRAND,
	ERR_BUSHI_SUR_TRAJET_GLISSEMENT,
	ERR_SAUTS_EN_COURS,
	ERR_CASE_OCCUPEE,
	ERR_CASE_HORS_PLATEAU,
	ERR_DIRECTION_INEXISTANTE,
	ERR_DIRECTION_PRECEDENTE_VEROUILLEE
	
}CodeErreurMouvement_e;


typedef enum {
	
	// NE PAS MODIFIER LES VALEURS, si CMD à rajouter faire un "append"
	CMD_AUCUNE 		= -1,
	CMD_HELP		= 0,
	CMD_LOAD		= 1,
	CMD_NEW_GAME	= 2,
	CMD_SELECT		= 3,
	CMD_REDRAW		= 4,
	CMD_SAVE		= 5,
	CMD_END			= 6,
	CMD_BACK		= 7
	
} typeCommandePrompt_e;


typedef enum {
	
	BUSHI_NUMERO_J1_DEBUT = 1,
	BUSHI_NUMERO_J1_FIN = 12,
	BUSHI_NUMERO_J2_DEBUT = 13,
	BUSHI_NUMERO_J2_FIN = 25
	
} NumeroIdentificationBushi_e;



/* structures ========================================================== */



typedef struct {
	/* 	Le ShingShang se joue sur UN plateau de taille max 10*10. Cette structure transmet DEUX entiers permettant de parcourir la variable globale
		plateau[y][x]. L'origine du plateau est situé dans la case "en HAUT à GAUCHE". */
	
	int x; // Designe le numéro de colonne
	int y; // Designe le numéro de ligne
} Coordonnees_s;



typedef struct {
	
	NumeroIdentificationBushi_e 		BushiJouePendantTour[NB_BUSHI_ARMEE];	
	int									nbShingShangPendantTour;
	int									nbSautPendantTourUnBushi;
	
	int 								numeroTour;
	NumeroJoueur_e 						numeroJoueur;
	Boolean 							tourTermine;
	
	Boolean 							victoire;

	Direction_e 						directionPrecedente[NB_BUSHI_ARMEE];
		
} etatPartie_s;



#endif
