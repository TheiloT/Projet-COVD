#include "niveaux.h"
#include "map.h"

void efface_tous_niveaux(const string niveau){ // Efface le Niveaux.txt

    string const nomFichier(stringSrcPath(niveau));
    ofstream fichier(nomFichier ); // flux d'ajout en fin de fichier
}

void efface_niveau (int k, int nb_niveaux, const string niveau){
    vector <Map> Liste_maps;

    for (int i=0; i<nb_niveaux; i++){
        if(i!=k){
            Map map;
            map.charger(i, niveau);
            Liste_maps.push_back(map);
        }
    }

    efface_tous_niveaux(niveau);

    for (int i=0; i<nb_niveaux-1; i++){
        Map map = Liste_maps[i];
        map.sauvegarder(niveau);
    }

}
