#include "map.h"
#include "correspondance.h"
#include "personnage.h"
#include "niveaux.h"
#include "graphismes.h"

Map::Map(){
}

Map::Map(string nom_map, int h, int l)
{
    nom = nom_map;
    H = h; // Hauteur
    L = l; // Longueur
    grille_blocs = MultiArray<int, 2> (L, H);
    grille_blocs.fill(vide);
    grille_couleurs = MultiArray<int, 2> (L, H);
    grille_couleurs.fill(neutre);
}

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

string Map::get_nom() const {
    return nom;
}

int Map::get_H() const{
    return H;
}

int Map::get_L() const{
    return L;
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

void Map::charger(int k, const string niveau){ // L'entier k indique la map a charger (ainsi reperee par sa position dans le fichier .txt)
    string const nomFichier(stringSrcPath( niveau ));
    ifstream flux(nomFichier); // Flux de lecture du fichier .txt contenant les codes des maps

    if(flux) // Si le fichier est bien lu
    {
        for(int n=0; n<k; n++){ // Boucle: on lit tous les niveaux avant le niveau k
            string map_name;
            flux >> map_name;
            int h,l;
            flux >> h;
            flux >> l;
            for (int x=0; x<l; x++){
                for (int y=0; y<h; y++){
                    int valeur;
                    flux >> valeur;
                }
            }
            for (int x=0; x<l; x++){
                for (int y=0; y<h; y++){
                    int valeur;
                    flux >> valeur;
                }
            }
        }

        flux >> nom;
        flux >> H;
        flux >> L;

        // Initialisation de la map
        grille_blocs = MultiArray<int, 2> (L, H);
        grille_blocs.fill(vide);
        grille_couleurs = MultiArray<int, 2> (L, H);
        grille_couleurs.fill(neutre);

        for (int x=0; x<L; x++){
            for (int y=0; y<H; y++){
                int valeur;
                flux >> valeur;
                grille_blocs(x, y) = valeur;
            }
        }
        for (int x=0; x<L; x++){
            for (int y=0; y<H; y++){
                int valeur;
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

void Map::sauvegarder(const string niveau) const{
    string const nomFichier(stringSrcPath((niveau)));
    ofstream flux(nomFichier, ios::app); // flux d'ajout en fin de fichier

    if(flux)
    {
        flux << nom << endl;
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

void Map::sauvegarder_et_ecraser(int num_map, const string niveau, int nb_niveaux) const{

    if (num_map == nb_niveaux-1){
        efface_niveau (num_map, nb_niveaux, niveau);
        sauvegarder(niveau); // On sauvegarde le niveau a la place num_map
        return;
    }
    // On conserve les niveaux avant num_map
    vector <Map> Liste_maps1;
    for (int i=0; i<num_map; i++){
        Map map;
        map.charger(i, niveau);
        Liste_maps1.push_back(map);
    }

    // On conserve les niveaux apres num_map
    vector <Map> Liste_maps2;
    for (int i=num_map+1; i<nb_niveaux; i++){
        Map map;
        map.charger(i, niveau);
        Liste_maps2.push_back(map);
    }
    efface_tous_niveaux(niveau); // On efface tout

    // On reecrit les niveaux conserves
    for (unsigned int m=0; m<Liste_maps1.size(); m++){
        Liste_maps1[m].sauvegarder(niveau);
    }
    sauvegarder(niveau); // On sauvegarde le niveau a la place num_map

    // On reecrit les niveaux conserves
    for (unsigned int m=0; m<Liste_maps2.size(); m++){
        Liste_maps2[m].sauvegarder(niveau);
    }


}
