#include "outils.h"

Point::Point(){
}

Point::Point(float x1, float y1){
    x = x1;
    y = y1;
}

bool est_dans (int num, vector<int> liste){
    if (liste.size() == 0){
        return false;
    }
    return *find(liste.begin(), liste.end()-1, num) == num;
}

bool est_dans (IntPoint2 p, vector<IntPoint2> liste){
    if (liste.size() == 0){
        return false;
    }
    return *find(liste.begin(), liste.end()-1, p) == p;
}

int Clavier(int &x, int &y, bool &clic, bool &clav) {
    Event e;
    do {
        getEvent(0,e);
        if (e.type==EVT_KEY_ON){
            clav = true;
            return e.key;
        }
        if (e.type==EVT_BUT_ON){
            x = e.pix[0];
            y = e.pix[1];
            clic = true;
            return e.button;

        }
    } while (e.type!=EVT_NONE);
    return 0;
}

void InitRandom()
{
    srand((unsigned int)time(0));
    rand();
}

int hasard(int a, int b)
{
    return a+(rand()%(b-a+1));
}

Color couleur_au_hasard(){
    return Color(hasard(0,255),hasard(0,255),hasard(0,255));
}

void ecris_dans_la_case(int x, int y, int w, int h, string message, int taille_police, Color couleur){
    int dx = int ( (w - taille_police * 0.88*message.size()) /2 ); // Le coefficient 0.88 est choisi empiriquement pour tenir compte du fait que tous les caracteres n'ont pas la meme taille
    int dy = int ( (h - taille_police) /2 );
    drawString(x + dx, y + h - dy, message, couleur, taille_police);
}
