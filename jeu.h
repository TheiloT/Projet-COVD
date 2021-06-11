#pragma once

#include "outils.h"
#include "map.h"

void affiche_boutons_joueur(int L, int H, int taille_case, int taille_case_editeur, int bande_texte, string nom_map, std::map<int, int> blocs_disponibles);

bool getAction_joueur(int x, int y, int &bouton_action, int bande_texte, int L, int taille_case, int taille_case_editeur);

void prepare_map(Map map, int L, int H, std::map<int, int> &blocs_disponibles);

void clignote(int x, int y, int taille_case);

void trace_etoile_pleine_vide(int x, int y, int taille_etoile, bool collectee);

void affiche_etoiles(int x, int y, int hauteur_etoile, int largeur_etoiles, int nb_etoiles_collectees);

void affiche_retour(int x, int y, int taille_bouton);

void affiche_victoire(int nb_etoiles_collectees);

bool run (const Map &map, int taille_case, int &nb_etoiles_collectees);

void jouer(Map map, int taille_case);
