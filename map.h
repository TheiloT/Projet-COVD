#pragma once

#include "outils.h"
class Personnage;


class Map
{
public:
    int H; // Hauteur
    int L; // Longueur
    MultiArray<int, 2> grille_blocs; // grille_blocs des types de blocs
    MultiArray<int, 2> grille_couleurs; // grille_blocs des couleurs
    string nom;

    void drawCase(int x, int y, int taille_case) const;
    void efface_etoiles_collectees(int x, int y, int taille_case, const Personnage &perso) const; // Affiche les etoiles

    Map(string nom_map, int h, int l);
    Map();

    void affiche(int taille_case, const Personnage &perso) const; // Affiche la map
    void affiche_tout(int taille_case) const; // Affiche toute la map
    void affiche_tout(int taille_case, const Personnage &perso) const; // Affiche toute la map en prenant en compte le passage du perso

    void set_case(int x, int y, int k); // Attribut la valeur k à la case type (x,y)
    int get_case(int x, int y) const; // Donne la valeur de la case type (x,y)

    void set_couleur(int x, int y, int k); // Attribut la valeur k à la case couleur (x,y)
    int get_couleur(int x, int y) const; // Donne la valeur de la case couleur (x,y)

    void charger(int k); // Charge une map
    void sauvegarder(); // Sauvegarde une map
};

void dessineCase(int x, int y, int taille_case, int bloc, int couleur);
