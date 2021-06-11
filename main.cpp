#include "menus.h"

int main()
{
    initRandom(); // On initialise le hasard, notamment pour les appels à couleur_au_hasard
    int taille_case = 28; // taille des cases

    lancer_menu(taille_case); // Lancement du jeu
    endGraphics();

    return 0;
}
