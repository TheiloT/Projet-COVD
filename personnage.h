#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <Imagine/Images.h>
using namespace Imagine;

#include "vector"
using namespace std;

#include "map.h"
#include "point.h"

class Personnage {
    // Position
    float x;
    float y;
    // Vitesse
    float vx;
    float vy;
    // Tableau des quatres coins
    Point Coins[4];
    // Etat du personnage
    bool vivant;
    bool arrive;

    void actualiser_coins();
public:
    Personnage(int x0, int y0, float vitesse);
    bool est_vivant();
    bool est_arrive();
    void affiche(int taille_case);
    void actualise_position();
    void interragit(Map map);
    void gravite(float g);
    void collision(Map map);
};

#endif // PERSONNAGE_H
