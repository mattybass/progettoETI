#include "coordinata.h"
#include <climits>
Coordinata::Coordinata(double _x,double _y,double _z){
    x=_x;
    y=_y;
    z=_z;
}

Coordinata::Coordinata(){
	x=	1.79769e+308;
	y=	1.79769e+308;
	z=	1.79769e+308;
}

double Coordinata::get_x()const{
    return x;
}

double Coordinata::get_y()const{
    return y;
}

double Coordinata::get_z()const{
    return z;
}

ostream& operator << (ostream& os,const Coordinata& _punto){
    return os<<"["<<_punto.x<<";"<<_punto.y<<";"<<_punto.z<<"]";
    
}
