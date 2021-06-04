#include "Niveaux.h"
#include "map.h"

void efface_tous_niveaux(string niveau){ // Efface le Niveaux.txt

    string const nomFichier(srcPath("Niveaux.txt"));
    ofstream fichier(nomFichier.c_str() ); // flux d'ajout en fin de fichier
}

void efface_niveau (int k, int nb_niveaux, string niveau){
    vector <Map> Liste_maps;

    for (int i=0; i<nb_niveaux && i!=k; i++){
        Map map;
        map.charger(i, niveau);
        Liste_maps.push_back(map);
    }

    efface_tous_niveaux(niveau);

    for (int i=0; i<nb_niveaux-1; i++){
        Map map = Liste_maps[i];
        map.sauvegarder(niveau);
    }

}
