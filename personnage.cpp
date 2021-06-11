#include "personnage.h"
#include "correspondance.h"

Personnage::Personnage(const Map &map){

    float vitesse = 0.125; // Regle la norme de la vitesse du perso

    int x0, y0; // Coordonnees de depart
    for (int j=0; j<map.get_L(); j++){
        for (int i=0; i<map.get_H(); i++){
            if ( est_dans(map.get_case(j, i), portes_entree) ){
                // Fixe les coordonnees de depart a la position de la porte d'entree
                x0 = j;
                y0 = i;
            }
        }
    }
    x = x0;
    y = y0;

    // Fixe la vitesse initiale horizontale suivant le sens de la porte d'entree
    vx = (map.get_case(x0, y0)==porte_entree_droite) ? vitesse : -vitesse;
    vy = 0;

    // Initialisation de l'etat du personnage
    vivant = true;
    arrive = false;

    // Initialisation de la couleur du personnage: le personnage prend la couleur de la porte d'entree
    couleur = map.get_couleur(x0, y0);

    // Reglage des hitbox
    actualiser_coins();
    actualiser_detecteurs();

    // Initialisation de la position du dernier retour en arriere en dehors de la map
    x_change_dir = -1;
    y_change_dir = -1;

    nb_etoile = 0;
    Liste_etoiles_collectees = {};
    // Nous n'avons pas eu le temps d'implémenter les etoiles comme initialement pense donc cet attribut n'est pas utilise,
    // mais aurait pu l'être pour mieux gerer les etoiles effectivement collectees par le joueur
}

float Personnage::get_x() const{
    return x;
}

float Personnage::get_y() const{
    return y;
}

int Personnage:: get_couleur() const{
    return couleur;
}

void Personnage:: set_couleur(int k){
    couleur = k;
}

bool Personnage::est_vivant() const{
    return vivant;
}

bool Personnage::est_arrive() const{
    return arrive;
}

bool Personnage::il_y_a_de_la_terre_en_dessous(const Map &map) const{
    bool assertion = false;
    int i = 0;
    while (i<2 && !assertion){
        Point detecteur = Detecteurs[i];
        int x_d = floor(detecteur.x);
        int y_d = floor(detecteur.y);
        int k = map.get_case(x_d, y_d); // Contenu de la case dans laquelle se trouve le detecteur

        //  Renvoit true si la case detectee est un mur ou un effet et qu'en plus le personnage ne traverse pas ce bloc
        assertion =      (  est_dans(k, murs) || est_dans(k, effets ))
                      && ( couleur != map.get_couleur(x_d, y_d) || couleur == neutre ) ;
        i+=1;
    }
    return assertion;
}

// Ajout de la condition de vitesse horizontale pour etre sur que le joueur court sur le sol
bool Personnage::est_sur_terre(const Map &map) const{
    return (    vy == 0
             && il_y_a_de_la_terre_en_dessous(map) );
}

// Actualise les 4 coins qui constituent la hitbox interieure du personnage
void Personnage::actualiser_coins(){
    const float marge_hitbox = 0.01;
    Coins[0] = Point (x + marge_hitbox, y + 1 - marge_hitbox);
    Coins[1] = Point (x + marge_hitbox, y + marge_hitbox);
    Coins[2] = Point (x + 1 - marge_hitbox, y + 1 - marge_hitbox);
    Coins[3] = Point (x + 1 - marge_hitbox, y + marge_hitbox);
}

// Actualise les 2 detecteurs qui permettent au personnage de detecter les blocs qui se trouvent en dessous de lui
void Personnage::actualiser_detecteurs(){
    const float marge_hitbox = 0.01;
    Detecteurs[0] = Point (x + marge_hitbox, y + 1 + marge_hitbox);
    Detecteurs[1] = Point (x + 1 - marge_hitbox, y + 1 + marge_hitbox);
}

// Actualise la position a l'aide de la vitesse
void Personnage::actualise_position(){
    x += vx;
    y += vy;
    actualiser_coins();
    actualiser_detecteurs();
}

