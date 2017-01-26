#include "fonctions.h" 
#include "plateau.h"
#include "configuration.h"
#include "interface.h"

#include <string.h>
#include <stdio.h>
#include <stddef.h> // Pour 'NULL'
 


void empty_buffer(void) {
/*-- Vide le buffer suite à une saisie au clavier --*/

	while(getchar() != '\n');
	return;
}



void saisir(char chaine[], int longueur) {
/*-- Permet la saisie de manière "sécurisée" --*/

	char *p_positionEntree = NULL;

	fgets(chaine, longueur, stdin);
	
	p_positionEntree = strchr(chaine, '\n'); // strchr retourne l'adresse de la première occurence du retour chariot
	if (p_positionEntree != NULL) // Adresse si l'utilisateur a saisi moins de caractère que la limite
	{ 
		*p_positionEntree = '\0'; // On remplace par '\0' pour fermer proprement la chaine de caractère.
	}
	else
	{
		empty_buffer();
	}
	
}



int valeur_absolue(int nombre){
	/*	Retourne la valeur absolue d'UN entier */
	
	if(nombre < 0){
		nombre = nombre * (-1);
	}
	
	return nombre;
}



char upper_character(char character) {
	/*	Retourne une lettre en majuscule */
	
	if(character >= 'a' && character <= 'z') { //Cf table des codes ASCII
		character = character - 'a' + 'A'; 
	}
	return character;
}



void recuperer_parametre_commande (char saisiePrompt[MAX_LENGTH_PROMPT], int tailleChaineCmd, char parametre[], int tailleParametre) {
	
	int indiceCaractere;
	
	for( indiceCaractere = 0 ; indiceCaractere < tailleParametre ; ++indiceCaractere )
	{
		parametre[indiceCaractere] = saisiePrompt[tailleChaineCmd + indiceCaractere];
	}
}


 
void sauvegarder_fichier (char labelFichierSauvegarde[MAX_LENGTH_FILES], etatPartie_s etatPartieEnCours) {
/* !--- ATTENTION : LE SYSTEME DE SAUVEGARDE EST SENSIBLE A LA MACHINE (sauvegarde en binaire) ---!	*/

	FILE *p_fichierSauvegarde = fopen(labelFichierSauvegarde , "wb");	//Ouverture du fichier en mode
	 
 	fwrite( plateau , sizeof(NumeroIdentificationBushi_e), (DIM_V_PLATEAU * DIM_V_PLATEAU) , p_fichierSauvegarde);	//Sauvegarde
	
 	fwrite( &etatPartieEnCours , sizeof(etatPartieEnCours) , 1 , p_fichierSauvegarde);
	 
	fclose(p_fichierSauvegarde);
 
}



void sauvegarder_une_partie (etatPartie_s *p_etatPartieEnCours, char saisiePrompt[MAX_LENGTH_PROMPT]) {
/* !--- ATTENTION : LE SYSTEME DE SAUVEGARDE EST SENSIBLE A LA MACHINE (sauvegarde en binaire) ---!	*/

	char labelFichierSauvegarde[MAX_LENGTH_FILES];
	FILE *p_fichierSauvegarde;
	
	/*	On recupere le nom du fichier a sauvegarger	*/
	recuperer_parametre_commande(saisiePrompt, strlen(p_typeCommandePrompt[CMD_LOAD]), labelFichierSauvegarde, MAX_LENGTH_FILES-5);  // 4 caracteres sont reserves pour l'extention et 1 pour '\0'
	
	strcat(labelFichierSauvegarde, ".bin");	//Ajout de l'extension '.bin' par concatenation (append)
				
	p_fichierSauvegarde = fopen(labelFichierSauvegarde , "r");	// retourne un pointeur 'NULL' si le fichier n'existe pas

	if(p_fichierSauvegarde != NULL)
	{
		if( saisi_de_confirmation("Voulez-vous écraser le fichier ?") == TRUE )	
		{
			sauvegarder_fichier(labelFichierSauvegarde, *p_etatPartieEnCours);
			raffraichir_affichage_plateau (*p_etatPartieEnCours);
			afficher_message_information_prompt("\nLa partie a été sauvegardée.");
		}
		else
		{
			raffraichir_affichage_plateau (*p_etatPartieEnCours);
			afficher_message_information_prompt("\nVous avez annulé la sauvegarde de la partie.");
		}
	}
	else {
			sauvegarder_fichier(labelFichierSauvegarde, *p_etatPartieEnCours);
			raffraichir_affichage_plateau (*p_etatPartieEnCours);
			afficher_message_information_prompt("\nLa partie a été sauvegardée.");
	}
			
}	



