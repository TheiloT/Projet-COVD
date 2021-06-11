#pragma once

#include "outils.h"
#include "map.h"

// Ce header concerne les fonctions pour l'edition de niveau et son interface graphique

void affiche_grille(int H, int L, int taille_case); // Affiche la grille pour faciliter la lecture et le placement lors de l'edition

void drawAction(int x, int y, int k, int taille_case); // Dessine les boutons d'action (faire partir le cube, sauvegarder...)

void drawBouton(int x, int y, int k, int taille_case_editeur); // Dessine les boutons des couleurs et blocs en mode edition

void affiche_boutons(int H, int L, int taille_case, int taille_case_editeur, int bande_texte, string nom_map); // Dessine les boutons des couleurs et blocs en mode joueurs

bool getAction(int x, int y, int &bouton_action, int bande_texte, int L, int taille_case, int taille_case_editeur); // Renvoie si le joueur a clique une action et la place dans bouton_action

bool getCouleur(int x, int y, int &bouton_couleur, int bande_texte, int L, int taille_case, int taille_case_editeur); // Renvoie si le joueur a clique une couleur et la place dans bouton_couleur

bool getBloc(int x, int y, int &bouton_bloc, int bande_texte, int L, int taille_case, int taille_case_editeur, int nb_lignes); // Renvoie si le joueur a clique un bloc et le place dans bouton_bloc

bool getEffet(int x, int y, int &bouton_effet, int bande_texte, int L, int taille_case, int taille_case_editeur, int nb_lignes); // Renvoie si le joueur a clique un effet et le place dans bouton_effet

bool placeBloc(int x, int y, int L, int H, int taille_case);// Renvoie si le joueur a cherche a placer un bloc

void creer_map(string nom_map, int L, int H, int taille_case, bool editer = false, Map map_a_editer = Map("",0,0), int num_map = -1, int nb_niveaux = -1, const string niveau = "Niveaux_perso.txt");
// creation de map. Des arguments sont passes avec une valeur par defaut arbitraire pour permettre l'edition d'un niveau deja existant.

void editer_map(Map map, int taille_case, int num_map, int nb_niveaux, string niveau = "Niveaux_perso"); // Edition de niveau
