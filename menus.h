#pragma once
#include "outils.h"

void draw_caracteristiques_niveau(int h, int hauteur, int largueur, string nom_map);

void draw_bouton_etiquette(int x, int y, int taille_bouton, int bouton);

void draw_etiquette(int x, int y, int k, int largeur_etiquette, int hauteur_etiquette, int largeur_texte_etiquette,
                    string nom_niveau, int taille_bouton, int marge_bouton, bool mode_perso);

void draw_bouton_bas(int x, int y, int taille_bouton, int bouton);


void draw_selection_niveau(int W, int H, int marge_x, int marge_y, int largeur_etiquette, int hauteur_etiquette,
                           int largeur_texte_etiquette, int taille_bouton, int marge_bouton,
                           int taille_bouton_bas, int marge_bouton_bas, int nombre_niveaux,
                           int nombre_niveaux_affiches, int page, const vector<tuple<string, int>> liste_niveaux, bool mode_perso);

vector<tuple<string, int>> recuperer_niveaux(bool mode_perso);

void draw_categorie_niveau(int W_menu, int H_menu, int marge_menu_x, int marge_menu_y, int taille_case);

void draw_titre(int taille, int x, int y);

void draw_menu(int W_menu, int H_menu, int marge_menu_x, int marge_menu_y);
