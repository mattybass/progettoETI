#include "coordinata.h"

ostream& operator << (ostream& os,const Coordinata& _punto){
    return os<<"["<<_punto.x<<";"<<_punto.y<<";"<<_punto.z<<"]";
    
}
