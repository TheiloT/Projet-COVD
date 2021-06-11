#pragma once

#include "outils.h"
#include "map.h"

// Fonctions relative au mode jeu

void affiche_boutons_joueur(int L, int H, int taille_case, int taille_case_editeur, int bande_texte, string nom_map, std::map<int, int> blocs_disponibles); // Affiche les boutons dans l'interface de placement des effets

bool getAction_joueur(int x, int y, int &bouton_action, int bande_texte, int L, int taille_case, int taille_case_editeur); // Renvoie si le joueur a clique une action, et la renseigne dans bouton_action

void prepare_map(Map map, int L, int H, std::map<int, int> &blocs_disponibles); // Prepare la map en vue de la jouer : conversion des blocs effets en blocs modifiables et remplissage des stocks d'effets dont dispose le joueur

void clignote(int x, int y, int taille_case); // Fait clignoter un bloc en rouge lorsqu'on ne peut pas y placer le bloc voulu (stock insuffisant ou tentative de placement d'un effet sur autre chose qu'un bloc modifiable)

void trace_etoile_pleine_vide(int x, int y, int taille_etoile, bool collectee); // Trace une etoile pleine si elle est collectee, vide sinon. Cette fonction est utilisee par affiche_etoiles dans le message de victoire en fin de niveau.

void affiche_etoiles(int x, int y, int hauteur_etoile, int largeur_etoiles, int nb_etoiles_collectees); // Affiche les etoiles collectees dans la fenetre de victoire

void affiche_retour(int x, int y, int taille_bouton); // Bouton de retour dans la fenetre de victoire

void affiche_victoire(int nb_etoiles_collectees); // Affichage de la fenetre de victoire en fin de niveau

bool run (const Map &map, int taille_case, int &nb_etoiles_collectees); // Deroulement de la partie a proprement parler : lance le cube, appelle les interactions du cube avec la map, rafraichit l'affichage.

void jouer(Map map, int taille_case); // Lance l'interface de placement des effets par le joueur
