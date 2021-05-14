#pragma once

#include <Imagine/Images.h>
using namespace Imagine;

#include<iostream>
#include <fstream>

#include "algorithm"
#include <vector>
using namespace std;


class Point
{
public:
    float x;
    float y;

    Point();
    Point(float x, float y);

};

bool est_dans (int num, vector<int> liste); // Renvoie true si num est dans la liste false sinon

