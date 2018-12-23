#include <iostream>
#include <cmath>
#include "coordinata.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

double angolo_XZ(Coordinata &c1,Coordinata &c2);
double angolo_XY(Coordinata &c1,Coordinata &c2);
double d_angolo(double &a1,double &a2);

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

double angolo_XY(Coordinata &c1,Coordinata &c2){
	if((c2.get_x()-c1.get_x())==0)
		return 90;
	double m=(c2.get_y()-c1.get_y())/(c2.get_x()-c1.get_x());
	return atan(m)*180/PI;
}

double angolo_XZ(Coordinata &c1,Coordinata &c2){
	if((c2.get_x()-c1.get_x())==0)
		return 90;	
	double m=(c2.get_z()-c1.get_z())/(c2.get_x()-c1.get_x());
	return atan(m)*180/PI;
}

double d_angolo(double &a1,double &a2){
	if(a1>0)
		return 180-a1+a2;
	else
		return 180+a1-a2;
}