void Personnage::collision( const Map &map){

    int i=0;
    bool collision_resolue = false;
    bool il_y_a_eu_collision = false;

    // Boucle sur les coins qui forment la hitbox du personnage tant que la collision n'est pas resolue
    while (   i<4
           && !collision_resolue){

        Point coin = Coins[i];
        int x_c = floor(coin.x);
        int y_c = floor(coin.y);
        int k = map.get_case(x_c, y_c); // Contenu de la case dans laquelle se trouve le coin

        // Coordonnees du coin a l'instant precedant
        int x_c_prev = floor(coin.x - vx);
        int y_c_prev = floor(coin.y - vy);

        // Variation horizontales et verticales entre l'instant precedant la collision et l'instant present de collision
        int delta_x = x_c - x_c_prev;
        int delta_y = y_c - y_c_prev;

        // Verifie si on sort de la map
        if ( (x_c + delta_x < 0) || (x_c + delta_x >= map.get_L()) || (y_c + delta_y < 0) || (y_c + delta_y >= map.get_H()) ) {
            collision_resolue = true;
            vivant = false;
        }

        // Si le bloc dans lequel se trouve le coin est un bloc que ne peut pas traverser le personnage
        else if (     ( couleur != map.get_couleur(x_c, y_c) || couleur == neutre )
                 &&
                 ( est_dans(k, murs)
                || est_dans(k, effets_action)
                || est_dans(k, effets_couleur) ) ){

            il_y_a_eu_collision = true; // Alors il y a eu une collision

            // Il reste a savoir si cette collision est une collision verticale (le personnage touche un mur)
            // et ne provoque pas la mort ou si cette collision est horizontale (le personnage percute un mur)
            // et provoque la mort

            if ( delta_y == 0 && delta_x != 0){ // Percute un mur
                vivant = false;
                collision_resolue = true;
            }

            else if ( delta_x == 0 && delta_y != 0){ // Touche un mur
                y = y_c_prev; // Lorsque qu'il y a collision car le personnage a touche un mur, on replace le personnage a sa place c'est a dire sur le bloc ou juste en dessous
                collision_resolue = true;
            }

            else{               // Le type de collision reste indetermine apres ce premier test nous faisons maintenant de la geometrie

                // Coefficients de la droite formée par le point actuel et le point precedant
                float a = delta_y / delta_x;
                float b = ( y_c + y_c_prev- a*(x_c + x_c_prev) ) / 2;
                float f_collision = a*x_c + b;

                if (delta_y > 0){ // Collision par le haut
                    float f_coin = y_c;
                    if (f_coin > f_collision){
                        vivant = false;
                        collision_resolue = true;
                    }
                    else{
                        y = y_c_prev;
                        collision_resolue = true;
                    }
                }


                else{             // Collision par le bas
                    float f_coin = y_c - 1;
                    if (f_coin < f_collision){
                        vivant = false;
                        collision_resolue = true;
                    }
                    else{
                        y = y_c_prev;
                        collision_resolue = true;
                    }
                }
            }
        }
        i += 1;
    }

    if (il_y_a_eu_collision){
        vy = 0; // Lorsque qu'il y a collision car le personnage a touche un mur, on ne conserve que sa vitesse selon x
                //afin que le personnage passe le test est_sur_terre aux instants suivants si rien ne se passe entre temps
    }
}

// Retourne true si la sortie est dans la hitbox du personnage
void Personnage::cherche_sortie(const Map &map){
    int i =0;
    while (i<4){
        Point coin = Coins[i];
        int x_c = floor(coin.x);
        int y_c = floor(coin.y);
        int k = map.get_case(x_c, y_c); // Contenu de la case dans laquelle se trouve le coin
        int map_couleur = map.get_couleur(x_c, y_c);
        if (k == porte_sortie && (map_couleur == neutre || map_couleur == couleur)){
                    arrive = true; // Arrive à la case d'arrivee
        }
        i += 1;
    }
}

// Affichage du personnage
void Personnage::affiche(int taille_case) const{
    int u = x*taille_case;
    int v = y*taille_case;
    int epaisseur = taille_case/15;

    fillRect(u, v, taille_case, taille_case, couleur_int_vers_color.at(couleur));

    drawRect(u, v, taille_case-1, taille_case-1, WHITE, epaisseur);
    drawLine(u, v, u + taille_case - 1, v + taille_case - 1, WHITE, epaisseur);
    drawLine(u, v + taille_case - 1, u + taille_case - 1, v, WHITE, epaisseur);
}

// Affichage de mort: des rectangles de couleurs aleatoires entourent le perso
void Personnage::affiche_mort(const Map &map, int taille_case) const{
    int u = x*taille_case;
    int v = y*taille_case;
    int epaisseur = taille_case/4;

    map.affiche_tout(taille_case);
    fillRect(u, v, taille_case, taille_case, couleur_au_hasard());
    milliSleep(100);
    for (int i=0; i<4; i++) {
        drawRect(u-i*epaisseur/2, v-i*epaisseur/2, taille_case+i*epaisseur, taille_case+i*epaisseur, couleur_au_hasard(), epaisseur);
        milliSleep(100);
    }
}

void Personnage::gravite(){
    vy += 0.02; // On prend g = 0.02
}

