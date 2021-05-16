#include "map.h"
#include "personnage.h"
#include "correspondance.h"
#include "outils.h"


void run (const Map &map, int taille_case){ // Joue le niveau

    int deltat = 10; // Regle la vitesse d'affichage

    Personnage perso (map);
    map.affiche_tout(taille_case); // Affichage de la map en entier

    while (    perso.est_vivant()
            && !perso.est_arrive() ){

        clock_t t = clock(); // Debut du timer

        noRefreshBegin();
        map.affiche(taille_case, perso); // Affichage de la map
        perso.affiche(taille_case); // Affichage du perso
        noRefreshEnd();

        if (!perso.est_sur_terre(map)){
                perso.gravite(); // Modifie la vitesse
        }
        perso.actualise_position(); // Modifie la position grace a la vitesse
        perso.collision(map); // Gere les collisions
        perso.collision_obstacle(map); // Gere les collisions avec les obstacles
        perso.cherche_etoile(map); // Collecte les etoiles
        perso.cherche_sortie(map); // Sort si touche la porte de sortie
        perso.interragit(map); // Gere les interractions avec les blocs en dessous

        while (clock() - t < deltat){  // On attend deltat
        }
    }
    map.affiche_tout(taille_case, perso); // On affiche la map a la fin
}

void affiche_grille(int H, int L, int taille_case){ // Affiche une grille_blocs de la bonne dimension pour la creation de niveau
    for (int i=0; i<=H; i++){
        drawLine(0, i*taille_case, L*taille_case, i*taille_case, BLACK);
    }
    for (int j=0; j<=L; j++){
        drawLine(j*taille_case, 0, j*taille_case, H*taille_case, BLACK);
    }
}

void affiche_boutons(int L, int taille_case, int taille_case_editeur, int bande_texte){
    int x_dep = L * taille_case;

    // Lignes de separation
    drawLine(x_dep, bande_texte, x_dep + 6.5 * taille_case_editeur, bande_texte, BLACK);
    drawLine(x_dep, bande_texte + 2 * taille_case_editeur, x_dep + 6.5 * taille_case_editeur, bande_texte + 2 * taille_case_editeur, BLACK);
    drawLine(x_dep, bande_texte + 4 * taille_case_editeur, x_dep + 6.5 * taille_case_editeur, bande_texte + 4 * taille_case_editeur, BLACK);

    // Affichage du nom de la map

    // Affichage des cases d'action
    int y_a = bande_texte + taille_case_editeur/2.0;
    for (int j = 0; j<3; j++){
        drawRect(x_dep + (1.5*j + 0.5)*taille_case_editeur, y_a, taille_case_editeur, taille_case_editeur, BLACK);
    }

    // Affichage des cases couleur
    int y_c = bande_texte + taille_case_editeur* (2.5);
    for (int j = 0; j<4; j++){
        drawRect(x_dep + (1.5*j + 0.5)*taille_case_editeur, y_c, taille_case_editeur, taille_case_editeur, BLACK);
    }
    // Affichage des cases bloc

    int y_b = bande_texte + taille_case_editeur* (4);
    for (int j = 0; j<4; j++){
        for (int i = 0; i<3; i++){
            drawRect(x_dep + (1.5*j + 0.5)*taille_case_editeur, y_b + (1.5*i + 0.5)*taille_case_editeur, taille_case_editeur, taille_case_editeur, BLACK);
        }
    }
}

bool getAction(int x, int y, int &bouton_action, int bande_texte, int L, int taille_case, int taille_case_editeur){
    int x_dep = L*taille_case;
    if ( y < bande_texte + 1.5*taille_case_editeur && y > bande_texte + 0.5*taille_case_editeur){
        float num_x = (2.0 *(x - x_dep) / float(taille_case_editeur)) / 3.0;
        if (num_x - floor(num_x) > 1/3.0
                && floor(num_x >= 0 && floor(num_x) < 4)){
            bouton_action = floor (num_x);
            return true;
        }
    }
    return false;
}

bool getCouleur(int x, int y, int &bouton_couleur, int bande_texte, int L, int taille_case, int taille_case_editeur){
    int x_dep = L*taille_case;
    if ( y < bande_texte + 3.5*taille_case_editeur && y > bande_texte + 2.5*taille_case_editeur){
        float num_x = (2.0 *(x - x_dep) / float(taille_case_editeur)) / 3.0;
        if (       num_x - floor(num_x) > 1/3.0
                && floor(num_x >= 0 && floor(num_x) < 4) ){
            bouton_couleur = floor (num_x);
            return true;
        }
    }
    return false;
}

