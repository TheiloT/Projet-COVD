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
