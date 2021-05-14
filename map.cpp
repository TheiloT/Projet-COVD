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

void Map::drawCase(int x, int y, int taille_case) const{

    int bloc = grille_blocs(x, y);
    int couleur = grille_couleurs(x, y);

    if (bloc == vide) fillRect(x*taille_case, y*taille_case, taille_case, taille_case, WHITE); // Il n'y a rien

    else if (bloc == mur_non_modif) {
        // Couleur du bloc
        if (couleur == neutre) fillRect(x*taille_case, y*taille_case, taille_case, taille_case, BLACK);

        else if (couleur == rouge) fillRect(x*taille_case, y*taille_case, taille_case, taille_case, RED);

        else if (couleur == vert) fillRect(x*taille_case, y*taille_case, taille_case, taille_case, GREEN);

        else if (couleur == bleu) fillRect(x*taille_case, y*taille_case, taille_case, taille_case, BLUE);
    }

    else if (bloc == mur_modif) fillRect(x*taille_case, y*taille_case, taille_case, taille_case, PURPLE); // On représente pour l'instant les blocs modifiables en violet

    else if (bloc == porte_entree){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, WHITE);
        drawCircle(x*taille_case+(1.0/2.0)*taille_case-1, y*taille_case+(1.0/2.0)*taille_case-1, (5.0/8.0)*taille_case-2, CYAN, 2);
        drawCircle(x*taille_case+(1.0/2.0)*taille_case-1, y*taille_case+(1.0/2.0)*taille_case-1, (3.0/8.0)*taille_case-2, CYAN, 2);
        drawPoint(x*taille_case+(1.0/2.0)*taille_case-1, y*taille_case+(1.0/2.0)*taille_case-1, CYAN);
    }

    else if (bloc == porte_sortie){
        fillRect(x*taille_case, y*taille_case, taille_case, taille_case, WHITE);
        fillRect(x*taille_case, y*taille_case+(1.0/2.0)*taille_case, taille_case-1, (1.0/2.0)*taille_case, ORANGE);
        fillCircle(x*taille_case+(1.0/2.0)*taille_case-1, y*taille_case+(1.0/2.0)*taille_case-1, (1.0/2.0)*taille_case-1, ORANGE);
        fillCircle(x*taille_case+(3.0/4.0)*taille_case-1, y*taille_case+(3.0/5.0)*taille_case, (1.0/10.0)*taille_case, BLACK);
    }

    else if (est_dans(bloc, effets_couleur)){
            fillRect(x*taille_case, y*taille_case, taille_case-1, taille_case-1, WHITE);
            drawRect(x*taille_case, y*taille_case, taille_case-1, taille_case-1, BLACK);
            if (bloc == rend_neutre) fillCircle(x*taille_case+taille_case/2, y*taille_case+taille_case/2, taille_case/3, BLACK);
            else if (bloc == rend_rouge) fillCircle(x*taille_case+taille_case/2, y*taille_case+taille_case/2, taille_case/3, RED);
            else if (bloc == rend_vert) fillCircle(x*taille_case+taille_case/2, y*taille_case+taille_case/2, taille_case/3, GREEN);
            else if (bloc == rend_bleu) fillCircle(x*taille_case+taille_case/2, y*taille_case+taille_case/2, taille_case/3, BLUE);
        }

    else if (bloc == saut){
        fillRect(x*taille_case, y*taille_case, taille_case-1, taille_case-1, WHITE);
        drawRect(x*taille_case, y*taille_case, taille_case-1, taille_case-1, BLACK);
        fillRect(x*taille_case+(1.0/7.0+5.0/28.0)*taille_case, y*taille_case+(1.0/9.0+7.0/18.0)*taille_case,
                 (7.0/18.0)*taille_case, (5.0/14.0)*taille_case, PURPLE); // Base de la fleche epaisse
        int coord_triangle[6] = {int(x*taille_case+(1.0/7.0)*taille_case), int(y*taille_case+(1.0/9.0+7.0/18.0)*taille_case),
                                 int(x*taille_case+(1.0/2.0)*taille_case), int(y*taille_case+(1.0/9.0)*taille_case),
                                 int(x*taille_case+(6.0/7.0)*taille_case), int(y*taille_case+(1.0/9.0+7.0/18.0)*taille_case)}; // coordonnées x1, y1, x2, y2, x3, y3.
        fillPoly(coord_triangle, 3, PURPLE);
    }

    else if (bloc == retour_arriere){
        fillRect(x*taille_case, y*taille_case, taille_case-1, taille_case-1, WHITE);
        drawRect(x*taille_case, y*taille_case, taille_case-1, taille_case-1, BLACK);

        // fleche vers la droite
        drawLine(x*taille_case+(1.0/4.0)*taille_case, y*taille_case+(1.0/3.0)*taille_case,
                 x*taille_case+(3.0/4.0)*taille_case, y*taille_case+(1.0/3.0)*taille_case, PURPLE, 2);
        int coord_triangle1[6] = {int(x*taille_case+(3.0/4.0)*taille_case+1), int(y*taille_case+(1.0/3.0)*taille_case),
                                 int(x*taille_case+(3.0/4.0)*taille_case-(1.0/6.0)*taille_case), int(y*taille_case+(1.0/3.0)*taille_case-(1.0/4.0)*taille_case),
                                 int(x*taille_case+(3.0/4.0)*taille_case-(1.0/6.0)*taille_case), int(y*taille_case+(1.0/3.0)*taille_case+(1.0/4.0)*taille_case)};
        fillPoly(coord_triangle1, 3, PURPLE);

        // fleche vers la gauche
        drawLine(x*taille_case+(1.0/4.0)*taille_case, y*taille_case+(2.0/3.0)*taille_case+1,
                 x*taille_case+(3.0/4.0)*taille_case, y*taille_case+(2.0/3.0)*taille_case+1, PURPLE, 2);
        int coord_triangle2[6] = {int(x*taille_case+(1.0/4.0)*taille_case)-1, int(y*taille_case+(2.0/3.0)*taille_case+1),
                                 int(x*taille_case+(1.0/4.0)*taille_case+(1.0/6.0)*taille_case), int(y*taille_case+(2.0/3.0)*taille_case-(1.0/4.0)*taille_case+1),
                                 int(x*taille_case+(1.0/4.0)*taille_case+(1.0/6.0)*taille_case), int(y*taille_case+(2.0/3.0)*taille_case+(1.0/4.0)*taille_case+1)};
        fillPoly(coord_triangle2, 3, PURPLE);
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
