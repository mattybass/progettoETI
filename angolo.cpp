#include "angolo.h"
#include "utility.h"

Angolo::Angolo(Coordinata& _c1,Coordinata& _c2,Coordinata& _c3, int _numeroframe){
    azimut = angolo_azimut(_c1, _c2, _c3);
    zenit= angolo_zenit(_c1,_c2,_c3);
    numeroframe=_numeroframe;
}

double Angolo::get_zenit()const{ return zenit; }
double Angolo::get_azimut()const{ return azimut; }
void Angolo::set_zenit(double z) { zenit = z; }
void Angolo::set_azimut(double a) { azimut = a; }
int Angolo::get_numeroframe()const{return numeroframe;}

ostream& operator << (ostream& os,const Angolo& _angolo){
   // return os<<"[Azimut: "<<_angolo.azimut<<" Zenit: "<<_angolo.zenit<<"]";
	return os << _angolo.numeroframe << " " << _angolo.azimut << " " << _angolo.zenit;
}
