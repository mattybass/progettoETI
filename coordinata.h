#ifndef __COORDINATA_H__
#define __COORDINATA_H__

#include <iostream>
#include <cstdlib>
#include <cmath>
#define PI 3.14159265
using namespace std;


ostream& operator << (ostream& os,const Cordinata& _punto);
class Coordinata{
	private:
		double x;
		double y;
		double z;
	public:
		Coordinata(double _x,double _y,double _z){
			x=_x;
			y=_y;
			z=_z;
		}
		double get_x()const{
			return x;
		}
		double get_y()const{
			return y;
		}
		double get_z()const{
			return z;
		}
    friend ostream& operator << (ostream& os,const Cordinata& _punto);
};

ostream& operator << (ostream& os,const Cordinata& _punto){
    return os<<"["<<_punto.x<<";"<<_punto.y<<";"<<_punto.z<<"]";
    
}




#endif
