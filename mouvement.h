/*	Module acces sur l'etude des differents mouvements possible via des codes erreurs	*/

#ifndef mouvement_h
#define mouvement_h


TypeMouvement_e 			determiner_mouvement						(Coordonnees_s casePivot, Coordonnees_s caseCible, etatPartie_s *p_etatPartieEnCours);
																					/*	Analyse les differents mouvements possible en fonctions des coordonnees des cases	*/

CodeErreurMouvement_e 		verifier_coherence_du_mouvement				(Coordonnees_s casePivot, Coordonnees_s caseCible);
																					/*	Verifie avant de s'interesser au mvt possible si il n'y a pas d'incoherence	*/

Boolean 					type_bushi_direction_verouillee				(NumeroIdentificationBushi_e numeroIdentificationBushi);
																					/*	Retourne si la direction d'un bushi est verrouillee pendant un tour grace au tableau global
																						'directionVerouilleePdtMouvement' de 'mouvement.c'	*/

CodeErreurMouvement_e		glissement_possible							(Coordonnees_s casePivot, Coordonnees_s caseCible, etatPartie_s *p_etatPartieEnCours);
																					/*	Retourne si un glissement est possible code erreur 'aucune'.	*/

Boolean 					case_vide_requis_pour_glissement			(Coordonnees_s casePivot, Coordonnees_s caseCible, Direction_e direction);
																					/*	Verifie que les cases sur la trajectoire d'un glissement soient bien vides	*/

void 						glisser										(Coordonnees_s casePivot, Coordonnees_s caseCible, etatPartie_s *p_etatPartieEnCours);
																					/*	effectue le glissement, la maj des coordonnes et termine le tour	*/

CodeErreurMouvement_e 		bushi_requis_pour_saut						(Coordonnees_s casePivot, Coordonnees_s caseCible, Direction_e direction);
																					/*	Verifie que les cases sur la trajectoire d'un saut contiennent bien toutes des bushis	*/

CodeErreurMouvement_e 		saut_possible								(Coordonnees_s casePivot, Coordonnees_s caseCible, Direction_e directionPrecedente[NB_BUSHI_ARMEE]);
																					/*	Verifie qu'un saut soit possible si c'est le cas, retourne un code erreur 'aucune'	*/

void 						sauter										(Coordonnees_s casePivot, Coordonnees_s caseCible, etatPartie_s *p_etatPartieEnCours);
																					/*	Effectue le saut, maj coor, maj direction precedente, increment nb saut du bushi	*/

void 						afficher_code_erreur_coherence_mouvement 	(CodeErreurMouvement_e codeErreurCoherenceMvt);
																					/*	Affiche un code erreur personnalise pour la coherence du mvt au moyen d'un switch case	*/

void 						afficher_code_erreur_glissement				(CodeErreurMouvement_e codeErreurGlissement, Coordonnees_s casePivot);
																					/*	Affiche un code erreur personnalise pour le glissement au moyen d'un switch case	*/

void 						afficher_code_erreur_saut					(CodeErreurMouvement_e codeErreurSaut, Coordonnees_s casePivot);
																					/*	Affiche un code erreur personnalise pour le saut du mvt au moyen d'un switch case	*/

void 						supprimer_figurine_apres_shing_shang		(Coordonnees_s casePivot, Coordonnees_s caseCible, etatPartie_s *p_etatPartieEnCours );
																					/*	Supprime une figurine si les conditions de shingShang sont remplis	*/


#endif
