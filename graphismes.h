#pragma once

void efface_bloc(int x, int y, int taille_case);

void contour_bloc(int x, int y, int taille_case);

void trace_bloc(int x, int y, int taille_case, int couleur);

void trace_bloc_modif(int x, int y, int taille_case);

void trace_porte_entree(int x, int y, int k, int taille_case, int couleur);

void trace_porte_sortie(int x, int y, int taille_case, int couleur);

void trace_saut(int x, int y, int taille_case);

void trace_retour_arriere(int x, int y, int taille_case);

void trace_pic(int x, int y, int k, int taille_case, int couleur);

void trace_lave(int x, int y, int taille_case, int bloc);

void trace_etoile(int x, int y, int taille_case);
