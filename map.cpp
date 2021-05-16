#include "map.h"
#include "personnage.h"
#include "correspondance.h"

Map::Map(){
}

Map::Map(int h, int l)
{
    H = h; // Hauteur
    L = l; // Longueur
    grille_blocs = MultiArray<int, 2> (L, H);
    grille_blocs.fill(vide);
    grille_couleurs = MultiArray<int, 2> (L, H);
    grille_couleurs.fill(neutre);
}

// ========== Fonctions des graphismes ==========
// (x, y) : coordonnees en cases ; (u, v) : coordonnees en pixels

void efface_bloc(int x, int y, int taille_case) {
    fillRect(x, y, taille_case, taille_case, WHITE);
}

void contour_bloc(int x, int y, int taille_case) {
   drawRect(x, y, taille_case-1, taille_case-1, BLACK);
}

void trace_bloc(int x, int y, int taille_case, int couleur) {
    fillRect(x, y, taille_case, taille_case, couleur_int_vers_color.at(couleur));
}

void trace_bloc_modif(int x, int y, int taille_case) {
    fillRect(x, y, taille_case, taille_case, PURPLE);
}

void trace_porte_entree(int x, int y, int k, int taille_case, int couleur) {
    int u = x;
    int v = y;
    int demi = taille_case/2;

    // planche de porte
    fillRect(u, v + demi, taille_case, demi, ORANGE);
    fillCircle(u + demi, v + demi, demi-1, ORANGE);

    // La fleche
    int udeb;
    int vdeb;
    int ufin;
    int vfin;
    int ua;
    int ub;
    int uc;
    int va;
    int vb;
    int vc;
    if (k == porte_entree_droite) {
        udeb = u + taille_case/4;
        vdeb = v + 5*taille_case/8;
        ufin = u + 7*taille_case/8;
        vfin = v + 5*taille_case/8;

        ua = ufin + 2;
        ub = ufin - taille_case/5;
        uc = ufin - taille_case/5;

        va = vfin;
        vb = vfin - taille_case/5;
        vc = vfin + taille_case/5;
    }
    else {
        udeb = u + 3*taille_case/4;
        vdeb = v + 5*taille_case/8;
        ufin = u + taille_case/8;
        vfin = v + 5*taille_case/8;

        ua = ufin - 2;
        ub = ufin + taille_case/5;
        uc = ufin + taille_case/5;

        va = vfin;
        vb = vfin - taille_case/5;
        vc = vfin + taille_case/5;
    }
    int epaisseur = taille_case/10;
    drawLine(udeb, vdeb, ufin, vfin, couleur_int_vers_color.at(couleur),epaisseur);
    int coord_triangle[6] = {ua, va, ub, vb, uc, vc};
    fillPoly(coord_triangle, 3, couleur_int_vers_color.at(couleur));
};

void trace_porte_sortie(int x, int y, int taille_case, int couleur) {
    int u = x;
    int v = y;
    int demi = taille_case/2;

    // planche de porte
    fillRect(u, v + demi, taille_case, demi, ORANGE);
    fillCircle(u + demi, v + demi, demi-1, ORANGE);

    // poignée
    fillCircle(u + 3*taille_case/4, v + 3*taille_case/5, taille_case/10, couleur_int_vers_color.at(couleur)); // La poignée indique la couleur de la sortie...
}

void trace_saut(int x, int y, int taille_case) {
    int u = x;
    int v = y;

    // base de la fleche
    int ua = u + taille_case/7 + 5*taille_case/28;
    int eu = 7*taille_case/18;

    int va = v + taille_case/9 + 7*taille_case/18;
    int ev = 5*taille_case/14;

    fillRect(ua, va, eu, ev, PURPLE);

    // triangle de la fleche
    int ub = u + taille_case/7;
    int uc = u + taille_case/2;
    int ud = u + 6*taille_case/7;

    int vb = v + taille_case/9 + 7*taille_case/18;
    int vc = v + taille_case/9;
    int vd = v + taille_case/9 + 7*taille_case/18;

    int coord_triangle[6] = {ub, vb, uc, vc, ud, vd};
    fillPoly(coord_triangle, 3, PURPLE);
}

