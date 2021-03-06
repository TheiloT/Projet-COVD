#pragma once

#include "outils.h"
class Personnage;


class Map
{
private:
    int H; // Hauteur
    int L; // Longueur
    MultiArray<int, 2> grille_blocs; // grille_blocs des types de blocs
    MultiArray<int, 2> grille_couleurs; // grille_blocs des couleurs
    string nom;

public:
    void drawCase(int x, int y, int taille_case) const; // Dessine la case
    void efface_etoiles_collectees(int x, int y, int taille_case, const Personnage &perso) const; // Affiche les etoiles

    Map(string nom_map, int h, int l);
    Map();

    void affiche(int taille_case, const Personnage &perso) const; // Affiche la map
    void affiche_tout(int taille_case) const; // Affiche toute la map
    void affiche_tout(int taille_case, const Personnage &perso) const; // Affiche toute la map en prenant en compte le passage du perso

    string get_nom() const; // Renvoie le nom du niveau

    int get_H() const; // Renvoie la hauteur du niveau
    int get_L() const; // Renvoie la longueur du niveau

    void set_case(int x, int y, int k); // Attribut la valeur k à la case type (x,y)
    int get_case(int x, int y) const; // Donne la valeur de la case type (x,y)

    void set_couleur(int x, int y, int k); // Attribut la valeur k à la case couleur (x,y)
    int get_couleur(int x, int y) const; // Donne la valeur de la case couleur (x,y)

    void charger(int k, const string niveau); // Charge une map
    void sauvegarder(const string niveau) const; // Sauvegarde une map
    void sauvegarder_et_ecraser(int num_map, const string niveau, int nb_niveaux) const; // Sauvegarde la map en ecrasant la map en position k
};

void dessineCase(int x, int y, int taille_case, int bloc, int couleur);
