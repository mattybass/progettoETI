#ifndef __COORDINATA_H__
#define __COORDINATA_H__

#include <iostream>
#include <cstdlib>
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
    double get_x()const;
    double get_y()const;
    double get_z()const;
    
    friend ostream& operator << (ostream& os,const Coordinata& _punto);
};

ostream& operator << (ostream& os,const Coordinata& _punto);




#endif
