#ifndef __COORDINATA_H__
#define __COORDINATA_H__

#include <iostream>
#include <cstdlib>
#include <climits>
#include <cmath>
#define PI 3.14159265

using namespace std;

class Coordinata{
	private:
		double x;
		double y;
		double z;
	public:
		Coordinata(double _x,double _y,double _z);
		Coordinata(); //Inizializza con un numero molto grande per potere essere identificato come valore da non considerare
		double get_x()const; //Ritorna la coordinata x
		double get_y()const; //Ritorna la coordinata y
		double get_z()const; //Ritorna la coordinata z
    
		friend ostream& operator << (ostream& os,const Coordinata& _punto);
};

ostream& operator << (ostream& os,const Coordinata& _punto);

#endif
