#pragma once

#include "outils.h"

// Fichier contenant les correspondances bloc-numero et couleur-numero

// ========== blocs ==========

const int vide = 0;
const int mur_non_modif = 1;
const int mur_modif = 2;
const int porte_entree = 3;
const int porte_sortie = 4;

const vector<int> murs = {mur_modif, mur_non_modif};

// Les obstacles
const int pic_bas = 5;
const int pic_droite = 6;
const int pic_haut = 7;
const int pic_gauche = 8;
const vector<int> pics = {pic_bas, pic_droite, pic_haut, pic_gauche};

// Les effets
const int rend_rouge = 9;
const int rend_vert = 10;
const int rend_bleu = 11;

const int saut = 12;
const int retour_arriere = 13;
const int accelerateur = 14;

const vector<int> effets_couleur = {rend_rouge, rend_vert, rend_bleu};
const vector<int> effets_action = {saut, retour_arriere, accelerateur};

// generateur ennemi
const int gen_ennemi = 15;

// etoile : a voir

// ========== couleurs ==========

const int neutre = 0; // Insensible a la couleur du joueur
const int rouge = 1;
const int vert = 2;
const int bleu = 3;

const vector<int> couleurs = {rouge, vert, bleu};

