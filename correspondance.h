#ifndef BLOC_H
#define BLOC_H

// Fichier contenant les correspondances bloc-numero et couleur-numero

// ========== blocs ==========

const int vide = 0;
const int mur_non_modif = 1;
const int mur_modif = 2;
const int porte_entree = 3;
const int porte_sortie = 4;

// Les obstacles
const int pic = 5;

// Les effets
const int rend_rouge = 6;
const int rend_vert = 7;
const int rend_bleu = 8;
const int saut = 9;
const int retour_arriere = 10;
const int accelerateur = 11;

// generateur ennemi
const int gen_ennemi = 12;

// etoile : a voir

// ========== couleurs ==========

const int neutre = 0; // Insensible a la couleur du joueur
const int rouge = 1;
const int vert = 2;
const int bleu = 3;


#endif // BLOC_H
