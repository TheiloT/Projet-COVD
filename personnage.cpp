#include "personnage.h"
#include "correspondance.h"

#include "outils.h"

Personnage::Personnage(const Map &map){

    float vitesse = 0.125; // Regle la vitesse du perso

    int x0, y0; // Coordonnee de depart
    for (int j=0; j<map.L; j++){
        for (int i=0; i<map.H; i++){
            if ( map.get_case(j,i) == porte_entree ){
                x0 = j;
                y0 = i;
            }
        }
    }
    x = x0;
    y = y0;
    vx = vitesse;
    vy = 0;
    vivant = true;
    arrive = false;
    couleur = neutre;
    actualiser_coins();
    actualiser_detecteurs();
    x_change_dir = -1;
    y_change_dir = -1;
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

        assertion =    est_dans(k, murs)
                    || est_dans(k, effets_action)
                    || est_dans(k, effets_couleur);
        i+=1;
    }
    return assertion;
}

bool Personnage::est_sur_terre(const Map &map) const{
    return (    vy == 0
             && il_y_a_de_la_terre_en_dessous(map) );
}

void Personnage::actualiser_coins(){
    const float marge_hitbox = 0.01;
    Coins[0] = Point (x + marge_hitbox, y + 1 - marge_hitbox);
    Coins[1] = Point (x + marge_hitbox, y + marge_hitbox);
    Coins[2] = Point (x + 1 - marge_hitbox, y + 1 - marge_hitbox);
    Coins[3] = Point (x + 1 - marge_hitbox, y + marge_hitbox);
}

void Personnage::actualiser_detecteurs(){
    const float marge_hitbox = 0.01;
    Detecteurs[0] = Point (x + marge_hitbox, y + 1 + marge_hitbox);
    Detecteurs[1] = Point (x + 1 - marge_hitbox, y + 1 + marge_hitbox);
}

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
    while (   i<4
           && !collision_resolue){

        Point coin = Coins[i];
        int x_c = floor(coin.x);
        int y_c = floor(coin.y);
        int k = map.get_case(x_c, y_c); // Contenu de la case dans laquelle se trouve le coin

        if (       est_dans(k, murs)
                || est_dans(k, effets_action)
                || est_dans(k, effets_couleur) ){

            il_y_a_eu_collision = true;
            int x_c_prev = floor(coin.x - vx);
            int y_c_prev = floor(coin.y - vy);

            int delta_x = x_c - x_c_prev;
            int delta_y = y_c - y_c_prev;

            if ( delta_y == 0 && delta_x != 0){ // Percute un mur
                vivant = false;
                collision_resolue = true;
            }

            else if ( delta_x == 0 && delta_y != 0){ // Touche un mur
                y = y_c_prev;
                collision_resolue = true;
            }

            else{               // Type de collision indetermine

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
        vy = 0;
    }
}

void Personnage::cherche_sortie(const Map &map){
    int i =0;
    while (i<4){
        Point coin = Coins[i];
        int x_c = floor(coin.x);
        int y_c = floor(coin.y);
        int k = map.get_case(x_c, y_c); // Contenu de la case dans laquelle se trouve le coin
        if (k == porte_sortie){
                    arrive = true; // Arrive à la case d'arrivee
        }
        i += 1;
    }
}

void Personnage::affiche(int taille_case) const{
    if (couleur == neutre) fillRect(x*taille_case, y*taille_case, taille_case, taille_case, BLACK);

    else if (couleur == rouge) fillRect(x*taille_case, y*taille_case, taille_case, taille_case, RED);

    else if (couleur == vert) fillRect(x*taille_case, y*taille_case, taille_case, taille_case, GREEN);

    else if (couleur == bleu) fillRect(x*taille_case, y*taille_case, taille_case, taille_case, BLUE);

    drawLine(x*taille_case+1, y*taille_case+1, x*taille_case+taille_case-1, y*taille_case+taille_case-1, WHITE, 2);

    drawLine(x*taille_case+1, y*taille_case+taille_case-1, x*taille_case+taille_case-1, y*taille_case+1, WHITE, 2);
}

void Personnage::gravite(){
    vy += 0.02; // On prend g = 0.02
}

void Personnage::sauter(){
    const float vitesse_saut = 0.42;
    vy = -vitesse_saut;
}

void Personnage::retourner_en_arriere(int x_d, int y_d){
    if (x_d != x_change_dir || y_d != y_change_dir){
        vx = -vx;
        x_change_dir = x_d;
        y_change_dir = y_d;
    }
}

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
