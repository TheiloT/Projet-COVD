#include "edition.h"
#include "correspondance.h"
#include "graphismes.h"

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
    drawLine(x_dep+1, 0, x_dep+1, H*taille_case, BLACK, 2);

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

// Fonctions pour le mode "jouer"

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

void affiche_etoiles(int x, int y, int hauteur_etoile, int largeur_etoiles) { // A adapter
    const int taille_etoile = hauteur_etoile/2;
    const int marge_etoile = taille_etoile/2;
    int x_etoiles = x + largeur_etoiles/2 - (3*taille_etoile + 2*marge_etoile)/2;
    for (int i=0; i<3; i++) {
        trace_etoile(x_etoiles + i*(taille_etoile + marge_etoile), y, taille_etoile);
    }
}

void affiche_retour(int x, int y, int taille_bouton){
    drawRect(x, y, taille_bouton, taille_bouton, WHITE, 2);
    ecris_dans_la_case(x-2, y, taille_bouton, taille_bouton, "X", taille_bouton/2, WHITE);
}

void affiche_victoire() { // Affiche que le niveau est gagne
    const int W_victoire = 400;
    const int H_victoire = 500;
    const int marge_x = int(W_victoire/15);
    const int marge_y = int(H_victoire/10);
    const int hauteur_etoiles = (H_victoire - marge_y)/5;
    const int hauteur_gagne = (H_victoire - marge_y)/3;
    const int hauteur_retour = (H_victoire - marge_y)/3;
    const int taille_bouton = hauteur_retour/2;

    const string menu = "Gagné !";
    Window victoire_Window = openWindow(W_victoire, H_victoire, menu);
    setActiveWindow(victoire_Window);
    fillRect(0, 0, W_victoire, H_victoire, BLACK);

    // Affichage du mot de victoire
    const vector<string> mots_victoire = {"Victoire!", "Gagné!", "Bravo!", "Super!"}; // On tirera un mot au hasard parmi ceux-là
    int mot = rand() % mots_victoire.size();
    int x_gagne = marge_x;
    int y_gagne = marge_y;
    ecris_dans_la_case(x_gagne, y_gagne, W_victoire - 2*marge_x, hauteur_gagne, mots_victoire[mot], hauteur_gagne/5, couleur_au_hasard());

    // Affichage des étoiles
    int y_etoiles = marge_y + hauteur_gagne;
    affiche_etoiles(marge_x, y_etoiles, hauteur_etoiles, W_victoire - 2*marge_x); // à compléter avec le relevé des étoiles

    // Affichage du bouton de retour
    int x_retour = W_victoire/2 - taille_bouton/2;
    int y_retour = y_etoiles + hauteur_etoiles + hauteur_retour/2 - taille_bouton/2;
    affiche_retour(x_retour, y_retour, taille_bouton);

    click();
    closeWindow(victoire_Window);

}
