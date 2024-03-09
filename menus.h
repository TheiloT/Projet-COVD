#pragma once
#include "outils.h"

// Fonctions graphiques et outils specifiques aux menus

void draw_caracteristiques_niveau(int h, int hauteur, int largueur, string nom_map); // Dessine le menu de creation de niveau et de choix de son nom et dimensions

void draw_bouton_etiquette(int x, int y, int taille_bouton, int bouton);// Dessine les boutons sur une etiquette

void draw_etiquette(int x, int y, int k, int largeur_etiquette, int hauteur_etiquette, int largeur_texte_etiquette,
                    string nom_niveau, int taille_bouton, int marge_bouton, bool mode_perso); // Dessine une etiquette dans la selection des niveaux

void draw_bouton_bas(int x, int y, int taille_bouton, int bouton); // Dessine les boutons du bas du menu de selection du niveau


void draw_selection_niveau(int W, int H, int marge_x, int marge_y, int largeur_etiquette, int hauteur_etiquette,
                           int largeur_texte_etiquette, int taille_bouton, int marge_bouton,
                           int taille_bouton_bas, int marge_bouton_bas, int nombre_niveaux,
                           int nombre_niveaux_affiches, int page, const vector<tuple<string, int>> liste_niveaux, bool mode_perso); // Fonction des graphismes de la selection de niveau
// Cette fonction prend beaucoup d'arguments car ce menu est tres modulable

vector<tuple<string, int>> recuperer_niveaux(bool mode_perso);
// Vecteur contenant la liste des noms des niveaux. Contient aussi le nombre d'etoiles collectees sur chaque niveau, mais cette feature n'a pas ete pleinement implementee dans le temps imparti

void draw_categorie_niveau(int W_menu, int H_menu, int marge_menu_x, int marge_menu_y, int taille_case); // Fonction des graphismes du menu de choix de la categorie de niveaux

void draw_titre(int taille, int x, int y); // Dessine le titre principal

void draw_menu(int W_menu, int H_menu, int marge_menu_x, int marge_menu_y); // Fonction des graphismes du menu principal

// Fonction d'appel des menus a proprement parler

void menu_creation_niveau(int taille_case); // Ouvre le menu de creation de niveau : choix du nom de niveau, de ses dimensions

void selection_niveau(bool mode_perso, int taille_case); // Ouvre la selection du niveau parmi la liste des niveaux disponibles, en fonction de la categorie de niveaux selectionnee

void menu_categorie_niveau(int taille_case); // Ouvre le menu de choix de la categorie de niveaux : aventure ou communautaire

void menu_regles(); // Ouvre le .txt des regles du jeu

void lancer_menu(int taille_case); // Lance le menu principal
