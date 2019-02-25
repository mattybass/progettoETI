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
		double zenit; //Altezza (Y-Z)
		double azimut; //Posizione (X-Y)
	public:
		Angolo(const Coordinata& c1, const Coordinata& c2, const Coordinata& c3){
			
		}
    
    
		double get_zenit()const{
			return zenit;
		}
		double get_azimut()const{
			return azimut;
		}
    
    friend ostream& operator << (ostream& os,const Angolo& _angolo);
};

ostream& operator << (ostream& os,const Angolo& _angolo);





#endif
