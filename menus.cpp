#include "outils.h"
#include "correspondance.h"
#include "map.h"
#include "graphismes.h"
#include "jeu.h"
#include "edition.h"
#include "niveaux.h"

// Fonctions graphiques et outils specifiques aux menus

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
        drawString(x + int(0.2*taille_bouton), y + int(0.85*taille_bouton), "E", BLACK, int (0.4*taille_bouton));
    }
    if (bouton == 1) { // dessine le bouton de deletion
        int d = int (0.2 * taille_bouton);
        fillRect(x, y, taille_bouton, taille_bouton, RED);
        drawLine(x + 4 + d, y + 4 + d, x + taille_bouton - 4 - d, y + taille_bouton - 4 - d, WHITE, 8);
        drawLine(x + taille_bouton - 4 - d, y + 4 + d, x + 4 + d, y + taille_bouton - 4 - d, WHITE, 8);
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
    int taille_police = 18;
    ecris_dans_la_case(x, y, largeur_texte_etiquette, hauteur_etiquette, nom_niveau, taille_police, Couleurs[k % 4]); // Ecrit le nom du niveau dans la couleur correspondant au numero de l'etiquette en partant du haut
    int x_boutons = x + int(1.4 * largeur_texte_etiquette);
    int y_boutons = y + (hauteur_etiquette-taille_bouton)/2;
    int pas = taille_bouton + marge_bouton;
    if (mode_perso) { // On affiche plus de boutons en mode "Mes niveaux"
        for (int i=0; i<3; i++)
            draw_bouton_etiquette(marge_bouton + x_boutons + i*pas, y_boutons, taille_bouton, i);
    }
    else draw_bouton_etiquette(marge_bouton + x_boutons + 2*pas, y_boutons, taille_bouton, 2);
}