void trace_retour_arriere(int x, int y, int taille_case) {
    int u = x;
    int v = y;
    int epaisseur = taille_case/10;

    // fleche vers la droite

    int u1deb = u + taille_case/4;
    int v1deb = v + taille_case/3;
    int u1fin = u + 3*taille_case/4;
    int v1fin = v + taille_case/3;

    int u1a = u1fin + 1;
    int u1b = u1fin - taille_case/6;
    int u1c = u1fin - taille_case/6;

    int v1a = v1fin;
    int v1b = v1fin - taille_case/4;
    int v1c = v1fin + taille_case/4;


    drawLine(u1deb, v1deb, u1fin, v1fin, PURPLE, epaisseur);
    int coord_triangle1[6] = {u1a, v1a, u1b, v1b, u1c, v1c};
    fillPoly(coord_triangle1, 3, PURPLE);

    // fleche vers la gauche

    int u2deb = u + 3*taille_case/4;
    int v2deb = v + 2*taille_case/3;
    int u2fin = u + taille_case/4;
    int v2fin = v + 2*taille_case/3;

    int u2a = u2fin - 1;
    int u2b = u2fin + taille_case/6;
    int u2c = u2fin + taille_case/6;

    int v2a = v2fin;
    int v2b = v2fin - taille_case/4;
    int v2c = v2fin + taille_case/4;


    drawLine(u2deb, v2deb, u2fin, v2fin, PURPLE, epaisseur);
    int coord_triangle2[6] = {u2a, v2a, u2b, v2b, u2c, v2c};
    fillPoly(coord_triangle2, 3, PURPLE);
}

void trace_pic(int x, int y, int k, int taille_case, int couleur){

    int u = x;
    int v = y;
    int demi = taille_case/2;

    int ua = u;
    int ub = u + demi;
    int uc = u + taille_case;
    int ud = u + taille_case;
    int ue = u + taille_case;
    int uf = u + demi;
    int ug = u;
    int uh = u;

    int va = v + taille_case;
    int vb = v + taille_case;
    int vc = v + taille_case;
    int vd = v + demi;
    int ve = v;
    int vf = v;
    int vg = v;
    int vh = v + demi;

    Color color = couleur_int_vers_color.at(couleur);

    if (k == pic_bas){
        int liste_points[6] = {ua, va, uc, vc, uf, vf};
        fillPoly(liste_points, 3, color);
    }

    else if (k == pic_droite){
        int liste_points[6] = {uc, vc, ue, ve, uh, vh};
        fillPoly(liste_points, 3, color);
    }

    else if (k == pic_haut){
        int liste_points[6] = {ug, vg, ue, ve, ub, vb};
        fillPoly(liste_points, 3, color);
    }

    else{
        int liste_points[6] = {ug, vg, ua, va, ud, vd};
        fillPoly(liste_points, 3, color);
    }


}

void trace_lave(int x, int y, int taille_case, int bloc){
    if (bloc == lave_totale) fillRect(x, y, taille_case, taille_case, ORANGE);
    else{
        fillRect(x, y+taille_case, taille_case, -0.6666 * taille_case, ORANGE);
    }
}

void trace_etoile(int x, int y, int taille_case){

    int demi = taille_case/2;
    int h = int (0.75*float(taille_case));

    int liste_1[6] = {x + demi, y, x, y + h, x + taille_case, y + h};
    fillPoly(liste_1, 3, YELLOW); // Premier triangle

    int liste_2[6] = {x, y + taille_case - h, x + demi, y + taille_case, x + taille_case, y + taille_case - h};
    fillPoly(liste_2, 3, YELLOW); // Deuxieme triangle
}

// ========== Fin gaphismes ==========

void dessineCase (int x, int y, int taille_case, int bloc, int couleur){

    if (bloc == vide) efface_bloc(x, y, taille_case); // Il n'y a rien

    else if (bloc == mur_non_modif) trace_bloc(x, y, taille_case, couleur);

    else if (bloc == mur_modif) trace_bloc_modif(x, y, taille_case); // On représente pour l'instant les blocs modifiables en violet

    else if (est_dans(bloc, portes_entree)){
        efface_bloc(x, y, taille_case);
        trace_porte_entree(x, y, bloc, taille_case, couleur);
    }

    else if (bloc == porte_sortie){
        efface_bloc(x, y, taille_case);
        trace_porte_sortie(x, y, taille_case, couleur);
    }

    else if (est_dans(bloc, effets_couleur)){
            efface_bloc(x, y, taille_case);
            contour_bloc(x, y, taille_case);
            fillCircle(x+taille_case/2, y+taille_case/2, taille_case/3, couleur_int_vers_color.at(bloc));
        }

    else if (bloc == saut){
        efface_bloc(x, y, taille_case);
        contour_bloc(x, y, taille_case);
        trace_saut(x, y, taille_case);
    }

    else if (bloc == retour_arriere){
        efface_bloc(x, y, taille_case);
        contour_bloc(x, y, taille_case);
        trace_retour_arriere(x, y, taille_case);
    }

    else if ( est_dans(bloc, pics) ){
        efface_bloc(x, y, taille_case);
        trace_pic (x, y, bloc, taille_case, couleur);
    }

    else if ( est_dans(bloc, laves) ){
        efface_bloc(x, y, taille_case);
        trace_lave(x, y, taille_case, bloc);
    }

    else if (bloc == etoile){
        efface_bloc(x, y, taille_case);
        trace_etoile(x, y, taille_case);
    }
}

