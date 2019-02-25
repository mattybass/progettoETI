#include "Frame.h"

Frame::Frame(int _numeroframe){
    numeroframe=_numeroframe;
}

int Frame::get_numeroframe()const{
    return numeroframe;
}

Coordinata Frame::get_coordinata(int _numerojoint){
    Coordinata c(0,0,0);
    map<int,Coordinata>::iterator iter=coordinatejoint.find(_numerojoint);
    if(iter!=coordinatejoint.end()){
        c=iter->second;
    }
    return c;
}

map<int,Coordinata>::const_iterator Frame::get_beginiter_cord()const{
    return coordinatejoint.begin();
}
map<int,Coordinata>::const_iterator Frame::get_enditer_cord()const{
    return coordinatejoint.end();
}
map<int,Angolo>::const_iterator Frame::get_beginiter_angolo()const{
    return angolijoint.begin();
}
map<int,Angolo>::const_iterator Frame::get_enditer_angolo()const{
    return angolijoint.end();
}

void Frame::insert_coordinata(int _numerojoint, double _x, double _y, double _z){
    coordinatejoint.insert(pair<int,Coordinata> (_numerojoint, Coordinata(_x,_y,_z)));
}

ostream& operator <<(ostream& os, const Frame& f){
    os<<"Frame: "<<f.numeroframe<<endl;
    map<int,Coordinata>::const_iterator iter;
    for(iter=f.coordinatejoint.begin();iter!=f.coordinatejoint.end();++iter){
        os<<iter->first<<": "<<iter->second<<endl;
    }
    os<<endl;
    map<int,Angolo>::const_iterator iteran;
    for(iteran=f.angolijoint.begin();iteran!=f.angolijoint.end();++iteran){
        os<<iter->first<<": "<<iter->second<<endl;
    }
    return os;
}
    
    
