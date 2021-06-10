#pragma once

#include <Imagine/Images.h>
using namespace Imagine;

#include<iostream>
#include <fstream>
#include <stdio.h>

#include "algorithm"
#include <vector>
#include <map>
using namespace std;

#include <stdlib.h>

#include <time.h>

class Point
{
public:
    float x;
    float y;

    Point();
    Point(float x, float y);

};

bool est_dans (int num, vector<int> liste); // Renvoie true si num est dans la liste false sinon
bool est_dans (IntPoint2 p, vector<IntPoint2> liste);

int Clavier(int &x, int &y, bool &clic, bool &clav);

void InitRandom();

//Renvoit un entier au hasard entre a et b
int hasard(int a, int b);

Color couleur_au_hasard(); // Renvoit une couleur au hasard
