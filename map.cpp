#include "map.h"

Map::Map(int h, int l)
{
    H = h;
    L = l;
    grille = MultiArray<int, 2> (L, H);
    grille.fill(0);
}

void Map::drawCase(int x, int y, int taille_case){

    if (grille(x,y) == 0){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, WHITE); // Il n'y a rien
    }

    if (grille(x,y) == 1){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, BLACK); // Le sol en noir
    }

    if (grille(x,y) == 2){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, GREEN); // Les sauts en vert
    }

    if (grille(x,y) == 3){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, YELLOW); // La fin en jaune
    }

    if (grille(x,y) == 4){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, PURPLE); // Les retours arriere en purple
    }
}

void Map::affiche(int taille_case){
    for (int x=0; x<L; x++){
        for (int y=0; y<H; y++){
            drawCase(x, y, taille_case);
        }
    }
}

void Map::set_case(int x, int y, int k){
    grille(x,y) = k;
}

int Map::get_case(int x, int y){
    return grille(x, y);
}

void Map::load(int k){

    string const nomFichier("Niveaux.txt");
    ifstream flux(nomFichier.c_str());

    if(flux)
    {
        for(int n=0; n<k; n++){
            string map_name;
            flux >> map_name;
            int h,l;
            flux >> h;
            flux >> l;
            for (int x=0; x<L; x++){
                for (int y=0; y<H; y++){
                    int valeur = get_case(x, y);
                    flux >> valeur;
                }
            }
        }

        string map_name;
        flux >> map_name;
        int h,l;
        flux >> h;
        H = h;
        flux >> l;
        L = l;
        for (int x=0; x<L; x++){
            for (int y=0; y<H; y++){
                int valeur = get_case(x, y);
                flux >> valeur;
                grille(x, y) = valeur;
            }
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}