void Map::drawCase(int x, int y, int taille_case) const{

    int bloc = grille_blocs(x,y);
    int couleur = grille_couleurs(x, y);
    dessineCase(x*taille_case, y*taille_case, taille_case, bloc, couleur);

}

void Map::efface_etoiles_collectees(int j, int i, int taille_case, const Personnage &perso) const{

    int bloc = grille_blocs(j,i);
    IntPoint2 point = {j, i};

    if (       bloc == etoile
            && est_dans(point, perso.Liste_etoiles_collectees) ){

        efface_bloc(j*taille_case, i*taille_case, taille_case);
    }
}

void Map::affiche_tout(int taille_case) const{ // Affiche la map partout
    for (int j=0; j<L; j++){
        for (int i=0; i<H; i++){
            drawCase(j, i, taille_case);
        }
    }
}

void Map::affiche_tout(int taille_case, const Personnage &perso) const{ // Affiche la map partout en tenant en compte du passage du personnage
    for (int j=0; j<L; j++){
        for (int i=0; i<H; i++){
            drawCase(j, i, taille_case);
            efface_etoiles_collectees(j, i, taille_case, perso);
        }
    }
}

void Map::affiche(int taille_case, const Personnage &perso) const{ // Rafraichit la map autour du joueur seulement
    int x_p = floor(perso.get_x());
    int y_p = floor(perso.get_y());

    for (int j=x_p - 1; j<x_p + 3  && j<L && j>-1; j++){
        for (int i=y_p - 1; i<y_p + 3 && i<H && i>-1; i++){
            drawCase(j, i, taille_case);
            efface_etoiles_collectees(j, i, taille_case, perso);
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
        for(int n=0; n<k; n++){ // Boucle: on lit tous les niveaux avant le niveau k
            string map_name;
            flux >> map_name;
            int a,b;
            flux >> a;
            flux >> b;
            for (int x=0; x<L; x++){
                for (int y=0; y<H; y++){
                    int valeur = get_case(x, y);
                    flux >> valeur;
                }
            }
            for (int x=0; x<L; x++){
                for (int y=0; y<H; y++){
                    int valeur = get_couleur(x, y);
                    flux >> valeur;
                }
            }
        }

        string map_name;
        flux >> map_name;
        flux >> H;
        flux >> L;

        // Initialisation de la map
        grille_blocs = MultiArray<int, 2> (L, H);
        grille_blocs.fill(vide);
        grille_couleurs = MultiArray<int, 2> (L, H);
        grille_couleurs.fill(neutre);

        for (int x=0; x<L; x++){
            for (int y=0; y<H; y++){
                int valeur = get_case(x, y);
                flux >> valeur;
                grille_blocs(x, y) = valeur;
            }
        }
        for (int x=0; x<L; x++){
            for (int y=0; y<H; y++){
                int valeur = get_couleur(x, y);
                flux >> valeur;
                grille_couleurs(x, y) = valeur;
            }
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}

void Map::sauvegarder(Window w, string nom_map){

    closeWindow(w);
    string const nomFichier(srcPath("Niveaux.txt"));
    ofstream flux(nomFichier.c_str(), ios::app); // flux d'ajout en fin de fichier

    if(flux)
    {
        flux << nom_map << endl;
        flux << H << " ";
        flux << L << endl;
        for (int x=0; x<L; x++){
            for (int y=0; y<H; y++){
                flux << grille_blocs(x, y) << " "; // Ecriture de grille_blocs
            }
        }
        flux << endl;
        for (int x=0; x<L; x++){
            for (int y=0; y<H; y++){
                flux << grille_couleurs(x, y) << " "; // Ecriture de grille_couleurs
            }
        }
        flux << endl;
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}





