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
