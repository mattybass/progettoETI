#include "angolo.h"



Angolo::Angolo(const Coordinata& c1, const Coordinata& c2, const Coordinata& c3){
    
    
}


ostream& operator << (ostream& os,const Angolo& _angolo){
    return os<<"[Azimut: "<<_angolo.azimut<<" Zenit: "<<_angolo.zenit<<"]";
}
