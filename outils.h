#pragma once

#include <Imagine/Images.h>
using namespace Imagine;

#include<iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include "algorithm"
#include <vector>
#include <map>
using namespace std;

#include <time.h>

struct Point // Une structure de point, utilisee notamment pour les hitboxes
{
    float x;
    float y;

    Point();
    Point(float x, float y);

};

bool est_dans (int num, vector<int> liste); // Renvoie true si num est dans la liste false sinon
bool est_dans (IntPoint2 p, vector<IntPoint2> liste);

int Clavier(int &x, int &y, bool &clic, bool &clav); // Indique si le joueur clique sur une touche du clavier ou de la souris, et renseigne le cas echeant la position de la souris dans x et y.

void InitRandom();

//Renvoie un entier au hasard entre a et b
int hasard(int a, int b);

Color couleur_au_hasard(); // Renvoie une couleur au hasard

void ecris_dans_la_case(int x, int y, int w, int h, string message, int taille_police, Color couleur=BLACK); // Ecrit au centre du rectangle.
