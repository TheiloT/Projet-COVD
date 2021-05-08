#include <Imagine/Images.h>
using namespace Imagine;
#include "map.h"
#include "personnage.h"

int main()
{
    int H = 30;
    int L = 55;
    int taille_case = 16;
    openWindow(taille_case*L, taille_case*H); // Ouverture d'une fenetre de bonne dimension pour afficher la map

    Map map(H, L);

    // Construction d'une map
    for (int x=0; x<L; x++){
            map.set_case(x, 20, 1); // Murs
            map.set_case(x, 16, 1);
    }
    map.set_case(30, 19, 1);
    map.set_case(28, 20, 2); // Case de saut
    map.set_case(42, 20, 2); // Case de saut
    map.set_case(42, 16, 0); // Trou
    map.set_case(43, 16, 0); // Trou
    map.set_case(44, 16, 0); // Trou
    // Position initiale du joueur
    map.x0 = 0;
    map.y0 = 19;
    // Case de fin
    map.set_case(L-1, 15, 3);

    float vitesse = 2/ float(taille_case);
    Personnage perso(map.x0, map.y0, vitesse);

    int deltat = 10;
    const float g = 0.006;

    while (    perso.est_vivant()
            && !perso.est_arrive() ){

        clearWindow();
        map.affiche(taille_case); // Affichage de la map
        perso.affiche(taille_case); // Affichage du perso
        perso.gravite(g); // Modifie la vitesse
        perso.actualise_position(); // Modifie la position grace a la vitesse
        perso.collision(map); // Gere les collisions
        perso.interragit(map); // Gere les interractions avec les blocs en dessous
        milliSleep(deltat);
    }



    endGraphics();
    return 0;
}
