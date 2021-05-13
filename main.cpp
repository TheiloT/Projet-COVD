#include <Imagine/Images.h>
using namespace Imagine;
#include "map.h"
#include "personnage.h"

#include<iostream>
#include <fstream>

void affiche_grille(int H, int L, int taille_case){ // Affiche une grille de la bonne dimension pour la creation de niveau
    for (int i=0; i<=H; i++){
        drawLine(0, i*taille_case, L*taille_case, i*taille_case, BLACK);
    }
    for (int j=0; j<=L; j++){
        drawLine(j*taille_case, 0, j*taille_case, H*taille_case, BLACK);
    }
}

void creer_map(string nom_map, int L, int H, int taille_case){
    Window w = openWindow(L*taille_case, H*taille_case);
    setActiveWindow(w);
    affiche_grille(H, L, taille_case);
    Map map(H,L);
    int N_case = 5;
    int i, j;
    while( getMouse(j, i) != 3 ){
        int x = floor(j/taille_case);
        int y = floor(i/taille_case);
        map.set_case(x, y, (map.get_case(x, y) + 1) % N_case);
        map.drawCase(x, y, taille_case);
    }

    if ( getMouse(j, i) == 3 ){ // On sauvegarde
        closeWindow(w);
        string const nomFichier("C:/Ecole_des_Ponts/Atelier de programmation/Projet-COVD/Niveaux.txt");
        ofstream flux(nomFichier.c_str(), ios::app); // flux d'ajout en fin de fichier

        if(flux)
        {
            flux << nom_map << endl;
            flux << H << " ";
            flux << L << endl;
            for (int x=0; x<L; x++){
                for (int y=0; y<H; y++){
                    flux << map.get_case(x, y) << " ";
                }
            }
        }
        else
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
        }
        return;
        }

    else // On ne sauvegarde pas
        return;
}

void run (Personnage perso, Map map, int taille_case, float g, int deltat){ // Joue le niveau
    while (    perso.est_vivant()
            && !perso.est_arrive() ){

        map.affiche(taille_case); // Affichage de la map
        perso.affiche(taille_case); // Affichage du perso
        perso.gravite(g); // Modifie la vitesse
        perso.actualise_position(); // Modifie la position grace a la vitesse
        perso.collision(map); // Gere les collisions
        perso.interragit(map); // Gere les interractions avec les blocs en dessous
        milliSleep(deltat);
    }
}

int main()
{
    int H = 30;
    int L = 55;
    int taille_case = 16;
    openWindow(taille_case*L, taille_case*H); // Ouverture d'une fenetre de bonne dimension pour afficher la map

    // Construction d'une map à la main
    Map map(H, L);
    for (int x=0; x<L; x++){
            map.set_case(x, 20, 1); // Murs
            map.set_case(x, 16, 1);
    }
    map.set_case(5, 18, 1);
    map.set_case(30, 19, 1);
    map.set_case(29, 20, 2); // Case de saut
    map.set_case(43, 20, 2); // Case de saut
    map.set_case(45, 16, 2); // Case de saut
    map.set_case(42, 16, 0); // Trou
    map.set_case(43, 16, 0); // Trou
    map.set_case(44, 16, 0); // Trou
    map.set_case(49, 16, 4); // Case de retour arrière
    // Position initiale du joueur
    map.x0 = 0;
    map.y0 = 19;
    // Case de fin
    map.set_case(1, 15, 3);

    float vitesse = 2/ float(taille_case);
    int deltat = 14;
    const float g = 0.02;

//    Personnage perso(map.x0, map.y0, vitesse);
//    run (perso, map, taille_case, g, deltat);

//    Creer_map("Ma_map", L, H, taille_case); // Cree et enregistre la map dans le fichier Niveaux.txt

    map.load(3); // Charge la map dans le fichier Niveaux.txt
    map.affiche(18);
    map.x0 = 0;
    map.y0 = 18;
    Personnage perso(map.x0, map.y0, vitesse);
    run (perso, map, taille_case, g, deltat); // Joue le niveau

    endGraphics();
    return 0;
}
