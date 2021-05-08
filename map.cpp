#include "map.h"

Map::Map(int h, int l)
{
    H = h;
    L = l;
    grille = MultiArray<int, 2> (L, H);
    grille.fill(0);
}

void Map::drawCase(int x, int y, int taille_case){
    if (grille(x,y) == 1){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, BLACK); // Le sol en noir
    }

    if (grille(x,y) == 2){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, GREEN); // Les sauts en vert
    }

    if (grille(x,y) == 3){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, YELLOW); // La fin en jaune
    }
}

void Map::affiche(int taille_case){
    for (int x=0; x<L; x++){
        for (int y=0; y<H; y++){
            drawCase(x, y, taille_case);
        }
    }
}

void Map::set_case(int x, int y, int k){
    grille(x,y) = k;
}

int Map::get_case(int x, int y){
    return grille(x, y);
}
