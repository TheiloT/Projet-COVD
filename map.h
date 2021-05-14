#pragma once

#include "outils.h"


class Map
{
public:
    int H; // Hauteur
    int L; // Longueur
    MultiArray<int, 2> grille_blocs; // grille_blocs des types de blocs
    MultiArray<int, 2> grille_couleurs; // grille_blocs des couleurs

    void drawCase(int x, int y, int taille_case) const;

    Map(int h, int l);
    void affiche(int taille_case) const; // Affiche la map

    void set_case(int x, int y, int k); // Attribut la valeur k à la case type (x,y)
    int get_case(int x, int y) const; // Donne la valeur de la case type (x,y)

    void set_couleur(int x, int y, int k); // Attribut la valeur k à la case couleur (x,y)
    int get_couleur(int x, int y) const; // Donne la valeur de la case couleur (x,y)

    void load(int k); // Charge une map
};

