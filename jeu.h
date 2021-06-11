#pragma once

#include "outils.h"
#include "map.h"

void prepare_map(Map map, int L, int H, std::map<int, int> &blocs_disponibles);

void clignote(int x, int y, int taille_case);

void affiche_etoiles(int x, int y, int hauteur_etoile, int largeur_etoiles);

void affiche_retour(int x, int y, int taille_bouton);

void affiche_victoire(int nb_etoiles_collectees);

bool run (const Map &map, int taille_case, int &nb_etoiles_collectees);

void jouer(Map map, int taille_case);
