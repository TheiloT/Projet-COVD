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
    // Nombre d'etoiles recuperees
    int nb_etoile;

    void actualiser_coins();
    void actualiser_detecteurs();

    void sauter();
    void retourner_en_arriere(int x_d, int y_d);

    bool il_y_a_de_la_terre_en_dessous(const Map &map) const;
public:
    vector <IntPoint2> Liste_etoiles_collectees; // Vecteur des etoiles collectees

    Personnage(const Map &map); // Initialise le personnage
    float get_x() const;
    float get_y() const;
    int get_couleur() const;
    void set_couleur(int k);
    bool est_vivant() const; // Renvoie tru si le jouer est vivant
    bool est_arrive() const; // Renvoit true si le joueur a atteint la porte de sortie
    bool est_sur_terre(const Map &map) const; // Renvoie true si le perso cours sur le sol
    void affiche(int taille_case) const; // Affiche le personnage
    void actualise_position(); // Calcul la nouvelle position a partir de la vitesse
    void collision(const Map &map); // Gere les collisions suivant qu'elles soient verticales ou horizontales
    void interragit(const Map &map); // Gere les Sauts, les retours arriere
    void gravite(); // Diminue la vitesse verticale
    void cherche_sortie(const Map &map); // Cherche la porte de sortie et actualise arrive
    void collision_obstacle(const Map &map); // gere les collisions avec les obstacles
    void cherche_etoile(const Map &map); // Recolte les etoiles a proximite
    int get_nb_etoile();
};

