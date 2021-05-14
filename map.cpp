#include "map.h"
#include "correspondance.h"

Map::Map(int h, int l)
{
    H = h; // Hauteur
    L = l; // Longueur
    grille_blocs = MultiArray<int, 2> (L, H);
    grille_blocs.fill(vide);
    grille_couleurs = MultiArray<int, 2> (L, H);
    grille_couleurs.fill(neutre);
}

void drawTriangle(int j, int i, int k, int taille_case){

    int x = j*taille_case;
    int y = i*taille_case;
    int demi = taille_case/2;

    int xa = x;
    int xb = x + demi;
    int xc = x + taille_case;
    int xd = x + taille_case;
    int xe = x + taille_case;
    int xf = x + demi;
    int xg = x;
    int xh = x;

    int ya = y + taille_case;
    int yb = y + taille_case;
    int yc = y + taille_case;
    int yd = y + demi;
    int ye = y;
    int yf = y;
    int yg = y;
    int yh = y + demi;

    if (k == pic_bas){
        int liste_points[6] = {xa, ya, xc, yc, xf, yf};
        fillPoly(liste_points, 3, BLACK);
    }

    else if (k == pic_droite){
        int liste_points[6] = {xc, yc, xe, ye, xh, yh};
        fillPoly(liste_points, 3, BLACK);
    }

    else if (k == pic_haut){
        int liste_points[6] = {xg, yg, xe, ye, xb, yb};
        fillPoly(liste_points, 3, BLACK);
    }

    else{
        int liste_points[6] = {xg, yg, xa, ya, xd, yd};
        fillPoly(liste_points, 3, BLACK);
    }


}

void Map::drawCase(int x, int y, int taille_case) const{

    int bloc = grille_blocs(x,y);

    if (grille_blocs(x,y) == vide){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, WHITE); // Il n'y a rien
    }

    else if (grille_blocs(x,y) == mur_modif || grille_blocs(x,y) == mur_non_modif){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, BLACK); // Le sol en noir
    }

    else if (grille_blocs(x,y) == saut){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, GREEN); // Les sauts en vert
    }

    else if (grille_blocs(x,y) == porte_sortie){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, YELLOW); // La fin en jaune
    }

    else if (grille_blocs(x,y) == porte_entree){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, ORANGE); // Le debut en orange
    }

    else if (grille_blocs(x,y) == retour_arriere){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, PURPLE); // Les retours arriere en purple
    }

    else if ( est_dans (bloc, pics) ){
        drawTriangle (x, y, bloc, taille_case);
    }
}

void Map::affiche(int taille_case) const{
    for (int x=0; x<L; x++){
        for (int y=0; y<H; y++){
            drawCase(x, y, taille_case);
        }
    }
}

void Map::set_case(int x, int y, int k){
    grille_blocs(x,y) = k;
}

int Map::get_case(int x, int y) const{
    return grille_blocs(x, y);
}

void Map::set_couleur(int x, int y, int k){
    grille_couleurs(x,y) = k;
}

int Map::get_couleur(int x, int y) const{
    return grille_couleurs(x, y);
}

void Map::load(int k){

    string const nomFichier(srcPath("Niveaux.txt"));
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
                grille_blocs(x, y) = valeur;
            }
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}
