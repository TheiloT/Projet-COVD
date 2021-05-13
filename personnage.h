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
    // Case du dernier changement de direction
    int x_change_dir, y_change_dir;

    void actualiser_coins();
public:
    Personnage(int x0, int y0, float vitesse);
    bool est_vivant();
    bool est_arrive();
    void affiche(int taille_case); // Affiche le personnage
    void actualise_position(); // Calcul la nouvelle position a partir de la vitesse
    void interragit(Map map); // Gere les Sauts, les retours arriere
    void gravite(float g); // Diminue la vitesse verticale
    void collision(Map map); // Gere les collisions suivant qu'elles soient verticales ou horizontales
};

#endif // PERSONNAGE_H
