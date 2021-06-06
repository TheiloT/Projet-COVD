#include "map.h"
#include "personnage.h"
#include "correspondance.h"
#include "niveaux.h"
#include "outils.h"

void ecris_dans_la_case(int x, int y, int w, int h, string message, int taille_police, Color couleur=BLACK){
    int dx = int ( (w - taille_police * 0.88*message.size()) /2 );
    int dy = int ( (h - taille_police) /2 );
    drawString(x + dx, y + h - dy, message, couleur, taille_police);
}
//taille_police * 0.88*message.size()

bool run (const Map &map, int taille_case){ // Joue le niveau

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

        while (clock() - t < deltat){  // On attend que le temps passe dans la boucle soit deltat
        }
    }
    map.affiche_tout(taille_case, perso); // On affiche la map a la fin
    return(perso.est_arrive());
}

void affiche_grille(int H, int L, int taille_case){ // Affiche une grille_blocs de la bonne dimension pour la creation de niveau
    for (int i=0; i<=H; i++){
        drawLine(0, i*taille_case, L*taille_case, i*taille_case, BLACK, 2);
    }
    for (int j=0; j<=L; j++){
        drawLine(j*taille_case, 0, j*taille_case, H*taille_case, BLACK, 2);
    }
}

void drawAction(int x, int y, int k, int taille_case){
    if (k == bouton_play){
        int xa = x + int (0.25*taille_case);
        int xb = x + int (0.25*taille_case);
        int xc = x + int (0.85*taille_case);
        int ya = y + int (0.80*taille_case);
        int yb = y + int (0.20*taille_case);
        int yc = y + int (0.5*taille_case);
        int coord_triangle[6] = {xa, ya, xb, yb, xc, yc};
        fillRect(x, y, taille_case, taille_case, RED);
        fillPoly(coord_triangle, 3, WHITE);
        drawPoly(coord_triangle, 3, BLACK, 2);
    }

    else if (k == bouton_sauvegarder){
        string s = "S";
        drawString(x + int(0.2*taille_case), y + int(0.85*taille_case), s, BLACK, int (0.5*taille_case));
    }

    else if (k == bouton_quitter){
        int d = int (0.2 * taille_case);
        fillRect(x, y, taille_case, taille_case, RED);
        drawLine(x + 4 + d, y + 4 + d, x + taille_case - 4 - d, y + taille_case - 4 - d, WHITE, 8);
        drawLine(x + taille_case - 4 - d, y + 4 + d, x + 4 + d, y + taille_case - 4 - d, WHITE, 8);
    }
    else if (k == bouton_reset){
        string r = "R";
        drawString(x + int(0.2*taille_case), y + int(0.85*taille_case), r, BLACK, int (0.5*taille_case));
    }
}

void drawBouton(int x, int y, int k, int taille_case_editeur){
    int marge = int (taille_case_editeur/8.0);
    dessineCase(x + marge, y + marge, taille_case_editeur - 2*marge, k, neutre);
}

void affiche_boutons(int H, int L, int taille_case, int taille_case_editeur, int bande_texte, string nom_map){

    int x_dep = L * taille_case;

    // Lignes de separation
    drawLine(x_dep, bande_texte, x_dep + 6.5 * taille_case_editeur, bande_texte, BLACK, 2);
    drawLine(x_dep, bande_texte + 2 * taille_case_editeur, x_dep + 6.5 * taille_case_editeur, bande_texte + 2 * taille_case_editeur, BLACK, 2);
    drawLine(x_dep, bande_texte + 4 * taille_case_editeur, x_dep + 6.5 * taille_case_editeur, bande_texte + 4 * taille_case_editeur, BLACK, 2);

    // Affichage du nom de la map
    int dx = int (3.25*taille_case_editeur - taille_case_editeur * 0.125 * nom_map.size() );
    int dy = int (0.5 * bande_texte - 0.125 * taille_case_editeur );
    drawString(x_dep + dx, bande_texte - dy, nom_map, BLACK, int (taille_case_editeur * 0.25));

    // Affichage des cases d'action
    int y_a = bande_texte + taille_case_editeur/2.0;
    for (int j = 0; j<3; j++){
        int x = x_dep + (1.5*j + 0.5)*taille_case_editeur;
        int y = y_a;
        drawAction(x, y, j, taille_case_editeur);
        drawRect(x, y, taille_case_editeur, taille_case_editeur, BLACK, 2);
    }

    // Affichage des cases couleur
    int y_c = bande_texte + taille_case_editeur* (2.5);
    for (int j = 0; j<4; j++){
        int x = x_dep + (1.5*j + 0.5)*taille_case_editeur;
        int y = y_c;
        fillRect(x, y, taille_case_editeur, taille_case_editeur, couleur_int_vers_color.at(j));
        drawRect(x, y, taille_case_editeur, taille_case_editeur, BLACK, 2);
    }

    // Affichage des cases bloc
    int y_b = bande_texte + taille_case_editeur* (4);
    for (int j = 0; j<4; j++){
        for (int i = 0; i<3; i++){
            int x = x_dep + (1.5*j + 0.5)*taille_case_editeur;
            int y = y_b + (1.5*i + 0.5)*taille_case_editeur;
            drawBouton(x, y, Liste_boutons[j + 4*i][0], taille_case_editeur);
            drawRect(x, y, taille_case_editeur, taille_case_editeur, BLACK, 2);

        }
    }
}

