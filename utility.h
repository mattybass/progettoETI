#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <map>
#include <list>
#include "coordinata.h"
#define PI 3.14159265
using namespace std;

class Angolo;

double angolo_azimut(Coordinata& c1, Coordinata& c2, Coordinata& c3);//La cordianta c2 deve essere la coordinata in comune alle due rette.
double angolo_zenit(Coordinata& c1, Coordinata& c2, Coordinata& c3);

double angolo_XY(Coordinata &c1,Coordinata &c2);
double angolo_XZ(Coordinata &c1,Coordinata &c2);

double media_azimut(list<Angolo> _lista); //Calcola la media della lista DI ANGOLO
double media_zenit(list<Angolo> _lista);

double devst_azimut(list<Angolo> _lista);
double devst_zenit(list<Angolo> _lista);



#endif
