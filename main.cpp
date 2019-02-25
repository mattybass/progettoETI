#include <iostream>
#include <cmath>
#include "coordinata.h"
#include "utility.h"
#include "json.hpp"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char** argv) {
	Coordinata A(5,1,0);
	Coordinata B(5,7,1);
	Coordinata C(1,1,1);
	double ABxy=angolo_XY(A,B);
	double ABxz=angolo_XZ(A,B);
	double ACxy=angolo_XY(A,C);
	double ACxz=angolo_XZ(A,C);
	cout<<"RETTA AB:"<<endl;
	cout<<"angolo xy = "<<ABxy<<endl<<"angolo xz = "<<ABxz<<endl;
	cout<<endl<<"RETTA AC:"<<endl;
	cout<<"angolo xy = "<<ACxy<<endl<<"angolo xz = "<<ACxz<<endl;	
	cout<<endl<<"DIFFERENZA:"<<endl;
	cout<<"angolo xy = "<<d_angolo(ABxy,ACxy)<<endl<<"angolo xz = "<<d_angolo(ABxz,ACxz)<<endl;
    

	return 0;
}