void affiche_boutons_joueur(int L, int H, int taille_case, int taille_case_editeur, int bande_texte, string nom_map, std::map<int, int> blocs_disponibles){

    int x_dep = L * taille_case;

    // Lignes de separation
    drawLine(x_dep, bande_texte, x_dep + 6.5 * taille_case_editeur, bande_texte, BLACK, 2);
    drawLine(x_dep, bande_texte + 2 * taille_case_editeur, x_dep + 6.5 * taille_case_editeur, bande_texte + 2 * taille_case_editeur, BLACK, 2);
    drawLine(x_dep+1, 0, x_dep+1, H*taille_case,BLACK, 2);

    // Affichage du nom de la map
    int dx = int (3.25*taille_case_editeur - taille_case_editeur * 0.125 * nom_map.size() );
    int dy = int (0.5 * bande_texte - 0.125 * taille_case_editeur );
    drawString(x_dep + dx, bande_texte - dy, nom_map, BLACK, int (taille_case_editeur * 0.25));

    // Affichage des cases d'action
    int y_a = bande_texte + taille_case_editeur/2.0;
    for (int j = 0; j<3; j++){
        int x = x_dep + (1.5*j + 0.5)*taille_case_editeur;
        int y = y_a;
        if (j == 1) drawAction(x, y, 3, taille_case_editeur);
        else drawAction(x, y, j, taille_case_editeur);
        drawRect(x, y, taille_case_editeur, taille_case_editeur, BLACK, 2);
    }

    // Affichage des cases effets
    int y_b = bande_texte + taille_case_editeur* (2);
    for (int j = 0; j<4; j++){
        for (int i = 0; i<2; i++){
            int x = x_dep + (1.5*j + 0.5)*taille_case_editeur;
            int y = y_b + (1.5*i + 0.5)*taille_case_editeur;
            drawBouton(x, y, effets[j + 4*i], taille_case_editeur);
            drawRect(x, y, taille_case_editeur, taille_case_editeur, BLACK, 2);
            // Affichage du "stock" : le nombre d'effets de ce type disponibles
            int xs = x + 2*taille_case_editeur/3;
            int ys = y + 2*taille_case_editeur/3;
            int w = taille_case_editeur/3;
            int h = taille_case_editeur/3;
            int stock = blocs_disponibles[effets[j + 4*i]];
            fillRect(xs, ys, w, h, WHITE);
            drawRect(xs, ys, w-1, h-1, BLACK);
            if (stock==0) ecris_dans_la_case(xs, ys, w, h, to_string(stock), taille_case_editeur/8, RED);
            else ecris_dans_la_case(xs, ys, w, h, to_string(stock), taille_case_editeur/8);
        }
    }
    // Affichage du mur non modifiable
    int x = x_dep + (1.5*3 + 0.5)*taille_case_editeur;
    int y = y_b + (1.5*1 + 0.5)*taille_case_editeur;
    fillRect(x, y, taille_case_editeur, taille_case_editeur, WHITE);
    drawBouton(x, y, mur_modif, taille_case_editeur);
    drawRect(x, y, taille_case_editeur, taille_case_editeur, BLACK, 2);
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
            int numero_case=floor(num_x);
            bouton_action = (numero_case == 1) ? 3 : numero_case; // Si floor(num_x) correspond à "sauvergarder", on change pour "reset"
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

bool getEffet(int x, int y, int &bouton_effet, int bande_texte, int L, int taille_case, int taille_case_editeur, int nb_lignes){
    int x_dep = L*taille_case;
    int y_dep = bande_texte + 2*taille_case_editeur;
    float num_x = (2.0 *(x - x_dep) / float(taille_case_editeur)) / 3.0;
    float num_y = (2.0 *(y - y_dep) / float(taille_case_editeur)) / 3.0;
    if (       num_x - floor(num_x) > 1/3.0 && num_y - floor(num_y) > 1/3.0
            && floor(num_x >= 0 && floor(num_x) < 4
            && floor(num_y >= 0 && floor(num_y) < nb_lignes  ))){
        int numero_case = floor (num_x) + 4 * floor(num_y);
        if (numero_case==7) bouton_effet=mur_modif;
        else bouton_effet = effets[numero_case];
        return true;
    }
    return false;
}

bool placeBloc(int x, int y, int L, int H, int taille_case){
    return ( x>0 && x<L*taille_case && y>0 && y<H*taille_case);
}

void creer_map(string nom_map, int L, int H, int taille_case, bool editer = false, Map map_a_editer = Map("",0,0), int num_map = -1, int nb_niveaux = -1, const string niveau = "Niveaux_perso.txt"){
    const int taille_case_editeur = 2*taille_case;
    const int bande_texte = taille_case_editeur;
    const int nb_lignes = 3;

    // Ouverture de la fenetre
    Window w = openWindow(L*taille_case + 6.5 * taille_case_editeur, max( H*taille_case, int(bande_texte + (9.0 * taille_case_editeur)) ) );
    setActiveWindow(w);

    if (!editer){ // Si on part de zero
        // Creation de la map
        map_a_editer = Map(nom_map, H,L);
    }

    map_a_editer.affiche_tout(taille_case); // Affichage de la map
    // Affichage de la grille et des boutons
    affiche_boutons(H, L, taille_case, taille_case_editeur, bande_texte, nom_map);
    affiche_grille(H, L, taille_case);

    int bouton_couleur = bouton_neutre; // Initialisation de la couleur a neutre
    int n_item = 0; // Correspond au premier item d'un vecteur bouton
    int bouton_bloc = 3; // Correspond au bloc vide
    int bouton_action = 4; // Correspond a aucune action

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
                drawLine(L * taille_case+1, 0, L * taille_case+1, H*taille_case,BLACK, 1); // Correction bug affichage
                run(map_a_editer, taille_case);
                map_a_editer.affiche_tout(taille_case);
                drawLine(L * taille_case+1, 0, L * taille_case+1, H*taille_case,WHITE, 1); // Correction bug affichage
                affiche_grille(H, L, taille_case);
            }
            else if (bouton_action == bouton_sauvegarder){
                if (!editer){
                    map_a_editer.sauvegarder(niveau);
                    closeWindow(w);
                    fin = true;
                }
                else{
                    map_a_editer.sauvegarder_et_ecraser(num_map, niveau, nb_niveaux);
                    closeWindow(w);
                    fin = true;
                }
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

            map_a_editer.set_case(x_case, y_case, Liste_boutons[bouton_bloc][n_item]);
            dernier_x_case = x_case;
            dernier_y_case = y_case;
            }

            if (set_couleur){
                map_a_editer.set_couleur(x_case, y_case, bouton_couleur);
            }

            // Dessin de la case
            map_a_editer.drawCase(x_case, y_case, taille_case);
            affiche_grille(H, L, taille_case);
        }
    }
}

