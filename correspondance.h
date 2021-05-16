#pragma once

#include "outils.h"

// Fichier contenant les correspondances bloc-numero et couleur-numero

// ========== blocs ==========

// Blocs basiques: de 0 a 29
const int vide = 0;
const int mur_non_modif = 1;
const int mur_modif = 2;
const int porte_entree_gauche = 3;
const int porte_entree_droite = 4;
const int porte_sortie = 5;

const vector<int> murs = {mur_non_modif, mur_modif};
const vector<int> portes_entree = {porte_entree_droite, porte_entree_gauche};

// Les effets de couleur: de 30 a 49
const int rend_rouge = 30;
const int rend_vert = 31;
const int rend_bleu = 32;
const int rend_neutre = 33;

const vector<int> effets_couleur = {rend_neutre, rend_rouge, rend_vert, rend_bleu};

// Les effets autres: de 50 a 69
const int saut = 50;
const int retour_arriere = 51;
const int accelerateur = 52;

const vector<int> effets_action = {saut, retour_arriere, accelerateur};
const vector<int> effets = {saut, retour_arriere, accelerateur, rend_neutre, rend_rouge, rend_vert, rend_bleu};

// Les obstacles: de 70 a 89
const int pic_bas = 70;
const int pic_droite = 71;
const int pic_haut = 72;
const int pic_gauche = 73;

const vector<int> pics = {pic_bas, pic_droite, pic_haut, pic_gauche};

const int lave_partiel = 75;
const int lave_totale = 76;

const vector<int> laves = {lave_partiel, lave_totale};

// generateur ennemi: apres 90
const int gen_ennemi = 90;

// Etoile
const int etoile = 100;

// ========== couleurs ==========

const int neutre = 0; // Insensible a la couleur du joueur
const int rouge = 1;
const int vert = 2;
const int bleu = 3;

const vector<int> couleurs = {neutre, rouge, vert, bleu};

// ========== Correspondances bouton - type d'action ==========

const int bouton_play = 0;
const int bouton_sauvegarder = 1;
const int bouton_quitter = 2;

// ========== Correspondances bouton - couleur ==========

// Les memes correspondances que pour les couleurs
const int bouton_neutre = neutre;
const int bouton_rouge = rouge;
const int bouton_vert = vert;
const int bouton_bleu = bleu;

// ========== Correspondances bouton - type de bloc ==========

const vector<int> bouton_mur = murs;
const vector<int> bouton_porte_entree = portes_entree;
const vector<int> bouton_porte_sortie = {porte_sortie};
const vector<int> bouton_vide = {vide};

const vector<int> bouton_saut = {saut};
const vector<int> bouton_retour_arriere = {retour_arriere};
const vector<int> bouton_accelerateur = {accelerateur};
const vector<int> bouton_rend_couleur = effets_couleur;

const vector<int> bouton_pic = pics;
const vector<int> bouton_lave = laves;
const vector<int> bouton_gen_ennemi = {gen_ennemi};
const vector<int> bouton_etoile = {etoile};

const vector<vector<int>> Liste_boutons = { bouton_mur, bouton_porte_entree, bouton_porte_sortie, bouton_vide,
                                            bouton_saut, bouton_retour_arriere, bouton_accelerateur, bouton_rend_couleur,
                                            bouton_pic, bouton_lave, bouton_gen_ennemi, bouton_etoile};

// Vecteur qui contient les vecteurs des blocs pour chaque bouton



// ========== associations couleut_int - couleur_Color ==========

const map<int, Color> couleur_int_vers_color {
    make_pair(neutre, BLACK), make_pair(rend_neutre, BLACK),
    make_pair(rouge, RED), make_pair(rend_rouge, RED),
    make_pair(vert, GREEN), make_pair(rend_vert, GREEN),
    make_pair(bleu, BLUE), make_pair(rend_bleu, BLUE)
};
