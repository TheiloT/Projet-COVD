#pragma once

#include "outils.h"
#include "map.h"

void affiche_grille(int H, int L, int taille_case);

void drawAction(int x, int y, int k, int taille_case);

void drawBouton(int x, int y, int k, int taille_case_editeur);

void affiche_boutons(int H, int L, int taille_case, int taille_case_editeur, int bande_texte, string nom_map);

void affiche_boutons_joueur(int L, int H, int taille_case, int taille_case_editeur, int bande_texte, string nom_map, std::map<int, int> blocs_disponibles);

bool getAction(int x, int y, int &bouton_action, int bande_texte, int L, int taille_case, int taille_case_editeur);

bool getAction_joueur(int x, int y, int &bouton_action, int bande_texte, int L, int taille_case, int taille_case_editeur);

bool getCouleur(int x, int y, int &bouton_couleur, int bande_texte, int L, int taille_case, int taille_case_editeur);

bool getBloc(int x, int y, int &bouton_bloc, int bande_texte, int L, int taille_case, int taille_case_editeur, int nb_lignes);

bool getEffet(int x, int y, int &bouton_effet, int bande_texte, int L, int taille_case, int taille_case_editeur, int nb_lignes);

bool placeBloc(int x, int y, int L, int H, int taille_case);

// Fonctions pour le mode "jouer"

void prepare_map(Map map, int L, int H, std::map<int, int> &blocs_disponibles);

void clignote(int x, int y, int taille_case);

void affiche_etoiles(int x, int y, int hauteur_etoile, int largeur_etoiles);

void affiche_retour(int x, int y, int taille_bouton);

void affiche_victoire();
