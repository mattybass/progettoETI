#include "Frame.h"

Frame::Frame(int _numeroframe){
    numeroframe=_numeroframe;
}

int Frame::get_numeroframe()const{
    return numeroframe;
}

map<int, Angolo> Frame::get_angolijoint()const {
	return angolijoint;
}

Coordinata Frame::get_coordinata(int _numerojoint){
    Coordinata c;
    map<int,Coordinata>::const_iterator iter=coordinatejoint.find(_numerojoint);
    if(iter!=coordinatejoint.end()){
        c=iter->second;
    }else{
        cout<<"Errore nel get della Coordinata, joint non trovato"<<endl;
    }
    return c;
}

void Frame::insert_coordinata(int _numerojoint, double _x, double _y, double _z){
    coordinatejoint.insert(pair<int,Coordinata> (_numerojoint, Coordinata(_x,_y,_z)));
}

void Frame::insert_angolo(int _joint,int a,int b,int c){
    map<int,Coordinata>::const_iterator itera;
    map<int,Coordinata>::const_iterator itera2;
    map<int,Coordinata>::const_iterator itera3;
	Coordinata c1,c2,c3;
	
	itera=coordinatejoint.find(a);
	if(itera!=coordinatejoint.end()){
		c1=itera->second;
	}
	itera2=coordinatejoint.find(b);
	if(itera2!=coordinatejoint.end()){
		c2=itera2->second;
	}
	itera3=coordinatejoint.find(c);
	if(itera3!=coordinatejoint.end()){
		c3=itera3->second;
	}

    if(itera!=coordinatejoint.end() && itera2!=coordinatejoint.end() && itera3!=coordinatejoint.end()){
        Angolo a(c1,c2,c3,numeroframe);
		angolijoint.insert(pair<int,Angolo> (_joint,a) );
    }
}

map<int,Coordinata> Frame::get_coordinatejoit()const{
    return coordinatejoint;
}

void Frame::completa_angolo(){
	insert_angolo(3,4,3,2);
	insert_angolo(2,1,2,3);
	insert_angolo(1,2,1,8);
	insert_angolo(5,1,5,6);
	insert_angolo(6,5,6,7);
	insert_angolo(8,1,8,9);
	insert_angolo(11,1,11,12);
	insert_angolo(9,8,9,10);
	insert_angolo(12,11,12,13);
}

ostream& operator <<(ostream& os, const Frame& f){
    os<<"Frame: "<<f.numeroframe<<endl;
    map<int,Coordinata>::const_iterator iter;
	
    for(iter=f.coordinatejoint.begin();iter!=f.coordinatejoint.end();++iter){
        os<<iter->first<<": "<<iter->second<<endl;
    }
    os<<endl;
    
    return os;
}
    
    

void Frame::set_angolo_zenit(int n, double nu){
    map<int,Angolo>::iterator iter;
    iter=angolijoint.find(n);
    if(iter!=angolijoint.end()){
        iter->second.set_zenit(nu);
    }
}

void Frame::set_angolo_azimut(int n, double nu){
    map<int,Angolo>::iterator iter;
    iter=angolijoint.find(n);
    if(iter!=angolijoint.end()){
        iter->second.set_azimut(nu);
    }
}

Angolo Frame::restituisci_angolo(int _angolo)const {
	map<int, Angolo>::const_iterator iter;
	iter = angolijoint.find(_angolo);
	return iter->second;
}