void editer_map(Map map, int taille_case, int num_map, int nb_niveaux, string niveau = "Niveaux_perso"){
    creer_map (map.nom, map.L, map.H, taille_case, true, map, num_map, nb_niveaux, niveau);
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

void prepare_map(Map map, int L, int H, std::map<int, int> &blocs_disponibles) {
    int k; // case courante
    for (int i=0; i<H; i++) {
        for (int j=0; j<L; j++) {
            k = map.get_case(j, i);
            if (est_dans(k, effets)) {
                map.set_case(j, i, mur_modif);
                blocs_disponibles[k] ++;
            }
        }
    }
}

void clignote(int x, int y, int taille_case){
    fillRect(x*taille_case, y*taille_case, taille_case, taille_case, RED);
    milliSleep(250);
}

void jouer(Map map, int taille_case) {
    const int L = map.L;
    const int H = map.H;
    const string nom = map.nom;

    std::map<int, int> blocs_disponibles;
    for (int k=0; k<int(effets.size()); k++)
        blocs_disponibles[effets[k]] = 0;

    prepare_map(map, L, H, blocs_disponibles);

    const int taille_case_editeur = 2*taille_case;
    const int bande_texte = taille_case_editeur;
    const int nb_lignes = 2;

    // Ouverture de la fenetre
    Window w = openWindow(L*taille_case + 6.5 * taille_case_editeur, max( H*taille_case, int(bande_texte + (9.0 * taille_case_editeur)) ) );
    setActiveWindow(w);
    // Affichage de la map, de la grille et des boutons
    map.affiche_tout(taille_case);
    // affiche_grille(H, L, taille_case);
    affiche_boutons_joueur(L, H, taille_case, taille_case_editeur, bande_texte, nom, blocs_disponibles);

    int bouton_action = 4; // Correspond a aucune action
    int bouton_effet = 7; // Correspond au mur modifiable

    // Coordonnees de la souris
    int x;
    int y;

    bool fin = false;
    while ( ! fin ){

        getMouse(x, y);

        if (getEffet(x, y, bouton_effet, bande_texte, L, taille_case, taille_case_editeur, nb_lignes));

        else if ( getAction_joueur(x, y, bouton_action, bande_texte, L, taille_case, taille_case_editeur) ){
            if (bouton_action == bouton_play){
                fin = run(map, taille_case);
                map.affiche_tout(taille_case);
//                affiche_grille(H, L, taille_case);
                if (fin){
                    closeWindow(w); // Fonction de fin a rajouter
                }
            }
            else if (bouton_action == bouton_reset){
                prepare_map(map, L, H, blocs_disponibles);
                map.affiche_tout(taille_case);
//                affiche_grille(H, L, taille_case);
                affiche_boutons_joueur(L, H, taille_case, taille_case_editeur, bande_texte, nom, blocs_disponibles);
            }
            else if (bouton_action == bouton_quitter){
                closeWindow(w);
                fin = true;
            }
        }

        else if (placeBloc(x, y, L, H, taille_case)){
            int x_case = floor(x/taille_case);
            int y_case = floor(y/taille_case);
            int bloc = map.get_case(x_case, y_case);

            bool modifiable = bloc==mur_modif || est_dans(bloc, effets);
            bool stock_suffisant = (blocs_disponibles[bouton_effet] > 0 || bouton_effet == mur_modif);

            // On modifie la map
            if (modifiable && stock_suffisant){
                map.set_case(x_case, y_case, bouton_effet);
                blocs_disponibles[bloc] ++;
                blocs_disponibles[bouton_effet] --;
            }
            else clignote(x_case, y_case, taille_case);

            // Dessin de la case
            map.drawCase(x_case, y_case, taille_case);
//            affiche_grille(H, L, taille_case);
            affiche_boutons_joueur(L, H, taille_case, taille_case_editeur, bande_texte, nom, blocs_disponibles);
        }
    }
}

// ========== Fonctions du menu ==========

void draw_bouton_etiquette(int x, int y, int taille_bouton, int bouton) {
    if (bouton == 0) { // dessine le bouton d'edition
        fillRect(x, y, taille_bouton, taille_bouton, YELLOW);
        drawRect(x, y, taille_bouton, taille_bouton, WHITE, 2);
        drawString(x + int(0.2*taille_bouton), y + int(0.85*taille_bouton), "E", BLACK, int (0.5*taille_bouton));
    }
    if (bouton == 1) { // dessine le bouton de deletion
        fillRect(x, y, taille_bouton, taille_bouton, RED);
        drawRect(x, y, taille_bouton, taille_bouton, WHITE, 2);
        drawString(x + int(0.23*taille_bouton), y + int(0.85*taille_bouton), "X", BLACK, int (0.5*taille_bouton));
    }
    if (bouton == 2) { // dessine le bouton jouer
        fillRect(x, y, taille_bouton, taille_bouton, GREEN);
        drawRect(x, y, taille_bouton, taille_bouton, WHITE, 2);

        // triangle
        int xa = x + taille_bouton/5;
        int xb = x + taille_bouton/5;
        int xc = x + 4*taille_bouton/5;

        int ya = y + taille_bouton/5;
        int yb = y + 4*taille_bouton/5;
        int yc = y + taille_bouton/2;

        int coord_triangle[6] = {xa, ya, xb, yb, xc, yc};
        fillPoly(coord_triangle, 3, BLACK);
    }
}

void draw_etiquette(int x, int y, int k, int largeur_etiquette, int hauteur_etiquette, int largeur_texte_etiquette,
                    string nom_niveau, int taille_bouton, int marge_bouton, bool mode_perso) { // Dessine une etiquette

    Color Couleurs[4] = {RED, BLUE, GREEN, PURPLE};
    drawRect(x, y, largeur_etiquette, hauteur_etiquette, WHITE, 2);
    int taille_police = hauteur_etiquette/6;
    ecris_dans_la_case(x, y, largeur_texte_etiquette, hauteur_etiquette, nom_niveau, taille_police, Couleurs[k % 4]);
    //drawLine(x+largeur_texte_etiquette, y, x+largeur_texte_etiquette, y+hauteur_etiquette, WHITE);
    int x_boutons = x + largeur_texte_etiquette;
    int y_boutons = y + (hauteur_etiquette-taille_bouton)/2;
    int pas = taille_bouton + marge_bouton;
    if (mode_perso) {
        for (int i=0; i<3; i++)
            draw_bouton_etiquette(marge_bouton + x_boutons + i*pas, y_boutons, taille_bouton, i);
    }
    else draw_bouton_etiquette(x_boutons + 2*pas, y_boutons, taille_bouton, 2);
}

void draw_bouton_bas(int x, int y, int taille_bouton, int bouton) {
    if (bouton == 0) { // dessine le bouton de retour
        drawRect(x, y, taille_bouton, taille_bouton, WHITE, 2);
        drawString(x + int(0.23*taille_bouton), y + int(0.85*taille_bouton), "X", WHITE, int (0.5*taille_bouton));
    }
    if (bouton == 1) { // dessine le bouton d'ajout de niveau
        drawRect(x, y, taille_bouton, taille_bouton, WHITE, 2);
        drawString(x + int(0.1*taille_bouton), y + int(0.85*taille_bouton), "+", WHITE, int (0.57*taille_bouton));
    }
    if (bouton == 2) { // dessine le bouton page suivante
        drawRect(x, y, taille_bouton, taille_bouton, WHITE, 2);

        // triangle
        int xa = x + 4*taille_bouton/5;
        int xb = x + 4*taille_bouton/5;
        int xc = x + taille_bouton/5;

        int ya = y + taille_bouton/5;
        int yb = y + 4*taille_bouton/5;
        int yc = y + taille_bouton/2;

        int coord_triangle[6] = {xa, ya, xb, yb, xc, yc};
        fillPoly(coord_triangle, 3, WHITE);
    }
    if (bouton == 3) { // dessine le bouton page precedente
        drawRect(x, y, taille_bouton, taille_bouton, WHITE);

        // triangle
        int xa = x + taille_bouton/5;
        int xb = x + taille_bouton/5;
        int xc = x + 4*taille_bouton/5;

        int ya = y + taille_bouton/5;
        int yb = y + 4*taille_bouton/5;
        int yc = y + taille_bouton/2;

        int coord_triangle[6] = {xa, ya, xb, yb, xc, yc};
        fillPoly(coord_triangle, 3, WHITE);
    }
}



void draw_selection_niveau(int marge_x, int marge_y, int largeur_etiquette, int hauteur_etiquette,
                           int largeur_texte_etiquette, int taille_bouton, int marge_bouton,
                           int taille_bouton_bas, int marge_bouton_bas, int nombre_niveaux,
                           int nombre_niveaux_affiches, int page, const vector<tuple<string, int>> liste_niveaux, bool mode_perso) {
    int W = largeur_etiquette + 2*marge_x;

    // Zone des etiquettes
    int x_etiquettes = marge_x;
    int y_etiquettes = marge_y;
    for (int i=0; i<min(nombre_niveaux,nombre_niveaux_affiches); i++) {
        string nom_niveau = get<0>(liste_niveaux[page*nombre_niveaux_affiches + i]);
        int pas = hauteur_etiquette + marge_y;
        draw_etiquette(x_etiquettes, y_etiquettes + i*pas, page*nombre_niveaux_affiches + i, largeur_etiquette, hauteur_etiquette, largeur_texte_etiquette, nom_niveau, taille_bouton, marge_bouton, mode_perso);
    }

    // Barre du bas
    int y_barre_bas = y_etiquettes + nombre_niveaux_affiches*(hauteur_etiquette+marge_y);
    drawLine(0, y_barre_bas, W, y_barre_bas, WHITE, 2);
    int y_boutons_bas = y_barre_bas + marge_bouton_bas;
    // Bouton de retour vers le menu precedent
    int x_retour = marge_bouton_bas;
    draw_bouton_bas(x_retour, y_boutons_bas, taille_bouton_bas, 0);
    // Bouton d'ajout de niveau
    int x_ajout = W/2 - taille_bouton_bas;
    draw_bouton_bas(x_ajout, y_boutons_bas, taille_bouton_bas, 1);
    // Boutons de pages suivante et precedente
    int largeur_index_page = 2*taille_bouton_bas; // largeur allouee a l'affichage de page/nombre_page
    int x_page = W - marge_bouton_bas - 2*taille_bouton_bas - largeur_index_page;
    draw_bouton_bas(x_page, y_boutons_bas, taille_bouton_bas, 2);
    draw_bouton_bas(x_page + taille_bouton_bas + largeur_index_page, y_boutons_bas, taille_bouton_bas, 3);
    int nb_pages = nombre_niveaux/nombre_niveaux_affiches;
    string index_page = to_string(page+1) + "/" + to_string(nb_pages+1);
    drawString(x_page + taille_bouton_bas + int(0.25*taille_bouton), y_boutons_bas + int(0.87*taille_bouton), index_page, WHITE, int (0.5*taille_bouton));
}

vector<tuple<string, int>> recuperer_niveaux(bool mode_perso) {
    vector<tuple<string, int>> liste_niveaux;

    string txt_niveaux = (mode_perso) ? "niveaux_perso.txt" : "niveaux_aventure.txt";
    string const nomFichier(stringSrcPath((txt_niveaux)));
    ifstream flux(nomFichier); // flux de lecture

    if(flux)
    {
        while(!flux.eof()){ // tant qu'on n'est pas a la fin du .txt
            string map_name;
            flux >> map_name;
            liste_niveaux.push_back(tuple<string, int> (map_name, 0));
            int h,l;
            flux >> h;
            flux >> l;
            int corbeille; // Cette variable ne servira pas, on ne s'en sert que pour le passage au caractere suivant
            for (int x=0; x<l; x++){
                for (int y=0; y<h; y++){
                    flux >> corbeille;
                }
            }
            for (int x=0; x<l; x++){
                for (int y=0; y<h; y++){
                    flux >> corbeille;
                }
            }
        }
        if (liste_niveaux.size() > 0){
            liste_niveaux.pop_back(); // Sans cela il reste un niveau artefact en fin de liste
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
    return liste_niveaux;
}

void selection_niveau(bool mode_perso, int taille_case) {
    // Geometrie de la fenetre
    const int largeur_etiquette = 600;
    const int hauteur_etiquette = 120;
    const int marge_x = int(largeur_etiquette/8); // marge entre une etiquette de niveau et le bord de la fenetre
    const int marge_y = int(hauteur_etiquette/4); // marge entre deux etiquette de niveau

    const int largeur_texte_etiquette = int(6*largeur_etiquette/10); // fraction de l'etiquette dediee aux boutons
    const int taille_bouton = int(largeur_etiquette/10);
    const int marge_bouton = int(largeur_etiquette/40); // marge entre deux boutons d'une etiquette

    const int nombre_niveaux_affiches = 4;

    const int hauteur_barre_bas = hauteur_etiquette;
    const int taille_bouton_bas = int(hauteur_barre_bas/2);
    const int marge_bouton_bas = int(hauteur_barre_bas/4);

    const int W_fenetre = largeur_etiquette + 2*marge_x;
    const int H_fenetre = nombre_niveaux_affiches * (hauteur_etiquette + marge_y) + marge_y + hauteur_barre_bas;
    const string menu = "Séléction de niveau";
    Window selection_niveau_Window = openWindow(W_fenetre, H_fenetre, menu);
    setActiveWindow(selection_niveau_Window);

    // Initialisation de la liste de niveaux
    vector<tuple<string, int>> liste_niveaux = recuperer_niveaux(mode_perso); // Contient l'id du niveau (repere par la position dans le vecteur), le nom du niveau et le nombre d'étoile collecté sur ce niveau
    int nombre_niveaux = liste_niveaux.size();

    int page = 0;

    // boucle principale
    bool fin = false;
    int x;
    int y;
    bool rafraichir_affichage = true; // Determine s'il faut rafraichir l'affichage lors du tour de boucle
    while (!fin) {
        if (rafraichir_affichage) {
            clearWindow();
            fillRect(0, 0, W_fenetre, H_fenetre, BLACK);
            draw_selection_niveau(marge_x, marge_y, largeur_etiquette, hauteur_etiquette,
                                  largeur_texte_etiquette, taille_bouton, marge_bouton,
                                  taille_bouton_bas, marge_bouton_bas, nombre_niveaux,
                                  nombre_niveaux_affiches, page, liste_niveaux, mode_perso);;
            rafraichir_affichage = false;
        }

        getMouse(x, y);
        if (y > marge_y && y < nombre_niveaux_affiches * (hauteur_etiquette + marge_y) + marge_y){ // si la souris est dans la zone des etiquette
            int num_etiquette = (y - marge_y) / (hauteur_etiquette + marge_y);
            int y_etiquette = (y - marge_y) % (hauteur_etiquette + marge_y);
            int num_niveau = page*nombre_niveaux_affiches + num_etiquette;
            bool dans_hauteur_bouton = y_etiquette > marge_bouton && (y_etiquette < marge_bouton + taille_bouton);
            if (dans_hauteur_bouton) { // si la souris est dans la hauteur des boutons de l'etiquette
                int num_bouton = (x - marge_x - largeur_texte_etiquette) / (taille_bouton + marge_bouton);
                if (num_bouton == 0 && mode_perso) { // Lance l'editeur du niveau
                    closeWindow(selection_niveau_Window);
                    Map map_selectionnee;
                    map_selectionnee.charger(num_niveau, "Niveaux_perso.txt");
                    creer_map(map_selectionnee.nom, map_selectionnee.L, map_selectionnee.H, taille_case, true, map_selectionnee, num_niveau, nombre_niveaux, "Niveaux_perso.txt");
                    selection_niveau_Window = openWindow(W_fenetre, H_fenetre, menu);
                    setActiveWindow(selection_niveau_Window);
                    rafraichir_affichage = true;
                }
                if (num_bouton == 1 && mode_perso) { // supprime le niveau
                    efface_niveau(num_niveau, nombre_niveaux, "Niveaux_perso.txt");
                    liste_niveaux = recuperer_niveaux(mode_perso);
                    nombre_niveaux -= 1;
                    page = min(page, nombre_niveaux/nombre_niveaux_affiches); // max entre la page atuel et le nouveau nombre de pages
                    rafraichir_affichage = true;
                }
                if (num_bouton == 2) { // joue le niveau
                    closeWindow(selection_niveau_Window);
                    string txt_niveaux = (mode_perso) ? "niveaux_perso.txt" : "niveaux_aventure.txt";
                    Map map_selectionnee;
                    map_selectionnee.charger(num_niveau, txt_niveaux);
                    jouer(map_selectionnee, taille_case);
                    selection_niveau_Window = openWindow(W_fenetre, H_fenetre, menu);
                    setActiveWindow(selection_niveau_Window);
                    rafraichir_affichage = true;
                }
            }
        }
    }
    click();
    closeWindow(selection_niveau_Window);
}

void draw_categorie_niveau(int W_menu, int H_menu, int marge_menu_x, int marge_menu_y, int taille_case){

    fillRect(0,0,W_menu,H_menu,BLACK); // fond noir
    vector <string> Liste_categories = {"Niveaux classiques", "Mes niveaux", "Retour au menu"};
    vector <Color> Liste_color = {RED, BLUE, GREEN};
    // Dessin des boutons
    for (int k=0; k<3; k++){
        int x = marge_menu_x;
        int y = (3*k+1)*marge_menu_y;
        int w = W_menu - 2*marge_menu_x;
        int h = 2*marge_menu_y;
        drawRect(x, y, w, h, WHITE, 2);

        ecris_dans_la_case (x, y, w, h, Liste_categories[k], 18, Liste_color[k]);
    }
}

void menu_categorie_niveau(int taille_case){
    const int W_menu = 600;
    const int H_menu = 700;
    const int marge_menu_x = int(W_menu/6);
    const int marge_menu_y = int(H_menu/10);

    const string selection = "Selection de la catégorie de niveau";
    Window menu_Window = openWindow(W_menu, H_menu, selection);

    draw_categorie_niveau(W_menu, H_menu, marge_menu_x, marge_menu_y, taille_case);

    // Coordonnees de la souris
    int x;
    int y;

    bool fin = false;
    while ( ! fin ){

        getMouse(x, y);

        if ( x > marge_menu_x && x < W_menu - marge_menu_x){ // Zonne de x dans laquelle se trouve les boutons
            float num_y = y/(3.0*marge_menu_y);
            if (num_y - floor(num_y) > 0.3333){ // Zone de y dans laquelle se trouve les boutons

                int k = floor(num_y); // Numero du bouton clique

                closeWindow(menu_Window);
                if (k==0){
                    selection_niveau(false, taille_case);
                    menu_Window = openWindow(W_menu, H_menu, selection);
                    draw_categorie_niveau(W_menu, H_menu, marge_menu_x, marge_menu_y, taille_case);
                }
                else if (k==1){
                    selection_niveau(true, taille_case);
                    menu_Window = openWindow(W_menu, H_menu, selection);
                    draw_categorie_niveau(W_menu, H_menu, marge_menu_x, marge_menu_y, taille_case);
                }

                else if (k==2){
                    fin = true;
                }
            }
        }
    }

}

void draw_caracteristiques_niveau(int h, int hauteur, int largueur, string nom_map){
    int taille_police = 12;

    drawRect(h, h, 5*h, h, WHITE, 2);
    drawRect(h, 2*h, 5*h, h, WHITE, 2);
    ecris_dans_la_case(h, h, 5*h, h, "Nom du niveau", taille_police, RED);
    ecris_dans_la_case(h, 2*h, 5*h, h, nom_map, taille_police, WHITE);

    vector<string> Liste_boutons = {"Hauteur", "Largueur", "Retour", "Créer"};
    vector<string> Liste_dim = {to_string(hauteur), to_string(largueur)};

    int y_dep = 3*h;
    for (int i=0; i<2; i++){
        for (int j=0; j<2; j++){
            int x = (3*j+1)*h;
            int y = y_dep + (3*i+1)*h;
            int k = j + 2*i;
            drawRect(x, y, 2*h, 2*h, WHITE, 2);
            if (i == 0){ // Boutons H et L
                drawLine( (3*j+1)*h, y_dep + (3*i+2)*h, (3*j+3)*h, y_dep + (3*i+2)*h, WHITE, 2);
                ecris_dans_la_case(x, y, 2*h, h, Liste_boutons[k], taille_police, BLUE);
                ecris_dans_la_case(x, y+h, 2*h, h, Liste_dim[k], taille_police, WHITE);
            }
            else{ // Boutons retour et creer
                ecris_dans_la_case(x, y, 2*h, 2*h, Liste_boutons[k], taille_police, GREEN);
            }
        }
    }
}

void menu_creation_niveau(){
    const int h = 60;
    const int W = 7*h;
    const int H = 10*h;

    const string niveau = "Sélection des caractéristiques du niveau";
    Window w = openWindow(W, H, niveau);
    setActiveWindow(w);

    string hauteur = "20";
    string largueur = "40";
    string nom_map = "Mon niveau";

    fillRect(0, 0, W, H, BLACK); // fond noir
    draw_caracteristiques_niveau(h, stoi(hauteur), stoi(largueur), nom_map);

    // Coordonnees de la souris
    int x;
    int y;

    // Case selectionnee
    int k = -1;

    //  Booleen qui indique si key correspond a un clic ou non
    bool clic = false;
    bool clav = false;

    int taille_case = 20; // A regler

    bool fin = false;
    while ( ! fin ){

        int key = Clavier(x, y, clic, clav);

        if (clic){
            if (x > h && x < W-h){ // Zonne de x dans laquelle se trouve les boutons

                if (y > h && y < 3*h ){
                    k = -1;
                    nom_map = "";
                    fillRect(0, 0, W, H, BLACK); // fond noir
                    draw_caracteristiques_niveau(h, stoi(hauteur), stoi(largueur), nom_map);
                }

                else{

                    int y_dep = 3*h;

                    float num_x = x/(3.0*h);
                    float num_y = (y-y_dep)/(3.0*h);

                    if (num_y - floor(num_y) > 0.3333 && num_x - floor(num_x) > 0.3333){ // Zone de y dans laquelle se trouve les boutons
                        k = floor(num_x) + 2*floor(num_y); // Numero du bouton

                        if (k == 0){
                            hauteur = "0";
                            fillRect(0, 0, W, H, BLACK); // fond noir
                            draw_caracteristiques_niveau(h, stoi(hauteur), stoi(largueur), nom_map);
                        }
                        else if (k == 1){
                            largueur = "0";
                            fillRect(0, 0, W, H, BLACK); // fond noir
                            draw_caracteristiques_niveau(h, stoi(hauteur), stoi(largueur), nom_map);
                        }

                        else if ( k == 2){
                            closeWindow(w);
                            fin = true;
                        }

                        else if ( k == 3){
                            closeWindow(w);
                            creer_map(nom_map, stoi(largueur), stoi(hauteur), taille_case);
                            w = openWindow(W, H, niveau);
                            setActiveWindow(w);
                            fillRect(0, 0, W, H, BLACK); // fond noir
                            draw_caracteristiques_niveau(h, stoi(hauteur), stoi(largueur), nom_map);
                        }
                    }
                }

            }
            clic = false;
        }

        else if (clav){

            if (key == KEY_BACK){
                if (k == -1 && nom_map.size() > 0)
                    nom_map.pop_back();
                else if (k == 0 && hauteur.size() > 0){
                    hauteur.pop_back();
                    if (hauteur.size() == 0)
                        hauteur = "0";
                }
                else if (k == 1 && largueur.size() > 0){
                    largueur.pop_back();
                    if (largueur.size() == 0)
                        largueur = "0";
                    }
            }
            else if (   k == -1
                     && ( (key<='z' && key>= 'a') | (key<='9' && key>='0') | (key<='Z' && key>= 'A') | (key == ' ') )){

                string caractere(1, char(key));
                nom_map.append(caractere);
            }

            else if (k == 0 && key<='9' && key>='0'){
                hauteur.append(string (1, char(key)));
            }
            else if (k == 1 && key<='9' && key>='0'){
                largueur.append(string (1, char(key)));
            }

            clav = false;
            fillRect(0, 0, W, H, BLACK); // fond noir
            draw_caracteristiques_niveau(h, stoi(hauteur), stoi(largueur), nom_map);
        }
    }
}

void menu_options(){

}

void draw_titre(int taille, int x, int y){ // Dessin du titre
    string titre = "Paint Runner";
    Color Liste_couleurs[12] = {Color(170,20,200), Color(169,27,176), Color(196,30,153), Color(207,0,99), Color(230,21,119), Color(243,77,154), Color(255,0,0), Color(223,40,35), Color(247,106,4), Color(206,156,72), Color(250,194,0), Color(254,221,39)};
    for (unsigned int i=0; i<3; i++){
        drawString(x + taille*i, y, {titre[i]}, Liste_couleurs[i], taille );
    }
    for (unsigned int i=3; i<5; i++){
        drawString(x + taille*i - 0.6*taille, y, {titre[i]}, Liste_couleurs[i], taille );
    }
    for (unsigned int i=5; i<titre.size(); i++){
        drawString(x + taille*i - 1.2*taille, y, {titre[i]}, Liste_couleurs[i], taille );
    }
}

void draw_menu(int W_menu, int H_menu, int marge_menu_x, int marge_menu_y){

    fillRect(0, 0, W_menu, H_menu, BLACK); // fond noir

    int x = marge_menu_x;
    int w = W_menu - 2*marge_menu_x; // largueur des boutons
    int h = 2*marge_menu_y; // hauteur des boutons

    draw_titre(48, x/2, 2.5*marge_menu_y);
    //ecris_dans_la_case (x, marge_menu_y, w, h, "Paint Runner", 40, Color(hasard(0, 255), hasard(0, 255), hasard(0, 255)));

    // Dessin des boutons
    vector <string> Liste_string = {"Jouer", "Options", "Quitter"}; // liste des noms des boutons
    vector <Color> Liste_color = {RED, BLUE, GREEN}; // liste des couleurs des boutons
    for (int k=1; k<4; k++){
        int y = (3*k+1)*marge_menu_y;
        drawRect(x, y, w, h, WHITE, 2);

        ecris_dans_la_case (x, y, w, h, Liste_string[k-1], 18, Liste_color[k-1]);
    }
}

void lancer_menu(int taille_case) {
    const int W_menu = 600;
    const int H_menu = 721;
    const int marge_menu_x = int(W_menu/6);
    const int marge_menu_y = int(H_menu/13);

    const string menu = "Menu";
    Window menu_Window = openWindow(W_menu, H_menu, menu);
    setActiveWindow(menu_Window);

    draw_menu(W_menu, H_menu, marge_menu_x, marge_menu_y);

    // Coordonnees de la souris
    int x;
    int y;

    bool fin = false;
    while ( ! fin ){

        getMouse(x, y);

        if ( x > marge_menu_x && x < W_menu - marge_menu_x){ // Zonne de x dans laquelle se trouve les boutons
            float num_y = y/(3.0*marge_menu_y);
            if (num_y - floor(num_y) > 0.3333){ // Zone de y dans laquelle se trouve les boutons

                int k = floor(num_y); // Numero du bouton clique

                closeWindow(menu_Window);

                if (k==1){
                    menu_categorie_niveau(taille_case);
                    menu_Window = openWindow(W_menu, H_menu, menu);
                    setActiveWindow(menu_Window);
                    draw_menu(W_menu, H_menu, marge_menu_x, marge_menu_y);
                }

                else if (k==2){
                    menu_options();
                    menu_Window = openWindow(W_menu, H_menu, menu);
                    setActiveWindow(menu_Window);
                    draw_menu(W_menu, H_menu, marge_menu_x, marge_menu_y);
                }

                else if (k==3){
                    fin = true;
                }

            }
        }
    }
}



// ========================================






int main()
{
//    initRandom();
    int taille_case = 28;

//    openWindow(taille_case*55, taille_case*22); // Ouverture d'une fenetre de bonne dimension pour afficher la map
//    string nom_map = "Map_a_la_mano";
//    Map map(nom_map, 21, 55);
//    construire_map_a_la_main(map);
//    run (map, taille_case);

//      lancer_menu(taille_case);

//    int L = 30;
//    int H = 20;
//    creer_map("Ma_map_nulle", L, H, taille_case); // Cree une map

//    Map map;
//    map.charger(0, "Niveaux.txt");
//    jouer(map, taille_case);

//    Map map;
//    map.charger(0); // Charge la map dans le fichier Niveaux_aventure.txt
//    openWindow(taille_case*map.L, taille_case*map.H); // Ouverture d'une fenetre de bonne dimension pour afficher la map
//    run (map, taille_case); // Joue le niveau

//    int nb_niveau = 3;
//    efface_niveau(0, nb_niveau, "Niveaux.txt");

//    Map map;
//    map.charger(1, "Niveaux.txt"); // Charge la map dans le fichier Niveaux.txt
//    editer_map(map, taille_case, 1, 3, "Niveaux.txt");



//    selection_niveau(true, taille_case);

    menu_creation_niveau();

    endGraphics();
    return 0;
}
