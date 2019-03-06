#ifndef __ANGOLO_H__
#define __ANGOLO_H__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "coordinata.h"
#define PI 3.14159265

using namespace std;

class Angolo{
	private:
		int numeroframe;
		double zenit; //Altezza (Y-Z)
		double azimut; //Posizione (X-Y)
	public:
    Angolo(Coordinata& c1,Coordinata& c2,Coordinata& c3,int _numeroframe); //Costruttore 4 parametri
    double get_zenit()const; //Ritorna l'angolo zenit
    double get_azimut()const; //Ritorna l'angolo azimut
	void set_azimut(double a);
	void set_zenit(double z);
    int get_numeroframe()const; //Ritorna il numero di Frame associato all'angolo
    friend ostream& operator << (ostream& os,const Angolo& _angolo);
};

ostream& operator << (ostream& os,const Angolo& _angolo);





#endif
