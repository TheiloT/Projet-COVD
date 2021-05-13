#include "personnage.h"

#include "vector"
using namespace std;

void Personnage::actualiser_coins(){
    const float marge_hitbox = 0.01;
    Coins[0] = Point (x + marge_hitbox, y + 1 - marge_hitbox);
    Coins[1] = Point (x + marge_hitbox, y + marge_hitbox);
    Coins[2] = Point (x + 1 - marge_hitbox, y + 1 - marge_hitbox);
    Coins[3] = Point (x + 1 - marge_hitbox, y + marge_hitbox);
}

Personnage::Personnage(int x0, int y0, float vitesse){
    x = x0;
    y = y0;
    vx = vitesse;
    vy = 0;
    vivant = true;
    arrive = false;
    actualiser_coins();
    x_change_dir = -1;
    y_change_dir = -1;
}

bool Personnage::est_vivant(){
    return vivant;
}

bool Personnage::est_arrive(){
    return arrive;
}

void Personnage::actualise_position(){
    x += vx;
    y += vy;
    actualiser_coins();
}

void Personnage::collision(Map map){

    int i=0;
    bool collision_resolue = false;
    while (   i<4
           && !collision_resolue){

        Point coin = Coins[i];
        int x_c = floor(coin.x);
        int y_c = floor(coin.y);
        int k = map.get_case(x_c, y_c); // Contenu de la case dans laquelle se trouve le coin

        if (k == 1 || k == 2 || k == 4){

            int x_c_prev = floor(coin.x - vx);
            int y_c_prev = floor(coin.y - vy);

            int delta_x = x_c - x_c_prev;
            int delta_y = y_c - y_c_prev;

            if ( delta_x != 0
              && delta_y == 0){ // Percute un mur

                vivant = false;
                collision_resolue = true;
            }

            else if ( delta_x == 0
                   && delta_y != 0){ // Touche un mur

                y = y_c_prev;
                vy = 0;
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
                        vy = 0;
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
                        vy = 0;
                        collision_resolue = true;
                    }
                }
            }
        }

        else if (k == 3){
            arrive = true; // Arrive à la case d'arrivee
            collision_resolue = true;
        }

        i += 1;
    }
}

void Personnage::affiche(int taille_case){
    fillRect(x*taille_case, y*taille_case, taille_case, taille_case, RED);
}

void Personnage::gravite(float g){
    vy += g;
}

void Personnage::interragit(Map map){

    const float vitesse_saut = 0.42;
    const float marge_hitbox = 0.01;

    if (    map.get_case(floor(x), floor(y + 1 + marge_hitbox)) == 2
         || map.get_case(floor(x+1), floor(y + 1 + marge_hitbox)) == 2 ){ // Saut

        vy = -vitesse_saut;

    }

    if (    map.get_case(floor(x), floor(y + 1 + marge_hitbox)) == 4 ){ // Retour arrière par la droite

         if (    x_change_dir != floor(x)
              || y_change_dir != floor(y + 1 + marge_hitbox) ){

             vx = -vx;
             x_change_dir = floor(x);
             y_change_dir = floor(y + 1 + marge_hitbox);
         }
    }
    if (    map.get_case(floor(x+1), floor(y + 1 + marge_hitbox)) == 4 ){ // Retour arrière par la gauche

         if (    x_change_dir != floor(x+1)
              || y_change_dir != floor(y + 1 + marge_hitbox) ){

             vx = -vx;
             x_change_dir = floor(x+1);
             y_change_dir = floor(y + 1 + marge_hitbox);
         }
    }

}

