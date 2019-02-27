#include "angolo.h"

Angolo::Angolo(Coordinata& _c1,Coordinata& _c2,Coordinata& _c3, int _frame){
    azimut = angolo_azimut(_c1, _c2, _c3);
    zenit= angolo_zenit(_c1,_c2,_c3);
    frame=_frame;
}

double Angolo::get_zenit()const{ return zenit; }
double Angolo::get_azimut()const{ return azimut; }
int Angolo::get_frame()const{return frame;}

ostream& operator << (ostream& os,const Angolo& _angolo){
    return os<<"[Azimut: "<<_angolo.azimut<<" Zenit: "<<_angolo.zenit<<"]";
}
