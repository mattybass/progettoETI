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
		Coordinata(double _x,double _y,double _z){
			x=_x;
			y=_y;
			z=_z;
		}
		double get_x(){
			return x;
		}
		double get_y(){
			return y;
		}
		double get_z(){
			return z;
		}
};


#endif
