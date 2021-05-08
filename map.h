#ifndef MAP_H
#define MAP_H

#include <Imagine/Images.h>
using namespace Imagine;


class Map
{
public:
    int H; // Hauteur
    int L; // Longueur
    MultiArray<int, 2> grille; // Grille d'entiers
    int x0, y0; // Position initiale du joueur

    void drawCase(int x, int y, int taille_case);

    Map(int h, int l);
    void affiche(int taille_case);
    void set_case(int x, int y, int k); // Attribut la valeur k à la case (x,y)
    int get_case(int x, int y);
};

#endif // MAP_H
