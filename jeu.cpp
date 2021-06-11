#include "jeu.h"
#include "correspondance.h"
#include "edition.h"
#include "personnage.h"
#include "outils.h"

// Fonctions pour le mode "jouer"

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

bool getAction_joueur(int x, int y, int &bouton_action, int bande_texte, int L, int taille_case, int taille_case_editeur){
    int x_dep = L*taille_case;
    if ( y < bande_texte + 1.5*taille_case_editeur && y > bande_texte + 0.5*taille_case_editeur){ // Verifie si la souris est a la bonne hauteur
        float num_x = (2.0 *(x - x_dep) / float(taille_case_editeur)) / 3.0; // Numero du bouton (numerotation de gauche a droite)
        if (num_x - floor(num_x) > 1/3.0
                && floor(num_x >= 0 && floor(num_x) < 4)){
            int numero_case=floor(num_x);
            bouton_action = (numero_case == 1) ? 3 : numero_case; // Si floor(num_x) correspond à "sauvergarder", on change pour "reset"
            return true;
        }
    }
    return false;
}

void prepare_map(Map map, int L, int H, std::map<int, int> &blocs_disponibles) {
    int k; // case courante
    for (int i=0; i<H; i++) { // On parcourt l'ensemble de la map
        for (int j=0; j<L; j++) {
            k = map.get_case(j, i);
            if (est_dans(k, effets)) { // Si le bloc est un effet, on le convertit en bloc modifiable et on incremente le stock d'effets correspondant
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

void trace_etoile_pleine_vide(int x, int y, int taille_etoile, bool collectee) {
    int demi = taille_etoile/2;
    int h = int (0.75*float(taille_etoile));

    int liste_1[6] = {x + demi, y, x, y + h, x + taille_etoile, y + h}; // Premier triangle
    int liste_2[6] = {x, y + taille_etoile - h, x + demi, y + taille_etoile, x + taille_etoile, y + taille_etoile - h}; // Deuxieme triangle

    if (collectee) {
        fillPoly(liste_1, 3, YELLOW);
        fillPoly(liste_2, 3, YELLOW);
    }
    else {
        drawPoly(liste_1, 3, YELLOW);
        drawPoly(liste_2, 3, YELLOW);
        int liste_1_noir[6] = {x + demi, y + 1, x + 1, y + h - 1, x + taille_etoile - 1, y + h - 1}; // Premier triangle noir
        int liste_2_noir[6] = {x + 1, y + taille_etoile - h + 1, x + demi, y + taille_etoile - 1, x + taille_etoile - 1, y + taille_etoile - h + 1}; // Deuxieme triangle noir
        fillPoly(liste_1_noir, 3, BLACK);
        fillPoly(liste_2_noir, 3, BLACK);
    }
}

void affiche_etoiles(int x, int y, int hauteur_etoile, int largeur_etoiles, int nb_etoiles_collectees) {
    const int taille_etoile = hauteur_etoile/2;
    const int marge_etoile = taille_etoile/2;
    int x_etoiles = x + largeur_etoiles/2 - (3*taille_etoile + 2*marge_etoile)/2;
    for (int i=0; i<3; i++) {
        int collectee = (i < nb_etoiles_collectees); // Le nombre d'etoiles pleines affichees (jusqu'a 3) est le nombre d'etoiles collectees durant la partie, les autres apparaissant creuses.
        trace_etoile_pleine_vide(x_etoiles + i*(taille_etoile + marge_etoile), y, taille_etoile, collectee);
    }
}

void affiche_retour(int x, int y, int taille_bouton){
    drawRect(x, y, taille_bouton, taille_bouton, WHITE, 2);
    ecris_dans_la_case(x-2, y, taille_bouton, taille_bouton, "X", taille_bouton/2, WHITE);
}

void affiche_victoire(int nb_etoiles_collectees) { // Affiche que le niveau est gagne
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
    ecris_dans_la_case(x_gagne, y_gagne, W_victoire - 2*marge_x, hauteur_gagne, mots_victoire[mot], hauteur_gagne/5, RED);

    // Affichage des étoiles
    int y_etoiles = marge_y + hauteur_gagne;
    affiche_etoiles(marge_x, y_etoiles, hauteur_etoiles, W_victoire - 2*marge_x, nb_etoiles_collectees);

    // Affichage du bouton de retour
    int x_retour = W_victoire/2 - taille_bouton/2;
    int y_retour = y_etoiles + hauteur_etoiles + hauteur_retour/2 - taille_bouton/2;
    affiche_retour(x_retour, y_retour, taille_bouton);

    click();
    closeWindow(victoire_Window);

}

bool run (const Map &map, int taille_case, int &nb_etoiles_collectees){ // Joue le niveau

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
    if (perso.est_arrive()) nb_etoiles_collectees = perso.get_nb_etoile();
    return(perso.est_arrive());
}

void jouer(Map map, int taille_case) {
    // Geometrie
    const int L = map.get_L();
    const int H = map.get_H();
    const string nom = map.get_nom();

    // Vecteur des stocks de chaque effet disponibles
    std::map<int, int> blocs_disponibles;
    for (int k=0; k<int(effets.size()); k++)
        blocs_disponibles[effets[k]] = 0;

    prepare_map(map, L, H, blocs_disponibles);

    const int taille_case_editeur = 2*taille_case; // dimension d'une case de l'editeur (bouton)
    const int bande_texte = taille_case_editeur; // hauteur de la bande contenant le nom du niveau
    const int nb_lignes = 2; // nombre de lignes de boutons

    // Ouverture de la fenetre
    const int H_win = max( H*taille_case, int(bande_texte + (9.0 * taille_case_editeur)) );
    Window w = openWindow(L*taille_case + 6.5 * taille_case_editeur, H_win);
    setActiveWindow(w);
    // Affichage de la map, de la grille et des boutons
    map.affiche_tout(taille_case);
    affiche_boutons_joueur(L, H, taille_case, taille_case_editeur, bande_texte, nom, blocs_disponibles);

    int bouton_action = 4; // Correspond a aucune action
    int bouton_effet = 7; // Correspond au mur modifiable

    // Coordonnees de la souris
    int x;
    int y;

    bool fin = false;
    while ( ! fin ){ // boucle principale

        getMouse(x, y);

        if (getEffet(x, y, bouton_effet, bande_texte, L, taille_case, taille_case_editeur, nb_lignes)); // Le joueur selectionne un effet

        else if ( getAction_joueur(x, y, bouton_action, bande_texte, L, taille_case, taille_case_editeur) ){
            if (bouton_action == bouton_play){ // Si le joueur lance la partie
                int nb_etoiles_collectees;
                fin = run(map, taille_case, nb_etoiles_collectees);
                map.affiche_tout(taille_case);
                if (fin){ // Si le joueur gagne la partie, on affiche la fenetre de victoire
                    affiche_victoire(nb_etoiles_collectees);
                    closeWindow(w);
                }
            }
            else if (bouton_action == bouton_reset){ // Reinitialise le placement des effets
                prepare_map(map, L, H, blocs_disponibles);
                map.affiche_tout(taille_case);
                affiche_boutons_joueur(L, H, taille_case, taille_case_editeur, bande_texte, nom, blocs_disponibles);
            }
            else if (bouton_action == bouton_quitter){ // Retour vers le menu precedent
                closeWindow(w);
                fin = true;
            }
        }

        else if (placeBloc(x, y, L, H, taille_case)){ // Le joueur place un effet
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
            affiche_boutons_joueur(L, H, taille_case, taille_case_editeur, bande_texte, nom, blocs_disponibles);
        }
    }
}
