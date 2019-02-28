#include "persona.h"

void Persona::insert_frame(int _numeroframe){
    sequenzaframe.insert(pair<int,Frame> (_numeroframe,Frame(_numeroframe)));
}

void Persona::insert_coordinata(int _numeroframe,int _numerojoint,double _x, double _y, double _z){
    map<int,Frame>::iterator iter;
    iter=sequenzaframe.find(_numeroframe);
    if(iter!=sequenzaframe.end()){
        iter->second.insert_coordinata(_numerojoint, _x, _y, _z);
    }else{
        cout<<"ERRORE: frame non trovato, coordinata non inserita\n";
    }
}


void Persona::completa_angoli(int _numeroframe){
    map<int,Frame>::iterator iter;
    iter=sequenzaframe.find(_numeroframe);
    
    if(iter!=sequenzaframe.end()){
        iter->second.completa_angoli();
    }else{
        cout<<"ERRORE: frame non trovato, angoli non creati\n";
    }
}

void Persona::popola_sequenzaangolo(){
    map<int,Frame>::iterator iter;
    int _numeroframe=0;
    for (iter=sequenzaframe.begin(); iter!=sequenzaframe.end(); ++iter) {
        _numeroframe=iter->first;
        
        //DA FINIRE, DEVO RIPASSARE COME CREARE MAP DI LISTE.
        
        
    }
    
    
    
    
}
