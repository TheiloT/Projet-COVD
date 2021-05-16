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
    int N_case = 100;
    int i, j;
    while( getMouse(j, i) != 3 ){
        int x = floor(j/taille_case);
        int y = floor(i/taille_case);
        map.set_case(x, y, (map.get_case(x, y) + 1) % N_case);
        map.drawCase(x, y, taille_case);
        affiche_grille(H, L, taille_case);
    }

    if ( getMouse(j, i) == 3 ){ // On sauvegarde
        closeWindow(w);
        string const nomFichier(srcPath("Niveaux.txt"));
        ofstream flux(nomFichier.c_str(), ios::app); // flux d'ajout en fin de fichier

        if(flux)
        {
            flux << nom_map << endl;
            flux << H << " ";
            flux << L << endl;
            for (int x=0; x<L; x++){
                for (int y=0; y<H; y++){
                    flux << map.get_case(x, y) << " "; // Ecriture de grille_blocs
                }
            }
            flux << endl;
            for (int x=0; x<L; x++){
                for (int y=0; y<H; y++){
                    flux << map.get_couleur(x, y) << " "; // Ecriture de grille_couleurs
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

void run (const Map &map, int taille_case){ // Joue le niveau

    int deltat = 10; // Regle la vitesse d'affichage

    Personnage perso (map);

    while (    perso.est_vivant()
            && !perso.est_arrive() ){

        clock_t t = clock(); // Debut du timer

        noRefreshBegin();
        map.affiche(taille_case); // Affichage de la map
        perso.affiche(taille_case); // Affichage du perso
        noRefreshEnd();

        if (!perso.est_sur_terre(map)){
                perso.gravite(); // Modifie la vitesse
        }
        perso.actualise_position(); // Modifie la position grace a la vitesse
        perso.collision(map); // Gere les collisions
        perso.collision_obstacle(map); // Gere les collisions avec les obstacles
        perso.cherche_sortie(map); // Sort si touche la porte de sortie
        perso.interragit(map); // Gere les interractions avec les blocs en dessous

        while (clock() - t < deltat){  // On attend deltat
        }
    }
}

void construire_map_a_la_main(Map map, int H, int L){
    // Construction d'une map à la main
    for (int x=0; x<L; x++){
            map.set_case(x, 20, mur_non_modif); // Murs
            map.set_case(x, 16, mur_non_modif);
    }
    map.set_case(7, 20, rend_rouge); // rend rouge

    // Murs rouges
    map.set_case(11, 19, mur_non_modif);
    map.set_case(11, 18, mur_non_modif);
    map.set_case(11, 17, mur_non_modif);
    map.set_couleur(11, 19, rouge);
    map.set_couleur(11, 18, rouge);
    map.set_couleur(11, 17, rouge);

    map.set_case(3, 18, mur_non_modif);
    map.set_case(6, 17, mur_non_modif);
    map.set_case(6, 18, pic_haut); // pic
    map.set_case(30, 19, mur_non_modif);
    map.set_case(29, 20, saut); // Case de saut
    map.set_case(42, 20, saut); // Case de saut
    map.set_case(45, 16, saut); // Case de saut
    map.set_case(43, 19, pic_bas); // pic
    map.set_couleur(40, 15, rouge); // pic rouge
    map.set_case(40, 15, pic_bas);
    map.set_case(41, 16, vide); // Trou
    map.set_case(42, 16, vide); // Trou
    map.set_case(43, 16, vide); // Trou
    map.set_case(44, 16, vide); // Trou
    map.set_case(49, 16, retour_arriere); // Case de retour arrière
    // Position et couleur initiale du joueur
    map.set_case(0, 19, porte_entree_droite);
    map.set_couleur(0, 19, bleu);
    map.set_case(3, 15, pic_bas); // pic vert
    map.set_couleur(3, 15, vert);
    // Case de fin
    map.set_case(3, 17, porte_sortie);
    map.set_couleur(3, 17, vert);
    // Rend vert
    map.set_case(20, 16, rend_vert);
    // Blocs verts
    map.set_couleur(3, 16, vert);
    map.set_couleur(4, 16, vert);
    map.set_couleur(2, 16, vert);
    // Lave
    map.set_case(45, 19, mur_non_modif);
    map.set_case(46, 19, lave_partiel);
    map.set_case(47, 19, lave_partiel);
    map.set_case(48, 19, lave_partiel);
    map.set_case(49, 19, mur_non_modif);

}

int main()
{
    int H = 30;
    int L = 55;
    int taille_case = 30;
    openWindow(taille_case*L, taille_case*H); // Ouverture d'une fenetre de bonne dimension pour afficher la map

    Map map(H, L);
    construire_map_a_la_main(map, H, L);
    run (map, taille_case);

//    creer_map("test_graphismes", L, H, taille_case); // Cree et enregistre la map dans le fichier Niveaux.txt

//    Map map(H, L);
//    map.load(0); // Charge la map dans le fichier Niveaux.txt
//    run (map, taille_case); // Joue le niveau

    endGraphics();
    return 0;
}
