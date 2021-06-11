#include "niveaux.h"
#include "map.h"

void efface_tous_niveaux(const string niveau){ // Efface tous les niveaux dans le fichier .txt en argument

    string const nomFichier(stringSrcPath(niveau));
    ofstream fichier(nomFichier ); // flux d'ajout en fin de fichier
}

void efface_niveau (int k, int nb_niveaux, const string niveau){
    // Pour effacer un niveau en particulier, on sauvegarde tous les niveaux sauf celui à effacer dans un vecteur,
    // on efface tout dans le .txt et on reecrit tous les niveaux du vecteur dans le fichier.
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
