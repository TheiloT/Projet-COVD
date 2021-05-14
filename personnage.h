#pragma once

#include "map.h"
#include "outils.h"

class Personnage {
    // Position
    float x;
    float y;
    // Vitesse
    float vx;
    float vy;
    // Tableau des quatres coins et des deux detecteurs
    Point Coins[4];
    Point Detecteurs[2];
    // Etat du personnage
    bool vivant;
    bool arrive;
    // Couleur du personnage
    int couleur;
    // Case du dernier changement de direction
    int x_change_dir, y_change_dir;

    void actualiser_coins();
    void actualiser_detecteurs();

    void sauter();
    void retourner_en_arriere(int x_d, int y_d);

    bool il_y_a_de_la_terre_en_dessous(const Map &map) const;
public:
    Personnage(const Map &map); // Initialise le personnage
    int get_couleur() const;
    bool est_vivant() const;
    bool est_arrive() const;
    bool est_sur_terre(const Map &map) const;
    void affiche(int taille_case) const; // Affiche le personnage
    void actualise_position(); // Calcul la nouvelle position a partir de la vitesse
    void collision(const Map &map); // Gere les collisions suivant qu'elles soient verticales ou horizontales
    void interragit(const Map &map); // Gere les Sauts, les retours arriere
    void gravite(); // Diminue la vitesse verticale
    void cherche_sortie(const Map &map); // Cherche la porte de sortie et actualise arrive
    void collision_obstacle(const Map &map); // gere les collisions avec les obstacles
};

