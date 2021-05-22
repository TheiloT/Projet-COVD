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
        drawLine(0, i*taille_case, L*taille_case, i*taille_case, BLACK, 2);
    }
    for (int j=0; j<=L; j++){
        drawLine(j*taille_case, 0, j*taille_case, H*taille_case, BLACK, 2);
    }
}

void drawAction(int x, int y, int k, int taille_case_editeur){
    if (k == bouton_play){
        int xa = x + int (0.25*taille_case_editeur);
        int xb = x + int (0.25*taille_case_editeur);
        int xc = x + int (0.85*taille_case_editeur);
        int ya = y + int (0.80*taille_case_editeur);
        int yb = y + int (0.20*taille_case_editeur);
        int yc = y + int (0.5*taille_case_editeur);
        int coord_triangle[6] = {xa, ya, xb, yb, xc, yc};
        fillRect(x, y, taille_case_editeur, taille_case_editeur, RED);
        fillPoly(coord_triangle, 3, WHITE);
        drawPoly(coord_triangle, 3, BLACK, 2);
    }

    else if (k == bouton_sauvegarder){
        string s = "S";
        drawString(x + int(0.2*taille_case_editeur), y + int(0.85*taille_case_editeur), s, BLACK, int (0.5*taille_case_editeur));
    }

    else if (k == bouton_quitter){
        int d = int (0.2 * taille_case_editeur);
        fillRect(x, y, taille_case_editeur, taille_case_editeur, RED);
        drawLine(x + 4 + d, y + 4 + d, x + taille_case_editeur - 4 - d, y + taille_case_editeur - 4 - d, WHITE, 8);
        drawLine(x + taille_case_editeur - 4 - d, y + 4 + d, x + 4 + d, y + taille_case_editeur - 4 - d, WHITE, 8);
    }
}

void drawBouton(int x, int y, int k, int taille_case_editeur){
    int marge = int (taille_case_editeur/8.0);
    dessineCase(x + marge, y + marge, taille_case_editeur - 2*marge, k, neutre);
}

//void affiche_boutons(int L, int taille_case, int taille_case_editeur, int bande_texte, string nom_map){

//    int x_dep = L * taille_case;

//    // Lignes de separation
//    drawLine(x_dep, bande_texte, x_dep + 6.5 * taille_case_editeur, bande_texte, BLACK, 2);
//    drawLine(x_dep, bande_texte + 2 * taille_case_editeur, x_dep + 6.5 * taille_case_editeur, bande_texte + 2 * taille_case_editeur, BLACK, 2);
//    drawLine(x_dep, bande_texte + 4 * taille_case_editeur, x_dep + 6.5 * taille_case_editeur, bande_texte + 4 * taille_case_editeur, BLACK, 2);

//    // Affichage du nom de la map
//    int dx = int (3.25*taille_case_editeur - taille_case_editeur * 0.125 * nom_map.size() );
//    int dy = int (0.5 * bande_texte - 0.125 * taille_case_editeur );
//    drawString(x_dep + dx, bande_texte - dy, nom_map, BLACK, int (taille_case_editeur * 0.25));

//    // Affichage des cases d'action
//    int y_a = bande_texte + taille_case_editeur/2.0;
//    for (int j = 0; j<3; j++){
//        int x = x_dep + (1.5*j + 0.5)*taille_case_editeur;
//        int y = y_a;
//        drawAction(x, y, j, taille_case_editeur);
//        drawRect(x, y, taille_case_editeur, taille_case_editeur, BLACK, 2);
//    }

//    // Affichage des cases couleur
//    int y_c = bande_texte + taille_case_editeur* (2.5);
//    for (int j = 0; j<4; j++){
//        int x = x_dep + (1.5*j + 0.5)*taille_case_editeur;
//        int y = y_c;
//        fillRect(x, y, taille_case_editeur, taille_case_editeur, couleur_int_vers_color.at(j));
//        drawRect(x, y, taille_case_editeur, taille_case_editeur, BLACK, 2);
//    }