void Personnage::sauter(){
    const float vitesse_saut = 0.42; // Parametre de saut
    vy = -vitesse_saut;
}

// Changement de direction en faisant attention: si la case de changement de direction est la dernière visitée
// on n'applique pas une deuxième fois l'effet
void Personnage::retourner_en_arriere(int x_d, int y_d){
    if (x_d != x_change_dir || y_d != y_change_dir){
        vx = -vx;
        x_change_dir = x_d;
        y_change_dir = y_d;
    }
}

// Gere les interractions avec les blocs d'effet
void Personnage::interragit(const Map &map){

    int i=0;
    while (i<2){
        Point detecteur = Detecteurs[i];
        int x_d = floor(detecteur.x);
        int y_d = floor(detecteur.y);
        int k = map.get_case(x_d, y_d); // Contenu de la case dans laquelle se trouve le detecteur

        if (k == saut){
            sauter();
        }

        if (k == retour_arriere){
            retourner_en_arriere(x_d, y_d);
        }

        if (est_dans(k, effets_couleur)){
            if (k==rend_neutre) set_couleur(neutre);
            if (k==rend_rouge) set_couleur(rouge);
            if (k==rend_vert) set_couleur(vert);
            if (k==rend_bleu) set_couleur(bleu);
        }

        i+=1;
    }
}

//Gere les collisions avec la lave
bool collision_lave(float y, int k){
    if (k == lave_totale){
        return true;
    }
    else{
        return y - floor(y) > 0.3333;
    }
}

// Gere les collisions avec les pics
bool collision_pic(float x, float y, int k){
    float x_case_i = x - float(floor(x));
    float y_case_i = y - float(floor(y));
    float x_case = x_case_i;
    float y_case = y_case_i;

    if (k == pic_droite){
        x_case = y_case_i;
        y_case = 1.0 - x_case_i;
    }
    else if (k == pic_haut){
        x_case = 1.0 - x_case_i;
        y_case = 1.0 - y_case_i;
    }
    else if (k == pic_gauche){
        x_case = 1.0 - y_case_i;
        y_case = x_case_i;
    }

    // Conditions geometriques concises: J'effectue une rotation des coordonnees des pics pour faire le test
    // sur le pic oriente de maniere classique
    bool a_gauche = (x_case < 0.5) && (y_case > 1.0 - 2.0*x_case);
    bool a_droite = (x_case > 0.5) && (y_case > (2.0*x_case - 1.0));
    return ( a_gauche || a_droite); // Retourne si il y a une collision sur la partie droite ou la partie gauche du pic
}

// Si cette condition sur le coin i est verifiee le bloc rentre obligatoirement en collision avec le pic de type k
bool est_coin_oppose (int i, int k){
    if (k == pic_bas){
        return (i == 1 || i == 3);
    }
    else if (k == pic_haut){
        return (i == 0 || i == 2);
    }
    else if (k == pic_droite){
        return (i == 0 || i == 1);
    }
    else{
        return (i == 2 || i == 3);
    }
}

// Gere les collisions avec tous les obstacles
void Personnage::collision_obstacle(const Map &map){ // gere les collisions avec les obstacles
    int i = 0;
    while (i<4 && vivant){
        Point coin = Coins[i];
        int x_c = floor(coin.x);
        int y_c = floor(coin.y);
        int k = map.get_case(x_c, y_c); // Contenu de la case dans laquelle se trouve le coin

        if ( est_dans(k, pics) ){

            if (      est_coin_oppose(i, k)
                 && ( couleur != map.get_couleur(x_c, y_c) || couleur == neutre )){
                vivant = false;
            }
            if (    ( couleur != map.get_couleur(x_c, y_c) || couleur == neutre )
                 && collision_pic(coin.x, coin.y, k) ){
                vivant = false;
            }
        }

        else if (    est_dans(k, laves)
                  && collision_lave(coin.y, k) ){
            vivant = false;
        }

        i += 1;
    }
}

// Ramasse les etoiles
void Personnage::cherche_etoile(const Map &map){

    int i =0;
    while (i<4){
        Point coin = Coins[i];
        int x_c = floor(coin.x);
        int y_c = floor(coin.y);
        IntPoint2 point = {x_c, y_c};
        int k = map.get_case(x_c, y_c); // Contenu de la case dans laquelle se trouve le coin

        if (       k == etoile
                && ! est_dans(point, Liste_etoiles_collectees) ){

                    nb_etoile += 1;
                    Liste_etoiles_collectees.push_back(point);
        }

        i += 1;
    }
}

// Retourne le nombre d'etoiles collectees
int Personnage::get_nb_etoile(){
    return nb_etoile;
}
