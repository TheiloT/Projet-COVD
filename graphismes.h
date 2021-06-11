#pragma once

#include "outils.h"

// Ce fichier rassemble des fonctions pour les graphismes en jeu

void efface_bloc(int x, int y, int taille_case); // Efface un bloc

void contour_bloc(int x, int y, int taille_case); // Dessine les contours d'un bloc

void trace_bloc(int x, int y, int taille_case, int couleur); // Trace un bloc

void trace_bloc_modif(int x, int y, int taille_case); // Trace un bloc modifiable (violet)

void trace_porte_entree(int x, int y, int k, int taille_case, int couleur); // Trace une porte d'entree avec une poignee dans la couleur demandee

void trace_porte_sortie(int x, int y, int taille_case, int couleur); // Idem pour la porte de sortie

void trace_saut(int x, int y, int taille_case); // Trace un bloc de saut

void trace_retour_arriere(int x, int y, int taille_case); // Trace un bloc de retour_arriere

void trace_pic(int x, int y, int k, int taille_case, int couleur); // Trace un pic dans une orientation donnee par l'entier k

void trace_lave(int x, int y, int taille_case, int bloc); // Trace un bloc de lave

void trace_etoile(int x, int y, int taille_case); // Trace une etoile
