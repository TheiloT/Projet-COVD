#include "edition.h"
#include "correspondance.h"
#include "jeu.h"

void affiche_grille(int H, int L, int taille_case){
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
        int coord_triangle[6] = {xa, ya, xb, yb, xc, yc}; // triangle du bouton "play"
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

void affiche_boutons(int L, int taille_case, int taille_case_editeur, int bande_texte, string nom_map){

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

bool getAction(int x, int y, int &bouton_action, int bande_texte, int L, int taille_case, int taille_case_editeur){
    int x_dep = L*taille_case;
    if ( y < bande_texte + 1.5*taille_case_editeur && y > bande_texte + 0.5*taille_case_editeur){ // Verifie que la souris est a la bonne hauteur
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
    if ( y < bande_texte + 3.5*taille_case_editeur && y > bande_texte + 2.5*taille_case_editeur){ // Verifie que la souris est a la bonne hauteur
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
    float num_x = (2.0 *(x - x_dep) / float(taille_case_editeur)) / 3.0; // numero de la colonne de boutons
    float num_y = (2.0 *(y - y_dep) / float(taille_case_editeur)) / 3.0; // numero de la ligne de boutons
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
    float num_x = (2.0 *(x - x_dep) / float(taille_case_editeur)) / 3.0; // numero de la colonne de boutons
    float num_y = (2.0 *(y - y_dep) / float(taille_case_editeur)) / 3.0; // numero de la ligne de boutons
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

void creer_map(string nom_map, int L, int H, int taille_case, bool editer, Map map_a_editer, int num_map, int nb_niveaux, const string niveau){
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
    affiche_boutons(L, taille_case, taille_case_editeur, bande_texte, nom_map);
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
                int trash; // Ici on n'utilise pas le nombre d'etoiles collectees, donc on utilise un une variable "poubelle"
                run(map_a_editer, taille_case, trash);
                map_a_editer.affiche_tout(taille_case);
                drawLine(L * taille_case+1, 0, L * taille_case+1, H*taille_case,WHITE, 1); // Correction bug affichage
                affiche_grille(H, L, taille_case);
            }
            else if (bouton_action == bouton_sauvegarder){ // Sauvevarder le niveau cree
                int nb_portes_entree = 0;
                for (int j=0; j<L; j++) {
                    for (int i=0; i<H; i++){
                        nb_portes_entree += est_dans(map_a_editer.get_case(j, i), portes_entree);
                    }
                }
                if (nb_portes_entree==1) { // S'il y a bien une seule entree
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
                else {
                    const int W_message = 700;
                    const int H_message = 100;
                    const int marge_x = int(W_message/12);
                    const int marge_y = int(H_message/2);

                    const string menu = "Erreur";
                    Window message_Window = openWindow(W_message, H_message, menu);
                    setActiveWindow(message_Window);
                    fillRect(0, 0, W_message, H_message, BLACK);

                    string message = "Votre niveau doit avoir exactement 1 entrée !";
                    drawString(marge_x, marge_y, message, WHITE, W_message/40);
                    click();
                    closeWindow(message_Window);
                    setActiveWindow(w);
                }
            }
            else if (bouton_action == bouton_quitter){ // Quitter la creation de map sans sauvegarder
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

void editer_map(Map map, int taille_case, int num_map, int nb_niveaux, string niveau){
    creer_map (map.get_nom(), map.get_L(), map.get_H(), taille_case, true, map, num_map, nb_niveaux, niveau);
}
