#include "outils.h"
#include "correspondance.h"
#include "map.h"
#include "graphismes.h"

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
//    drawLine(x+largeur_texte_etiquette, y, x+largeur_texte_etiquette, y+hauteur_etiquette, WHITE);
    int x_boutons = x + largeur_texte_etiquette;
    int y_boutons = y + (hauteur_etiquette-taille_bouton)/2;
    int pas = taille_bouton + marge_bouton;
    if (mode_perso) {
        for (int i=0; i<3; i++)
            draw_bouton_etiquette(marge_bouton + x_boutons + i*pas, y_boutons, taille_bouton, i);
    }
    else draw_bouton_etiquette(marge_bouton + x_boutons + 2*pas, y_boutons, taille_bouton, 2);
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
        drawRect(x, y, taille_bouton, taille_bouton, WHITE, 2);

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


void draw_selection_niveau(int W, int H, int marge_x, int marge_y, int largeur_etiquette, int hauteur_etiquette,
                           int largeur_texte_etiquette, int taille_bouton, int marge_bouton,
                           int taille_bouton_bas, int marge_bouton_bas, int nombre_niveaux,
                           int nombre_niveaux_affiches, int page, const vector<tuple<string, int>> liste_niveaux, bool mode_perso) {
    fillRect(0, 0, W, H, BLACK);

    // Zone des etiquettes
    int x_etiquettes = marge_x;
    int y_etiquettes = marge_y;
    for (int i=0; i<nombre_niveaux_affiches; i++) {
        if (page*nombre_niveaux_affiches + i < nombre_niveaux) {
            string nom_niveau = get<0>(liste_niveaux[page*nombre_niveaux_affiches + i]);
            int pas = hauteur_etiquette + marge_y;
            draw_etiquette(x_etiquettes, y_etiquettes + i*pas, page*nombre_niveaux_affiches + i, largeur_etiquette, hauteur_etiquette, largeur_texte_etiquette, nom_niveau, taille_bouton, marge_bouton, mode_perso);
        }
    }

    // Barre du bas
    int y_barre_bas = y_etiquettes + nombre_niveaux_affiches*(hauteur_etiquette+marge_y);
    drawLine(0, y_barre_bas, W, y_barre_bas, WHITE, 2);
    int y_boutons_bas = y_barre_bas + marge_bouton_bas;
    // Bouton de retour vers le menu precedent
    int x_retour = marge_bouton_bas;
    draw_bouton_bas(x_retour, y_boutons_bas, taille_bouton_bas, 0);
    // Bouton d'ajout de niveau
    if (mode_perso) {
        int x_ajout = W/2 - taille_bouton_bas;
        draw_bouton_bas(x_ajout, y_boutons_bas, taille_bouton_bas, 1);
    }
    // Boutons de pages suivante et precedente
    int largeur_index_page = 2*taille_bouton_bas; // largeur allouee a l'affichage de page/nombre_page
    int x_page = W - marge_bouton_bas - 2*taille_bouton_bas - largeur_index_page;
    draw_bouton_bas(x_page, y_boutons_bas, taille_bouton_bas, 2);
    draw_bouton_bas(x_page + taille_bouton_bas + largeur_index_page, y_boutons_bas, taille_bouton_bas, 3);
    int nb_pages = max((nombre_niveaux-1)/nombre_niveaux_affiches, 0);
    string index_page = to_string(page+1) + "/" + to_string(nb_pages+1);
    drawString(x_page + taille_bouton_bas + int(0.25*taille_bouton), y_boutons_bas + int(0.87*taille_bouton), index_page, WHITE, int (0.5*taille_bouton));
}

vector<tuple<string, int>> recuperer_niveaux(bool mode_perso) {
    vector<tuple<string, int>> liste_niveaux;

    string txt_niveaux = (mode_perso) ? "niveaux_perso.txt" : "niveaux_aventure.txt";
    string const nomFichier(stringSrcPath((txt_niveaux)));
    ifstream flux(nomFichier); // flux de lecture

    if(flux) try
    {
        bool fichier_vide = (flux.peek() == std::ifstream::traits_type::eof());
            // indique si le fichier des maps n'est pas vide. En effet, le test !flux.eof() ne prend pas en compte ce cas.
        while(!flux.eof() && !fichier_vide){ // tant qu'on n'est pas a la fin du .txt
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
    catch (std::bad_alloc error) {
        cout << "Erreur a la lecture des niveaux. Verifiez que le fichier des niveaux '" + txt_niveaux + "' est correctement rempli, par exemple qu'il n'y a pas de nom de niveau avec un espace. \n";
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
    return liste_niveaux;
}

void draw_categorie_niveau(int W_menu, int H_menu, int marge_menu_x, int marge_menu_y, int taille_case){

    fillRect(0,0,W_menu,H_menu,BLACK); // fond noir
    vector <string> Liste_categories = {"Mode aventure", "Mes niveaux", "Retour au menu"};
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
    vector <string> Liste_string = {"Jouer", "Règles", "Quitter"}; // liste des noms des boutons
    vector <Color> Liste_color = {RED, BLUE, GREEN}; // liste des couleurs des boutons
    for (int k=1; k<4; k++){
        int y = (3*k+1)*marge_menu_y;
        drawRect(x, y, w, h, WHITE, 2);

        ecris_dans_la_case (x, y, w, h, Liste_string[k-1], 18, Liste_color[k-1]);
    }
}