void charger_fichier(char labelFichierCharge[MAX_LENGTH_FILES], etatPartie_s *p_etatPartieEnCours) {
/* !--- ATTENTION : LE SYSTEME DE SAUVEGARDE EST SENSIBLE A LA MACHINE (sauvegarde en binaire) ---!	*/

	FILE *p_fichierCharge = fopen(labelFichierCharge , "r");
	 
	fread( plateau , sizeof(NumeroIdentificationBushi_e), (DIM_V_PLATEAU * DIM_V_PLATEAU) , p_fichierCharge);
	
	fread( p_etatPartieEnCours , sizeof(*p_etatPartieEnCours) , 1 , p_fichierCharge);
	
	fclose(p_fichierCharge);
 
}
			
			
			
void charger_une_partie(etatPartie_s *p_etatPartieEnCours, char saisiePrompt[MAX_LENGTH_PROMPT]) {
/* !--- ATTENTION : LE SYSTEME DE SAUVEGARDE EST SENSIBLE A LA MACHINE (sauvegarde en binaire) ---!	*/

	char labelFichierSauvegarde[MAX_LENGTH_FILES];
	FILE *p_fichierSauvegarde;
	
	/*	On récupère le nom du fichier à charger	*/
	recuperer_parametre_commande(saisiePrompt, strlen(p_typeCommandePrompt[CMD_LOAD]), labelFichierSauvegarde, MAX_LENGTH_FILES-5);  // 4 caracteres sont reserves pour l'extention et 1 pour '\0'
	
	strcat(labelFichierSauvegarde, ".bin");	//Ajout de l'extension '.bin' par concatenation (append)
				
	p_fichierSauvegarde = fopen(labelFichierSauvegarde , "r");	// retourne un pointeur 'NULL' si le fichier n'existe pas

	if(p_fichierSauvegarde != NULL)	
	{
		if( saisi_de_confirmation("Voulez-vous charger la partie ?") == TRUE )
		{
			charger_fichier(labelFichierSauvegarde, p_etatPartieEnCours);
			raffraichir_affichage_plateau (*p_etatPartieEnCours);
			afficher_message_information_prompt("\nLa partie a été chargée.");
		}
		else
		{
			raffraichir_affichage_plateau (*p_etatPartieEnCours);
			afficher_message_information_prompt("\nVous avez annulé le chargement de la partie.");
		}
	}
	else {
			raffraichir_affichage_plateau (*p_etatPartieEnCours);
			afficher_message_information_prompt("Le fichier specifiée n'existe pas.");
	}
			
	fclose(p_fichierSauvegarde);
}
 
 
 
Coordonnees_s convertir_saisie_en_coordonnees(char coordonneesAlphaNumerique[TAILLE_COORDONNEES_ALPHA_NUMERIQUE]) {
	
	Coordonnees_s caseCible;
	caseCible.x = ( upper_character(coordonneesAlphaNumerique[0]) - 'A');
	caseCible.y = 9 - ((int) (coordonneesAlphaNumerique[1] - '0'));
	
	return caseCible;
	
}



Boolean conversion_possible_coordonnees_alpha_numerique (char coordonneesAlphaNumerique[TAILLE_COORDONNEES_ALPHA_NUMERIQUE]) {
	
	int nbCoordonneesVerifiees;
	
	for( nbCoordonneesVerifiees = 0 ; nbCoordonneesVerifiees < 2 ; ++nbCoordonneesVerifiees)
	{
		if(lettre_coordonnee_valide(coordonneesAlphaNumerique[INDICE_COOR_LETTRE], DIM_V_PLATEAU) != TRUE )
		{
			return FALSE;
		}
		if(chiffre_coordonnee_valide(coordonneesAlphaNumerique[INDICE_COOR_CHIFFRE], DIM_V_PLATEAU) != TRUE )
		{
			return FALSE;
		}
	}
	if (coordonneesAlphaNumerique[TAILLE_COORDONNEES_ALPHA_NUMERIQUE-1] != '\0')
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}



Boolean lettre_coordonnee_valide(char lettreCoordonnee, int borneMaxCoordonnee) {
	
	if( ( (upper_character(lettreCoordonnee) - 'A') >= 0) && ((upper_character(lettreCoordonnee) - 'A') < borneMaxCoordonnee) )
	{
		return TRUE;
	}
	else{
		return FALSE;
	}
}



Boolean chiffre_coordonnee_valide(char c_chiffreCoordonnee, int borneMaxCoordonnee) {
	
	int i_chiffreCoordonnee = (int) (c_chiffreCoordonnee - '0');
	if( (i_chiffreCoordonnee >= 0) && (i_chiffreCoordonnee < borneMaxCoordonnee) )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
 


