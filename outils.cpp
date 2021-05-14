#include "outils.h"

Point::Point(){
}

Point::Point(float x1, float y1){
    x = x1;
    y = y1;
}

bool est_dans (int num, vector<int> liste){
    return *find(liste.begin(), liste.end()-1, num) == num;
}
