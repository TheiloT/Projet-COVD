#include "correspondance.h"
#include "outils.h"
#include "menus.h"
#include "edition.h"
#include "map.h"
#include "personnage.h"
#include "Niveaux.h"
#include "graphismes.h"

// ========== Fonctions de jeu et d'edition de niveaux ==========
// Utilisent les fonctions de edition.cpp

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
    if(!perso.est_vivant()) perso.affiche_mort(map, taille_case);
    map.affiche_tout(taille_case, perso); // On affiche la map a la fin
    return(perso.est_arrive());
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

void editer_map(Map map, int taille_case, int num_map, int nb_niveaux, string niveau = "Niveaux_perso"){
    creer_map (map.nom, map.L, map.H, taille_case, true, map, num_map, nb_niveaux, niveau);
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
    const int H_win = max( H*taille_case, int(bande_texte + (9.0 * taille_case_editeur)) );
    Window w = openWindow(L*taille_case + 6.5 * taille_case_editeur, H_win);
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
                    affiche_victoire();
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
// Utilisent les fonction de menus.h

void menu_creation_niveau(){
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
    vector<tuple<string, int>> liste_niveaux = recuperer_niveaux(mode_perso); // Contiendra le nom du niveau et le nombre d'etoiles collectees sur ce niveau (a programmer
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
                int x_boutons = marge_x + largeur_texte_etiquette;
                int num_bouton = (x - x_boutons) / (taille_bouton + marge_bouton);
                bool est_dans_largeur_bouton = (x > (x_boutons + marge_bouton + num_bouton*(taille_bouton + marge_bouton)))
                                                && (x < (x_boutons + marge_bouton + (num_bouton+1)*(taille_bouton + marge_bouton) - marge_bouton));
                if (est_dans_largeur_bouton) {
                        if (num_bouton == 0 && mode_perso) { // Lance l'editeur du niveau
                        closeWindow(selection_niveau_Window);
                        Map map_selectionnee;
                        map_selectionnee.charger(num_niveau, "Niveaux_perso.txt");
                        creer_map(map_selectionnee.nom, map_selectionnee.L, map_selectionnee.H, taille_case, true, map_selectionnee, num_niveau, nombre_niveaux, "Niveaux_perso.txt");
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
                menu_creation_niveau();
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

void menu_regles(){
    int result = system("D:/Documents/Etudes/\"Ponts et Chaussees\"/Cours/COVD/projet-COVD/regles_du_jeu.txt");
//    int result = system(srcPath("regles_du_jeu.txt"));

    if (result) {
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



int main()
{
    initRandom();
    int taille_case = 28;

    lancer_menu(taille_case);
    endGraphics();

    return 0;
}