//    // Affichage des cases bloc
//    int y_b = bande_texte + taille_case_editeur* (4);
//    for (int j = 0; j<4; j++){
//        for (int i = 0; i<3; i++){
//            int x = x_dep + (1.5*j + 0.5)*taille_case_editeur;
//            int y = y_b + (1.5*i + 0.5)*taille_case_editeur;
//            drawBouton(x, y, Liste_boutons[j + 4*i][0], taille_case_editeur);
//            drawRect(x, y, taille_case_editeur, taille_case_editeur, BLACK, 2);
//        }
//    }
//}

void affiche_boutons(int L, int taille_case, int taille_case_editeur, int bande_texte, string nom_map){

    int x_dep = L * taille_case;

    // Lignes de separation
    drawLine(x_dep, bande_texte, x_dep + 6.5 * taille_case_editeur, bande_texte, BLACK, 2);
    drawLine(x_dep, bande_texte + 2 * taille_case_editeur, x_dep + 6.5 * taille_case_editeur, bande_texte + 2 * taille_case_editeur, BLACK, 2);

    // Affichage du nom de la map
    int dx = int (3.25*taille_case_editeur - taille_case_editeur * 0.125 * nom_map.size() );
    int dy = int (0.5 * bande_texte - 0.125 * taille_case_editeur );
    drawString(x_dep + dx, bande_texte - dy, nom_map, BLACK, int (taille_case_editeur * 0.25));

    // Affichage des cases d'action
    int y_a = bande_texte + taille_case_editeur/2.0;
    int x = x_dep + 0.5*taille_case_editeur;
    int y = y_a;
    drawAction(x, y, 0, taille_case_editeur);
    drawRect(x, y, taille_case_editeur, taille_case_editeur, BLACK, 2);
    x = x_dep + (1.5 + 0.5)*taille_case_editeur;
    y = y_a;
    drawAction(x, y, 2, taille_case_editeur);
    drawRect(x, y, taille_case_editeur, taille_case_editeur, BLACK, 2);

    // Affichage des cases bloc
    int y_b = bande_texte + taille_case_editeur* (2);
    for (int j = 0; j<4; j++){
        for (int i = 0; i<3; i++){
            int x = x_dep + (1.5*j + 0.5)*taille_case_editeur;
            int y = y_b + (1.5*i + 0.5)*taille_case_editeur;
            drawBouton(x, y, Liste_boutons[j + 4*i][0], taille_case_editeur);
            drawRect(x, y, taille_case_editeur, taille_case_editeur, BLACK, 2);
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

bool getAction_joueur(int x, int y, int &bouton_action, int bande_texte, int L, int taille_case, int taille_case_editeur){
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

void efface_tous_niveaux(){ // Efface le Niveaux.txt

    string const nomFichier(srcPath("Niveaux.txt"));
    ofstream fichier(nomFichier.c_str() ); // flux d'ajout en fin de fichier
}

void efface_niveau (int k, int nb_niveaux){
    vector <Map> Liste_maps;

    for (int i=0; i<nb_niveaux && i!=k; i++){
        Map map;
        map.charger(i);
        Liste_maps.push_back(map);
    }

    efface_tous_niveaux();

    for (int i=0; i<nb_niveaux-1; i++){
        Map map = Liste_maps[i];
        map.sauvegarder();
    }

}

void creer_map(string nom_map, int L, int H, int taille_case){
    const int taille_case_editeur = 2*taille_case;
    const int bande_texte = taille_case_editeur;
    const int nb_lignes = 3;

    // Ouverture de la fenetre
    Window w = openWindow(L*taille_case + 6.5 * taille_case_editeur, max( H*taille_case, int(bande_texte + (9.0 * taille_case_editeur)) ) );
    setActiveWindow(w);
    // Affichage de la grille et des boutons
    affiche_grille(H, L, taille_case);
    affiche_boutons(L, taille_case, taille_case_editeur, bande_texte, nom_map);
    // Creation de la map
    Map map(nom_map, H,L);

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
                map.sauvegarder();
                closeWindow(w);
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
            else{
                    n_item = 0; // On repasse au premier item si on ne reclique pas sur la même case
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

void construire_map_a_la_main(Map map){

    // Construction d'une map à la main
    for (int x=0; x<55; x++){
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

void jouer(Map map, int taille_case) {
    const int L = map.L;
    const int H = map.H;
    const string nom = map.nom;

    std::map<int, int> blocs_disponibles;
    for (int k=0; k<int(effets.size()); k++)
        blocs_disponibles[effets[k]] = 0;

    // Préparation de la map pour le joueur

    int k; // case courante
    for (int i=0; i<H; i++) {
        for (int j=0; j<L; j++) {
            k = map.get_case(i, j);
            if (est_dans(k, effets)) {
                map.set_case(i, j, mur_modif);
                blocs_disponibles[k] ++;
            }
        }
    }

    // Le jeu

    const int taille_case_editeur = 2*taille_case;
    const int bande_texte = taille_case_editeur;
    const int nb_lignes = 3;

    // Ouverture de la fenetre
    Window w = openWindow(L*taille_case + 6.5 * taille_case_editeur, max( H*taille_case, int(bande_texte + (9.0 * taille_case_editeur)) ) );
    setActiveWindow(w);
    // Affichage de la grille et des boutons
    affiche_grille(H, L, taille_case);
    affiche_boutons(L, taille_case, taille_case_editeur, bande_texte, nom);

    int n_item = 0; // Correspond au premier item d'un vecteur bouton
    int bouton_action = 3; // Correspond a aucune action

    // Coordonnees de la souris
    int x;
    int y;

    // Memoire de la derniere case visitee
    int dernier_x_case = -1;
    int dernier_y_case = -1;

    // Mode de saisi

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
                map.sauvegarder();
                closeWindow(w);
                fin = true;
            }
            else if (bouton_action == bouton_quitter){
                closeWindow(w);
                fin = true;
            }
        }

        else if (placeBloc(x, y, L, H, taille_case)){
            int x_case = floor(x/taille_case);
            int y_case = floor(y/taille_case);

            // On modifie la map
            if (set_bloc){
                if (x_case == dernier_x_case && y_case == dernier_y_case){
                    n_item = (n_item + 1) % Liste_boutons[bouton_bloc].size(); // On passe a l'item suivant si on reclique sur la meme case
                }
            else{
                    n_item = 0; // On repasse au premier item si on ne reclique pas sur la même case
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

// ========== Fonctions du menu ==========

void lancer_menu() {

}

void menu_categorie_niveau(){

}

void menu_creation_niveau(){

}

void menu_options(){}

void menu_quitter(){}

// ========================================

void selection_niveau(bool mode_aventure) {} // reminder : le nombre de niveau est recompter en parcourant le .txt





int main()
{
    int taille_case = 30;

//    openWindow(taille_case*55, taille_case*22); // Ouverture d'une fenetre de bonne dimension pour afficher la map
//    string nom_map = "Map_a_la_mano";
//    Map map(nom_map, 21, 55);
//    construire_map_a_la_main(map);
//    run (map, taille_case);

      lancer_menu();

    int L = 30;
    int H = 20;
    creer_map("Ma_map_nulle", L, H, taille_case); // Cree une map

//    Map map;
//    map.charger(0); // Charge la map dans le fichier Niveaux.txt
//    openWindow(taille_case*map.L, taille_case*map.H); // Ouverture d'une fenetre de bonne dimension pour afficher la map
//    run (map, taille_case); // Joue le niveau

//    int nb_niveau = 2;
//    efface_niveau(1, nb_niveau);

    endGraphics();
    return 0;
}