bool getBloc(int x, int y, int &bouton_bloc, int bande_texte, int L, int taille_case, int taille_case_editeur, int nb_lignes){
    int x_dep = L*taille_case;
    int y_dep = bande_texte + 4*taille_case_editeur;
    float num_x = (2.0 *(x - x_dep) / float(taille_case_editeur)) / 3.0;
    float num_y = (2.0 *(y - y_dep) / float(taille_case_editeur)) / 3.0;
    if (       num_x - floor(num_x) > 1/3.0 && num_y - floor(num_y) > 1/3.0
            && floor(num_x >= 0 && floor(num_x) < 4
            && floor(num_y >= 0 && floor(num_y) < nb_lignes  ))){
        bouton_bloc = floor (num_x) + 4 * floor(num_y);
        return true;
    }
    return false;
}

bool placeBloc(int x, int y, int L, int H, int taille_case){
    return ( x>0 && x<L*taille_case && y>0 && y<H*taille_case);
}

void creer_map(string nom_map, int L, int H, int taille_case){
    const int taille_case_editeur = 48;
    const int bande_texte = 48;
    const int nb_lignes = 3;

    // Ouverture de la fenetre
    Window w = openWindow(L*taille_case + 6.5 * taille_case_editeur, max( H*taille_case, int(bande_texte + (9.0 * taille_case_editeur)) ) );
    setActiveWindow(w);
    // Affichage de la grille et des boutons
    affiche_grille(H, L, taille_case);
    affiche_boutons(L, taille_case, taille_case_editeur, bande_texte);
    // Creation de la map
    Map map(H,L);

    int bouton_couleur = bouton_neutre; // Initialisation de la couleur a neutre
    int n_item = 0; // Correspond au premier item d'un vecteur bouton
    int bouton_bloc = 3; // Correspond au bloc vide
    int bouton_action = 3; // Correspond a aucune action

    // Coordonnees de la souris
    int x;
    int y;

    // Memoire de la derniere case visitee
    int dernier_x_case = -1;
    int dernier_y_case = -1;

    // Mode de saisi
    bool set_bloc = false;
    bool set_couleur = false;

    bool fin = false;
    while ( ! fin ){

        getMouse(x, y);

        if ( getAction(x, y, bouton_action, bande_texte, L, taille_case, taille_case_editeur) ){
            if (bouton_action == bouton_play){
                run(map, taille_case);
                map.affiche_tout(taille_case);
                affiche_grille(H, L, taille_case);
            }
            else if (bouton_action == bouton_sauvegarder){
                map.sauvegarder(w, nom_map);
                fin = true;
            }
            else if (bouton_action == bouton_quitter){
                closeWindow(w);
                fin = true;
            }
        }

        else if (getCouleur(x, y, bouton_couleur, bande_texte, L, taille_case, taille_case_editeur)){
            set_couleur = true;
            set_bloc = false;
        }

        else if (getBloc(x, y, bouton_bloc, bande_texte, L, taille_case, taille_case_editeur, nb_lignes)){
            n_item = 0;
            set_bloc = true;
            set_couleur = false;
            bouton_couleur = bouton_neutre;
        }

        else if (placeBloc(x, y, L, H, taille_case)){
            int x_case = floor(x/taille_case);
            int y_case = floor(y/taille_case);

            // On modifie la map
            if (set_bloc){
                if (x_case == dernier_x_case && y_case == dernier_y_case){
                    n_item = (n_item + 1) % Liste_boutons[bouton_bloc].size(); // On passe a l'item suivant si on reclique sur la meme case
                }
                map.set_case(x_case, y_case, Liste_boutons[bouton_bloc][n_item]);
                dernier_x_case = x_case;
                dernier_y_case = y_case;
            }

            if (set_couleur){
                map.set_couleur(x_case, y_case, bouton_couleur);
            }

            // Dessin de la case
            map.drawCase(x_case, y_case, taille_case);
            affiche_grille(H, L, taille_case);
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
    // Etoiles
    map.set_case(42, 13, etoile);
    map.set_case(43, 14, etoile);

}

int main()
{
    int H = 30;
    int L = 55;
    int taille_case = 24;

//    openWindow(taille_case*L, taille_case*H); // Ouverture d'une fenetre de bonne dimension pour afficher la map
//    Map map(H, L);
//    construire_map_a_la_main(map, H, L);
//    run (map, taille_case);

//    creer_map("test_graphismes", L, H, taille_case); // Cree une map

    openWindow(taille_case*L, taille_case*H); // Ouverture d'une fenetre de bonne dimension pour afficher la map
    Map map(H, L);
    map.load(0); // Charge la map dans le fichier Niveaux.txt
    run (map, taille_case); // Joue le niveau

    endGraphics();
    return 0;
}
