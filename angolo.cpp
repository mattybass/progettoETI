#include "angolo.h"

ostream& operator << (ostream& os,const Angolo& _angolo){
    return os<<"[Azimut: "<<_angolo.azimut<<" Zenit: "<<_angolo.zenit<<"]";
}