void draw_bouton_bas(int x, int y, int taille_bouton, int bouton) {
    if (bouton == 0) { // dessine le bouton de retour
        // draw_bouton_etiquette(x, y, taille_bouton, 1);
        int d = int (0.2 * taille_bouton);
        // fillRect(x, y, taille_bouton, taille_bouton, RED);
        drawRect(x, y, taille_bouton, taille_bouton, WHITE, 2);
        drawLine(x + 4 + d, y + 4 + d, x + taille_bouton - 4 - d, y + taille_bouton - 4 - d, WHITE, 8);
        drawLine(x + taille_bouton - 4 - d, y + 4 + d, x + 4 + d, y + taille_bouton - 4 - d, WHITE, 8);
    }
    if (bouton == 1) { // dessine le bouton d'ajout de niveau
        drawRect(x, y, taille_bouton, taille_bouton, WHITE, 2);
        drawString(x + int(0.1*taille_bouton), y + int(0.85*taille_bouton), "+", WHITE, int (0.45*taille_bouton));
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
    drawString(x_page + taille_bouton_bas + int(0.25*taille_bouton), y_boutons_bas + int(0.87*taille_bouton), index_page, WHITE, int (0.4*taille_bouton));
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

void draw_categorie_niveau(int W_menu, int H_menu, int marge_menu_x, int marge_menu_y){

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
    const double facteur = 1.4;
    for (unsigned int i=0; i<3; i++){
        drawString(x + facteur * taille*i, y, {titre[i]}, Liste_couleurs[i], taille );
    }
    for (unsigned int i=3; i<5; i++){
        drawString(x + facteur * taille*i - 0.6*taille, y, {titre[i]}, Liste_couleurs[i], taille );
    }
    for (unsigned int i=5; i<titre.size(); i++){
        drawString(x + facteur * taille*i - 1.2*taille, y, {titre[i]}, Liste_couleurs[i], taille );
    }
}

void draw_menu(int W_menu, int H_menu, int marge_menu_x, int marge_menu_y){

    fillRect(0, 0, W_menu, H_menu, BLACK); // fond noir

    int x = marge_menu_x;
    int w = W_menu - 2*marge_menu_x; // largueur des boutons
    int h = 2*marge_menu_y; // hauteur des boutons

    draw_titre(48, int(1.2*x), 2.5*marge_menu_y);
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

// Fonction d'appel des menus a proprement parler

void menu_creation_niveau(int taille_case){
    const int h = 60;
    const int W = 7*h;
    const int H = 10*h;

    const string niveau = "Sélection des caractéristiques du niveau";
    Window w = openWindow(W, H, niveau);
    setActiveWindow(w);

    string hauteur = "20";
    string largeur = "40";
    string nom_map = "Mon_niveau";

    fillRect(0, 0, W, H, BLACK); // fond noir
    draw_caracteristiques_niveau(h, stoi(hauteur), stoi(largeur), nom_map); // stoi : string to integer

    // Coordonnees de la souris
    int x;
    int y;

    // Case selectionnee
    int k = -1;

    //  Booleen qui indique si key correspond a un clic ou non
    bool clic = false;
    bool clav = false;

    bool fin = false;
    while ( ! fin ){

        int key = Clavier(x, y, clic, clav);

        if (clic){
            if (x > h && x < W-h){ // Zonne de x dans laquelle se trouve les boutons

                if (y > h && y < 3*h ){
                    k = -1;
                    nom_map = "";
                    fillRect(0, 0, W, H, BLACK); // fond noir
                    draw_caracteristiques_niveau(h, stoi(hauteur), stoi(largeur), nom_map);
                }

                else{

                    int y_dep = 3*h;

                    float num_x = x/(3.0*h);
                    float num_y = (y-y_dep)/(3.0*h);

                    if (num_y - floor(num_y) > 0.3333 && num_x - floor(num_x) > 0.3333){ // Zone de y dans laquelle se trouve les boutons
                        k = floor(num_x) + 2*floor(num_y); // Numero du bouton

                        if (k == 0){ // Modification de la hauteur
                            hauteur = "0";
                            fillRect(0, 0, W, H, BLACK); // fond noir
                            draw_caracteristiques_niveau(h, stoi(hauteur), stoi(largeur), nom_map);
                        }
                        else if (k == 1){ // Mofification de la largueur
                            largeur = "0";
                            fillRect(0, 0, W, H, BLACK); // fond noir
                            draw_caracteristiques_niveau(h, stoi(hauteur), stoi(largeur), nom_map);
                        }

                        else if ( k == 2){ // Bouton quitter
                            closeWindow(w);
                            fin = true;
                        }

                        else if ( k == 3){ // Bouton Creer
                            closeWindow(w);
                            creer_map(nom_map, stoi(largeur), stoi(hauteur), taille_case);
                            fin = true;
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
                else if (k == 1 && largeur.size() > 0){
                    largeur.pop_back();
                    if (largeur.size() == 0)
                        largeur = "0";
                    }
            }
            else if (   k == -1
                     && ( (key<='z' && key>= 'a') | (key<='9' && key>='0') | (key<='Z' && key>= 'A') | (key == '-') | (key == '_'))){

                string caractere(1, char(key));
                nom_map.append(caractere);
            }

            else if (k == 0 && key<='9' && key>='0'){
                hauteur.append(string (1, char(key)));
            }
            else if (k == 1 && key<='9' && key>='0'){
                largeur.append(string (1, char(key)));
            }

            clav = false;
            fillRect(0, 0, W, H, BLACK); // fond noir
            draw_caracteristiques_niveau(h, stoi(hauteur), stoi(largeur), nom_map);
        }
    }
}

void selection_niveau(bool mode_perso, int taille_case) {
    // Geometrie de la fenetre
    const int largeur_etiquette = 1200;
    const int hauteur_etiquette = 240;
    const int marge_x = int(largeur_etiquette/8); // marge entre une etiquette de niveau et le bord de la fenetre
    const int marge_y = int(hauteur_etiquette/4); // marge entre deux etiquette de niveau

    const int largeur_texte_etiquette = int(4*largeur_etiquette/10); // fraction de l'etiquette dediee aux boutons
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
    vector<tuple<string, int>> liste_niveaux = recuperer_niveaux(mode_perso); // Contiendra le nom du niveau et le nombre d'etoiles collectees sur ce niveau
    int nombre_niveaux;

    int page = 0;
    int nombre_pages;

    // boucle principale
    bool fin = false;
    int x;
    int y;
    bool rafraichir_affichage = true; // Determine s'il faut rafraichir l'affichage lors du tour de boucle
    while (!fin) {
        nombre_niveaux = liste_niveaux.size();
        nombre_pages = max((nombre_niveaux-1)/nombre_niveaux_affiches, 0);
        page = min(page, nombre_pages);
        if (rafraichir_affichage) {
            clearWindow();
            draw_selection_niveau(W_fenetre, H_fenetre, marge_x, marge_y, largeur_etiquette, hauteur_etiquette,
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
            bool dans_hauteur_bouton = y_etiquette > (hauteur_etiquette-taille_bouton)/2 && (y_etiquette < (hauteur_etiquette+taille_bouton)/2);
            if (dans_hauteur_bouton && num_niveau < nombre_niveaux) { // si la souris est dans la hauteur des boutons de l'etiquette ET que le numéro du niveau ne dépasse pas le nombre de niveaux existants
                int x_boutons = marge_x + int(1.4 * largeur_texte_etiquette);
                int num_bouton = (x - x_boutons) / (taille_bouton + marge_bouton);
                bool est_dans_largeur_bouton = (x > (x_boutons + marge_bouton + num_bouton*(taille_bouton + marge_bouton)))
                                                && (x < (x_boutons + marge_bouton + (num_bouton+1)*(taille_bouton + marge_bouton) - marge_bouton));
                if (est_dans_largeur_bouton) {
                        if (num_bouton == 0 && mode_perso) { // Lance l'editeur du niveau
                        closeWindow(selection_niveau_Window);
                        Map map_selectionnee;
                        map_selectionnee.charger(num_niveau, "Niveaux_perso.txt");
                        creer_map(map_selectionnee.get_nom(), map_selectionnee.get_L(), map_selectionnee.get_H(), taille_case, true, map_selectionnee, num_niveau, nombre_niveaux, "Niveaux_perso.txt");
                        liste_niveaux = recuperer_niveaux(mode_perso);
                        selection_niveau_Window = openWindow(W_fenetre, H_fenetre, menu);
                        setActiveWindow(selection_niveau_Window);
                        rafraichir_affichage = true;
                    }
                    if (num_bouton == 1 && mode_perso) { // supprime le niveau
                        efface_niveau(num_niveau, nombre_niveaux, "Niveaux_perso.txt");
                        liste_niveaux = recuperer_niveaux(mode_perso);
                        rafraichir_affichage = true;
                    }
                    if (num_bouton == 2) { // joue le niveau
                    closeWindow(selection_niveau_Window);
                    string txt_niveaux = (mode_perso) ? "niveaux_perso.txt" : "niveaux_aventure.txt";
                    Map map_selectionnee;
                    map_selectionnee.charger(num_niveau, txt_niveaux);
                    jouer(map_selectionnee, taille_case);
                    liste_niveaux = recuperer_niveaux(mode_perso);
                    selection_niveau_Window = openWindow(W_fenetre, H_fenetre, menu);
                    setActiveWindow(selection_niveau_Window);
                    rafraichir_affichage = true;
                }
                }
            }
        }
        int y_barre_bas = marge_y + nombre_niveaux_affiches*(hauteur_etiquette+marge_y);
        if ((y > y_barre_bas + marge_bouton_bas) && (y < y_barre_bas + marge_bouton_bas + taille_bouton_bas)) { // Si la souris est dans la hauteur des boutons du bas
            if ((x > marge_bouton_bas) && (x < marge_bouton_bas + taille_bouton_bas)) { // retourne au menu precedent
                closeWindow(selection_niveau_Window);
                fin = true;
            }
            if ((x > W_fenetre/2 - taille_bouton_bas) && (x < W_fenetre/2 + taille_bouton_bas) && mode_perso) { // Creation de niveau
                closeWindow(selection_niveau_Window);
                menu_creation_niveau(taille_case);
                liste_niveaux = recuperer_niveaux(mode_perso);
                page = nombre_pages+1; // Pour diriger l'utilisateur a l'endroit du niveau qu'il vient de creer
                selection_niveau_Window = openWindow(W_fenetre, H_fenetre, menu);
                setActiveWindow(selection_niveau_Window);
                rafraichir_affichage = true;
            }
            int largeur_index_page = 2*taille_bouton_bas; // largeur allouee a l'affichage de page/nombre_page
            int x_page = W_fenetre - marge_bouton_bas - 2*taille_bouton_bas - largeur_index_page;
            if ((x > x_page) && (x < x_page + taille_bouton_bas)) { // page precedente
                page = max(page-1, 0);
                rafraichir_affichage = true;
            }
            if ((x > W_fenetre - marge_bouton_bas - taille_bouton_bas) && (x < W_fenetre - marge_bouton_bas)) { // page suivante
                page = page+1;
                rafraichir_affichage = true;
            }
        }
    }
}

void menu_categorie_niveau(int taille_case){
    const int W_menu = 1200;
    const int H_menu = 1400;
    const int marge_menu_x = int(W_menu/6);
    const int marge_menu_y = int(H_menu/10);

    const string selection = "Selection de la catégorie de niveau";
    Window menu_Window = openWindow(W_menu, H_menu, selection);

    draw_categorie_niveau(W_menu, H_menu, marge_menu_x, marge_menu_y);

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
                    draw_categorie_niveau(W_menu, H_menu, marge_menu_x, marge_menu_y);
                }
                else if (k==1){
                    selection_niveau(true, taille_case);
                    menu_Window = openWindow(W_menu, H_menu, selection);
                    draw_categorie_niveau(W_menu, H_menu, marge_menu_x, marge_menu_y);
                }

                else if (k==2){
                    fin = true;
                }
            }
        }
    }

}

void menu_regles(){
    // Ouverture du fichier .txt des regles du jeu.
    // La fonction system execute une commande, ici l'ouverture du .txt des regles du jeu.
    // Or, des problemes surviennent avec l'utilisation de srcPath. Notre hypothese est que les problemes surviennent lorsque des espaces existent dans les noms de dossier du chemin vers le .txt.
    // Ainsi, en commentaire, on a renseigné notre chemin local en echappant par un antislash des guillemets encadrant le nom du dossier posant probleme...
//    int result = system("D:/Documents/Etudes/\"Ponts et Chaussees\"/Cours/COVD/projet-COVD/regles_du_jeu.txt");
    int result = system(srcPath("regles_du_jeu.txt"));

    if (result) { // En cas de mauvais chargement, on ouvre une fenetre avec un message d'erreur
        const int W_message = 700;
        const int H_message = 100;
        const int marge_x = int(W_message/12);
        const int marge_y = int(H_message/2);

        const string menu = "Erreur";
        Window message_Window = openWindow(W_message, H_message, menu);
        setActiveWindow(message_Window);
        fillRect(0, 0, W_message, H_message, BLACK);

        string message = "Désolé, fichier \"regles_du_jeu.txt\" introuvable.";
        string message2 = "Veuillez y accéder directement dans les dossiers du jeu !";
        drawString(marge_x, marge_y, message, WHITE, W_message/50);
        drawString(marge_x, marge_y + W_message/25, message2, WHITE, W_message/50);
        click();
        closeWindow(message_Window);
    }
}

void lancer_menu(int taille_case) {
    const int W_menu = 1200;
    const int H_menu = 1442;
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
                    menu_regles();
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

