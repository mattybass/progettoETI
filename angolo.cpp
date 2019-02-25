#include "angolo.h"

Angolo::Angolo(Coordinata& _c1,Coordinata& _c2,Coordinata& _c3){
    azimut = angolo_azimut(_c1, _c2, _c3);
    zenit= angolo_zenit(_c1,_c2_c3);
}

double Angolo::get_zenit()const{ return zenit; }
double Angolo::get_azimut()const{ return azimut; }

ostream& operator << (ostream& os,const Angolo& _angolo){
    return os<<"[Azimut: "<<_angolo.azimut<<" Zenit: "<<_angolo.zenit<<"]";
}
