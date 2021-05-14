#include "map.h"
#include "personnage.h"
#include "correspondance.h"

void affiche_grille(int H, int L, int taille_case){ // Affiche une grille_blocs de la bonne dimension pour la creation de niveau
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
    int N_case = 11;
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
            flux << endl;
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

void run (const Map &map, int taille_case, float g, int deltat, float vitesse){ // Joue le niveau

    Personnage perso (map, vitesse);

    while (    perso.est_vivant()
            && !perso.est_arrive() ){

        noRefreshBegin();
        map.affiche(taille_case); // Affichage de la map
        perso.affiche(taille_case); // Affichage du perso
        noRefreshEnd();

        if (!perso.est_sur_terre(map)){
                perso.gravite(g); // Modifie la vitesse
        }
        perso.actualise_position(); // Modifie la position grace a la vitesse
        perso.collision(map); // Gere les collisions
        perso.cherche_sortie(map); // Sort si touche la porte de sortie
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
            map.set_case(x, 20, mur_non_modif); // Murs
            map.set_case(x, 16, mur_non_modif);
    }
    map.set_case(5, 18, mur_non_modif);
    map.set_case(30, 19, mur_non_modif);
    map.set_case(29, 20, saut); // Case de saut
    map.set_case(42, 20, saut); // Case de saut
    map.set_case(45, 16, saut); // Case de saut
    map.set_case(41, 16, vide); // Trou
    map.set_case(42, 16, vide); // Trou
    map.set_case(43, 16, vide); // Trou
    map.set_case(44, 16, vide); // Trou
    map.set_case(49, 16, retour_arriere); // Case de retour arrière
    // Position initiale du joueur
    map.set_case(0, 19, porte_entree);
    // Case de fin
    map.set_case(1, 15, porte_sortie);

    float vitesse = 2/ float(taille_case);
    int deltat = 30;
    const float g = 0.02;

    run (map, taille_case, g, deltat, vitesse);

//    creer_map("Ma_map", L, H, taille_case); // Cree et enregistre la map dans le fichier Niveaux.txt

//    map.load(4); // Charge la map dans le fichier Niveaux.txt
//    run (map, taille_case, g, deltat, vitesse); // Joue le niveau

    endGraphics();
    return 0;
}
